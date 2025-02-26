#!/usr/bin/env python3
# -*- coding: utf-8 -*-

"""
ESP8266UDPClient用 UDP受信スクリプト（統計情報表示版）

このスクリプトは、ESP8266UDPClientライブラリを使用して送信されたUDPパケットを
PC（Windows、Mac、Linux）で受信するためのものです。
IPアドレスごとの受信統計情報と最後に受信したパケットの内容を表示します。

使用方法:
    python3 udp_receiver.py

作成者: necobit
日付: 2025-02-26
"""

import socket
import time
import datetime
from collections import defaultdict

# UDPの設定
UDP_IP = "0.0.0.0"  # すべてのインターフェースでリッスン
UDP_PORT = 8888     # Spresenseからのデータを受信するポート

def main():
    # UDPソケットの作成
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.bind((UDP_IP, UDP_PORT))
    
    print(f"UDP受信待機中... ポート: {UDP_PORT}")
    
    # IPアドレスごとの受信カウンターと最終更新時間
    ip_counters = defaultdict(int)
    last_report_time = time.time()
    
    # 最後に受信したパケットの情報
    last_packets = {}
    
    try:
        while True:
            # ノンブロッキングモードに設定
            sock.setblocking(0)
            
            current_time = time.time()
            elapsed = current_time - last_report_time
            
            # 1秒経過したら統計を表示してカウンターをリセット
            if elapsed >= 1.0:
                # 統計情報の表示
                print(f"\n[{datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')}] 受信統計:")
                
                if not ip_counters:
                    print("  データ受信なし")
                else:
                    for ip, count in ip_counters.items():
                        rate = count / elapsed
                        print(f"  {ip}: {count}パケット ({rate:.2f} パケット/秒)")
                        
                        # 最後に受信したパケットの内容を表示
                        if ip in last_packets:
                            print(f"    最後の受信内容: {last_packets[ip]}")
                
                # カウンターのリセットと時間の更新
                ip_counters.clear()
                last_report_time = current_time
            
            # データの受信（ノンブロッキング）
            try:
                data, addr = sock.recvfrom(1024)  # バッファサイズは1024バイト
                
                # IPアドレスごとのカウンターを更新
                ip_counters[addr[0]] += 1
                
                # 最後に受信したパケットの内容を保存
                try:
                    last_packets[addr[0]] = data.decode('utf-8')
                except UnicodeDecodeError:
                    last_packets[addr[0]] = f"バイナリデータ ({len(data)} バイト)"
                
            except BlockingIOError:
                # データがない場合は少し待つ
                time.sleep(0.001)
            
    except KeyboardInterrupt:
        print("\n終了します")
    finally:
        sock.close()

if __name__ == "__main__":
    main()
