/*
* Author: BtheDestroyer
* SpriteTools is an open source 3DS Homebrew Library which can be found here:
* https://github.com/BtheDestroyer/SpriteTools
*/

#include <3ds.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <spritetools_debug.h>
#include <spritetools_input.h>
#include <spritetools_textcolors.h>
#include <spritetools_render.h>

/*******************************\
|*     Debugging Variables     *|
\*******************************/

static int DEBUG = 0; /* Is debug on? This will tell you (and the engine) */
static ST_NamedPointer *DEBUGVars; /* List of variables being debugged */
static int DEBUGScroll = 0; /* Number of variables currently scrolled through */

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

/*****************************\
|*     General Debugging     *|
\*****************************/

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

/* Cleans up debug variables */
/* Returns 1 on success */
/* Returns 0 if DEBUGVars cannot be allocated */
int ST_DebugFini(void)
{
  free(DEBUGVars);

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
    case STR :
    sprintf(tempstr, "%.2d. char*  %s = %s", id, DEBUGVars[id].name,
      *(char **)DEBUGVars[id].pointer);
    break;
    case INT :
    sprintf(tempstr, "%.2d. int    %s = %d", id, DEBUGVars[id].name,
      *(int *)DEBUGVars[id].pointer);
    break;
    case DOUBLE :
    sprintf(tempstr, "%.2d. double %s = %f", id, DEBUGVars[id].name,
      *(double *)DEBUGVars[id].pointer);
    break;
    case FLOAT :
    sprintf(tempstr, "%.2d. float  %s = %f", id, DEBUGVars[id].name,
      *(float *)DEBUGVars[id].pointer);
    break;

    case U8 :
    sprintf(tempstr, "%.2d. u8     %s = %" PRIu8, id, DEBUGVars[id].name,
      *(u8 *)DEBUGVars[id].pointer);
    break;
    case U16 :
    sprintf(tempstr, "%.2d. u16    %s = %" PRIu16, id, DEBUGVars[id].name,
      *(u16 *)DEBUGVars[id].pointer);
    break;
    case U32 :
    sprintf(tempstr, "%.2d. u32    %s = %" PRIu32, id, DEBUGVars[id].name,
      *(u32 *)DEBUGVars[id].pointer);
    break;
    case U64 :
    sprintf(tempstr, "%.2d. u64    %s = %" PRIu64, id, DEBUGVars[id].name,
      *(u64 *)DEBUGVars[id].pointer);
    break;

    case S8 :
    sprintf(tempstr, "%.2d. s8     %s = %" PRId8, id, DEBUGVars[id].name,
      *(s8 *)DEBUGVars[id].pointer);
    break;
    case S16 :
    sprintf(tempstr, "%.2d. s16    %s = %" PRId16, id, DEBUGVars[id].name,
      *(s16 *)DEBUGVars[id].pointer);
    break;
    case S32 :
    sprintf(tempstr, "%.2d. s32    %s = %" PRId32, id, DEBUGVars[id].name,
      *(s32 *)DEBUGVars[id].pointer);
    break;
    case S64 :
    sprintf(tempstr, "%.2d. s64    %s = %" PRId64, id, DEBUGVars[id].name,
      *(s64 *)DEBUGVars[id].pointer);
    break;

    case VU8 :
    sprintf(tempstr, "%.2d. vu8    %s = %" PRIu8, id, DEBUGVars[id].name,
      *(vu8 *)DEBUGVars[id].pointer);
    break;
    case VU16 :
    sprintf(tempstr, "%.2d. vu16   %s = %" PRIu16, id, DEBUGVars[id].name,
      *(vu16 *)DEBUGVars[id].pointer);
    break;
    case VU32 :
    sprintf(tempstr, "%.2d. vu32   %s = %" PRIu32, id, DEBUGVars[id].name,
      *(vu32 *)DEBUGVars[id].pointer);
    break;
    case VU64 :
    sprintf(tempstr, "%.2d. vu64   %s = %" PRIu64, id, DEBUGVars[id].name,
      *(vu64 *)DEBUGVars[id].pointer);
    break;

    case VS8 :
    sprintf(tempstr, "%.2d. vs8    %s = %" PRIu8, id, DEBUGVars[id].name,
      *(vs8 *)DEBUGVars[id].pointer);
    break;
    case VS16 :
    sprintf(tempstr, "%.2d. vs16   %s = %" PRIu16, id, DEBUGVars[id].name,
      *(vs16 *)DEBUGVars[id].pointer);
    break;
    case VS32 :
    sprintf(tempstr, "%.2d. vs32   %s = %" PRIu32, id, DEBUGVars[id].name,
      *(vs32 *)DEBUGVars[id].pointer);
    break;
    case VS64 :
    sprintf(tempstr, "%.2d. vs64   %s = %" PRIu64, id, DEBUGVars[id].name,
      *(vs64 *)DEBUGVars[id].pointer);
    break;

    case ST_NAMEDPOINTER :
    sprintf(tempstr, "%.2d. ST_NP  %s = %p", id, DEBUGVars[id].name,
      *(void **)DEBUGVars[id].pointer);
    break;
    case VOID :
    sprintf(tempstr, "%.2d. VOID   %s = %p", id, DEBUGVars[id].name,
      *(void **)DEBUGVars[id].pointer);
    break;
    default :
    sprintf(tempstr, "%.2d. UNK   %s = %p", id, DEBUGVars[id].name,
      *(void **)DEBUGVars[id].pointer);
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
  printf("\x1b[2J\x1b[H");
}

