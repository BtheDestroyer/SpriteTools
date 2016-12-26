/*
* Author: BtheDestroyer
* SpriteTools is an open source 3DS Homebrew Library which can be found here:
* https://github.com/BtheDestroyer/SpriteTools
*/

#include <spritetools.h>

/* Inits all modules */
int ST_Init(void)
{
  ST_DebugInit();
  ST_InputInit();
}

/* Cleans up all modules */
void ST_Fini(void)
{
  ST_DebugFini();
}
