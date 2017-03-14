/*
* Author: BtheDestroyer
* SpriteTools is an open source 3DS Homebrew Library which can be found here:
* https://github.com/BtheDestroyer/SpriteTools
*/

#include <3ds.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "spritetools/spritetools_input.h"

static touchPosition INPUTTouchOrigin;
static touchPosition INPUTTouchPosition;
static touchPosition INPUTTouchLastPosition;
static s64 INPUTTouchLength;
static circlePosition INPUTCirclePosition;
static accelVector INPUTAccelVector;
static angularRate INPUTGyroRate;
static u32 INPUTKeysDown;
static u32 INPUTKeysHeld;
static u32 INPUTKeysUp;

/* Enables the Accelerometer and Gyroscope at startup */
/* Returns 1 on success and 0 on failure */
u8 ST_InputInit(void)
{
  HIDUSER_EnableAccelerometer();
  HIDUSER_EnableGyroscope();
  INPUTTouchLength = 0;

  return 1;
}

/* Scans Keys down, held, and up as well as circle and touch positions */
/*   All values are stored in static variables */
void ST_InputScan(void)
{
  hidScanInput();
  INPUTKeysDown = hidKeysDown();
  INPUTKeysHeld = hidKeysHeld();
  INPUTKeysUp = hidKeysUp();
  hidTouchRead(&INPUTTouchPosition);
  hidCircleRead(&INPUTCirclePosition);
  hidAccelRead(&INPUTAccelVector);
  hidGyroRead(&INPUTGyroRate);

  if (INPUTKeysDown & KEY_TOUCH) /* New touch was started */
  {
    INPUTTouchLength = 0;
    hidTouchRead(&INPUTTouchOrigin);
    hidTouchRead(&INPUTTouchLastPosition);
  }

  if (INPUTKeysHeld & KEY_TOUCH) /* Touch is currently held */
  {
    u32 xdiff = abs(INPUTTouchPosition.px - INPUTTouchLastPosition.px);
    u32 ydiff = abs(INPUTTouchPosition.py - INPUTTouchLastPosition.py);
    INPUTTouchLength += sqrt(xdiff * xdiff + ydiff * ydiff);
    hidTouchRead(&INPUTTouchLastPosition);
  }
  else /* Touch is not being held */
  {
    INPUTTouchLength = -1;
  }
}

/* Checks for if a button was just pressed. Requires ST_InputScan before it */
/* Takes key value enum from ctrulib to check */
/* Returns 1 if the button has just been pressed. 0 if not */
u8 ST_InputButtonPressed(u32 key)
{
  if (INPUTKeysDown & key)
    return 1;
  return 0;
}

/* Checks for if a button is being pressed. Requires ST_InputScan before it */
/* Takes key value enum from ctrulib to check */
/* Returns 1 if the button is currently down. 0 if not */
u8 ST_InputButtonDown(u32 key)
{
  if (INPUTKeysHeld & key)
    return 1;
  return 0;
}

/* Checks for if a button was just released. Requires ST_InputScan before it */
/* Takes key value enum from ctrulib to check */
/* Returns 1 if the button was just released. 0 if not */
u8 ST_InputButtonReleased(u32 key)
{
  if (INPUTKeysUp & key)
    return 1;
  return 0;
}

/* Returns X position of touch. Requires ST_InputScan before it */
/* Returns -1 if the touch screen is currently not being touched */
s16 ST_InputTouchX(void)
{
  if (INPUTKeysHeld & KEY_TOUCH)
    return INPUTTouchPosition.px;
  return -1;
}

/* Returns Y position of touch. Requires ST_InputScan before it */
/* Returns -1 if the touch screen is currently not being touched */
s16 ST_InputTouchY(void)
{
  if (INPUTKeysHeld & KEY_TOUCH)
    return INPUTTouchPosition.py;
  return -1;
}

/* Returns X position of where the touch started. */
/*   Requires ST_InputScan before it */
/* Returns -1 if the touch screen is currently not being touched */
s16 ST_InputTouchOriginX(void)
{
  if (INPUTKeysHeld & KEY_TOUCH)
    return INPUTTouchOrigin.px;
  return -1;
}

/* Returns Y position of where the touch started. */
/*   Requires ST_InputScan before it */
/* Returns -1 if the touch screen is currently not being touched */
s16 ST_InputTouchOriginY(void)
{
  if (INPUTKeysHeld & KEY_TOUCH)
    return INPUTTouchOrigin.py;
  return -1;
}

/* Returns X difference between where the touch is and where it started. */
/*   Requires ST_InputScan before it */
/* Returns -1 if the touch screen is currently not being touched */
s16 ST_InputTouchDistanceX(void)
{
  if (INPUTKeysHeld & KEY_TOUCH)
    return abs(INPUTTouchPosition.px - INPUTTouchOrigin.px);
  else
    return -1;
}

/* Returns Y difference between where the touch is and where it started. */
/*   Requires ST_InputScan before it */
/* Returns -1 if the touch screen is currently not being touched */
s16 ST_InputTouchDistanceY(void)
{
  if (INPUTKeysHeld & KEY_TOUCH)
    return abs(INPUTTouchPosition.py - INPUTTouchOrigin.py);
  else
    return -1;
}

/* Returns distance between where the touch is and where it started. */
/*   Requires ST_InputScan before it */
/* Returns -1 if the touch screen is currently not being touched */
s16 ST_InputTouchDistance(void)
{
  if (INPUTKeysHeld & KEY_TOUCH)
    return sqrt(ST_InputTouchDistanceX() * ST_InputTouchDistanceX() +
                ST_InputTouchDistanceY() * ST_InputTouchDistanceY());
  else
    return -1;
}

/* Returns length of line drawn on touchscreen. */
/*   Requires ST_InputScan before it */
/* Returns -1 if the touch screen is currently not being touched */
s64 ST_InputTouchLength(void)
{
  return INPUTTouchLength;
}

/* Returns X position of Circle Pad. Requires ST_InputScan before it */
s16 ST_InputCirclePadX(void)
{
  return INPUTCirclePosition.dx;
}

/* Returns Y position of Circle Pad. Requires ST_InputScan before it */
s16 ST_InputCirclePadY(void)
{
  return INPUTCirclePosition.dy;
}

/* Returns Accelerometer Vector. Requires ST_InputScan before it */
accelVector ST_InputAccel(void)
{
  return INPUTAccelVector;
}

/* Returns x of Accelerometer Vector. Requires ST_InputScan before it */
s16 ST_InputAccelX(void)
{
  return INPUTAccelVector.x;
}

/* Returns y of Accelerometer Vector. Requires ST_InputScan before it */
s16 ST_InputAccelY(void)
{
  return INPUTAccelVector.x;
}

/* Returns z of Accelerometer Vector. Requires ST_InputScan before it */
s16 ST_InputAccelZ(void)
{
  return INPUTAccelVector.x;
}

/* Returns Gyroscope angular Rate. Requires ST_InputScan before it */
angularRate ST_InputGyro(void)
{
  return INPUTGyroRate;
}

/* Returns x of Accelerometer Vector. Requires ST_InputScan before it */
s16 ST_InputGyroRoll(void)
{
  return INPUTGyroRate.x;
}

/* Returns y of Accelerometer Vector. Requires ST_InputScan before it */
s16 ST_InputGyroYaw(void)
{
  return INPUTGyroRate.y;
}

/* Returns z of Accelerometer Vector. Requires ST_InputScan before it */
s16 ST_InputGyroPitch(void)
{
  return INPUTGyroRate.z;
}
