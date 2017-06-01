/*
* Author: BtheDestroyer
* SpriteTools is an open source 3DS Homebrew Library which can be found here:
* https://github.com/BtheDestroyer/SpriteTools
*/

#include <3ds.h>
#include "spritetools/spritetools_splash.h"
#include "spritetools/spritetools_time.h"
#include "splash_png.h"

/************************\
|*     Splashscreen     *|
\************************/
/* Displays splashscreen */
/* Takes time to display in ms */
void ST_Splashscreen(u64 time)
{
  u8 fade = 0;
  u32 bg = ST_RenderGetBackground();

  st_spritesheet *splash_s = ST_SpritesheetCreateSpritesheetPNG(splash_png);

  ST_RenderSetBackground(0x00, 0x00, 0x00);

  /* Splash for 4 seconds */
  while (ST_TimeRunning() <= time)
  {
    if (ST_TimeRunning() <= 255)
      fade = ST_TimeRunning(); /* Fade in */
    else if (time - ST_TimeRunning() <= 255)
      fade = time - ST_TimeRunning(); /* Fade out */
    else
      fade = 255; /* Mid splash */

    ST_RenderStartFrame(GFX_TOP);
    ST_RenderSpriteAdvanced(splash_s, 0, 0, 400, 240, 200, 120,
      1.0, 0.0, 255, 255, 255, fade);
    ST_RenderEndRender();
  }

  /* Clean frame */
  ST_RenderStartFrame(GFX_TOP);
  ST_RenderEndRender();

  /* Free splashscreen */
  ST_SpritesheetFreeSpritesheet(splash_s);

  /* Return original background */
  ST_RenderSetBackground(RGBA8_GET_R(bg), RGBA8_GET_G(bg), RGBA8_GET_B(bg));
}
