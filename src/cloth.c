#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SFML/Graphics.h>
#include "cloth.h"
#include "util/vector2.h"


float CONSTRAINT_LENGTH = 1;
float DRAG = 0.999;
float MULTIPLIER = 1;

Vector2f g = {x:0, y:0.001};
Vector2f *GRAVITY = &g;


ClothVert *ClothVert_create(int x, int y, int pinned) {
  ClothVert* vert = malloc(sizeof(ClothVert));

  vert->pinned = pinned;
  vert->position = Vector2f_create(x, y);
  vert->velocity = Vector2f_create(0, 0);
  return vert;
}


sfVertex ClothVert_toSfVert(ClothVert *self) {
  Vector2f vp = *(self->position);

  sfVector2f position = {vp.x, vp.y};

  sfVertex vert = { position, sfWhite };
  
  return vert;
}

void Cloth_printVerts(Cloth *self) {
  return;
  for(int i = 0; i < self -> vert_count; i++) {
    // printf("Arr Addr:%x\n", self -> verts);
    ClothVert_print(self -> verts[i]);
  }
  for(int i = 0; i < self -> vert_count; i++) {
    printf("Vaddrs:%x\n", self -> verts[i]);
  }
}

void ClothVert_print(ClothVert *self) {
  // printf("Position:\n  ");
  // Vector2f_print(self -> position);
  // printf("Velocity:\n  ");
  // Vector2f_print(self -> velocity);
  // printf(
  //   "Connections for %x :\n\t%x\n\t%x\n\t%x\n\t%x\n", 
  //   self,
  //   self -> connections[0], 
  //   self -> connections[1], 
  //   self -> connections[2], 
  //   self -> connections[3]
  //   );
}

Cloth *Cloth_create(int width, int height) {
  
  Cloth *cloth = malloc(sizeof(Cloth) + (width * height) * sizeof(ClothVert *));

  cloth -> width = width;
  cloth -> height = height;
  cloth -> vert_count = width * height;

  return cloth;
}

void Cloth_populate(Cloth *self) {
  int h = self -> height;
  int w = self -> width;

  printf("Populating %dx%d\n", w, h);
  
  // Instantiating verts
  for(int y = 0; y < h; y++) {
    for(int x = 0; x < w; x++) {
      int pin = ((y == 0) && (x % 10 == 0 || x == w-1));
      ClothVert *v_ptr = ClothVert_create(x, y, pin);
      self -> verts[x + y * h] = v_ptr;
    }
  }
  
  // Connecting the verts...
  for(int y = 0; y < h; y++) {
    for(int x = 0; x < w; x++) {
      ClothVert *v_ptr = self -> verts[x + y * h];

      v_ptr -> connections[0] = 0;
      v_ptr -> connections[1] = 0;
      v_ptr -> connections[2] = 0;
      v_ptr -> connections[3] = 0;

      if(x > 0) v_ptr -> connections[0] = self -> verts[(x - 1) + y * h]; // Left
      if(x < w-1) v_ptr -> connections[1] = self -> verts[(x + 1) + y * h]; // Right
      if(y > 0) v_ptr -> connections[2] = self -> verts[x + (y - 1) * h]; // Top
      if(y < h-1) v_ptr -> connections[3] = self -> verts[x + (y + 1) * h]; // Down
    }
  }
}

void Cloth_fillVertexArray(Cloth *self, sfVertexArray *varr) {
  int count = self->vert_count;
  for(int i = 0; i < count; i++) {
    for(int j = 0; j < 4; j++){
      if(self->verts[i]->connections[j]){
        sfVertexArray_append(varr, ClothVert_toSfVert(self->verts[i]));
        sfVertexArray_append(varr, ClothVert_toSfVert(self->verts[i]->connections[j]));
      }
    }
  }
}

static void ClothVert_applyConstraint(ClothVert *self, ClothVert *other) {
  float dx = self->position->x - other->position->x;
  float dy = self->position->y - other->position->y;
  float dist = dy*dy + dx*dx;
  float multDiv = 1/dist;

  float mult = fmax(dist - CONSTRAINT_LENGTH, 0) * 0.1 * multDiv;

  dx *= mult;
  dy *= mult;

  float sqd = sqrt(dist);

  self->velocity->x -= dx;
  self->velocity->y -= dy;

  return;
}

void Cloth_stepConstrain(Cloth *self) {
  for(int i = 0; i < self -> vert_count; i++) {
    // Applying gravity
    Vector2f_add(self->verts[i]->velocity, GRAVITY);

    // Applying Constraints
    for(int j = 0; j < 4; j++){
      if(self -> verts[i] -> connections[j]) {
        ClothVert_applyConstraint(self -> verts[i], self -> verts[i] -> connections[j]);
      }
    }

    // Applying drag
    Vector2f_multiplyScalor(self->verts[i]->velocity, DRAG);
  }
}

void Cloth_stepMove(Cloth *self) {
  for(int i = 0; i < self -> vert_count; i++) {
    if(!self->verts[i]->pinned){
      self->verts[i]->position->x += self->verts[i]->velocity->x * MULTIPLIER;
      self->verts[i]->position->y += self->verts[i]->velocity->y * MULTIPLIER;
    }
  } 
}