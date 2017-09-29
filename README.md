# Office-Climate-Monitor
A personal project for monitoring the office humidity, temperature, pressure and altitude.

Altitude is calculated from barometric pressure, and is only an estimate. If actual sea-level value at location is known, a more accurate estimate can be obtained.

A couple important troubleshooting tips:

-Remember to install all required libraries:

Adafruit-GFX
Adafruit_Sensor
Adafruit_BME280
Adafruit_SSD1306
NewliquidCrystal (by fmalpartida)

These were the libraries used in this project, but your needs will depend on the hardware you are using.

-You may need to change the I2C address from 0x77 to 0x76 in the Adafruit_BME280.h file in the BME280 library.

-Remember to specify your display size in Adafruit_SSD1306.h

Good luck!
