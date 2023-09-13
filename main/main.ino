/*
Author : Ali Mochtar
Robot name : AlMo
Version : Beta-test1
Date created : 12/08/2023, 22:35 PM
Our Contacts:
  - GitHub : https://www.github.com/alimochtaar
  - Linkedin : https://www.linkedin.com/in/alimochtarahd/
  - Instagram : https://www.instagram.com/alimochtarr/
  - Email : alimochtarahdinasabilarrosyad@mail.ugm.ac.id
            alimochas123@gmail.com
*/
#include "U8glib.h"
#include <string.h>
U8GLIB_SSD1306_128X32 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);

#define fan_pinout 10
#define s0 12
#define s1 14
#define s2 15
#define s3 16
#define AI A6
#define BOTON 9
#define pwm_left  3   //PWM LEFT MOTOR
#define left1  5   //LEFT1 MOTOR
#define left2  4   //LEFT2 MOTOR
#define pwm_right  11  //PWM RIGHT MOTOR
#define right1  6   //RIGHT1 MOTOR
#define right2  7   //RIGHT2 MOTOR

int sensor[16];
bool digital[16];
int readBG[16];
int readLine[16];
int limits[16];
//int limits=750; //-------------------------------------- PAKAI INI KALAU INGIN INPUT MANUAL ANALOG VALUE UTK TCRT5000
int approximate=20;
byte bin_Sensor = 0b00000000;

long int sumap, sum, pos, poslast, position;

//TCRT5000 CONFIG: BLACK=0 WHITE=1
int line=0;

int pattern=1;

boolean onoff = 0;
int val, cnt = 0, v[3];

//-------------------------------------------- PID Variable
//float KP=0.18;//konstanta proportional
//float KD=4;//konstanta derivativa
//float KI=0.002;//konstanta integral
float Kp=0;//konstanta proportional
float Kd=0;//konstanta derivativa
float Ki=0;//konstanta integral
uint8_t multiP = 1;
uint8_t multiI = 1;
uint8_t multiD = 1;
int vel=150;//KECEPATAN MOTOR MAKS 255

int vel_maju=200;//KECEPATAN REM + MAJU
int vel_mundur=200;//KECEPATAN REM + MUNDUR

//-------------------------------------------- data integral
int error1=0;
int error2=0;
int error3=0;
int error4=0;
int error5=0;
int error6=0;
/////////////////////////

///////////variable PID///////////////
int proportional=0;
int integral=0;
int derivative=0;
int differential=0;
int last_prop;
int setpoint=750;

void setup() {
  Serial.begin(9600); //----------------------------------------- Serial utk ke bluetooth

  //------------------------------------------------------------- Set frekuensi PWM
  // for GA-120 no-load rpm 2000 N20 Motors
  
  //TCCR2B = TCCR2B & B11111000 | B00000001;
  //set timer 2 divisor to     1 for PWM frequency of 31372.55 Hz

  //TCCR2B = TCCR2B & B11111000 | B00000010; 
  //set timer 2 divisor to     8 for PWM frequency of  3921.16 Hz

  //TCCR2B = TCCR2B & B11111000 | B00000011;   
  //set timer 2 divisor to    32 for PWM frequency of   980.39 Hz

  TCCR2B = TCCR2B & B11111000 | B00000100;   
  //set timer 2 divisor to    64 for PWM frequency of   490.20 Hz (The DEFAULT)

  //TCCR2B = TCCR2B & B11111000 | B00000101;   
  //set timer 2 divisor to   128 for PWM frequency of   245.10 Hz

  //TCCR2B = TCCR2B & B11111000 | B00000110;   
  //set timer 2 divisor to   256 for PWM frequency of   122.55 Hz

  //TCCR2B = TCCR2B & B11111000 | B00000111;   
  //set timer 2 divisor to  1024 for PWM frequency of    30.64 Hz
  
  pinMode(fan_pinout, OUTPUT);
  pinMode(left1,OUTPUT);
  pinMode(left2,OUTPUT);
  pinMode(right1,OUTPUT);
  pinMode(right2,OUTPUT);

  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BOTON, INPUT);
  
  delay(500); 
  u8g.setFont(u8g_font_courB08);

  //------------------------------------Initial display on OLED
  u8g.firstPage();  
  do {
    //u8g.drawFrame(0, 0, 128, 64);  
    u8g.setPrintPos(5, 15); 
    u8g.print("Hello!!!!!");
    u8g.setPrintPos(5, 25); 
    u8g.print("Lets Get Started");
  } while( u8g.nextPage() );
  
  delay(1000);
  u8g.setFont(u8g_font_4x6);
  //------------------------------------MENU Display on OLED Display
    u8g.firstPage();
    do {
      u8g.setPrintPos(5, 10); 
      u8g.print("P1 - Calibrate BG");
      u8g.setPrintPos(5, 20); 
      u8g.print("P2 - Calibrate Line");
      u8g.setPrintPos(5, 30); 
      u8g.print("P3 - Start");
    } while( u8g.nextPage() ); 
  //----------------------------------------
  
  while(digitalRead(BOTON));  calibrate_bg();
  
  printText1("CALIBRATE SUCCESS", 0, 10);
  delay(100);
      
  while(digitalRead(BOTON));  calibrate_line();
                              average();
  
  printText1("CALIBRATE SUCCESS", 0, 10);
  delay(100);

  while(digitalRead(BOTON))
  delay(100);
  
  u8g.setFont(u8g_font_courB08);
  printText1("READY TO GO", 15, 15);
  delay(2000);
  printText1("CONTROL USING HC-05", 10, 15);
  delay(200);
}

void loop()
{
  readhc05();
  if(onoff==1){
      FAN(200);
      brake();
      baca();
      PID();
  }
  if(onoff==0){
      motor_start(0,0);
      delay(250);
      FAN(0);
  }
}
