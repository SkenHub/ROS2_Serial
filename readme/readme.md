# シリアル通信[PC<->Arduino UNO R4]

serial.py

```py

import serial

data = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,]

ser = serial.Serial("/dev/ttyACM0", baudrate=9600)

while True:
    ser.write(bytes(data))  
    received_data = ser.read(16)
    
    for a in range(16):
        data[a] = received_data[a]

    print(data)
```
`import serial`: Pythonのserialモジュールをインポート

`data = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]`: 16個の要素を持つリストdataを作成  64まで確認済み

`ser = serial.Serial("/dev/ttyACM0", baudrate=9600)`: シリアルポートを開く.Arduinoが接続されているポート（"/dev/ttyACM0"）と通信速度（baudrate=9600）

`ser.write(bytes(data))`: dataリストをバイトに変換してArduinoに送信.ser.writeメソッドを使用してデータをシリアルポートへ

`received_data = ser.read(16)`: Arduinoからのデータを16バイト読み取り.

`for a in range(16): data[a] = received_data[a]`: 受信したデータを元のdataリストにコピー次のループで同じデータを送信することが可能

ros2-serial.ino
```c
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

  delay(100);  // Pythonがデータを受信するのを待つために小さな遅延を追加

  if (Serial.available() >= 8) {
    Serial.readBytes(receive_data, 8);

    if (receive_data[0] >= 2 && receive_data[0] <= 8) {
      digitalWrite(LED_BUILTIN, HIGH);
    } else {
      digitalWrite(LED_BUILTIN, LOW);
    }
  }
}

```
64まで確認済み
UNO R4 minimaであればdelayなしで通信可能でした．
