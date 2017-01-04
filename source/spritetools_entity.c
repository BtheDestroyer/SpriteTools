/*
* Author: BtheDestroyer
* SpriteTools is an open source 3DS Homebrew Library which can be found here:
* https://github.com/BtheDestroyer/SpriteTools
*/

#include <3ds.h>
#include <stdlib.h>
#include <spritetools_entity.h>

#define PI 3.1415926535897932384626433832795

/* Takes 2 strings and compares them */
/* Returns 1 on match, 0 on difference */
static int mystrcmp(char *strA, char *strB) /* bc standard strcmp is dumb */
{
  while (*strA == *strB)
  {
    if (!*strA)
      return 1; /* Both strings have matched and reached \0 at the same time */

      strA++, strB++;
  }

  return 0; /* One of the strings didn't match */
}

/***************************\
|*     Entity Creation     *|
\***************************/
/* Returns a pointer to an entity */
/*   Returns NULL if failed */
/* Takes a position and number of animations */
st_entity *ST_EntityCreateEntity(s64 x, s64 y, u8 animCount)
{
  st_entity *tempent = calloc(sizeof(st_entity), 0);

  tempent->animations = calloc(sizeof(st_animation*), animCount);
  tempent->names = calloc(sizeof(char*), animCount);
  tempent->animationCount = 0;
  tempent->xpos = x;
  tempent->ypos = y;
  tempent->scale = 1.0;
  tempent->rotation = 0.0;
  tempent->red = 0;
  tempent->green = 0;
  tempent->blue = 0;
  tempent->alpha = 0;
  tempent->dir = "east";
  tempent->currentAnim = calloc(sizeof(char), 128);

  return tempent;
}

/* Frees frame from memory */
/* Takes a pointer to a frame */
void ST_EntityFreeEntity(st_entity *entity)
{
  int i;
  for (i = 0; i < entity->animationCount; i++)
  {
    ST_AnimationFreeAnimation(entity->animations[i]);
  }
  free(entity);
}

/* Adds an animation to an entity */
/* Takes a pointer to an entity, a pointer to an animation, */
/*   and a name for the animation */
/* Returns 1 on success and 0 on failure */
int ST_EntityAddAnimation(st_entity *entity, st_animation *anim, char *name)
{
  if (entity->animationCount < entity->totalAnims)
  {
    entity->animations[entity->animationCount] = anim;
    entity->names[entity->animationCount] = name;
    entity->animationCount++;
    return 1;
  }
  return 0;
}

/**************************\
|*     Setting Values     *|
\**************************/
/* Sets the x position of a given entity */
/* Takes a pointer to an entity and a position */
void ST_EntitySetXPosition(st_entity *entity, s64 x)
{
  entity->xpos = x;
}

/* Sets the y position of a given entity */
/* Takes a pointer to an entity and a position */
void ST_EntitySetYPosition(st_entity *entity, s64 y)
{
  entity->ypos = y;
}

/* Sets the position of a given entity */
/* Takes a pointer to an entity and a position */
void ST_EntitySetPosition(st_entity *entity, s64 x, s64 y)
{
  entity->xpos = x;
  entity->ypos = y;
}

/* Sets the scale of an entity */
/* Takes a pointer to an entity and a scale */
void ST_EntitySetScale(st_entity *entity, double scale)
{
  entity->scale = scale;
}

/* Sets the rotation of an entity */
/* Takes a pointer to an entity and a rotation value */
void ST_EntitySetRotation(st_entity *entity, double rotation)
{
  entity->rotation = rotation;
}

/* Sets the red value of the color to blend an entity with when rendering */
/* Takes a pointer to an entity and a red value */
void ST_EntitySetRed(st_entity *entity, u8 red)
{
  entity->red = red;
}

/* Sets the green value of the color to blend an entity with when rendering */
/* Takes a pointer to an entity and a green value */
void ST_EntitySetGreen(st_entity *entity, u8 green)
{
  entity->green = green;
}

/* Sets the blue value of the color to blend an entity with when rendering */
/* Takes a pointer to an entity and a blue value */
void ST_EntitySetBlue(st_entity *entity, u8 blue)
{
  entity->blue = blue;
}

/* Sets the alpha value of the color to blend an entity with when rendering */
/* Takes a pointer to an entity and a alpha value */
void ST_EntitySetAlpha(st_entity *entity, u8 alpha)
{
  entity->alpha = alpha;
}

/* Sets the values of the color to blend an entity with when rendering */
/* Takes a pointer to an entity and red, green, blue, and alpha values */
void ST_EntitySetColor(st_entity *entity, u8 red, u8 green, u8 blue, u8 alpha)
{
  entity->red = red;
  entity->green = green;
  entity->blue = blue;
  entity->alpha = alpha;
}

