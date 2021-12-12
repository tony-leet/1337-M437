#!/usr/bin/env python3
import time
import serialcom
import helper
from database import writeDHTValues as dbDHT
from database import writeAverageValues as dbAVG


def monitorDHT(baud, arduino):
    print("Starting to monitor DHT sensors...")
    serialcom.setupSerial(baud, arduino)
    while True:
        # send a command to the arduino
        arduinoReply = serialcom.sendCommand("Monitor")
        avgValue = handleArduinoReply(arduinoReply)
        analyzeData(avgValue)
        time.sleep(30)


def handleArduinoReply(ardReply):
    now = helper.getTime()
    date = now[0]
    time = now[1]
    dataList = []
    avgHum = []
    avgTemp = []

    # put the values from the arduino in list
    splitted = [r.split() for r in [r for r in ardReply.split(";")]]

    for i in range(0, len(splitted), 1):
        s = i + 1
        sensor = s
        hum = splitted[i][0]
        temp = splitted[i][1]
        dataTuples = (int(sensor), float(hum), float(temp),
                      str(date), str(time))
        dataList.append(dataTuples)
        avgHum.append(float(hum))
        avgTemp.append(float(temp))

    ah = helper.getAverage(avgHum)
    at = helper.getAverage(avgTemp)

    dbDHT(dataList)
    dbAVG(ah, at, date, time)

    return ah, at


def analyzeData(values):
    hum = values[0]
    temp = values[1]

    print(hum)
    print(temp)

    if(hum > 70):
        print("Humidity too high...")
        # do some shit
    elif(hum < 50):
        print("Humidity too low...")
        # do some shit

    if(temp > 13):
        print("Temperature too high...")
        # do some shit
    elif(temp < 5):
        print("Temperature too low...")
        # do some shit


