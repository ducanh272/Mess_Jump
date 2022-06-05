#include "CommonFunction.h"
#include "BaseObject.h"
#include "gamemap.h"
#include "MainObject.h"
#include "Timer.h"
#include "ThreatObject.h"
#include "Explosion.h"
#include "TextObject.h"
#include "ExtraIndex.h"

#define NUM_MOVE_THREAT 8
#define NUM_STATIC_THREAT 20
BaseObject g_background; 
TTF_Font* font_time = NULL;
TTF_Font* font_menu = NULL;
TTF_Font* font_score = NULL;
int num_die  = 0;

bool InitData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0) return false;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    g_window = SDL_CreateWindow("Game.Cpp.SDL.2.0",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                SCREEN_WIDTH, SCREEN_HEIGHT,
                                SDL_WINDOW_SHOWN);
    if (g_window == NULL)
    {
        success = false;
    }                
    else 
    {
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if (g_screen == NULL) 
        {
            success = false;
        }
        else 
        {
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            int imgFlags = IMG_INIT_PNG;
            if (!(IMG_Init(imgFlags) && imgFlags)) success = false;
        }

        if (TTF_Init() == -1)
        {
            success = false;
        }

        font_time = TTF_OpenFont("assets//fonts//CuBaoWide.ttf", 25);
        font_menu = TTF_OpenFont("assets//fonts//CuBaoWide.ttf", 40);
        font_score = TTF_OpenFont("assets//fonts//CuBaoWide.ttf", 50);
        
        if (font_time == NULL || font_menu == NULL)
        {
          success = false;
        }
    } 

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
      success = false;

    g_sound_exp = Mix_LoadWAV("assets//sounds//Bomb+1.wav");
    music = Mix_LoadMUS("assets//music//music.wav");

    if (g_sound_exp == NULL) 
      success = false;
   
  return success;            
}

bool LoadBackground()
{
    bool ret = g_background.LoadImg("assets//images//background.png", g_screen);
    if (ret == false) return false;
    return true;
}

void close()
{
    g_background.Free();

    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;

    Mix_CloseAudio();

    IMG_Quit();
    SDL_Quit();
}

std::vector<ThreatObject*> MakeThreatList()
{
    std::vector<ThreatObject*> list_threats;

    ThreatObject* dynamic_threats = new ThreatObject[NUM_MOVE_THREAT];
    for (int i = 0; i < NUM_MOVE_THREAT; ++i)
    {
        ThreatObject* p_threat = (dynamic_threats + i);
        if (p_threat != NULL)
        {
            p_threat->LoadImg("assets//images//threat_left.png", g_screen);
            p_threat->set_clips();
            p_threat->set_type_move(ThreatObject::MOVE_IN_SPACE_THREAT);
            p_threat->set_x_pos(500 + i*1500);
            p_threat->set_y_pos(200);

            int pos1 = p_threat->get_x_pos() - 60;
            int pos2 = p_threat->get_x_pos() + 60;
            p_threat->SetAnimationPos(pos1, pos2);
            p_threat->set_input_left(1);
            list_threats.push_back(p_threat);
        }
    }

    ThreatObject* threat_objs = new ThreatObject[NUM_STATIC_THREAT];
    for (int i = 0; i < NUM_STATIC_THREAT; ++i)
    {
        ThreatObject* p_threat = (threat_objs + i);
        if (p_threat != NULL)
        {
            p_threat->LoadImg("assets//images//bomb.png", g_screen);
            p_threat->set_clips();
            p_threat->set_x_pos(700 + i*1500);
            p_threat->set_y_pos(250);
            p_threat->set_type_move(ThreatObject::STATIC_THREAT);
            p_threat->set_input_left(0);
            list_threats.push_back(p_threat);
        }
    }

  return list_threats;
}


