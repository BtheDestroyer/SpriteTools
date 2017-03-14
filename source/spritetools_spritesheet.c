/*
* Author: BtheDestroyer
* SpriteTools is an open source 3DS Homebrew Library which can be found here:
* https://github.com/BtheDestroyer/SpriteTools
*/

#include <3ds.h>
#include "spritetools/spritetools_spritesheet.h"

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
