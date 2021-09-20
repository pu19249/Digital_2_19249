/*
   LAB06 = Decade counter
   Tiva C. tm4c123
   Jonathan Pu
   c. 19249
*/

/* ========================================
    PREDEFINITION OF VARIABLES
   ========================================
*/
//setup pins for player1
#define led1_1 PB_5
#define led2_1 PB_0
#define led3_1 PB_1
#define led4_1 PE_4
#define led5_1 PE_5
#define led6_1 PB_4
#define led7_1 PA_5
#define led8_1 PA_6

//setup pins for player2
#define led1_2 PB_3
#define led2_2 PC_4
#define led3_2 PC_5
#define led4_2 PC_6
#define led5_2 PC_7
#define led6_2 PD_6
#define led7_2 PD_7
#define led8_2 PA_3

//setup pins for traffic lights
const byte red = RED_LED;
const byte blue = BLUE_LED;
const byte green = GREEN_LED;

int counter1 = 0; //initialize counter in 0
int counter2 = 0;
int state1 = 0; //flag to increment counter
int state2 = 0;
int start = 0; //flag to start the traffic light sequence
int outPins[8] = {led1_1, led2_1, led3_1, led4_1, led5_1, led6_1, led7_1, led8_1};

/* ========================================
    pins SETUP
   ========================================
*/
void setup() {
  //initialize the PUSH1 and PUSH2 as an input
  pinMode(PUSH1, INPUT_PULLUP);
  pinMode(PUSH2, INPUT_PULLUP);
  pinMode(PB_7, INPUT_PULLUP);
  //initialize 8 pins as output for the decade counter
  pinMode(led1_1, OUTPUT);
  pinMode(led2_1, OUTPUT);
  pinMode(led3_1, OUTPUT);
  pinMode(led4_1, OUTPUT);
  pinMode(led5_1, OUTPUT);
  pinMode(led6_1, OUTPUT);
  pinMode(led7_1, OUTPUT);
  pinMode(led8_1, OUTPUT);

  pinMode(led1_2, OUTPUT);
  pinMode(led2_2, OUTPUT);
  pinMode(led3_2, OUTPUT);
  pinMode(led4_2, OUTPUT);
  pinMode(led5_2, OUTPUT);
  pinMode(led6_2, OUTPUT);
  pinMode(led7_2, OUTPUT);
  pinMode(led8_2, OUTPUT);

  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);

}

/* ========================================
    MAIN LOOP
   ========================================
*/

