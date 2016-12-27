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
  sf2d_set_clear_color(RGBA8(0x20, 0xA0, 0x20, 0xFF));

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
