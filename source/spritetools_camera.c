/*
* Author: BtheDestroyer
* SpriteTools is an open source 3DS Homebrew Library which can be found here:
* https://github.com/BtheDestroyer/SpriteTools
*/

#include <3ds.h>
#include <stdlib.h>
#include "spritetools/spritetools_entity.h"
#include "spritetools/spritetools_camera.h"

#ifndef PI
#define PI 3.1415926535897932384626433832795
#endif

static void addU8(u8 *lhs, u8 rhs)
{
  if (rhs > 0)
  {
    if (*lhs + rhs < *lhs)
      *lhs = 0xFF;
    else
      *lhs += rhs;
  }
  else
  {
    if (*lhs + rhs > *lhs)
      *lhs = 0;
    else
      *lhs += rhs;
  }
}

/****************************\
|*     Camera Functions     *|
\****************************/
/* Create a new camera */
st_camera *ST_CameraCreate(s32 x, s32 y)
{
  st_camera *tempcam = calloc(1, sizeof(st_camera));

  tempcam->x = x;
  tempcam->y = y;
  tempcam->zoom = 1.0;
  tempcam->red = 0xFF;
  tempcam->green = 0xFF;
  tempcam->blue = 0xFF;
  tempcam->alpha = 0xFF;

  return tempcam;
}

/* Free a given camera */
void ST_CameraFree(st_camera *cam)
{
  if (cam)
    free(cam);
}

/* Move a given camera by a given amount */
void ST_CameraMoveBy(st_camera *cam, s32 x, s32 y)
{
  cam->x += x;
  cam->y += y;
}

/* Move a given camera to a given position */
void ST_CameraMoveTo(st_camera *cam, s32 x, s32 y)
{
  cam->x = x;
  cam->y = y;
}

/* Rotate a given camera to a given amount */
/* Will wrap */
void ST_CameraRotateBy(st_camera *cam, float rot)
{
  cam->rotation += rot;
  while (cam->rotation >= 2 * PI)
    cam->rotation -= 2 * PI;
  while (cam->rotation < 0)
    cam->rotation += 2 * PI;
}

/* Set a given camera's rotation */
/* Will wrap */
void ST_CameraRotateSet(st_camera *cam, float rot)
{
  cam->rotation = rot;
  while (cam->rotation >= 2 * PI)
    cam->rotation -= 2 * PI;
  while (cam->rotation < 0)
    cam->rotation += 2 * PI;
}

/* Change a given camera's zoom by a given amount */
void ST_CameraZoomBy(st_camera *cam, float zoom)
{
  cam->zoom += zoom;
}

/* Set a given camera's zoom */
void ST_CameraZoomSet(st_camera *cam, float zoom)
{
  cam->zoom = zoom;
}

/* Change a given camera's blend color by given amounts */
void ST_CameraColorChange(st_camera *cam, u8 r, u8 g, u8 b, u8 a)
{
  addU8(&cam->red, r);
  addU8(&cam->green, g);
  addU8(&cam->blue, b);
  addU8(&cam->alpha, a);
}

/* Set a given camera's blend color */
void ST_CameraColorSet(st_camera *cam, u8 r, u8 g, u8 b, u8 a)
{
  cam->red = r;
  cam->green = g;
  cam->blue = b;
  cam->alpha = a;
}