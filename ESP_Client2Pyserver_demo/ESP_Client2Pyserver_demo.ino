/*
 * Demonstrate how ESP01 can connect to a server run on a PC in Python script
 * and send literal strings and numeric string (float) to the server
 * 
 * This is to be improved by using Arduino nano or Pro mini as a "brain" and
 * reduce the functionality of the ESP01 to just only serial communication link
 */


#include <ESP8266WiFi.h>

#define HEADERSIZE 1
#define GET (char*)"GET"
#define INQ (char*)"INQ" 
#define DIS (char*)"DIS!"
#define float_rand(X) (float)(random(X)/(X+0.5))

const uint16_t port = 5050;
const char * host = "192.168.1.121";

const char* ssid = "Suchart";
const char* password = "0850434514";

float dummy_data = 8.832;

// Function prototype
void send2server(char*);
void sendNum2server(float);
void send_float(float,int);
float findMod(float, float);

// client class
static WiFiClient client;
    
void setup()
{
  Serial.begin(115200); // monitor serial
  


  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");

 
}

void loop() {
     // Connect to the server
    client.connect(host, port);
    while (!client.connected()) {
        Serial.println("Connection to host failed");
        delay(1000);
        client.connect(host, port);
    }
 
    Serial.println("Connected to server successful!");

    // while connected to server, send data at every speific interval
    send2server("Hello");
    while(client.connected()){
        sendNum2server(dummy_data);
        delay(1000);
        dummy_data += float_rand(4);
    }
    
}

void send2server(char* data){

  // send header
  int header_size = (int)(sizeof(data))+1;
  Serial.print("Header:");
  Serial.println(header_size);
  client.write(header_size);
        
  // send content
  client.print(data);
  Serial.print("Sent: ");
  Serial.println(data);
        
  // receive response
  // read header
  while(!client.available()){}
        
        byte buffer[HEADERSIZE];
        client.readBytes((char*) buffer,HEADERSIZE);
        int len = (int)buffer[HEADERSIZE-1];
        Serial.println(sizeof(len));
        
        // read content
        char* msg = (char*)malloc(len);
        client.readBytes(msg, len);
        Serial.println(msg);
        free(msg);
}


void sendNum2server(float data){
  // convert float to characters and send the content
  send_float(data,2);  // 2 decimal places
        
  // receive response
  // read header
  while(!client.available()){}
        
        byte buffer[HEADERSIZE];
        client.readBytes((char*) buffer,HEADERSIZE);
        int len = (int)buffer[HEADERSIZE-1];
        Serial.println(len);
        
        // read content
        char* msg = (char*)malloc(len);
        client.readBytes(msg, len);
        Serial.println(msg);
        free(msg);
}


void send_float(float f,int precision){char* string_handle = (char*)calloc(20,sizeof(char)); int headersize;
  // integer
  // find order of the integer
  float divider = 10;
  int bfd = 1;
  while(true){
    if (((int)(f/divider) == 0) && (findMod(f, divider) == f)){
      break;
    }
    divider = divider*10;
    bfd +=1 ;
  }
  headersize = bfd;
  // extracting digit
  divider = 10;
  for(int i = 1; i<bfd-1;i++){
    divider = divider*10;
  }

  int buffer_num;
  int l;
  for(int i = 0; i<=bfd-1;i++){
  
    buffer_num = (int)(f/divider);
    string_handle[i] = (char)(buffer_num + '0');
    
    f = f-buffer_num*divider;
    divider = divider/10;

    l = i;
  }

  l += 1;
  string_handle[l] = '.'; // concat .
  
  // decimal
  for(int k = l+1; k <=precision+l; k++){
    buffer_num = (int)(f/divider);
    string_handle[k] = (char)(buffer_num + '0');
  
    f = f-(float)buffer_num*divider;
    divider = divider/10;
  }
  /************************************************************/
  // send header size
  headersize = bfd+precision +1;
  client.write(headersize);
  Serial.println(headersize);
  
   // send content
  client.print(string_handle);
  Serial.print("Sent ");
  Serial.println(string_handle);

  return;
}

float findMod(float a, float b)
{
    float mod;
    // Handling negative values
    if (a < 0){
        mod = -a;
    }else{
        mod =  a;
    }
    if (b < 0){
        b = -b;
    }
    // Finding mod by repeated subtraction

    while (mod >= b){
        mod = mod - b;
    }
    // Sign of result typically depends
    // on sign of a.
    if (a < 0){
        return -mod;
    }
    return mod;
}
