from email.mime import message
from multiprocessing import Value
from tkinter import messagebox
from turtle import bgcolor, title
from PyQt5 import QtWidgets, uic
from PyQt5.QtSerialPort import QSerialPort, QSerialPortInfo
from PyQt5.QtCore import QIODevice

app = QtWidgets.QApplication([])

greenLedState = False
blueLedState = False
portState = False
receivedDataString = ""

ui = uic.loadUi("design.ui")
serial = QSerialPort()
portList = []
QSerialPortInfo
ports = QSerialPortInfo.availablePorts()
for port in ports:
    portList.append(port.portName())
ui.comPortBox.addItems(portList)  

baudRate = ["1200", "2400", "4800", "9600", "19200", "38400", "57600", "115200"]
ui.baudRateBox.addItems(baudRate)
ui.baudRateBox.setCurrentIndex(3)

dataBits = ["5", "6", "7", "8"]
ui.dataBitsBox.addItems(dataBits)
ui.dataBitsBox.setCurrentIndex(3)

stopBits = ["1", "3", "2"]
ui.stopBitsBox.addItems(stopBits)
ui.stopBitsBox.setCurrentIndex(0)

parity = ["none", "even", "odd", "space", "mark"]
parityValue = [serial.Parity.NoParity, serial.Parity.EvenParity, serial.Parity.OddParity, serial.Parity.SpaceParity, serial.Parity.MarkParity]
ui.parityBox.addItems(parity)
ui.parityBox.setCurrentIndex(0)

ui.celciusLabel.setText("\u00B0" + "C")
ui.temperatureValueLabel.setText("00.0")

ui.greenLedButton.setEnabled(False)
ui.blueLedButton.setEnabled(False)

def openClosePort():
    global portState
    if portState == False:
        serial.setPortName(ui.comPortBox.currentText())
        serial.setBaudRate((int)(baudRate[ui.baudRateBox.currentIndex()]))    
        serial.setDataBits((int)(dataBits[ui.dataBitsBox.currentIndex()]))
        serial.setStopBits((int)(stopBits[ui.stopBitsBox.currentIndex()]))
        serial.setParity(parityValue[ui.parityBox.currentIndex()])
        serial.open(QIODevice.ReadWrite) 
        if serial.isOpen():
            portState = True
            ui.openCloseButton.setText("Close")
            ui.greenLedButton.setEnabled(True)
            ui.blueLedButton.setEnabled(True)   
            ui.dataBitsBox.setEnabled(False)
            ui.baudRateBox.setEnabled(False)
            ui.stopBitsBox.setEnabled(False)
            ui.parityBox.setEnabled(False)
            messagebox.showwarning(message = "Success to open")
        else:
            messagebox.showwarning(message = "Fail to open")
    elif portState == True:
        portState = False
        ui.openCloseButton.setText("Open")
        ui.greenLedButton.setEnabled(False)
        ui.blueLedButton.setEnabled(False)
        ui.dataBitsBox.setEnabled(True)
        ui.baudRateBox.setEnabled(True)
        ui.stopBitsBox.setEnabled(True)
        ui.parityBox.setEnabled(True)
        serial.close()
        messagebox.showwarning(message = "Port closed")

def serialSend(data):
    txs = ""
    for val in data:
        txs += str(val)    
    serial.write(txs.encode())

def greenLedControl(value):
    global greenLedState
    if greenLedState == False:
        greenLedState = True
        ui.greenLedButton.setText("OFF")
        serialSend([1, 0])
    elif greenLedState == True:
        greenLedState = False
        ui.greenLedButton.setText("ON")
        serialSend([1, 1])

def blueLedControl(value):
    global blueLedState
    if blueLedState == False:
        blueLedState = True
        ui.blueLedButton.setText("OFF")
        serialSend([2, 0])
    elif blueLedState == True:
        blueLedState = False
        ui.blueLedButton.setText("ON")
        serialSend([2, 1])   

def temperatureControl():
    rxData = serial.readLine()
    if len(rxData) == 4:
        global receivedDataString 
        if rxData[0] == b'1':
            receivedDataString = '-'
        elif rxData[0] == b'0': 
            receivedDataString = '+'    
        receivedDataString += str(rxData[1], 'utf-8')
        receivedDataString += str(rxData[2], 'utf-8')
        receivedDataString += '.'
        receivedDataString += str(rxData[3], 'utf-8')
        ui.temperatureValueLabel.setText(receivedDataString)
        receivedDataString = ""


ui.openCloseButton.clicked.connect(openClosePort)
ui.greenLedButton.clicked.connect(greenLedControl)
ui.blueLedButton.clicked.connect(blueLedControl)
serial.readyRead.connect(temperatureControl)

ui.show()
app.exec()