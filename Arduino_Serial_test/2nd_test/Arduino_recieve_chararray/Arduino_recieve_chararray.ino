/*/
 * Test if hardware serial ports of Arduino are working 
 * Test serialization method
 */
#include<SoftwareSerial.h>

SoftwareSerial s(9,10); //rx tx
void setup() {
  pinMode(2,OUTPUT); //green
  pinMode(3,OUTPUT); //red
  Serial.begin(115200); 
  s.begin(9600);
  digitalWrite(2, HIGH); 
    delay(500);
    digitalWrite(2, LOW); 
     delay(500);
     digitalWrite(3, HIGH); 
     delay(500);
     digitalWrite(3, LOW); 
     delay(500);
}

void loop() {
  
  Serial.println("Reading...");
  while(!s.available()){}

  // read string size
  byte len_buffer[1];
  s.readBytes(len_buffer,1);
  int len = int(len_buffer[0]);

  char* txt = (char*) malloc(len +1);
  int x = s.readBytes(txt,len);
  txt[len] = '\0';
  Serial.println( txt);

      if(String(txt) == "DATA"){
       
        Serial.println("green");
        digitalWrite(2, HIGH); 
        delay(1000);
        digitalWrite(2, LOW); 
         delay(1000);
      }else{
        
         Serial.println("red");
         digitalWrite(3, HIGH); 
         delay(1000);
         digitalWrite(3, LOW); 
         delay(1000);
}

}
 
  
