#include "vector.h"

Vector2 newVector2(int x, int y)
{
    Vector2 vec;
    vec.x = x;
    vec.y = y;
    return vec;
}

dVector2 newDVector2(double x, double y)
{
    dVector2 vec;
    vec.x = x;
    vec.y = y;
    return vec;
}

dVector2 convertVector2(Vector2 vec)
{
    dVector2 dVec;
    dVec.x = (double)vec.x;
    dVec.y = (double)vec.y;
    return dVec;
}

Vector2 convertDVector2(Vector2 vec)
{
    Vector2 dVec;
    dVec.x = (int)vec.x;
    dVec.y = (int)vec.y;
    return dVec;
}