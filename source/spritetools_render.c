/*
* Author: BtheDestroyer
* SpriteTools is an open source 3DS Homebrew Library which can be found here:
* https://github.com/BtheDestroyer/SpriteTools
*/

#include <3ds.h>
#include <spritetools_render.h>
#include <spritetools_entity.h>

static u32 st_background = 0;

/*****************************\
|*     General Functions     *|
\*****************************/
/* Inits rendering */
/* Returns 1 on success and 0 on failure */
u8 ST_RenderInit(void)
{
  if (!sf2d_init())
    return 0;
  sf2d_set_clear_color(RGBA8(0x00, 0x00, 0x00, 0xFF));
  st_background = RGBA8(0x00, 0x00, 0x00, 0xFF);

  return 1;
}

/* Finishes rendering */
/* Returns 1 on success, 0 on failure */
u8 ST_RenderFini(void)
{
  if (!sf2d_fini())
    return 0;

  return 1;
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

u16 ST_RenderScreenWidth(gfxScreen_t screen)
{
  if (screen == GFX_TOP)
    return 400;
  else
    return 240;
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
  st_background = RGBA8(red, green, blue, 0xFF);
}

/* Returns background color in the RGBA8 format */
u32 ST_RenderGetBackground(void)
{
  return st_background;
}

/*******************************\
|*     Render Spritesheets     *|
\*******************************/
/* Draw Spritesheet at Position */
/* Takes spritesheet and x and y of position to render on screen */
void ST_RenderSpritesheetPosition(st_spritesheet *spritesheet, s64 x, s64 y)
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
  u32 xleft, u32 ytop,
  u32 width, u32 height,
  s64 x, s64 y)
{
  sf2d_draw_texture_part(spritesheet, x, y, xleft, ytop, width, height);
}

/* Draw Sprite in Spritesheet at 0,0 */
/* Takes spritesheet */
/*   Takes x and y of the top left pixel of the sprite in the spritesheet */
/*   Takes width and height of the sprite in the spritesheet */
void ST_RenderSprite(st_spritesheet *spritesheet,
  u32 xleft, u32 ytop,
  u32 width, u32 height)
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
  u32 xleft, u32 ytop,
  u32 width, u32 height,
  s64 x, s64 y,
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
  u32 xleft, u32 ytop,
  u32 width, u32 height,
  s64 x, s64 y,
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
  u32 xleft, u32 ytop,
  u32 width, u32 height,
  s64 x, s64 y,
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
  u32 xleft, u32 ytop,
  u32 width, u32 height,
  s64 x, s64 y,
  double scale,
  double rotate,
  u8 red, u8 green, u8 blue, u8 alpha)
{
  /* This is a temporary fix until I rewrite the low level rendering (sf2d) */
  width = (width + 1) / 2 * 2;
  height = (height + 1) / 2 * 2;

  sf2d_draw_texture_part_rotate_scale_blend(spritesheet, x, y, rotate,
    xleft, ytop, width, height, scale, scale, RGBA8(red, green, blue, alpha));
}

/*************************\
|*     Render Frames     *|
\*************************/
/* Draw frame at given position */
/* Takes spritesheet and position at which to draw */
void ST_RenderFramePosition(st_frame *frame, s64 x, s64 y)
{
  ST_RenderSpriteAdvanced(frame->spritesheet,
    frame->xleft, frame->ytop,
    frame->width, frame->height,
    x - frame->xoff, y - frame->yoff,
    1.0,
    0.0,
    255, 255, 255, 255);
}

/* Draw scaled frame at given position */
/* Takes spritesheet, position at which to draw and a scalar multiplier */
void ST_RenderFrameScale(st_frame *frame, s64 x, s64 y, double scale)
{
  ST_RenderSpriteAdvanced(frame->spritesheet,
    frame->xleft, frame->ytop,
    frame->width, frame->height,
    x + frame->xoff, y + frame->yoff,
    scale,
    0.0,
    255, 255, 255, 255);
}

/* Draw rotated frame at given position */
/* Takes spritesheet, position at which to draw and a rotation in radians */
void ST_RenderFrameRotate(st_frame *frame, s64 x, s64 y, double rotate)
{
  ST_RenderSpriteAdvanced(frame->spritesheet,
    frame->xleft, frame->ytop,
    frame->width, frame->height,
    x + frame->xoff, y + frame->yoff,
    1.0,
    rotate,
    255, 255, 255, 255);
}

/* Draw scaled, rotated, and blended frame at given position */
/* Takes spritesheet and position at which to draw */
/*   Takes scalar multiplier and rotation in radians */
/*   Takes red, green, blue, and alpha of color to blend */
void ST_RenderFramePositionAdvanced(st_frame *frame, s64 x, s64 y,
  double scale, double rotate,
  u8 red, u8 green, u8 blue, u8 alpha)
{
  ST_RenderSpriteAdvanced(frame->spritesheet,
    frame->xleft, frame->ytop,
    frame->width, frame->height,
    x - frame->xoff, y - frame->yoff,
    scale,
    rotate,
    red, green, blue, alpha);
}

/*****************************\
|*     Render Animations     *|
\*****************************/
/* Draw the current frame of an animation at given position */
/* Takes a pointer to an animation and a position */
void ST_RenderAnimationCurrent(st_animation *animation, s64 x, s64 y)
{
  ST_RenderFramePosition(animation->frames[animation->currentFrame], x, y);
}

