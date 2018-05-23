######################
HOW TO RUN

Created by: pacomaster
######################

Step 1. Install Arduino IDE

  https://www.arduino.cc/en/Main/Software

Step 2. Install ESP8266 boards

  Go to Tools > Boards > Board manager and search "ESP8266"  and install those boards
  
  If you cannot find the board follow the instructions in this page:  
  https://randomnerdtutorials.com/how-to-install-esp8266-board-arduino-ide/

Step 3. install ESP8266Wifi.h lib and ArduinoJson.hello-world-app-with-node-js-and-express-c1eb7cfa8a30

  Go to Sketch > Include Library > Manage Library and search those two libraries and install

Step 4. Start NodeJS service

  https://medium.com/@adnanrahic/hello-world-app-with-node-js-and-express-c1eb7cfa8a30
  
  You need to check your IP address in windows "ipconfig"  
  And change that IP address in the code in the variable "host"
  Also you need to change the name of the Wifi router and password to work
  The computer that runs the nodeJs code should be in the same router as the arduino.
  
Step 5. Load the code to the ESPWifi module

  5.a Check figA.jpg to see the connections
  5.b Check figB.jpg to see tools configuration
  5.c Click upload
	
Step 6. Validate

  When the code completes uploading open in tools > Serial Monitor the same port 115200 Baud and check the Hello
