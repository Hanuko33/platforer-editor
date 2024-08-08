#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include "text.h"
SDL_Window *window;
SDL_Renderer *renderer;
struct Player
{
    int x;
    int y;
    float y_velocity;
    char going_right;
    char on_ground;
};

struct Player player;
SDL_Texture* playerr_texture;
SDL_Texture* playerl_texture;
SDL_Texture* tile_texture;

SDL_Texture* load_texture(const char * texture_name)
{
    SDL_Texture* texture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(texture_name); 
    if (loadedSurface == NULL)
    {
        printf("Unable to load texture: %s error: %s\n", texture_name, SDL_GetError()); 
            exit(0);
    }
    else 
    {    
        texture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

        if (texture == NULL)
        {
            printf("Unable to create texture: %s error: %s\n", texture_name, SDL_GetError());
            exit(0);
        }
        SDL_FreeSurface(loadedSurface);
    }

    return texture;
}


int init_sdl2()
{
    window = SDL_CreateWindow("Platforer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 1024, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        return 1;
    }
    
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) 
    {
        printf("\nUnable to initialize sdl_image:  %s\n", IMG_GetError());
        return 1;
    }

    if (TTF_Init() == -1)
    {
        printf("\nUnable to initialize sdl_ttf:  %s\n", TTF_GetError());
        return 1;
    }

    SDL_Surface* icon = IMG_Load("textures/icon.png");
    if (icon == NULL) {
        printf("\nUnable to load image %s! SDL_image Error: %s\n", "textures/icon.png", IMG_GetError());
        return 1;
    }
    SDL_SetWindowIcon(window, icon);
    SDL_FreeSurface(icon);


    return 0;
}


void draw()
{
    SDL_Rect player_rect = {player.x, player.y, 64, 64};
    if (player.going_right)
        SDL_RenderCopy(renderer, playerr_texture, NULL, &player_rect);
    else
        SDL_RenderCopy(renderer, playerl_texture, NULL, &player_rect);
    SDL_RenderDrawRect(renderer, &player_rect);

    char text[256];
    int text_y=16;
    
    sprintf(text, "X: %d", player.x);
    write_text(10, text_y, text, (SDL_Color){255,255,255,255}, 20, window, renderer);
    text_y+=16;

    sprintf(text, "Y: %d", player.y);
    write_text(10, text_y, text, (SDL_Color){255,255,255,255}, 20, window, renderer);
    text_y+=16;
    
    sprintf(text, "On ground: %d", player.on_ground);
    write_text(10, text_y, text, (SDL_Color){255,255,255,255}, 20, window, renderer);
    SDL_Rect tile_rect = {0, 1024-464, 100, 500};
    SDL_RenderCopy(renderer, tile_texture, NULL, &tile_rect);
}
void update(const Uint8 * keys)
{
    if (keys[SDL_SCANCODE_D])
    {
        player.going_right = 1;
        player.x += 10;
    }
    else if (keys[SDL_SCANCODE_A])
    {
        player.going_right = 0;
        player.x += -10;
    }

    if (player.y>500 && player.x<100)
    {
        player.on_ground=1;
    }
    else
    {
        player.on_ground=0;
    }
    
    if (!player.on_ground)
        player.y_velocity += 0.5;
    else
        player.y_velocity = 0;
    

    if (keys[SDL_SCANCODE_SPACE] && player.on_ground)
    {
        player.on_ground=0;
        player.y_velocity = -15;
    }

    player.y+=(int)(player.y_velocity);
}

int main()
{
    player.on_ground=1;
    player.x=60;
    player.y=160;
    player.y_velocity=0;

    if (init_sdl2() != 0)
    {
        SDL_Quit();
        return 1;
    }
    load_font();
    playerr_texture = load_texture("textures/playerr.png");
    playerl_texture = load_texture("textures/playerl.png");
    tile_texture = load_texture("textures/tile.png");

    for (;;)
    {
        // Keyboard handling by events
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                SDL_Quit();
                return 0;
            }
            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        SDL_Quit();
                        return 0;
                }
            }
        }

        
        SDL_RenderClear(renderer);
        
        // Keyboard handling by states
        const Uint8 * keys = SDL_GetKeyboardState(NULL);
        update(keys);
        draw();

        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / 60);
    }
}

        
