/*Author: Jesus Ledezma
//Exercise 1 of Assignment 1 
//EENG 350 SEED Lab (Colorado School of Mines)
//9/3/2025
//A script written for the Arduino Uno that will turn on 4 LEDs in order until all of them have lit up and extinguish them in order
//until every one of them is off. Can be connected to a "gas" and "brake" button that will speed up or slow down the blinking respectively.
*/
int EXT_INTERRUPT_1 = 2;
int EXT_INTERRUPT_2 = 3;

int LEDs[] = {4, 5, 6, 7};

volatile bool timerCompareFlag; 
const int minDelayCounts = 155; //10 ms min
const int maxDelayCounts = 15624; //1s max

//in gasOn, decrease amount of counts until timer interrupt
void gasOn() {
  if (OCR1A >= (minDelayCounts + 100)) OCR1A -= 100; //can you reference OCR1A like this in different interrupts w/o calling it a volatile or something?
}

//in breakOn, increase amount of counts until timer interrupt
void brakeOn() {
  if (OCR1A <= (maxDelayCounts - 100)) OCR1A += 100;
}

ISR(TIMER1_COMPA_vect){
  timerCompareFlag = true;  
}

void setup() {
  cli(); //clear interrupts while setting shit up

  //setting up Timer1 since it is 16 bit
  TCCR1A = 0; //set TCCR1A register to 0
  TCCR1B = 0; //set TCCR1B reg to 0 
  TCNT1 = 0; //initialize counter at 0
  OCR1A = 1562; //set compare match reg to give 10 Hz interrupt frequency (100ms default) 
                //compare match reg = [(16Mhz(Arduino clk speed) / (prescaler*10Hz(want 100 ms interrupt))] -1
                //output compare register 1
  TCCR1B |= (1 << WGM12); //setup CTC mode (ClearTimeronCompare)
  TCCR1B |= (1 << CS12) | (1 << CS10); // Set CS10 and CS12 bits for 1024 prescaler
  TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt
  
  for (int i = 0; i < 4; i++) pinMode(LEDs[i], OUTPUT);

  pinMode(EXT_INTERRUPT_1, INPUT);
  pinMode(EXT_INTERRUPT_2, INPUT);

  attachInterrupt(digitalPinToInterrupt(EXT_INTERRUPT_1), gasOn, RISING);
  attachInterrupt(digitalPinToInterrupt(EXT_INTERRUPT_2), brakeOn, RISING);

  timerCompareFlag = false;
  sei();
  
}



void loop() {

  for (int i = 0; i < 4; i++) {
    digitalWrite(LEDs[i], HIGH);
    while(timerCompareFlag == false);
    timerCompareFlag = false;
  }

  while(timerCompareFlag == false);
  timerCompareFlag = false;

  for (int i = 0; i < 4; i++) {
    digitalWrite(LEDs[i], LOW);
    while(timerCompareFlag == false);
    timerCompareFlag = false;
  }

}

