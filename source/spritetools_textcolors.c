/*
* Author: BtheDestroyer
* SpriteTools is an open source 3DS Homebrew Library which can be found here:
* https://github.com/BtheDestroyer/SpriteTools
*/

#include <3ds.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <spritetools_textcolors.h>

/**************************************\
|*     Standard Foreground Colors     *|
\**************************************/
/* Sets foreground to black */
void ST_TextBlackFore(void)
{
  printf("\x1b[30m");
}

/* Sets foreground to red */
void ST_TextRedFore(void)
{
  printf("\x1b[31m");
}

/* Sets foreground to green */
void ST_TextGreenFore(void)
{
  printf("\x1b[32m");
}

/* Sets foreground to yellow */
void ST_TextYellowFore(void)
{
  printf("\x1b[33m");
}

/* Sets foreground to blue */
void ST_TextBlueFore(void)
{
  printf("\x1b[34m");
}

/* Sets foreground to magenta */
void ST_TextMagentaFore(void)
{
  printf("\x1b[35m");
}

/* Sets foreground to cyan */
void ST_TextCyanFore(void)
{
  printf("\x1b[36m");
}

/* Sets foreground to white */
void ST_TextWhiteFore(void)
{
  printf("\x1b[37m");
}

/* Sets foreground to the default color */
void ST_TextDefaultFore(void)
{
  printf("\x1b[39m");
}

/**************************************\
|*     Standard Background Colors     *|
\**************************************/
/* Sets background to black */
void ST_TextBlackBack(void)
{
  printf("\x1b[40m");
}

/* Sets background to red */
void ST_TextRedBack(void)
{
  printf("\x1b[41m");
}

/* Sets background to green */
void ST_TextGreenBack(void)
{
  printf("\x1b[42m");
}

/* Sets background to yellow */
void ST_TextYellowBack(void)
{
  printf("\x1b[43m");
}

/* Sets background to blue */
void ST_TextBlueBack(void)
{
  printf("\x1b[44m");
}

/* Sets background to magenta */
void ST_TextMagentaBack(void)
{
  printf("\x1b[45m");
}

/* Sets background to cyan */
void ST_TextCyanBack(void)
{
  printf("\x1b[46m");
}

/* Sets background to white */
void ST_TextWhiteBack(void)
{
  printf("\x1b[47m");
}

/* Sets background to the default color */
void ST_TextDefaultBack(void)
{
  printf("\x1b[49m");
}

/****************************\
|*     Standard Effects     *|
\****************************/

/* Sets foreground to be a brighter shade */
void ST_TextBright(void)
{
  printf("\x1b[1m");
}

/* Sets foreground to be a darker shade */
void ST_TextDark(void)
{
  printf("\x1b[2m");
}

/* Sets foreground to be a standard shade */
void ST_TextNoBright(void)
{
  printf("\x1b[22m");
}

/* Turns on underlining */
void ST_TextUnderline(void)
{
  printf("\x1b[4m");
}

/* Turns off underlining */
void ST_TextNoUnderline(void)
{
  printf("\x1b[24m");
}

/* Turns on inverted colors (background <-> foreground) */
void ST_TextNegative(void)
{
  printf("\x1b[7m");
}

/* Turns off inverted colors (background <-> foreground) */
void ST_TextPositive(void)
{
  printf("\x1b[27m");
}

/* Turns on strikethrough */
void ST_TextStrikethrough(void)
{
  printf("\x1b[9m");
}

/* Turns off strikethrough */
void ST_TextStrikethrough(void)
{
  printf("\x1b[29m");
}

/************************\
|*     Default text     *|
\************************/
/* Text with all default settings*/
void ST_TextDefault(void)
{
  printf("\x1b[0m");
}
