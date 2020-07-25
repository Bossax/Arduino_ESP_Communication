/*/
 * Send a message to esp01 and listen for its echo
 */
#include<SoftwareSerial.h>

size_t my_strlen(const char);

SoftwareSerial s(9,10); //rx tx
void setup() {
  pinMode(2,OUTPUT);

  Serial.begin(115200); // link to esp01
  s.begin(9600);
}

void loop() {
  
  if(!s.availableForWrite()){
     Serial.println("Sending...");
     digitalWrite(2,HIGH);
     delay(200);
     digitalWrite(2,LOW);
     
   // send string size
    char *text = "Boris";
    s.write((int) my_strlen(text));
    s.write(text);
    
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
   
    delay(5000);
  }
}


size_t my_strlen(const char *str)
{
  size_t i;

  for (i = 0; str[i]; i++);
  return i;
}
  
