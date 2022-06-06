#ifndef COMMON_FUNCTION_H_
#define COMMON_FUNCTION_H_

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <vector>
#include <unistd.h>
#include "BaseObject.h"

static Mix_Chunk* g_sound_exp = NULL;
static Mix_Music* music = NULL;

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;

const int FRAME_PER_SECOND = 50; //fps
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const int RENDER_DRAW_COLOR = 0xff;

#define BLANK_TILE 0
#define TILE_SIZE 64
#define MAX_MAP_X 206
#define MAX_MAP_Y 10

#define STATE_MONEY 7

struct Input
{
    int left;
    int right;
    int up;
    int jump;
    int down;
};

 struct Map
{
    int start_x_;
    int start_y_;
    
    int max_x_;
    int max_y_;

    int tile[MAX_MAP_Y][MAX_MAP_X];
    char* file_name_;
};

namespace SDLCommonFunc
{
    bool CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2);
    int ShowMenu(SDL_Renderer* g_screen, TTF_Font* font,
                 const std::string& menu1, 
                 const std::string& menu2,
                 const std::string& img_name,
                 const int& mark_value);
}

#endif