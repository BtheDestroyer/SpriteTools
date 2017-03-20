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
  CFF_ROTATE_WITH_ENTITY = 0x1,
  CFF_OFFSET_WITH_ROTATION = 0x10,
  CFF_INVERT_SCALE_WITH_ENTITY = 0x100,
  CFF_OFFSET_WITH_SCALE = 0x1000,
  CFF_ALL = 0x11111111
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

/***********************************\
|*     Follow Entity Functions     *|
\***********************************/

/* Set a given camera's entity to follow */
/* Takes a camera pointer and pointer of the entity to follow */
void ST_CameraSetFollowEntity(st_camera *cam, st_entity *ent);

/* Clears a given camera's entity to follow */
/* Takes a camera pointer */
void ST_CameraClearFollowEntity(st_camera *cam);

/* Move a given camera's follow offset by a given amount */
/* Takes a camera pointer and position to move it's offset by */
void ST_CameraMoveFollowOffsetBy(st_camera *cam, s32 x, s32 y);

/* Move a given camera's follow offset to a given position */
/* Takes a camera pointer and position to move it's offset to */
void ST_CameraMoveFollowOffsetTo(st_camera *cam, s32 x, s32 y);

/* Clears a given camera's entity to follow */
/* Takes a camera pointer */
void ST_CameraMoveToFollow(st_camera *cam);

/* Set's a camera's given follow flag to the given state */
/* Takes a camera pointer, flag to set, and state to set the flag to */
void ST_CameraSetFollowFlag(st_camera *cam, CAMERA_FOLLOW_FLAGS flag, bool state);

/* Toggles's a camera's given follow flag */
/* Takes a camera pointer and flag to toggle */
void ST_CameraToggleFollowFlag(st_camera *cam, CAMERA_FOLLOW_FLAGS flag);

/* Checks a camera's given follow flag. Returns 0 if it's not set and 1 if it is */
/* Takes a camera pointer and flag to check */
u8 ST_CameraCheckFollowFlag(st_camera *cam, CAMERA_FOLLOW_FLAGS flag);

#endif
