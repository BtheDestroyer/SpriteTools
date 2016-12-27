/*
* Author: BtheDestroyer
* SpriteTools is an open source 3DS Homebrew Library which can be found here:
* https://github.com/BtheDestroyer/SpriteTools
*/

#ifndef __spritetools_spritesheet_h

#define __spritetools_spritesheet_h

/* For now, this depends on sf2d. */
/* In the future, it will be rewritten to be fully independant */
/* This means that you can technically use sf2d stuff and it'll work, but */
/* only using spritetools functions and types means you will be able to */
/* more easily and safely update */
#include <sf2d.h>

/*******************************\
|*     Spritesheet Defines     *|
\*******************************/
/* Temporary define until this is split from sf2d */
#define st_spritesheet sf2d_texture
/* image structure */
#define st_image struct {\
  unsigned int width;\
  unsigned int height;\
  unsigned int bytes_per_pixel;\
  unsigned char pixel_data[];\
}

/*********************************\
|*     Spritesheet Functions     *|
\*********************************/
/* Load spritesheet from image */
/* Takes image */
/* Returns pointer to st_spritesheet */
st_spritesheet *ST_SpritesheetCreateSpritesheet(const unsigned char *pixel_data,
    unsigned int width, unsigned int height);

/* Free spritesheet */
/* Takes st_spritesheet */
void ST_SpritesheetFreeSpritesheet(st_spritesheet *spritesheet);

#endif
