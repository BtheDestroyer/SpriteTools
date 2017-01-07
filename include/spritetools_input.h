/*
* Author: BtheDestroyer
* SpriteTools is an open source 3DS Homebrew Library which can be found here:
* https://github.com/BtheDestroyer/SpriteTools
*/

#ifndef __spritetools_input_h

#define __spritetools_input_h
#include <3ds.h>

/* Enables the Accelerometer and Gyroscope at startup */
/* Returns 1 on success and 0 on failure */
u8 ST_InputInit(void);

/* Scans Keys down, held, and up as well as circle and touch positions */
/*   All values are stored in static variables */
void ST_InputScan(void);

/* Checks for if a button was just pressed. Requires ST_InputScan before it */
/* Takes key value enum from ctrulib to check */
/* Returns 1 if the button has just been pressed. 0 if not */
u8 ST_InputButtonPressed(u32 key);

/* Checks for if a button is being pressed. Requires ST_InputScan before it */
/* Takes key value enum from ctrulib to check */
/* Returns 1 if the button is currently down. 0 if not */
u8 ST_InputButtonDown(u32 key);

/* Checks for if a button was just released. Requires ST_InputScan before it */
/* Takes key value enum from ctrulib to check */
/* Returns 1 if the button was just released. 0 if not */
u8 ST_InputButtonReleased(u32 key);

/* Returns X position of touch. Requires ST_InputScan before it */
/* Returns -1 if the touch screen is currently not being touched */
s16 ST_InputTouchX(void);

/* Returns Y position of touch. Requires ST_InputScan before it */
/* Returns -1 if the touch screen is currently not being touched */
s16 ST_InputTouchY(void);

/* Returns X position of where the touch started. */
/*   Requires ST_InputScan before it */
/* Returns -1 if the touch screen is currently not being touched */
s16 ST_InputTouchOriginX(void);

/* Returns Y position of where the touch started. */
/*   Requires ST_InputScan before it */
/* Returns -1 if the touch screen is currently not being touched */
s16 ST_InputTouchOriginY(void);

/* Returns X difference between where the touch is and where it started. */
/*   Requires ST_InputScan before it */
/* Returns -1 if the touch screen is currently not being touched */
s16 ST_InputTouchDistanceX(void);

/* Returns Y difference between where the touch is and where it started. */
/*   Requires ST_InputScan before it */
/* Returns -1 if the touch screen is currently not being touched */
s16 ST_InputTouchDistanceY(void);

/* Returns distance between where the touch is and where it started. */
/*   Requires ST_InputScan before it */
/* Returns -1 if the touch screen is currently not being touched */
s16 ST_InputTouchDistance(void);

/* Returns length of line drawn on touchscreen. */
/*   Requires ST_InputScan before it */
/* Returns -1 if the touch screen is currently not being touched */
s64 ST_InputTouchLength(void);

/* Returns X position of Circle Pad. Requires ST_InputScan before it */
s16 ST_InputCirclePadX(void);

/* Returns Y position of Circle Pad. Requires ST_InputScan before it */
s16 ST_InputCirclePadY(void);

/* Returns Accelerometer Vector. Requires ST_InputScan before it */
accelVector ST_InputAccel(void);

/* Returns x of Accelerometer Vector. Requires ST_InputScan before it */
s16 ST_InputAccelX(void);

/* Returns y of Accelerometer Vector. Requires ST_InputScan before it */
s16 ST_InputAccelY(void);

/* Returns z of Accelerometer Vector. Requires ST_InputScan before it */
s16 ST_InputAccelZ(void);

/* Returns Gyroscope's angular Rate. Requires ST_InputScan before it */
angularRate ST_InputGyro(void);

/* Returns x of Gyroscope's angular Rate. Requires ST_InputScan before it */
s16 ST_InputGyroRoll(void);

/* Returns y of Gyroscope's angular Rate. Requires ST_InputScan before it */
s16 ST_InputGyroYaw(void);

/* Returns z of Gyroscope's angular Rate. Requires ST_InputScan before it */
s16 ST_InputGyroPitch(void);

#endif
