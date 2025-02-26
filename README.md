# ESP8266UDPClient

ESP8266 Wi-FiモジュールをATコマンドで制御し、UDP通信を行うためのArduinoライブラリです。

Spresenseなどのマイコンボードで使用できます。

テスト環境:Spresense+ThousanDIY SPRESENSE用Wi-Fi add-onボード https://www.switch-science.com/products/4042

## 機能

- ESP8266モジュールを使ったWi-Fi接続
- UDPパケットの送信
- シンプルなAPI

## インストール方法

### Arduino IDEの場合

1. このリポジトリをZIPファイルとしてダウンロード
2. Arduino IDEを開き、「スケッチ」→「ライブラリをインクルード」→「.ZIP形式のライブラリをインストール...」を選択
3. ダウンロードしたZIPファイルを選択

### PlatformIOの場合

1. プロジェクトのlib/フォルダにこのリポジトリをクローン
2. `#include <ESP8266UDPClient.h>`でインクルード

## 使い方

### 基本的な使い方

```cpp
#include <ESP8266UDPClient.h>

// ESP8266UDPClientのインスタンスを作成（Serial2を使用）
ESP8266UDPClient udpClient(Serial2);

void setup() {
  // シリアル通信の初期化
  Serial.begin(115200);
  Serial2.begin(115200);  // ESP8266との通信速度
  
  // Wi-Fi接続
  udpClient.begin("your_wifi_ssid", "your_wifi_password");
  
  // UDPコネクションの設定
  udpClient.beginUDP("192.168.1.100", "8888");
}

void loop() {
  // UDPパケットの送信
  String message = "Hello, UDP!";
  udpClient.sendPacket(message);
  
  delay(1000);  // 1秒待機
}
```

### 詳細な使い方

詳細な使い方については、[examples/UDPSender/UDPSender.ino](examples/UDPSender/UDPSender.ino)を参照してください。

## PC側での受信方法

このリポジトリには、PC（Windows、Mac、Linuxなど）でUDPパケットを受信するためのPythonスクリプトも含まれています。

### シンプル表示版

```bash
cd examples/PCReceiver
python3 udp_simple_receiver.py
```

### 統計情報表示版

```bash
cd examples/PCReceiver
python3 udp_receiver.py
```

## ハードウェア接続

### Spresenseの場合

ESP8266モジュールをSpresenseのSerial2ポートに接続します。

- ESP8266 RX → Spresense TX2 (D01)
- ESP8266 TX → Spresense RX2 (D02)
- ESP8266 VCC → 3.3V
- ESP8266 GND → GND
- ESP8266 CH_PD → 3.3V

## 注意事項

- ESP8266モジュールの標準ボーレートは115200bpsです。高速通信を行う場合は、サンプルコードのコメントを参照してください。
- Wi-Fi接続やUDP通信に問題がある場合は、SSIDやパスワード、IPアドレス、ポート番号が正しいか確認してください。
- ファイアウォールがUDP通信をブロックしていないか確認してください。

## ライセンス

MIT

## 作者

necobit
