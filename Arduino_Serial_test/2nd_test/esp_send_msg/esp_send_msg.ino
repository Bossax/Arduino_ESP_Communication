

void setup() {
  Serial.begin(9600); 
  
}

void loop(){
  if(Serial.availableForWrite()){
    // send string size
    Serial.write(4);
    Serial.write("DATA");
    delay(5000);
  }
    
}
