# PROCUDRE TO INSTALL Fonctionnal components ( hostapd, mosquitto, grafana, influxdb... )

connect to your Raspi with  
>
    ssh pi@RASPI_IP_ADDRESS + password ( defautl = raspberry )  
and execute the following commands  

# Install Access Point with Hostapd & dnsmasq ( [Using this repository](https://github.com/TamataOcean/rpi_wifi_direct.git) )
Configure AP SSID = WifiRaspi  
Password = raspberry  
IP = 172.24.1.1  

>
    sudo -s
    mkdir /home/pi/code
    cd /home/pi/code
    wget -P /home/pi/code https://raw.githubusercontent.com/TamataOcean/rpi_wifi_direct/master/raspberry_pi4/install_wifi_direct.sh
    chmod +x /home/pi/code/install_wifi_direct.sh
    bash -x /home/pi/code/install_wifi_direct.sh

# Install InfluxDB on Raspi 4 ( Buster ) : [Source here](https://computingforgeeks.com/install-influxdb-on-debian-10-buster-linux/)
#### Add InfluxDB APT repository.
     sudo apt update
     sudo apt install -y gnupg2 curl wget
     wget -qO- https://repos.influxdata.com/influxdb.key | sudo apt-key add -
     echo "deb https://repos.influxdata.com/debian buster stable" | sudo tee /etc/apt/sources.list.d/influxdb.list

#### Once the repository is added, install InfluxDB on Debian 10 (Buster) Linux:
     sudo apt update
     sudo apt install -y influxdb

InfluxDB default configuration file is located under /etc/influxdb/influxdb.conf. Most sections are commented out, you can modify it to your liking and restart influxdb service after.

#### Start and enable the service to start on boot up.

     sudo systemctl enable --now influxdb

# Install Grafana
>
    echo "deb https://packages.grafana.com/oss/deb stable main" | sudo tee /etc/apt/sources.list.d/grafana.list
    wget -q -O - https://packages.grafana.com/gpg.key | sudo apt-key add -
    sudo apt-get update
    sudo apt-get install apt-transport-https
    sudo apt-get install -y grafana
    sudo update-rc.d grafana defaults
    sudo systemctl daemon-reload
    sudo systemctl enable grafana.service
    sudo systemctl unmask grafana
    sudo systemctl enable grafana-server
    sudo systemctl start grafana-server

# Install Mosquitto Server & Client Install

>     
     sudo apt-get install -y mosquitto
     wget http://repo.mosquitto.org/debian/mosquitto-repo.gpg.key
     sudo apt-key add mosquitto-repo.gpg.key
     cd /etc/apt/sources.list.d/
     sudo wget http://repo.mosquitto.org/debian/mosquitto-buster.list
     #sudo -i 
     sudo apt-get update 
     sudo apt-get install -y mosquitto
     sudo apt-get install -y mosquitto-clients
     cd

# Install NodeJS
    curl -sL https://deb.nodesource.com/setup_10.x | sudo bash -
    sudo apt-get install -y nodejs

# Install Systools service for BME280
    cd
    mkdir code
    cd code/
    git clone https://github.com/TamataOcean/esp32Bme280.git
    cd esp32Bme280/systools/
    npm install
    cd

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
