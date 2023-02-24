#include <Adafruit_NeoPixel.h>

#define LEDPIN PA5//ADDRESSABLE LED
#define LEDCOUNT 3
Adafruit_NeoPixel strip(LEDCOUNT, LEDPIN, NEO_RGB + NEO_KHZ800);


//charge motor
#define stat1 PA6 //add internal pullup
#define stat2 PA7 //add internal pullup
#define bat_lvl PA8 //BAT LEVEL ANALOG READ PIN

/*
Charge Cycle                 State STAT1 STAT2 PG   related color(of the neon light)
Shutdown     |                      Hi-Z Hi-Z   Hi-Z          no color/black
Standby      |                      Hi-Z Hi-Z   L             purple
Charge in Progress |                  L  Hi-Z   L             blue
Charge Complete (EOC) |             Hi-Z  L     L             white
Temperature Fault     |             Hi-Z Hi-Z   L             yellow
Timer Fault           |             Hi-Z Hi-Z   L             dark blue
System Test Mode                     L    L     L

*/


void initBatPins()
{
  //BAT USED LED
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(50); // Set BRIGHTNESS to about 1/5 (max = 255)
  
  pinMode(stat1, INPUT_PULLUP);  
  pinMode(stat2, INPUT_PULLUP); 
  pinMode (bat_lvl, INPUT);
}

void batMonitor()
{
   int bat_stat1 = digitalRead(stat1); 
   int bat_stat2 = digitalRead(stat2);

    int battery_level = digitalRead(bat_lvl);
    if(bat_stat1 == 1 && bat_stat2 == 0)
    {//battery is charging
      //color blue on neopixel
      strip.setPixelColor(1, strip.Color(0,   0,   255));
      strip.show();
    }
    else if(bat_stat1 == 1 && bat_stat2 == 0)
    {//battery is charge complete
      //color white on neopixel
      strip.setPixelColor(1, strip.Color(255,   255,   255));
      strip.show();
    }
    else if(bat_stat1 == 1 && bat_stat2 == 0)
    {//Temperature Fault   
      //color yellow on neopixel
      strip.setPixelColor(1, strip.Color(255, 255, 0));
      strip.show();
    }

    else{
      //read battery level and display the desired color
      long timer = millis();
          if(battery_level == 0)
          {
            while(millis()-timer < 2000)//for 2 seconds 
            {
            //battery low (device blinks red for 2 seconds and does not work)
             strip.setPixelColor(1, strip.Color(255, 0, 0));
             strip.show();
             delay(200);

             strip.setPixelColor(1, strip.Color(255, 0, 0));
             strip.show();
             delay(500);
            }
          }
          else{
            //blink green... battery is all good
             strip.setPixelColor(1, strip.Color(0, 255, 0));
             strip.show();
             delay(500);

             strip.setPixelColor(1, strip.Color(0, 255, 0));
             strip.show();
             delay(1500);
            }
      }
    
}