/* Displays generic debug info if DEBUG is on */
/* Returns 1 if debug was on and 0 if it was off */
int ST_DebugDisplay(void)
{
  int i;
  char tempstr[128];

  if (!ST_DebugGet())
    return 0;

  for (i = 0; i < 22; i++)
    printf("\x1b[%d;1H{                                    }", 2 + i);

  ST_DebugPrint("\x1b[2;2HSPRITETOOLS DEBUG");
  ST_DebugPrint("\x1b[3;2HVersion: ");
  ST_TextGreenFore();
  ST_DebugPrint(SPRITETOOLS_VERSION);
  ST_TextDefault();
  ST_DebugPrint("\x1b[4;2HVariables in Debug:");
  ST_DebugPrintVarAllFromUntilPosition(ST_DebugGetScroll(),
    10 + ST_DebugGetScroll(), 2, 5);
  ST_DebugPrint("\x1b[15;2HButtons:");
  ST_DebugButtonFormattedAtPosition(4, 16);
  ST_DebugPrint("\x1b[15;17HTouchscreen:");
  sprintf(tempstr,"\x1b[16;17HCurrent: (%d,%d)",
    ST_InputTouchX(), ST_InputTouchY());
  ST_DebugPrint(tempstr);
  sprintf(tempstr,"\x1b[17;17HOrigin: (%d,%d)", ST_InputTouchOriginX(),
    ST_InputTouchOriginY());
  ST_DebugPrint(tempstr);
  sprintf(tempstr,"\x1b[18;17HDist: %d", ST_InputTouchDistance());
  ST_DebugPrint(tempstr);
  sprintf(tempstr,"\x1b[18;27HLen: %d", ST_InputTouchLength());
  ST_DebugPrint(tempstr);
  sprintf(tempstr, "\x1b[20;2HMemory: %9.3f KB used\x1b[21;10H%9.3f KB total\
    \x1b[22;10H%9.3f KB left",
    osGetMemRegionUsed(MEMREGION_ALL) * 0.0001,
    osGetMemRegionSize(MEMREGION_ALL) * 0.0001,
    osGetMemRegionFree(MEMREGION_ALL) * 0.0001);
  ST_DebugPrint(tempstr);
  sprintf(tempstr,"\x1b[23;2HFPS: %f", ST_RenderFPS());
  ST_DebugPrint(tempstr);

  return 1;
}


/****************************\
|*     Button Debugging     *|
\****************************/

