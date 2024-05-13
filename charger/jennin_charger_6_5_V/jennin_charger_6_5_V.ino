#include <QC3Control.h> // Add missing include statement

// Antti Suomi 11.5.2024
// 6.5 V and 1 amp charger for Led hoop
// Pin 4 for Data+
// Pin 5 for Data-

QC3Control quickCharge(4, 5);

void setup()
{
  pinMode(6, OUTPUT); // green led
 
//Pin 4 for Data+
//Pin 5 for Data-
//See How to connect in the documentation for more details.
 
  //Optional
  quickCharge.begin();
  //set voltage to 12V
  quickCharge.set5V();
  delay(3000);
}
void loop() {
  //And you can change it on the fly
  digitalWrite(6, HIGH);

  quickCharge.setMilliVoltage(6600);
  delay(3000);
  digitalWrite(6, LOW);
}