/* Draw the next frame of an animation at given position */
/*   Also adds 1 to the current frame */
/* Takes a pointer to an animation and a position */
void ST_RenderAnimationNext(st_animation *animation, s64 x, s64 y)
{
  animation->currentFrame++;
  if(animation->currentFrame >= animation->length)
    animation->currentFrame = animation->loopFrame;
  ST_RenderAnimationCurrent(animation, x, y);
}

/* Draw the previous frame of an animation at given position */
/*   Also subtracts 1 from the current frame */
/* Takes a pointer to an animation and a position */
void ST_RenderAnimationPrevious(st_animation *animation, s64 x, s64 y)
{
  animation->currentFrame--;
  if(animation->currentFrame >= animation->length)
    animation->currentFrame = animation->loopFrame;
  ST_RenderAnimationCurrent(animation, x, y);
}

/* Plays an animation at given position */
/*   This also accounts for the animation's speed */
/* Takes a pointer to an animation and a position */
void ST_RenderAnimationPlay(st_animation *animation, s64 x, s64 y)
{
  animation->ftn++;
  if (animation->fpf >= 0)
  {
    if (animation->ftn >= animation->fpf)
    {
      animation->ftn = 0;
      ST_RenderAnimationNext(animation, x, y);
    }
    else
    {
      ST_RenderAnimationCurrent(animation, x, y);
    }
  }
  else
  {
    if (animation->ftn >= -1 * animation->fpf)
    {
      animation->ftn = 0;
      ST_RenderAnimationPrevious(animation, x, y);
    }
    else
    {
      ST_RenderAnimationCurrent(animation, x, y);
    }
  }
}


/****************************************\
|*     Advanced Animation Rendering     *|
\****************************************/
/* The following functions also take a scalar multiplier, */
/*   rotation in radians, and red, green, blue, and alpha of a */
/*   color to blend with */


void ST_RenderAnimationCurrentAdvanced(st_animation *animation, s64 x, s64 y,
  double scale, double rotate,
  u8 red, u8 green, u8 blue, u8 alpha)
{
  ST_RenderFramePositionAdvanced(animation->frames[animation->currentFrame],
    x, y, scale, rotate, red, green, blue, alpha);
}

void ST_RenderAnimationNextAdvanced(st_animation *animation, s64 x, s64 y,
  double scale, double rotate,
  u8 red, u8 green, u8 blue, u8 alpha)
{
  animation->currentFrame++;
  if(animation->currentFrame >= animation->length)
    animation->currentFrame = animation->loopFrame;
  ST_RenderAnimationCurrentAdvanced(animation, x, y,
    scale, rotate, red, green, blue, alpha);
}

void ST_RenderAnimationPreviousAdvanced(st_animation *animation, s64 x, s64 y,
  double scale, double rotate,
  u8 red, u8 green, u8 blue, u8 alpha)
{
  animation->currentFrame--;
  if(animation->currentFrame >= animation->length)
    animation->currentFrame = animation->loopFrame;
  ST_RenderAnimationCurrentAdvanced(animation, x, y,
    scale, rotate, red, green, blue, alpha);
}

void ST_RenderAnimationPlayAdvanced(st_animation *animation, s64 x, s64 y,
  double scale, double rotate,
  u8 red, u8 green, u8 blue, u8 alpha)
{
  animation->ftn++;
  if (animation->fpf >= 0)
  {
    if (animation->ftn > animation->fpf)
    {
      animation->ftn = 0;
      ST_RenderAnimationNextAdvanced(animation, x, y,
        scale, rotate, red, green, blue, alpha);
    }
    else
    {
      ST_RenderAnimationCurrentAdvanced(animation, x, y,
        scale, rotate, red, green, blue, alpha);
    }
  }
  else
  {
    if (animation->ftn > -1 * animation->fpf)
    {
      animation->ftn = 0;
      ST_RenderAnimationPreviousAdvanced(animation, x, y,
        scale, rotate, red, green, blue, alpha);
    }
    else
    {
      ST_RenderAnimationCurrentAdvanced(animation, x, y,
        scale, rotate, red, green, blue, alpha);
    }
  }
}

/****************************\
|*     Entity Rendering     *|
\****************************/
/* Plays the current animation of an entity */
/* Takes a pointer to an entity */
/* Returns 1 on success and 0 on failure */
u8 ST_RenderEntity(st_entity *entity)
{
    ST_RenderAnimationPlayAdvanced(entity->animations[entity->currentAnim],
      entity->xpos, entity->ypos, entity->scale, entity->rotation, entity->red,
      entity->green, entity->blue, entity->alpha);
  return 0;
}

/****************************\
|*     Camera Rendering     *|
\****************************/
/* Plays the current animation of an entity modified by a camera's values */
/* Takes a pointer to an entity and a pointer to a camera */
/* Returns 1 on success and 0 on failure */
u8 ST_RenderEntityCamera(st_entity *entity, st_camera *cam)
{
    ST_RenderAnimationPlayAdvanced(entity->animations[entity->currentAnim],
      entity->xpos - cam->x - (ST_RenderScreenWidth(ST_RenderCurrentScreen()) / 2),
      entity->ypos - cam->y - (240 / 2),
      entity->scale * cam->zoom, entity->rotation + cam->rotation,
      entity->red, entity->green,
      entity->blue, entity->alpha);
  return 0;
}
