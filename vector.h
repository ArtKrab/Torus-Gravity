
//структура данных для векторных значений в модели: скорости и положения
typedef struct {
    double x;
    double y;
} Vector;

//упоминание заданных в vector.c функций над векторами:

//длина вектора
double vector_len (Vector vec);

//умножение вектора на число
Vector vector_mul_scalar (Vector vec, double gamma);

//сложение векторов
Vector vector_sum (Vector vec_a, Vector vec_b);

//скалярное умножение
double vector_dot_product (Vector vec_a, Vector vec_b);