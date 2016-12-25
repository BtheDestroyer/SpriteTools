/*
* Author: BtheDestroyer
* SpriteTools is an open source 3DS Homebrew Library which can be found here:
* https://github.com/BtheDestroyer/SpriteTools
*/

#ifndef __spritetools_input_h

#define __spritetools_input_h

/* Enables the Accelerometer and Gyroscope at startup */
void ST_InputInit(void);

/* Scans Keys down, held, and up as well as circle and touch positions */
/*   All values are stored in static variables */
void ST_InputScan(void);

/* Checks for if a button was just pressed. Requires ST_InputScan before it */
/* Takes key value enum from ctrulib to check */
/* Returns 1 if the button has just been pressed. 0 if not */
int ST_InputButtonPressed(u32 key);

/* Checks for if a button is being pressed. Requires ST_InputScan before it */
/* Takes key value enum from ctrulib to check */
/* Returns 1 if the button is currently down. 0 if not */
int ST_InputButtonDown(u32 key);

/* Checks for if a button was just released. Requires ST_InputScan before it */
/* Takes key value enum from ctrulib to check */
/* Returns 1 if the button was just released. 0 if not */
int ST_InputButtonReleased(u32 key);

/* Returns X position of touch. Requires ST_InputScan before it */
/* Returns -1 if the touch screen is currently not being touched */
int ST_InputTouchX(void);

/* Returns Y position of touch. Requires ST_InputScan before it */
/* Returns -1 if the touch screen is currently not being touched */
int ST_InputTouchY(void);

/* Returns X position of where the touch started. */
/*   Requires ST_InputScan before it */
/* Returns -1 if the touch screen is currently not being touched */
int ST_InputTouchOriginX(void);

/* Returns Y position of where the touch started. */
/*   Requires ST_InputScan before it */
/* Returns -1 if the touch screen is currently not being touched */
int ST_InputTouchOriginY(void);

/* Returns X difference between where the touch is and where it started. */
/*   Requires ST_InputScan before it */
/* Returns -1 if the touch screen is currently not being touched */
int ST_InputTouchDistanceX(void);

/* Returns Y difference between where the touch is and where it started. */
/*   Requires ST_InputScan before it */
/* Returns -1 if the touch screen is currently not being touched */
int ST_InputTouchDistanceY(void);

/* Returns distance between where the touch is and where it started. */
/*   Requires ST_InputScan before it */
/* Returns -1 if the touch screen is currently not being touched */
int ST_InputTouchDistance(void);

/* Returns length of line drawn on touchscreen. */
/*   Requires ST_InputScan before it */
/* Returns -1 if the touch screen is currently not being touched */
int ST_InputTouchLength(void);

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

/* Returns Gyroscope angular Rate. Requires ST_InputScan before it */
angularRate ST_InputGyro(void);

/* Returns x of Accelerometer Vector. Requires ST_InputScan before it */
s16 ST_InputGyroRoll(void);

/* Returns y of Accelerometer Vector. Requires ST_InputScan before it */
s16 ST_InputGyroYaw(void);

/* Returns z of Accelerometer Vector. Requires ST_InputScan before it */
s16 ST_InputGyroPitch(void);

#endif
