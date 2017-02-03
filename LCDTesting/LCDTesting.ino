#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C LCD(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

void setup() {
    LCD.begin(20, 4);  // 20 lines by 4 rows
    LCD.clear();
    LCD.setBacklight(0);
    LCD.setCursor(0,0);
    LCD.print("Hello Line 1");
    LCD.setCursor(0,1);
    LCD.print("Hello Line 2");
}

void loop() {
    LCD.setBacklight(0);
    delay(1000);
    LCD.setBacklight(1);
    LCD.clear();
    LCD.home();
    LCD.print(millis());
}
