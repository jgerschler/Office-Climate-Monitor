#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>// NOTE: you may need to change I2C address in library from 0x77 to 0x76, depending on which sensor you're using. You'll see a reported pressure of 0, or an altitude of 44300m if the address is incorrect.

Adafruit_BME280 bme;

//includes modified waveshare wiki code
#define        COV_RATIO                       0.2            //ug/mmm / mv
#define        NO_DUST_VOLTAGE                 400            //mv
#define        SYS_VOLTAGE                     5000           

const int iled = 24;                                            //infrared led
const int vout = A0;                                            //analog input

float density, voltage;
float val_temp;
float val_hum;
float val_pres;
int adcvalue;
int pm25;
int hum;
int pres;
int temp;

int Filter(int m)
{
  static int flag_first = 0, _buff[10], sum;
  const int _buff_max = 10;
  int i;
  
  if(flag_first == 0)
  {
    flag_first = 1;

    for(i = 0, sum = 0; i < _buff_max; i++)
    {
      _buff[i] = m;
      sum += _buff[i];
    }
    return m;
  }
  else
  {
    sum -= _buff[0];
    for(i = 0; i < (_buff_max - 1); i++)
    {
      _buff[i] = _buff[i + 1];
    }
    _buff[9] = m;
    sum += _buff[9];
    
    i = sum / 10.0;
    return i;
  }
}


void setup() {
  bme.begin();
  read_sensor();
  
  pinMode(iled, OUTPUT);
  digitalWrite(iled, LOW);                                     
  
  Serial.begin(9600);                                         
}

void loop(void)
{
  digitalWrite(iled, HIGH);
  delayMicroseconds(280);
  adcvalue = analogRead(vout);
  digitalWrite(iled, LOW);
  
  adcvalue = Filter(adcvalue);

  voltage = (SYS_VOLTAGE / 1024.0) * adcvalue * 11;
  
  if(voltage >= NO_DUST_VOLTAGE)
  {
    voltage -= NO_DUST_VOLTAGE;
    
    density = voltage * COV_RATIO;
  }
  else
    density = 0;

  read_sensor();
  
  pm25 = (int) density;
  hum = (int) val_hum;
  pres = (int) val_pres;
  temp = (int) val_temp;

  // might decide to avoid String function in the future
  String pm25String = String(pm25);
  String humString = String(hum);
  String presString = String(pres);
  String tempString = String(temp);
  String dataString = pm25String + "-" + humString + "-" + presString + "-" + tempString;

  Serial.println(dataString);
  
  delay(1000);
}

void read_sensor() {
  val_temp = bme.readTemperature();
  val_pres = bme.readPressure() / 100.0F;
  val_hum = bme.readHumidity();
}
