import processing.serial.*;

PImage logoCamara;
PImage thermometer;
PImage humidity;
PImage fanWithColor, fanWithoutColor;
PImage fireWithColor, fireWithoutColor;
PImage lightWithColor, lightWithoutColor;
PImage powerButtonON, powerButtonOFF;

//Serial port;

// Float[] data;
/**
 * data[0] -> temperatura interna
 * data[0] -> temperatura externa
 * data[0] -> humidade
 * data[0] -> valor da ação do algoritmo de pi
 * data[0] -> 
 */

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
boolean lightsON;
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
    // port = new Serial(this, "/dev/ttyACM0", 115200);
    // port.clear();

    firstColumn =  width * 0.25 - 7;
    secondColumn = width * 0.5;
    thirdColumn = width * 0.75 + 15;

    rectHeight = 100;
    rectWidth = 230;
    cornerRadius = 15;

    distance = rectHeight * 2;
    rect1X = firstColumn - rectWidth/2; 
    rect1Y = height * 0.32 - rectHeight/2 + 7;
    rect2X = firstColumn - rectWidth/2; 
    rect2Y = rect1Y + distance;
    rect3X = firstColumn - rectWidth/2;; 
    rect3Y = rect2Y + distance;

    logoCamara = loadImage("./Images/Camara-Termica-Logo.png");
    logoCamara.resize(0, int(logoCamara.height * 1.1));

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

    buttonX = thirdColumn - powerButtonON.width/2;
    buttonY = rect2Y - powerButtonON.height/2 + rectHeight/2;
    isOverTheButton = false;

    fanON = false;
    lightsON = false;
    heatingON = false;
    powerON = false;

    textSize = 40;
    // String[] fontList = PFont.list();
    // printArray(fontList);
    /**
     * Mudar para uma fonte disponivel no seu computador
     */
    myTextFont = createFont("Dyuthi", textSize);
    textFont(myTextFont);
    inside = "Inside";
    outside = "Outside";

    // dados = new Float[4];
    
    // for (int i = 0; i < 4; i++)
    //     data[i] = 0.0;  
        
    //port.bufferUntil('\n');
}

void draw() { 
    background(158, 164, 201);

    image(logoCamara, secondColumn - logoCamara.width/2, height*0.12 - logoCamara.height/2);

    intTemp = "33°C";
    extTemp = "22°C";
    humidityValue = "83%";
    fanON = true;

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

    if (fanON) {
        image(fanWithColor, secondColumn - fanWithColor.width/2, rect1Y);
    } else {
        image(fanWithoutColor, secondColumn - fanWithoutColor.width/2, rect1Y);
    }

    if (lightsON) {
        image(lightWithColor, secondColumn - lightWithColor.width/2, rect2Y);
    } else {
        image(lightWithoutColor, secondColumn - lightWithoutColor.width/2, rect2Y);
    }

    if (heatingON) {
        image(fireWithColor, secondColumn - fireWithColor.width/2, rect3Y);
    } else {
        image(fireWithoutColor, secondColumn - fireWithoutColor.width/2, rect3Y);
    }

    if (powerON) {
        image(powerButtonON, buttonX, buttonY);
    } else {
        image(powerButtonOFF, buttonX, buttonY);
    }

    update(mouseX, mouseY);
}

// void serialEvent(Serial p) {
//     int i;
//     String temporary;

//     temporary = p.readString();
//     temporary = trim(temporary);
//     //println(temporary);
//     String[] vals = split(temporary, ',');
//     //println(vals.length);
//     if (vals.length != 8)
//         return;
//     //println(vals);

//     if (vals[7].equals("d")) {
//         if (vals[4].equals("1")) {
//             i = int(vals[3]);
//             dados1[0][i] = float(vals[1]);
//             dados1[1][i] = float(vals[2]);
//         } else if (vals[4].equals("2")) {
//             i = int(vals[3]);
//             dados2[0][i] = float(vals[1]);
//             dados2[1][i] = float(vals[2]);
//         }
//     } else if (vals[7].equals("w")) {
//         i = int(vals[6]);
//         wave[i].set("Vrms", float(vals[1]));
//         wave[i].set("def", float(vals[2]));
//         wave[i].set("frequencia", float(vals[3]));
//         wave[i].set("periodo", float(vals[4]));
//         wave[i].set("amplitude", float(vals[5]));
//     }
// }


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
    }
}
