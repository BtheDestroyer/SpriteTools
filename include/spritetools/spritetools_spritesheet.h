/*
* Author: BtheDestroyer
* SpriteTools is an open source 3DS Homebrew Library which can be found here:
* https://github.com/BtheDestroyer/SpriteTools
*/

#ifdef __cplusplus
extern "C"{
#endif

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
/* Load spritesheet from image as a C file */
/* Takes image */
/* Returns pointer to st_spritesheet */
st_spritesheet *ST_SpritesheetCreateSpritesheet(const unsigned char *pixel_data,
    unsigned int width, unsigned int height);

/* Free spritesheet */
/* Takes st_spritesheet */
void ST_SpritesheetFreeSpritesheet(st_spritesheet *spritesheet);

#ifdef SFIL_H
/**********************************\
|*     SFILLIB Implimentation     *|
\**********************************/
/* To use these, include sfil.h before spritetools_spritesheet.h */
/* Check out the sfillib example for an example */
/* https://github.com/xerpi/sfillib/tree/master/sample */

/* Load spritesheet from image as a PNG file */
/* Takes buffer */
/* Returns pointer to st_spritesheet */
st_spritesheet *ST_SpritesheetCreateSpritesheetPNG(const void *buffer);

/* Load spritesheet from image as a BMP file */
/* Takes filename */
/* Returns pointer to st_spritesheet */
st_spritesheet *ST_SpritesheetCreateSpritesheetBMP(const void *buffer);

/* Load spritesheet from image as a JPEG file */
/* Takes filename */
/* Returns pointer to st_spritesheet */
st_spritesheet *ST_SpritesheetCreateSpritesheetJPEG(const void *buffer, unsigned long buffer_size);

#endif

#endif

#ifdef __cplusplus
}
#endif
