/*
* Author: BtheDestroyer
* SpriteTools is an open source 3DS Homebrew Library which can be found here:
* https://github.com/BtheDestroyer/SpriteTools
*/

#include <spritetools.h>

/* Inits all modules */
void ST_Init(void)
{
  ST_DebugInit();
  ST_InputInit();
  ST_RenderInit();
}

/* Cleans up all modules */
int ST_Fini(void)
{
  if (!ST_DebugFini())
    return 0;

  return 1;
}
