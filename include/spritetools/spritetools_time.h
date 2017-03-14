/*
* Author: BtheDestroyer
* SpriteTools is an open source 3DS Homebrew Library which can be found here:
* https://github.com/BtheDestroyer/SpriteTools
*/

#ifdef __cplusplus
extern "C"{
#endif

#ifndef __spritetools_time_h

#define __spritetools_time_h

#include <3ds/types.h>

/**************************\
|*     Time Functions     *|
\**************************/
/* Inits times */
u8 ST_TimeInit(void);

/* Returns time since program started in ms */
u64 ST_TimeRunning(void);

/* Returns time (since January 1st, 1990) when the program started in ms */
u64 ST_TimeStarted(void);

/* Returns time since January 1st, 1990 in ms */
u64 ST_TimeOS(void);

#endif

#ifdef __cplusplus
}
#endif
