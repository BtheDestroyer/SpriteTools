/*
* Author: BtheDestroyer
* SpriteTools is an open source 3DS Homebrew Library which can be found here:
* https://github.com/BtheDestroyer/SpriteTools
*/

#ifndef __spritetools_h

#define __spritetools_h

#include <spritetools_debug.h>
#include <spritetools_input.h>
#include <spritetools_textcolors.h>
#include <spritetools_spritesheet.h>
#include <spritetools_render.h>

/* Inits all modules and sets up */
void ST_Init(void);

/* Cleans up all modules */
int ST_Fini(void);

#endif
