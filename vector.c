#include "vector.h"
#include <math.h>

double vector_len (Vector vec) {
    return sqrt(vector_dot_product(vec, vec));
}

double vector_dot_product (Vector vec_a, Vector vec_b) {
    return (vec_a.x*vec_b.x + vec_a.y*vec_b.y);
}

Vector vector_mul_scalar (Vector vec, double gamma) {
    Vector res = {vec.x *= gamma, vec.y *= gamma};
    return res;
}

Vector vector_sum (Vector vec_a, Vector vec_b) {
    Vector res = {vec_a.x + vec_b.x, vec_a.y + vec_b.y};
    return (res);
}