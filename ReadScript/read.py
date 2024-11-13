import serial
import time
import matplotlib.pyplot as plt

# 初始化串口
ser = serial.Serial(
        port='COM6',
        baudrate=115200,
        bytesize=serial.EIGHTBITS,
        parity=serial.PARITY_EVEN,
        stopbits=serial.STOPBITS_ONE,
        timeout=1
    )
# the 3rd byte will toggle after each massage sent
sendToggle = 1
cardNumber = bytearray()
baseLine = 0x09 # 读取的起始行
totalLine = 0x05 # 读取的总行数
dataLenth = 0x20 # SOF+10+20(数据长度)+2CRC
dataRead = [0] * 300
xPlot = range(300)
yPlot = [0] * 300

def calculate_crc(data):
    # CRC-16/MCRF4XX 计算
    crc = 0xFFFF
    for byte in data:
        crc ^= byte
        for _ in range(8):
            if crc & 0x0001:
                crc = (crc >> 1) ^ 0x8408
            else:
                crc >>= 1
    return crc

def send_data(data, function):
    responseBuffer = bytearray()
    responseToProcess = bytearray()
    # 去掉开头的0xFA进行CRC计算
    crc = calculate_crc(data[1:])
    data_with_crc = data + crc.to_bytes(2, byteorder='little')

    try:
        ser.write(data_with_crc)
        # print("Data sent:", data_with_crc.hex())
        # 等待接收返回的数据
        while ser.in_waiting != 0:
            response = ser.read(ser.in_waiting or 1)
            responseBuffer.extend(response)
            time.sleep(0.01)
            if response:
                # print(len(responseBuffer),responseBuffer[1])
                # print("Received:", responseBuffer.hex())
                if len(responseBuffer) == responseBuffer[1]+1:
                    responseToProcess = responseBuffer.copy()
                    responseBuffer.clear()
                    print("Received:", responseToProcess.hex())
    except Exception as e:
        print(f"Error: {e}")
    else:
        # 根据function处理response
        if function == 'initialData':
            pass
        if function == 'configData':
            pass
        if function ==  'cardFrame':
            if responseToProcess:
                # print(len(responseToProcess))
                if responseToProcess[1] == 0x17 and responseToProcess[4] == 0x31 and responseToProcess[15:22] != [0x00, 0x00, 0x00, 0x00,0x00,0x00, 0x00, 0x00]:
                    global cardNumber
                    cardNumber.extend(responseToProcess[15:22])  # 从第16位开始的7位为卡号
                    print("Card number received:", cardNumber.hex())
                    return True
                else:
                    return False
            else:
                    return False
        if function == 'connectFrame':
            pass
        if function == 'dataRequestFrame':
            if responseToProcess:
                if responseToProcess[1] == dataLenth and responseToProcess[4] == 0x34:
                    data_points = [
                    responseToProcess[11] * 100 + responseToProcess[12],
                    responseToProcess[13] * 100 + responseToProcess[14],
                    responseToProcess[15] * 100 + responseToProcess[16],
                    responseToProcess[17] * 100 + responseToProcess[18],
                    responseToProcess[19] * 100 + responseToProcess[20]
                    ]
                    print(data_points)
                    # Convert ASCII strings to integers for plotting
                    values = [int(s) for s in data_points]
                    return values

def initial_frame():
    # 定义数据包，0xFA开头，第二位为数据长度
    initialPayload = [0xC0]  # 示例数据，你可以根据需要修改
    data_length = len(initialPayload) + 2 + 2  # 包括长度, 数据包长度和CRC字节
    initialFrame = bytearray([0xFA, data_length, 0xFF] + initialPayload)
    send_data(initialFrame, 'initialFrame')
    time.sleep(0.5)     # 等待串口数据

    # 声明 sendToggle 为全局变量
    global sendToggle
    for configCount in range(8):
        configHeader = [
        0xFA,
        8,      # 总长度固定为8
        0xFF,
        0x00 if sendToggle else 0x40,
        0x01,
        configCount,
        0x01]
        configFrame = bytearray(configHeader)
        time.sleep(1)
        send_data(configFrame, 'configFrame')
        sendToggle = not sendToggle

def card_recognize():
    global sendToggle
    getCardFlag = False
    
    # 构建数据帧用于获取卡号
    while getCardFlag == False:
        cardFrame = bytearray([0xFA, 0x0B, 0xFF, 0x00 if sendToggle else 0x40, 0x31, 0x02, 0x01, 0x02, 0x00, 0x00])
        print(getCardFlag)
        getCardFlag = send_data(cardFrame, 'cardFrame')
        sendToggle = not sendToggle
        time.sleep(1)

def get_data():
    global xPlot, yPlot
    global sendToggle
    # 连接卡
    connectFrame = bytearray([0xFA, 0X11, 0XFF, 0x00 if sendToggle else 0x40, 0X32, 0X00, 0X02, 0X01, 0X07])
    connectFrame.extend(cardNumber.copy())
    send_data(connectFrame, 'connectFrame')
    sendToggle = not sendToggle

    # 准备数据图像
    plt.ion()  # 启用交互模式
    fig, ax = plt.subplots()
    line, = ax.plot([])
    ax.set_ylim(0, 5000)  # 设置y轴范围，根据你的数据范围进行调整


    # 请求数据
    while(True):
        dataRequestFrame = bytearray([0xFA, 0X0E, 0XFF, 0x00 if sendToggle else 0x40, 0x34, 0x01, 0x06, 0x1C, 0x00, baseLine, 0x00, totalLine, 0x00])
        values = send_data(dataRequestFrame, 'dataRequestFrame')
        time.sleep(0.05)
        sendToggle = not sendToggle

        if values:
            dataRead.extend(values)
            yPlot = dataRead[-300:]

            # graph.remove()
            line.set_ydata(yPlot)
            line.set_xdata(range(len(yPlot)))
            ax.relim()
            ax.autoscale_view()
            plt.pause(0.05)  # 更新图形，可以根据需要调整刷新频率

def main():
    # initial_frame()
    card_recognize()
    get_data()

    
if __name__ == "__main__":
    main()