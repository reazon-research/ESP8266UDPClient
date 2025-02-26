# ESP8266UDPClient

- ESP8266 Wi-Fi モジュールを AT コマンドで制御し、UDP 通信を行うための Arduino ライブラリです。
- Spresense などのマイコンボードで使用できます。
- テスト環境:Spresense+ThousanDIY SPRESENSE 用 Wi-Fi add-on ボード https://www.switch-science.com/products/4042

## 機能

- ESP8266 モジュールを使った Wi-Fi 接続
- UDP パケットの送信
- シンプルな API

## インストール方法

### Arduino IDE の場合

1. このリポジトリを ZIP ファイルとしてダウンロード
2. Arduino IDE を開き、「スケッチ」→「ライブラリをインクルード」→「.ZIP 形式のライブラリをインストール...」を選択
3. ダウンロードした ZIP ファイルを選択

### PlatformIO の場合

1. プロジェクトの lib/フォルダにこのリポジトリをクローン
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

## PC 側での受信方法

- PC のローカル IP アドレスを調べて Arduino スケッチのアドレスを書き換えます。
- ターミナルで自分のローカル IP を調べるコマンド例：echo "$(ipconfig getifaddr en0) $(ipconfig getifaddr en1)"
- このリポジトリには、PC（Windows、Mac、Linux など）で UDP パケットを受信するための Python スクリプトも含まれています。

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

### Spresense の場合

ESP8266 モジュールを Spresense の Serial2 ポートに接続します。

- ESP8266 RX → Spresense TX2 (D01)
- ESP8266 TX → Spresense RX2 (D02)
- ESP8266 VCC → 3.3V
- ESP8266 GND → GND
- ESP8266 CH_PD → 3.3V

## 注意事項

- ESP8266 モジュールの標準ボーレートは 115200bps です。高速通信を行う場合は、サンプルコードのコメントを参照してください。
- Wi-Fi 接続や UDP 通信に問題がある場合は、SSID やパスワード、IP アドレス、ポート番号が正しいか確認してください。
- ファイアウォールが UDP 通信をブロックしていないか確認してください。

## ライセンス

MIT

## 作者

necobit
