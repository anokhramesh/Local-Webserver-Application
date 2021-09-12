#Control GPIO Pins of ESP8266 over webserver with Tkinter Buttons in Python Programming
from tkinter import *# import everything from Tkinter
import requests# import request library

root=Tk()
root.geometry('500x600')
root.title("Webbrowser App")
root.iconbitmap("python_logo_icon.ico")
Appname=Label(root,text='WELCOME TO ANOKHAUTOMATION',fg='#120d11',bg='#de09b0',font="Georgea 20 bold")
Appname.pack(pady=10)
root.configure(background="#0da1d6")
on_image =PhotoImage(file='OnLamp.png')
off_image =PhotoImage(file='OffLamp.png')
global relay1
global relay2
global relay3
global relay4
relay1 =True
relay2 =True
relay3 =True
relay4 =True
#Define Button1 function
def Button_1():
    global relay1
    if relay1:
        requests.get("http://192.168.0.113/relay?r1=on")
        button_1.config(image=off_image)
        load1_label.config(text="LOAD 1 is Off",fg="blue")
        relay1=False
    else:
        requests.get("http://192.168.0.113/relay?r1=off")
        button_1.config(image=on_image)
        load1_label.config(text="LOAD 1 is ON",fg="red")
        relay1=True
#Define button2 function
def Button_2():
        global relay2
        if relay2:
            requests.get("http://192.168.0.113/relay?r2=on")
            button_2.config(image=off_image)
            load2_label.config(text="LOAD 2 is Off", fg="blue")
            relay2 = False
        else:
            requests.get("http://192.168.0.113/relay?r2=off")
            button_2.config(image=on_image)
            load2_label.config(text="LOAD 2 is ON", fg="red")
            relay2 = True
#Function for Button-3
def Button_3():
    global relay3
    if relay3:
        requests.get("http://192.168.0.113/relay?r3=on")
        button_3.config(image=off_image)
        load3_label.config(text="LOAD 3 is Off",fg="blue")
        relay3=False
    else:
        requests.get("http://192.168.0.113/relay?r3=off")
        button_3.config(image=on_image)
        load3_label.config(text="LOAD 3 is ON",fg="red")
        relay3=True
#Function for Button -4
def Button_4():
        global relay4
        if relay4:
            requests.get("http://192.168.0.113/relay?r4=on")
            button_4.config(image=off_image)
            load4_label.config(text="LOAD 4 is Off", fg="blue")
            relay4 = False
        else:
            requests.get("http://192.168.0.113/relay?r4=off")
            button_4.config(image=on_image)
            load4_label.config(text="LOAD 4 is ON", fg="red")
            relay4 = True
#label for Load-1
load1_label=Label(root,text="Click Btn-1 ",bg="white",fg="blue",font=("Verdana",15,"bold"))
load1_label.pack(pady=5)
#button for Load-1
button_1=Button(root,image=off_image,bg='#0da1d6',borderwidth=0,command=Button_1)
button_1.pack(pady=1)
#label for Load-2
load2_label=Label(root,text="Click Btn-2",bg="white",fg="blue",font=("Verdana",15,"bold"))
load2_label.pack(pady=10)
#button for Load-2
button_2=Button(root,image=off_image,bg='#0da1d6',borderwidth=0,command=Button_2)
button_2.pack(pady=1)
#label for Load-3
load3_label=Label(root,text="Click Btn-3",bg="white",fg="blue",font=("Verdana",15,"bold"))
load3_label.pack(pady=10)
#button for Load-3
button_3=Button(root,image=off_image,bg='#0da1d6',borderwidth=0,command=Button_3)
button_3.pack(pady=1)
#label for Load-4
load4_label=Label(root,text="Click Btn-4",bg="white",fg="blue",font=("Verdana",15,"bold"))
load4_label.pack(pady=10)
#button for Load-4
button_4=Button(root,image=off_image,bg='#0da1d6',borderwidth=0,command=Button_4)
button_4.pack(pady=1)
root.mainloop()