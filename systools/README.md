# Raspi Install

### Access Point
[Procedure here](https://thepi.io/how-to-use-your-raspberry-pi-as-a-wireless-access-point/)

### Install InfluxDB - Grafana
[OLD Procedure here](https://github.com/TamataOcean/TamataSpiru/wiki/Install-Influx,-Graphana)


### Mosquitto Server & Client Install

>     
     sudo apt-get install mosquitto
     wget http://repo.mosquitto.org/debian/mosquitto-repo.gpg.key
     sudo apt-key add mosquitto-repo.gpg.key
     cd /etc/apt/sources.list.d/
     sudo wget http://repo.mosquitto.org/debian/mosquitto-wheezy.list
     sudo -i 
     apt-get update 
     apt-get install mosquitto 
     apt-get install mosquitto-clients

### NodeJS
>
     curl -sL https://deb.nodesource.com/setup_10.x | sudo bash -
     sudo apt-get install -y nodejs
     node --version
Should see : v10.16.0

## Install esp32Bme280 Service
     git clone https://github.com/TamataOcean/esp32Bme280.git
     cd esp32Bme280/systools
     npm install

### save_data.js
In charge of listening Mosquitto, when a message arrive, keeping BME280 Sensor information and push to InfluxDB 
     
     node save_data.js
     [Format]
     {"user":"BME280-Station1","Humidity":"41.86","Pressure":"102229.23","Altitude":"-75.00","Temperature":"26.84"}

### Configure service esp32Bme280
#### Create file : /lib/systemd/system/esp32Bme280.service 

     [Unit]
      Description=esp32Bme280
      After=multi-user.target

      [Service]
      WorkingDirectory=/home/pi/code/esp32Bme280/systools
      ExecStart=/usr/bin/node save_data.js
      Restart=on-failure

      [Install]
      WantedBy=multi-user.target

#### Declare service  
      sudo systemctl enable esp32Bme280.service  

#### Start service  
      sudo systemctl start esp32Bme280.service  

#### Log Service
      sudo journalctl -u esp32Bme280.service 
