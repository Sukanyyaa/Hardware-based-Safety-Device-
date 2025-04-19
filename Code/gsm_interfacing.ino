#include <SoftwareSerial.h>

SoftwareSerial Gsm(7, 8); // TX, RX
char phone_no[] = "+919302942991";  
int buttonPin = 4; 

void setup() {
  Serial.begin(9600);
  Gsm.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP); 

  delay(1000);
  Serial.println("Initializing GSM Module...");
  initializeGSM();
}

void loop() {
  if (digitalRead(buttonPin) == LOW) {
    Serial.println("Button Pressed! Sending Alert...");
    sendSMS(phone_no, "ALERT! I NEED HELP IMMEDIATELY.");
    delay(10000); // Prevent multiple rapid SMS sends
  }
}

void initializeGSM() {
  Gsm.println("AT");
  delay(1000);
  Gsm.println("AT+CMGF=1");
  delay(1000);
  Gsm.println("AT+CNMI=1,2,0,0,0"); 
  delay(1000);
}

void sendSMS(const char* number, const char* message) {
  Gsm.print("AT+CMGS=\"");
  Gsm.print(number);
  Gsm.println("\"");
  delay(500);
  Gsm.print(message);
  delay(500);
  Gsm.write(26);  // ASCII code for CTRL+Z (end of message)
  delay(5000);
  Serial.println("SMS Sent Successfully!");
}
