#include "sdl_aux.h"

#include <SDL.h>
#include <math.h>

char const *init_window_and_renderer(SDL_Window **window_indirect, SDL_Renderer **renderer_indirect, int width, int height, char const *ascii_title) {
	char const *error_message = "";

	SDL_ClearError();
	*window_indirect = SDL_CreateWindow(ascii_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
	if (*(error_message = SDL_GetError())) goto END;
	SDL_ClearError();
	*renderer_indirect = SDL_CreateRenderer(*window_indirect, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (*(error_message = SDL_GetError())) goto END;

END:
	return error_message;
}

void destroy_window_and_renderer(SDL_Window *window, SDL_Renderer *renderer) {
	if (NULL != renderer) SDL_DestroyRenderer(renderer);
	if (NULL != window) SDL_DestroyWindow(window);
}


//int const SCREEN_WIDTH = screen_w = 1000, SCREEN_HEIGHT = screen_h = 600;
void IKI_DrawCircle(SDL_Renderer *renderer, IKI_Circle const *circle, int const screen_w, int const screen_h) {
	for (int h = 0; h < circle->r; ++h) {

	    //Полуширина текущих линий с центром в cx
		int x_offset = (int)sqrt(circle->r * circle->r - h * h);

        //SDL_RenderDrawLine(renderer, circle->cx - x_offset, circle->cy - h, circle->cx + x_offset, circle->cy - h);
        //SDL_RenderDrawLine(renderer, circle->cx - x_offset, circle->cy + h, circle->cx + x_offset, circle->cy + h);



		//Здесь проверяется нужно ли вообще хитрить с вырисовыванием текущей (!) линии:
		//(x_offset < cx < screen_w-x_offset) и (h < cy < screen_h-h)
		//1 - вблизи нет x-границ
		// .1 - вблизи нет y-границ
		// .2 - есть контакт c y-границей
		//   .1 - c верхней границей
		//   .2 - с нижней границей
		//2 - есть контакт с левой границей
		//  .1 - вблизи нет y-границ
		//  .2 - есть контакт c y-границей
        //   .1 - c верхней границей
        //   .2 - с нижней границей
		//3 - есть контакт с правой границей
        //  .1 - вблизи нет y-границ
        //  .2 - есть контакт c y-границей
        //   .1 - c верхней границей
        //   .2 - с нижней границей

		if (x_offset <= circle->cx && circle->cx <= screen_w-x_offset) {
            if (h <= circle->cy && circle->cy <= screen_h - h) {
// 1.1
                SDL_RenderDrawLine(renderer, circle->cx - x_offset, circle->cy - h, circle->cx + x_offset,
                                   circle->cy - h);
                SDL_RenderDrawLine(renderer, circle->cx - x_offset, circle->cy + h, circle->cx + x_offset,
                                   circle->cy + h);
            } else if (h > circle->cy) {
// 1.2.1
                SDL_RenderDrawLine(renderer, circle->cx - x_offset, screen_h + circle->cy - h, circle->cx + x_offset,
                                   screen_h + circle->cy - h);
                SDL_RenderDrawLine(renderer, circle->cx - x_offset, circle->cy + h, circle->cx + x_offset,
                                   circle->cy + h);
            } else {
// 1.2.2
                SDL_RenderDrawLine(renderer, circle->cx - x_offset, circle->cy - h, circle->cx + x_offset,
                                   circle->cy - h);
                SDL_RenderDrawLine(renderer, circle->cx - x_offset, circle->cy + h - screen_h, circle->cx + x_offset,
                                   circle->cy + h - screen_h);
            }
        }
		else if (x_offset > circle->cx) {
            if (h <= circle->cy && circle->cy <= screen_h - h) {
//2.1
                SDL_RenderDrawLine(renderer, screen_w + circle->cx - x_offset, circle->cy - h, screen_w - 0,
                                   circle->cy - h);
                SDL_RenderDrawLine(renderer, 0, circle->cy - h, circle->cx + x_offset, circle->cy - h);
                SDL_RenderDrawLine(renderer, screen_w + circle->cx - x_offset, circle->cy + h, screen_w - 0,
                                   circle->cy + h);
                SDL_RenderDrawLine(renderer, 0, circle->cy + h, circle->cx + x_offset, circle->cy + h);
            } else if (h > circle->cy) {
//2.2.1
                SDL_RenderDrawLine(renderer, screen_w + circle->cx - x_offset, screen_h + circle->cy - h, screen_w - 0,
                                   screen_h + circle->cy - h);
                SDL_RenderDrawLine(renderer, 0, screen_h + circle->cy - h, circle->cx + x_offset, screen_h + circle->cy - h);
                SDL_RenderDrawLine(renderer, screen_w + circle->cx - x_offset, circle->cy + h, screen_w - 0,
                                   circle->cy + h);
                SDL_RenderDrawLine(renderer, 0, circle->cy + h, circle->cx + x_offset, circle->cy + h);
            } else {
//2.2.2
                SDL_RenderDrawLine(renderer, screen_w + circle->cx - x_offset, circle->cy - h, screen_w - 0,
                                   circle->cy - h);
                SDL_RenderDrawLine(renderer, 0, circle->cy - h, circle->cx + x_offset, circle->cy - h);
                SDL_RenderDrawLine(renderer, screen_w + circle->cx - x_offset, circle->cy + h - screen_h, screen_w - 0,
                                   circle->cy + h - screen_h);
                SDL_RenderDrawLine(renderer, 0, circle->cy + h - screen_h, circle->cx + x_offset, circle->cy + h - screen_h);
            }
        } else {
            if (h <= circle->cy && circle->cy <= screen_h - h) {
//3.1
                SDL_RenderDrawLine(renderer, circle->cx - x_offset, circle->cy - h, screen_w - 0,
                                   circle->cy - h);
                SDL_RenderDrawLine(renderer, 0, circle->cy - h, circle->cx + x_offset - screen_w, circle->cy - h);
                SDL_RenderDrawLine(renderer, circle->cx - x_offset, circle->cy + h, screen_w - 0,
                                   circle->cy + h);
                SDL_RenderDrawLine(renderer, 0, circle->cy + h, circle->cx + x_offset - screen_w, circle->cy + h);
            } else if (h > circle->cy) {
//3.2.1
                SDL_RenderDrawLine(renderer, circle->cx - x_offset, screen_h + circle->cy - h, screen_w - 0,
                                   screen_h + circle->cy - h);
                SDL_RenderDrawLine(renderer, 0, screen_h + circle->cy - h, circle->cx + x_offset - screen_w, screen_h + circle->cy - h);
                SDL_RenderDrawLine(renderer, circle->cx - x_offset, circle->cy + h, screen_w - 0,
                                   circle->cy + h);
                SDL_RenderDrawLine(renderer, 0, circle->cy + h, circle->cx + x_offset - screen_w, circle->cy + h);
            } else {
//3.2.2
                SDL_RenderDrawLine(renderer, circle->cx - x_offset, circle->cy - h, screen_w - 0,
                                   circle->cy - h);
                SDL_RenderDrawLine(renderer, 0, circle->cy - h, circle->cx + x_offset - screen_w, circle->cy - h);
                SDL_RenderDrawLine(renderer, circle->cx - x_offset, circle->cy + h - screen_h, screen_w - 0,
                                   circle->cy + h - screen_h);
                SDL_RenderDrawLine(renderer, 0, circle->cy + h - screen_h, circle->cx + x_offset - screen_w, circle->cy + h - screen_h);
            }
		}

	}
}