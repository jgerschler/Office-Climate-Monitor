
import grafica.*;
import java.util.Random;

public GPlot plot1, plot2, plot3, plot4;
public GPointsArray polygonPoints;
public float[] gaussianStack;
public float[] uniformStack;
public int gaussianCounter;
public int uniformCounter;
public PImage mug;
public PShape star;
public Random r;

public void setup() {
  size(1024, 768);



  // Setup for the first plot
  plot1 = new GPlot(this);
  plot1.setPos(0, 0);
  plot1.setXLim(1, 100);
  plot1.setYLim(0.1, 3);
  plot1.getTitle().setText("Multiple layers plot");
  plot1.getXAxis().getAxisLabel().setText("Time");
  plot1.getYAxis().getAxisLabel().setText("noise (0.1 time)");
  plot1.setLogScale("xy");
  plot1.setPoints(points1a);
  plot1.setLineColor(color(200, 200, 255));
  plot1.addLayer("layer 1", points1b);
  plot1.getLayer("layer 1").setLineColor(color(150, 150, 255));
  plot1.addLayer("layer 2", points1c);
  plot1.getLayer("layer 2").setLineColor(color(100, 100, 255));


  // Leave empty the points for the second plot. We will fill them in draw()

  // Setup for the second plot 
  plot2 = new GPlot(this);
  plot2.setPos(460, 0);
  plot2.setDim(250, 250);
  plot2.getTitle().setText("Mouse position");
  plot2.getXAxis().getAxisLabel().setText("mouseX");
  plot2.getYAxis().getAxisLabel().setText("-mouseY");

  // Setup for the third plot 
  plot3 = new GPlot(this);
  plot3.setPos(0, 300);
  plot3.setDim(250, 250);
  plot3.setYLim(-0.02, 0.45);
  plot3.setXLim(5, -5);
  plot3.getTitle().setText("Gaussian distribution (" + str(gaussianCounter) + " points)");
  plot3.getTitle().setTextAlignment(LEFT);
  plot3.getTitle().setRelativePos(0);
  plot3.getYAxis().getAxisLabel().setText("Relative probability");
  plot3.getYAxis().getAxisLabel().setTextAlignment(RIGHT);
  plot3.getYAxis().getAxisLabel().setRelativePos(1);
  plot3.setPoints(points3);
  plot3.startHistograms(GPlot.VERTICAL);
  plot3.getHistogram().setDrawLabels(true);
  plot3.getHistogram().setRotateLabels(true);
  plot3.getHistogram().setBgColors(new color[] {
    color(0, 0, 255, 50), color(0, 0, 255, 100), 
    color(0, 0, 255, 150), color(0, 0, 255, 200)
  }
  );


  // Setup for the fourth plot 
  plot4 = new GPlot(this);
  plot4.setPos(370, 350);
  plot4.setYLim(-0.005, 0.1);
  plot4.getTitle().setText("Uniform distribution (" + str(uniformCounter) + " points)");
  plot4.getTitle().setTextAlignment(LEFT);
  plot4.getTitle().setRelativePos(0.1);
  plot4.getXAxis().getAxisLabel().setText("x variable");
  plot4.getYAxis().getAxisLabel().setText("Relative probability");
  plot4.setPoints(points4);
  plot4.startHistograms(GPlot.VERTICAL);

  // Setup the mouse actions
  plot1.activatePanning();
  plot1.activateZooming(1.2, CENTER, CENTER);
  plot1.activatePointLabels();
  plot2.activateZooming(1.5);
  plot3.activateCentering(LEFT, GPlot.CTRLMOD);
  plot4.activateZooming();

  // Load some images and shapes to use later in the plots
  mug = loadImage("beermug.png");
  mug.resize(int(0.7*mug.width), int(0.7*mug.height));
  star = loadShape("star.svg");
  star.disableStyle();
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
  plot1.drawPoints(star);
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
  plot2.drawPoints(star);
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
  plot3.drawPoints(star);
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
  plot4.drawPoints(star);
  plot4.endDraw();
}