/* Displays status of A button */
/* Will print [ ] and return 0 if A is up */
/* Will print <A> and return 1 when A is pressed */
/* Will print [A] and return 2 if A is down */
int ST_DebugButtonA(void)
{
  if (ST_InputButtonPressed(KEY_A))
  {
    ST_DebugPrint("<A>");
    return 1;
  }
  if (ST_InputButtonDown(KEY_A))
  {
    ST_DebugPrint("[A]");
    return 2;
  }

  ST_DebugPrint("[ ]");
  return 0;
}

/* Displays status of B button */
/* Will print [ ] and return 0 if B is up */
/* Will print <B> and return 1 when B is pressed */
/* Will print [B] and return 2 if B is down */
int ST_DebugButtonB(void)
{
  if (ST_InputButtonPressed(KEY_B))
  {
    ST_DebugPrint("<B>");
    return 1;
  }
  if (ST_InputButtonDown(KEY_B))
  {
    ST_DebugPrint("[B]");
    return 2;
  }

  ST_DebugPrint("[ ]");
  return 0;
}

/* Displays status of X button */
/* Will print [ ] and return 0 if X is up */
/* Will print <X> and return 1 when X is pressed */
/* Will print [X] and return 2 if X is down */
int ST_DebugButtonX(void)
{
  if (ST_InputButtonPressed(KEY_X))
  {
    ST_DebugPrint("<X>");
    return 1;
  }
  if (ST_InputButtonDown(KEY_X))
  {
    ST_DebugPrint("[X]");
    return 2;
  }

  ST_DebugPrint("[ ]");
  return 0;
}

/* Displays status of Y button */
/* Will print [ ] and return 0 if Y is up */
/* Will print <Y> and return 1 when Y is pressed */
/* Will print [Y] and return 2 if Y is down */
int ST_DebugButtonY(void)
{
  if (ST_InputButtonPressed(KEY_Y))
  {
    ST_DebugPrint("<Y>");
    return 1;
  }
  if (ST_InputButtonDown(KEY_Y))
  {
    ST_DebugPrint("[Y]");
    return 2;
  }

  ST_DebugPrint("[ ]");
  return 0;
}

/* Displays status of Start button */
/* Will print [  ] and return 0 if Start is up */
/* Will print <St> and return 1 when Start is pressed */
/* Will print [St] and return 2 if Start is down */
int ST_DebugButtonStart(void)
{
  if (ST_InputButtonPressed(KEY_START))
  {
    ST_DebugPrint("<St>");
    return 1;
  }
  if (ST_InputButtonDown(KEY_START))
  {
    ST_DebugPrint("[St]");
    return 2;
  }

  ST_DebugPrint("[  ]");
  return 0;
}

/* Displays status of Select button */
/* Will print [  ] and return 0 if Select is up */
/* Will print <Se> and return 1 when Select is pressed */
/* Will print [Se] and return 2 if Select is down */
int ST_DebugButtonSelect(void)
{
  if (ST_InputButtonPressed(KEY_SELECT))
  {
    ST_DebugPrint("<Se>");
    return 1;
  }
  if (ST_InputButtonDown(KEY_SELECT))
  {
    ST_DebugPrint("[Se]");
    return 2;
  }

  ST_DebugPrint("[  ]");
  return 0;
}

/* Displays status of R button */
/* Will print [ ] and return 0 if R is up */
/* Will print <R> and return 1 when R is pressed */
/* Will print [R] and return 2 if R is down */
int ST_DebugButtonR(void)
{
  if (ST_InputButtonPressed(KEY_R))
  {
    ST_DebugPrint("<R>");
    return 1;
  }
  if (ST_InputButtonDown(KEY_R))
  {
    ST_DebugPrint("[R]");
    return 2;
  }

  ST_DebugPrint("[ ]");
  return 0;
}

/* Displays status of L button */
/* Will print [ ] and return 0 if L is up */
/* Will print <L> and return 1 when L is pressed */
/* Will print [L] and return 2 if L is down */
int ST_DebugButtonL(void)
{
  if (ST_InputButtonPressed(KEY_L))
  {
    ST_DebugPrint("<L>");
    return 1;
  }
  if (ST_InputButtonDown(KEY_L))
  {
    ST_DebugPrint("[L]");
    return 2;
  }

  ST_DebugPrint("[ ]");
  return 0;
}

