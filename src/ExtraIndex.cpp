#include "ExtraIndex.h"

AliveIndex::AliveIndex()
{
    number = 0;
}

AliveIndex::~AliveIndex()
{

}

void AliveIndex::AddPos(const int& xp)
{
    pos_list.push_back(xp);
}

void AliveIndex::Init(SDL_Renderer* screen)
{
    LoadImg("assets//images//heart.png", screen);
    number = 3;
    if (pos_list.size() > 0)
    {
        pos_list.clear();
    }

    AddPos(20);
    AddPos(60);
    AddPos(100);
}

void AliveIndex::Show(SDL_Renderer* screen)
{
    for (int i = 0; i < pos_list.size(); ++i)
    {
        rect_.x = pos_list.at(i);
        rect_.y = 0;
        Render(screen);
    }
}

void AliveIndex::Decrease()
{
    number--;
    pos_list.pop_back();
}

void AliveIndex::InCrease()
{
    number++;
    int last_pos = pos_list.back();
    last_pos += 40;
    pos_list.push_back(last_pos);
}

CoinIndex::CoinIndex()
{
    x_pos_ = 0;
    y_pos_ = 0;
}

CoinIndex::~CoinIndex()
{

}

void CoinIndex::Init(SDL_Renderer* screen)
{
    bool ret = LoadImg("assets//images//coin-02.png", screen);
}

void CoinIndex::Show(SDL_Renderer* screen)
{
    rect_.x = x_pos_;
    rect_.y = y_pos_;
    Render(screen);
}