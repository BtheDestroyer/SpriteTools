/*
* Author: BtheDestroyer
* SpriteTools is an open source 3DS Homebrew Library which can be found here:
* https://github.com/BtheDestroyer/SpriteTools
*/

#include <3ds.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <spritetools_debug.h>

static int DEBUG = 0;
static ST_NamedPointer *DEBUGVars;
static int DEBUGScroll = 0;

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

/* Sets up debug variables */
/* Returns 1 on success */
/* Returns 0 if DEBUGVars cannot be allocated */
int ST_DebugInit(void)
{
  DEBUGVars = calloc(ST_DEBUG_MAX_VAR, sizeof(ST_NamedPointer));
  if (!DEBUGVars)
    return 0;

  return 1;
}

/* Returns DEBUG State */
int ST_DebugGet(void)
{
  return DEBUG;
}

/* Sets DEBUG State to on */
/* Returns DEBUG State */
int ST_DebugSetOn(void)
{
  DEBUG = 1;
  return DEBUG;
}

/* Sets DEBUG State to off */
/* Returns DEBUG State */
int ST_DebugSetOff(void)
{
  DEBUG = 0;
  return DEBUG;
}

/* Prints a string if DEBUG is on */
/* Takes string to print */
/* Returns characters printed */
int ST_DebugPrint(char *str)
{
  if (DEBUG)
    return printf(str);

  return -1;
}

/* Adds Variable to debug list */
/* Takes name of variable, pointer to variable (void *), and type of variable */
/* Returns id of var */
/*   Will return -1 if name allocation had an error */
int ST_DebugAddVar(char *name, void *varp, ST_PointerType datatype)
{
  /* ID of variable */
  int id = 0;

  while (DEBUGVars[id].pointer) /* Loop until an open index is found */
  {
    id++;
  }

  /* An empty index was found */
  /* Set Variable Pointer of node to given address */
  DEBUGVars[id].pointer = varp;
  
  /* Allocates memory for name of node */
  DEBUGVars[id].name = calloc((size_t) 128, sizeof(char));
  if (!DEBUGVars[id].name) /* If name was not allocated correctly... */
    return -1; /* Stop and return -1. Something went wrong */

  /* Sets type of pointer */
  DEBUGVars[id].type = datatype;

  /* Sets name */
  strcpy(DEBUGVars[id].name, name);

  return id;
}

/* Removes Variable with given id from DEBUGVars array */
/* Takes id of variable */
/* Returns 1 when the variable was cleared */
/*   Returns 0 when the variable was already empty */
int ST_DebugRemoveId(int id)
{
  if (DEBUGVars[id].name == NULL && DEBUGVars[id].pointer == NULL)
    return 0;

  DEBUGVars[id].name = NULL;
  DEBUGVars[id].pointer = NULL;
  DEBUGVars[id].type = VOID;
  return 1;
}

/* Removes Variable with given name from DEBUGVars array */
/* Takes name of variable */
/* Returns 1 when the variable was cleared */
/*   Returns 0 when there is no variable by that name */
int ST_DebugRemoveName(char *name)
{
  int i; /* For loop index */

  for (i = 0; i < ST_DEBUG_MAX_VAR; i++)
  {
    if (mystrcmp(DEBUGVars[i].name, name))
    { /* Name was found! Clear that index */
      return ST_DebugRemoveId(i);
    } 
  }

  return 0;
}

/* Removes last variable from DEBUGVars array */
/* Returns index of cleared variable */
/*   Returns -1 when all indexes are open */
int ST_DebugRemoveLast(void)
{
  int i; /* For loop index */
  int last = -1; /* last filled index */

  for (i = 0; i < ST_DEBUG_MAX_VAR; i++)
  {
    if (DEBUGVars[i].name || DEBUGVars[i].pointer)
    { /* Current index filled. Set last */
      last = i;
    }
  }

  if (last != -1)
  {
    ST_DebugRemoveId(last);
  }

  return last;
}

