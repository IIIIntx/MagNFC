/*
 * Copyright 2015-2018,2022 NXP
 * NXP confidential.
 * This software is owned or controlled by NXP and may only be used strictly
 * in accordance with the applicable license terms.  By expressly accepting
 * such terms or by downloading, installing, activating and/or otherwise using
 * the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms.  If you do not agree to
 * be bound by the applicable license terms, then you may not retain, install,
 * activate or otherwise use the software.
 */

#include <string.h>
#include <stdlib.h>

#include "board.h"
#include "ndeft2t/ndeft2t.h"
#include "../mods/uarttx/uarttx.h"

/* ------------------------------------------------------------------------- */

#define LOCALE "en" /**< Language used when creating TEXT records. */
#define MIME "nhs31xx/example.ndef" /**< Mime type used when creating MIME records. */

/** The URL will be used in a single-record NDEF message. */
#define MAX_URI_PAYLOAD (254 - NDEFT2T_MSG_OVERHEAD(true, NDEFT2T_URI_RECORD_OVERHEAD(true)))

/**
 * The text and the MIME data are always presented together, in a dual-record NDEF message.
 * Payload length is split evenly between TEXT and MIME.
 */
#define MAX_TEXT_PAYLOAD (254 - (NDEFT2T_MSG_OVERHEAD(true, \
        NDEFT2T_TEXT_RECORD_OVERHEAD(true, sizeof(LOCALE) - 1) + \
        NDEFT2T_MIME_RECORD_OVERHEAD(true, sizeof(MIME) - 1)) / 2))
uint8_t sText[MAX_TEXT_PAYLOAD] = "AABBCCDDEEFFGGHH";

/** @copydoc MAX_TEXT_PAYLOAD */
#define MAX_MIME_PAYLOAD MAX_TEXT_PAYLOAD
__attribute__((aligned(4)))
	uint8_t message[32] = {  // 调整数组大小以容纳20字节数据 + TLV头 + 填充
	    0x03,               // Type: NDEF TLV
	    0x1C,               // Length of NDEF data (30 bytes = 20+8)
	    0xD1,               // NDEF Record Header (MB=1, ME=1, SR=1, TNF=1)
	    0x01,               // Type Length (1 byte)
	    0x18,               // Payload Length, without Record Type(22 bytes = 2-byte lang + 20-byte data)
	    (uint8_t)'T',       // Record Type ("T" for Text)
	    0x02,               // Language Code Length (2 bytes)
	    (uint8_t)'e',       // Language Code ("en")
	    (uint8_t)'n',
	    // 将每个4位数拆分为2字节（共10*2=20字节）
		0xFF,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00,
		0xFE, /* Terminator TLV used to indicate the end of the used NFC memory. */
	    0x00, /* NULL TLV for word alignment */
	};

//debug
bool nfcTransWaitFlag; //False = finished collect data, True = keep on collecting
/* ------------------------------------------------------------------------- */


static volatile bool sButtonPressed = false; /** @c true when the WAKEUP button is pressed on the Demo PCB */
static volatile bool sMsgAvailable = false; /** @c true when a new NDEF message has been written by the tag reader. */
static volatile bool sFieldPresent = true; /** @c true when an NFC field is detected and the tag is selected. */

//static void GenerateNdef_Url(void);
static void GenerateNdef_TextMime(int measurement[5]);
//static void ParseNdef(void);

/* ------------------------------------------------------------------------- */

// 将measurement数组移到全局作用域
int measurement[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};  // 初始化为0

// 添加I2D转换完成标志位
volatile bool i2dConversionComplete = false;

void I2D_IRQHandler(void){
	if ((Chip_I2D_Int_GetRawStatus(NSS_I2D) & I2D_INT_CONVERSION_RDY)) {
		if ((Chip_I2D_ReadStatus(NSS_I2D) & I2D_STATUS_CONVERSION_DONE)) {
		/* No need to check interrupt flag here, as I2D_STATUS_CONVERSION_DONE status flag holds the same meaning. */
		Chip_I2D_Int_ClearRawStatus(NSS_I2D, I2D_INT_CONVERSION_RDY);
		Chip_GPIO_SetPinOutLow(NSS_GPIO, 0, IOCON_PIO0_9);
		i2dConversionComplete = true;  // 设置转换完成标志
		}
	}
}

