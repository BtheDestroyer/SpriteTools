/*
* Author: BtheDestroyer
* SpriteTools is an open source 3DS Homebrew Library which can be found here:
* https://github.com/BtheDestroyer/SpriteTools
*/

#ifdef __cplusplus
extern "C"{
#endif

#ifndef __spritetools_render_h

#define __spritetools_render_h

#include <spritetools/spritetools_spritesheet.h>
#include <spritetools/spritetools_animation.h>
#include <spritetools/spritetools_entity.h>
#include <spritetools/spritetools_camera.h>

/*****************************\
|*     General Functions     *|
\*****************************/
/* Inits rendering */
/* Returns 1 on success and 0 on failure */
u8 ST_RenderInit(void);

/* Finishes rendering */
u8 ST_RenderFini(void);

/* Start frame */
/* Takes screen (GFX_TOP or GFX_BOTTOM) */
void ST_RenderStartFrame(gfxScreen_t screen);

/* Ends rendering the current frame (for both screens) */
void ST_RenderEndRender(void);

/* Returns current screen */
gfxScreen_t ST_RenderCurrentScreen(void);

/* Returns width of given screen */
u16 ST_RenderScreenWidth(gfxScreen_t screen);

u16 ST_RenderScreenHeight(void);

/* Returns current fps */
float ST_RenderFPS(void);

/* Sets background to given color */
void ST_RenderSetBackground(u8 red, u8 green, u8 blue);

/* Returns background color in the RGBA8 format */
u32 ST_RenderGetBackground(void);

/*******************************\
|*     Render Spritesheets     *|
\*******************************/
/* Draw Spritesheet at Position */
/* Takes spritesheet and x and y of position to render on screen */
void ST_RenderSpritesheetPosition(st_spritesheet *spritesheet, s64 x, s64 y);

/* Draw Spritesheet at 0,0 */
/* Takes spritesheet */
void ST_RenderSpritesheet(st_spritesheet *spritesheet);

/* Draw Sprite in Spritesheet at Position */
/* Takes spritesheet */
/*   Takes x and y of the top left pixel of the sprite in the spritesheet */
/*   Takes width and height of the sprite in the spritesheet */
/*   Takes position to print the sprite on screen */
void ST_RenderSpritePosition(st_spritesheet *spritesheet,
  u32 xleft, u32 ytop,
  u32 width, u32 height,
  s64 x, s64 y);

/* Draw Sprite in Spritesheet at 0,0 */
/* Takes spritesheet */
/*   Takes x and y of the top left pixel of the sprite in the spritesheet */
/*   Takes width and height of the sprite in the spritesheet */
void ST_RenderSprite(st_spritesheet *spritesheet,
  u32 xleft, u32 ytop,
  u32 width, u32 height);

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
  double scale);

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
  double rotate);

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
  u32 xleft, u32 ytop,
  u32 width, u32 height,
  s64 x, s64 y,
  double scale,
  double rotate,
  u8 red, u8 green, u8 blue, u8 alpha);

/*************************\
|*     Render Frames     *|
\*************************/
/* Draw frame at given position */
/* Takes spritesheet and position at which to draw */
void ST_RenderFramePosition(st_frame *frame, s64 x, s64 y);

/* Draw scaled frame at given position */
/* Takes spritesheet, position at which to draw and a scalar multiplier */
void ST_RenderFrameScale(st_frame *frame, s64 x, s64 y, double scale);

/* Draw rotated frame at given position */
/* Takes spritesheet, position at which to draw and a rotation in radians */
void ST_RenderFrameRotate(st_frame *frame, s64 x, s64 y, double rotate);

/* Draw scaled, rotated, and blended frame at given position */
/* Takes spritesheet and position at which to draw */
/*   Takes scalar multiplier and rotation in radians */
/*   Takes red, green, blue, and alpha of color to blend */
void ST_RenderFramePositionAdvanced(st_frame *frame, s64 x, s64 y,
  double scale, double rotate,
  u8 red, u8 green, u8 blue, u8 alpha);

/*****************************\
|*     Render Animations     *|
\*****************************/
/* Draw the current frame of an animation at given position */
/* Takes a pointer to an animation and a position */
void ST_RenderAnimationCurrent(st_animation *animation, s64 x, s64 y);

/* Draw the next frame of an animation at given position */
/*   Also adds 1 to the current frame */
/* Takes a pointer to an animation and a position */
void ST_RenderAnimationNext(st_animation *animation, s64 x, s64 y);

/* Draw the previous frame of an animation at given position */
/*   Also subtracts 1 from the current frame */
/* Takes a pointer to an animation and a position */
void ST_RenderAnimationPrevious(st_animation *animation, s64 x, s64 y);

/* Plays an animation at given position */
/*   This also accounts for the animation's speed */
/* Takes a pointer to an animation and a position */
void ST_RenderAnimationPlay(st_animation *animation, s64 x, s64 y);

/****************************************\
|*     Advanced Animation Rendering     *|
\****************************************/
/* The following functions also take a scalar multiplier, */
/*   rotation in radians, and red, green, blue, and alpha of a */
/*   color to blend with */

void ST_RenderAnimationCurrentAdvanced(st_animation *animation, s64 x, s64 y,
  double scale, double rotate,
  u8 red, u8 green, u8 blue, u8 alpha);

void ST_RenderAnimationNextAdvanced(st_animation *animation, s64 x, s64 y,
  double scale, double rotate,
  u8 red, u8 green, u8 blue, u8 alpha);

void ST_RenderAnimationPreviousAdvanced(st_animation *animation, s64 x, s64 y,
  double scale, double rotate,
  u8 red, u8 green, u8 blue, u8 alpha);

void ST_RenderAnimationPlayAdvanced(st_animation *animation, s64 x, s64 y,
  double scale, double rotate,
  u8 red, u8 green, u8 blue, u8 alpha);

/****************************\
|*     Entity Rendering     *|
\****************************/
/* Plays the current animation of an entity by name */
/* Takes a pointer to an entity */
/* Returns 1 on success and 0 on failure */
u8 ST_RenderEntity(st_entity *entity);

/****************************\
|*     Camera Rendering     *|
\****************************/
/* Plays the current animation of an entity modified by a camera's values */
/* Takes a pointer to an entity and a pointer to a camera */
/* Returns 1 on success and 0 on failure */
u8 ST_RenderEntityCamera(st_entity *entity, st_camera *cam);

/* Plays the current animation of an entity modified by a camera's values */
/* Takes a pointer to an entity and a pointer to a camera */
/* This version does not rotate sprites, just modifies their positions */
/* Returns 1 on success and 0 on failure */
u8 ST_RenderEntityCameraNoSpriteRot(st_entity *entity, st_camera *cam);

/* Plays the current animation of an entity modified by a main camera's values */
/* Takes a pointer to an entity */
/* Returns 1 on success and 0 on failure */
u8 ST_RenderEntityMainCamera(st_entity *entity);

/* Plays the current animation of an entity modified by a main camera's values */
/* Takes a pointer to an entity and a pointer to a camera */
/* This version does not rotate sprites, just modifies their positions */
/* Returns 1 on success and 0 on failure */
u8 ST_RenderEntityMainCameraNoSpriteRot(st_entity *entity, st_camera *cam);

#endif

#ifdef __cplusplus
}
#endif
