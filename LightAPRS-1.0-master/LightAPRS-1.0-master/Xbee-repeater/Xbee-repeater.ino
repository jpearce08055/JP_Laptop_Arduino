void setup() {
  // put your setup code here, to run once:
  Serial1.begin(9600); // Xbee
  Serial.begin (9600); //Console
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial1.available() > 0 )
  {
     Serial.println(Serial1.read());
//    if (Serial1.read () == 'D')
//    {
//      Serial1.print ("K");
//      Serial.println("QSL");
//    }
    delay (1000);
  
  }
  Serial.println ("------------------------");
}
