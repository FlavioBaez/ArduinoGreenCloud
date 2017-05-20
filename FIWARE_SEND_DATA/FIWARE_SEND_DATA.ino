#include <Time.h>
#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; //DirecciÃ³n Mac para el arduino
IPAddress server(207,249,127,215);  // IP del servidor al cual se hara la conexiÃ³n 


IPAddress ip(192, 168, 0, 103); // IP para nuestro arduino

const int sensorPin = A0;//Pin para el sensor de humedad
String valor = "";

EthernetClient client;

void setup() {
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

   // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.println("connecting...");
}//llave del Setup

void loop() {
  int humedad = analogRead(sensorPin);
  String humedadS = String(humedad);
  //String data = "{\"contextElements\":[{\"type\":\"habitacion\",\"isPattern\":\"false\",\"id\":\"cherubshect\",\"attributes\":[{\"name\":\"humedadSuelo\",\"type\":\"float\",\"value\":\""+humedadS+"\"}]}],\"updateAction\":\"APPEND\"}";
 // String data = "{{\"id\":\"cherubs19\",\"type\":\"cherubs\",\"empresa\":{\"type\":\"Integer\",\"value\":\"123\"},\"fecha\":{\"type\":\"String\",\"value\":\"12:06:2017 10:20\"},\"humedadRelativa\":{\"type\":\"Float\",\"value\":\"888\"},\"humedadSuelo\":{\"type\":\"Float\",\"value\":\"431\"},\"position\":{\"type\":\"Float\",\"value\":\"0,0\"},\"temperatura\":{\"type\":\"Integer\",\"value\":\"777\"}}";


//String data = "{\"contextElements\":[{\"type\":\"cherubs\",\"isPattern\":\"false\",\"id\":\"EntidadTTT\",\"attributes\":[{\"name\":\"Humedad\",\"type\":\"float\",\"value\":\"100.9999\"},{\"name\":\"Velocidad\",\"type\":\"Float\",\"value\":\"12303\"}]}],\"updateAction\":\"APPEND\"}";
//String data = "";
String data = "{\"contextElements\":[{\"type\":\"prueva\",\"isPattern\":\"false\",\"id\":\"cherubs22\",\"attributes\":[{\"name\":\"empresa\",\"type\":\"integer\",\"value\":\"123\"},{\"name\":\"humedadRelativa\",\"type\":\"Float\",\"value\":\""+humedadS+"\"}]}],\"updateAction\":\"APPEND\"}";
String data1 = "{\"contextElements\":[{\"type\":\"prueva\",\"isPattern\":\"false\",\"id\":\"cherubs22\",\"attributes\":[{\"name\":\"position\",\"type\":\"Float\",\"value\":\"0,0\"},{\"name\":\"temperatura\",\"type\":\"Integer\",\"value\":\"10\"}]}],\"updateAction\":\"APPEND\"}";
String data2 = "{\"contextElements\":[{\"type\":\"prueva\",\"isPattern\":\"false\",\"id\":\"cherubs22\",\"attributes\":[{\"name\":\"fecha\",\"type\":\"String\",\"value\":\"12:06:2016 10:35\"},{\"name\":\"humedadSuelo\",\"type\":\"float\",\"value\":\"0101\"}]}],\"updateAction\":\"APPEND\"}";


   Serial.println(data);      // String data = "{\"contextElements\":[{\"type\":\"habitacion\",\"isPattern\":\"false\",\"id\":\"cherubshect\",\"attributes\":[{\"name\":\"humedadSuelo\",\"type\":\"float\",\"value\":\""+humedadS+"\"}]}],\"updateAction\":\"APPEND\"}";
 Serial.println(data1);
 Serial.println(data2);

  
   if (client.connect(server, 1026) > 0) {
    client.println("POST /v1/updateContext HTTP/1.1");
    client.println("Host: 207.249.127.215");
    client.println("Content-Type: application/json");
    client.println("User-Agent: Arduino 1/0");
    client.print("Content-Length: ");
    client.println(data.length());
    client.println();
    client.print(data);
    client.println();
    
    client.println("POST /v1/updateContext HTTP/1.1");
    client.println("Host: 207.249.127.215");
    client.println("Content-Type: application/json");
    client.println("User-Agent: Arduino 1/0");
    client.print("Content-Length: ");
    client.println(data1.length());
    client.println();
    client.print(data1);
    client.println();
    
       client.println("POST /v1/updateContext HTTP/1.1");
    client.println("Host: 207.249.127.215");
    client.println("Content-Type: application/json");
    client.println("User-Agent: Arduino 1/0");
    client.print("Content-Length: ");
    client.println(data2.length());
    client.println();
    client.print(data2);
    client.println();

    Serial.println("ENTIDAD ACTUALIZADA");
   }else
   {
      Serial.println("NO CREADA");
   }

   if (!client.connected()) {
    Serial.println("Disconnected!");
  }
  client.stop();
  client.flush();
  delay(2000); // Espero un minuto antes de tomar otra muestra
}
