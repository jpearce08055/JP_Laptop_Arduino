const int ReadPin = A0;
long reading;

void setup() {
  // put your setup code here, to run once:
  analogReference(EXTERNAL);
  Serial.begin(9600);
  Serial.println ("Starting up");
}

void loop() {
  // put your main code here, to run repeatedly:
    //reading = analogRead(ReadPin);
    Serial.println ("Pin 0="+String(analogRead(A0)));
    Serial.println ("Pin 1="+String(analogRead(A1)));
    Serial.println ("Pin 2="+String(analogRead(A2)));
    //Serial.println ("Pin "+String(ReadPin) + " = " + String(reading));
    Serial.println ("");
    delay (3000);

}
