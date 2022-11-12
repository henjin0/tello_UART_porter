#ifndef TELLO_OPERATION
#define TELLO_OPERATION

#include <SerialCommands.h>
#include <Tello.h>

extern Tello tello;
extern SerialCommands serial_commands_2_;

void tello_op_setup(const int RXpin, const int TXpin);

#endif
