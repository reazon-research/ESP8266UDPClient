#ifndef ESP8266_UDP_CLIENT_H
#define ESP8266_UDP_CLIENT_H

#include <Arduino.h>

class ESP8266UDPClient {
public:
    /**
     * コンストラクタ
     * @param serial ESP8266と通信するためのシリアルポート
     */
    ESP8266UDPClient(HardwareSerial &serial);
    
    /**
     * Wi-Fi接続を初期化する
     * @param ssid Wi-FiのSSID
     * @param password Wi-Fiのパスワード
     * @return 接続に成功したらtrue、失敗したらfalse
     */
    bool begin(const char* ssid, const char* password);
    
    /**
     * UDPコネクションを設定する
     * @param host 宛先ホストのIPアドレス
     * @param port 宛先ポート番号
     * @param localPort ローカルポート番号（通常は宛先ポートと同じ）
     * @return 設定に成功したらtrue、失敗したらfalse
     */
    bool beginUDP(const char* host, const char* port, const char* localPort = nullptr);
    
    /**
     * UDPパケットを送信する
     * @param message 送信するメッセージ
     */
    void sendPacket(const String &message);
    
    /**
     * ESP8266からのレスポンスを取得する（通常の待機時間）
     * @param waitTime 待機時間（ミリ秒）
     * @return レスポンス文字列
     */
    String getResponse(int waitTime);
    
    /**
     * ESP8266からのレスポンスを高速に取得する（短い待機時間）
     * @param waitTime 待機時間（マイクロ秒）
     * @return レスポンス文字列
     */
    String getResponseHigh(int waitTime);

private:
    HardwareSerial &_serial;  // ESP8266と通信するためのシリアルポート
};

#endif // ESP8266_UDP_CLIENT_H
