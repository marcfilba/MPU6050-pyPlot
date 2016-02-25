import serial
import numpy as np

from sys import stdin
from matplotlib import pyplot as plt

#serialPort = '/dev/ttyACM0'
baudRate = 9600

#ser = serial.Serial(serialPort, baudRate)

plt.ion() # set plot to animated

xAccelData = [0] * 50
yAccelData = [0] * 50
zAccelData = [0] * 50

xAnVelData = [0] * 50
yAnVelData = [0] * 50
zAnVelData = [0] * 50

tempData = [0] * 50

ax1=plt.axes()

plt.figure(1).subplots_adjust(hspace=.5)

plt.subplot(311).set_title("Acceleration")
xAccel, = plt.plot(xAccelData)
yAccel, = plt.plot(yAccelData)
zAccel, = plt.plot(zAccelData)

plt.subplot(312).set_title("Angular Velocity")
xAnVel, = plt.plot(xAnVelData)
yAnVel, = plt.plot(yAnVelData)
zAnVel, = plt.plot(zAnVelData)

plt.subplot(313).set_title("Temperature")
temp, = plt.plot(tempData)

plt.ylim([0,0])

while True:

    input_var = stdin.readline().split("\n")[0]
    rawData = ""
    rawDataSplitted = []
    while len (rawDataSplitted) != 7 or not 'AccelRange' in rawData or not 'GyroRange' in rawData:
        rawData = ser.readline().rstrip()	# llegim accel, gyro i temp
        rawDataSplitted = rawData.split (",")

    if sys.stdin.isatty():
        ser.write(stdin.readline())

    if len(rawDataSplitted) == 7:
    	xAccelData.append(float (str(rawData[0])))
    	yAccelData.append(float (str(rawData[1])))
    	zAccelData.append(float (str(rawData[2])))

    	xAnVelData.append(float (str(rawData[3])))
    	yAnVelData.append(float (str(rawData[4])))
    	zAnVelData.append(float (str(rawData[5])))

    	tempData.append (float (str(rawData[6])))

    	plt.subplot(311)
    	plt.ylim([\
    				min (min (xAccelData), min (yAccelData), min (zAccelData)) -200, \
    				max (max (xAccelData), max (yAccelData), max (zAccelData)) + 200])

    	plt.subplot(312)
    	plt.ylim([\
    				min (min (xAnVelData), min (yAnVelData), min (zAnVelData)) -200, \
    				max (max (xAnVelData), max (yAnVelData), max (zAnVelData)) + 200])

    	plt.subplot(313)
    	plt.ylim([min (tempData)-3,max (tempData)+3])

    	del xAccelData [0]
    	del yAccelData [0]
    	del zAccelData [0]

    	del xAnVelData [0]
    	del yAnVelData [0]
    	del zAnVelData [0]

    	del tempData [0]

    	xAccel.set_xdata(np.arange(len(xAccelData)))
    	xAccel.set_ydata(xAccelData)

    	yAccel.set_xdata(np.arange(len(yAccelData)))
    	yAccel.set_ydata(yAccelData)

    	zAccel.set_xdata(np.arange(len(zAccelData)))
    	zAccel.set_ydata(zAccelData)


    	xAnVel.set_xdata(np.arange(len(xAnVelData)))
    	xAnVel.set_ydata(xAnVelData)

    	yAnVel.set_xdata(np.arange(len(yAnVelData)))
    	yAnVel.set_ydata(yAnVelData)

    	zAnVel.set_xdata(np.arange(len(zAnVelData)))
    	zAnVel.set_ydata(zAnVelData)

    	temp.set_xdata(np.arange(len(tempData)))
    	temp.set_ydata(tempData)

    	plt.draw()
    else:
		print rawData
