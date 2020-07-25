/*
 * Test serial communication with Arduino
 * Echo back what is received from Arduino
 */

#define float_rand(X) (float)(random(X)/(X+0.5))


float dummy_data = 8.832;
    
void setup()
{
  Serial.begin(9600); // link to arduino
 
}

void loop() {
    
        Serial.println(dummy_data);
        
        delay(1000);
        dummy_data += float_rand(4);
   
    
}
