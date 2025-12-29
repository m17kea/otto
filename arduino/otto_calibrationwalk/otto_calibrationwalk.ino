//----------------------------------------------------------------
//-- Otto DIY invests time and resources providing open source code and hardware, 
//-- please support by purchasing kits from https://www.ottodiy.com/
//-- Make sure to have installed all libraries: https://github.com/OttoDIY/OttoDIYLib
//-----------------------------------------------------------------
#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <EEPROM.h>
#include <Otto.h> //-- Otto Library
Otto ottoBot;  //This is Otto!

#define LeftLeg 2 
#define RightLeg 3
#define LeftFoot 4 
#define RightFoot 5 
#define Buzzer  12 

double angle_rad = PI/180.0;
double angle_deg = 180.0/PI;
int YL;
int YR;
int RL;
int RR;

void setup(){
      ottoBot.init(LeftLeg, RightLeg, LeftFoot, RightFoot, true, Buzzer); //Set the servo pins and Buzzer pin
    Serial.begin(9600);
    YL = EEPROM.read(0);
    if (YL > 128) YL -= 256;
    YR = EEPROM.read(1);
    if (YR > 128) YR -= 256;
    RL = EEPROM.read(2);
    if (RL > 128) RL -= 256;
    RR = EEPROM.read(3);
    if (RR > 128) RR -= 256;
    ottoBot.home();
    Serial.println("OTTO CALIBRATION PROGRAM");
    Serial.println("PRESS a or z for adjusting Left Leg");
    Serial.println("PRESS s or x for adjusting Left Foot");
    Serial.println("PRESS k or m for adjusting Right Leg");
    Serial.println("PRESS j or n for adjusting Right Foot");
    Serial.println();
    Serial.println("PRESS f to test Otto walking");
    Serial.println("PRESS h to return servos to home position"); 
}

void loop(){
    int charRead = 0;

    if((Serial.available()) > (0)){
        charRead = Serial.read();
    }
    if(((charRead)==('a' ))){
        YL++;
        ottoBot.setTrims(YL,YR,RL,RR);
        calib_homePos();
        ottoBot.saveTrimsOnEEPROM();
    }else{
        if(((charRead)==( 'z' ))){
            YL--;
            ottoBot.setTrims(YL,YR,RL,RR);
            calib_homePos();
            ottoBot.saveTrimsOnEEPROM();
        }else{
            if(((charRead)==( 's' ))){
                RL++;
                ottoBot.setTrims(YL,YR,RL,RR);
                calib_homePos();
                ottoBot.saveTrimsOnEEPROM();
            }else{
                if(((charRead)==( 'x' ))){
                    RL--;
                    ottoBot.setTrims(YL,YR,RL,RR);
                    calib_homePos();
                    ottoBot.saveTrimsOnEEPROM();
                }else{
                    if(((charRead)==( 'k' ))){
                        YR++;
                        ottoBot.setTrims(YL,YR,RL,RR);
                        calib_homePos();
                        ottoBot.saveTrimsOnEEPROM();
                    }else{
                        if(((charRead)==( 'm' ))){
                            YR--;
                            ottoBot.setTrims(YL,YR,RL,RR);
                            calib_homePos();
                            ottoBot.saveTrimsOnEEPROM();
                        }else{
                            if(((charRead)==( 'j' ))){
                                RR++;
                                ottoBot.setTrims(YL,YR,RL,RR);
                                calib_homePos();
                                ottoBot.saveTrimsOnEEPROM();
                            }else{
                                if(((charRead)==( 'n' ))){
                                    RR--;
                                    ottoBot.setTrims(YL,YR,RL,RR);
                                    calib_homePos();
                                    ottoBot.saveTrimsOnEEPROM();
                                }else{
                                    if(((charRead)==( 'f' ))){
                                        ottoBot.walk(1,1000,1);
                                    }else{
                                        if(((charRead)==( 'h' ))){
                                            ottoBot.home();
                                        }else{
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    } 
}

void calib_homePos() {
  int servoPos[4];
  servoPos[0]=90;
  servoPos[1]=90;
  servoPos[2]=90;
  servoPos[3]=90;
  ottoBot._moveServos(500, servoPos);
  ottoBot.detachServos();
}
