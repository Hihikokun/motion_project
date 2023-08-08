import serial.tools.list_ports
import numpy as np

ports = serial.tools.list_ports.comports()
serialInst = serial.Serial()

portList = []

for onePort in ports:
    portList.append(str(onePort))
    print(str(onePort))

val = input("select Port: /dev/cu.")

for x in range(0,len(portList)):
    if portList[x].startswith("/dev/cu." + str(val)):
        portVar = str("/dev/cu." + str(val))
        print(portList[x])

serialInst.baudrate = 115200
serialInst.port = portVar
serialInst.open()

lastTen = [0,0,0,0,0,0,0,0,0,0]

while True:
    if serialInst.in_waiting:
        packet = serialInst.readline()
        lastTen.pop(0)
        input = packet.decode('utf').rstrip().split("_")
        for i in range(len(input)):
            input[i] = float(input[i])
        lastTen.append(input)
        print(lastTen)
    

        