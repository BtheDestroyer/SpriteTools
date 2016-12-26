/*
* Author: BtheDestroyer
* SpriteTools is an open source 3DS Homebrew Library which can be found here:
* https://github.com/BtheDestroyer/SpriteTools
*/

#include <spritetools.h>

/* Inits all modules */
int ST_Init(void)
{
  if (!ST_DebugInit())
    return 0;
  if (!ST_InputInit())
    return 0;

  return 1;
}

/* Cleans up all modules */
int ST_Fini(void)
{
  if (!ST_DebugFini())
    return 0;

  return 1;
}
