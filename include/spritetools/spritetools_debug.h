/*
* Author: BtheDestroyer
* SpriteTools is an open source 3DS Homebrew Library which can be found here:
* https://github.com/BtheDestroyer/SpriteTools
*/

#ifdef __cplusplus
extern "C"{
#endif

#ifndef __spritetools_debug_h

#define __spritetools_debug_h

#include <3ds/types.h>

/* Current version of SpriteTools */
#define SPRITETOOLS_VERSION "Release 2.2"

/* Maximum number of variables that can be debugged at once */
#define ST_DEBUG_MAX_VAR 64

/****************************\
|*     Type Definitions     *|
\****************************/

typedef enum {
  UNK,
  VOID,
  PTR,
  CHAR,
  STR,
  INT,
  DOUBLE,
  FLOAT,
  U8,
  U16,
  U32,
  U64,
  S8,
  S16,
  S32,
  S64,
  VU8,
  VU16,
  VU32,
  VU64,
  VS8,
  VS16,
  VS32,
  VS64,
  ST_NAMEDPOINTER
} ST_PointerType;

typedef struct NamedPointer {
  char *name;
  void *pointer;
  ST_PointerType type;
} ST_NamedPointer;

/*****************************\
|*     General Debugging     *|
\*****************************/

/* Sets up debug variables */
/* Returns 1 on success */
/* Returns 0 if DEBUGVars cannot be allocated */
u8 ST_DebugInit(void);

/* Cleans up all modules */
u8 ST_DebugFini(void);

/* Returns DEBUG State */
u8 ST_DebugGet(void);

/* Sets DEBUG State to on */
/* Returns DEBUG State */
u8 ST_DebugSetOn(void);

/* Sets DEBUG State to off */
/* Returns DEBUG State */
u8 ST_DebugSetOff(void);

/* Prints a string if DEBUG is on */
/* Takes string to print */
/* Returns characters printed */
u8 ST_DebugPrint(char *str);

/* Adds Variable to debug list */
/* Takes name of variable, pointer to variable (void *), and type of variable */
/* Returns id of var */
/*   Will return -1 if name allocation had an error */
s8 ST_DebugAddVar(char *name, void *varp, ST_PointerType datatype);

/* Removes Variable with given id from DEBUGVars array */
/* Takes id of variable */
/* Returns 1 when the variable was cleared */
/*   Returns 0 when the variable was already empty */
u8 ST_DebugRemoveId(u8 id);

/* Removes Variable with given name from DEBUGVars array */
/* Takes name of variable */
/* Returns 1 when the variable was cleared */
/*   Returns 0 when there is no variable by that name */
u8 ST_DebugRemoveName(char *name);

/* Removes last variable from DEBUGVars array */
/* Returns index of cleared variable */
/*   Returns -1 when all indexes are open */
s8 ST_DebugRemoveLast(void);

/* DebugPrints the given id in the DEBUGVars array */
/* Takes id of variable */
/* Returns pointer of var (void *) */
void *ST_DebugPrintVarId(u8 id);

/* Just runs ST_DebugPrintVarId but sets the cursor position first */
/* Takes id of variable, x of cursor, and y of cursor */
/* Returns pointer of var (void *) */
void *ST_DebugPrintVarIdPosition(u8 id, s8 x, s8 y);

/* DebugPrints the given name in the DEBUGVars array */
/* Takes name of variable in DEBUGVars */
/* Returns pointer of var (void *) */
void *ST_DebugPrintVarName(char *name);

/* Just runs ST_DebugPrintVarName but sets the cursor position first */
/* Takes name of variable, x of cursor, and y of cursor */
/* Returns pointer of var (void *) */
void *ST_DebugPrintVarNamePosition(char *name, s8 x, s8 y);

/* DebugPrints all variables in the DEBUGVars array */
void ST_DebugPrintVarAll(void);

/* DebugPrints all variables in the DEBUGVars array at given x and y */
/* Takes x and y of cursor */
void ST_DebugPrintVarAllPosition(s8 x, s8 y);

/* DebugPrints all variables in the DEBUGVars array until given id */
/* Takes max id of array to be printed */
void ST_DebugPrintVarAllUntil(u8 max);

/* DebugPrints all variables in the DEBUGVars array at given x and y */
/* Takes max id of array to be printed and x and y of cursor */
void ST_DebugPrintVarAllUntilPosition(u8 max, s8 x, s8 y);

/* DebugPrints all variables in the DEBUGVars array starting at given id */
/* Takes starting id of array to be printed */
void ST_DebugPrintVarAllFrom(u8 start);

/* DebugPrints all variables in the DEBUGVars array starting at given id */
/*   at given x and y */
/* Takes starting id of array to be printed and x and y of cursor */
void ST_DebugPrintVarAllFromPosition(u8 start, s8 x, s8 y);

/* DebugPrints all variables in the DEBUGVars array starting at given id */
/*   and ending at given id */
/* Takes starting and ending ids of array to be printed */
void ST_DebugPrintVarAllFromUntil(u8 start, u8 max);

/* DebugPrints all variables in the DEBUGVars array starting at given id */
/*   and ending at given id at given x and y */
/* Takes starting and ending ids of array to be printed and x and y of cursor */
void ST_DebugPrintVarAllFromUntilPosition(u8 start, u8 max, s8 x, s8 y);

/* Scrolls up on the Debug Variable list */
/* Takes number of lines to scroll by */
/* Returns number of lines scrolled */
u8 ST_DebugScrollUp(s8 scroll);

/* Scrolls down on the Debug Variable list */
/* Takes number of lines to scroll by */
/* Returns number of lines scrolled */
u8 ST_DebugScrollDown(s8 scroll);

/* Returns DEBUGScroll */
u8 ST_DebugGetScroll(void);

/* Clears the console */
void ST_DebugClear(void);

/* Displays generic debug info if DEBUG is on */
/* Returns 1 if debug was on and 0 if it was off */
u16 ST_DebugDisplay(void);

/****************************\
|*     Button Debugging     *|
\****************************/

/* Displays status of A button */
/* Will print [ ] and return 0 if A is up */
/* Will print <A> and return 1 when A is pressed */
/* Will print [A] and return 2 if A is down */
u8 ST_DebugButtonA(void);

/* Displays status of B button */
/* Will print [ ] and return 0 if B is up */
/* Will print <B> and return 1 when B is pressed */
/* Will print [B] and return 2 if B is down */
u8 ST_DebugButtonB(void);

/* Displays status of X button */
/* Will print [ ] and return 0 if X is up */
/* Will print <X> and return 1 when X is pressed */
/* Will print [X] and return 2 if X is down */
u8 ST_DebugButtonX(void);

/* Displays status of Y button */
/* Will print [ ] and return 0 if Y is up */
/* Will print <Y> and return 1 when Y is pressed */
/* Will print [Y] and return 2 if Y is down */
u8 ST_DebugButtonY(void);

/* Displays status of Start button */
/* Will print [  ] and return 0 if Start is up */
/* Will print <St> and return 1 when Start is pressed */
/* Will print [St] and return 2 if Start is down */
u8 ST_DebugButtonStart(void);

/* Displays status of Select button */
/* Will print [  ] and return 0 if Select is up */
/* Will print <Se> and return 1 when Select is pressed */
/* Will print [Se] and return 2 if Select is down */
u8 ST_DebugButtonSelect(void);

/* Displays status of R button */
/* Will print [ ] and return 0 if R is up */
/* Will print <R> and return 1 when R is pressed */
/* Will print [R] and return 2 if R is down */
u8 ST_DebugButtonR(void);

/* Displays status of L button */
/* Will print [ ] and return 0 if L is up */
/* Will print <L> and return 1 when L is pressed */
/* Will print [L] and return 2 if L is down */
u8 ST_DebugButtonL(void);

/* Displays status of Dpad's Up button */
/* Will print [ ] and return 0 if Up is up */
/* Will print <^> and return 1 when Up is pressed */
/* Will print [^] and return 2 if Up is down */
u8 ST_DebugButtonDUp(void);

/* Displays status of Dpad's Right button */
/* Will print [ ] and return 0 if Right is up */
/* Will print <>> and return 1 when Right is pressed */
/* Will print [>] and return 2 if Right is down */
u8 ST_DebugButtonDRight(void);

/* Displays status of Dpad's Down button */
/* Will print [ ] and return 0 if Down is up */
/* Will print <v> and return 1 when Down is pressed */
/* Will print [v] and return 2 if Down is down */
u8 ST_DebugButtonDDown(void);

/* Displays status of Dpad's Left button */
/* Will print [ ] and return 0 if Left is up */
/* Will print <<> and return 1 when Left is pressed */
/* Will print [<] and return 2 if Left is down */
u8 ST_DebugButtonDLeft(void);

/* Displays status of all buttons */
/* Will print a formatted set of all buttons using the above functions */
void ST_DebugButtonFormatted(void);

/* Displays status of all buttons at given position */
/* Takes X and Y of where to start printing from */
/* Will print a formatted set of all buttons using the above functions */
void ST_DebugButtonFormattedAtPosition(s8 x, s8 y);

#endif

#ifdef __cplusplus
}
#endif
