/*
 * https://solarbotics.com/product/33600/
 * 42BYGHW811 NEMA-17 Bipolar 48mm Stepper
 * Board Connector A is Black
 * Board Connector B is Green
 * Board Connector C is Red
 * Board Connector D is Blue
 * Voltage 3.1V
 * Current 2.5A
 * To wire for counter-clockwise rotation, swap the Red and Blue wires.
 *
 * https://www.allaboutcircuits.com/tools/voltage-divider-calculator/
 * Vin = 5 V
 * R1 = 220 Ohm
 * R2 = 330 Ohm
 *
 * https://www.pololu.com/product/1182
 * A4988 Stepper Motor Driver Carrier
 */

// Run a A4998 Stepstick from an Arduino UNO.
// Paul Hurley Aug 2015
int x;
#define BAUD (9600)


void setup()
{
  Serial.begin(BAUD);
  pinMode(6,OUTPUT); // Enable
  pinMode(5,OUTPUT); // Step
  pinMode(4,OUTPUT); // Dir
  digitalWrite(6,LOW); // Set Enable low
}

void loop()
{
  digitalWrite(6,LOW); // Set Enable low
  digitalWrite(4,HIGH); // Set Dir high
  Serial.println("Loop 200 steps (1 rev)");
  for(x = 0; x < 200; x++) // Loop 200 times
  {
    digitalWrite(5,HIGH); // Output high
    delay(10); // Wait
    digitalWrite(5,LOW); // Output low
    delay(100); // Wait
  }
  Serial.println("Pause");
  delay(1000); // pause one second
}
