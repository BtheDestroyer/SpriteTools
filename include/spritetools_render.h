/*
* Author: BtheDestroyer
* SpriteTools is an open source 3DS Homebrew Library which can be found here:
* https://github.com/BtheDestroyer/SpriteTools
*/

#ifndef __spritetools_render_h

#define __spritetools_render_h

/* For now, this depends on sf2d. */
/* In the future, it will be rewritten to be fully independant */
/* This means that you can technically use sf2d stuff and it'll work, but */
/* only using spritetools functions and types means you will be able to */
/* more easily and safely update */
#include <sf2d.h>

/****************************\
|*     Render Functions     *|
\****************************/
/* Inits rendering */
/* Returns 1 on success and 0 on failure */
int ST_RenderInit(void);

/* Start frame */
/* Takes screen (GFX_TOP or GFX_BOTTOM) */
void ST_RenderStartFrame(gfxScreen_t screen);

/* Ends rendering the current frame (for both screens) */
void ST_RenderEndRender(void);

/* Draw Spritesheet at Position */
/* Takes spritesheet and x and y of position to render on screen */
/* Untested */
void ST_RenderSpritesheetPosition(st_spritesheet *spritesheet, int x, int y);

/* Draw Spritesheet at 0,0 */
/* Takes spritesheet */
/* Untested */
void ST_RenderSpritesheet(st_spritesheet *spritesheet);

/* Draw Sprite in Spritesheet at Position */
/* Takes spritesheet */
/*   Takes x and y of the top left pixel of the sprite in the spritesheet */
/*   Takes width and height of the sprite in the spritesheet */
/*   Takes position to print the sprite on screen */
/* Untested */
void ST_RenderSpritePosition(st_spritesheet *spritesheet,
  unsigned int xleft, unsigned int ytop,
  unsigned int width, unsigned int height,
  int x, int y);

/* Draw Sprite in Spritesheet at 0,0 */
/* Takes spritesheet */
/*   Takes x and y of the top left pixel of the sprite in the spritesheet */
/*   Takes width and height of the sprite in the spritesheet */
/* Untested */
void ST_RenderSprite(st_spritesheet *spritesheet,
  unsigned int xleft, unsigned int ytop,
  unsigned int width, unsigned int height);

/* Draw Scaled Sprite in Spritesheet at Position */
/* Takes spritesheet */
/*   Takes x and y of the top left pixel of the sprite in the spritesheet */
/*   Takes width and height of the sprite in the spritesheet */
/*   Takes position to print the sprite on screen */
/*   Takes value to scale by */
/* Untested */
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
/* Untested */
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
/* Untested */
void ST_RenderSpritePositionScaleRotate(st_spritesheet *spritesheet,
  unsigned int xleft, unsigned int ytop,
  unsigned int width, unsigned int height,
  int x, int y,
  double scale,
  double rotate);

#endif
