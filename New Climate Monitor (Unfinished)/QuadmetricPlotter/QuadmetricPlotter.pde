import grafica.*;
//import java.util.Random;
import processing.serial.*;

int index = 0;
int numVals = 100;
int[] nums = {0, 0, 0, 0};

float inByte = 0;

float[] PM25Vals = new float[numVals];
float[] HumidityVals = new float[numVals];
float[] BarometricVals = new float[numVals];
float[] TemperatureVals = new float[numVals];

GPointsArray PM25Points = new GPointsArray(numVals);
GPointsArray HumidityPoints = new GPointsArray(numVals);
GPointsArray BarometricPoints = new GPointsArray(numVals);
GPointsArray TemperaturePoints = new GPointsArray(numVals);

GPlot plot1, plot2, plot3, plot4;
Serial myPort;   

void setup () {
  size(1366, 768);
  this.surface.setTitle("Environmental Monitor");

  myPort = new Serial(this, Serial.list()[1], 9600);
  myPort.bufferUntil('\n');
  
  plot1 = new GPlot(this);
  plot1.setPos(0, 20);
  plot1.setDim(1220, 100);
  plot1.setXLim(1, 100);
  plot1.setPointSize(5);
  plot1.getTitle().setText("Approximate PM2.5 (\u03BCg/m\u00B3)");

  plot2 = new GPlot(this);
  plot2.setPos(0, 190);
  plot2.setDim(1220, 100);
  plot2.setXLim(1, 100);
  plot2.setPointSize(5);
  plot2.setLineColor(color(255, 0, 0));
  plot2.setPointColor(color(255, 0, 0));
  plot2.getTitle().setText("Humidity (%)");

  plot3 = new GPlot(this);
  plot3.setPos(0, 360);
  plot3.setDim(1220, 100);
  plot3.setXLim(1, 100);
  plot3.setPointSize(5);
  plot3.setLineColor(color(0, 255, 0));
  plot3.setPointColor(color(0, 255, 0));
  plot3.getTitle().setText("Barometric Pressure (cPa)");
  
  plot4 = new GPlot(this);
  plot4.setPos(0, 530);
  plot4.setDim(1220, 100);
  plot4.setXLim(1, 100);
  plot4.setPointSize(5);
  plot4.setLineColor(color(0, 0, 255));
  plot4.setPointColor(color(0, 0, 255));
  plot4.getTitle().setText("Temperature (\u00B0C)");
}

void draw () {
  PM25Points = new GPointsArray();
  HumidityPoints = new GPointsArray();
  BarometricPoints = new GPointsArray();
  TemperaturePoints = new GPointsArray();
  color[] pointColors = new color[numVals];
  for (int i=0; i < index; i++) {
    PM25Points.add(i+1, PM25Vals[i]);
    HumidityPoints.add(i+1, HumidityVals[i]);
    BarometricPoints.add(i+1, BarometricVals[i]);
    TemperaturePoints.add(i+1, TemperatureVals[i]);
    if (PM25Vals[i] < 51) {
      pointColors[i] = color(0, 255, 0);
    }
    else if (PM25Vals[i] < 101) {
      pointColors[i] = color(255, 255, 0);
    }
    else if (PM25Vals[i] < 151) {
      pointColors[i] = color(255, 165, 0);
    }
    else if (PM25Vals[i] < 201) {
      pointColors[i] = color(255, 0, 0);
    }
    else if (PM25Vals[i] < 301) {
      pointColors[i] = color(138, 43, 226);
    }
    else if (PM25Vals[i] < 501) {
      pointColors[i] = color(178, 34, 34);
    }
    else {
      pointColors[i] = color(0, 0, 0);
    }    
  }
  
  background(255);
 
  plot1.setPoints(PM25Points);
  plot1.setPointColors(pointColors); 
  plot1.beginDraw();
  plot1.drawBackground();
  plot1.drawBox();
  plot1.drawXAxis();
  plot1.drawYAxis();
  plot1.drawTitle();
  plot1.drawGridLines(GPlot.BOTH);
  plot1.drawPoints();
  plot1.drawLines();
  plot1.endDraw();

  plot2.setPoints(HumidityPoints);
  plot2.beginDraw();
  plot2.drawBackground();
  plot2.drawBox();
  plot2.drawXAxis();
  plot2.drawYAxis();
  plot2.drawTitle();
  plot2.drawGridLines(GPlot.BOTH);
  plot2.drawPoints();
  plot2.drawLines();
  plot2.endDraw();
  
  plot3.setPoints(BarometricPoints);
  plot3.beginDraw();
  plot3.drawBackground();
  plot3.drawBox();
  plot3.drawXAxis();
  plot3.drawYAxis();
  plot3.drawTitle();
  plot3.drawGridLines(GPlot.BOTH);
  plot3.drawPoints();
  plot3.drawLines();
  plot3.endDraw();

  plot4.setPoints(TemperaturePoints);
  plot4.beginDraw();
  plot4.drawBackground();
  plot4.drawBox();
  plot4.drawXAxis();
  plot4.drawYAxis();
  plot4.drawTitle();
  plot4.drawGridLines(GPlot.BOTH);
  plot4.drawPoints();
  plot4.drawLines();
  plot4.endDraw();  
}

void serialEvent (Serial myPort) {
  String inString = myPort.readStringUntil('\n');

  if (inString != null) {
    inString = trim(inString);
    nums = int(split(inString, '-'));
    if (nums.length == 4) {
      PM25Vals[index] = nums[0];
      HumidityVals[index] = nums[1];
      BarometricVals[index] = nums[2];
      TemperatureVals[index] = nums[3];
      index++;
      if (index == 100) {
        index = 0;
      }
    }
    println(nums);
  }
}