/* Sets the direction of an entity */
/* Takes a pointer to an entity and a direction */
/* Returns 1 on success and 0 on failure */
int ST_EntitySetDirection(st_entity *entity, char *dir)
{
  if (mystrcmp(dir, "east"))
  {
    entity->dir = "east";
    return 1;
  }
  if (mystrcmp(dir, "south east"))
  {
    entity->dir = "south east";
    return 1;
  }
  if (mystrcmp(dir, "south"))
  {
    entity->dir = "south";
    return 1;
  }
  if (mystrcmp(dir, "south west"))
  {
    entity->dir = "south west";
    return 1;
  }
  if (mystrcmp(dir, "west"))
  {
    entity->dir = "west";
    return 1;
  }
  if (mystrcmp(dir, "north west"))
  {
    entity->dir = "north west";
    return 1;
  }
  if (mystrcmp(dir, "north"))
  {
    entity->dir = "north";
    return 1;
  }
  if (mystrcmp(dir, "north east"))
  {
    entity->dir = "north east";
    return 1;
  }

  return 0;
}

/* Sets the direction of an entity */
/* Takes a pointer to an entity and a direction id */
/*   0 = east */
/*   1 = south */
/*   2 = west */
/*   3 = north */
/* Returns 1 on success and 0 on failure */
int ST_EntitySetDirectionId(st_entity *entity, u8 dir)
{
  if (dir == 0)
  {
    entity->dir = "east";
    return 1;
  }
  if (dir == 1)
  {
    entity->dir = "south east";
    return 1;
  }
  if (dir == 2)
  {
    entity->dir = "south";
    return 1;
  }
  if (dir == 3)
  {
    entity->dir = "south west";
    return 1;
  }
  if (dir == 4)
  {
    entity->dir = "west";
    return 1;
  }
  if (dir == 5)
  {
    entity->dir = "north west";
    return 1;
  }
  if (dir == 6)
  {
    entity->dir = "north";
    return 1;
  }
  if (dir == 7)
  {
    entity->dir = "north east";
    return 1;
  }

  return 0;
}

/****************************\
|*     Modifying Values     *|
\****************************/
/* Modifies the x position of a given entity by a given amount */
/* Takes a pointer to an entity and an amount to change the position by */
void ST_EntityModifyXPosition(st_entity *entity, s64 x)
{
  entity->xpos += x;
}

/* Modifies the y position of a given entity by a given amount */
/* Takes a pointer to an entity and an amount to change the position by */
void ST_EntityModifyYPosition(st_entity *entity, s64 y)
{
  entity->ypos += y;
}

/* Modifies the position of a given entity by a given amount */
/* Takes a pointer to an entity and an amount to change the position by */
void ST_EntityModifyPosition(st_entity *entity, s64 x, s64 y)
{
  entity->xpos += x;
  entity->ypos += y;
}

/* Modifies the scale of an entity by a given amount */
/* Takes a pointer to an entity and a value to modify its scale by */
void ST_EntityModifyScale(st_entity *entity, double scale)
{
  entity->scale += scale;
}

/* Modifies the rotation of an entity by a given amount */
/* Takes a pointer to an entity and a value to modify its rotation by */
void ST_EntityModifyRotation(st_entity *entity, double rotation)
{
  entity->rotation += rotation;
  while (entity->rotation - (2 * PI) > 2 * PI)
    entity->rotation -= 2 * PI;
}

/* Modifies the red of the blend color of an entity by a given amount */
/* Takes a pointer to an entity and a red value */
void ST_EntityModifyRed(st_entity *entity, u8 red)
{
  entity->red += red;
}

/* Modifies the green of the blend color of an entity by a given amount */
/* Takes a pointer to an entity and a green value */
void ST_EntityModifyGreen(st_entity *entity, u8 green)
{
  entity->green += green;
}

/* Modifies the blue of the blend color of an entity by a given amount */
/* Takes a pointer to an entity and a blue value */
void ST_EntityModifyBlue(st_entity *entity, u8 blue)
{
  entity->blue += blue;
}

/* Modifies the alpha of the blend color of an entity by a given amount */
/* Takes a pointer to an entity and a alpha value */
void ST_EntityModifyAlpha(st_entity *entity, u8 alpha)
{
  entity->alpha += alpha;
}

/* Modifies the values of the blend color of an entity by a given amount */
/* Takes a pointer to an entity and red, green, blue, and alpha values */
void ST_EntityModifyColor(st_entity *entity,
  u8 red, u8 green, u8 blue, u8 alpha)
{
  entity->red += red;
  entity->green += green;
  entity->blue += blue;
  entity->alpha += alpha;
}

