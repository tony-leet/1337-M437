import sqlite3

def createTable():
    mydb = sqlite3.connect('test4.db')
    c = mydb.cursor()
    c.execute('''CREATE TABLE sensors1
                (id integer primary key,sensor integer,
                humidity real, temperature real,date text, time text)''')

    c.execute('''CREATE TABLE average (id integer primary key, humidity real,
            temperature real, date text, time text)''')
    mydb.commit()
    c.close


def writeDHTValues(dataList):
    try:
        mydb = sqlite3.connect('test4.db')
        c = mydb.cursor()

        c.executemany("INSERT INTO sensors1(sensor, humidity, temperature, date, time)VALUES(?, ?, ?, ?, ?)", dataList)
        mydb.commit()
        c.close()

        print("DHT Success!")

    except sqlite3.Error as error:
        print("Failed to insert Python variable into sqlite table sensors1", error)

    finally:
        if mydb:
            mydb.close()
            print("Conection with sensors1 ended")


def writeAverageValues(hum, temp, date, time):

    try:
        mydb = sqlite3.connect('test4.db')
        c = mydb.cursor()

        query = '''INSERT INTO average(humidity,temperature, date, time)
                       VALUES(?,?,?,?)'''
        dataTuple = (hum, temp, date, time)

        c.execute(query, dataTuple)
        mydb.commit()
        c.close()

        print("Average Success!")

    except sqlite3.Error as error:
        print("Failed to insert Python variable into sqlite table Average", error)

    finally:
        if mydb:
            mydb.close()
            print("Conection with Average ended")


def printalltables():
    mydb = sqlite3.connect('test4.db')
    c = mydb.cursor()
    x = c.execute("SELECT * FROM sqlite_master where type='table'")
    for y in x:
        print(y)
    c.close()


def printcontenttable():
    mydb = sqlite3.connect('test4.db')
    c = mydb.cursor()
    c.execute("SELECT * FROM sensors1")
    print(c.fetchall())
    print()
    c.close()


#printcontenttable()

