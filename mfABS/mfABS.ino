

#include <TFT_eSPI.h>
#include "NotoSansBold15.h"
#include "NotoSansBold36.h"
#include "Final_Frontier_28.h"
#include <CST816S.h>
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite sprite = TFT_eSprite(&tft);

#define small NotoSansBold15
#define final Final_Frontier_28
#define big NotoSansBold36 

#define TOUCH_INT 40
#define TOUCH_SDA 38
#define TOUCH_SCL 39
#define TOUCH_RST 16

//......................................colors
#define backColor 0x0026
#define gaugeColor 0x055D
#define dataColor 0x0311
#define purple 0xEA16
#define needleColor 0xF811

//............................dont edit this
int cx=120;
int cy=120;
int r=120;
int ir=116;
int n=0;
int angle=0;

float x[360]; //outer points of Speed gaouges
float y[360];
float px[360]; //ineer point of Speed gaouges
float py[360];
float lx[360]; //text of Speed gaouges
float ly[360];
float nx[360]; //needle low of Speed gaouges
float ny[360];

float x2[360]; //outer points of Speed gaouges
float y2[360];
float px2[360]; //ineer point of Speed gaouges
float py2[360];


double rad=0.01745;
unsigned short color1;
unsigned short color2;
float sA;
float rA;
int blinkPeriod=500;
unsigned long currentTimeL=0;
unsigned long currentTimeR=0;
int brightnesses[5]={40,80,120,150,240};
int selectedBrightness=3;
int deb1=0;
int deb2=0;
int debB=0;



//........................................................colors
unsigned short blockColor[4]={0x0312,0x0290,0x01EC,0x016A};
unsigned short dirColor[2]={0x0312,TFT_ORANGE};
unsigned short lightColor[3]={0x01EC,0x0FA8,0xB79F};

// .........important variables
bool leftPointer=0; 
bool rightPointer=0;
float speedAngle=0; //...speed variable 0-240
int segments=0; 


const int pwmFreq = 5000;
const int pwmResolution = 8;
const int pwmLedChannelTFT = 0;


CST816S touch(TOUCH_SDA, TOUCH_SCL, TOUCH_RST, TOUCH_INT); // sda, scl, rst, irq

void setup() {



  tft.init();

    
    tft.fillScreen(backColor);
    sprite.createSprite(240,240);
    sprite.setSwapBytes(true);
    sprite.setTextDatum(4);
    sprite.setTextColor(TFT_WHITE,backColor);
    sprite.setTextDatum(4);

  ledcSetup(pwmLedChannelTFT, pwmFreq, pwmResolution);
  ledcAttachPin(45, pwmLedChannelTFT);
  ledcWrite(pwmLedChannelTFT, 30); //brightnes of screen

  touch.begin();


  int a=120;
  for(int i=0;i<360;i++)
    {
       x[i]=((r-10)*cos(rad*a))+cx;
       y[i]=((r-10)*sin(rad*a))+cy;
       px[i]=((r-14)*cos(rad*a))+cx;
       py[i]=((r-14)*sin(rad*a))+cy;
       lx[i]=((r-24)*cos(rad*a))+cx;
       ly[i]=((r-24)*sin(rad*a))+cy;
       nx[i]=((r-36)*cos(rad*a))+cx;
       ny[i]=((r-36)*sin(rad*a))+cy;

        x2[i]=((r-50)*cos(rad*a))+cx;
       y2[i]=((r-50)*sin(rad*a))+cy;
       px2[i]=((r-62)*cos(rad*a))+cx;
       py2[i]=((r-62)*sin(rad*a))+cy;
    

       a++;
       if(a==360)
       a=0;
    }
     
}

int x1=0;

