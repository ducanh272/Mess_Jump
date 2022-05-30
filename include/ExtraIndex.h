#ifndef EXTRA_INDEX_H
#define EXTRA_INDEX_H

#include "CommonFunction.h"
#include "BaseObject.h"

class AliveIndex : public BaseObject
{
public:
    AliveIndex();
    ~AliveIndex();

    void SetNum(const int& num) { number = num; }
    void AddPos(const int& xPos);
    void Show(SDL_Renderer* screen);
    void Init(SDL_Renderer* screen);

    void InCrease();
    void Decrease();

private:
    int number;
    std::vector<int>pos_list;
};

class CoinIndex : public BaseObject
{
public:
    CoinIndex();
    ~CoinIndex();

    void Init(SDL_Renderer* screen);
    void Show(SDL_Renderer* screen);
    void SetPos(const int&x, const int& y) {x_pos_ = x; y_pos_ = y;}

private:
    int x_pos_;
    int y_pos_;

};

#endif