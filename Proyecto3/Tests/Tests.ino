
int status2;
void setup() {
  Serial2.begin(115200);
  Serial2.setTimeout(50);
  delay(100);
  Serial.begin(115200);
  
  pinMode(12, OUTPUT); //e
  pinMode(14, OUTPUT); //d
  pinMode(27, OUTPUT); //c
  pinMode(26, OUTPUT); //g
  pinMode(25, OUTPUT); //f
  pinMode(33, OUTPUT); //a
  pinMode(32, OUTPUT); //b
}
void loop() {
  if (Serial2.available()) {
    status2 = Serial2.read();
    //0
    if (status2 == '0') {
      status2 = 0;
      Serial.print('0');
      digitalWrite(33, HIGH); //
      digitalWrite(32, HIGH); //
      digitalWrite(27, HIGH); //
      digitalWrite(14, HIGH); //
      digitalWrite(12, HIGH); //
      digitalWrite(25, HIGH); //
      digitalWrite(26, LOW); //
      delay(1000);
    }
    else if (status2 == '1') {
      //1
      status2 = 0;
      Serial.print('1');
      digitalWrite(33, LOW); //
      digitalWrite(32, HIGH); //
      digitalWrite(27, HIGH); //
      digitalWrite(14, LOW); //
      digitalWrite(12, LOW); //
      digitalWrite(25, LOW); //
      digitalWrite(26, LOW); //
      delay(1000);
    }
    else if (status2 == '2') {
      //2
      status2 = 0;
      Serial.print('2');
      digitalWrite(33, HIGH); //
      digitalWrite(32, HIGH); //
      digitalWrite(27, LOW); //
      digitalWrite(14, HIGH); //
      digitalWrite(12, HIGH); //
      digitalWrite(25, LOW); //
      digitalWrite(26, HIGH); //
      delay(1000);
    }
    else if (status2 == '3') {
      //3
      status2 = 0;
      Serial.print('3');
      digitalWrite(33, HIGH); //
      digitalWrite(32, HIGH); //
      digitalWrite(27, HIGH); //
      digitalWrite(14, HIGH); //
      digitalWrite(12, LOW); //
      digitalWrite(25, LOW); //
      digitalWrite(26, HIGH); //
      delay(1000);
    }
    else if (status2 == '4') {
      //4
      //status2 = 0;
      Serial.print('4');
      digitalWrite(33, LOW); //
      digitalWrite(32, HIGH); //
      digitalWrite(27, HIGH); //
      digitalWrite(14, LOW); //
      digitalWrite(12, LOW); //
      digitalWrite(25, HIGH); //
      digitalWrite(26, HIGH); //
      delay(1000);
    }
    else  if (status2 == '5') {
      //5
      //status2 = 0;
      Serial.print('5');
      digitalWrite(33, HIGH); //
      digitalWrite(32, LOW); //
      digitalWrite(27, HIGH); //
      digitalWrite(14, HIGH); //
      digitalWrite(12, LOW); //
      digitalWrite(25, HIGH); //
      digitalWrite(26, HIGH); //
      delay(1000);
    }
    else if (status2 == '6') {
      //6
      //status2 = 0;
      Serial.print('6');
      digitalWrite(33, LOW); //
      digitalWrite(32, LOW); //
      digitalWrite(27, HIGH); //
      digitalWrite(14, HIGH); //
      digitalWrite(12, HIGH); //
      digitalWrite(25, HIGH); //
      digitalWrite(26, HIGH); //
      delay(1000);
    }
    else if (status2 == '7') {
      //7
      //status2 = 0;
      Serial.print('7');
      digitalWrite(33, HIGH); //
      digitalWrite(32, HIGH); //
      digitalWrite(27, HIGH); //
      digitalWrite(14, LOW); //
      digitalWrite(12, LOW); //
      digitalWrite(25, LOW); //
      digitalWrite(26, LOW); //
      delay(1000);
    }
    else if (status2 == '8') {
      //8
      //status2 = 0;
      Serial.print('8');
      digitalWrite(33, HIGH); //
      digitalWrite(32, HIGH); //
      digitalWrite(27, HIGH); //
      digitalWrite(14, HIGH); //
      digitalWrite(12, HIGH); //
      digitalWrite(25, HIGH); //
      digitalWrite(26, HIGH); //
      delay(1000);
    }
  }


}
