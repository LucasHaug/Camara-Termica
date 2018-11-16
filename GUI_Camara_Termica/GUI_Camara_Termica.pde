import processing.serial.*;

PImage logoCamara;
PImage thermometer;
PImage humidity;
PImage fanWithColor, fanWithoutColor;
PImage fireWithColor, fireWithoutColor;
PImage lightWithColor, lightWithoutColor;
PImage powerButtonON, powerButtonOFF;

// Screen tela;
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

int rectHight, rectWidth;
float rect1X, rect1Y;
float rect2X, rect2Y;
float rect3X, rect3Y;

boolean isOverTheButton;

boolean fanON;
boolean lightsON;
boolean heatingON;
boolean powerON;

PFont myTextFont;
String inside;
String outside;
int textSize;

void setup() {
    // fullScreen();
    size(1200, 800);

    // tela = new Screen();

    // println(Serial.list()[0]);
    //port = new Serial(this, Serial.list()[0], 115200);
    //port.clear();

    firstColumn =  width * 0.15;
    secondColumn = width * 0.5;
    thirdColumn = width * 0.8;

    rectHight = 50;
    rectWidth = 200;

    rect1X = firstColumn - rectWidth/2; 
    rect1Y = height * 0.3 - rectHight/2;
    rect2X = firstColumn - rectWidth/2; 
    rect2Y = height * 0.4 - rectHight/2 + height * 0.1;
    rect3X = firstColumn - rectWidth/2;; 
    rect3Y = height * 0.5 - rectHight/2 + height * 0.1 * 2;

    logoCamara = loadImage("./Images/Camara-Termica-Logo.png");

    thermometer = loadImage("./Images/thermometer.png");
    thermometer.resize(0, int(rectHight));

    humidity = loadImage("./Images/humidity.png");
    humidity.resize(0, int(rectHight));

    fanWithColor = loadImage("./Images/fan_with_color.png");
    fanWithColor.resize(0, int(rectHight)); 
    fanWithoutColor = loadImage("./Images/fan_without_color.png");
    fanWithoutColor.resize(0, int(rectHight));

    fireWithColor = loadImage("./Images/fire_with_color.png");
    fireWithColor.resize(0, int(rectHight));
    fireWithoutColor = loadImage("./Images/fire_without_color.png");
    fireWithoutColor.resize(0, int(rectHight));

    lightWithColor = loadImage("./Images/light_with_color.png");
    lightWithColor.resize(0, int(rectHight));
    lightWithoutColor = loadImage("./Images/light_without_color.png");
    lightWithoutColor.resize(0, int(rectHight));

    powerButtonON = loadImage("./Images/power_button_ON.png");
    powerButtonON.resize(0, int(rectHight * 2));
    powerButtonOFF = loadImage("./Images/power_button_OFF.png");
    powerButtonOFF.resize(0, int(rectHight * 2));

    isOverTheButton = false;

    fanON = false;
    lightsON = false;
    heatingON = false;
    powerON = false;

    // String[] fontList = PFont.list();
    // printArray(fontList);
    textSize = 40;
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
        
    // rectColor = color(0);
    // rectHighlight = color(51);

    // baseColor = color(102);
    // currentColor = baseColor;

    // rectX = width/2-rectSize-10;
    // rectY = height/2-rectSize/2;
    // ellipseMode(CENTER);p


    //port.bufferUntil('\n');
}

//(87, 20, 168)

void draw() { 
    background(158, 164, 201);

    image(logoCamara, width*0.5 - logoCamara.width/2, height*0.12 - logoCamara.height/2);

    stroke(255);
    fill(210);
    rect(rect1X, rect1Y, rectWidth, rectHight);
    fill(0);
    text("Inside", rect1X + rectWidth/2 - textWidth(inside)/2, rect1Y + rectHight + textSize);
    image(thermometer, rect1X - thermometer.width - 4, rect1Y);

    noStroke();
    fill(255, 0, 0);
    rect(rect2X, rect2Y, rectWidth, rectHight);
    image(thermometer, rect2X - thermometer.width - 4, rect2Y);

    noStroke();
    fill(255, 0, 0);
    rect(rect3X, rect3Y, rectWidth, rectHight);
    image(humidity, rect3X - thermometer.width - 7, rect3Y);

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
        image(powerButtonON, thirdColumn - powerButtonON.width/2, rect2Y);
    } else {
        image(powerButtonOFF, thirdColumn - powerButtonOFF.width/2, rect2Y);
    }

    update(mouseX, mouseY);
    
    


    // tela.update();

   
    // delay(1);
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


// class Screen {
//     Info intTemp;
//     Info extTemp;
//     Info lamp;
//     Info fan;
//     Info heating;

//     Screen() {
//         intTemp = new Info (new Float[]{height*0.10, width*0.20, width*0.05, height*0.55});
//         extTemp = new Info (new Float[]{height*0.10, width*0.20, width*0.05, height*0.55});
//         lamp = new Info (new Float[]{height*0.10, width*0.20, width*0.05, height*0.55});
//         fan = new Info (new Float[]{height*0.10, width*0.20, width*0.05, height*0.55});
//         heating = new Info (new Float[]{height*0.10, width*0.20, width*0.05, height*0.55});
//     }

//     void update() {
//         intTemp.update();
//         extTemp.update();
//         lamp.update();
//         fan.update();
//         heating.update();
//     }
// }

// class Info {
//     float esquerda;
//     float direita;
//     float topo;
//     float base;
//     float tambase;
//     float tamlat;

//     Info(Float[] meas) {
//         tamlat   = meas[0];
//         tambase  = meas[1];
//         esquerda = meas[2];
//         direita  = esquerda + tambase;
//         topo     = meas[3];
//         base     = topo + tamlat;
//     }

//     void update() {
//         noStroke();
//         fill(160);
//         rect(esquerda, topo, tambase, tamlat);

//         stroke(255);
//         noFill();
//         line(esquerda + 30, topo, esquerda + 30, base);

//         fill(255);

//         textSize(60);
//         textAlign(CENTER, TOP);
//         text("PSImetro", width*0.15, height*0.04);
//         textSize(15);

//         pushMatrix();
//             textAlign(CENTER, CENTER);
//             textSize(20);
//             translate(esquerda + 15, (base+topo)/2);
//             rotate(radians(-90));
//             text("intTemp", 0, 0);
//         popMatrix();

//         textSize(18);
//         textAlign(LEFT, CENTER);

//         text("Modo " + text, (esquerda + direita)/2, base + 20);
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
    isOverTheButton = overButton(thirdColumn - powerButtonON.width/2, rect2Y, powerButtonON.width, powerButtonON.height); 
}

void mousePressed() {
    if(isOverTheButton) {
        powerON = !powerON;
    }
}
