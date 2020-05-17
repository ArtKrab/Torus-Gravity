#include "model.h"
#include <math.h>
#include <stdio.h>
//Поиск наименьшего радиус-вектора a -> b
Vector closest_radius (Vector loc_a, Vector loc_b) {
    double res_x, res_y;
    int flag_x = abs(loc_b.x-loc_a.x)<=1.0 ? 0 : 1 ;
    int flag_y = abs(loc_b.y-loc_a.y)<=1.0 ? 0 : 1 ;
    res_x = loc_a.x < 0 ? (1-flag_x)*(loc_b.x - loc_a.x) + flag_x*((-1.0 - loc_a.x) + (loc_b.x - 1.0)) : (1-flag_x)*(loc_b.x - loc_a.x) + flag_x*((1.0 - loc_a.x) + (loc_b.x + 1.0));
    res_y = loc_a.y < 0 ? (1-flag_y)*(loc_b.y - loc_a.y) + flag_y*((-1.0 - loc_a.y) + (loc_b.y - 1.0)) : (1-flag_y)*(loc_b.y - loc_a.y) + flag_y*((1.0 - loc_a.y) + (loc_b.y + 1.0));
    Vector res = {res_x, res_y};
    return res;
}
//Функция 'телепортации' тела при пересечении границы
void teleport_body (Vector *loc) {
    if (abs(loc->x) > 1.0) {
        loc->x = loc->x > 1.0 ? loc->x - 2.0 : loc->x + 2.0;
    }
    if (abs(loc->y) > 1.0) {
        loc->y = loc->y > 1.0 ? loc->y - 2.0 : loc->y + 2.0;
    }
}

//УДААААААААААААААААААААААААААААААААР (упругий)
void elastic_collision(Vector loc_a, Vector loc_b, Vector v_a, Vector v_b) {

}

//Шаг по времени по схеме 'предиктор-корректор'
void model_predictor_time_step(Model *model, double dt) {

    Vector radius_vec = closest_radius(model->a.loc, model->b.loc);
    double len_r = vector_len(radius_vec);

    //рассчет ускорения в момент времени t: a_i = radius_vector * (m_j / len_r^3)
    Vector acc_a = vector_x_double(radius_vec, (model->G*model->b.m/(len_r*len_r*len_r)));
    Vector acc_b = vector_x_double(radius_vec, -(model->G*model->a.m/(len_r*len_r*len_r)));

    //скорость в момент времени t + 0.5dt - 'предсказанная' по текущему ускорению скорость
    Vector v_a_predict = vector_sum(model->a.v, vector_x_double(acc_a, dt*0.5));
    Vector v_b_predict = vector_sum(model->b.v, vector_x_double(acc_b, dt*0.5));

    //новые положения, учитывающие ускорение
    model->a.loc = vector_sum(model->a.loc, vector_x_double(v_a_predict, dt));
        teleport_body(&(model->a.loc));
    model->b.loc = vector_sum(model->b.loc, vector_x_double(v_b_predict, dt));
        teleport_body(&(model->b.loc));


    //новое, 'предсказанное' значение ускорения
    Vector radius_vec_predict = closest_radius(model->a.loc, model->b.loc);
    double len_r_predict = vector_len(radius_vec_predict);

    Vector acc_a_predict = vector_x_double(radius_vec_predict, (model->G*model->b.m/(len_r_predict*len_r_predict*len_r_predict)));
    Vector acc_b_predict = vector_x_double(radius_vec_predict, -(model->G*model->a.m/(len_r_predict*len_r_predict*len_r_predict)));

    //на основе среднего ускорения вычисляем новую скорость
    model->a.v = vector_sum(model->a.v, vector_x_double(vector_sum(acc_a, acc_a_predict), dt*0.5));
    model->b.v = vector_sum(model->b.v, vector_x_double(vector_sum(acc_b, acc_b_predict), dt*0.5));
}