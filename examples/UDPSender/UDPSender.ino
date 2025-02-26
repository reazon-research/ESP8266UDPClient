/*
 * ESP8266UDPClient ライブラリのサンプルスケッチ
 * 
 * このサンプルは、ESP8266 Wi-FiモジュールをWi-Fiモジュールとして使用してUDPパケットを送信する方法を示しています。
 * Spresenseボードで動作確認していますが、他のArduino互換ボードでも使用可能です。
 * 
 * 使用方法:
 * 1. ESP8266モジュールをシリアルポートに接続します（Spresenseの場合はSerial2を使用）
 * 2. Wi-FiのSSID、パスワード、宛先IPアドレス、ポート番号を設定します
 * 3. スケッチをアップロードして実行します
 * 
 * 作成者: necobit
 * 日付: 2025-02-26
 */

#include <ESP8266UDPClient.h>

// Wi-Fi設定
#define SSID "your_wifi_ssid"        // Wi-Fi SSID
#define PASS "your_wifi_password"    // Wi-Fi パスワード
#define UDP_HOST "192.168.1.100"     // 宛先IPアドレス（受信側PCのIPアドレス）
#define UDP_PORT "8888"              // UDPポート番号
#define INTERVAL 1000                // データ送信間隔(msec)

unsigned long lastSendTime = 0;      // 前回の送信時刻
unsigned long count = 0;             // カウンター

// ESP8266UDPClientのインスタンスを作成
ESP8266UDPClient udpClient(Serial2);

void setup()
{
  // シリアルデバッグコンソール
  Serial.begin(115200);
  while (!Serial)
  {
    delay(1);
  };

  // ESP8266との通信用シリアル
  // 注意: ESP8266の標準ボーレートは115200bpsです
  // 高速通信を行う場合は、以下の2行のコメントを外して実行後、
  // Serial2.begin(2000000)の行を有効にしてください
  
  // Serial2.begin(115200);
  // Serial2.println("AT+UART_DEF=2000000,8,1,0,0");
  
  Serial2.begin(115200);  // ESP8266の標準ボーレート
  //Serial2.begin(2000000);
  while (!Serial2)
  {
    delay(1);
  };

  Serial.println(F("ESP8266 UDP Sender Example"));

  // Wi-Fi接続
  if (!udpClient.begin(SSID, PASS))
  {
    Serial.println("Wi-Fi接続に失敗しました");
    while (1)
    {
      delay(1);
    };
  }

  // UDPコネクションの設定
  if (!udpClient.beginUDP(UDP_HOST, UDP_PORT))
  {
    Serial.println("UDPコネクション設定に失敗しました");
    while (1)
    {
      delay(1);
    };
  }

  lastSendTime = millis();
}

void loop()
{
  unsigned long currentTime = millis();

  // 指定間隔ごとにデータを送信
  if (currentTime - lastSendTime >= INTERVAL)
  {
    // メッセージの準備
    String message = "Count = " + String(count) + ", Time = " + String(currentTime);

    // UDPパケットの送信
    udpClient.sendPacket(message);
    
    // デバッグ表示
    Serial.println("送信: " + message);

    count++;
    lastSendTime = currentTime;
  }
}
