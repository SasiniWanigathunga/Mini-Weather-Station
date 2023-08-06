# WeatherWise - Mini Weather Station
Welcome to WeatherWise, a mini weather station project created by me as part of a university endeavor in the field of electronics and sensors.
## Overview
WeatherWise is a smart and connected weather station designed to measure temperature, humidity, atmospheric pressure, and ambient light intensity. It provides real-time weather data that can be accessed through a web dashboard and a mobile application.
## Key Features
1. Accurate and Reliable Measurements: WeatherWise is equipped with high-quality sensors (BMP280, HTU21D, and LDR) that deliver precise and reliable weather data.
2. WiFi Connectivity: The weather station connects to the Blynk IoT platform via WiFi, allowing users to monitor weather data from anywhere using a web dashboard or mobile app.
3. Power Optimization: WeatherWise employs power-saving techniques to maximize battery life, including data transmission at specific intervals and reduced current consumption.
4. Buzzer Alert: The integrated buzzer provides alerts during extreme weather conditions, ensuring users stay informed about significant weather changes.
## Design Process
### PCB Design
![pcb](https://github.com/SasiniWanigathunga/Mini-Weather-Station/assets/92870335/b7c275fa-4b74-4834-8cb9-7cb28a54b0db)
### Enclosure Design
![enclosure2](https://github.com/SasiniWanigathunga/Mini-Weather-Station/assets/92870335/4e048c23-27f8-40a5-9f4e-1684eb879e60)

All the design files including schematic design files, PCB design files and enclosure design files are shared in this repository. 
## Specifications
### Measurement Ranges:
+ Temperature: -40°C to 85°C
+ Atmospheric Pressure: 300hPa to 1100hPa
+ Humidity: 0% to 100% RH
+ Ambient Light Intensity: 0 lux to 1000 lux
### Power Source:
+ Battery: Rechargeable Li-ion (3.7V, 1800mAh)
+ Charging: Micro USB with 5V adapter
+ Battery Life:
  + With display continuously on: Approximately 22 hours
  + With display turned off: Approximately 33 hours
## Hardware and Software
+ ESP32 DevKit V1 development board
+ BMP280, HTU21D, and LDR sensors
+ Custom PCB design using Altium Designer
+ SolidWorks 2020 for enclosure design
## Installation and Setup
+ Clone this repository to your local machine.
+ Follow the hardware assembly instructions in the provided documentation.
+ Upload the firmware to the ESP32 board using the Arduino IDE.
+ Power on WeatherWise using a 5V adapter or rechargeable Li-ion battery.
## Usage
+ Connect WeatherWise to your WiFi network using the provided instructions.
+ Access real-time weather data through the web dashboard or mobile application.
## Validation and Testing
WeatherWise has undergone rigorous validation and testing to ensure accurate measurements and reliable performance. It has been exposed to various weather conditions, and the buzzer activation during extreme weather events has been thoroughly assessed.
## Contributing
We welcome contributions from the open-source community! If you have any ideas, bug fixes, or enhancements, feel free to submit a pull request.
