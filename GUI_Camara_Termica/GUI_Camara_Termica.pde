import processing.serial.*;

PImage chamberLogo;
PImage thermometer;
PImage humidity;
PImage fanWithColor, fanWithoutColor;
PImage fireWithColor, fireWithoutColor;
PImage lightWithColor, lightWithoutColor;
PImage powerButtonON, powerButtonOFF;
PImage tree;
PImage plantLogo;

Serial port;

/**
 * received[0] -> internal temperatura
 * received[1] -> external temperatura
 * received[2] -> humidity
 * received[3] -> fan on/off
 * received[4] -> heat on/off
 */
Float[] receivedData;

float firstColumn, secondColumn, thirdColumn;

int cornerRadius;
float rectHeight, rectWidth;
float distance;
float rect1X, rect1Y;
float rect2X, rect2Y;
float rect3X, rect3Y;

float buttonX;
float buttonY;

boolean isOverTheButton;

boolean fanON;
boolean heatingON;
boolean powerON;

PFont myTextFont;
String inside;
String outside;
String intTemp;
String extTemp;
String humidityValue;
float textSize;

void setup() {
    frame.setTitle("Bethany");
    /**
     * width = 1200;
     * height = 800;
     */
    size(1200, 800);

    // println(Serial.list()[0]);
    port = new Serial(this, Serial.list()[0], 115200);
    port.clear();

    firstColumn =  width * 0.25 - 7;
    secondColumn = width * 0.5;
    thirdColumn = width * 0.75 + 15;

    rectHeight = 100;
    rectWidth = 210;
    cornerRadius = 15;

    distance = rectHeight * 2;
    rect1X = firstColumn - rectWidth/2;
    rect1Y = height * 0.32 - rectHeight/2 + 7;
    rect2X = firstColumn - rectWidth/2;
    rect2Y = rect1Y + distance;
    rect3X = firstColumn - rectWidth/2;;
    rect3Y = rect2Y + distance;

    chamberLogo = loadImage("./Images/Camara-Termica-Logo.png");
    chamberLogo.resize(0, int(chamberLogo.height * 1.1));

    thermometer = loadImage("./Images/thermometer.png");
    thermometer.resize(0, int(rectHeight));

    humidity = loadImage("./Images/humidity.png");
    humidity.resize(0, int(rectHeight));

    fanWithColor = loadImage("./Images/fan_with_color.png");
    fanWithColor.resize(0, int(rectHeight));
    fanWithoutColor = loadImage("./Images/fan_without_color.png");
    fanWithoutColor.resize(0, int(rectHeight));

    fireWithColor = loadImage("./Images/fire_with_color.png");
    fireWithColor.resize(0, int(rectHeight));
    fireWithoutColor = loadImage("./Images/fire_without_color.png");
    fireWithoutColor.resize(0, int(rectHeight));

    lightWithColor = loadImage("./Images/light_with_color.png");
    lightWithColor.resize(0, int(rectHeight));
    lightWithoutColor = loadImage("./Images/light_without_color.png");
    lightWithoutColor.resize(0, int(rectHeight));

    powerButtonON = loadImage("./Images/power_button_ON.png");
    powerButtonON.resize(0, int(rectHeight * 2));
    powerButtonOFF = loadImage("./Images/power_button_OFF.png");
    powerButtonOFF.resize(0, int(rectHeight * 2));

    tree = loadImage("./Images/tree.png");
    tree.resize(int(width * 0.8), 0);

    plantLogo = loadImage("./Images/plantLogo.png");
    plantLogo.resize(0, int(chamberLogo.height * 0.75));

    buttonX = thirdColumn - powerButtonON.width/2;
    buttonY = rect2Y - powerButtonON.height/2 + rectHeight/2;
    isOverTheButton = false;

    fanON = false;
    heatingON = false;
    powerON = false;

    textSize = 40;
    myTextFont = createFont("Dyuthi.ttf", textSize);
    textFont(myTextFont);
    inside = "Inside";
    outside = "Outside";

    receivedData = new Float[5];

    for (int i = 0; i < 5; i++)
        receivedData[i] = 0.0;

    port.bufferUntil('\n');
}

