/*A smaller version for the Arduino UNO that doesn't
  show the pressure plot data.*/

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

int temp_array[121];
int hum_array[121];
int min_temp_y = 0;
int max_temp_y = 0;
int min_hum_y = 0;
int max_hum_y = 0;
int min_temp_val;
int max_temp_val;
int min_hum_val;
int max_hum_val;
float val_temp;
float val_hum;
float val_pres;
float val_alt;
unsigned long previousMillis = 0;
byte index = 0;
bool oled_disp = 0;

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
  LCD.backlight();
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
  if (currentMillis - previousMillis >= 5000) {// change to 10000 later
    previousMillis = currentMillis;
    //check lights here
    if (oled_disp == 0) {
      temp_oled();
      oled_disp = 1;
    }
    else {
      hum_oled();
      oled_disp = 0;
    }
  }
  if (currentMillis - previousMillis >= 10000) {// change to 60000 later
    previousMillis = currentMillis;
    read_sensor();
    update_lcd();
    //check if there is space in array
    if (index <= 120) {
      temp_array[index] = round(val_temp);
      hum_array[index] = round(val_hum);
      index+=1;
    }
    else {
      for (int i=0; i<120; i++) {
        temp_array[i] = temp_array[i+1];
        hum_array[i] = hum_array[i+1];
      }
      temp_array[120] = round(val_temp);
      hum_array[120] = round(val_hum);
    }
  }
}

void temp_oled() {
  if (min_temp_y == max_temp_y) {
    min_temp_y = floor(val_temp * 0.5);
    max_temp_y = ceil(val_temp * 1.5);
    min_temp_val = val_temp;
    max_temp_val = val_temp;
  }
  if (val_temp > max_temp_val) {
    max_temp_val = val_temp;
    max_temp_y = ceil(val_temp * 1.5);
  }
  if (val_temp < min_temp_val) {
    min_temp_val = val_temp;
    min_temp_y = floor(val_temp * 0.5);
  }
  // array isn't full, or just full
  if (index-1 <= 120) {
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
    for (int i=0; i<=120; i++) {
      display.drawPixel(i+1, 41*(max_temp_y - temp_array[i])/(max_temp_y - min_temp_y) + 19, WHITE);
    }
    display.display();
  }
}

void hum_oled() {
  if (min_hum_y == max_hum_y) {
    min_hum_y = floor(val_hum * 0.5);
    max_hum_y = ceil(val_hum * 1.5);
    min_hum_val = val_hum;
    max_hum_val = val_hum;
  }
  if (val_hum > max_hum_val) {
    max_hum_val = val_hum;
    max_hum_y = ceil(val_hum * 1.5);
  }
  if (val_hum < min_hum_val) {
    min_hum_val = val_hum;
    min_hum_y = floor(val_hum * 0.5);
  }
  if (index-1 <= 120) {
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.clearDisplay();
    display.println("Humidity:");
    display.drawLine(0, 19, 0, 60, WHITE);
    display.setTextSize(1);
    display.setCursor(3, 16);
    display.println(String(max_hum_y));
    display.setCursor(3, 57);
    display.println(String(min_hum_y));
    for (int i=0; i<=index-1; i++) {
      display.drawPixel(i+1, 41*(max_hum_y - hum_array[i])/(max_hum_y - min_hum_y) + 19, WHITE);
    }
    display.display();
  }
  else {
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.clearDisplay();
    display.println("Humidity:");
    display.drawLine(0, 19, 0, 60, WHITE);
    display.setTextSize(1);
    display.setCursor(3, 16);
    display.println(String(max_hum_y));
    display.setCursor(3, 57);
    display.println(String(min_hum_y));
    for (int i=0; i<=120; i++) {
      display.drawPixel(i+1, 41*(max_hum_y - hum_array[i])/(max_hum_y - min_hum_y) + 19, WHITE);
    }
    display.display();
  }
}