/* DebugPrints the given id in the DEBUGVars array */
/* Takes id of variable */
/* Returns pointer of var (void *) */
void *ST_DebugPrintVarId(int id)
{
  char tempstr[128];

  switch (DEBUGVars[id].type)
  {
    case CHAR :
    sprintf(tempstr, "%.2d. char   %s = %c", id, DEBUGVars[id].name,
      *(char *)DEBUGVars[id].pointer);
    break;
    case INT :
    sprintf(tempstr, "%.2d. int    %s = %d", id, DEBUGVars[id].name,
      *(int *)DEBUGVars[id].pointer);
    break;
    case U32 :
    sprintf(tempstr, "%.2d. u32    %s = %lu", id, DEBUGVars[id].name,
      *(u32 *)DEBUGVars[id].pointer);
    break;
    case DOUBLE :
    sprintf(tempstr, "%.2d. double %s = %f", id, DEBUGVars[id].name,
      *(double *)DEBUGVars[id].pointer);
    break;
    case FLOAT :
    sprintf(tempstr, "%.2d. float  %s = %f", id, DEBUGVars[id].name,
      *(float *)DEBUGVars[id].pointer);
    break;
    case ST_NAMEDPOINTER :
    sprintf(tempstr, "%.2d. ST_NP  %s = %p", id, DEBUGVars[id].name,
      DEBUGVars[id].pointer);
    break;
    case VOID :
    sprintf(tempstr, "%.2d. VOID  %s = %p", id, DEBUGVars[id].name,
      DEBUGVars[id].pointer);
    break;
    default :
    sprintf(tempstr, "%.2d. UNK   %s = %p", id, DEBUGVars[id].name,
      DEBUGVars[id].pointer);
    break;
  }
  
  ST_DebugPrint(tempstr);
  return DEBUGVars[id].pointer;
}

/* Just runs ST_DebugPrintVarId but sets the cursor position first */
/* Takes id of variable, x of cursor, and y of cursor */
/* Returns pointer of var (void *) */
void *ST_DebugPrintVarIdPosition(int id, int x, int y)
{
  printf ("\x1b[%d;%dH", y, x);
  return ST_DebugPrintVarId(id);
}

/* DebugPrints the given name in the DEBUGVars array */
/* Takes name of variable in DEBUGVars */
/* Returns pointer of var (void *) */
void *ST_DebugPrintVarName(char *name)
{
  int i; /* For loop index */

  for (i = 0; i < ST_DEBUG_MAX_VAR; i++)
  {
    if (mystrcmp(DEBUGVars[i].name, name))
      return ST_DebugPrintVarId(i); /* Name was found! Print that index */
  }
  return NULL; /* Returns NULL if name is not found in array */
}

/* Just runs ST_DebugPrintVarName but sets the cursor position first */
/* Takes name of variable, x of cursor, and y of cursor */
/* Returns pointer of var (void *) */
void *ST_DebugPrintVarNamePosition(char *name, int x, int y)
{
  printf ("\x1b[%d;%dH", y, x);
  return ST_DebugPrintVarName(name);
}

/* DebugPrints all variables in the DEBUGVars array */
void ST_DebugPrintVarAll(void)
{
  int i;
  for (i = 0; i < ST_DEBUG_MAX_VAR; i++)
  {
    ST_DebugPrintVarId(i);
    putchar ('\n');
  }
}

/* DebugPrints all variables in the DEBUGVars array at given x and y */
/* Takes x and y of cursor */
void ST_DebugPrintVarAllPosition(int x, int y)
{
  int i;
  for (i = 0; i < ST_DEBUG_MAX_VAR; i++)
  {
    printf ("\x1b[%d;%dH", y + i, x);
    ST_DebugPrintVarId(i);
  }
}

