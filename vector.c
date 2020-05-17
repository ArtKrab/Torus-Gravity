#include "vector.h"

double vector_len (Vector vec) {
    return (vec.x)*(vec.x)+(vec.y)*(vec.y);
}

Vector vector_x_double (Vector vec, double gamma) {
    vec.x *= gamma;
    vec.y *= gamma;
}

Vector vector_sum (Vector vec_a, Vector vec_b) {
    Vector res = {vec_a.x + vec_b.x, vec_a.y + vec_b.y};
    return (res);
}