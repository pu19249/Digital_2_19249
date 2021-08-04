# -*- coding: utf-8 -*-
"""
Created on Mon Aug  2 01:46:14 2021

@author: Jonathan Pu
"""
# import serial

# com_serial = serial.Serial(port = None, 
#                            baudrate = 9600,
#                            bytesize= 8,
#                            parity = 'N',
#                            stopbits= 1)

from tkinter import *
from tkinter.font import Font
from time import sleep 
import serial
import time
import sys

#CREAR PUERTO SERIAL PARA LA COMUNICACION  USANDO PYTHON
puerto= serial.Serial()

#DEFINIR VELOCIDAD EN BAUDIOS
puerto.baudrate=9600
puerto.timeout=3#tiempo hasta recibir un caracterer de fin de linea
#DEFINIR PUERTO COM DEL FTDI232
puerto.port= "COM3"
# #abrir una conexion serial
# puerto.open()
# print('PUERTO SERIAL LISTO PARA LA COMUNICACION')

#Crear un objeto Tk() 
vent=Tk()

#TITULO DE LA INTERFAZ
vent.title("COMUNICACION SERIAL PYTHON   -  PIC16F887")

#DIMENSIONES DE LA INTERFAZ
vent.geometry('500x500')
entrada = Entry(vent)
#----------------------------------------

#CREACION DE FUNCIONES ASOCIADOS A CADA BOTON DE LA INTERFAZ GRAFICA
def button1(): #CUANDO SE PRESIONA EL BOTON DE "LED ON"
    global vent
    # mystring=str(2)
    # b = mystring.encode('utf-8')
    print("SE HA CONECTADO LA COM. SERIAL")
    #ABRIR UNA CONEXION SERIAL
    puerto.open()
    #puerto.write(b)#ESCRIBIR 
    tex.delete(1.0,END)
    #INSERTAR UN MENSJAE EN LA INTERFAZ GRAFICA
    tex.insert(1.0,"SE HA CONECTADO") 
def button2():#CUANDO SE PRESIONA EL BOTON DE "LED OFF"
    global vent
    # mystring=str(1)
    # b = mystring.encode('utf-8')
    #puerto.write(b)
    print("DESCONECTAR")
    puerto.close()
    tex.delete(1.0,END)
    #INSERTAR UN MENSJAE EN LA INTERFAZ GRAFICA
    tex.insert(1.0,"SE HA DESCONECTADO")

def button3():#CUANDO SE PRESIONA EL BOTON DE "LED BLINK"
    global vent
    centena=input()
    b = mystring.encode('ascii')
    print("BOTON 3 SE HA PRESIONADO")
    puerto.write(b)
    tex.delete(1.0,END)
    #INSERTAR UN MENSJAE EN LA INTERFAZ GRAFICA
    tex.insert(1.0,"LED PARPADEANDO")
    
def button4(): 
    global vent
    decena=input()
    b = decena.encode('ascii')
    printf("BOTON 4 SE HA PRESIONADO")
    puerto.write(b)
    tex.delete(1.0,END)
    tex.insert(1.0,"UNIDAD ENVIADA")
    
def button5(): 
    global vent
    decena=input()
    b = decena.encode('ascii')
    printf("BOTON 4 SE HA PRESIONADO")
    puerto.write(b)
    tex.delete(1.0,END)
    tex.insert(1.0,"UNIDAD ENVIADA")
#-------------------------------------------------------------------------------------
#CREACION DE BOTONES
l1=Button(vent,text='CONECTAR',command=button1,cursor='circle')
l2=Button(vent,text='DESCONECTAR',command=button2,cursor='circle')
l3=Button(vent,text='ENVIAR CENTENA', command=button3, cursor='arrow') 
l4=Button(vent,text='ENVIAR DECENA',command=button4,cursor='arrow')
l5=Button(vent,text='ENVIAR UNIDAD', command=button5, cursor='arrow')

inputtxt = Text(vent, height = 3,
                width = 6,
                bg = "light yellow") 
inputtxt.pack()
inputtxt.place(x=190,y=300)


inputtxt1 = Text(vent, height = 3,
                width = 6,
                bg = "light blue") 
inputtxt1.pack()
inputtxt1.place(x=290,y=300)


#CREACION DE ETIQUETAS 
#lab1=Label(vent,text='ENVIAR VALORES',width=15,height=3)
lb2=Label(vent,text='PYTHON COMUNICACION SERIAL PIC16F887',width=38,height=4)

#CREACION DE TEXTO
tex= Entry(vent)

#ESTABLECER POSICIONES DE LOS BOTONES EN LA INTERFAZ GRAFICA
l1.place(x=180,y=200)
l2.place(x=270,y=200)
l3.place(x=100,y=250)
l4.place(x=220,y=250)
l5.place(x=340,y=250)

#ESTABLECER POSICIONES DE LAS ETQIUETAS Y TEXTOS EN LA INTERFAZ GRAFICA
#lb1.place(x=150,y=100)
lb2.place(x=145,y=40)
tex.place(x=205,y=140)
vent.mainloop()

#CERRAR EL PUERTO SERIAL
puerto.close()
print('PUERTO BLOQUEADO')
sys.exit(0)
