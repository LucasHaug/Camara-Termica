import processing.serial.*;
 
// processing-java --sketch=/home/lhaug/Documents/Interface_Camara_Termica/ --run --force

PImage logoCamara;
PImage termometro;
PImage gota;
// Screen tela;
//Serial port;

// Float[] data;

int rectHight, rectWidth;
float rect1X, rect1Y;
float rect2X, rect2Y;
float rect3X, rect3Y;

void setup() {
    // fullScreen();
    size(1200, 800);

    // tela = new Screen();

    // println(Serial.list()[0]);
    //port = new Serial(this, Serial.list()[0], 115200);
    //port.clear();
    rectHight = 50;
    rectWidth = 200;

    rect1X = width * 0.15 - rectWidth/2; 
    rect1Y = height * 0.3 - rectHight/2;
    rect2X = width * 0.15 - rectWidth/2; 
    rect2Y = height * 0.4 - rectHight/2 + height * 0.1;
    rect3X = width * 0.15 - rectWidth/2;; 
    rect3Y = height * 0.5 - rectHight/2 + height * 0.1 * 2;

    logoCamara = loadImage("./Camara-Termica-Logo.png");
    termometro = loadImage("./termometro.png");
    termometro.resize(0, int(rectHight));
    gota = loadImage("./gota.png");
    gota.resize(0, int(rectHight));


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

void draw() {
    background(150);

    image(logoCamara, width*0.5 - logoCamara.width/2, height*0.12 - logoCamara.height/2);

    stroke(255);
    fill(210);
    rect(rect1X, rect1Y, rectWidth, rectHight);
    image(termometro, rect1X - termometro.width - 4, rect1Y);

    noStroke();
    fill(255, 0, 0);
    rect(rect2X, rect2Y, rectWidth, rectHight);
    image(termometro, rect2X - termometro.width - 4, rect2Y);

    noStroke();
    fill(255, 0, 0);
    rect(rect3X, rect3Y, rectWidth, rectHight);
    image(gota, rect3X - termometro.width - 4, rect3Y);

    // update(mouseX, mouseY);
    // tela.update();

    
    // if (rectOver) {
    //   fill(rectHighlight);
    // } else {
    //   fill(rectColor);
    // }
    // stroke(255);
    // rect(rectX, rectY, rectSize, rectSize);
    
    // if (circleOver) {
    //   fill(circleHighlight);
    // } else {
    //   fill(circleColor);
    // }
    // stroke(0);
    // ellipse(circleX, circleY, circleSize, circleSize);
    
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

// class Button {
//     int rectX, rectY;      // Position of square button
//     int rectSize = 90;     // Diameter of rect
//     color rectColor, baseColor;
//     color rectHighlight;
//     boolean rectOver = false;

//     Button() {

//     }
// }

// void mousePressed() {
//   if (rectOver) {
//     currentColor = rectColor;
//   }
// }

// boolean overRect(int x, int y, int width, int height)  {
//   if (mouseX >= x && mouseX <= x+width && 
//       mouseY >= y && mouseY <= y+height) {
//     return true;
//   } else {
//     return false;
//   }
// }

// void update(int x, int y) {
//   if ( overCircle(circleX, circleY, circleSize) ) {
//     circleOver = true;
//     rectOver = false;
//   } else if ( overRect(rectX, rectY, rectSize, rectSize) ) {
//     rectOver = true;
//     circleOver = false;
//   } else {
//     circleOver = rectOver = false;
//   }
// }
