### Resume
This direcory contain Main Arduino code, exemples to scan network & scan I2C sensors, and Arduino library. 
Inspired by [Esp32 mqtt publish](https://randomnerdtutorials.com/esp32-mqtt-publish-subscribe-arduino-ide/)

### Install ESP32 Addon for Arduino
[Windows config follow this link](https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/)  
[Linux & MacOs follow this link](https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-mac-and-linux-instructions/)  

### Clone this repository  
>
      git clone https://github.com/TamataOcean/esp32Bme280.git
     
### Configure Arduino library directory
File > Preference > 

![Config_Arduino_Client_For_ESP32](https://user-images.githubusercontent.com/25310798/76499307-c55a4980-643e-11ea-9f10-c07390334761.jpg)

### First launch 
Open the ESP32Bme280.ino  
Connect the ESP32 with USB port  
Configure SSID, Password & MQTT_IP_SERVER
Compile & Launch 

![Config_Arduino_Client_For_ESP32](https://user-images.githubusercontent.com/25310798/76503487-4c5ef000-6446-11ea-92b3-def1f87c8c99.jpg)

#### Console Log result
![Console_Log_Arduino](https://user-images.githubusercontent.com/25310798/76503188-b2974300-6445-11ea-8ea9-87c9dea87004.jpg)

#### AZDelivery Pin OUT...
![ESP32-DOIT-DEVKIT-V1-Board-Pinout-36-GPIOs-updated](https://user-images.githubusercontent.com/25310798/76535881-dffee380-647b-11ea-9cc1-0aa3fd092c9f.jpg)


