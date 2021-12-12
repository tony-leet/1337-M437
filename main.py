#TO DO:
#
#
# send msg to lcd
#
#
###############################################################################
# -*- coding: utf-8 -*-
# GNU General Public License v3
import handleDHT as dht


arduino0 = '/dev/ttyUSB0'
arduino1 = '/dev/ttyACM0'

# Dictionary
menu_options = {
    1: 'Monitor DHT Sensors',
    2: 'Check Logs',
    3: 'Check Hardware',
    4: 'Exit',
}


def option1():
    print("Starting to monitor DHT Sensors...")
    # dht.monitorDHT(9600, arduino1)


def option2():
    print("Checking logs...")


def option3():
    print("Starting to monitor Hardware...")


def option4():
    print("Exiting program...")
    exit("Program ended")


def invalidOption():
    print("Invalid Choice dumb ass")


def printMenu():
    print(30*"-", "1337 M34T", 30*"-")
    for key in menu_options.keys():
        val = menu_options[key]
        print(f"{key}. {val}")
    print(71 * "-")


def start():
    printMenu()

    option = int(input("Enter your choice: "))
    match option:
        case 1:
            option1()
        case 2:
            option2()
        case 3:
            option3()
        case 4:
            option4()
        case _:
            # default handler
            invalidOption()
    # try:
    #    option = int(input("Enter your choice: "))
    # except:
    #   invalidChoice()

    # if option ==1:
    #    option1()
    # elif option ==2:
    #   option2()
    # elif option ==3:
    #     option3()
    # elif option ==4:
    #   option4()


if __name__ == "__main__":
    start()

