/*
* Author: BtheDestroyer
* SpriteTools is an open source 3DS Homebrew Library which can be found here:
* https://github.com/BtheDestroyer/SpriteTools
*/

#ifndef __spritetools_camera_h

#define __spritetools_camera_h

/********************\
|*     Typedefs     *|
\********************/
/* Frame of animation from a spritesheet */
typedef struct {
  s32 x, y;
  float zoom, rotation;
  u8 red, green, blue, alpha;
  st_entity *following;
  u8 followFlags;
  s32 followXOff, followYOff;
} st_camera;

typedef enum {
  CFF_ROTATE_WITH_ENTITY,
  CFF_OFFSET_WITH_ROTATION,
  CFF_COUNT,
} CAMERA_FOLLOW_FLAGS;

/****************************\
|*     Camera Functions     *|
\****************************/
/* Create a new camera */
/* Takes x and y positions of the new camera */
/* Returns created camera */
st_camera *ST_CameraCreate(s32 x, s32 y);

/* Free a given camera */
/* Takes a pointer to a camera to free */
void ST_CameraFree(st_camera *cam);

/* Move a given camera by a given amount */
/* Takes a camera pointer and position to move it by */
void ST_CameraMoveBy(st_camera *cam, s32 x, s32 y);

/* Move a given camera to a given position */
/* Takes a camera pointer and position to move it to */
void ST_CameraMoveTo(st_camera *cam, s32 x, s32 y);

/* Rotate a given camera to a given amount */
/*   Will wrap */
/* Takes a camera pointer and value to rotate it by */
void ST_CameraRotateBy(st_camera *cam, float rot);

/* Set a given camera's rotation */
/*   Will wrap */
/* Takes a camera pointer and value to rotate it to */
void ST_CameraRotateSet(st_camera *cam, float rot);

/* Change a given camera's zoom by a given amount */
/* Takes a camera pointer and value to zoom it by */
void ST_CameraZoomBy(st_camera *cam, float zoom);

/* Set a given camera's zoom */
/* Takes a camera pointer and value to zoom it to */
void ST_CameraZoomSet(st_camera *cam, float zoom);

/* Change a given camera's blend color by given amounts */
/* Takes a camera pointer and rgba values to modify its color by */
void ST_CameraColorChange(st_camera *cam, u8 r, u8 g, u8 b, u8 a);

/* Set a given camera's blend color */
/* Takes a camera pointer and rgba values to set its color to */
void ST_CameraColorSet(st_camera *cam, u8 r, u8 g, u8 b, u8 a);

#endif
