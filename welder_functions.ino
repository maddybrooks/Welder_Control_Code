
#include <Adafruit_DS3502.h>
Adafruit_DS3502 ds3502 = Adafruit_DS3502();
#define WIPER_VALUE_PIN A0

void setup() {
  pinMode(7, OUTPUT); //connect to transistor?
  pinMode(10, OUTPUT); //connect to wire feed motor
  Serial.begin(115200);
  // Wait until serial port is opened
  while (!Serial) { delay(1); }

  Serial.println("Adafruit DS3502 Test");

  if (!ds3502.begin()) {
    Serial.println("Couldn't find DS3502 chip");
    while (1);
  }
  Serial.println("Found DS3502 chip");

}

void loop() {
int check_Val;
int wire_speed;
//control logic? ie. while(welding==true){
digitalWrite(7, HIGH); //turns on gas
check_Val=SetWiper(200); //control welder amperage - ramp up?
analogWrite(10, wire_speed); //writes PWM to motor
//}

//welding done:
analogWrite(10, 0);
SetWiper(0);
digitalWrite(7, LOW); //turn off the gas last
}

int SetWiper(int WiperVal){
  int actual_val;
  ds3502.setWiper(WiperVal);
  delay(500);
  actual_val=analogRead(WIPER_VALUE_PIN);
  if(actual_val==WiperVal)
    return 1;
   else
    return -1;
  }
