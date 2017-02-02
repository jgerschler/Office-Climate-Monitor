/*Things that need to be done:
  Set up millis timers:
  1)Check every ten seconds if lights have been turned off.
    a)inside loop, check if analog voltage has changed past threshold.
      i)if yes, then turn on LCD backlight, and set pins high for ambient lighting.
      ii)if lights are already on, keep on, etc.
  1.5)Switch every ten seconds to secondary OLED display.
    a)plot data held in respective array.
  2)Check every minute for new environmental data.
    a)update array
    b)update LCD
  3)Plot every minute environmental data.

  ALTER WIRING FOR DAISY-CHAINING I2C DEVICES!!!!!

  add scaling!

  check array sizes

  increment index
*/

//#include <SPI.h>//do we need this?
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define OLED_RESET 4
#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme;
Adafruit_SSD1306 display(OLED_RESET);
LiquidCrystal_I2C LCD(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

int temperature_array[121];
int pressure_array[121];
int humidity_array[121];
int min_temp_y = 0;
int max_temp_y = 0;
int min_val;
int max_val;
int value = 1; //delete this later
float val_temp;
float val_humidity;
float val_pressure;
float val_altitude;
unsigned long previousMillis = 0;
int index = 0;

void setup()   {
  //  Serial.begin(9600);
  //get data here before updating displays
  read_sensor();
  
  LCD.begin(20, 4);
  LCD.clear();
  LCD.backlight();//fix later
  LCD.setCursor(0, 0);
  LCD.print("Temp: "+String(val_temp));
  LCD.setCursor(0, 1);
  LCD.print("Humidity: "+String(val_humidity));
  LCD.setCursor(0, 2);
  LCD.print("Pressure: "+String(val_pressure));
  LCD.setCursor(0, 3);
  LCD.print("Altitude: "+String(val_altitude));

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
}

void update_lcd {
  LCD.clear();
  LCD.setCursor(0, 0);
  LCD.print("Temp: "+String(val_temp));
  LCD.setCursor(0, 1);
  LCD.print("Humidity: "+String(val_humidity));
  LCD.setCursor(0, 2);
  LCD.print("Pressure: "+String(val_pressure));
  LCD.setCursor(0, 3);
  LCD.print("Altitude: "+String(val_altitude));
}

void read_sensor {
  val_temp = bme.readTemperature();
  val_pressure = bme.readPressure() / 100.0F;
  val_altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);
  val_humidity = bme.readHumidity();
}

void update_arrays() {
  if index
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 10000) {
    //things happening every ten seconds
    //refresh OLED
    //check light
    previousMillis = currentMillis;
  }
  if (currentMillis - previousMillis >= 60000) {
    //things happening every minute --> update counter for arrays,
    previousMillis = currentMillis;
    //sample sensor
    read_sensor();
    //update arrays
    
    //update lcd
    update_lcd();
    //check if there is space in array
    if (index <= 120) {
      //array still has space
      temperature_array[index] = round(val_temp);
      pressure_array[index] = round(val_pressure);
      humidity_array[index] = round(val_humidity);
      
    }
    else {
      //array is full

    }
  }
}

void temp_oled() {
  //update min, max, and scaling of window
  if (min_temp_y == max_temp_y) {
    min_temp_y = floor(val_temp * 0.5);
    max_temp_y = ceil(val_temp * 1.5);
    min_val = val_temp;
    max_val = val_temp;
  }
  if (val_temp > max_val) {
    max_val = val_temp;
    max_temp_y = ceil(val_temp * 1.5);
  }
  if (val_temp < min_val) {
    min_val = val_temp;
    min_temp_y = floor(val_temp * 0.5);
  }
  //array isn't full, so just plot what's there
  if (index < 120) {
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.clearDisplay();
    display.println("Temp:");
    display.drawLine(0, 19, 0, 60, WHITE);
    display.setTextSize(1);
    display.setCursor(3, 16);
    display.println(String(max_temp_y));
    display.setCursor(3, 57);
    display.println(String(min_temp_y));
    for (i=0; i<=index; i++) {
      display.drawPixel(i+1, temperature_array[i], WHITE);//fix scaling!
    }
    display.display();
  }
  //array is full
  else {
    for (i=0; i<120; i++) {//check numbers, imax
      temperature_array[i] = temperature_array[i+1];
    }
    temperature_array[120] = round(val_temp);
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.clearDisplay();
    display.println("Temp:");
    display.drawLine(0, 19, 0, 60, WHITE);
    display.setTextSize(1);
    display.setCursor(3, 16);
    display.println(String(max_temp_y));
    display.setCursor(3, 57);
    display.println(String(min_temp_y));
    for (i=0; i<=120; i++) {
      display.drawPixel(i+1, temperature_array[i], WHITE);//fix scaling!
    }
    display.display();
  }




  
  else {
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.clearDisplay();
    display.println("Temp:");
    display.drawLine(0, 19, 0, 60, WHITE);
    display.setTextSize(1);
    display.setCursor(3, 16);
    display.println(String(max_temp_y));
    display.setCursor(3, 57);
    display.println(String(min_temp_y));
    display.display();
  }
}
