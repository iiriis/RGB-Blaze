#include <FastLED.h>
#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11);

#define n 51
CRGB leds[n];
//const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
char s[10];
char* sp = s;
String rgb="";

void setup() {
  mySerial.begin(9600);
  FastLED.addLeds<WS2812, 7, GRB>(leds, n); 
  FastLED.setBrightness(255);
  //  lcd.begin(16, 2);
    Serial.begin(2000000);
    //Serial.begin(9600);
    while(!Serial){}

}


 

bool f=true;


byte r=255,g=0,b=0,state=0;
byte cr=0,cg=0,cb=0;

void loop() {

colorpicker();
}

int i;

void colorpicker()
{
  
  if (Serial.available() > 0)
  {
    delayMicroseconds(20);
    while (Serial.available()!=0)
    {
       *sp = (char)Serial.read();
        sp++;
    }
    sp=s;
    cr=((s[0]-'0')*100)+((s[1]-'0')*10)+(s[2]-'0');
    cg=((s[3]-'0')*100)+((s[4]-'0')*10)+(s[5]-'0');
    cb=((s[6]-'0')*100)+((s[7]-'0')*10)+(s[8]-'0');  

      for (int i = 0; i < n; i++)
      leds[i] = CRGB(cr,cg,cb);

  
  Serial.print(cr);
  Serial.print("  ");
  Serial.print(cg);
  Serial.print("  ");
  Serial.println(cb);
  
  FastLED.show();
  }

 // lcd.setCursor(0, 0);
 // lcd.print(s);
  
    
     
      //FastLED.delay(50);
}


void colorpickerbt()
{
  rgb="";
  if (mySerial.available() > 0)
  {
    
    delay(7);
    while (mySerial.available()!=0)
    {
       rgb+=(char)mySerial.read();
    }
  
cr=rgb.substring(rgb.indexOf('R')+1, rgb.indexOf('g')).toInt();
cg=rgb.substring(rgb.indexOf('g')+1, rgb.indexOf('b')).toInt();
cb=rgb.substring(rgb.indexOf('b')+1).toInt();


for (int i = 0; i < n; i++)
      leds[i] = CRGB(cr,cg,cb);

      FastLED.show();

  
  }
}



void fadeshow()
{
   switch(state)
  {
    case 0: g++;
            state = g==255?1:0;
            break;
    
    case 1: r--;
            state = r==0?2:1;
            break;
            
    case 2: b++;
            state = b==255?3:2;
            break;

    case 3: g--;
            state = g==0?4:3;
            break;
            
    case 4: r++;
            state = r==255?5:4;
            break;

    case 5: b--;
            state = b==0?0:5;
            break;
  }
    
    
  
     for (int i = 0; i < n; i++)
      leds[i] = CRGB(r,g,b);

  
  
 FastLED.show();
 FastLED.delay(50);
}


int mapp(double x, double in_min, double in_max, int out_min, int out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

