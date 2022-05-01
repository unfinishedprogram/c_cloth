#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include <SFML/Graphics.h>

#include "cloth.h"

static int TICKS_PER_FRAME = 12;

int main (void) {
  // Initalizing rendering context
  sfVideoMode mode = {150, 150, 32};
  sfRenderWindow* window;
  window = sfRenderWindow_create(mode, "Window", sfResize | sfClose, NULL);

  Cloth* cloth = Cloth_create(100, 100);

  Cloth_populate(cloth);

  Cloth_printVerts(cloth);

  sfVertexArray *varr = sfVertexArray_create();

  sfVertexArray_setPrimitiveType(varr, sfLines);
  sfClock *clock = sfClock_create();


  while (sfRenderWindow_isOpen(window)){


    // Process events
    sfEvent event;

    // Iterate over all events, if closed event found, kill
    while(sfRenderWindow_pollEvent(window, &event)) {
      if (event.type == sfEvtClosed) sfRenderWindow_close(window);
    }




    int i = TICKS_PER_FRAME;
    
    sfClock_restart(clock);

    while(i--){
      Cloth_stepConstrain(cloth);
      Cloth_stepMove(cloth);
    }

    long delta = sfClock_getElapsedTime(clock).microseconds;

    sfClock_restart(clock);

    float tps = TICKS_PER_FRAME * 1000/(delta/1000.0);


    // Clear and show keep the window open
    sfRenderWindow_clear(window, sfBlack);
    
    sfVertexArray_clear(varr);
    Cloth_fillVertexArray(cloth, varr);
    sfRenderWindow_drawVertexArray(window, varr, NULL);
    sfRenderWindow_display(window);

    delta = sfClock_getElapsedTime(clock).microseconds;

    printf("fps:%0.2f\ntps:%0.2f\n", 1000/(delta/1000.0), tps);

  }

  // Clean up
  sfRenderWindow_destroy(window);
  return 0;
}