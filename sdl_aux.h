#include <SDL.h>

//служебные функции для SDL
char const *init_window_and_renderer(SDL_Window **window_indirect, SDL_Renderer **renderer_indirect, int width, int height, char const *ascii_title);
void destroy_window_and_renderer(SDL_Window *window, SDL_Renderer *renderer);

//структура для описания положения тела на экране
typedef struct {
	int cx, cy, r;
} IKI_Circle;

//функция рисования круга
void IKI_DrawCircle(SDL_Renderer *renderer, IKI_Circle const *circle, int const screen_w, int const screen_h);