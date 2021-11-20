dim speech
clock = hour(Time) & Minute(Time) & "p" & "m"
welcome = "System Activated, Welcome Yash. The date today is " & Date & " and the time is " & clock
initiation = "Seting up your Control Interface"
set speech=CreateObject("sapi.spvoice")
speech.speak welcome
speech.speak initiation


