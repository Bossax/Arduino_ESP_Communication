#include <SoftwareSerial.h>

#define HEADERSIZE 1
#define SEND_SUCC "OK"
#define SEND_FAIL "Fail"
#define PRECISION 1


const byte rxPin = 9;
const byte txPin = 10;

int GREEN_LED = 12;
int sensorPin = A0;    // select the input pin for the Soil moisture sensor
float sensorValue = 0;  // variable to store the value coming from the sensor


void sendNum2ESP(float);
void send_float2ESP(float,int);
float findMod(float, float);

SoftwareSerial s (rxPin,txPin);

void setup() {
  Serial.begin(115200); 
  s.begin(9600); 
  pinMode(GREEN_LED, OUTPUT);
  digitalWrite(GREEN_LED, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(6000);                       // wait for a second
  digitalWrite(GREEN_LED, LOW);    // turn the LED off by making the voltage LOW
  delay(4000);
}

void loop() {
    // read data
//    sensorValue = (float)analogRead(sensorPin); 
//    send_float2ESP(sensorValue,PRECISION);
//    String s1 = "PD";
    // send data to ESP01 and to server
    Serial.write(2);
    Serial.print("OK");

    s.write(2);
    s.print("OK");

    // Check message
    /*
     while(!Serial.available()){}
     char* msg = (char*)malloc(2);;
     Serial.readBytes(msg,2);
     if(msg == SEND_SUCC){
      
        digitalWrite(GREEN_LED, HIGH);   // turn the LED on (HIGH is the voltage level)
        delay(500);                       // wait for a second
        digitalWrite(GREEN_LED, LOW);    // turn the LED off by making the voltage LOW
     }else{
        digitalWrite(GREEN_LED, HIGH);   // turn the LED on (HIGH is the voltage level)
        delay(100);                       // wait for a second
        digitalWrite(GREEN_LED, LOW);    // turn the LED off by making the voltage LOW
        delay(100);
        digitalWrite(GREEN_LED, HIGH);   // turn the LED on (HIGH is the voltage level)
        delay(100);                       // wait for a second
        digitalWrite(GREEN_LED, LOW);    // turn the LED off by making the voltage LOW
        delay(100);
        digitalWrite(GREEN_LED, HIGH);   // turn the LED on (HIGH is the voltage level)
        delay(100);                       // wait for a second
        digitalWrite(GREEN_LED, LOW);    // turn the LED off by making the voltage LOW
        delay(100);
      }
      */
       delay(800); 
        
    
}


void send_float2ESP(float f,int precision){char* string_handle = (char*)calloc(20,sizeof(char)); int headersize;
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
  Serial.write(headersize);
  
   // send content
  Serial.print(string_handle);

  for(int o = 1;o <40; o++){
  digitalWrite(GREEN_LED, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);                       // wait for a second
  digitalWrite(GREEN_LED, LOW);    // turn the LED off by making the voltage LOW
  delay(100);
  }
  digitalWrite(GREEN_LED, LOW);    // turn the LED off by making the voltage LOW
  delay(5000);
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
