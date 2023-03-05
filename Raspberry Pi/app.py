import os
import serial
import picamera
from time import sleep
from gpiozero import Button

labels = []
money_amount = 0
button = Button(2)
camera = picamera.PiCamera()
ser = serial.Serial("/dev/ttyS0", 9600)  # Open port with baud rate

while True:
    waiting_state = ser.inWaiting()  # check for remaining byte
    if waiting_state:
        received_data = ser.read()
        if(received_data == 1):
            button.wait_for_press()  # waiting for start button

            # capturing an image with pi camera
            camera.capture("/ home/pi/image.jpeg")
            camera.close()

            os.system(
                "!python detect.py --weights ../best.pt --conf 0.25 --source ../image.jpeg")  # running the model

            with open("User.txt", "r") as file:  # reading labels
                for item in file:
                    labels = file.readlines()

            for label in labels:  # calculate money amount
                money_amount += int(label.split('_')[0])

            ser.write(money_amount)  # transmit data serially
