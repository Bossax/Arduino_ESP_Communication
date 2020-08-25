/*/
 * Send a message to esp01 and listen for its echo
 */
#include<SoftwareSerial.h>

size_t my_strlen(const char);
void ESPFlush();

SoftwareSerial s(9,10); //rx tx
void setup() {
  pinMode(2,OUTPUT);
  Serial.begin(115200); 
  s.begin(9600); // link to esp01
  Serial.println("Wait for esp to boot...");
  while(!s.available()){}
  ESPFlush();
  Serial.println("Ready...");
}

void loop() {
  
  if(!s.availableForWrite()){
     Serial.println("Sending...");
   // send string size
    char *text = "AA";
    s.write((int) my_strlen(text));
    s.write(text);
   Serial.println(text);

  Serial.println("Recieving...");
  while(!s.available()){}
   //recieve echo
   // read string size
   byte len_buffer[1];
   s.readBytes(len_buffer,1);
   int len = int(len_buffer[0]);

   char* txt = (char*) malloc(len +1);
   int x = s.readBytes(txt,len);
   txt[len] = '\0';
  
   Serial.println(txt);
   
  // debugging LED status
   if((String) txt == (String) text){
    digitalWrite(2,HIGH);
    delay(1000);
    digitalWrite(2,LOW);
   }else{
    digitalWrite(2,HIGH);
    delay(200);
    digitalWrite(2,LOW);
    delay(200);
    digitalWrite(2,HIGH);
    delay(200);
    digitalWrite(2,LOW);
    delay(200);
    digitalWrite(2,HIGH);
    delay(200);
    digitalWrite(2,LOW);
   }
    delay(3000);
  }
}

void ESPFlush(){String boot_msg;
  s.setTimeout(100);
  while(s.available()) {
    boot_msg = s.readString();
  }
  Serial.println(boot_msg);
}    
  
size_t my_strlen(const char *str)
{
  size_t i;

  for (i = 0; str[i]; i++);
  return i;
}
  
