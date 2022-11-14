# tello_UART_porter
EDUじゃないTelloをネット越しに動かしたいときに使えます。ピン配置はATOM liteのものを使っています。

# 動作確認環境
- [tello (EDUじゃないやつでもOK)](https://www.ryzerobotics.com/jp/tello)
- [M5ATOM](https://shop.m5stack.com/products/atom-lite-esp32-development-kit?variant=32259605200986)
- Arduino IDE: 1.8.13
- Arduino-SerialCommands: 2.2.0
- M5Atom: 0.1.0
- telloArduino: [このcommitの内容を使用した](https://github.com/akshayvernekar/telloArduino/commit/3eb7110bc50598820faf4a8a026e74d9f1082e08)

# 環境構築
Arduino　IDEにて事前に下記ライブラリをインストールしてください。

- [Arduino-SerialCommands](https://github.com/ppedro74/Arduino-SerialCommands)　また、ライブラリマネージャーから"SerialCommands"で検索してインストール可能
- [M5Atom](https://docs.m5stack.com/en/quick_start/atom/arduino) こちらの手順に従いインストール
- [telloArduino](https://github.com/akshayvernekar/telloArduino) READMEの手順に従いインストール

# 使い方

1. 本リポジトリをArduinoフォルダへgit cloneする。(zipダウンロードしてtello_UART_porterフォルダを作成&展開するのもOK)
2. tello_UART_porter.ino内の`WiFiEvent`関数を探し、内部の`tello_op_setup(26,32)`を任意のピンへ書き換える。
3. 2で設定したピンと制御するガジェットをUART通信にて結線する。この時、通信するさいのビットレートは*115200bps*となっている。また、tello_opetation.cppの`tello_op_setup`関数内のSerial2のビットレートを変更すると任意の通信速度にすることが可能。
4. M5ATOMへ本コードを書き込む。書き込む方法は環境構築のM5ATOMの項を参考にする。
5. telloの電源を入れる。
6. telloのランプが緑になることを確認する。
7. 結線したガジェットから通信すると任意の制御をすることができる。

# 通信時のプロトコルについて
コマンドは`[半角小文字コマンド名] [数字] [数字]　...[改行コード]`と半角スペースで区切って送る。また、最後は改行コード`char(10)`を送る必要がある。
実行できるコマンド名は[telloArduino](https://github.com/akshayvernekar/telloArduino)と同じ名前を取っているが、文字をすべて小文字にしてアンダーバーを消す必要がある。
また、gettemperatureなどの値を取得するようなコマンドに関しては、コマンド実行後に値を文字列(byte配列)としてUART経由で渡される。

- telloを離陸させる
```telloを離陸させる:shell
takeoff
# 改行
```

- telloを着陸させる
```telloを着陸させる:shell
land
# 改行
```

- telloをヨー軸で時計回りに30度回す
```telloをヨー軸で時計回りに30度回す:shell
rotateclockwise 300
# 改行
```

