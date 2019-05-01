# IOTdummycam

This repository is intended for the sharing of code associated with turning a dollar story "dummy" camera into a smart "camera" using a Wemos D1 mini based on the ESP8266
I have created a video that goes into depth of how I modified the camera and created this IOT device that sends you notifications of tresspassers through the AdafruitIO and IFTTT service.

<YouTube Link>

Download the .ino file as well as the .h file and place into the same directory. Modify the Arduino code as you see fit.
The .h file can be used to set up your static WiFi credentials, but keep in mind if these change you will have to reprogram your device with the credentials hard coded each time something changes. 

If you want a more dynamic solution where you can wirelessly confirgure your WiFi settings, I have this code working with "Wifi Manager Library"

Follow the steps in the video to edit the Adafruit libraries to use the WifiManager library graciously created by tzapu here on Github. 

Thank you and enjoy!
