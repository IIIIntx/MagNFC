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
static const uint8_t sUrl[MAX_URI_PAYLOAD + 1 /* NUL */] = "nxp.com/NTAGSMARTSENSOR";

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
static uint8_t sBytes[MAX_MIME_PAYLOAD] = {0, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE};

/* ------------------------------------------------------------------------- */

/**
 * Used to determine which NDEF message must be generated.
 * - @c true: generate a single-record NDEF message containing a URL.
 * - @c false: generate a dual-record NDEF message containing a TEXT and a MIME record.
 */
static bool sState;

static volatile bool sButtonPressed = false; /** @c true when the WAKEUP button is pressed on the Demo PCB */
static volatile bool sMsgAvailable = false; /** @c true when a new NDEF message has been written by the tag reader. */
static volatile bool sFieldPresent = true; /** @c true when an NFC field is detected and the tag is selected. */

static void GenerateNdef_Url(void);
static void GenerateNdef_TextMime(int measurement[5]);
static void ParseNdef(void);

/* ------------------------------------------------------------------------- */

/**
 * Handler for PIO0_0 / WAKEUP pin.
 * Overrides the WEAK function in the startup module.
 */
void PIO0_IRQHandler(void)
{
    Chip_GPIO_ClearInts(NSS_GPIO, 0, 1);
    sButtonPressed = true; /* Handled in main loop */
}

/**
 * Called under interrupt.
 * @see NDEFT2T_FIELD_STATUS_CB
 * @see pNdeft2t_FieldStatus_Cb_t
 */
