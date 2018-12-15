
import grafica.*;
import java.util.Random;

public GPlot plot1, plot2, plot3, plot4;
//public GPointsArray polygonPoints;
//public float[] gaussianStack;
//public float[] uniformStack;
//public int gaussianCounter;
//public int uniformCounter;
//public PImage mug;
public PShape star;
PFont f;
//public Random r;

public void setup() {
  size(1366, 768);
  f = createFont("Arial",11,true);
  




  plot1 = new GPlot(this);
  plot1.setPos(0, 50);
  plot1.setDim(1300, 100);
  plot1.getTitle().setText("Temperature (C)");
  //plot1.getXAxis().getAxisLabel().setText("mouseX");
  plot1.getYAxis().getAxisLabel().setText("-mouseY");

  plot2 = new GPlot(this);
  plot2.setPos(0, 190);
  plot2.setDim(1000, 100);
  plot2.getTitle().setText("Humidity (%)");
  //plot2.getXAxis().getAxisLabel().setText("mouseX");
  plot2.getYAxis().getAxisLabel().setText("-mouseY");

  plot3 = new GPlot(this);
  plot3.setPos(0, 400);
  plot3.setDim(1000, 100);
  plot3.getTitle().setText("Barometric Pressure (cPa)");
  //plot3.getXAxis().getAxisLabel().setText("mouseX");
  plot3.getYAxis().getAxisLabel().setText("-mouseY");
  
  plot4 = new GPlot(this);
  plot4.setPos(0, 500);
  plot4.setDim(1000, 100);
  plot4.getTitle().setText("Approximate PM2.5 (mg/m3)");
 // plot4.getXAxis().getAxisLabel().setText("mouseX");
  plot4.getYAxis().getAxisLabel().setText("-mouseY");


}


public void draw() {
  background(255);

  // Draw the first plot
  plot1.beginDraw();
  plot1.drawBackground();
  plot1.drawBox();
  plot1.drawXAxis();
  plot1.drawYAxis();
  plot1.drawTitle();
  plot1.drawGridLines(GPlot.BOTH);
  plot1.drawLines();
  plot1.endDraw();

  // Draw the second plot  
  plot2.beginDraw();
  plot2.drawBackground();
  plot2.drawBox();
  plot2.drawXAxis();
  plot2.drawYAxis();
  plot2.drawTitle();
  plot2.drawGridLines(GPlot.BOTH);
  plot2.drawLines();
  plot2.endDraw();

  // Draw the third plot  
  plot3.beginDraw();
  plot3.drawBackground();
  plot3.drawBox();
  plot3.drawXAxis();
  plot3.drawYAxis();
  plot3.drawTitle();
  plot3.drawGridLines(GPlot.BOTH);
  plot3.drawLines();
  plot3.endDraw();

  // Draw the forth plot  
  plot4.beginDraw();
  plot4.drawBackground();
  plot4.drawBox();
  plot4.drawXAxis();
  plot4.drawYAxis();
  plot4.drawTitle();
  plot4.drawGridLines(GPlot.BOTH);
  plot4.drawLines();
  plot4.endDraw();
  
  textAlign(CENTER);
  textFont(f,11);
  fill(0);
  text("Approximate PM2.5 Concentration in Teotitlán de Flores de Magon, Oaxaca", width / 2, 620);
  text("Last updated " + str(day()) + "/" + str(month()) + "/" + str(year()) + " " + str(hour()) + ":" + str(minute()) + ". Bars represent half hour intervals. Units: μg/m3", width / 2, 640);
}