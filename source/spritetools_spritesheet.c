/*
* Author: BtheDestroyer
* SpriteTools is an open source 3DS Homebrew Library which can be found here:
* https://github.com/BtheDestroyer/SpriteTools
*/

#include <3ds.h>
#include "spritetools/spritetools_spritesheet.h"
#include <sfil.h>

/*********************************\
|*     Spritesheet Functions     *|
\*********************************/
/* Load spritesheet from image */
/* Takes image */
/* Returns pointer to st_spritesheet */
st_spritesheet *ST_SpritesheetCreateSpritesheet(const unsigned char *pixel_data,
    unsigned int width, unsigned int height)
{
  return sf2d_create_texture_mem_RGBA8(pixel_data, width, height,
    TEXFMT_RGBA8, SF2D_PLACE_RAM);
}

/* Free spritesheet */
/* Takes st_spritesheet */
void ST_SpritesheetFreeSpritesheet(st_spritesheet *spritesheet)
{
  sf2d_free_texture(spritesheet);
}

/**********************************\
|*     SFILLIB Implimentation     *|
\**********************************/
/* To use these, include sfil.h before spritetools_spritesheet.h */
/* Check out the sfillib example for an example */
/* https://github.com/xerpi/sfillib/tree/master/sample */

/* Load spritesheet from image as a PNG file */
/* Takes buffer */
/* Returns pointer to st_spritesheet */
st_spritesheet *ST_SpritesheetCreateSpritesheetPNG(const void *buffer)
{
  return sfil_load_PNG_buffer(buffer, SF2D_PLACE_RAM);
}

/* Load spritesheet from image as a BMP file */
/* Takes filename */
/* Returns pointer to st_spritesheet */
st_spritesheet *ST_SpritesheetCreateSpritesheetBMP(const void *buffer)
{
  return sfil_load_BMP_buffer(buffer, SF2D_PLACE_RAM);
}

/* Load spritesheet from image as a JPEG file */
/* Takes filename */
/* Returns pointer to st_spritesheet */
st_spritesheet *ST_SpritesheetCreateSpritesheetJPEG(const void *buffer, unsigned long buffer_size)
{
  return sfil_load_JPEG_buffer(buffer, buffer_size, SF2D_PLACE_RAM);
}
