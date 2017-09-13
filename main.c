#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"


#define     FPS         20
#define     WIDTH       320
#define     HEIGHT      240
#define     DEPTH       32


int RUNNING = 0;
SDL_Surface *frames[80] = {NULL};
SDL_Event event;


void load_images();
void clean_images();
void cancelOnKeyPress();


static void terminateHandler(int signal){
    RUNNING = 0;
}


int main(int argc, char *argv[]){
    putenv("SDL_VIDEODRIVER=fbcon");
    putenv("SDL_FBDEV=/dev/fb1");

    signal(SIGINT, terminateHandler);
    signal(SIGTERM, terminateHandler);
    RUNNING = 1;

    SDL_Surface *screen = NULL;
    SDL_Surface *background = NULL;

    load_images();

    if ( SDL_Init(SDL_INIT_EVERYTHING) == -1){
        puts("could not start SDL");
    }
    SDL_ShowCursor(SDL_DISABLE);

    screen = SDL_SetVideoMode(WIDTH, HEIGHT, DEPTH, SDL_SWSURFACE);
    if ( screen == NULL){
        puts("could not create the screen");
    }

    int flags = IMG_INIT_JPG | IMG_INIT_PNG;
    int initted = IMG_Init(flags);

    if( (initted & flags) != flags) {
        puts("could not init SDL_Image");
        printf("Reason: %s\n", IMG_GetError());
    }

    int i = 0;
    unsigned int start;
    background = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, DEPTH, 0, 0, 0, 0);

    SDL_Rect pos;
    pos.x = WIDTH / 2 - 64;
    pos.y = HEIGHT / 2 - 64;

    while(RUNNING){
        start = SDL_GetTicks();
        cancelOnKeyPress();
        SDL_FillRect(background, NULL, 0x000000);
        SDL_BlitSurface(frames[i], NULL, background, &pos);
        SDL_BlitSurface(background, NULL, screen, NULL);
        i = (i + 1) % 80;
        SDL_Flip(screen);
        if((1000 / FPS) > (SDL_GetTicks() - start)){
            SDL_Delay(1000 / FPS - (SDL_GetTicks() - start));
        }
    }

    SDL_FreeSurface(background);

    clean_images();

    SDL_Quit();

    return 0;
}


void load_images(){
    int i = 0;
    char str[46] = "\0";
    for(i = 0; i < 80; i++){
        sprintf(str, "/home/adam/git/rpi_frames/frame_%02d.png", i);
        frames[i] = IMG_Load(str);
        if(frames[i] == NULL){
            printf("could not load image: %s\n", str);
        }
    }
}


void clean_images(){
    int i = 0;
    for(i = 0; i < 80; i++){
        SDL_FreeSurface(frames[i]);
    }
}


void cancelOnKeyPress(){
	if(SDL_PollEvent(&event) != 0){
		if(event.type == SDL_QUIT){
			RUNNING = 0;
		}
		else if(event.type == SDL_KEYDOWN) {
			RUNNING = 0;
/*			switch(event.key.keysym.sym) {
				case SDLK_ESCAPE:
					RUNNING = 0;
				break;
				case SDLK_DOWN:
				break;
				default:
				break;
			}*/
		}
	}
}
