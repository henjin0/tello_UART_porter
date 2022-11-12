#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include "HardwareSerial.h"
#include "tello_operation.h"

char serial_commands_2_buffer_[32];
SerialCommands serial_commands_2_(&Serial2, serial_commands_2_buffer_, sizeof(serial_commands_2_buffer_));

void cmd_takeoff(SerialCommands* sender)
{
  tello.takeoff();
}
void cmd_land(SerialCommands* sender)
{
  sender->GetSerial()->print(tello.land());
}

void cmd_startVideoStream(SerialCommands* sender)
{
  sender->GetSerial()->print(tello.startVideoStream());
}

void cmd_stopVideoStream(SerialCommands* sender)
{
  sender->GetSerial()->print(tello.stopVideoStream());
}

void cmd_turnOff(SerialCommands* sender)
{
  sender->GetSerial()->print(tello.turnOff());
}

void cmd_up(SerialCommands* sender)
{
  char* value_str = sender->Next();
  const int value = atoi(value_str);
  sender->GetSerial()->print(tello.up(value));
}

void cmd_down(SerialCommands* sender)
{
  char* value_str = sender->Next();
  const int value = atoi(value_str);
  sender->GetSerial()->print(tello.down(value));
}

void cmd_left(SerialCommands* sender)
{
  char* value_str = sender->Next();
  const int value = atoi(value_str);
  sender->GetSerial()->print(tello.left(value));
}

void cmd_right(SerialCommands* sender)
{
  char* value_str = sender->Next();
  const int value = atoi(value_str);
  sender->GetSerial()->print(tello.right(value));
}


void cmd_forward(SerialCommands* sender)
{
  char* value_str = sender->Next();
  const int value = atoi(value_str);
  sender->GetSerial()->print(tello.forward(value));
}

void cmd_back(SerialCommands* sender)
{
  char* value_str = sender->Next();
  const int value = atoi(value_str);
  sender->GetSerial()->print(tello.back(value));
}

void cmd_rotate_clockwise(SerialCommands* sender)
{
  char* value_str = sender->Next();
  const int value = atoi(value_str);
  sender->GetSerial()->print(tello.rotate_clockwise(value));
}

void cmd_rotate_anticlockwise(SerialCommands* sender)
{
  char* value_str = sender->Next();
  const int value = atoi(value_str);
  sender->GetSerial()->print(tello.rotate_anticlockwise(value));
}

void cmd_flip_front(SerialCommands* sender)
{
  sender->GetSerial()->print(tello.flip_front());
}

void cmd_flip_back(SerialCommands* sender)
{
  sender->GetSerial()->print(tello.flip_back());
}

void cmd_flip_left(SerialCommands* sender)
{
  sender->GetSerial()->print(tello.flip_left());
}

void cmd_flip_right(SerialCommands* sender)
{
  sender->GetSerial()->print(tello.flip_right());
}

void cmd_setSpeed(SerialCommands* sender)
{
  char* value_str = sender->Next();
  const int value = atoi(value_str);
  sender->GetSerial()->print(tello.setSpeed(value));
}

void cmd_sendRCcontrol(SerialCommands* sender)
{
  char* x_str = sender->Next();
  const int x = atoi(x_str);
  char* y_str = sender->Next();
  const int y = atoi(y_str);
  char* z_str = sender->Next();
  const int z = atoi(z_str);

//  tello.sendRCcontrol(x,y,z);
  sender->GetSerial()->print(1);
}

void cmd_changeWifi(SerialCommands* sender)
{
  char* ssid = sender->Next();
  char* password = sender->Next();

  sender->GetSerial()->print(tello.changeWifi(ssid, password));
}

void cmd_getSpeed(SerialCommands* sender)
{
  sender->GetSerial()->print(tello.getSpeed());
}

void cmd_getBattery(SerialCommands* sender)
{
  sender->GetSerial()->print(tello.getBattery());
}

void cmd_getTime(SerialCommands* sender)
{
  sender->GetSerial()->print(tello.getTime());
}

void cmd_getHeight(SerialCommands* sender)
{
  sender->GetSerial()->print(tello.getHeight());
}

void cmd_getTemperature(SerialCommands* sender)
{
  sender->GetSerial()->print(tello.getTemperature());
}

void cmd_getBaro(SerialCommands* sender)
{
  sender->GetSerial()->print(tello.getBaro());
}

