#include "ESP8266UDPClient.h"

ESP8266UDPClient::ESP8266UDPClient(HardwareSerial &serial) : _serial(serial)
{
    // コンストラクタでは何もしない
}

bool ESP8266UDPClient::begin(const char *ssid, const char *password)
{
    Serial.println("Wi-Fi接続を開始します...");

    // モジュールのリセット
    _serial.println("AT+RST");
    getResponse(1000);

    // Wi-Fiモードを設定（1: Stationモード）
    _serial.println("AT+CWMODE=1");
    getResponse(500);

    // Wi-Fiに接続
    String cmd = "AT+CWJAP=\"";
    cmd += ssid;
    cmd += "\",\"";
    cmd += password;
    cmd += "\"";
    _serial.println(cmd);
    getResponse(10000);

    // IPアドレスの確認
    _serial.println("AT+CIFSR");
    getResponse(500);

    return true;
}

bool ESP8266UDPClient::beginUDP(const char *host, const char *port, const char *localPort)
{
    Serial.println("UDPコネクション設定中...");

    // UDPコネクションの設定
    String udpSetup = "AT+CIPSTART=\"UDP\",\"";
    udpSetup += host;
    udpSetup += "\",";
    udpSetup += port;
    udpSetup += ",";

    // ローカルポートが指定されていない場合は宛先ポートを使用
    if (localPort == nullptr)
    {
        udpSetup += port;
    }
    else
    {
        udpSetup += localPort;
    }

    udpSetup += ",0"; // 0: 接続を維持する

    _serial.println(udpSetup);
    getResponse(1000);

    return true;
}

void ESP8266UDPClient::sendPacket(const String &message)
{
    // メッセージの長さを取得
    int messageLength = message.length();

    // AT+CIPSENDコマンドの送信
    _serial.print("AT+CIPSEND=");
    _serial.println(messageLength);
    getResponseHigh(1);

    // メッセージの送信
    _serial.print(message);
    getResponseHigh(1);

    // Serial.println("送信: " + message); // デバッグ用
}

String ESP8266UDPClient::getResponse(int waitTime)
{
    int i;
    String response = "";
    for (i = 0; i < waitTime; i++)
    {
        if (_serial.available())
        {
            char c = _serial.read();
            response += c;
            Serial.write(c);
        }
        delay(1);
    }
    Serial.println(response); // デバッグ用
    return response;
}

String ESP8266UDPClient::getResponseHigh(int waitTime)
{
    int i;
    String response = "";
    for (i = 0; i < waitTime; i++)
    {
        if (_serial.available())
        {
            char c = _serial.read();
            response += c;
        }
        delayMicroseconds(1500);
    }
    // Serial.println(response); // デバッグ用
    return response;
}
