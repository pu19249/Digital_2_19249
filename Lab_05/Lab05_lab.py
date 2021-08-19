# AdafruitIO
# Universidad del Valle de Guatemala
# Digital 2
# Jonathan Pu
# Adafruit IO
# https://io.adafruit.com/

# if Module not Found. Open Terminal/CMD and execute:
# pip3 install Adafruit_IO

from Adafruit_IO import Client, RequestError, Feed
import serial
import time
import sys

centenas = 0
decenas = 0
unidades = 0
enviar = 0
centena1 = 0
decena1 = 0
unidad1 = 0

ADAFRUIT_IO_KEY = "aio_XnKI18Zc1tRONAwqwWgVj1Tf1lZv"
ADAFRUIT_IO_USERNAME = "JonnyPu"
aio = Client(ADAFRUIT_IO_USERNAME, ADAFRUIT_IO_KEY)

#Feeds qe se van a utilizar
contador = aio.feeds('sen1')
mandar_value = aio.feeds('send') #mandar de Adafruit a pic


ser = serial.Serial()
ser.baudrate = 9600
ser.timeout = 3
ser.port = 'COM1'



ser.open()

#Esto para leer el contador del pic
ser.write(b'b')
centenas = ser.readline(1).decode("ascii", "ignore")
decenas = ser.readline(1).decode("ascii", "ignore")
unidades = ser.readline(1).decode("ascii", "ignore")
contador_botones = int(centenas+decenas+unidades) #se concatenan
aio.send_data(contador.key, contador_botones)

mandar_0 = aio.receive(mandar_value.key)
mandar_1 = mandar_0.value

centena1 = mandar_1[0:1].encode("ascii")
decena1 = mandar_1[1:2].encode("ascii")
unidad1 = mandar_1[2:3].encode("ascii")

#Ahora ya solo quiero mandar los valores para que mi pic los reciba
ser.write(centena1)
time.sleep(0.01)
ser.write(decena1)
time.sleep(0.01)
ser.write(unidad1)


# sensor1_1 = 15
# analog_feed = aio.feeds('sen1')
# aio.send_data(analog_feed.key, sensor1_1)
# digital_data = aio.receive(analog_feed.key)
# print(f'analog signal: {digital_data.value}')

# sensor2_2 = 15
# analog_feed_2 = aio.feeds('sen2')
# aio.send_data(analog_feed_2.key, sensor2_2)
# digital_data_2 = aio.receive(analog_feed_2.key)
# print(f'analog signal: {digital_data_2.value}')
    

# analog_feed_2 = aio.feeds('send')
# # aio.send_data(analog_feed_2.key, sensor2_2)
# digital_data_2 = aio.receive(analog_feed_2.key)
# print(f'analog signal: {digital_data_2.value}')


    
# ser.close()

    
# #Digital Feed
# analog_feed = aio.feeds('sen1')
# aio.send_data(analog_feed.key, sensor1_1)
# digital_data = aio.receive(analog_feed.key)
# print(f'analog signal: {digital_data.value}')

# analog_feed_2 = aio.feeds('sen2')
# aio.send_data(analog_feed_2.key, sensor2_2)
# digital_data_2 = aio.receive(analog_feed_2.key)
# print(f'analog signal: {digital_data_2.value}')