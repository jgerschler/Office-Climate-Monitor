import grafica.*;
import java.util.Random;
import processing.serial.*;

GPlot plot1, plot2, plot3, plot4;
Serial myPort;        
IntList data;
IntList dataScaled;
float inByte = 0;
int nPoints = 20;
GPointsArray points = new GPointsArray(nPoints);

void setup () {
  size(1366, 768);
  this.surface.setTitle("Environmental Monitor");

  data = new IntList( 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 );
  dataScaled = new IntList( 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 );
  myPort = new Serial(this, Serial.list()[1], 9600);
  myPort.bufferUntil('\n');
  
  plot1 = new GPlot(this);
  plot1.setPos(0, 20);
  plot1.setDim(1220, 100);
  plot1.getTitle().setText("Temperature (\u00B0C)");

  plot2 = new GPlot(this);
  plot2.setPos(0, 190);
  plot2.setDim(1220, 100);
  plot2.getTitle().setText("Humidity (%)");

  plot3 = new GPlot(this);
  plot3.setPos(0, 360);
  plot3.setDim(1220, 100);
  plot3.getTitle().setText("Barometric Pressure (cPa)");
  
  plot4 = new GPlot(this);
  plot4.setPos(0, 20);
  plot4.setDim(1220, 600);
  plot4.getTitle().setText("Approximate PM2.5 (\u03BCg/m\u00B3)");
}

void draw () {
  background(255);
 
  /*
  plot1.beginDraw();
  plot1.drawBackground();
  plot1.drawBox();
  plot1.drawXAxis();
  plot1.drawYAxis();
  plot1.drawTitle();
  plot1.drawGridLines(GPlot.BOTH);
  plot1.drawLines();
  plot1.endDraw();

  plot2.beginDraw();
  plot2.drawBackground();
  plot2.drawBox();
  plot2.drawXAxis();
  plot2.drawYAxis();
  plot2.drawTitle();
  plot2.drawGridLines(GPlot.BOTH);
  plot2.drawLines();
  plot2.endDraw();

  plot3.beginDraw();
  plot3.drawBackground();
  plot3.drawBox();
  plot3.drawXAxis();
  plot3.drawYAxis();
  plot3.drawTitle();
  plot3.drawGridLines(GPlot.BOTH);
  plot3.drawLines();
  plot3.endDraw();
  */

  for(int i = 0; i < nPoints; i++){
    points.add(i, dataScaled.get(i));
  }
  plot4.beginDraw();
  plot4.drawBackground();
  plot4.drawBox();
  plot4.drawXAxis();
  plot4.drawYAxis();
  plot4.drawTitle();
  plot4.drawGridLines(GPlot.BOTH);
  
  
  plot4.setPoints(points);
  plot4.drawPoints();
  plot4.endDraw();  


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