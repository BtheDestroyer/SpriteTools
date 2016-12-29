/*
* Author: BtheDestroyer
* SpriteTools is an open source 3DS Homebrew Library which can be found here:
* https://github.com/BtheDestroyer/SpriteTools
*/

#ifndef __spritetools_animation_h

#define __spritetools_animation_h

#include <spritetools_spritesheet.h>

/********************\
|*     Typedefs     *|
\********************/
/* Frame of animation from a spritesheet */
typedef struct {
  st_spritesheet *spritesheet;
  unsigned int xleft;
  unsigned int ytop;
  unsigned int width;
  unsigned int height;
} st_frame;

/***************************\
|*     Frame Functions     *|
\***************************/
/* Returns a pointer to a frame */
/*   Returns NULL if failed */
/* Takes a pointer to a spritesheet */
/*   Takes the position of the frame in the spritesheet */
/*   Takes the dimensions of the frame */
st_frame *ST_FrameCreateFrame(st_spritesheet *spritesheet,
  unsigned int xleft, unsigned int ytop,
  unsigned int width, unsigned int height);

/* Frees frame from memory */
/* Takes a pointer to a frame */
void ST_FrameFreeFrame(st_frame *frame);

#endif