/* DebugPrints all variables in the DEBUGVars array until given id */
/* Takes max id of array to be printed */
void ST_DebugPrintVarAllUntil(int max)
{
  int i;
  for (i = 0; i < ST_DEBUG_MAX_VAR && i < max; i++)
  {
    ST_DebugPrintVarId(i);
    putchar ('\n');
  }
}

/* DebugPrints all variables in the DEBUGVars array at given x and y */
/* Takes max id of array to be printed and x and y of cursor */
void ST_DebugPrintVarAllUntilPosition(int max, int x, int y)
{
  int i;
  for (i = 0; i < ST_DEBUG_MAX_VAR && i < max; i++)
  {
    printf ("\x1b[%d;%dH", y + i, x);
    ST_DebugPrintVarId(i);
  }
}

/* DebugPrints all variables in the DEBUGVars array starting at given id */
/* Takes starting id of array to be printed */
void ST_DebugPrintVarAllFrom(int start)
{
  int i;
  for (i = 0; start + i < ST_DEBUG_MAX_VAR; i++)
  {
    ST_DebugPrintVarId(start + i);
    putchar ('\n');
  }
}

/* DebugPrints all variables in the DEBUGVars array starting at given id */
/*   at given x and y */
/* Takes starting id of array to be printed and x and y of cursor */
void ST_DebugPrintVarAllFromPosition(int start, int x, int y)
{
  int i;
  for (i = 0; start + i < ST_DEBUG_MAX_VAR; i++)
  {
    printf ("\x1b[%d;%dH", y + i, x);
    ST_DebugPrintVarId(start + i);
  }
}

/* DebugPrints all variables in the DEBUGVars array starting at given id */
/*   and ending at given id */
/* Takes starting and ending ids of array to be printed */
void ST_DebugPrintVarAllFromUntil(int start, int max)
{
  int i;
  for (i = 0; start + i < ST_DEBUG_MAX_VAR && start + i < max; i++)
  {
    ST_DebugPrintVarId(start + i);
    putchar ('\n');
  }
}

/* DebugPrints all variables in the DEBUGVars array starting at given id */
/*   and ending at given id at given x and y */
/* Takes starting and ending ids of array to be printed and x and y of cursor */
void ST_DebugPrintVarAllFromUntilPosition(int start, int max, int x, int y)
{
  int i;
  for (i = 0; start + i < ST_DEBUG_MAX_VAR && start + i < max; i++)
  {
    printf ("\x1b[%d;%dH", y + i, x);
    ST_DebugPrintVarId(start + i);
  }
}

/* Scrolls up on the Debug Variable list */
/* Takes number of lines to scroll by */
/* Returns number of lines scrolled */
int ST_DebugScrollUp(int scroll)
{
  int i;
  for (i = 0; i < scroll && DEBUGScroll > 0; i++)
    DEBUGScroll--;
  
  return i;
}

/* Scrolls down on the Debug Variable list */
/* Takes number of lines to scroll by */
/* Returns number of lines scrolled */
int ST_DebugScrollDown(int scroll)
{
  int i;
  for (i = 0; i < scroll && DEBUGScroll + 1 < ST_DEBUG_MAX_VAR; i++)
    DEBUGScroll++;
  
  return i;
}

/* Returns DEBUGScroll */
int ST_DebugGetScroll(void)
{
  return DEBUGScroll;
}

/* Clears the console */
void ST_DebugClear(void)
{
  printf("\x1b[0;0H\033[H\033[J");
}

/* Displays generic debug info if DEBUG is on */
/* Returns characters printed */
int ST_DebugDisplay(void)
{
  int c = 0; /* Character counter */
  ST_DebugClear();
  c += ST_DebugPrint("\x1b[2;2HSPRITETOOLS DEBUG");
  c += ST_DebugPrint("\x1b[3;2HVersion: Beta 2.0");
  c += ST_DebugPrint("\x1b[4;2HVariables in Debug:");
  ST_DebugPrintVarAllFromUntilPosition(DEBUGScroll, 10 + DEBUGScroll, 2, 5);

  return c;
}
