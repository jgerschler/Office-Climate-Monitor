import processing.serial.*;

Serial myPort;        
IntList data;
IntList dataScaled;
float inByte = 0;
PFont f;

void setup () {
  size(400, 300);
  f = createFont("Arial",16,true);
  data = new IntList( 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 );
  dataScaled = new IntList( 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 );
  myPort = new Serial(this, Serial.list()[1], 9600);
  myPort.bufferUntil('\n');
  background(224, 224, 224);
}

void draw () {
  background(224, 224, 224);
  textAlign(CENTER);
  textFont(f,11);
  text("Approximate PM2.5 Concentration in Teotitlán de Flores de Magon, Oaxaca", width / 2, 20);
  text("Last updated " + str(day()) + "/" + str(month()) + "/" + str(year()) + " " + str(hour()) + ":" + str(minute()) + ". Bars represent half hour intervals. Units: μg/m3", width / 2, 40);
  textFont(f,16);
  for(int i = 0; i < 10; i++) {
    if (data.get(i) <= 50) {
      fill(0, 228, 0);
    } else if (data.get(i) <= 100) {
      fill(255, 255, 0);
    } else if (data.get(i) <= 150) {
      fill(255, 128, 0);
    } else if (data.get(i) <= 200) {
      fill(255, 0, 0);
    } else if (data.get(i) <= 300) {
      fill(143, 63, 151);
    } else if (data.get(i) <= 500) {
      fill(126, 0, 35);
    } else {
      fill(128, 128, 128);
    }
    rect((2 * i + 1) * (width / 21), height - dataScaled.get(i), width / 21, height);
    fill(0);
    text(str(data.get(i)), (2 * i + 1) * (width / 21), height - dataScaled.get(i) - 20);
  }
}

void serialEvent (Serial myPort) {
  String inString = myPort.readStringUntil('\n');

  if (inString != null) {
    inString = trim(inString);
    inByte = float(inString);
    data.remove(0);
    data.append(round(inByte));
    dataScaled.remove(0);
    dataScaled.append(round(map(inByte, 0, 500, 0, height - 20)));
  }
}