void draw() {
    background(158, 164, 201);

    image(chamberLogo, secondColumn - chamberLogo.width/2 - plantLogo.width/2, height * 0.12 - chamberLogo.height/2);
    image(plantLogo, secondColumn + plantLogo.width * 1.3, height * 0.13 - chamberLogo.height/2);

    intTemp = String.valueOf(receivedData[0]) + "°C";
    extTemp = String.valueOf(receivedData[1]) + "°C";

    if (receivedData[2] < 0) {
        humidityValue = " - %";
    } else {
        humidityValue = String.valueOf(receivedData[2])  + "%";
    }

    stroke(255);
    strokeWeight(5);
    fill(210);
    rect(rect1X, rect1Y, rectWidth, rectHeight, cornerRadius);
    image(thermometer, rect1X - thermometer.width - 4, rect1Y);
    fill(0, 0, 94);
    text(inside, rect1X + rectWidth/2 - textWidth(inside)/2, rect1Y + rectHeight + textSize + 5);
    fill(0);
    text(intTemp, rect1X + rectWidth/2 - textWidth(intTemp)/2, rect1Y + rectHeight/2 + textSize/4);

    stroke(255);
    strokeWeight(5);
    fill(210);
    rect(rect2X, rect2Y, rectWidth, rectHeight, cornerRadius);
    image(thermometer, rect2X - thermometer.width - 4, rect2Y);
    fill(0, 0, 94);
    text(outside, rect2X + rectWidth/2 - textWidth(outside)/2, rect2Y + rectHeight + textSize + 5);
    fill(0);
    text(extTemp, rect2X + rectWidth/2 - textWidth(extTemp)/2, rect2Y + rectHeight/2 + textSize/4);


    stroke(255);
    strokeWeight(5);
    fill(210);
    rect(rect3X, rect3Y, rectWidth, rectHeight, cornerRadius);
    image(humidity, rect3X - thermometer.width - 11, rect3Y);
    fill(0);
    text(humidityValue, rect3X + rectWidth/2 - textWidth(humidityValue)/2, rect3Y + rectHeight/2 + textSize/4);

    image(tree, width - tree.width * 0.55, height - tree.height * 0.47);

    if (powerON) {
        image(powerButtonON, buttonX, buttonY);
        image(lightWithColor, secondColumn - lightWithColor.width/2, rect2Y);

        fanON = boolean(int(receivedData[3]));
        if (fanON) {
            image(fanWithColor, secondColumn - fanWithColor.width/2, rect1Y);
        } else {
            image(fanWithoutColor, secondColumn - fanWithoutColor.width/2, rect1Y);
        }

        heatingON = boolean(int(receivedData[4]));
        if (heatingON) {
            image(fireWithColor, secondColumn - fireWithColor.width/2, rect3Y);
        } else {
            image(fireWithoutColor, secondColumn - fireWithoutColor.width/2, rect3Y);
        }
    } else {
        image(powerButtonOFF, buttonX, buttonY);
        image(lightWithoutColor, secondColumn - lightWithoutColor.width/2, rect2Y);
        image(fanWithoutColor, secondColumn - fanWithoutColor.width/2, rect1Y);
        image(fireWithoutColor, secondColumn - fireWithoutColor.width/2, rect3Y);
    }

    update(mouseX, mouseY);
}

void serialEvent(Serial p) {
    String temporary;

    /**
     * infos[0] -> start flag
     * infos[1] -> internal temperatura
     * infos[2] -> external temperatura
     * infos[3] -> humidity
     * infos[4] -> fan on/off
     * infos[5] -> heat on/off
     * infos[6] -> end flag
     */
    String[] infos;

    temporary = p.readString();
    temporary = trim(temporary);
    // println(temporary);
    infos = split(temporary, ',');
    // println(infos);


    if (infos[0].equals("s") && infos[6].equals("e")) {
        for (int i = 0; i < 5; i++) {
            receivedData[i] = float(infos[i + 1]);
        }
    }
    // println(receivedData);

    powerON = true;
    for (int i = 0; i < 7; i++) {
        if (infos[i].equals("stop")) {
            powerON = false;
            break;
        }
    }
}


boolean overButton(float x, float y, int width, int height)  {
  if (mouseX >= x && mouseX <= x + width &&
      mouseY >= y && mouseY <= y + height) {
    return true;
  } else {
    return false;
  }
}

void update(int x, int y) {
    isOverTheButton = overButton(buttonX, buttonY, powerButtonON.width, powerButtonON.height);
}

void mousePressed() {
    if(isOverTheButton) {
        powerON = !powerON;
        port.write(byte(powerON));
    }
}
