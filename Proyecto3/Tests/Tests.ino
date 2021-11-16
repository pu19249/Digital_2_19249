int status2;
void setup() {
  Serial.begin(115200);
  Serial.setTimeout(50);
  delay(100);
}
void loop() {
  if (Serial.available()>0) {
    // read the incoming byte:
    status2 = Serial.read();
    if (status2 == '1')
    {
      Serial.print('1');
    }
  }
}
