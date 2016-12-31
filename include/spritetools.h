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
#include <spritetools_splash.h>
#include <spritetools_animation.h>
#include <spritetools_time.h>

/* Inits all modules and sets up */
/* Returns 1 on success, 0 on failure */
int ST_Init(void);

/* Cleans up all modules */
void ST_Fini(void);

#endif
