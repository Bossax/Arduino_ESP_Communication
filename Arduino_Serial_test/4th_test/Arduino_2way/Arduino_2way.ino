/*/
 * Send a message to esp01 and listen for its echo
 * Handshaking protocol
 * 1. Arduino establishes contact
 * 2. Arduino sends data if an OK signal is recieved
 * 3. Arduino checks if data reaches the terminal
 * 
 * Arduino must be powered up before ESP01 !!
 */
#include<SoftwareSerial.h>

size_t my_strlen(const char);

// fucntion prototypes
boolean establishContact();
boolean tx_data(char*);
void ESPFlush();
size_t my_strlen(const char*);


SoftwareSerial s(9, 10); //rx tx

void setup() {
    pinMode(2, OUTPUT);    // status LED 
    Serial.begin(115200); // link to esp01
    s.begin(9600);
    Serial.println("Wait for ESP 01 to power up");
    while(!s.available()){}
    ESPFlush();  // clear debug msg of ESP 01 from
}

void loop() {

    // 0. prepare data to send by retriving it from a sensor, convert to ASCII characters
    char* data;
    data = "AA";

    // 1. establish connection
    boolean connect_ok = false;
    Serial.println("Establishing connection...");
    while (!connect_ok) {
        digitalWrite(2, HIGH);
        connect_ok = establishContact();
        digitalWrite(2, LOW);
        delay(50);
        Serial.print("...");

    }
    Serial.println("Ready to send!");

    // 2. transmit data
    boolean tx_ok = tx_data(data);
    if (tx_ok) {
        digitalWrite(2, HIGH);
        delay(300);
        digitalWrite(2, LOW);
        Serial.println("TX Successful");

    }
    else {
        digitalWrite(2, HIGH);
        delay(100);
        digitalWrite(2, LOW);
        delay(100);
        digitalWrite(2, HIGH);
        delay(100);
        digitalWrite(2, LOW);
        Serial.println("TX Unsuccessful");
    }

    delay(4000);

}

/*
 * ///////////// establishContact ///////////////////////
 * Desciption: send a byte with a specific code to esp01 and wait for a response
 * Input: None
 * Output: boolean if the contact is established
 */
boolean establishContact() {
    s.write(5);   // enquiry character
    delay(100);
    if (s.available() > 0) {
        int rsp = s.read();
        delay(5);
        Serial.print("Return from ESP: ");
        Serial.println(rsp);
        if (rsp == 6) {   // acknowledge character
            return true;
        }
    }
    return false;
}

/*
 * ///////////// tx_data ///////////////////////
 * Desciption: transmit data and wait for response. Pre-set timeout = 100 msec
 * Input: char array pointer
 * Output: boolean if the tx is successful
 */
boolean tx_data(char* str) {
    // send data
    //while (s.availableForWrite() <=0 ) {}
    Serial.print("Sending..."); Serial.print((int)my_strlen(str)); Serial.println(str);
    s.write((int)my_strlen(str));
    s.write(str);

    //recieve echo  
    Serial.println("Recieving...");
    while (!s.available()) {}

    // read string size+
    byte len_buffer[1];
    s.readBytes(len_buffer, 1);
    int len = int(len_buffer[0]);

    // read message
    char* txt = (char*)malloc(len + 1);
    int x = s.readBytes(txt, len);
    txt[len] = '\0';                   // terminate string my NULL char
    Serial.println(txt);
    if ((String)txt == "OK") {
        return true;
    }
    else {
        return false;
    }
}

/*
 * Clear serial receive buffer 
 */
void ESPFlush(){String boot_msg;
  s.setTimeout(100);
  while(s.available()) {
    boot_msg = s.readString();
  }
  Serial.println(boot_msg);
}    
/*
 * ///////////// my_strlen ///////////////////////
 * Desciption: return the length of the char array
 * Input: char array pointer
 * Output: size_t length of the array
 */
size_t my_strlen(const char* str)
{
    size_t i;

    for (i = 0; str[i]; i++);
    return i;
}
