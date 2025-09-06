/*Jesus Ledezma
 *Exercise 2 of Assignment 1
 *Date of Creation: 9/4/2025
 *Notes: Don't need pullup resitor from Arduino in code, connect + to 5v. Connect DT to APIN (2 in this case), and CLK to BPIN for "proper" CW and CCW
 */

int APIN = 2;
int BPIN = 3;

int thisA;
int thisB;
int lastA;
int lastB;

long encoderCounts = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(APIN, INPUT);
  pinMode(BPIN, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly
  
  thisA = digitalRead(APIN);
  thisB = digitalRead(BPIN);
  
  if (lastA != thisA || lastB != thisB) {
    Serial.print(thisA);
    Serial.print("\t");
    Serial.println(thisB);
    
    if ((lastA != thisA) && (thisA == thisB)) {
      encoderCounts++; //clockwise is positive by convention
    } else if ((lastB != thisB) && (thisA == thisB)) { // conditional right?
      encoderCounts--;
    }

    lastA = thisA;
    lastB = thisB;
    //Serial.print("enderCounts value is: ");
    //Serial.println(encoderCounts);
  }
}
