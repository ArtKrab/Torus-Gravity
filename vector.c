#include "vector.h"
#include <math.h>

double vector_len (Vector vec) {
    return sqrt((vec.x)*(vec.x)+(vec.y)*(vec.y));
}

Vector vector_x_double (Vector vec, double gamma) {
    Vector res = {vec.x *= gamma, vec.y *= gamma};
    return res;
}

Vector vector_sum (Vector vec_a, Vector vec_b) {
    Vector res = {vec_a.x + vec_b.x, vec_a.y + vec_b.y};
    return (res);
}