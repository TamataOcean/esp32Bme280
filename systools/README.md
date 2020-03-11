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
     sudo apt install nodejs
     node --version

Should see : v10.16.0
