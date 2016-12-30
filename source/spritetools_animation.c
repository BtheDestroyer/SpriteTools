/*
* Author: BtheDestroyer
* SpriteTools is an open source 3DS Homebrew Library which can be found here:
* https://github.com/BtheDestroyer/SpriteTools
*/

#include <stdlib.h>
#include <stdarg.h>
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

/*******************************\
|*     Animation Functions     *|
\*******************************/
/* Returns a pointer to an animation */
/*   Returns NULL if failed */
/* Takes speed of animation (in frames between each frame of animation) */
/*   Takes frame to loop to when the animation has reached its end */
/*   Takes length of animation in frames */
/*   Takes a list of pointers to frames */
st_animation *ST_AnimationCreateAnimation(int fpf, unsigned int loopFrame,
  unsigned int length, ...)
{
  int i;
  va_list ap;

  st_animation *tempanim = calloc(sizeof(st_animation), 1);
  if (!tempanim)
    return 0;

  tempanim->fpf = fpf;
  tempanim->loopFrame = loopFrame;
  tempanim->length = length;
  tempanim->frames = calloc(sizeof(st_frame*), length);

  va_start(ap, length);

  for (i = 0; i < length; i++)
    tempanim->frames[i] = va_arg(ap, st_frame*);

  va_end (ap);

  return tempanim;
}
