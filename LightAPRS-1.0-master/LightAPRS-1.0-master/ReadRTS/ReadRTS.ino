void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println ("Starting up");
  pinMode (3, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println ("RTS="+String(digitalRead(3)));
  delay (100);
}
