/*
* Author: BtheDestroyer
* SpriteTools is an open source 3DS Homebrew Library which can be found here:
* https://github.com/BtheDestroyer/SpriteTools
*/

#include <3ds.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <spritetools.h>

/* Inits all modules */
void ST_Init(void)
{
  ST_DebugInit();
  ST_InputInit();
}
