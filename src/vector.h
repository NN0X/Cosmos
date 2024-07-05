#ifndef VECTOR_H
#define VECTOR_H

struct Vector2
{
    int x;
    int y;
} typedef Vector2;

struct dVector2
{
    double x;
    double y;
} typedef dVector2;

Vector2 newVector2(int x, int y);
dVector2 newDVector2(double x, double y);

dVector2 convertVector2(Vector2 vec);
Vector2 convertDVector2(Vector2 vec);

#endif