void cmd_unrecognized(SerialCommands* sender, const char* cmd)
{
  sender->GetSerial()->print("ERROR: Unrecognized command [");
  sender->GetSerial()->print(cmd);
  sender->GetSerial()->println("]");
}


SerialCommand cmd_takeoff_("takeoff", cmd_takeoff);
SerialCommand cmd_land_("land", cmd_land);
SerialCommand cmd_startVideoStream_("startvideostream", cmd_startVideoStream);
SerialCommand cmd_stopVideoStream_("stopvideostream", cmd_stopVideoStream);
SerialCommand cmd_turnOff_("turnoff", cmd_turnOff);
SerialCommand cmd_up_("up", cmd_up);
SerialCommand cmd_down_("down", cmd_down);
SerialCommand cmd_left_("left", cmd_left);
SerialCommand cmd_right_("right", cmd_right);
SerialCommand cmd_forward_("forward", cmd_forward);
SerialCommand cmd_back_("forward", cmd_back);
SerialCommand cmd_rotate_clockwise_("rotateclockwise", cmd_rotate_clockwise);
SerialCommand cmd_rotate_anticlockwise_("rotateanticlockwise", cmd_rotate_anticlockwise);
SerialCommand cmd_flip_front_("flipfront", cmd_flip_front);
SerialCommand cmd_flip_right_("flipright", cmd_flip_right);
SerialCommand cmd_flip_left_("flipleft", cmd_flip_left);
SerialCommand cmd_flip_back_("flipback", cmd_flip_back);
SerialCommand cmd_setSpeed_("setspeed", cmd_setSpeed);
SerialCommand cmd_sendRCcontrol_("sendrccontrol", cmd_sendRCcontrol);
SerialCommand cmd_changeWifi_("changewifi", cmd_changeWifi);
SerialCommand cmd_getSpeed_("getspeed", cmd_getSpeed);
SerialCommand cmd_getBattery_("getbattery", cmd_getBattery);
SerialCommand cmd_getTime_("gettime", cmd_getTime);
SerialCommand cmd_getHeight_("getheight", cmd_getHeight);
SerialCommand cmd_getTemperature_("gettemperature", cmd_getTemperature);
SerialCommand cmd_getBaro_("getbaro", cmd_getBaro);

void tello_op_setup(const int RXpin, const int TXpin)
{
    Serial2.begin(57600, SERIAL_8N1,RXpin,TXpin);
    serial_commands_2_.AddCommand(&cmd_takeoff_);
    serial_commands_2_.AddCommand(&cmd_land_);
    serial_commands_2_.AddCommand(&cmd_startVideoStream_);
    serial_commands_2_.AddCommand(&cmd_stopVideoStream_);
    serial_commands_2_.AddCommand(&cmd_turnOff_);
    serial_commands_2_.AddCommand(&cmd_up_);
    serial_commands_2_.AddCommand(&cmd_down_);
    serial_commands_2_.AddCommand(&cmd_right_);
    serial_commands_2_.AddCommand(&cmd_left_);
    serial_commands_2_.AddCommand(&cmd_forward_);
    serial_commands_2_.AddCommand(&cmd_back_);
    serial_commands_2_.AddCommand(&cmd_rotate_clockwise_);
    serial_commands_2_.AddCommand(&cmd_rotate_anticlockwise_);
    serial_commands_2_.AddCommand(&cmd_flip_front_);
    serial_commands_2_.AddCommand(&cmd_flip_right_);
    serial_commands_2_.AddCommand(&cmd_flip_left_);
    serial_commands_2_.AddCommand(&cmd_flip_back_);
    serial_commands_2_.AddCommand(&cmd_setSpeed_);
    serial_commands_2_.AddCommand(&cmd_sendRCcontrol_);
    serial_commands_2_.AddCommand(&cmd_changeWifi_);
    serial_commands_2_.AddCommand(&cmd_getSpeed_); 
    serial_commands_2_.AddCommand(&cmd_getBattery_);
    serial_commands_2_.AddCommand(&cmd_getTime_);  
    serial_commands_2_.AddCommand(&cmd_getHeight_);
    serial_commands_2_.AddCommand(&cmd_getTemperature_); 
    serial_commands_2_.AddCommand(&cmd_getBaro_);
    
    serial_commands_2_.SetDefaultHandler(&cmd_unrecognized);
}
