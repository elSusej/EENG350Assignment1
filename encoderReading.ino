/*Jesus Ledezma
 *Exercise 2 of Assignment 1
 *Date of Creation: 9/4/2025
 *Notes: Don't need pullup resitor from Arduino in code, connect + to 5v. Connect DT to APIN (2 in this case), and CLK to BPIN for "proper" CW and CCW
 */

int APIN = 2;
int BPIN = 4;
int thisA;
int thisB;
int lastA;
int lastB;

volatile long encoderCounts = 0;
unsigned long desired_Ts_ms = 25; // desired sample time in milliseconds
unsigned long last_time_ms;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(APIN, INPUT);
  pinMode(BPIN, INPUT);

  attachInterrupt(digitalPinToInterrupt(APIN), APIN_Interrupt,CHANGE);
}

void APIN_Interrupt(){
  thisA = digitalRead(APIN);
  thisB = digitalRead(BPIN);

  if (thisA == thisB) {
    encoderCounts+=2;
    //rotated 2 counts in one direction
  } else {
    encoderCounts-=2;
    // 2 counts in other direction
  }

  lastA = thisA;
  lastB = thisB;
}

long MyEnc() {
  thisA = digitalRead(APIN);
  thisB = digitalRead(BPIN);
  int prev = (lastA << 1) | lastB;
  int curr = (thisA << 1) | thisB;

  switch(prev) {
    case 0b00:
      if(curr == 0b01) encoderCounts++; // CW
      else if(curr == 0b10) encoderCounts--; // CCW
      break;
    case 0b01:
      if(curr == 0b11) encoderCounts++; // CW
      else if(curr == 0b00) encoderCounts--; // CCW
      break;
    case 0b11:
      if(curr == 0b10) encoderCounts++; // CW
      else if(curr == 0b01) encoderCounts--; // CCW
      break;
    case 0b10:
      if(curr == 0b00) encoderCounts++; // CW
      else if(curr == 0b11) encoderCounts--; // CCW
      break;
}
  lastA = thisA;
  lastB = thisB; 

  return encoderCounts;
}
void loop() {
  Serial.println(MyEnc());
  while (millis()<last_time_ms + desired_Ts_ms) {
  //wait until desired time passes to go top of the loop
  }
  last_time_ms = millis();
}
