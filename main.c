#include "sdl_aux.h"
#include "model.h"

#include <SDL.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

Uint32 timer_function_draw_event(Uint32 interval, void *_params) {
	SDL_UserEvent userevent;
	userevent.type = SDL_USEREVENT;
	userevent.code = 0;

	SDL_Event event;
	event.type = SDL_USEREVENT;
	event.user = userevent;

	SDL_PushEvent(&event);
	return interval;
}

typedef struct {
	IKI_Circle *Circle_a;
    IKI_Circle *Circle_b;
} IKI_Scene;

void draw_scene(SDL_Renderer *renderer, IKI_Scene const *scene, int const screen_w, int const screen_h) {
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(renderer);

	SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
	IKI_DrawCircle(renderer, scene->Circle_a, screen_w, screen_h);

	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
	IKI_DrawCircle(renderer, scene->Circle_b, screen_w, screen_h);

	SDL_RenderPresent(renderer);
}

//Функция для вывода на экран полной энергии системы
void log_energy(Model const *model) {
    printf("ax=%f\n", model->a.loc.x);
}

//Функция преобразования из координат модели в координаты окна
void map_model_to_scene(Model const *model, IKI_Scene *scene, int const screen_w, int const screen_h) {
	int circle_a_x = model->a.loc.x * screen_w/2 + screen_w/2;
    int circle_a_y = model->a.loc.y * screen_h/2 + screen_h/2;
    scene->Circle_a->cx = circle_a_x;
	scene->Circle_a->cy = circle_a_y;
    int circle_b_x = model->b.loc.x * screen_w/2 + screen_w/2;
    int circle_b_y = model->b.loc.y * screen_h/2 + screen_h/2;
    scene->Circle_b->cx = circle_b_x;
    scene->Circle_b->cy = circle_b_y;
}





int main(int agc, char **argv) {
	if (0 != SDL_Init(SDL_INIT_VIDEO)) {
		printf("Can't initialize SDL.\nCause: %s\n", SDL_GetError());
		goto END;
	}

	{
		SDL_Window *main_window = NULL;
		SDL_Renderer *main_renderer = NULL;
		SDL_TimerID timer_id;

		int const SCREEN_WIDTH = 1000, SCREEN_HEIGHT = 700; //TODO(Сыграть с нормировкой пространства в НЕквадратном окне)
		const char *error_message = "";

		if (*(error_message = init_window_and_renderer(&main_window, &main_renderer, SCREEN_WIDTH, SCREEN_HEIGHT, "SDL Render Draw Example"))) {
			printf("Can't create window or renderer.\nCause: %s\n", error_message);
			goto CLEANUP;
		}

        //Данные модели (model) и шаг по времени (dt)
		Model model = {1, {-0.5, 0}, {0, 1},
                       1, {0.5, 0}, {-1, 0},
                       5};
		double dt = 2.5e-6; //TODO(Значение G const)

        //При изменении начального положения тел в модели изменить и здесь (?)
		IKI_Circle circle_a = { SCREEN_WIDTH/4, SCREEN_HEIGHT/2, 40 };
		IKI_Circle circle_b = { 3*SCREEN_WIDTH/4, SCREEN_HEIGHT/2, 40 };
		IKI_Scene scene = { &circle_a, &circle_b };

		timer_id = SDL_AddTimer(33, timer_function_draw_event, NULL);

		SDL_Event e;
		bool proceed = true;
		while (proceed) {
			if (SDL_PollEvent(&e)) {
				switch (e.type) {
					case SDL_QUIT:
					{
						proceed = false;
						break;
					}

					case SDL_USEREVENT:
					{
                        //log_energy(&model);
						map_model_to_scene(&model, &scene, SCREEN_WIDTH, SCREEN_HEIGHT);
						draw_scene(main_renderer, &scene, SCREEN_WIDTH, SCREEN_HEIGHT);

                        //IKI_Circle test = {SCREEN_WIDTH/2, SCREEN_HEIGHT/2,50};
                        //SDL_SetRenderDrawColor(main_renderer, 0x00, 0xFF, 0x00, 0xFF);
                        //IKI_DrawCircle(main_renderer, &test, SCREEN_WIDTH, SCREEN_HEIGHT);

                        SDL_RenderPresent(main_renderer);
						break;
					}
				}
			}

			model_predictor_time_step(&model, dt);  //раскомментировать для вычисления движения тела по схеме 'предиктор-корректор'
			
		}

	CLEANUP:
		destroy_window_and_renderer(main_window, main_renderer);
		SDL_RemoveTimer(timer_id);
	}

END:
	SDL_Quit();
	return 0;
}