#include "vector.h"

//структура для описания тела в модели
typedef struct {
    double m;
    Vector loc;
    Vector v;
} Body;

//Структура Model описывает данные, необходимые для моделирования движения тел
typedef struct {
    Body a; //информация о положении и скорости тел - больше информации в model.h
    Body b;
    double G; //гравитационная постоянная
} Model;

void model_predictor_time_step(Model *model, double dt);