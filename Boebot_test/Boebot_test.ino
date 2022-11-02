#include <Servo.h>    //voegt de library's toe die nodig zijn om het allemaal werkend te krijgen.

Servo servoL; // voegt servo Links toe.
Servo servoR; // voegt servo Rechts toe.

void setup()
{
  servoL.attach(11);    //koppelt servoL aan pin 11
  servoR.attach(10);    //koppelt servoR aan pin 10
  Serial.begin(9600);   //initiatie serial modem
  Serial.println("Test1\n"); 
}
void loop()
{     Serial.println("draaien rechts\n"); 
      servoL.writeMicroseconds(2000);
      servoR.writeMicroseconds(2000);    
      delay(2000);
      Serial.println("draaien links\n");    
      servoL.writeMicroseconds(1000);
      servoR.writeMicroseconds(1000);
      delay(2000);
      Serial.println("vooruit \n");    
      servoL.writeMicroseconds(2000);
      servoR.writeMicroseconds(1000);
      delay(1000);
      Serial.println("achteruit \n");   
      servoL.writeMicroseconds(1000);
      servoR.writeMicroseconds(2000);
      delay(1000);
      Serial.println("Stop \n");   
      servoL.writeMicroseconds(1500);
      servoR.writeMicroseconds(1500);
      delay(1200);
      // while(1);
}









