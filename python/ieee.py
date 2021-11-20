#import required libraries
import pyttsx3
import speech_recognition as sr
import pyowm
from pygame import mixer
import pyaudio
import datetime
import subprocess
import re
import os
import webbrowser
import serial
import time
import wolframalpha
import wikipedia
from bs4 import BeautifulSoup as soup
from urllib.request import urlopen

os.system("welcome.vbs")

#Setup News scrapper
news = "https://news.google.com/news/rss"

#Setup weather API
owm = pyowm.OWM('59e4065593a3042148ff4cf85edc626a')

#setting up wolfram alpha client for use
app_id = "TKPTKH-GULXE8R83L"
client = wolframalpha.Client(app_id)

#Initiate Speech Engine
engine = pyttsx3.init()
voiceid = "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Speech\Voices\Tokens\TTS_MS_EN-US_ZIRA_11.0"
engine.setProperty('rate', 150)
engine.setProperty('volume', 0.9)
engine.setProperty('voice', voiceid)

#Initiate music player
mixer.init()

#set wikipedia language
#wikipedia.set_lang("fr")

#arduino = serial.Serial(port='COM3', baudrate=9600, timeout=.1)

def MyCommand(Ques):

    #Setup Mic
    r = sr.Recognizer()

    command = ""

    with sr.Microphone() as source:
        engine.say(Ques)
        engine.runAndWait()
        print("Ready for your Command: ")
        r.pause_threshold = 1
        r.adjust_for_ambient_noise(source, duration=1)
        audio = r.listen(source)

    try:
        command = r.recognize_google(audio).lower()
        print("You Said: " + command)

    except sr.UnknownValueError:
        print("Sorry, could not recognize your voice.")
        engine.say("Please repeat your request.")
        MyCommand(Ques)

    return command

def whichSong():
    songs = MyCommand("Which song would you like to listen to?")
    songpath = "D://" + songs + ".mp3"
    return songpath

def read():
   data = arduino.readline()
   return data

def write(x):
    arduino.write(bytes(x, 'utf-8'))
    time.sleep(0.05)

def play(x):
    mixer.music.load(x)
    mixer.music.play()

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

while True:
    
    type = MyCommand("What can I help you with?")

    if type == "wikipedia":

        question = MyCommand("What should I search wikipedia for?")
            
        print(wikipedia.summary(question, sentences = 2))
        engine.say(wikipedia.summary(question, sentences = 2))
        engine.runAndWait()
        continue
        
    if type == "wolfram":
        
        question = MyCommand("WHat would you like to look up on Wolfram Alpha?")
        
        #obtain result from wolfram client as text
        result = client.query(question)
        answer = next(result.results).text
        print(answer)
        engine.say(answer)
        engine.runAndWait()
        continue

    if type == "open":
        website = MyCommand("Which website would you like to launch?")
        url = 'https://www.' + website + '.com'
        engine.say("Launching " + website)
        engine.runAndWait()
        webbrowser.open(url)
        continue

    if type == "launch":
        app = MyCommand("Which application would you like to launch?")
        if app == "word":
            subprocess.call("C:\\Users\\Yash Puneet\\AppData\\Local\\Microsoft\\WindowsApps\\winword.exe")
            engine.say("Launching " + app)
            engine.runAndWait()
            continue
        
        else:
            print("Please request app support")
            engine.say("Please request app support")
            engine.runAndWait()
            continue
        
        continue

    if type == "time":
        now = datetime.datetime.now()
        engine.say('Current time is %d %d' % (now.hour, now.minute))
        engine.runAndWait()
        continue

    if type == "music":

        song = whichSong()
        
        try:
            mixer.music.load(song)
            mixer.music.play()
            continue
            
        except Exception:
            print("Request song integration")
            engine.say("Request song integration")
            engine.runAndWait()
            continue

        continue

    if type == "stop":
        mixer.music.stop()
        continue
      
    if type == "pause":
        mixer.music.pause()
        continue

    if type == "resume":
        mixer.music.unpause()
        continue

    if type == "weather":
        
        detail = MyCommand("What would you like to know?")

        if detail == "temperature":
            sg = owm.weather_at_place('Singapore, SG')
            weather = sg.get_weather()
            degrees = weather.get_temperature('celsius')['temp']
            print(degrees)
            engine.say("The temperature is " + str(degrees) + "degrees Celcius")
            engine.runAndWait()
            continue

        if detail == "sunrise":
            sg = owm.weather_at_place('Singapore, SG')
            weather = sg.get_weather()
            print(weather.get_sunrise_time(timeformat='iso'))
            continue
        
        if detail == "sunset":
            sg = owm.weather_at_place('Singapore, SG')
            weather = sg.get_weather()
            print(weather.get_sunset_time(timeformat='iso'))
            continue

        if detail == "climate":
            sg = owm.weather_at_place('Singapore, SG')
            weather = sg.get_weather()
            print(weather.get_detailed_status())
            continue

        if detail == "humidity":
            sg = owm.weather_at_place('Singapore, SG')
            weather = sg.get_weather()
            humid = weather.get_humidity()
            engine.say("The humidity is " + humid + "percent")
            print(humid)
            engine.runAndWait()
            continue

    if type == "headlines":
        Client = urlopen(news)
        xmlpage = Client.read()
        Client.close()

        souppage = soup(xmlpage, "xml")
        newslist = souppage.findAll("item")
        engine.say("Here are your headlines for today")
        engine.runAndWait()

        for headings in newslist:
            headline = headings.title.text
            print(headline)
            #print(headline.link.text)
            engine.say(headline)
            engine.runAndWait()
            print("-"*60)

        continue
            
    else:
        print("Error: Please input valid type")
        continue
    
    

