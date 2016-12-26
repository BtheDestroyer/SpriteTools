/*
* Author: BtheDestroyer
* SpriteTools is an open source 3DS Homebrew Library which can be found here:
* https://github.com/BtheDestroyer/SpriteTools
*/

#include <3ds.h>
#include <sf2d.h>
#include <stdio.h>
#include <spritetools_spritesheet.h>

/*********************************\
|*     Spritesheet Functions     *|
\*********************************/
/* Inits spritesheets */
/* Returns 1 on success and 0 on failure */
int ST_SpritesheetInit(void)
{
  if (!sf2d_init())
    return 0;
  sf2d_set_clear_color(RGBA8(0x20, 0xA0, 0x20, 0xFF));

  return 1;
}

/* Load spritesheet from image */
/* Takes image */
/* Returns pointer to st_spritesheet */
st_spritesheet *ST_SpritesheetCreateSpritesheet(st_image image)
{
  return sf2d_create_texture_mem_RGBA8(image.pixel_data,
    image.width, image.height, TEXFMT_RGBA8, SF2D_PLACE_RAM);
}

/* Free spritesheet */
/* Takes st_spritesheet */
void ST_SpritesheetFreeSpritesheet(st_spritesheet *spritesheet)
{
  sf2d_free_texture(spritesheet);
}
