//Arduino Leonardo XBee Test Code
int led = 13;
int temp = 0;
 
void setup() {
  Serial1.begin(9600); 
  Serial.begin (9600);
  pinMode(led, OUTPUT);
}
 
void loop() {
  if (Serial1.available() > 0) {
    temp = Serial1.read();
    Serial.println (temp);
    digitalWrite(led, HIGH);
    //delay(1000);
    digitalWrite(led, LOW);
    //delay(1000);
  }
  //Serial1.print ('0'); 
}
