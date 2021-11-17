#include "sense.h"
#include <stdio.h>

pi_joystick_t* joystick;

void openJoystick(void) {

	if (joystick==NULL) {
		joystick = getJoystickDevice();
	}

}

void closeJoystick(void) {

	if (joystick) {
		freeJoystick(joystick);
	}
	joystick = NULL;
}

void checkJoystick(void (*callback)(unsigned int code), int delay) {
	pollJoystick(joystick,callback,delay);
}
