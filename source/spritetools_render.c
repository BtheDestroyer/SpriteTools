/*
* Author: BtheDestroyer
* SpriteTools is an open source 3DS Homebrew Library which can be found here:
* https://github.com/BtheDestroyer/SpriteTools
*/

#include <3ds.h>
#include <spritetools_render.h>

/*****************************\
|*     General Functions     *|
\*****************************/
/* Inits rendering */
/* Returns 1 on success and 0 on failure */
int ST_RenderInit(void)
{
  if (!sf2d_init())
    return 0;
  sf2d_set_clear_color(RGBA8(0x00, 0x00, 0x00, 0xFF));

  return 1;
}

/* Finishes rendering */
void ST_RenderFini(void)
{
  sf2d_fini();
}

/* Start frame */
/* Takes screen (GFX_TOP or GFX_BOTTOM) */
void ST_RenderStartFrame(gfxScreen_t screen)
{
  if (screen == GFX_TOP)
  {
    sf2d_start_frame(screen, GFX_LEFT);
  }
  else
  {
    sf2d_start_frame(screen, (gfx3dSide_t)NULL);
  }
}

/* Ends frame */
void ST_RenderEndRender(void)
{
  sf2d_swapbuffers();
}

/* Returns current screen */
gfxScreen_t ST_RenderCurrentScreen(void)
{
  return sf2d_get_current_screen();
}

/* Returns current fps */
float ST_RenderFPS(void)
{
  return sf2d_get_fps();
}

/* Sets background to given color */
void ST_RenderSetBackground(u8 red, u8 green, u8 blue)
{
  sf2d_set_clear_color(RGBA8(red, green, blue, 0xFF));
}

/*******************************\
|*     Render Spritesheets     *|
\*******************************/
/* Draw Spritesheet at Position */
/* Takes spritesheet and x and y of position to render on screen */
void ST_RenderSpritesheetPosition(st_spritesheet *spritesheet, int x, int y)
{
  sf2d_draw_texture(spritesheet, x, y);
}

/* Draw Spritesheet at 0,0 */
/* Takes spritesheet */
void ST_RenderSpritesheet(st_spritesheet *spritesheet)
{
  sf2d_draw_texture(spritesheet, 0, 0);
}

/* Draw Sprite in Spritesheet at Position */
/* Takes spritesheet */
/*   Takes x and y of the top left pixel of the sprite in the spritesheet */
/*   Takes width and height of the sprite in the spritesheet */
/*   Takes position to print the sprite on screen */
void ST_RenderSpritePosition(st_spritesheet *spritesheet,
  unsigned int xleft, unsigned int ytop,
  unsigned int width, unsigned int height,
  int x, int y)
{
  sf2d_draw_texture_part(spritesheet, x, y, xleft, ytop, width, height);
}

/* Draw Sprite in Spritesheet at 0,0 */
/* Takes spritesheet */
/*   Takes x and y of the top left pixel of the sprite in the spritesheet */
/*   Takes width and height of the sprite in the spritesheet */
void ST_RenderSprite(st_spritesheet *spritesheet,
  unsigned int xleft, unsigned int ytop,
  unsigned int width, unsigned int height)
{
  ST_RenderSpritePosition(spritesheet, 0, 0, xleft, ytop, width, height);
}

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
  double scale)
{
  sf2d_draw_texture_part_scale(spritesheet, x, y, xleft, ytop,
    width, height, scale, scale);
}

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
  double rotate)
{
  sf2d_draw_texture_part_rotate_scale(spritesheet, x, y, rotate, xleft, ytop,
    width, height, 1.0, 1.0);
}

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
  double rotate)
{
  sf2d_draw_texture_part_rotate_scale(spritesheet, x, y, rotate, xleft, ytop,
    width, height, scale, scale);
}

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
  u8 red, u8 green, u8 blue, u8 alpha)
{
  sf2d_draw_texture_part_rotate_scale_blend(spritesheet, x, y, rotate,
    xleft, ytop, width, height, scale, scale, RGBA8(red, green, blue, alpha));
}

/*************************\
|*     Render Frames     *|
\*************************/
/* Draw frame at given position */
/* Takes spritesheet and position at which to draw */
void ST_RenderFramePosition(st_frame *frame, int x, int y)
{
  ST_RenderSpriteAdvanced(frame->spritesheet,
  frame->xleft, frame->ytop,
  frame->width, frame->height,
  x, y,
  1.0,
  0.0,
  255, 255, 255, 255);
}

/* Draw scaled frame at given position */
/* Takes spritesheet, position at which to draw and a scalar multiplier */
void ST_RenderFrameScale(st_frame *frame, int x, int y, double scale)
{
  ST_RenderSpriteAdvanced(frame->spritesheet,
  frame->xleft, frame->ytop,
  frame->width, frame->height,
  x, y,
  scale,
  0.0,
  255, 255, 255, 255);
}

/* Draw rotated frame at given position */
/* Takes spritesheet, position at which to draw and a rotation in radians */
void ST_RenderFrameRotate(st_frame *frame, int x, int y, double rotate)
{
  ST_RenderSpriteAdvanced(frame->spritesheet,
  frame->xleft, frame->ytop,
  frame->width, frame->height,
  x, y,
  1.0,
  rotate,
  255, 255, 255, 255);
}

/* Draw scaled, rotated, and blended frame at given position */
/* Takes spritesheet and position at which to draw */
/*   Takes scalar multiplier and rotation in radians */
/*   Takes red, green, blue, and alpha of color to blend */
void ST_RenderFramePositionAdvanced(st_frame *frame, int x, int y,
  double scale, double rotate,
  u8 red, u8 green, u8 blue, u8 alpha)
{
  ST_RenderSpriteAdvanced(frame->spritesheet,
  frame->xleft, frame->ytop,
  frame->width, frame->height,
  x, y,
  scale,
  rotate,
  red, green, blue, alpha);
}

/*****************************\
|*     Render Animations     *|
\*****************************/
/* Draw the current frame of an animation at given position */
/* Takes a pointer to an animation and a position */
void ST_RenderAnimationCurrent(st_animation *animation, int x, int y)
{
  ST_RenderFramePosition(animation->frames[animation->currentFrame], x, y);
}

/* Draw the next frame of an animation at given position */
/*   Also adds 1 to the current frame */
/* Takes a pointer to an animation and a position */
void ST_RenderAnimationNext(st_animation *animation, int x, int y)
{
  animation->currentFrame++;
  if(animation->currentFrame >= animation->length)
    animation->currentFrame = animation->loopFrame;
  ST_RenderFramePosition(animation->frames[animation->currentFrame], x, y);
}

/* Draw the previous frame of an animation at given position */
/*   Also subtracts 1 from the current frame */
/* Takes a pointer to an animation and a position */
void ST_RenderAnimationPrevious(st_animation *animation, int x, int y)
{
  animation->currentFrame--;
  if(animation->currentFrame >= animation->length)
    animation->currentFrame = animation->loopFrame;
  ST_RenderFramePosition(animation->frames[animation->currentFrame], x, y);
}

/* Plays an animation at given position */
/*   This also accounts for the animation's speed */
/* Takes a pointer to an animation and a position */
void ST_RenderAnimationPlay(st_animation *animation, int x, int y)
{
  animation->ftn++;
  if (animation->ftn > animation->fpf)
  {
    animation->ftn = 0;
    ST_RenderAnimationNext(animation, x, y);
  }
  else
  {
    ST_RenderAnimationCurrent(animation, x, y);
  }
}
