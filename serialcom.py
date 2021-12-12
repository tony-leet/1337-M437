#!/usr/bin/env python3
import serial

startMarker = '<'
endMarker = '>'
terminator = '$'
dataStarted = False
dataBuff = ""
messageComplete = False


def setupSerial(baudRate, serialPortName):
    global serialPort
    serialPort = serial.Serial(port=serialPortName, baudrate=baudRate, timeout=0, rtscts=True)
    print("Serial port " + serialPortName + " opened Baudrate " + str(baudRate))
    waitForArduino()


def sendToArduino(stringToSend):
        # this add the start and end marker before sending
    global startMarker, endMarker, terminator, serialPort

    stringWithMarkers = (startMarker)
    stringWithMarkers += stringToSend
    stringWithMarkers += (endMarker)
    stringWithMarkers += (terminator)

    serialPort.write(stringWithMarkers.encode('utf-8'))


def recvLikeArduino():
    global startMarker, endMarker, serialPort, dataStarted, dataBuff, messageComplete

    if serialPort.inWaiting() > 0 and messageComplete == False:
        x = serialPort.read().decode("utf-8")

        if dataStarted:
            if x != endMarker:
                dataBuff = dataBuff + x
            else:
                dataStarted = False
                messageComplete = True

        elif x == startMarker:
            dataBuff = ''
            dataStarted = True

    if(messageComplete):
        messageComplete = False
        return dataBuff
    else:
        return "XXXX"


def waitForArduino():
    # wait until the arduino sends 'Arduino is ready' - allow time for arduino reset
    # it also ensure that any bytesleft over from a previous message are discarded
    print("Waiting for arduino to reset")
    msg = ""
    while msg.find("Arduino is ready") == -1:
        msg = recvLikeArduino()
        if not (msg == 'XXXX'):
            print(msg)


def sendCommand(stringToSend):
    sendToArduino(stringToSend)
    receivingData = True
    while receivingData:
        arduinoReply = recvLikeArduino()
        if not(arduinoReply == 'XXXX'):
            #printDHT(arduinoReply)
            receivingData = False
            return arduinoReply