/* Displays status of Dpad's Up button */
/* Will print [ ] and return 0 if Up is up */
/* Will print <^> and return 1 when Up is pressed */
/* Will print [^] and return 2 if Up is down */
int ST_DebugButtonDUp(void)
{
  if (ST_InputButtonPressed(KEY_DUP))
  {
    ST_DebugPrint("<^>");
    return 1;
  }
  if (ST_InputButtonDown(KEY_DUP))
  {
    ST_DebugPrint("[^]");
    return 2;
  }

  ST_DebugPrint("[ ]");
  return 0;
}

/* Displays status of Dpad's Right button */
/* Will print [ ] and return 0 if Right is up */
/* Will print <>> and return 1 when Right is pressed */
/* Will print [>] and return 2 if Right is down */
int ST_DebugButtonDRight(void)
{
  if (ST_InputButtonPressed(KEY_DRIGHT))
  {
    ST_DebugPrint("<>>");
    return 1;
  }
  if (ST_InputButtonDown(KEY_DRIGHT))
  {
    ST_DebugPrint("[>]");
    return 2;
  }

  ST_DebugPrint("[ ]");
  return 0;
}

/* Displays status of Dpad's Down button */
/* Will print [ ] and return 0 if Down is up */
/* Will print <v> and return 1 when Down is pressed */
/* Will print [v] and return 2 if Down is down */
int ST_DebugButtonDDown(void)
{
  if (ST_InputButtonPressed(KEY_DDOWN))
  {
    ST_DebugPrint("<v>");
    return 1;
  }
  if (ST_InputButtonDown(KEY_DDOWN))
  {
    ST_DebugPrint("[v]");
    return 2;
  }

  ST_DebugPrint("[ ]");
  return 0;
}

/* Displays status of Dpad's Left button */
/* Will print [ ] and return 0 if Left is up */
/* Will print <<> and return 1 when Left is pressed */
/* Will print [<] and return 2 if Left is down */
int ST_DebugButtonDLeft(void)
{
  if (ST_InputButtonPressed(KEY_DLEFT))
  {
    ST_DebugPrint("<<>");
    return 1;
  }
  if (ST_InputButtonDown(KEY_DLEFT))
  {
    ST_DebugPrint("[<]");
    return 2;
  }

  ST_DebugPrint("[ ]");
  return 0;
}

/* Displays status of all buttons */
/* Will print a formatted set of all buttons using the above functions */
void ST_DebugButtonFormatted(void)
{
  ST_DebugButtonDUp();
  ST_DebugButtonDRight();
  ST_DebugButtonDDown();
  ST_DebugButtonDLeft();

  ST_DebugPrint("\n");
  ST_DebugButtonA();
  ST_DebugButtonB();
  ST_DebugButtonX();
  ST_DebugButtonY();

  ST_DebugPrint("\n");
  ST_DebugButtonL();
  ST_DebugButtonR();

  ST_DebugPrint("\n");
  ST_DebugButtonStart();
  ST_DebugButtonSelect();
}

/* Displays status of all buttons at given position */
/* Takes X and Y of where to start printing from */
/* Will print a formatted set of all buttons using the above functions */
void ST_DebugButtonFormattedAtPosition(int x, int y)
{
  char tempstr[128] = {0};

  sprintf(tempstr, "\x1b[%d;%dH", y, x);
  ST_DebugPrint(tempstr);
  ST_DebugButtonDUp();
  ST_DebugButtonDRight();
  ST_DebugButtonDDown();
  ST_DebugButtonDLeft();

  sprintf(tempstr, "\x1b[%d;%dH", y + 1, x);
  ST_DebugPrint(tempstr);
  ST_DebugButtonA();
  ST_DebugButtonB();
  ST_DebugButtonX();
  ST_DebugButtonY();

  sprintf(tempstr, "\x1b[%d;%dH", y + 2, x);
  ST_DebugPrint(tempstr);
  ST_DebugButtonL();
  ST_DebugButtonR();

  sprintf(tempstr, "\x1b[%d;%dH", y + 3, x);
  ST_DebugPrint(tempstr);
  ST_DebugButtonStart();
  ST_DebugButtonSelect();
}