void draw()
{
  sprite.fillSprite(backColor);
  sprite.fillSmoothCircle(cx, cy, r+2, backColor);
  sprite.loadFont(small);
   
 
  sprite.drawSmoothArc(cx, cy, r, ir, 30, 330, gaugeColor, backColor);
  sprite.drawSmoothArc(cx, cy, r-5, r-6, 30, 330, TFT_WHITE, backColor);
  sprite.drawSmoothArc(cx, cy, r-9, r-8, 270, 330, purple, backColor);
  sprite.drawSmoothArc(cx, cy, r-40, ir-39, 30, 330, gaugeColor, backColor);

  sprite.drawSmoothArc(cx, cy, r-50, r-49, 30, 330, 0xCE59, backColor);
  sprite.drawSmoothArc(cx, cy, r-62, r-61, 30, 330, 0xCE59, backColor);

  sprite.drawRect(110,170,20,14,TFT_RED);
  sprite.fillRect(113,167,4,3,TFT_RED);
  sprite.fillRect(124,167,4,3,TFT_RED);
  sprite.drawLine(114,174,118,174,TFT_RED);
  sprite.drawLine(122,174,126,174,TFT_RED);
  sprite.drawLine(124,176,124,172,TFT_RED);

   sprite.fillTriangle(90,95,100,86,100,104,dirColor[leftPointer]);   //dirction pointers
   sprite.fillRect(100,90,10,10,dirColor[leftPointer]);
   sprite.fillTriangle(140,86,140,104,150,95,dirColor[rightPointer]);
   sprite.fillRect(130,90,10,10,dirColor[rightPointer]);
   

  
  
  //.....................................................draw GAUGES
     for(int i=0;i<26;i++){
     if(i<20) {color1=gaugeColor; color2=TFT_WHITE;} else {color1=purple; color2=purple;}

      for(int i=0;i<segments;i++)
      sprite.drawSmoothArc(cx, cy, r-58, r-54, 35+(i*25), 35+(i*25)+15, 0x4FFF, backColor);

     for(int i=0;i<13;i++)
     sprite.drawWedgeLine(x2[i*25],y2[i*25],px2[i*25],py2[i*25],1,1,0xCE59);

  if(i%2==0) {
  sprite.drawWedgeLine(x[i*12],y[i*12],px[i*12],py[i*12],3,1,color1);
  
  sprite.setTextColor(color2,backColor);
  sprite.drawString(String(i*10),lx[i*12],ly[i*12]);
  }else
  {sprite.drawWedgeLine(x[i*12],y[i*12],px[i*12],py[i*12],1,1,0xCE59);
  
  }
  }

  // ........................................needles draw
   sA=speedAngle*1.2;
  

    sprite.drawWedgeLine(px[(int)sA],py[(int)sA],nx[(int)sA],ny[(int)sA],3,3,needleColor);
  


  //.....................................drawing  TEXT
  sprite.setTextColor(TFT_WHITE,backColor);
  sprite.drawString("KM/H",cx,cy+34);
  sprite.unloadFont();
  sprite.loadFont(big);
  sprite.drawString(String((int)speedAngle),cx,cy+12);
  sprite.unloadFont();
  sprite.setTextColor(TFT_RED,backColor);
  sprite.drawString("12."+String(random(10,97)),120,194);
  
  
 
  
  sprite.setTextColor(TFT_WHITE,blockColor[3]);
   sprite.drawString("32452.23",120,212,2);

  sprite.setTextColor(TFT_ORANGE,backColor);

   sprite.drawString("BRIGHTNESS:"+String(x1),120,226);
  

 
  
   //..............................................push Sprite to screen  
   sprite.pushSprite(0,0);
  
}

int blinking=1;
long curentTime=0;
int period=400;

long curentTime2=0;
int period2=500;


void loop() {

    if (touch.available())
    {
        x1=touch.data.x;
        ledcWrite(pwmLedChannelTFT, x1);
    }

 if(millis()>curentTime+period) 
 {curentTime=millis();
  leftPointer=!leftPointer;}

   if(millis()>curentTime2+period2) 
 {curentTime2=millis();
  segments++;
  if(segments==13)
  segments=0;
  }

 speedAngle=speedAngle+2;
 if(speedAngle>220) speedAngle=0;
  draw();
  

}

