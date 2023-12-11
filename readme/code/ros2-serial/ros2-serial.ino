#include <SoftwareSerial.h>

uint8_t send_data[16];
uint8_t receive_data[8];

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  for (int a = 0; a < 16; a++) send_data[a] = a;
  Serial.write(send_data, 16);

  //delay(100);  

  if (Serial.available() >= 8) {
    Serial.readBytes(receive_data, 8);

    if (receive_data[0] >= 2 && receive_data[0] <= 8) {
      digitalWrite(LED_BUILTIN, HIGH);
    } else {
      digitalWrite(LED_BUILTIN, LOW);
    }
  }
}
