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
st_frame *ST_AnimationCreateFrame(st_spritesheet *spritesheet,
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
void ST_AnimationFreeFrame(st_frame *frame)
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
st_animation *ST_AnimationCreateAnimation(u16 fpf, u16 loopFrame,
  u16 length, ...)
{
  int i;
  va_list ap;

  st_animation *tempanim = calloc(sizeof(st_animation), 1);
  if (!tempanim)
    return 0;

  tempanim->fpf = fpf;
  tempanim->ftn = 0;

  if (loopFrame < length)
    tempanim->loopFrame = loopFrame;
  else
    tempanim->loopFrame = length - 1;
  tempanim->length = length;
  tempanim->frames = calloc(sizeof(st_frame*), length);
  tempanim->currentFrame = 0;


  va_start(ap, length);

  for (i = 0; i < length; i++)
    tempanim->frames[i] = va_arg(ap, st_frame*);

  va_end (ap);

  return tempanim;
}

/* Frees an animation and all of its frames from memory */
/* Takes a pointer to an animation */
void ST_AnimationFreeAnimation(st_animation *animation)
{
  int i;
  for (i = 0; i < animation->length; i++)
    ST_AnimationFreeFrame(animation->frames[i]);
  free(animation);
}

/* Sets the current frame of an animation */
/* Takes a pointer to an animation and frame to go to */
void ST_AnimationSetFrame(st_animation *animation, u16 frame)
{
  animation->currentFrame = frame;
}

/* Adds 1 to the current frame of an animation. Wraps to 0 if needed */
/* Takes a pointer to an animation */
void ST_AnimationNextFrame(st_animation *animation)
{
  animation->currentFrame++;
  if (animation->currentFrame >= animation->length)
    animation->currentFrame = 0;
}

/* Subs 1 from the current frame of an animation */
/*   Wraps to the last frame if needed */
/* Takes a pointer to an animation */
void ST_AnimationPreviousFrame(st_animation *animation)
{
  animation->currentFrame--;
  if (animation->currentFrame >= animation->length)
    animation->currentFrame = animation->length;
}

/* Sets the speed (fpf) of an animation */
/* Takes a pointer to an animation and frame to go to */
void ST_AnimationSetSpeed(st_animation *animation, s16 speed)
{
  animation->fpf = speed;
}
