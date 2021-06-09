//Libraries required for interfacing with the LED strips
//These are compatible with the Arduino IDE
//https://github.com/adafruit/Adafruit_NeoPixel
//https://github.com/FastLED/FastLED
#include <Adafruit_NeoPixel.h>
#include <FastLED.h>

//BEFORE YOU BEGIN, CHECK WHICH STRIP IS BIG USED AND COUNT HOW MANY LEDS ARE ON THE STRIP

/////////////////////////////////////////////////////////////////////////////////////
//Definitions

#define NUM_LEDS 80//40//80   //total number of LEDs
#define RIGHT_PIN 6        //which microcontroller pin is sending the signal
#define LEFT_PIN 4//7
#define LEFT_P 5
#define RIGHT_P 7

//define the strip for the Adafruit_NeoPixel library
Adafruit_NeoPixel right_strip = Adafruit_NeoPixel(NUM_LEDS, RIGHT_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel left_strip = Adafruit_NeoPixel(NUM_LEDS, LEFT_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel right_s = Adafruit_NeoPixel(NUM_LEDS, RIGHT_P, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel left_s = Adafruit_NeoPixel(NUM_LEDS, LEFT_P, NEO_GRB + NEO_KHZ800);

//create an array holding each led in the strip
CRGB leds[NUM_LEDS];  



/////////////////////////////////////////////////////////////////////////////////////
//The following functions are implementation functions that style functions use to execute the pattern

//This function will assign a colour to an led based on which library functions are calling it
void setPixel(int Pixel, byte red, byte green, byte blue)
{
#ifdef ADAFRUIT_NEOPIXEL_H
  // NeoPixel
  left_strip.setPixelColor(Pixel, left_strip.Color(red, green, blue));
  right_strip.setPixelColor(Pixel, right_strip.Color(red, green, blue));
  left_s.setPixelColor(Pixel, left_s.Color(red, green, blue));
  right_s.setPixelColor(Pixel, right_s.Color(red, green, blue));
#endif

#ifndef ADAFRUIT_NEOPIXEL_H
  // FastLED
  leds[Pixel].r = red;
  leds[Pixel].g = green;
  leds[Pixel].b = blue;
#endif
}

//This function will send the signal to the strip based on which libary functions are calling it
void showStrip()
{
#ifdef ADAFRUIT_NEOPIXEL_H
  //NeoPixel
  right_strip.show();
  left_strip.show();
  right_s.show();
  left_s.show();
#endif

#ifndef ADAFRUIT_NEOPIXEL_H
  //FastLED
  FastLED.show();
#endif
}

//This function sets all leds in the strip to the same colour
void setAll(byte red, byte green, byte blue){
  for (int point = 0; point < NUM_LEDS; point++){
    setPixel(point, red, green, blue);
  }
  showStrip();
}



/////////////////////////////////////////////////////////////////////////////////////

// sends a wave down and back the strip
void pattern(int red, int green, int blue, int SpeedDelay){

 for( int loopin = 0; loopin < 3; loopin++){
  for (int i = 0; i < NUM_LEDS; i+=4){
    setPixel(i, red, green, blue);
    setPixel(i+1, red, green, blue);

  }
  showStrip();

  delay(SpeedDelay);
  setAll(0,0,0);
  showStrip();
  for (int i = 3; i < NUM_LEDS; i+=4){
    setPixel(i, red, green, blue);
    setPixel(i+1, red, green, blue);

  }
  showStrip();

  delay(SpeedDelay);
  setAll(0,0,0);
  showStrip();
 }
}


void pattern3(int red, int green, int blue, int SpeedDelay){

   for( int loopin = 0; loopin < round(4*4154/SpeedDelay); loopin++){   

      setAll(red, green, blue);
      showStrip();

     delay(SpeedDelay);

      setAll(0, 0, 0);
      showStrip();

      delay(SpeedDelay);
   }
}




void setup() {
 
  //Neo pixel LED array initialization
  right_strip.begin();
  left_strip.begin();
//  right_s.begin();
  left_s.begin();
 
  //specify type of strip below. There are two robot sides with identical LEDs
  FastLED.addLeds<WS2812B, RIGHT_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<WS2812B, LEFT_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<WS2812B, RIGHT_P, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.addLeds<WS2812B, LEFT_P, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  
  Serial.begin(9600);
}


void loop(){

  delay(2000);

   //tired
   //32,0,0
  pattern3(31, 0, 0, 4154);
  setAll(0,0,0);
  delay(2000);

  //happy
  //0,255,0
  pattern3(0, 255, 0, 1609);
  setAll(0,0,0);
  delay(2000);

  //excited
  //0,174,0
  pattern3(0, 174, 0, 300);
  setAll(0,0,0);
  delay(2000);

  //annoyed
  //62,0,0
  pattern3(64, 0, 0, 1828);
  setAll(0,0,0);
  delay(2000);  
  
  //fear
  //57,0,0
  pattern3(54, 0, 0, 2958);
  setAll(0,0,0);
  delay(2000);

}  
