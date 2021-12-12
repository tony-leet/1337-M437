// https://learn.adafruit.com/adafruit-gfx-graphics-library/overview
// https://www.arduino.cc/en/Serial/Print

#include <Adafruit_GFX.h>    // Core graphics library
#include <MCUFRIEND_kbv.h>   // Hardware-specific library
MCUFRIEND_kbv tft;

#define BLACK   0x0000
#define RED     0xF800
#define GREEN   0x07E0
#define WHITE   0xFFFF
#define GREY    0x8410

void setup() {
  // put your setup code here, to run once:
  

    uint16_t ID = tft.readID();
    if (ID == 0xD3D3) ID = 0x9481; //force ID if write-only display
    tft.begin(ID);
    tft.setRotation(1); // 0 vertical, 1 horizontal

    tft.fillScreen(BLACK);
    showMenu();
    
}

void loop() {
  
    // tft.fillScreen(BLACK);
    // tft.drawLine(0,0,100,100,GREEN);
    //showmsgXY(20, 10, 1, NULL, "System x1");
}

void showMenu()
{
  tft.setCursor(14,0);
  tft.setTextColor(GREEN);
  tft.setTextSize(4);
  //tft.setTextWrap(true);
  tft.print("---- 1337 M347 ----");
  tft.setTextSize(2);
  
  tft.drawRect(14,75,15,15,GREEN); // (x0,y0,width,height,color)
  tft.setCursor(50,75);
  tft.println("Start monitoring Sensors");
  
  tft.drawRect(14,100,15,15, GREEN);
  tft.setCursor(50,100);
  tft.println("Check Logs");
  

}

void showmsgXY(int x, int y, int sz, const GFXfont *f, const char *msg)
{
  int16_t x1, y1;   // 16 bit integer
  uint16_t wid, ht; // datatype that's unsigned and is 16 bits wide.  So, the maximum value is 2^16, or 65535.
  tft.drawFastHLine(0, y, tft.width(), GREEN);
  tft.setFont(f);
  tft.setCursor(x, y);
  tft.setTextColor(GREY);
  tft.setTextSize(sz);
  tft.print(msg);
  delay(1000);

}
