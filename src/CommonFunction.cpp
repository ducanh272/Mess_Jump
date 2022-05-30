
#include "CommonFunction.h"
#include "TextObject.h"

int SDLCommonFunc::ShowMenu(SDL_Renderer* g_screen, TTF_Font* font,
                            const std::string& menu1, 
                            const std::string& menu2,
                            const std::string& img_name,
                            const int& mark_value)
{
    BaseObject gBackground;
    bool ret = gBackground.LoadImg(img_name, g_screen);
    if (!ret) return 1;

    TextObject score_gained;
    score_gained.SetColor(TextObject::WHITE_TEXT);
    if (mark_value != -1) 
    {
    std::string score = std::to_string(mark_value);
    std::string show_score("Your score: ");
    show_score += score;

    
    score_gained.SetText(show_score);
    score_gained.LoadFromRenderText(font, g_screen);
    }

    const int NUM_MENU_ITEM = 2;
    std::string labels[NUM_MENU_ITEM];
    labels[0] = menu1;
    labels[1] = menu2;

    TextObject text_menu[NUM_MENU_ITEM];
    text_menu[0].SetText(labels[0]);
    text_menu[0].SetColor(TextObject::BLACK_TEXT);
    text_menu[0].LoadFromRenderText(font, g_screen);

    text_menu[1].SetText(labels[1]);
    text_menu[1].SetColor(TextObject::BLACK_TEXT);
    text_menu[1].LoadFromRenderText(font, g_screen);

    SDL_Rect pos[NUM_MENU_ITEM];
    pos[0].x = SCREEN_WIDTH*0.5 - text_menu[0].GetWidth()*0.5;
    pos[0].y = SCREEN_HEIGHT*0.5 + 30;
    pos[1].x = SCREEN_WIDTH*0.5 - text_menu[1].GetWidth()*0.5;
    pos[1].y = SCREEN_HEIGHT*0.5 + 90;

    bool selected[NUM_MENU_ITEM] = {0, 0};
    int xm = 0;
    int ym = 0;
    SDL_Event m_event;
    while (true)
    {
        gBackground.Render(g_screen, NULL);
        while (SDL_PollEvent(&m_event))
        {
            switch (m_event.type)
            {
            case SDL_QUIT:
                text_menu[0].Free();
                text_menu[1].Free();
                gBackground.Free();
                return 1;
            case SDL_MOUSEMOTION:
                xm = m_event.motion.x;
                ym = m_event.motion.y;
                for (int i = 0; i < NUM_MENU_ITEM; ++i)
                {
                    if (xm >= pos[i].x && xm <= pos[i].x + pos[i].w &&
                        ym >= pos[i].y && ym <= pos[i].y + pos[i].h)
                    {
                        if (!selected[i])
                        {
                            selected[i] = 1;
                            text_menu[i].SetText(labels[i]);
                            text_menu[i].SetColor(TextObject::RED_TEXT);
                            text_menu[i].LoadFromRenderText(font, g_screen);
                        }
                    }
                    else 
                    {
                        if (selected[i])
                        {
                            selected[i] = 0;
                            text_menu[i].SetText(labels[i]);
                            text_menu[i].SetColor(TextObject::BLACK_TEXT);
                            text_menu[i].LoadFromRenderText(font, g_screen);
                        }                            
                    }
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                xm = m_event.button.x;
                ym = m_event.button.y;
                for (int i = 0; i < NUM_MENU_ITEM; ++i) {
                    if (xm >= pos[i].x && xm <= pos[i].x + pos[i].w &&
                        ym >= pos[i].y && ym <= pos[i].y + pos[i].h)
                    {
                        text_menu[0].Free();
                        text_menu[1].Free();
                        gBackground.Free();
                        return i;                
                    }
                }
                break;
            case SDL_KEYDOWN:
                if (m_event.key.keysym.sym == SDLK_ESCAPE)
                {
                    text_menu[0].Free();
                    text_menu[1].Free();
                    gBackground.Free();
                    return 1;
                }
            }
        }
        for (int i = 0; i < NUM_MENU_ITEM; ++i)
        {
            text_menu[i].RendererText(g_screen, pos[i].x, pos[i].y);
            pos[i].w = text_menu[i].GetWidth();
            pos[i].h = text_menu[i].GetHeight();
        }
        if (mark_value != -1)
            score_gained.RendererText(g_screen, 
                                      SCREEN_WIDTH*0.5 - score_gained.GetWidth()*0.5, 
                                      SCREEN_HEIGHT*0.5 - 20);
        SDL_RenderPresent(g_screen);
    }
    return 1;
}

bool SDLCommonFunc::CheckCollision(const SDL_Rect& object1, const SDL_Rect& object2)
{
    int left_a = object1.x;
    int right_a = object1.x + object1.w;
    int top_a = object1.y;
    int bottom_a = object1.y + object1.h;
    
    int left_b = object2.x;
    int right_b = object2.x + object2.w;
    int top_b = object2.y;
    int bottom_b = object2.y + object2.h;
    
    // Case 1: size object 1 < size object 2
    if (left_a > left_b && left_a < right_b)
    {
        if (top_a > top_b && top_a < bottom_b)
        {
        return true;
        }
    }
    
    if (left_a > left_b && left_a < right_b)
    {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
        return true;
        }
    }
    
    if (right_a > left_b && right_a < right_b)
    {
        if (top_a > top_b && top_a < bottom_b)
        {
        return true;
        }
    }
    
    if (right_a > left_b && right_a < right_b)
    {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
        return true;
        }
    }
    
    // Case 2: size object 1 < size object 2
    if (left_b > left_a && left_b < right_a)
    {
        if (top_b > top_a && top_b < bottom_a)
        {
        return true;
        }
    }
    
    if (left_b > left_a && left_b < right_a)
    {
        if (bottom_b > top_a && bottom_b < bottom_a)
        {
        return true;
        }
    }
    
    if (right_b > left_a && right_b < right_a)
    {
        if (top_b > top_a && top_b < bottom_a)
        {
        return true;
        }
    }
    
    if (right_b > left_a && right_b < right_a)
    {
        if (bottom_b > top_a && bottom_b < bottom_a)
        {
        return true;
        }
    }
    
    // Case 3: size object 1 = size object 2
    if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
    {
        return true;
    }
    
    return false;
}

