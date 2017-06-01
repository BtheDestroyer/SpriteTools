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

/* Used for adding U8s and preventing underflow/overflow */
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

static st_camera *MainCamera = NULL;

/****************************\
|*     Camera Functions     *|
\****************************/
/* Create a new camera */
st_camera *ST_CameraCreate(double x, double y)
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
void ST_CameraMoveBy(st_camera *cam, double x, double y)
{
  cam->x += x;
  cam->y += y;
}

/* Move a given camera to a given position */
void ST_CameraMoveTo(st_camera *cam, double x, double y)
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

/***********************************\
|*     Follow Entity Functions     *|
\***********************************/

/* Set a given camera's entity to follow */
/* Takes a camera pointer and pointer of the entity to follow */
void ST_CameraSetFollowEntity(st_camera *cam, st_entity *ent)
{
  cam->following = ent;
}

/* Clears a given camera's entity to follow */
/* Takes a camera pointer */
void ST_CameraClearFollowEntity(st_camera *cam)
{
  ST_CameraSetFollowEntity(cam, NULL);
}

/* Move a given camera's follow offset by a given amount */
/* Takes a camera pointer and position to move it's offset by */
void ST_CameraMoveFollowOffsetBy(st_camera *cam, double x, double y)
{
  cam->followXOff += x;
  cam->followYOff += y;
}

/* Move a given camera's follow offset to a given position */
/* Takes a camera pointer and position to move it's offset to */
void ST_CameraMoveFollowOffsetTo(st_camera *cam, double x, double y)
{
  cam->followXOff = x;
  cam->followYOff = y;
}

/* Clears a given camera's entity to follow */
/* Takes a camera pointer */
void ST_CameraMoveToFollow(st_camera *cam)
{
  if (!cam->following)
    return;
  cam->x = cam->following->xpos + cam->followXOff;
  cam->y = cam->following->ypos + cam->followYOff;

  if (ST_CameraCheckFollowFlag(cam, CFF_ROTATE_WITH_ENTITY))
    cam->rotation = cam->following->rotation;

  if (ST_CameraCheckFollowFlag(cam, CFF_OFFSET_WITH_ROTATION))
  {
    cam->x = cam->x * cos(cam->following->rotation) - cam->y * sin(cam->following->rotation);
    cam->y = cam->y * sin(cam->following->rotation) + cam->x * cos(cam->following->rotation);
  }

  if (ST_CameraCheckFollowFlag(cam, CFF_INVERT_SCALE_WITH_ENTITY))
    cam->zoom = (float) (1.0 / cam->following->scale);

  if (ST_CameraCheckFollowFlag(cam, CFF_OFFSET_WITH_SCALE))
  {
    cam->x *= cam->following->scale;
    cam->y *= cam->following->scale;
  }
}

/* Set's a camera's given follow flag to the given state */
/* Takes a camera pointer, flag to set, and state to set the flag to */
void ST_CameraSetFollowFlag(st_camera *cam, CAMERA_FOLLOW_FLAGS flag, bool state)
{
  if (state)
    cam->followFlags |= flag;
  else
    cam->followFlags &= ~flag;
}

/* Toggles's a camera's given follow flag */
/* Takes a camera pointer and flag to toggle */
void ST_CameraToggleFollowFlag(st_camera *cam, CAMERA_FOLLOW_FLAGS flag)
{
  cam->followFlags ^= flag;
}

/* Checks a camera's given follow flag. Returns 0 if it's not set and 1 if it is */
/* Takes a camera pointer and flag to check */
u8 ST_CameraCheckFollowFlag(st_camera *cam, CAMERA_FOLLOW_FLAGS flag)
{
  return (cam->followFlags & flag) != 0;
}

/*********************************\
|*     Main Camera Functions     *|
\*********************************/
/* Sets the main camera to a given camera */
/* Takes the camera to set it to */
void ST_MainCameraSet(st_camera *cam)
{
  MainCamera = cam;
}

/* Clears the main camera */
void ST_MainCameraClear(void)
{
  ST_MainCameraSet(NULL);
}

/* Returns the Main Camera */
st_camera *ST_MainCameraGet(void)
{
  return MainCamera;
}