void NFC_IRQHandler(void){
	Chip_GPIO_SetPinToggle(NSS_GPIO, 0, IOCON_PIO0_2);
	NVIC_DisableIRQ(NFC_IRQn);
    NFC_INT_T status = Chip_NFC_Int_GetRawStatus(NSS_NFC);
    // 添加LED或GPIO指示所有类型的NFC中断
    if (NFC_INT_CMDREAD) {
        nfcTransWaitFlag = false;
        // 将当前采集的数据写入NDEF消息
        GenerateNdef_TextMime(measurement);
        // 重置measurement数组，开始新一轮采集
        for(int i = 0; i < 10; i++) {
            measurement[i] = 0;
        }
        Chip_GPIO_SetPinToggle(NSS_GPIO, 0, IOCON_PIO0_2);
    }

    Chip_NFC_Int_ClearRawStatus(NSS_NFC, status);
    NVIC_EnableIRQ(NFC_IRQn);
}
/**
 * Called under interrupt.
 * @see NDEFT2T_FIELD_STATUS_CB
 * @see pNdeft2t_FieldStatus_Cb_t
 */
void App_FieldStatusCb(bool status)
{
//    if (status) {
//        LED_On(LED_RED);
//    }
//    else {
//        LED_Off(LED_RED);
//    }
    sFieldPresent = status; /* Handled in main loop */
}

/**
 * Called under interrupt.
 * @see NDEFT2T_MSG_AVAILABLE_CB
 * @see pNdeft2t_MsgAvailable_Cb_t
 */
void App_MsgAvailableCb(void)
{
    sMsgAvailable = true; /* Handled in main loop */
}

/* ------------------------------------------------------------------------- */

/** Generates a dual-record NDEF message containing a TEXT and a MIME record, and copies it to the NFC shared memory. */
static void GenerateNdef_TextMime(int measurement[10])
{
    // 指向message中数据部分的起始位置（跳过TLV头和语言代码）
    uint8_t *data_ptr = &message[10];  // 从第9字节开始（下标8）

    // 将每个4位数拆分为高2位和低2位，存入message
    for (int i = 0; i < 10; i++) {
        data_ptr[2*i]   = (measurement[i] / 100) & 0xFF;  // 高2位（如12→0x0C）
        data_ptr[2*i+1] = (measurement[i] % 100) & 0xFF;  // 低2位（如34→0x22）
    }
	ASSERT(NFC_SHARED_MEM_BYTE_SIZE >= sizeof(message));

	if (Chip_NFC_WordWrite(NSS_NFC, (uint32_t*)NFC_SHARED_MEM_START, (uint32_t*)message, sizeof(message) / 4)) {
		/* Success. The message can now be read by a PCD (Proximity Coupled Device) like a USB NFC read or a phone. */
	}
	Chip_GPIO_SetPinToggle(NSS_GPIO, 0, IOCON_PIO0_1);
}

/* ------------------------------------------------------------------------- */