void App_FieldStatusCb(bool status)
{
    if (status) {
        LED_On(LED_RED);
    }
    else {
        LED_Off(LED_RED);
    }
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

/** Generates a single-record NDEF message containing a URL, and copies it to the NFC shared memory. */
static void GenerateNdef_Url(void)
{
    uint8_t instance[NDEFT2T_INSTANCE_SIZE];
    uint8_t buffer[NFC_SHARED_MEM_BYTE_SIZE ];
    NDEFT2T_CREATE_RECORD_INFO_T recordInfo = {.pString = NULL /* don't care */,
                                               .shortRecord = true,
                                               .uriCode = 0x01 /* "http://www." */};
    NDEFT2T_CreateMessage(instance, buffer, NFC_SHARED_MEM_BYTE_SIZE, true);
    if (NDEFT2T_CreateUriRecord(instance, &recordInfo)) {
        if (NDEFT2T_WriteRecordPayload(instance, sUrl, (int)strlen((char *)sUrl))) {
            NDEFT2T_CommitRecord(instance);
        }
    }
    NDEFT2T_CommitMessage(instance); /* Copies the generated message to NFC shared memory. */
}

/** Generates a dual-record NDEF message containing a TEXT and a MIME record, and copies it to the NFC shared memory. */
static void GenerateNdef_TextMime(int measurement[5])
{
	int j;
    uint8_t instance[NDEFT2T_INSTANCE_SIZE];
    uint8_t buffer[NFC_SHARED_MEM_BYTE_SIZE ];
    NDEFT2T_CREATE_RECORD_INFO_T textRecordInfo = {.pString = (uint8_t *)"en" /* language code */,
                                                   .shortRecord = true,
                                                   .uriCode = 0 /* don't care */};
//    NDEFT2T_CREATE_RECORD_INFO_T mimeRecordInfo = {.pString = (uint8_t *)MIME /* mime type */,
//                                                   .shortRecord = true,
//                                                   .uriCode = 0 /* don't care */};
    NDEFT2T_CreateMessage(instance, buffer, NFC_SHARED_MEM_BYTE_SIZE, true);
//    snprintf((char*)sText, MAX_TEXT_PAYLOAD, "AA %d%d%d%d%d",
    for (j = 0; j < 5; j++) {
    		int value = measurement[j];
            sText[j * 2 + 3] = (value / 100) & 0xFF;  // Get the high byte
            sText[j * 2 + 4] = (value % 100) & 0xFF;  // Get the low byte
        }
    if (NDEFT2T_CreateTextRecord(instance, &textRecordInfo)) {
        if (NDEFT2T_WriteRecordPayload(instance, sText, sizeof(sText) - 1 /* exclude NUL char */)) {
            NDEFT2T_CommitRecord(instance);
        }
    }
//    if (NDEFT2T_CreateMimeRecord(instance, &mimeRecordInfo)) {
//        if (NDEFT2T_WriteRecordPayload(instance, sBytes, sizeof(sBytes))) {
//            NDEFT2T_CommitRecord(instance);
//        }
//    }
    NDEFT2T_CommitMessage(instance); /* Copies the generated message to NFC shared memory. */
}

/** Parses the NDEF message in the NFC shared memory, and copies the TEXT and MIME payloads. */
static void ParseNdef(void)
{
    uint8_t instance[NDEFT2T_INSTANCE_SIZE];
    uint8_t buffer[NFC_SHARED_MEM_BYTE_SIZE];
    NDEFT2T_PARSE_RECORD_INFO_T recordInfo;
    int len = 0;
    uint8_t *pData = NULL;

    if (NDEFT2T_GetMessage(instance, buffer, NFC_SHARED_MEM_BYTE_SIZE)) {
        while (NDEFT2T_GetNextRecord(instance, &recordInfo) != false) {
            pData = (uint8_t *)NDEFT2T_GetRecordPayload(instance, &len);
            switch (recordInfo.type) {
                case NDEFT2T_RECORD_TYPE_TEXT:
                    if ((size_t)len <= MAX_TEXT_PAYLOAD) {
                        memcpy(sText, pData, (size_t)len);
                        memset(sText + len, 0, MAX_TEXT_PAYLOAD - (size_t)len);
                    }
                    break;
                case NDEFT2T_RECORD_TYPE_MIME:
                    if ((size_t)len <= MAX_MIME_PAYLOAD) {
                        memcpy(sBytes, pData, (size_t)len);
                        memset(sBytes + len, 0, MAX_MIME_PAYLOAD - (size_t)len);
                    }
                    break;
                default:
                    /* ignore */
                    break;
            }
        }
    }
}

/* ------------------------------------------------------------------------- */

int main(void)
{
    Board_Init();
    NDEFT2T_Init();
    UartTx_Init();
    int i;
//    Chip_IOCON_Init(NSS_IOCON);

    Chip_IOCON_SetPinConfig(NSS_IOCON, IOCON_ANA0_0, IOCON_FUNC_1);
    Chip_ADCDAC_Init(NSS_ADCDAC0);
    Chip_ADCDAC_SetMuxDAC(NSS_ADCDAC0, ADCDAC_IO_ANA0_0);
    Chip_ADCDAC_SetModeDAC(NSS_ADCDAC0, ADCDAC_CONTINUOUS);
    Chip_ADCDAC_WriteOutputDAC(NSS_ADCDAC0, 4096);

    int i2dValue;
	int i2dNativeValue;
	int measurement[5];


	Chip_IOCON_SetPinConfig(NSS_IOCON, IOCON_ANA0_4, IOCON_FUNC_1); /* Set pin function to analog */
	Chip_I2D_Init(NSS_I2D);
	Chip_I2D_Setup(NSS_I2D, I2D_SINGLE_SHOT, I2D_SCALER_GAIN_100_1, I2D_CONVERTER_GAIN_LOW, 10);
	Chip_I2D_SetMuxInput(NSS_I2D, I2D_INPUT_ANA0_4);
	for (;;)
	{
		for(i;i<5;i++){
			Chip_I2D_Start(NSS_I2D);
			while (!(Chip_I2D_ReadStatus(NSS_I2D) & I2D_STATUS_CONVERSION_DONE)) {
				; /* wait */
			}
			i2dNativeValue = Chip_I2D_GetValue(NSS_I2D);
			i2dValue = Chip_I2D_NativeToPicoAmpere(i2dNativeValue, I2D_SCALER_GAIN_100_1, I2D_CONVERTER_GAIN_LOW, 10);

			//	 UART print to give out data

//			UartTx_Printf("%d\r\n", i2dValue);
	//		UartTx_DeInit();
			measurement[i] = i2dValue/100000;
		}
		if (sFieldPresent) { /* Update the NDEF message once when there is an NFC field */
			GenerateNdef_TextMime(measurement);
			/* Update the payloads for the next message. */
			sText[0] = (uint8_t)((sText[0] == '9') ? '0' : (sText[0] + 1));
			sBytes[0]++;
		}
		i = 0;




//	while (sFieldPresent) {
//		if (sMsgAvailable) {
//			sMsgAvailable = false;
//			ParseNdef();
//		}
//		Chip_Clock_System_BusyWait_ms(10);
//	}
	}

//    Chip_IOCON_SetPinConfig(NSS_IOCON, IOCON_ANA0_0, IOCON_FUNC_1);
//    Chip_ADCDAC_Init(NSS_ADCDAC0);
//	Chip_ADCDAC_SetMuxADC(NSS_ADCDAC0, ADCDAC_IO_ANA0_0);
//	Chip_ADCDAC_SetInputRangeADC(NSS_ADCDAC0, ADCDAC_INPUTRANGE_WIDE);
//	Chip_ADCDAC_SetModeADC(NSS_ADCDAC0, ADCDAC_SINGLE_SHOT);
//	int adcInput=99;
//
//    NVIC_EnableIRQ(PIO0_IRQn); /* PIO0_IRQHandler is called when this interrupt fires. */
//    Chip_GPIO_EnableInt(NSS_GPIO, 0, 1);
//
//
//    for (;;) {
//    	int vMeasure;
//		// Toggle LED
//		LED_Toggle(LED_RED);
//
////		// Read out ADC
////		Chip_ADCDAC_StartADC(NSS_ADCDAC0);
////		while (!(Chip_ADCDAC_ReadStatus(NSS_ADCDAC0) & ADCDAC_STATUS_ADC_DONE)) { /* wait */ }
////		adcInput = Chip_ADCDAC_GetValueADC(NSS_ADCDAC0);
////		vMeasure = ((float)adcInput*1.6)/4096;
//
//        if (sButtonPressed) {
//            sButtonPressed = false;
//            sState = !sState; /* Switch between generating URL and TEXT+MIME. */
//        }
//        if (sFieldPresent) { /* Update the NDEF message once when there is an NFC field */
//            if (sState) {
//                GenerateNdef_Url();
//            }
//            else {
//                GenerateNdef_TextMime(vMeasure);
//                /* Update the payloads for the next message. */
//                sText[0] = (uint8_t)((sText[0] == '9') ? '0' : (sText[0] + 1));
//                sBytes[0]++;
//            }
//        }
//        while (sFieldPresent) {
//            if (sMsgAvailable) {
//                sMsgAvailable = false;
//                ParseNdef();
//            }
//            Chip_Clock_System_BusyWait_ms(10);
//        }
//    }
//
////    while (1) {
////            // Toggle LED
////            LED_Toggle(LED_RED);
////
////            // Read out ADC
////            Chip_ADCDAC_StartADC(NSS_ADCDAC0);
////            while (!(Chip_ADCDAC_ReadStatus(NSS_ADCDAC0) & ADCDAC_STATUS_ADC_DONE)) { /* wait */ }
////            adcInput = Chip_ADCDAC_GetValueADC(NSS_ADCDAC0);
////
////            // UART print to give out data
////            UartTx_Init();
////            UartTx_Printf("ADC:%d\n", adcInput);
////            UartTx_DeInit();
////
////            // Pause
////            Chip_Clock_System_BusyWait_ms(250);
////        }
//
//    return 0;
}
