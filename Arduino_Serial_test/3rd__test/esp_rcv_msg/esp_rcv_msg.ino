/*
 * Listen for a message from the Arduino and echo back the message
 */

void setup() {
  Serial.begin(9600); 
}

void loop(){char* data;  int len;
  while(true){ 
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
   
  }
   
    // echo
  while(!Serial.availableForWrite()){}
  Serial.write(len);
  Serial.write(data);
  delay(1000);
}
