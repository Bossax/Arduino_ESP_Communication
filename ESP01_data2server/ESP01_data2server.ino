/*
 * ESP01 receives data from Arduino nano via serial input before
 * relaying it to a server
 */
#include <ESP8266WiFi.h>
#define HEADERSIZE 1
#define SEND_SUCC "OK"
#define SEND_FAIL "Fail"
// Server configuration

const uint16_t port = 5050;
const char * host = "192.168.1.121";

const char* ssid = "Suchart";
const char* password = "0850434514";

// Function Prototype
void send2server(int,char*);

WiFiClient client;

void setup() {
  Serial.begin(9600); // enable communication link to Arduino

  // connect to AP
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }
 

}

void loop() { 
  client.connect(host, port);
    while (!client.connected()) {
        delay(1000);
        client.connect(host, port);
    }
    
   while(client.connected()){
    char* text1 = "WAIT";
      send2server(4,text1);
   // Listen from Arduino
     while(!Serial.available()){}
     if(Serial.available()){
      
      char* text = "NOW";
      send2server(3,text);
      // read header
      byte buffer[HEADERSIZE];
      client.readBytes((char*) buffer,HEADERSIZE);
      int len = (int)buffer[HEADERSIZE-1];
      
      // read content
      char* msg = (char*)malloc(len);
      Serial.readBytes(msg,len);

      // send data
      send2server(len,msg);

      char* text2 = "SENT";
      send2server(4,text2);
      /*
      // send serial
      Serial.write(2);
      Serial.print("OK");
      */
      delay(1);
     }
   }
}

void send2server(int header_size,char* data){
  // send header
  client.write(header_size);
        
  // send content
  client.print(data);
   
   return;     
  // receive response
  // read header
//  while(!client.available()){}
//        
//   byte buffer[HEADERSIZE];
//   client.readBytes((char*) buffer,HEADERSIZE);
//    int len = (int)buffer[HEADERSIZE-1];
//    
//  // read response
//  char* msg = (char*)malloc(len);
//  client.readBytes(msg, len);
//
//  if(String(msg) == SEND_SUCC){
//    return true;
//  }else{
//   return false;
//  }
}
