#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1030.00)//modify with local sea level pressure -- normal is 1013.25 hPa

Adafruit_BME280 bme;
Adafruit_SSD1306 display(4);
LiquidCrystal_I2C LCD(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

int temp_array[101];
int min_temp_y = 0;
int max_temp_y = 0;
int min_temp_val;
int max_temp_val;
float val_temp;
float val_hum;
float val_pres;
float val_alt;
unsigned long timer2_Millis = 0;
byte index = 0;

void setup()   {
  bme.begin();
  read_sensor();
  
  LCD.begin(20, 4);
  LCD.clear();
  LCD.setCursor(0, 0);
  LCD.print("Temp: "+String(val_temp)+"*C");
  LCD.setCursor(0, 1);
  LCD.print("Humidity: "+String(val_hum)+"%");
  LCD.setCursor(0, 2);
  LCD.print("Pressure: "+String(val_pres)+" hPa");
  LCD.setCursor(0, 3);
  LCD.print("Altitude: "+String(val_alt)+" m");

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
}

void update_lcd() {
  LCD.clear();
  LCD.setCursor(0, 0);
  LCD.print("Temp: "+String(val_temp)+"*C");
  LCD.setCursor(0, 1);
  LCD.print("Humidity: "+String(val_hum)+"%");
  LCD.setCursor(0, 2);
  LCD.print("Pressure: "+String(val_pres)+" hPa");
  LCD.setCursor(0, 3);
  LCD.print("Altitude: "+String(val_alt)+" m");
}

void read_sensor() {
  val_temp = bme.readTemperature();
  val_pres = bme.readPressure() / 100.0F;
  val_alt = bme.readAltitude(SEALEVELPRESSURE_HPA);
  val_hum = bme.readHumidity();
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - timer2_Millis >= 60000) {
    timer2_Millis = currentMillis;
    read_sensor();
    update_lcd();
    temp_oled();
    //check if there is space in array
    if (index <= 100) {
      temp_array[index] = round(val_temp);
      index+=1;
    }
    else {
      for (int i=0; i<100; i++) {
        temp_array[i] = temp_array[i+1];
      }
      temp_array[100] = round(val_temp);
    }
  }
}

void temp_oled() {
  if (min_temp_y == max_temp_y) {
    min_temp_y = floor(val_temp * 0.8);
    max_temp_y = ceil(val_temp * 1.2);
    min_temp_val = val_temp;
    max_temp_val = val_temp;
  }
  if (val_temp > max_temp_val) {
    max_temp_val = val_temp;
    max_temp_y = ceil(val_temp * 1.2);
  }
  if (val_temp < min_temp_val) {
    min_temp_val = val_temp;
    min_temp_y = floor(val_temp * 0.8);
  }
  // array isn't full, or just barely full
  if (index-1 <= 100) {
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
    for (int i=0; i<=index-1; i++) {
      display.drawPixel(i+1, 41*(max_temp_y - temp_array[i])/(max_temp_y - min_temp_y) + 19, WHITE);// the formula scales the y-value to the correct range, customized for 128x64 display.
    }
    display.display();
  }
  // array is full
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
    for (int i=0; i<=100; i++) {
      display.drawPixel(i+1, 41*(max_temp_y - temp_array[i])/(max_temp_y - min_temp_y) + 19, WHITE);
    }
    display.display();
  }
}