int main(int argc, char* argv[])
{
    if (InitData() == false) return -1;

    bool is_quit = false;
    ImpTimer fps_timer;
    
    //Make menu game
    int ret_menu = SDLCommonFunc::ShowMenu(g_screen, font_menu, "Play Game", "Exit", 
                                          "assets//images//run.png", -1);
    if (ret_menu == 1)
      is_quit = true;

    if (LoadBackground() == false) return -1;

again_label:
    GameMap game_map;
    game_map.LoadMap("map/map02.dat");
    game_map.LoadTiles(g_screen);

    MainObject p_player;
    p_player.LoadImg("assets//images//main_right-03.png", g_screen);
    p_player.set_clips();

    CoinIndex player_money;
    player_money.Init(g_screen);
    player_money.SetPos(SCREEN_WIDTH*0.1 + 80, 10);

    std::vector<ThreatObject*> threats_list = MakeThreatList();

    ExplosionObject exp_threat;
    bool tRet = exp_threat.LoadImg("assets//images//exp3.png", g_screen);
    if (!tRet) return -1;
    exp_threat.set_clip();

    ExplosionObject exp_main;
    bool mRet = exp_main.LoadImg("assets//images//exp3.png", g_screen);
    if (!mRet) return -1;
    exp_main.set_clip();
    
    TextObject mark_game;
    mark_game.SetColor(TextObject::WHITE_TEXT);
    int mark_value = 0;

    TextObject money_game;
    money_game.SetColor(TextObject::WHITE_TEXT);

    //Game loop
    while (!is_quit)
    {
        int money_count = 0;
        mark_value++;

        if(Mix_PlayingMusic() == 0 ) Mix_PlayMusic(music, -1);

        fps_timer.start();

        while (SDL_PollEvent(&g_event) != 0)
        {
            if (g_event.type == SDL_QUIT) 
            {
              is_quit = true;
            }
            p_player.HandleInPut(g_event, g_screen);
        }

        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);

        g_background.Render(g_screen, NULL);

        game_map.DrawMap(g_screen);
        Map map_data = game_map.getMap();

        p_player.SetMapXY(map_data.start_x_, map_data.start_y_);
        p_player.DoPlayer(map_data);
        p_player.Show(g_screen);

        game_map.SetMap(map_data);
        game_map.DrawMap(g_screen);

        player_money.Show(g_screen);

        bool game_over = p_player.CheckDie(); 
        money_count = p_player.GetMoneyCount();

        for (int i = 0; i < threats_list.size(); ++i)
        {
            ThreatObject* p_threat = threats_list.at(i);
            if (p_threat != NULL)
            {
                p_threat->SetMapXY(map_data.start_x_, map_data.start_y_);
                p_threat->ImpMoveType(g_screen);
                p_threat->DoPlayer(map_data);
                p_threat->Show(g_screen);

                //Check Collision Player - Threats
                int frame_exp_width = exp_threat.get_frame_width();
                int frame_exp_height = exp_threat.get_frame_height();

                SDL_Rect rect_player = p_player.GetRectFrame();
                SDL_Rect rect_threat = p_threat->GetRectFrame();
                bool crash = SDLCommonFunc::CheckCollision(rect_player, rect_threat);

                if (crash)
                {
                    for (int ex = 0; ex < NUM_FRAME_EXP; ++ex)
                    {
                      int x_pos = p_threat->GetRect().x - frame_exp_width*0.5;
                      int y_pos = p_threat->GetRect().y - frame_exp_height*0.5;

                      exp_threat.set_frame(ex);
                      exp_threat.SetRect(x_pos, y_pos);
                      exp_threat.Show(g_screen);
                    }
                    Mix_PlayChannel(-1, g_sound_exp, 0);
                    game_over = true;
                }  
            }
        } 

        std::string val_str_mark = std::to_string(mark_value);
        std::string strMark("Score: ");
        strMark += val_str_mark;

        mark_game.SetText(strMark);
        mark_game.LoadFromRenderText(font_time, g_screen);
        mark_game.RendererText(g_screen, SCREEN_WIDTH - 300, 18);

        
        std::string money_str = std::to_string(money_count);
        money_game.SetText(money_str);
        money_game.LoadFromRenderText(font_time, g_screen);
        money_game.RendererText(g_screen, SCREEN_WIDTH*0.1 + 40, 18);

        SDL_RenderPresent(g_screen);

        // MENU GAME OVER
        int score = mark_value + money_count;
        if (game_over == true)
        {
            int ret_menu = SDLCommonFunc::ShowMenu(g_screen, font_menu,
                                                  "Play Again", "Exit",
                                                  "assets//images//end.png", score);
            

            if (ret_menu == 1)
            {
                is_quit = true;
                continue;
            }
            else
            { 
                is_quit = false;
                mark_value = 0;
                goto again_label;
            }
        }

        //Fps
        int real_imp_time = fps_timer.get_ticks();
        int time_one_frame = 1000/FRAME_PER_SECOND; //ms

        if (real_imp_time < time_one_frame)
        {
          int delay_time =  time_one_frame - real_imp_time;
          if (delay_time >= 0) SDL_Delay(delay_time);
        }
    }

    close();
    return 0;
}