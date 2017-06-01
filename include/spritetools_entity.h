/*
* Author: BtheDestroyer
* SpriteTools is an open source 3DS Homebrew Library which can be found here:
* https://github.com/BtheDestroyer/SpriteTools
*/

#ifndef __spritetools_entity_h

#define __spritetools_entity_h

#include <spritetools_animation.h>

/********************\
|*     Typedefs     *|
\********************/
/* Entity with a ton of rendering info */
typedef struct {
  st_animation **animations;
  char **names;
  char *dir;
  double xpos;
  double ypos;
  double scale;
  double rotation;
  u32 flags;
  u8 animationCount;
  u8 totalAnims;
  u8 currentAnim;
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
/* Takes a position and number of animations */
st_entity *ST_EntityCreateEntity(double x, double y, u8 animCount);

/* Frees frame from memory */
/* Takes a pointer to a frame */
void ST_EntityFreeEntity(st_entity *entity);

/* Adds an animation to an entity */
/* Takes a pointer to an entity, a pointer to an animation, */
/*   and a name for the animation */
/* Returns 1 on success and 0 on failure */
u8 ST_EntityAddAnimation(st_entity *entity, st_animation *anim, char *name);

/**************************\
|*     Setting Values     *|
\**************************/
/* Sets the x position of a given entity */
/* Takes a pointer to an entity and a position */
void ST_EntitySetXPosition(st_entity *entity, double x);

/* Sets the y position of a given entity */
/* Takes a pointer to an entity and a position */
void ST_EntitySetYPosition(st_entity *entity, double y);

/* Sets the position of a given entity */
/* Takes a pointer to an entity and a position */
void ST_EntitySetPosition(st_entity *entity, double x, double y);

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

/* Sets the direction of an entity */
/* Takes a pointer to an entity and a direction */
/* Returns 1 on success and 0 on failure */
u8 ST_EntitySetDirection(st_entity *entity, char *dir);

/* Sets the direction of an entity */
/* Takes a pointer to an entity and a direction id */
/*   0 = east */
/*   1 = south east */
/*   2 = south */
/*   3 = south west */
/*   4 = west */
/*   5 = north west */
/*   6 = north */
/*   7 = north east */
/* Returns 1 on success and 0 on failure */
u8 ST_EntitySetDirectionId(st_entity *entity, u8 dir);

/* Sets the current animation of an entity by name */
/* Takes a pointer to an entity and the name of the animation to set */
/* Returns 1 on success and 0 on failure */
u8 ST_EntitySetAnimationName(st_entity *entity, char *name);

/* Sets the current animation of an entity by id */
/* Takes a pointer to an entity and the id of the animation to set */
/* Returns 1 on success and 0 on failure */
u8 ST_EntitySetAnimationId(st_entity *entity, u8 id);

/****************************\
|*     Modifying Values     *|
\****************************/
/* Modifies the x position of a given entity by a given amount */
/* Takes a pointer to an entity and an amount to change the position by */
void ST_EntityModifyXPosition(st_entity *entity, double x);

/* Modifies the y position of a given entity by a given amount */
/* Takes a pointer to an entity and an amount to change the position by */
void ST_EntityModifyYPosition(st_entity *entity, double y);

/* Modifies the position of a given entity by a given amount */
/* Takes a pointer to an entity and an amount to change the position by */
void ST_EntityModifyPosition(st_entity *entity, double x, double y);

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

/* Modifies the direction of an entity */
/* Takes a pointer to an entity and a value to turn by */
/*   Positive turns right, negative turns left */
void ST_EntityModifyDirection(st_entity *entity, s8 dir);

/*****************************************\
|*     Non-Wrapping Modifying Values     *|
\*****************************************/
/* The following are just like the above, but they will not wrap */
/*   (Values greater than the maximum will be reduced to the maximum) */
/*   (Values lower than the minimum will be raised to the minimum) */

void ST_EntityModifyRotationNoWrap(st_entity *entity, double rotation);

void ST_EntityModifyRedNoWrap(st_entity *entity, u8 red);

void ST_EntityModifyGreenNoWrap(st_entity *entity, u8 green);

void ST_EntityModifyBlueNoWrap(st_entity *entity, u8 blue);

void ST_EntityModifyAlphaNoWrap(st_entity *entity, u8 alpha);

void ST_EntityModifyColorNoWrap(st_entity *entity,
  u8 red, u8 green, u8 blue, u8 alpha);

/*****************\
|*     Flags     *|
\*****************/
/* Turns on a given flag (sets it to 1) */
/* Takes a pointer to an entity and the id of the flag */
void ST_EntityFlagOn(st_entity *entity, u8 flag);

/* Turns off a given flag (sets it to 0) */
/* Takes a pointer to an entity and the id of the flag */
void ST_EntityFlagOff(st_entity *entity, u8 flag);

/* Toggles the given flag (1->0 and 0->1) */
/* Takes a pointer to an entity and the id of the flag */
void ST_EntityFlagToggle(st_entity *entity, u8 flag);

/* Returns the current state of a flag (1 or 0) */
/* Takes a pointer to an entity and the id of the flag */
u8 ST_EntityFlagGet(st_entity *entity, u8 flag);

#endif
