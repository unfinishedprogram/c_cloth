#include <stdlib.h>
#include <stdio.h>
#include "vector2.h"

Vector2f* Vector2f_create(float x, float y) {

  Vector2f *v = malloc(sizeof(Vector2f));

  v->x = x;
  v->y = y;

  // Vector2f_print(v);

  return v;
}

Vector2f *Vector2f_clone(Vector2f *target) {
  return Vector2f_create(target->x, target->y);
}

void Vector2f_copy(Vector2f *self, Vector2f *other) {
  self->x = other->x;
  self->y = other->y;
}

void Vector2f_add(Vector2f *self, Vector2f *other) {
  self->x += other->x;
  self->y += other->y;
}

void Vector2f_sub(Vector2f *self, Vector2f *other) {
  self->x -= other->x;
  self->y -= other->y;
}

void Vector2f_print(Vector2f *self) {
  printf("(x:%.2f, y:%.2f)\n", self -> x, self -> y);
}

void Vector2f_multiplyScalor(Vector2f *self, float scalor) {
  self->x *= scalor;
  self->y *= scalor;
}

float Vector2f_distSq(Vector2f *a, Vector2f *b) {
  float dx = a->x - b->x;
  float dy = a->y - b->y;

  dx = dx * dx;
  dy = dy * dy;

  return dx+dy;
}

// float Vector2f_dist(Vector2f *a, Vector2f *b) {

// }