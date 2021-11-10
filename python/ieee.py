import serial
import time
from pygame import mixer
import pyttsx3
import pyaudio
import speech_recognition as sr
import os

r = sr.Recognizer()
engine = pyttsx3.init()
mixer.init()
arduino = serial.Serial(port='COM3', baudrate=9600, timeout=.1)

def read():
   data = arduino.readline()
   return data

#def write(x):
#    arduino.write(bytes(x, 'utf-8'))
#    time.sleep(0.05)

def play(x):
    mixer.music.load(x)
    mixer.music.play()

with sr.Microphone() as source:
    audio_data = r.record(source, duration = 5)
    print("SPEAK!")
    text = r.recognize_google(audio_data)
    print(text)

#engine.say("This Works! Yay!")
#engine.runAndWait()

#while True:
    #print("1 = Play, 2 = Pause, 3 = Resume, 4 = Stop, 5 = End Program")
#    query = read() #int(input())
#    query = int.from_bytes(query, "big")
#    print(query)

#    if query == 49:
#        engine.say("Time to play some music. Let's play Awaken!")
#        engine.runAndWait()
#        play("awaken.mp3")

#    if query == '2':
#        mixer.music.pause()

#   if query == '3':
#        mixer.music.unpause()

#    if query == '4':
#        mixer.music.stop()

#    if query == '5':
#        break
    
    

