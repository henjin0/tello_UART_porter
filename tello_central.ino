#include "tello_operation.h"

// WiFi network name and password:
const char * networkName = "TELLO-xxxxxxxx";//Replace with your Tello SSID
const char * networkPswd = "";

//Are we currently connected?
boolean connected = false;
Tello tello;

void setup() 
{
  Serial.begin(115200); 
  //Connect to the WiFi network
  connectToWiFi(networkName, networkPswd);

}

void loop() 
{
  // put your main code here, to run repeatedly:
  if(connected)
  {
    serial_commands_2_.ReadSerial();
  }
}



/**
 * wifiに接続する処理
 */
void connectToWiFi(const char * ssid, const char * pwd) 
{
  Serial.println("Connecting to WiFi network: " + String(ssid));

  // delete old config
  WiFi.disconnect(true);
  //register event handler
  WiFi.onEvent(WiFiEvent);

  //Initiate connection
  WiFi.begin(ssid, pwd);

  Serial.println("Waiting for WIFI connection...");
}

/**
 * Wifi接続時に関する各種イベントを受け取るハンドラ
 */
//wifi event handler
void WiFiEvent(WiFiEvent_t event) 
{
  switch (event) 
  {
    case SYSTEM_EVENT_STA_GOT_IP:
      //When connected set
      Serial.print("WiFi connected! IP address: ");
      Serial.println(WiFi.localIP());
      //initialise Tello after we are connected
      tello.init();
      tello_op_setup(19,22);
      connected = true;
      break;
      
    case SYSTEM_EVENT_STA_DISCONNECTED:
      Serial.println("WiFi lost connection");
      connected = false;
      break;
  }
}
