/*
* Author: BtheDestroyer
* SpriteTools is an open source 3DS Homebrew Library which can be found here:
* https://github.com/BtheDestroyer/SpriteTools
*/

#include <3ds.h>
#include "spritetools/spritetools_time.h"

/* Time from January 1st, 1990 until the program was started in ms */
static u64 ST_StartTime = 0;

/**************************\
|*     Time Functions     *|
\**************************/
/* Inits times */
u8 ST_TimeInit(void)
{
  ST_StartTime = osGetTime();
  if (ST_StartTime)
    return 1;

  return 0;
}

/* Returns time since program started in ms */
u64 ST_TimeRunning(void)
{
  return osGetTime() - ST_StartTime;
}

/* Returns time (since January 1st, 1990) when the program started in ms */
u64 ST_TimeStarted(void)
{
  return ST_StartTime;
}

/* Returns time since January 1st, 1990 in ms */
u64 ST_TimeOS(void)
{
  return osGetTime();
}