void loop() {

  //PRELAB
  //  int i = 0; //two variables to iterate over to for loops
  //  int j = 0;
  //  if (digitalRead(PUSH1) == LOW) { //push to activate the counter
  //    for (i = 0; i < 255; i++) { //255 numbers we can get
  //      for (j = 0; j < 8; j++) { //8 leds that we have
  //        if ( ((i >> j) & 1 )  == 1)  { //division to take the binary number
  //          digitalWrite(outPins[j], HIGH); //turn on the leds in the array
  //        }
  //        else {
  //          digitalWrite(outPins[j], LOW); //or turn them all down
  //        }
  //      }
  //      delay(250);
  //    }
  //  }

  //LAB

  if (digitalRead(PUSH1) == HIGH && state1 == 0) { //initialize everything off
    digitalWrite(led1_1, LOW);
    digitalWrite(led2_1, LOW);
    digitalWrite(led3_1, LOW);
    digitalWrite(led4_1, LOW);
    digitalWrite(led5_1, LOW);
    digitalWrite(led6_1, LOW);
    digitalWrite(led7_1, LOW);
    digitalWrite(led8_1, LOW);

    digitalWrite(led1_2, LOW);
    digitalWrite(led2_2, LOW);
    digitalWrite(led3_2, LOW);
    digitalWrite(led4_2, LOW);
    digitalWrite(led5_2, LOW);
    digitalWrite(led6_2, LOW);
    digitalWrite(led7_2, LOW);
    digitalWrite(led8_2, LOW);
    
  }
  //debouncing for the two push buttons
  if (digitalRead(PUSH1) == HIGH) {
    state1 = 1;
  }
  if (digitalRead(PUSH2) == HIGH) {
    state2 = 1;
  }
  if (digitalRead(PUSH1) == LOW && state1 == 1) {
    counter1++;
    state1 = 0;
  }
  if (digitalRead(PUSH2) == LOW && state2 == 1) {
    counter2++;
    state2 = 0;
  }

  //Traffic light routine with RGB
  if ((counter1 == 1 || counter2 == 1) && (start == 0)) {
    digitalWrite(red, HIGH);
    delay(1000);
    digitalWrite(green, HIGH);
    delay(1000);
    digitalWrite(red, LOW);
    delay(1000);
    digitalWrite(green, LOW);
    delay(1000);
    start = 1;
    counter1 = 2;
    counter2 = 2;
  }

  //start of the counters for each player
  //PLAYER1
  if (counter1 == 3) {
    digitalWrite(led1_1, HIGH);
    delay(100);
    digitalWrite(green, LOW);
  }
  if (counter1 == 4) {
    digitalWrite(led1_1, LOW);
    digitalWrite(led2_1, HIGH);
    delay(100);
  }
  if (counter1 == 5) {
    digitalWrite(led1_1, LOW);
    digitalWrite(led2_1, LOW);
    digitalWrite(led3_1, HIGH);
    delay(100);
  }
  if (counter1 == 6) {
    digitalWrite(led3_1, LOW);
    digitalWrite(led4_1, HIGH);
    delay(100);
  }
  if (counter1 == 7) {
    digitalWrite(led4_1, LOW);
    digitalWrite(led5_1, HIGH);
  }
  if (counter1 == 8) {
    digitalWrite(led5_1, LOW);
    digitalWrite(led6_1, HIGH);
  }
  if (counter1 == 9) {
    digitalWrite(led6_1, LOW);
    digitalWrite(led7_1, HIGH);
  }
  if (counter1 == 10) {
    digitalWrite(led7_1, LOW);
    digitalWrite(led8_1, HIGH);

    digitalWrite(green, HIGH);
    delay(1000);
    digitalWrite(green, LOW);
    counter1 = 0;
    counter2 = 0;
    start = 0; //initialize traffic light again

    state1 = 0;
  }

  
  //PLAYER2
  if (counter2 == 3) {
    digitalWrite(led1_2, HIGH);
    digitalWrite(green, LOW);
    delay(100);
  }
  if (counter2 == 4) {
    digitalWrite(led1_2, LOW);
    digitalWrite(led2_2, HIGH);
    delay(100);
  }
  if (counter2 == 5) {
    digitalWrite(led2_2, LOW);
    digitalWrite(led3_2, HIGH);
    delay(100);
  }
  if (counter2 == 6) {
    digitalWrite(led3_2, LOW);
    digitalWrite(led4_2, HIGH);
    delay(100);
  }
  if (counter2 == 7) {
    digitalWrite(led4_2, LOW);
    digitalWrite(led5_2, HIGH);
  }
  if (counter2 == 8) {
    digitalWrite(led5_2, LOW);
    digitalWrite(led6_2, HIGH);
  }
  if (counter2 == 9) {
    digitalWrite(led6_2, LOW);
    digitalWrite(led7_2, HIGH);
  }
  if (counter2 == 10) {
    digitalWrite(led7_2, LOW);
    digitalWrite(led8_2, HIGH);

    digitalWrite(red, HIGH);
    digitalWrite(blue, HIGH);
    delay(1000);
    digitalWrite(blue, LOW);
    digitalWrite(red, LOW);
    counter1 = 0;
    counter2 = 0;
    start = 0; //initialize traffic light again
    state1 = 0;
    
  }
}
