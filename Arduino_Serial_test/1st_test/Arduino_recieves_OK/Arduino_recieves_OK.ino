/*/
 * Test if hardware serial ports of Arduino are working 
 * alternating 'O' and 'K'
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
  char txt;
  Serial.println("Reading...");
  while(!s.available()){}
  txt = s.read();
  Serial.println(sizeof(txt));
  if(txt == 'K'){
    Serial.println(txt);
    Serial.println("green");
    digitalWrite(2, HIGH); 
    delay(1000);
    digitalWrite(2, LOW); 
     delay(1000);
  }
  else if(txt == 0){
    Serial.println("Null");
  } 
  else{
  
    Serial.println(txt);
     Serial.println("red");
     digitalWrite(3, HIGH); 
     delay(1000);
     digitalWrite(3, LOW); 
     delay(1000);
  }
 
  
}
