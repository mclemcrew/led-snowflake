// This is a demonstration on how to use an input device to trigger changes on your neo pixels.
// You should wire a momentary push button to connect from ground to a digital IO pin.  When you
// press the button it will change to a new pixel animation.  Note that you need to press the
// button once to start the first animation!

#include <Adafruit_NeoPixel.h>

#define BUTTON_PIN_1   3    // Digital IO pin connected to the button.  This will be
                          // driven with a pull-up resistor so the switch should
                          // pull the pin to ground momentarily.  On a high -> low
                          // transition the button press logic will execute.
#define BUTTON_PIN_2  5

#define PIXEL_PIN    12    // Digital IO pin connected to the NeoPixels.

#define PIXEL_COUNT 24

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

bool oldState1 = HIGH;
bool oldState2 = HIGH;
bool newState1 = HIGH;
bool newState2 = HIGH;
int colorIndicator = 0;
int showIndicator = 0;

void setup() {
  pinMode(BUTTON_PIN_1, INPUT_PULLUP);
  pinMode(BUTTON_PIN_2, INPUT_PULLUP);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  colorType(0);
  showType(0);
}

void loop() {
  // Get current button state.
  newState1 = digitalRead(BUTTON_PIN_1);
  newState2 = digitalRead(BUTTON_PIN_2);

  // Check if state changed from high to low (button press).
  if (newState1 == LOW && oldState1 == HIGH) {
    // Short delay to debounce button.
    delay(15);
    // Check if button is still low after debounce.
    newState1 = digitalRead(BUTTON_PIN_1);
    if (newState1 == LOW) {
      colorIndicator++;
      if (colorIndicator > 3)
        colorIndicator=0;
      oldState1 = newState1;
      colorType(colorIndicator);
    }
  }

  if (newState2 == LOW && oldState2 == HIGH) {
    // Short delay to debounce button.
    delay(15);
    // Check if button is still low after debounce.
    newState2 = digitalRead(BUTTON_PIN_2);
    if (newState2 == LOW) {
      showIndicator++;
      if (showIndicator > 3)
        showIndicator=0;
      oldState2 = newState2;
      showType(showIndicator);
    }
  }

  // Set the last button state to the old state.
  oldState1 = newState1;
  oldState2 = newState2;
}

void colorType(int i) {
  switch(i){
    case 0: 
      if(showIndicator==0) {
        solid(0, 50); 
      }  
      if(showIndicator==1) {
        theaterChase(0, 120);
      }
      break;
    case 1:
      if(showIndicator==0) {
        solid(1, 50); 
      }  
      if(showIndicator==1) {
        theaterChase(1, 120);
      }
      break;
    case 2: 
      if(showIndicator==0) {
        solid(2, 50); 
      }  
      if(showIndicator==1) {
        theaterChase(2, 120);
      }
      break;
    case 3: 
      if(showIndicator==0) {
        solid(3, 50); 
      }  
      if(showIndicator==1) {
        theaterChase(3, 120);
      }
      break;
  }
}

void showType(int i) {
  switch(i){
    case 0: 
      if(colorIndicator==0) {
        solid(0, 50); 
      }  
      if(colorIndicator==1) {
        solid(1, 50);
      }
      if(colorIndicator==2) {
        solid(2, 50); 
      }  
      if(colorIndicator==3) {
        solid(3, 50);
      }
      break;
    case 1: 
      if(colorIndicator==0) {
        theaterChase(0, 120); 
      }  
      if(colorIndicator==1) {
        theaterChase(1, 120);
      }
      if(colorIndicator==2) {
        theaterChase(2, 120); 
      }  
      if(colorIndicator==3) {
        theaterChase(3, 120);
      }
      break;
    case 2: rainbowCycle(30);
            break;
    case 3: rainbow(30);
            break;
  }
}

