#!/usr/bin/env python3
import datetime


# i do what i want
def getTime():
    now = datetime.datetime.now()
    date = (str(now.day)+"-"+str(now.month)+"-"+str(now.year))
    time = (str(now.hour) + ":" + str(now.minute))

    return date, time


def getAverage(lst):
    return round((sum(lst) / len(lst)), 2)




