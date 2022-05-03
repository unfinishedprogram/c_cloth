#include <SFML/Graphics.h>
#include <stdio.h>
#include "mouse.h"

static const float MOUSE_DIST = 1.0;
static const float MOUSE_DIST_SQ = MOUSE_DIST * MOUSE_DIST;


void deleteVertex(Cloth *cloth, int index) {
	for(int i = 0; i < 4; i++) {

		ClothVert *otherVert = cloth->verts[index]->connections[i];
		if(!otherVert) continue;

		for(int j = 0; j < 4; j++) {
			if(!otherVert->connections[j]) continue;

			if(otherVert->connections[j] == cloth->verts[index]) {
				otherVert->connections[j] = NULL;
			}
		}

		cloth->verts[index]->connections[i] = NULL;
	}
}

void handleMouseInput(sfRenderWindow *window, Cloth *cloth, int scale) {
	const sfWindow *w = (sfWindow*)window;

	sfVector2i mouse_position = sfMouse_getPosition(w);

	printf("X:%d, y:%d", mouse_position.x, mouse_position.y);


	Vector2f mp = {
		mouse_position.x/scale, mouse_position.y/scale
	};

	int vert_count = cloth->vert_count;
	for(int i = 0; i < vert_count; i++){
		if(cloth->verts[i]) {
			if(Vector2f_distSq(cloth->verts[i]->position, &mp) < MOUSE_DIST_SQ){
				deleteVertex(cloth, i);
			}
		}
	}
}
