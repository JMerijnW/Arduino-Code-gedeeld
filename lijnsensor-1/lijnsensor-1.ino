#include <Servo.h>    //voegt de library's toe die nodig zijn om de servo's aan te sturen via PWM.

#define LEVEL 400     // Analoog grensniveau van de (lijn/geen lijn) detectie van de reflectiemeting met de CNY70 
#define STP 1500  // waarde in micro seconden om de rotating servo's te laten stoppen.
#define VOORUIT 1530
#define ACHTERUIT 1470



Servo servoL; // maakt servo object (L)inks aan.
Servo servoR; // maakt servo object (R)echts aan.

const int Reflectpin_a = A0;    // selecteer de input pin A0 voor reflectiesensor a met een vaste waarde (const)
const int Reflectpin_b = A1;    // selecteer de input pin A1 voor reflectiesensor b met een vaste waarde (const)
const int Reflectpin_c = A2;    // selecteer de input pin A2 voor reflectiesensor c met een vaste waarde (const)
const int Reflectpin_d = A3;    // selecteer de input pin A3 voor reflectiesensor d met een vaste waarde (const)
const int Sharp_pin    = A4;    // select the input pin for Sharp afstandssensor 

//Prototypes:
char SensorRead(void); // Prototype functie: returnwaarde:  0000DCBA  A, B, C, D    0 of 1 afhankelijk of sensorwaarde hoger of lager dan LEVEL is.
void Actie(int);   //Prototype functie: bepaald servoactie op basis returnwaarde SensorRead 
void Servostring(int, char);   //Prototype functie sturing sensors

void setup() {
  servoR.attach(10);    //koppelt servoL (linker servo) aan pin 11
  servoL.attach(11);    //koppelt servoR (Rechter servo) aan pin 10
  Serial.begin(9600);
    while (!Serial) {
      ; // wait for serial port to connect. Needed for native USB port only
    }

  Serial.println("START programma.");

  pinMode(7, OUTPUT);
  
}

void loop() {
    // put your main code here, to run repeatedly:
  
  digitalWrite(9, LOW);
  digitalWrite(7, LOW);

  char SensorOutput;
  SensorOutput = SensorRead();
  Actie(SensorOutput);

  Serial.println(SensorOutput, BIN);

  delay(20); // deze delay bepaalt (mede) de reactiesnelheid 
}

char SensorRead(void)
{
//digitalWrite(SensorToggle, HIGH); // Optie: batterij besparing: Schakel de sensoren in
  
int ReflectValue_a = 0;
int ReflectValue_b = 0;
int ReflectValue_c = 0;
int ReflectValue_d = 0;
int ReturnValue = 0;

ReflectValue_a = analogRead(Reflectpin_a);
ReflectValue_b = analogRead(Reflectpin_b);
ReflectValue_c = analogRead(Reflectpin_c);
ReflectValue_d = analogRead(Reflectpin_d);
//Serial.print("sensor_a = " );       // debug                
//Serial.println(ReflectValue_a);     // debug
if(ReflectValue_a < LEVEL) ReturnValue |= 0x01; else ReturnValue &= ~(0x01);
if(ReflectValue_b < LEVEL) ReturnValue |= 0x02; else ReturnValue &= ~(0x02);
if(ReflectValue_c < LEVEL) ReturnValue |= 0x04; else ReturnValue &= ~(0x04);
if(ReflectValue_d < LEVEL) ReturnValue |= 0x08; else ReturnValue &= ~(0x08); // True set: -------1, False reset: -------0, zie blz 91 en 92 boek "IzmC"
//Serial.println(ReturnValue);        // debug

// zelf verder invullen
 
//digitalWrite(SensorToggle, LOW); // Optie batterijbesparing: Schakel de sensoren uit

return ReturnValue;
}

void Actie(char waarde)
{
  
  switch(waarde)  // 16 mogelijke waarden met 4 sensoren, ServoSturingswaarden zijn in dit concept willekeuring gekozen, zelf aanpassen.
  {
  
    case 0x00:
    {Servostring("achteruit",0);
    digitalWrite(7, HIGH);
    }
    break;

    case 0x01:
    {Servostring("vooruit",0);
    }
    break;

    case 0x02:
    {Servostring("rechts",100);
    }
    break;

    case 0x03:
    {Servostring("vooruit",0);
    }
    break;

    case 0x04:
    {Servostring("achteruit",0);
    }
    break;

    case 0x05:
    {Servostring("vooruit",0);
    }
    break;

    case 0x06:
    {Servostring("vooruit",0);
    }
    break;
  
    case 0x07:  
    {//Servostring("vooruit",0);
    }
    break;

    case 0x08:
    {Servostring("links",100);
    }
    break;

    case 0x09:
    {Servostring("vooruit",0);
    }
    break;    

    case 0x0A:
    {//Servostring("vooruit",0);
    }
    break;

    case 0x0B:
    {//Servostring("vooruit",0);
    }
    break;

    case 0x0C:
    {Servostring("links",0);
    }
    break;

    case 0x0D:
    {//Servostring("vooruit",0);
    }
    break;

    case 0x0E:
    {//Servostring("vooruit",0);
    }
    break;

    case 0x0F:
    {Servostring("vooruit",0);
    }
    break;

    
}
}

void Servostring(int input_var, char var)
{       
      //TODO   De links en rechts richtingen van de servo's zijn misschien ongedraaid
      // dit moet nog aangepast worden

      if (input_var == "vooruit") {
        servoL.writeMicroseconds(1700-var);
        servoR.writeMicroseconds(1300+var);
        Serial.println("vooruit");
      }
      else if (input_var == "links"){
        servoL.writeMicroseconds(1400-var);
        servoR.writeMicroseconds(1400-var);
        Serial.println("links");
      }
      else if (input_var == "rechts"){
        servoL.writeMicroseconds(1600+var);
        servoR.writeMicroseconds(1600+var);
        Serial.println("rechts");
      }
      else if (input_var == "achteruit"){
        servoL.writeMicroseconds(1700-var);
        servoR.writeMicroseconds(1300+var);
        Serial.println("achteruit");
      }
      else if (input_var == "stilstaan"){
        servoL.writeMicroseconds(1500);
        servoR.writeMicroseconds(1500);
        Serial.println("stilstaan");
      }
}
