/*
* Author: BtheDestroyer
* SpriteTools is an open source 3DS Homebrew Library which can be found here:
* https://github.com/BtheDestroyer/SpriteTools
*/

#ifdef __cplusplus
extern "C"{
#endif

#ifndef __spritetools_textcolors_h

#define __spritetools_textcolors_h

/**************************************\
|*     Standard Foreground Colors     *|
\**************************************/
/* Sets foreground to black */
void ST_TextBlackFore(void);

/* Sets foreground to red */
void ST_TextRedFore(void);

/* Sets foreground to green */
void ST_TextGreenFore(void);

/* Sets foreground to yellow */
void ST_TextYellowFore(void);

/* Sets foreground to blue */
void ST_TextBlueFore(void);

/* Sets foreground to magenta */
void ST_TextMagentaFore(void);

/* Sets foreground to cyan */
void ST_TextCyanFore(void);

/* Sets foreground to white */
void ST_TextWhiteFore(void);

/* Sets foreground to the default color */
void ST_TextDefaultFore(void);

/**************************************\
|*     Standard Background Colors     *|
\**************************************/
/* Sets background to black */
void ST_TextBlackBack(void);

/* Sets background to red */
void ST_TextRedBack(void);

/* Sets background to green */
void ST_TextGreenBack(void);

/* Sets background to yellow */
void ST_TextYellowBack(void);

/* Sets background to blue */
void ST_TextBlueBack(void);

/* Sets background to magenta */
void ST_TextMagentaBack(void);

/* Sets background to cyan */
void ST_TextCyanBack(void);

/* Sets background to white */
void ST_TextWhiteBack(void);

/* Sets background to the default color */
void ST_TextDefaultBack(void);

/****************************\
|*     Standard Effects     *|
\****************************/

/* Sets foreground to be a brighter shade */
void ST_TextBright(void);

/* Sets foreground to be a darker shade */
void ST_TextDark(void);

/* Sets foreground to be a standard shade */
void ST_TextNoBright(void);

/* Turns on underlining */
void ST_TextUnderline(void);

/* Turns off underlining */
void ST_TextNoUnderline(void);

/* Turns on inverted colors (background <-> foreground) */
void ST_TextNegative(void);

/* Turns off inverted colors (background <-> foreground) */
void ST_TextPositive(void);

/* Turns on strikethrough */
void ST_TextStrikethrough(void);

/* Turns off strikethrough */
void ST_TextNoStrikethrough(void);

/************************\
|*     Default text     *|
\************************/
/* Text with all default settings */
void ST_TextDefault(void);

#endif

#ifdef __cplusplus
}
#endif
