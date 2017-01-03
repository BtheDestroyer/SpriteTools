/*
* Author: BtheDestroyer
* SpriteTools is an open source 3DS Homebrew Library which can be found here:
* https://github.com/BtheDestroyer/SpriteTools
*/

#ifndef __spritetools_entity_h

#define __spritetools_entity_h

#include <spritetools_animation.h>

#define ST_ENTITY_ANIMATIONS 16

/********************\
|*     Typedefs     *|
\********************/
/* Frame of animation from a spritesheet */
typedef struct {
  st_animation **animations;
  char **names;
  int animationCount;
  s64 xpos;
  s64 ypos;
  double scale;
  double rotation;
  u8 red;
  u8 green;
  u8 blue;
  u8 alpha;
} st_entity;

/***************************\
|*     Entity Creation     *|
\***************************/
/* Returns a pointer to an entity */
/*   Returns NULL if failed */
/* Takes a position, scale, and rotation */
st_entity *ST_EntityCreateEntity(s64 x, s64, y);

/* Frees frame from memory */
/* Takes a pointer to a frame */
void ST_EntityFreeEntity(st_entity *entity);

/* Adds an animation to an entity */
/* Takes a pointer to an entity, a pointer to an animation, */
/*   and a name for the animation */
/* Returns 1 on success and 0 on failure */
int ST_EntityAddAnimation(st_entity *entity, st_animation *anim, char *name);

/**************************\
|*     Setting Values     *|
\**************************/
/* Sets the x position of a given entity */
/* Takes a pointer to an entity and a position */
void ST_EntitySetXPosition(st_entity *entity, s64 x);

/* Sets the y position of a given entity */
/* Takes a pointer to an entity and a position */
void ST_EntitySetYPosition(st_entity *entity, s64 y);

/* Sets the position of a given entity */
/* Takes a pointer to an entity and a position */
void ST_EntitySetPosition(st_entity *entity, s64 x, s64 y);

/* Sets the scale of an entity */
/* Takes a pointer to an entity and a scale */
void ST_EntitySetScale(st_entity *entity, double scale);

/* Sets the rotation of an entity */
/* Takes a pointer to an entity and a rotation value */
void ST_EntitySetRotation(st_entity *entity, double rotation);

/* Sets the red value of the color to blend an entity with when rendering */
/* Takes a pointer to an entity and a red value */
void ST_EntitySetRed(st_entity *entity, u8 red);

/* Sets the green value of the color to blend an entity with when rendering */
/* Takes a pointer to an entity and a green value */
void ST_EntitySetGreen(st_entity *entity, u8 green);

/* Sets the blue value of the color to blend an entity with when rendering */
/* Takes a pointer to an entity and a blue value */
void ST_EntitySetBlue(st_entity *entity, u8 blue);

/* Sets the alpha value of the color to blend an entity with when rendering */
/* Takes a pointer to an entity and a alpha value */
void ST_EntitySetAlpha(st_entity *entity, u8 alpha);

/* Sets the values of the color to blend an entity with when rendering */
/* Takes a pointer to an entity and red, green, blue, and alpha values */
void ST_EntitySetColor(st_entity *entity, u8 red, u8 green, u8 blue, u8 alpha);

/****************************\
|*     Modifying Values     *|
\****************************/
/* Modifies the x position of a given entity by a given amount */
/* Takes a pointer to an entity and an amount to change the position by */
void ST_EntityModifyXPosition(st_entity *entity, s64 x);

/* Modifies the y position of a given entity by a given amount */
/* Takes a pointer to an entity and an amount to change the position by */
void ST_EntityModifyYPosition(st_entity *entity, s64 y);

/* Modifies the position of a given entity by a given amount */
/* Takes a pointer to an entity and an amount to change the position by */
void ST_EntityModifyPosition(st_entity *entity, s64 x, s64 y);

/* Modifies the scale of an entity by a given amount */
/* Takes a pointer to an entity and a value to modify its scale by */
void ST_EntityModifyScale(st_entity *entity, double scale);

/* Modifies the rotation of an entity by a given amount */
/* Takes a pointer to an entity and a value to modify its rotation by */
void ST_EntityModifyRotation(st_entity *entity, double rotation);

/* Modifies the red of the blend color of an entity by a given amount */
/* Takes a pointer to an entity and a red value */
void ST_EntityModifyRed(st_entity *entity, u8 red);

/* Modifies the green of the blend color of an entity by a given amount */
/* Takes a pointer to an entity and a green value */
void ST_EntityModifyGreen(st_entity *entity, u8 green);

/* Modifies the blue of the blend color of an entity by a given amount */
/* Takes a pointer to an entity and a blue value */
void ST_EntityModifyBlue(st_entity *entity, u8 blue);

/* Modifies the alpha of the blend color of an entity by a given amount */
/* Takes a pointer to an entity and a alpha value */
void ST_EntityModifyAlpha(st_entity *entity, u8 alpha);

/* Modifies the values of the blend color of an entity by a given amount */
/* Takes a pointer to an entity and red, green, blue, and alpha values */
void ST_EntityModifyColor(st_entity *entity,
  u8 red, u8 green, u8 blue, u8 alpha);

/*****************************************\
|*     Non-Wrapping Modifying Values     *|
\*****************************************/
/* The following are just like the above, but they will not wrap */
/*   (Values greater than the maximum will be reduced to the maximum) */
/*   (Values lower than the minimum will be raised to the minimum) */

void ST_EntityModifyRotationNoWrap(st_entity *entity, double rotation);

void ST_EntityModifyRedNoWrap(st_entity *entity, int red);

void ST_EntityModifyGreenNoWrap(st_entity *entity, int green);

void ST_EntityModifyBlueNoWrap(st_entity *entity, int blue);

void ST_EntityModifyAlphaNoWrap(st_entity *entity, int alpha);

void ST_EntityModifyColorNoWrap(st_entity *entity,
  int red, int green, int blue, int alpha);

#endif
