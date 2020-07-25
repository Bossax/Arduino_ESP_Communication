/*
 * Listen for a message from the Arduino and echo back the message
 */

void setup() {
  Serial.begin(9600); 
  pinMode(2, OUTPUT);

  digitalWrite(2, HIGH);   
  delay(500);
  digitalWrite(2, LOW); 
  delay(500);  
  
}

void loop(){char* data;  int len;
  while(true){
    digitalWrite(2, HIGH);  
    if(Serial.available()){
      byte len_buffer[1];
      Serial.readBytes(len_buffer,1);
       len = int(len_buffer[0]);

      data = (char*) malloc(len +1);
      int x = Serial.readBytes(data,len);
      data[len] = '\0';
      break;
    }
    delay(50);
    digitalWrite(2, LOW);
    delay(200);
  }
   digitalWrite(2, LOW); 
    // echo
  while(!Serial.availableForWrite()){}
  Serial.write(len);
  Serial.write(data);
  delay(1000);
}
