#ifndef _CLOTH_H
#define _CLOTH_H

#include "util/vector2.h"
#include <SFML/Graphics.h>

typedef struct ClothVert ClothVert;

struct ClothVert{
  int pinned;
  Vector2f *position;
  Vector2f *velocity;
  ClothVert *connections[4];
};


typedef struct {
  int vert_count;
  int width;
  int height;
  ClothVert *verts[];
} Cloth;

Cloth *Cloth_create(int width, int height);
ClothVert *ClothVert_create(int x, int y, int pinned);
void ClothVert_init(ClothVert *self, int x, int y);
void Cloth_populate(Cloth *self);
void ClothVert_print(ClothVert *self);
void Cloth_printVerts(Cloth *self);
void Cloth_fillVertexArray(Cloth *self, sfVertexArray *varr);
void Cloth_stepMove(Cloth *self);
void Cloth_stepConstrain(Cloth *self);
#endif