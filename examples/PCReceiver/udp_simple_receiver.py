#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
ESP8266UDPClient用 UDP受信スクリプト

このスクリプトは、ESP8266UDPClientライブラリを使用して送信されたUDPパケットを
PC（Windows、Mac、Linux）で受信するためのものです。
受信したパケットの内容と1秒あたりの受信レートを表示します。

使用方法:
    python3 udp_simple_receiver.py

作成者: necobit
日付: 2025-02-26
"""

import socket
import datetime
import time

# UDPの設定
UDP_IP = "0.0.0.0"  # すべてのインターフェースでリッスン
UDP_PORT = 8888     # Spresenseからのデータを受信するポート

def main():
    # UDPソケットの作成
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.bind((UDP_IP, UDP_PORT))
    
    print(f"UDP受信待機中... ポート: {UDP_PORT}")
    print(f"受信したパケットをそのまま表示します。終了するには Ctrl+C を押してください。")
    
    # 受信カウンターと時間計測用の変数
    packet_count = 0
    last_count_time = time.time()
    packets_per_second = 0
    
    try:
        while True:
            # データの受信
            data, addr = sock.recvfrom(1024)  # バッファサイズは1024バイト
            
            # 受信カウンターをインクリメント
            packet_count += 1
            
            # 現在時刻の取得
            current_time = time.time()
            elapsed = current_time - last_count_time
            
            # 1秒経過したら受信レートを計算
            if elapsed >= 1.0:
                packets_per_second = packet_count / elapsed
                packet_count = 0
                last_count_time = current_time
            
            # 時刻のフォーマット
            time_str = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S.%f")[:-3]
            
            # 受信データのデコード
            try:
                message = data.decode('utf-8')
                # 表示（先頭に受信レートを追加）
                print(f"[{packets_per_second:.1f}パケット/秒] [{time_str}] {addr[0]}:{addr[1]} から受信: {message}")
            except UnicodeDecodeError:
                # バイナリデータの場合
                print(f"[{packets_per_second:.1f}パケット/秒] [{time_str}] {addr[0]}:{addr[1]} からバイナリデータを受信: {len(data)}バイト")
                print(f"HEX: {data.hex()}")
            
    except KeyboardInterrupt:
        print("\n終了します")
    finally:
        sock.close()

if __name__ == "__main__":
    main()
