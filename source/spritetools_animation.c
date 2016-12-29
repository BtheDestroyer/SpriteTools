/*
* Author: BtheDestroyer
* SpriteTools is an open source 3DS Homebrew Library which can be found here:
* https://github.com/BtheDestroyer/SpriteTools
*/

#include <stdlib.h>
#include <spritetools_animation.h>

/***************************\
|*     Frame Functions     *|
\***************************/
/* Returns a pointer to a frame */
/* Takes a pointer to a spritesheet */
/*   Takes the position of the frame in the spritesheet */
/*   Takes the dimensions of the frame */
st_frame *ST_FrameCreateFrame(st_spritesheet *spritesheet,
  unsigned int xleft, unsigned int ytop,
  unsigned int width, unsigned int height)
{
  st_frame *tempframe = calloc(sizeof(st_frame), 1);
  if (!tempframe)
    return 0;

  tempframe->spritesheet = spritesheet;
  tempframe->xleft = xleft;
  tempframe->ytop = ytop;
  tempframe->width = width;
  tempframe->height = height;

  return tempframe;
}

/* Frees frame from memory */
/* Takes a pointer to a frame */
void ST_FrameFreeFrame(st_frame *frame)
{
  free(frame);
}
