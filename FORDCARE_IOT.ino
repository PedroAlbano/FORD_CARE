/* IOT PROJETO FORD CARE 2020
 * PEDRO HENRIQUE ALBANO 
*/
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>
String json = "";
const char* ssid     = ""; // REDE WIFI
const char* password = ""; //SENHA
const char* host = ""; // HOST 
const int httpPort = 80;//PORTA

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
 }

 
void loop() {
   // Serial.println("teste");M
    if(WiFi.status()== WL_CONNECTED){   //CHECA CONEXÃO WIFI
        HTTPClient http;    //DECLARA HTTPClient
         
        if(Serial.available()){       
        json += Serial.readString();
    
            Serial.println(json);
            http.begin("/addcar_data");//HOST DO REQUEST
            http.addHeader("Content-Type", "application/json");
            int httpCode = http.POST(json);//ENVIA O REQUEST
            String payload = http.getString();        
            http.end(); 
            json = ""; // LIMPA O JSON
            delay(5000);                     
           
        }else{
        Serial.println("Error in WiFi connection");   
    }
 
}}
