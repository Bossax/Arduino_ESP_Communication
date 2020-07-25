/*
 * Listen for a message from the Arduino and echo back the message
 * Handshaking protocol
 * 1. waiting for contac request from Arduino, then send acknowledge char
 * 2. receiving data from arduino
 * 3. send OK message back to Arduino if the string matches
 */

 // function prototypes
 void contactRequest();
 char*  get_data();
 void buffer_clear();
 void ack_msg(boolean);
 void blink_LED();

void setup() {
  Serial.begin(9600); 
  pinMode(2, OUTPUT); // status LED
  
}

void loop(){
  
  // 1. waiting for contact request
   contactRequest();

  digitalWrite(2,LOW);
  // 2. recieving data
  char* data = get_data();
  digitalWrite(2,HIGH);
  // 3. echo check message
  if(data == "AA"){
    ack_msg(true);
  }else{
    ack_msg(false);
  }
}

void contactRequest(){boolean contact_est = false;
  while(!contact_est){
    blink_LED();
    if(Serial.available()){
      int request = Serial.read();
      delay(5);
      if(request == 5){
        buffer_clear(); // clear recieve buffer
        contact_est = true;
        Serial.write(6);  // acknowledge
        digitalWrite(2,LOW);
        return;
      }
   }
  }
}

char* get_data(){char* str;  int len;
    blink_LED();
    while(!Serial.available()){}
    byte len_buffer[1];
    Serial.readBytes(len_buffer,1);
    len = int(len_buffer[0]);

    str = (char*) malloc(len +1);
    int x = Serial.readBytes(str,len);
    str[len] = '\0';
    return str;
}

void ack_msg(boolean echo){
  if(echo){
    Serial.write(2);
    Serial.write("OK");
  }else{
    Serial.write(2);
    Serial.write("XX");
  }
  return;
  
}


void blink_LED(){
  digitalWrite(2,HIGH);
  delay(100);
  digitalWrite(2,LOW);
}

void buffer_clear(){
  while(Serial.available()){
    Serial.read();
  }
}

  
