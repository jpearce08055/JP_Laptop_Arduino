  
#include <VirtualWire.h>

// Define pins for radio
const int transmit_pin = 12;

//Define pins for joystick
#define ParkPin 12
int VertPin = A0;
int HorizPin = A1;
int xPosition = 0;
int yPosition = 0;
int Vmsg=83;
int Hmsg=83;
int park = 0;
//String Vmsg;
//String Hmsg;
//String VHmsg;

void setup() 
{
  // put your setup code here, to run once:
  vw_set_tx_pin(transmit_pin);
  vw_setup (2000);
  pinMode (13,OUTPUT); // Use motherboard pin fo xmit indicator
  Serial.begin(9600);
}

void Read_Joystick ()
{
  xPosition = analogRead(HorizPin);
  yPosition = analogRead(VertPin);
  park = digitalRead(ParkPin);
//  Serial.println("Starting print");
  Serial.println("X="+String(xPosition));
  Serial.println("Y="+String(yPosition));
//  delay (3000);

  //Moving up
  if (yPosition > 400)Vmsg=85;

  //Moving down
  if (yPosition < 200)Vmsg=68;

  //Moving right
  if (xPosition > 400) Hmsg=76;
 
  //Moving left
  if (xPosition < 200) Hmsg=82;
 
  // Not moving vert
  if (( (yPosition - 200) | (400 - yPosition)) >= 0) Vmsg=83;

  // Not moving horiz
  if (( (xPosition - 200) | (400 - xPosition)) >= 0) Hmsg=83;
}

void loop() 
{
  Read_Joystick();
//   Message is vertical, horiz move. S=stopped. U,D for vertical, L,R for horizontal
//     Rsend ("SS");
   char msg [2] = {Vmsg, Hmsg};

//  Serial.println ("Sending " + VHmsg);
  Rsend (msg);
  delay (100);
}

void Rsend (char *message)
{
  digitalWrite(13,HIGH); //Turn on motherboard LED
  vw_send((uint8_t *)message, strlen(message));
  vw_wait_tx ();
  //Serial.println ("Sent packet");
  digitalWrite(13,LOW);
}