int main(void)
{
    Board_Init();
    NDEFT2T_Init();
//    UartTx_Init();
    int i, j;
    Chip_Clock_System_SetClockFreq(1 * 1000 * 1000);
    Chip_SysCon_Peripheral_DisablePower(SYSCON_PERIPHERAL_POWER_TSEN);

    //NFC interrupt
    NVIC_EnableIRQ(NFC_IRQn);
    Chip_NFC_Int_SetEnabledMask(NSS_NFC, NFC_INT_TARGETREAD);

    //debug pin
    Chip_IOCON_SetPinConfig(NSS_IOCON, IOCON_PIO0_9, IOCON_FUNC_0 | IOCON_I2CMODE_PIO);
    Chip_IOCON_SetPinConfig(NSS_IOCON, IOCON_PIO0_1, IOCON_FUNC_0 | IOCON_I2CMODE_PIO);
    Chip_IOCON_SetPinConfig(NSS_IOCON, IOCON_PIO0_2, IOCON_FUNC_0 | IOCON_I2CMODE_PIO);
    Chip_GPIO_SetPinDIROutput(NSS_GPIO, 0, IOCON_PIO0_9);
    Chip_GPIO_SetPinDIROutput(NSS_GPIO, 0, IOCON_PIO0_1);
    Chip_GPIO_SetPinDIROutput(NSS_GPIO, 0, IOCON_PIO0_2);
    Chip_GPIO_SetPinOutHigh(NSS_GPIO, 0, IOCON_PIO0_9);
	Chip_GPIO_SetPinOutLow(NSS_GPIO, 0, IOCON_PIO0_9);
	Chip_GPIO_SetPinOutHigh(NSS_GPIO, 0, IOCON_PIO0_1);
	Chip_GPIO_SetPinOutLow(NSS_GPIO, 0, IOCON_PIO0_1);
	Chip_GPIO_SetPinOutHigh(NSS_GPIO, 0, IOCON_PIO0_2);
	Chip_GPIO_SetPinOutLow(NSS_GPIO, 0, IOCON_PIO0_2);


    Chip_ADCDAC_Init(NSS_ADCDAC0);
    Chip_ADCDAC_SetMuxDAC(NSS_ADCDAC0, ADCDAC_IO_ANA0_0);
    Chip_ADCDAC_SetModeDAC(NSS_ADCDAC0, ADCDAC_CONTINUOUS);
    Chip_ADCDAC_SetModeADC(NSS_ADCDAC0, ADCDAC_SINGLE_SHOT);
    Chip_ADCDAC_SetInputRangeADC(NSS_ADCDAC0, ADCDAC_INPUTRANGE_WIDE);
    Chip_IOCON_SetPinConfig(NSS_IOCON, IOCON_ANA0_0, IOCON_FUNC_1);
    Chip_ADCDAC_WriteOutputDAC(NSS_ADCDAC0, 1200);
    Chip_IOCON_SetPinConfig(NSS_IOCON, IOCON_ANA0_4, IOCON_FUNC_1); /* Set pin function to analog */
    Chip_I2D_Init(NSS_I2D);
	Chip_I2D_Setup(NSS_I2D, I2D_SINGLE_SHOT, I2D_SCALER_GAIN_10_1, I2D_CONVERTER_GAIN_LOW, 3);
	Chip_I2D_SetMuxInput(NSS_I2D, I2D_INPUT_ANA0_4);
	Chip_I2D_Int_SetEnabledMask(NSS_I2D,I2D_INT_CONVERSION_RDY);
	NVIC_EnableIRQ(I2D_IRQn);
	Chip_Clock_System_BusyWait_ms(10);

	// 设置中断优先级
    NVIC_SetPriority(I2D_IRQn, 0);  // 设置I2D中断为最高优先级
    NVIC_SetPriority(NFC_IRQn, 1);  // 设置NFC中断为次高优先级

    int i2dTotalValue;
    int i2dNativeValue;

	for (;;)
	{
		for(i=0;i<10;i++){
			for(j=0;j<5;j++){
				i2dConversionComplete = false;  // 重置转换完成标志
				Chip_I2D_Start(NSS_I2D);
				Chip_GPIO_SetPinOutHigh(NSS_GPIO, 0, IOCON_PIO0_9);
				Chip_PMU_PowerMode_EnterSleep();
				
				// 等待I2D转换完成
				while(!i2dConversionComplete) {
					__WFI();  // 等待中断
				}
				
				i2dNativeValue = Chip_I2D_GetValue(NSS_I2D);
				i2dTotalValue += Chip_I2D_NativeToPicoAmpere(i2dNativeValue, I2D_SCALER_GAIN_10_1, I2D_CONVERTER_GAIN_LOW, 3)/100;
			}

			// 每个元素递增
			//	 UART print to give out data
//			measurement[i] = i2dTotalValue/5;
			measurement[i] = (measurement[i] + i*100) % 10000;  // 限制在0-9999范围内
			i2dTotalValue = 0;
//			UartTx_Printf("%d\r\n", measurement[i]);
//			UartTx_DeInit();
		}

		// 不再在这里生成NDEF消息，而是在NFC中断中处理

	}

}
