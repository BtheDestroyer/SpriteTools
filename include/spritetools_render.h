/*
* Author: BtheDestroyer
* SpriteTools is an open source 3DS Homebrew Library which can be found here:
* https://github.com/BtheDestroyer/SpriteTools
*/

#ifndef __spritetools_render_h

#define __spritetools_render_h

#include <spritetools_spritesheet.h>
#include <spritetools_animation.h>

/*****************************\
|*     General Functions     *|
\*****************************/
/* Inits rendering */
/* Returns 1 on success and 0 on failure */
int ST_RenderInit(void);

/* Finishes rendering */
void ST_RenderFini(void);

/* Start frame */
/* Takes screen (GFX_TOP or GFX_BOTTOM) */
void ST_RenderStartFrame(gfxScreen_t screen);

/* Ends rendering the current frame (for both screens) */
void ST_RenderEndRender(void);

/* Returns current screen */
gfxScreen_t ST_RenderCurrentScreen(void);

/*******************************\
|*     Render Spritesheets     *|
\*******************************/
/* Draw Spritesheet at Position */
/* Takes spritesheet and x and y of position to render on screen */
void ST_RenderSpritesheetPosition(st_spritesheet *spritesheet, int x, int y);

/* Draw Spritesheet at 0,0 */
/* Takes spritesheet */
void ST_RenderSpritesheet(st_spritesheet *spritesheet);

/* Draw Sprite in Spritesheet at Position */
/* Takes spritesheet */
/*   Takes x and y of the top left pixel of the sprite in the spritesheet */
/*   Takes width and height of the sprite in the spritesheet */
/*   Takes position to print the sprite on screen */
void ST_RenderSpritePosition(st_spritesheet *spritesheet,
  unsigned int xleft, unsigned int ytop,
  unsigned int width, unsigned int height,
  int x, int y);

/* Draw Sprite in Spritesheet at 0,0 */
/* Takes spritesheet */
/*   Takes x and y of the top left pixel of the sprite in the spritesheet */
/*   Takes width and height of the sprite in the spritesheet */
void ST_RenderSprite(st_spritesheet *spritesheet,
  unsigned int xleft, unsigned int ytop,
  unsigned int width, unsigned int height);

/* Draw Scaled Sprite in Spritesheet at Position */
/* Takes spritesheet */
/*   Takes x and y of the top left pixel of the sprite in the spritesheet */
/*   Takes width and height of the sprite in the spritesheet */
/*   Takes position to print the sprite on screen */
/*   Takes value to scale by */
void ST_RenderSpritePositionScale(st_spritesheet *spritesheet,
  unsigned int xleft, unsigned int ytop,
  unsigned int width, unsigned int height,
  int x, int y,
  double scale);

/* Draw Rotated Sprite in Spritesheet at Position */
/* Takes spritesheet */
/*   Takes x and y of the top left pixel of the sprite in the spritesheet */
/*   Takes width and height of the sprite in the spritesheet */
/*   Takes position to print the sprite on screen */
/*   Takes radian value to rotate by */
void ST_RenderSpritePositionRotate(st_spritesheet *spritesheet,
  unsigned int xleft, unsigned int ytop,
  unsigned int width, unsigned int height,
  int x, int y,
  double rotate);

/* Draw Scaled and Rotated Sprite in Spritesheet at Position */
/* Takes spritesheet */
/*   Takes x and y of the top left pixel of the sprite in the spritesheet */
/*   Takes width and height of the sprite in the spritesheet */
/*   Takes position to print the sprite on screen */
/*   Takes value to scale by */
/*   Takes value to rotate by */
void ST_RenderSpritePositionScaleRotate(st_spritesheet *spritesheet,
  unsigned int xleft, unsigned int ytop,
  unsigned int width, unsigned int height,
  int x, int y,
  double scale,
  double rotate);

/* Draw Scaled, Rotated, and Blended Sprite in Spritesheet at Position */
/* Takes spritesheet */
/*   Takes x and y of the top left pixel of the sprite in the spritesheet */
/*   Takes width and height of the sprite in the spritesheet */
/*   Takes position to print the sprite on screen */
/*   Takes value to scale by */
/*   Takes value to rotate by */
/*   Takes color to blend with (rgba8) */
void ST_RenderSpriteAdvanced(st_spritesheet *spritesheet,
  unsigned int xleft, unsigned int ytop,
  unsigned int width, unsigned int height,
  int x, int y,
  double scale,
  double rotate,
  u8 red, u8 green, u8 blue, u8 alpha);

/*************************\
|*     Render Frames     *|
\*************************/
/* Draw frame at given position */
/* Takes spritesheet and position at which to draw */
void ST_RenderFramePosition(st_frame *frame, int x, int y);

/* Draw scaled frame at given position */
/* Takes spritesheet, position at which to draw and a scalar multiplier */
void ST_RenderFrameScale(st_frame *frame, int x, int y, double scale);

/* Draw rotated frame at given position */
/* Takes spritesheet, position at which to draw and a rotation in radians */
void ST_RenderFrameRotate(st_frame *frame, int x, int y, double rotate);

/* Draw scaled, rotated, and blended frame at given position */
/* Takes spritesheet and position at which to draw */
/*   Takes scalar multiplier and rotation in radians */
/*   Takes red, green, blue, and alpha of color to blend */
void ST_RenderFramePositionAdvanced(st_frame *frame, int x, int y,
  double scale, double rotate,
  u8 red, u8 green, u8 blue, u8 alpha);

/*****************************\
|*     Render Animations     *|
\*****************************/
/* Draw the current frame of an animation at given position */
/* Takes a pointer to an animation and a position */
void ST_RenderAnimationCurrent(st_animation *animation, int x, int y);

/* Draw the next frame of an animation at given position */
/*   Also adds 1 to the current frame */
/* Takes a pointer to an animation and a position */
void ST_RenderAnimationNext(st_animation *animation, int x, int y);

/* Draw the previous frame of an animation at given position */
/*   Also subtracts 1 from the current frame */
/* Takes a pointer to an animation and a position */
void ST_RenderAnimationPrevious(st_animation *animation, int x, int y);

/* Plays an animation at given position */
/*   This also accounts for the animation's speed */
/* Takes a pointer to an animation and a position */
void ST_RenderAnimationPlay(st_animation *animation, int x, int y);

#endif
