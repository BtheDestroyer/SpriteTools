/*
* Author: BtheDestroyer
* SpriteTools is an open source 3DS Homebrew Library which can be found here:
* https://github.com/BtheDestroyer/SpriteTools
*/

#include <3ds.h>
#include "spritetools/spritetools_collision.h"

/* Inits collision */
u8 ST_CollisionInit(void)
{
  return 1;
}

/***************************\
|*     Hitbox Creation     *|
\***************************/
/* Returns a pointer to a hitbox */
/*   Returns NULL if failed */
/* Takes a position */
st_hitboxpoint *ST_HitboxCreatePoint(double x, double y)
{
  st_hitboxpoint *tempbox = calloc(sizeof(st_hitboxpoint), 1);
  if (!tempbox)
    return NULL;

  tempbox->xpos = x;
  tempbox->ypos = y;

  return tempbox;
}

/* Frees hitbox from memory */
/* Takes a pointer to a hitbox */
void ST_HitboxFreePoint(st_hitboxpoint *hitbox)
{
  if (!hitbox)
    return;
  free(hitbox);
}

/* Returns a pointer to a hitbox */
/*   Returns NULL if failed */
/* Takes a position and radius */
st_hitboxcircle *ST_HitboxCreateCircle(double x, double y, double radius)
{
  st_hitboxcircle *tempbox = calloc(sizeof(st_hitboxcircle), 1);
  if (!tempbox)
    return NULL;

  tempbox->xpos = x;
  tempbox->ypos = y;
  tempbox->radius = radius;

  return tempbox;
}

/* Frees hitbox from memory */
/* Takes a pointer to a hitbox */
void ST_HitboxFreeCircle(st_hitboxcircle *hitbox)
{
  if (!hitbox)
    return;
  free(hitbox);
}

/* Returns a pointer to a hitbox */
/*   Returns NULL if failed */
/* Takes two positions */
st_hitboxline *ST_HitboxCreateLine(double x1, double y1, double x2, double y2)
{
  st_hitboxpoint *start = ST_HitboxCreatePoint(x1, y1);
  if (!start)
    return NULL;

  st_hitboxpoint *end = ST_HitboxCreatePoint(x2, y2);
  if (!end)
  {
    ST_HitboxFreePoint(start);
    return NULL;
  }

  st_hitboxline *tempbox = calloc(sizeof(st_hitboxline), 1);
  if (!tempbox)
  {
    ST_HitboxFreePoint(start);
    ST_HitboxFreePoint(end);
    return NULL;
  }

  tempbox->start = start;
  tempbox->end = end;

  return tempbox;
}

/* Frees hitbox from memory */
/* Takes a pointer to a hitbox */
void ST_HitboxFreeLine(st_hitboxline *hitbox)
{
  if (!hitbox)
    return;
  ST_HitboxFreePoint(hitbox->start);
  ST_HitboxFreePoint(hitbox->end);
  free(hitbox);
}

/* Returns a pointer to a hitbox */
/*   Returns NULL if failed */
/* Takes a position and size */
st_hitboxrect *ST_HitboxCreateRect(double x, double y, double w, double h)
{
  st_hitboxcircle *tempbox = calloc(sizeof(st_hitboxrect), 1);
  if (!tempbox)
    return NULL;

  tempbox->xpos = x;
  tempbox->ypos = y;
  tempbox->width = w;
  tempbox->height = h;

  return tempbox;
}

/* Frees hitbox from memory */
/* Takes a pointer to a hitbox */
void ST_HitboxFreeRect(st_hitboxrect *hitbox)
{
  if (!hitbox)
    return;
  free(hitbox);
}

/******************************\
|*     Collision Checking     *|
\******************************/
/******************************************************************************/
/* Point and point */
u8 ST_CollisionCheckPointPoint(st_hitboxpoint *hb1, st_hitboxpoint *hb2)
{
  if (hb1->xpos == hb2->xpos && hb1->ypos == hb2->ypos)
    return 1;
  return 0;
}

/* Point and circle */
u8 ST_CollisionCheckPointCircle(st_hitboxpoint *hb1, st_hitboxcircle *hb2)
{
  double xdiff = hb1->xpos - hb2->xpos;
  double ydiff = hb1->ypos - hb2->ypos;
  if (hb2->radius * hb2->radius <= xdiff * xdiff + ydiff * ydiff)
    return 1;
  return 0;
}

/* Point and rect */
u8 ST_CollisionCheckPointRect(st_hitboxpoint *hb1, st_hitboxrect *hb2)
{
  if (hb1->xpos >= hb2->xpos && hb1->xpos <= hb2->xpos + hb2->width &&
      hb1->ypos >= hb2->ypos && hb1->ypos <= hb2->ypos + hb2->height)
    return 1;
  return 0;
}
/******************************************************************************/
/* Circle and point */
u8 ST_CollisionCheckCirclePoint(st_hitboxcircle *hb1, st_hitboxpoint *hb2)
{
  double xdiff = hb1->xpos - hb2->xpos;
  double ydiff = hb1->ypos - hb2->ypos;
  if (hb1->radius * hb1->radius <= xdiff * xdiff + ydiff * ydiff)
    return 1;
  return 0;
}

/* Circle and circle */
u8 ST_CollisionCheckCircleCircle(st_hitboxcircle *hb1, st_hitboxcircle *hb2)
{
  double xdiff = hb1->xpos - hb2->xpos;
  double ydiff = hb1->ypos - hb2->ypos;
  double radius = hb1->radius + hb2->radius;
  if (radius * radius  <= xdiff * xdiff + ydiff * ydiff)
    return 1;
  return 0;
}

/* Circle and rect */
u8 ST_CollisionCheckCircleRect(st_hitboxcircle *hb1, st_hitboxrect *hb2);
/******************************************************************************/
/* Rect and point */
u8 ST_CollisionCheckRectPoint(st_hitboxrect *hb1, st_hitboxpoint *hb2);

/* Rect and circle */
u8 ST_CollisionCheckRectCircle(st_hitboxrect *hb1, st_hitboxcircle *hb2);

/* Rect and rect */
u8 ST_CollisionCheckRectRect(st_hitboxrect *hb1, st_hitboxrect *hb2);
