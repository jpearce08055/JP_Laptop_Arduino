int VertPin = A0;
int HorizPin = A1;
int LED1 = 2;
int LED2 = 3;
int xPosition = 0;
int yPosition = 0;
String yChar;
String xChar;

int debug = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600);
  pinMode (VertPin, INPUT);
  pinMode (HorizPin, INPUT);
  pinMode (LED1,OUTPUT);
  pinMode (LED2,OUTPUT);
}

void PrintConstant ()
{
  Serial.print ("X");
}


void ReadJoystick() 
{
  // put your main code here, to run repeatedly:
  digitalWrite(LED2,HIGH);
  xPosition = analogRead(A0);
  yPosition = analogRead(A1);

  yChar = 'S';
  if (yPosition > 600) yChar = "U";
  if (yPosition < 300) yChar = "D";

  xChar = 'S';
  if (xPosition > 600) xChar = "L";
  if (xPosition < 300) xChar = "R";
  if(debug == 1)
  {
    Serial.println ();
    Serial.println ("xP="+String(xPosition));
    Serial.println ("yP="+String(yPosition));
    Serial.println ("Y="+String(yChar));
    Serial.println ("X="+String(xChar));
  }
//  Serial.print ('0'); 
//  Serial.print (xChar);
//  Serial.print (yChar);
  Serial.print ('0'+xChar+yChar);
  //Serial.println ();

  delay (10);
  digitalWrite(LED2,LOW);
  delay(100);
}

void loop()
{
  ReadJoystick();
  //PrintConstant();
}  
