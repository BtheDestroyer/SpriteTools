/*
* Author: BtheDestroyer
* SpriteTools is an open source 3DS Homebrew Library which can be found here:
* https://github.com/BtheDestroyer/SpriteTools
*/

#if defined (__cplusplus)
extern "C" {
#endif

#ifndef __spritetools_h

#define __spritetools_h

#include <spritetools/spritetools_debug.h>
#include <spritetools/spritetools_input.h>
#include <spritetools/spritetools_textcolors.h>
#include <spritetools/spritetools_spritesheet.h>
#include <spritetools/spritetools_render.h>
#include <spritetools/spritetools_splash.h>
#include <spritetools/spritetools_animation.h>
#include <spritetools/spritetools_time.h>
#include <spritetools/spritetools_entity.h>
#include <spritetools/spritetools_camera.h>
#include <spritetools/spritetools_collision.h>

/* Inits all modules and sets up */
/* Returns 1 on success, 0 on failure */
u8 ST_Init(void);

/* Cleans up all modules */
/* Returns 1 on success, 0 on failure */
u8 ST_Fini(void);

#endif

#if defined (__cplusplus)
}
#endif
