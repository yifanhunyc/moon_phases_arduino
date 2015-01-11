
//Encoders
#include <Encoder.h>

//LEDs
#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

//Servo
#include <Servo.h>

//Encoders (yellow, white) 
Encoder myEncMonth(3, 5);
Encoder myEncDate(18, 6);
Encoder myEncYear(19, 4);
Encoder myEncMotor(2, 7);

long oldPositionY  = -999;
long oldPositionM  = -999;
long oldPositionD  = -999;

//LED:
Adafruit_8x16matrix matrix1 = Adafruit_8x16matrix(); //71
Adafruit_8x8matrix matrix2 = Adafruit_8x8matrix(); //70
Adafruit_8x8matrix matrix3 = Adafruit_8x8matrix();  //72
Adafruit_8x8matrix matrix4 = Adafruit_8x8matrix();  //73
Adafruit_8x8matrix matrix5 = Adafruit_8x8matrix();  //74
Adafruit_8x8matrix matrix6 = Adafruit_8x8matrix();  //75
Adafruit_8x8matrix matrix7 = Adafruit_8x8matrix();  //76

String inputString;

String _month;
String _date;
String _year;

int LEDBrightness = 20;

//Servo
Servo myservo;

int des = 0;
int currentPos = 0;
int motorSpeed = 9;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(10);
  Serial.println("0,0,0,0");

  matrix1.begin(0x71);  // pass in the address
  matrix2.begin(0x70);  // pass in the address
  matrix3.begin(0x72);  // pass in the address
  matrix4.begin(0x74);  // pass in the address
  matrix5.begin(0x73);  // pass in the address
  matrix6.begin(0x75);  // pass in the address
  matrix7.begin(0x76);  // pass in the address

  inputString = "00.00.0000"; //today's date
  
  myservo.attach(9);

}

static const uint8_t PROGMEM
smile_bmp[] =
{ B00111100,
  B01000010,
  B10100101,
  B10000001,
  B10100101,
  B10011001,
  B01000010,
  B00111100
},
neutral_bmp[] =
{ B00111100,
  B01000010,
  B10100101,
  B10000001,
  B10111101,
  B10000001,
  B01000010,
  B00111100
},
frown_bmp[] =
{ B00111100,
  B01000010,
  B10100101,
  B10000001,
  B10011001,
  B10100101,
  B01000010,
  B00111100
};

void loop() {

  //LED Matrix
  matrix1.setBrightness(LEDBrightness);
  matrix1.setRotation(1);
  matrix1.setTextSize(1);
  matrix1.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
  matrix1.setTextColor(LED_ON);
  matrix1.clear();
  matrix1.setCursor(2, 0);
  matrix1.print(inputString);
  matrix1.writeDisplay();

  matrix2.setBrightness(LEDBrightness);
  matrix2.setRotation(1);
  matrix2.setTextSize(1);
  matrix2.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
  matrix2.setTextColor(LED_ON);
  matrix2.clear();
  matrix2.setCursor(-14, 0);
  matrix2.print(inputString);
  matrix2.writeDisplay();

  matrix3.setBrightness(LEDBrightness);
  matrix3.setRotation(1);
  matrix3.setTextSize(1);
  matrix3.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
  matrix3.setTextColor(LED_ON);
  matrix3.clear();
  matrix3.setCursor(-22, 0);
  matrix3.print(inputString);
  matrix3.writeDisplay();

  matrix4.setBrightness(LEDBrightness);
  matrix4.setRotation(1);
  matrix4.setTextSize(1);
  matrix4.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
  matrix4.setTextColor(LED_ON);
  matrix4.clear();
  matrix4.setCursor(-30, 0);
  matrix4.print(inputString);
  matrix4.writeDisplay();


  matrix5.setBrightness(4);
  matrix5.setRotation(1);
  matrix5.setTextSize(1);
  matrix5.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
  matrix5.setTextColor(LED_ON);
  matrix5.clear();
  matrix5.setCursor(-38, 0);
  matrix5.print(inputString);
  matrix5.writeDisplay();

  matrix6.setBrightness(LEDBrightness);
  matrix6.setRotation(1);
  matrix6.setTextSize(1);
  matrix6.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
  matrix6.setTextColor(LED_ON);
  matrix6.clear();
  matrix6.setCursor(-46, 0);
  matrix6.print(inputString);
  matrix6.writeDisplay();

  matrix7.setBrightness(LEDBrightness);
  matrix7.setRotation(1);
  matrix7.setTextSize(1);
  matrix7.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
  matrix7.setTextColor(LED_ON);
  matrix7.clear();
  matrix7.setCursor(-54, 0);
  matrix7.print(inputString);
  matrix7.writeDisplay();

  //Encoders
  long newPositionM = myEncMonth.read() / 4;
  long newPositionD = myEncDate.read() / 4;
  long newPositionY = myEncYear.read() / 4;
  
  //Servo
  long currentPos = (myEncMotor.read() - 10) / 5 + 2;
 
  //Make the servo still when it starts
  
  if(currentPos == des){
    myservo.write(92);
  }else if(currentPos < des){
   myservo.write(92 + motorSpeed); 
  }else if(currentPos > des){
   myservo.write(92 - motorSpeed); 
  }
  
  //Serial Communication:
  if (Serial.available()) {
    long month = Serial.parseInt();
    long date = Serial.parseInt();
    long year = Serial.parseInt();
    long light_pos = Serial.parseInt();

    if(year >= 0 && year < 10){
      _year = "000" + String(year,DEC);
    }
    else if(year >= 10 && year < 100){
      _year = "00" + String(year,DEC); 
    }
    else if(year >= 100 && year < 1000){
      _year = "0" + String(year,DEC); 
    }
    else{
      _year = "" + String(year,DEC); 
    }

    if(month >= 0 && month < 10){
      _month = "0" + String(month,DEC); 
    }
    else{
      _month = "" + String(month,DEC); 
    }

    if(date >= 0 && date < 10){
      _date = "0" + String(date,DEC); 
    }
    else{
      _date = "" + String(date,DEC); 
    }

    inputString = _month + "." + _date + "." + _year;
    
    des = light_pos;

    Serial.print(newPositionY);
    Serial.print(",");
    Serial.print(newPositionM);
    Serial.print(",");
    Serial.print(newPositionD);
    Serial.print(",");
    Serial.println(currentPos);
  } 
}
