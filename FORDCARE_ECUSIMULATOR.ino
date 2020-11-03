/* SIMULADOR DE ECU PROJETO FORD CARE 2020
 * PEDRO HENRIQUE ALBANO 
*/
#include <ArduinoJson.h>
#include <SoftwareSerial.h>
#include <EEPROM.h>

const int potenciometro1 = 0;
const int potenciometro2 = 1;
const int potenciometro3 = 2;
int valor1 = 0.0;
int valor2 = 0.0;
int valor3 = 0.0;
int valor_tempmap; 
int valor_tempmap2; 
int valor_loadmap;
int valor_pwrmap;
int valor_rpmmap;
int valor_mileage;
int valor_mileagebuf1;
int valor_mileagebuf2;
int valor_mileagebuf3;
String AIR_INTAKE_TEMPbuf;
String ENGINE_COOLANT_TEMPbuf;
String ENGINE_LOADbuf;
String ENGINE_POWERbuf;
String ENGINE_RPMbuf;
String INTAKE_MANIFOLD_PRESSUREbuf;
String SPEEDbuf;
String THROTTLE_POSbuf;
String MILEAGEbuf;
String car_id;
String json;
int button1;
int button2;
int buttonstate = 0;
 
void setup() {
  Serial.begin(115200);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  }
void loop() {
  button1 = digitalRead(2);
  button2 = digitalRead(3);
    if (button1 == HIGH){
   buttonstate = 1;
    }
    if (button2 == HIGH){
    buttonstate = 0;
    }
    if (buttonstate == 1){
    car_id = "5f700a577504ff40d41390fc";
      }else{
      car_id = "5f700b2d7504ff40d41390fd";
      }
valor1 = analogRead(potenciometro1);
valor2 = analogRead(potenciometro2);
valor3 = analogRead(potenciometro3);

valor_tempmap = map(valor2,0,1023,0,200);
valor_tempmap2 = map(valor2,0,1023,0,130);
valor_loadmap = map(valor3,0,1023,0,100);
valor_rpmmap = map(valor1,0,1023,500,7000);
valor_pwrmap = map(valor1,0,1023,0,300);
valor_mileagebuf1 = EEPROM.read(0);
valor_mileagebuf2 =map(valor_mileagebuf1,0,255,0,20000);
valor_mileage = valor_mileagebuf2 + valor_pwrmap;

AIR_INTAKE_TEMPbuf  += (String(valor_tempmap2));
ENGINE_COOLANT_TEMPbuf  += (String(valor_tempmap));
ENGINE_LOADbuf += (String(valor_loadmap));
ENGINE_POWERbuf += (String(valor_pwrmap));
ENGINE_RPMbuf += (String(valor_rpmmap));
INTAKE_MANIFOLD_PRESSUREbuf += (String(valor_pwrmap));
SPEEDbuf += (String(valor_pwrmap));               
THROTTLE_POSbuf += (String(valor_tempmap));
MILEAGEbuf +=  (String(valor_mileage));
          
valor_mileagebuf3 = map(valor_mileage,0,20000,0,255);  
EEPROM.write(0,valor_mileagebuf3);
              
DynamicJsonDocument doc(200);

doc["CAR"] = car_id;
doc["AIR_INTAKE_TEMP"] = AIR_INTAKE_TEMPbuf;
doc["ENGINE_COOLANT_TEMP"] = ENGINE_COOLANT_TEMPbuf;
doc["ENGINE_LOAD"] = ENGINE_LOADbuf;
doc["ENGINE_POWER"] = ENGINE_POWERbuf;
doc["ENGINE_RPM"] = ENGINE_RPMbuf;
doc["INTAKE_MANIFOLD_PRESSURE"] = INTAKE_MANIFOLD_PRESSUREbuf;
doc["SPEED"] = SPEEDbuf;
doc["THROTTLE_POS"] = THROTTLE_POSbuf;
doc["ODOMETER"] = MILEAGEbuf;
               
serializeJson(doc, json);              
Serial.println(json);               
delay(5000);

AIR_INTAKE_TEMPbuf  = "";
ENGINE_COOLANT_TEMPbuf = "";
ENGINE_LOADbuf = "";
ENGINE_POWERbuf = "";
ENGINE_RPMbuf = "";
INTAKE_MANIFOLD_PRESSUREbuf = "";
SPEEDbuf = "";          
THROTTLE_POSbuf = "";
MILEAGEbuf = "";
json = "";
  }
