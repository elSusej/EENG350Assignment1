A script written for the Arduino Uno that will turn on 4 LEDs in order until all of them have lit up and extinguish them in order until every one of them is off. Can be connected to a "gas" and "brake" button that will speed up or slow down the blinking respectively.

NOTE: LEDs MUST be connected to digital pins 4-7 through a resistor, and then be wired back to GND. 2 buttons must then be wired to 5v and a pull-down resistor so that the arduino reads a consistent 0 when the button is NOT pressed (active-high). 
      The output of the buttons must then go to digital pins 2 and 3 on the Arduino Uno, as these are the only external interrupt pins avaiable. 