/* Modifies the direction of an entity */
/* Takes a pointer to an entity and a value to turn by */
/*   Positive turns right, negative turns left */
void ST_EntityModifyDirection(st_entity *entity, s8 dir)
{
  if (dir > 0)
  {
    int i;
    for (i = 0; i < dir; i++)
    {
      if (mystrcmp(entity->dir, "east"))
        entity->dir = "south east";
      else if (mystrcmp(entity->dir, "south east"))
        entity->dir = "south";
      else if (mystrcmp(entity->dir, "south"))
        entity->dir = "south west";
      else if (mystrcmp(entity->dir, "south west"))
        entity->dir = "west";
      else if (mystrcmp(entity->dir, "west"))
        entity->dir = "north west";
      else if (mystrcmp(entity->dir, "north west"))
        entity->dir = "north";
      else if (mystrcmp(entity->dir, "north"))
        entity->dir = "north east";
      else if (mystrcmp(entity->dir, "north east"))
        entity->dir = "east";
    }
  }
  if (dir < 0)
  {
    int i;
    for (i = 0; i > dir; i--)
    {
      if (mystrcmp(entity->dir, "east"))
        entity->dir = "south east";
      else if (mystrcmp(entity->dir, "south east"))
        entity->dir = "south";
      else if (mystrcmp(entity->dir, "south"))
        entity->dir = "south west";
      else if (mystrcmp(entity->dir, "south west"))
        entity->dir = "west";
      else if (mystrcmp(entity->dir, "west"))
        entity->dir = "north west";
      else if (mystrcmp(entity->dir, "north west"))
        entity->dir = "north";
      else if (mystrcmp(entity->dir, "north"))
        entity->dir = "north east";
      else if (mystrcmp(entity->dir, "north east"))
        entity->dir = "east";
    }
  }
}

/*****************************************\
|*     Non-Wrapping Modifying Values     *|
\*****************************************/
/* The following are just like the above, but they will not wrap */
/*   (Values greater than the maximum will be reduced to the maximum) */
/*   (Values lower than the minimum will be raised to the minimum) */

void ST_EntityModifyRotationNoWrap(st_entity *entity, double rotation)
{
  entity->rotation += rotation;
  if (entity->rotation > 2 * PI)
    entity->rotation = 2 * PI;
  if (entity->rotation < 0)
    entity->rotation = 0;
}

void ST_EntityModifyRedNoWrap(st_entity *entity, int red)
{
  if (red > 0)
  {
    if (entity->red + red < entity->red)
    {
      entity->red = 255;
    }
    else
    {
      entity->red += red;
    }
  }
  if (red < 0)
  {
    if (entity->red + red > entity->red)
    {
      entity->red = 0;
    }
    else
    {
      entity->red += red;
    }
  }
}

void ST_EntityModifyGreenNoWrap(st_entity *entity, int green)
{
  if (green > 0)
  {
    if (entity->green + green < entity->green)
    {
      entity->green = 255;
    }
    else
    {
      entity->green += green;
    }
  }
  if (green < 0)
  {
    if (entity->green + green > entity->green)
    {
      entity->green = 0;
    }
    else
    {
      entity->green += green;
    }
  }
}

void ST_EntityModifyBlueNoWrap(st_entity *entity, int blue)
{
  if (blue > 0)
  {
    if (entity->blue + blue < entity->blue)
    {
      entity->blue = 255;
    }
    else
    {
      entity->blue += blue;
    }
  }
  if (blue < 0)
  {
    if (entity->blue + blue > entity->blue)
    {
      entity->blue = 0;
    }
    else
    {
      entity->blue += blue;
    }
  }
}

void ST_EntityModifyAlphaNoWrap(st_entity *entity, int alpha)
{
  if (alpha > 0)
  {
    if (entity->alpha + alpha < entity->alpha)
    {
      entity->alpha = 255;
    }
    else
    {
      entity->alpha += alpha;
    }
  }
  if (alpha < 0)
  {
    if (entity->alpha + alpha > entity->alpha)
    {
      entity->alpha = 0;
    }
    else
    {
      entity->alpha += alpha;
    }
  }
}

void ST_EntityModifyColorNoWrap(st_entity *entity,
  int red, int green, int blue, int alpha)
{
  ST_EntityModifyRedNoWrap(entity, red);
  ST_EntityModifyGreenNoWrap(entity, green);
  ST_EntityModifyBlueNoWrap(entity, blue);
  ST_EntityModifyAlphaNoWrap(entity, alpha);
}
