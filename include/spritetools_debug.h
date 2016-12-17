/*
* Author: BtheDestroyer
* SpriteTools is an open source 3DS Homebrew Library which can be found here:
* https://github.com/BtheDestroyer/SpriteTools
*/

#ifndef __spritetools_debug_h

#define __spritetools_debug_h
#define ST_DEBUG_MAX_VAR 64

typedef enum {
  VOID,
  CHAR,
  INT,
  U32,
  DOUBLE,
  FLOAT,
  ST_NAMEDPOINTER
} ST_PointerType;

typedef struct NamedPointer {
  char *name;
  void *pointer;
  ST_PointerType type;
} ST_NamedPointer;

/* Sets up debug variables */
/* Returns 1 on success */
/* Returns 0 if DEBUGVars cannot be allocated */
int ST_DebugInit(void);

/* Returns DEBUG State */
int ST_DebugGet(void);

/* Sets DEBUG State to on */
/* Returns DEBUG State */
int ST_DebugSetOn(void);

/* Sets DEBUG State to off */
/* Returns DEBUG State */
int ST_DebugSetOff(void);

/* Prints a string if DEBUG is on */
/* Takes string to print */
/* Returns characters printed */
int ST_DebugPrint(char *str);

/* Adds Variable to debug list */
/* Takes name of variable, pointer to variable (void *), and type of variable */
/* Returns id of var */
/*   Will return -1 if name allocation had an error */
int ST_DebugAddVar(char *name, void *varp, ST_PointerType datatype);

/* Removes Variable with given id from DEBUGVars array */
/* Takes id of variable */
/* Returns 1 when the variable was cleared */
/*   Returns 0 when the variable was already empty */
int ST_DebugRemoveId(int id);

/* Removes Variable with given name from DEBUGVars array */
/* Takes name of variable */
/* Returns 1 when the variable was cleared */
/*   Returns 0 when there is no variable by that name */
int ST_DebugRemoveName(char *name);

/* Removes last variable from DEBUGVars array */
/* Returns index of cleared variable */
/*   Returns -1 when all indexes are open */
int ST_DebugRemoveLast(void);

/* DebugPrints the given id in the DEBUGVars array */
/* Takes id of variable */
/* Returns pointer of var (void *) */
void *ST_DebugPrintVarId(int id);

/* Just runs ST_DebugPrintVarId but sets the cursor position first */
/* Takes id of variable, x of cursor, and y of cursor */
/* Returns pointer of var (void *) */
void *ST_DebugPrintVarIdPosition(int id, int x, int y);

/* DebugPrints the given name in the DEBUGVars array */
/* Takes name of variable in DEBUGVars */
/* Returns pointer of var (void *) */
void *ST_DebugPrintVarName(char *name);

/* Just runs ST_DebugPrintVarName but sets the cursor position first */
/* Takes name of variable, x of cursor, and y of cursor */
/* Returns pointer of var (void *) */
void *ST_DebugPrintVarNamePosition(char *name, int x, int y);

/* DebugPrints all variables in the DEBUGVars array */
void ST_DebugPrintVarAll(void);

/* DebugPrints all variables in the DEBUGVars array at given x and y */
/* Takes x and y of cursor */
void ST_DebugPrintVarAllPosition(int x, int y);

/* DebugPrints all variables in the DEBUGVars array until given id */
/* Takes max id of array to be printed */
void ST_DebugPrintVarAllUntil(int max);

/* DebugPrints all variables in the DEBUGVars array at given x and y */
/* Takes max id of array to be printed and x and y of cursor */
void ST_DebugPrintVarAllUntilPosition(int max, int x, int y);

/* DebugPrints all variables in the DEBUGVars array starting at given id */
/* Takes starting id of array to be printed */
void ST_DebugPrintVarAllFrom(int start);

/* DebugPrints all variables in the DEBUGVars array starting at given id */
/*   at given x and y */
/* Takes starting id of array to be printed and x and y of cursor */
void ST_DebugPrintVarAllFromPosition(int start, int x, int y);

/* DebugPrints all variables in the DEBUGVars array starting at given id */
/*   and ending at given id */
/* Takes starting and ending ids of array to be printed */
void ST_DebugPrintVarAllFromUntil(int start, int max);

/* DebugPrints all variables in the DEBUGVars array starting at given id */
/*   and ending at given id at given x and y */
/* Takes starting and ending ids of array to be printed and x and y of cursor */
void ST_DebugPrintVarAllFromUntilPosition(int start, int max, int x, int y);

/* Scrolls up on the Debug Variable list */
/* Takes number of lines to scroll by */
/* Returns number of lines scrolled */
int ST_DebugScrollUp(int scroll);

/* Scrolls down on the Debug Variable list */
/* Takes number of lines to scroll by */
/* Returns number of lines scrolled */
int ST_DebugScrollDown(int scroll);

/* Returns DEBUGScroll */
int ST_DebugGetScroll(void);

/* Clears the console */
void ST_DebugClear(void);

/* Displays generic debug info if DEBUG is on */
/* Returns characters printed */
int ST_DebugDisplay(void);

#endif