// Fill the dots one after the other with a color
void solid(uint8_t color, uint8_t wait) {
  if(color==0) {
    for(uint16_t i=0; i<strip.numPixels(); i=i+2) {
      strip.setPixelColor(i, strip.Color(0, 35, 180));
      delay(wait);
      strip.show();
    }
    for(uint16_t i=1; i<strip.numPixels(); i=i+2) {
      strip.setPixelColor(i, strip.Color(127, 127, 127));
      delay(wait);
      strip.show();
    }
  }
  if(color==1) {
    for(uint16_t i=0; i<strip.numPixels(); i=i+2) {
      strip.setPixelColor(i, strip.Color(127, 0, 0));
      delay(wait);
      strip.show();
    }
    for(uint16_t i=1; i<strip.numPixels(); i=i+2) {
      strip.setPixelColor(i, strip.Color(0, 127, 0));
      delay(wait);
      strip.show();
    }
  }
  if(color==2) {
    for(uint16_t i=0; i<strip.numPixels(); i=i+2) {
      strip.setPixelColor(i, strip.Color(160,120,16));
      delay(wait);
      strip.show();
    }
    for(uint16_t i=1; i<strip.numPixels(); i=i+2) {
      strip.setPixelColor(i, strip.Color(100,100,100));
      delay(wait);
      strip.show();
    }
  }
  if(color==3) {
    for(uint16_t i=0; i<strip.numPixels(); i=i+2) {
      strip.setPixelColor(i, strip.Color(170,30,0));
      delay(wait);
      strip.show();
    }
    for(uint16_t i=1; i<strip.numPixels(); i=i+2) {
      strip.setPixelColor(i, strip.Color(170,30,0));
      delay(wait);
      strip.show();
    }
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;
  while(1){
  for(j=0; j<256; j++) {
    newState2 = digitalRead(BUTTON_PIN_2);

    if (newState2 == LOW && oldState2 == HIGH) {
      // Short delay to debounce button.
      delay(15);
      // Check if button is still low after debounce.
      newState2 = digitalRead(BUTTON_PIN_2);
      if (newState2 == LOW) {
        showIndicator++;
        if (showIndicator > 3)
          showIndicator=0;
        oldState2 = newState2;
        showType(showIndicator);
      }
      return;
    }
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
    oldState2 = newState2;
  }
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;
  while(1){
  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    newState2 = digitalRead(BUTTON_PIN_2);

    if (newState2 == LOW && oldState2 == HIGH) {
      // Short delay to debounce button.
      delay(15);
      // Check if button is still low after debounce.
      newState2 = digitalRead(BUTTON_PIN_2);
      if (newState2 == LOW) {
        showIndicator++;
        if (showIndicator > 3)
          showIndicator=0;
        oldState2 = newState2;
        showType(showIndicator);
      }
      return;
    }
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
    oldState2 = newState2;
  }
  }
}

//Theatre-style crawling lights.
void theaterChase(uint8_t color, uint8_t wait) {
  while (1) {  //do 10 cycles of chasing
  
    for (int q=0; q < 3; q++) {
      newState2 = digitalRead(BUTTON_PIN_2);

      if (newState2 == LOW && oldState2 == HIGH) {
        // Short delay to debounce button.
        delay(15);
        // Check if button is still low after debounce.
        newState2 = digitalRead(BUTTON_PIN_2);
        if (newState2 == LOW) {
          showIndicator++;
          if (showIndicator > 3)
            showIndicator=0;
          oldState2 = newState2;
          showType(showIndicator);
        }
        return;
      }
      if(color==0) {
        int change = 0;
        for(uint16_t i=0; i<strip.numPixels(); i=i+3) {
          if(change==0) {
            strip.setPixelColor(i+q, strip.Color(0, 35, 180));
            change = 1;
          }
          else {
            strip.setPixelColor(i+q, strip.Color(127, 127, 127));
            change = 0;
          }
        }   
      }
      if(color==1) {
        int change = 0;
        for(uint16_t i=0; i<strip.numPixels(); i=i+3) {
          if(change==0) {
            strip.setPixelColor(i+q, strip.Color(127, 0, 0));
            change = 1;
          }
          else {
            strip.setPixelColor(i+q, strip.Color(0, 127, 0));
            change = 0;
          }
        }   
      }
      if(color==2) {
        int change = 0;
        for(uint16_t i=0; i<strip.numPixels(); i=i+3) {
          if(change==0) {
            strip.setPixelColor(i+q, strip.Color(160,120,16));
            change = 1;
          }
          else {
            strip.setPixelColor(i+q, strip.Color(100, 100, 100));
            change = 0;
          }
        }   
      }
      if(color==3) {
        for(uint16_t i=0; i<strip.numPixels(); i=i+3) {
            strip.setPixelColor(i+q, strip.Color(170,30,0));
          }
       }   
      strip.show();
      delay(wait);

      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
      oldState2 = newState2;
    } 
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j=0; j < 256; j++) {     // cycle all 256 colors in the wheel
    for (int q=0; q < 3; q++) {
      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, Wheel( (i+j) % 255));    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
