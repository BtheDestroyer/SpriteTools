/*
* Author: BtheDestroyer
* SpriteTools is an open source 3DS Homebrew Library which can be found here:
* https://github.com/BtheDestroyer/SpriteTools
*/

#ifdef __cplusplus
extern "C"{
#endif

#ifndef __spritetools_collision_h

#define __spritetools_collision_h

#include <3ds/types.h>

/* Inits collision */
u8 ST_CollisionInit(void);

/********************\
|*     Typedefs     *|
\********************/
/* Point hitbox */
typedef struct {
  double xpos;
  double ypos;
} st_hitboxpoint;

/* Circle hitbox */
typedef struct {
  double xpos;
  double ypos;
  double radius;
} st_hitboxcircle;

/* Line hitbox */
typedef struct {
  st_hitboxpoint start;
  st_hitboxpoint end;
} st_hitboxline;

/* Rectangle hitbox */
typedef struct {
  double xpos;
  double ypos;
  double width;
  double height;
} st_hitboxrect;

/***************************\
|*     Hitbox Creation     *|
\***************************/
/* Returns a pointer to a hitbox */
/*   Returns NULL if failed */
/* Takes a position */
st_hitboxpoint *ST_HitboxCreatePoint(double x, double y);

/* Frees hitbox from memory */
/* Takes a pointer to a hitbox */
void ST_HitboxFreePoint(st_hitboxpoint *hitbox);

/* Returns a pointer to a hitbox */
/*   Returns NULL if failed */
/* Takes a position and radius */
st_hitboxcircle *ST_HitboxCreateCircle(double x, double y, double radius);

/* Frees hitbox from memory */
/* Takes a pointer to a hitbox */
void ST_HitboxFreeCircle(st_hitboxcircle *hitbox);

/* Returns a pointer to a hitbox */
/*   Returns NULL if failed */
/* Takes two positions */
st_hitboxline *ST_HitboxCreateLine(double x1, double y1, double x2, double y2);

/* Frees hitbox from memory */
/* Takes a pointer to a hitbox */
void ST_HitboxFreeLine(st_hitboxline *hitbox);

/* Returns a pointer to a hitbox */
/*   Returns NULL if failed */
/* Takes a position and size */
st_hitboxrect *ST_HitboxCreateRect(double x, double y, double w, double h);

/* Frees hitbox from memory */
/* Takes a pointer to a hitbox */
void ST_HitboxFreeRect(st_hitboxrect *hitbox);

/******************************\
|*     Collision Checking     *|
\******************************/
/* Point and point */
u8 ST_CollisionCheckPointPoint(st_hitboxpoint *hb1, st_hitboxpoint *hb2);

/* Point and circle */
u8 ST_CollisionCheckPointCircle(st_hitboxpoint *hb1, st_hitboxcircle *hb2);

/* Point and line */
u8 ST_CollisionCheckPointLine(st_hitboxpoint *hb1, st_hitboxline *hb2);

/* Point and rect */
u8 ST_CollisionCheckPointRect(st_hitboxpoint *hb1, st_hitboxrect *hb2);
/******************************************************************************/
/* Circle and point */
u8 ST_CollisionCheckCirclePoint(st_hitboxcircle *hb1, st_hitboxpoint *hb2);

/* Circle and circle */
u8 ST_CollisionCheckCircleCircle(st_hitboxcircle *hb1, st_hitboxcircle *hb2);

/* Circle and line */
u8 ST_CollisionCheckCircleLine(st_hitboxcircle *hb1, st_hitboxline *hb2);

/* Circle and rect */
u8 ST_CollisionCheckCircleRect(st_hitboxcircle *hb1, st_hitboxrect *hb2);
/******************************************************************************/
/* Line and point */
u8 ST_CollisionCheckLinePoint(st_hitboxline *hb1, st_hitboxpoint *hb2);

/* Line and circle */
u8 ST_CollisionCheckLineCircle(st_hitboxline *hb1, st_hitboxcircle *hb2);

/* Line and line */
u8 ST_CollisionCheckLineLine(st_hitboxline *hb1, st_hitboxline *hb2);

/* Line and rect */
u8 ST_CollisionCheckLineRect(st_hitboxline *hb1, st_hitboxrect *hb2);
/******************************************************************************/
/* Rect and point */
u8 ST_CollisionCheckRectPoint(st_hitboxrect *hb1, st_hitboxpoint *hb2);

/* Rect and circle */
u8 ST_CollisionCheckRectCircle(st_hitboxrect *hb1, st_hitboxcircle *hb2);

/* Rect and line */
u8 ST_CollisionCheckRectLine(st_hitboxrect *hb1, st_hitboxline *hb2);

/* Rect and rect */
u8 ST_CollisionCheckRectRect(st_hitboxrect *hb1, st_hitboxrect *hb2);

#endif

#ifdef __cplusplus
}
#endif
