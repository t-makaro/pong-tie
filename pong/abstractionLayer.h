/*
 * File name: Animations.h
 * Author: Tyler Makaro
 * How to use: 
 *  Use the ledNumToPoint to use turn the LEDs into a cartesian plane, and thus also for 3D functions z=f(x,f) for animation. Use the strengthFunction
 *  typedefs to pass these functions into a common structure for display it.
 * Notes:
 *  This file modified from https://github.com/t-makaro/TinkerTie
 */
typedef struct {
  char x; //in .5mm
  char y; //divide by 20. to get a float in centimeters
} point;

typedef float (*strengthFunction)(point, float);

point ledNumToPoint(byte ledNum){
  switch (ledNum){
    case 0:
      return {82,35};
    case 1:
      return {82,18};
    case 2:
      return {82,0};
    case 3:
      return {82,-18};
    case 4:
      return {82,-35};
    case 5:
      return {62,-26};
    case 6:
      return {62,-10};
    case 7:
      return {62,10};
    case 8:
      return {62,26};
    case 9:
      return {45,18};
    case 10:
      return {45,0};
    case 11:
      return {45,-18};
    case 12:
      return {27,-10};
    case 13:
      return {27,10};
    case 14:
      return {-27,10};
    case 15:
      return {-27,-10};
    case 16:
      return {-45,-18};
    case 17:
      return {-45,0};
    case 18:
      return {-45,19};
    case 19:
      return {-62,26};
    case 20:
      return {-62,10};
    case 21:
      return {-62,-10};
    case 22:
      return {-62,-26};
    case 23:
      return {-82,-35};
    case 24:
      return {-82,-18};
    case 25:
      return {-82,0};
    case 26:
      return {-82,18};
    case 27:
      return {-82,35};
  }
}

//helper functions
int red  (uint32_t colour) { return colour >> 16 & 0xFF; }
int green(uint32_t colour) { return colour >> 8 & 0xFF; }
int blue (uint32_t colour) { return colour & 0xFF; }

//strength 0 return the base colour, strength 1 returns the accent colour,
uint32_t addAccentColour(uint32_t baseColour, uint32_t accentColour, float strength){
  uint32_t r = constrain(  red(baseColour) + ((  red(accentColour) -   red(baseColour)) * strength), 0, 255);
  uint32_t g = constrain(green(baseColour) + ((green(accentColour) - green(baseColour)) * strength), 0, 255);
  uint32_t b = constrain( blue(baseColour) + (( blue(accentColour) -  blue(baseColour)) * strength), 0, 255);
  
  return (r << 16) | (g << 8) | b;
}
