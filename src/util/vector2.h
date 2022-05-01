#ifndef _VECTOR2_H
#define _VECTOR2_H

typedef struct {
  float x;
  float y;
} Vector2f;

Vector2f *Vector2f_create(float x, float y);

Vector2f *Vector2f_clone(Vector2f *target);

void Vector2f_copy(Vector2f *self, Vector2f *other);

void Vector2f_add(Vector2f *self, Vector2f *other);

void Vector2f_sub(Vector2f *self, Vector2f *other);

void Vector2f_print(Vector2f *self);

float Vector2f_distSq(Vector2f *a, Vector2f *b);

void Vector2f_multiplyScalor(Vector2f *self, float scalor);

#endif