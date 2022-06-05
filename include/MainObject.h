#ifndef MAIN_OBJECT_H
#define MAIN_OBJECT_H

#include "CommonFunction.h"
#include "BaseObject.h"
#include "ExtraIndex.h"

#define GRAVITY_SPEED 0.8
#define MAX_FALL_SPEED 15
#define PLAYER_SPEED 8
#define PLAYER_JUMP_VAL 22
#define NUM_FRAME 5
#define TRAP_STATE_1 21
#define TRAP_STATE_2 22

class MainObject : public BaseObject
{
public:
    MainObject();
    ~MainObject();

    enum WalkType
    {
        WALK_NONE = 0,
        WALK_RIGHT = 1,
        WALK_LEFT = 2
    };

    bool LoadImg(std::string path, SDL_Renderer*screen);
    void Show(SDL_Renderer* des);
    void HandleInPut(SDL_Event events, SDL_Renderer* screen);
    void set_clips();
    void DoPlayer(Map& map_data);
    void CheckToMap(Map& map_data);
    void SetMapXY(const int map_x, const int map_y) {map_x_ = map_x; map_y_ = map_y;};
    void CenterEntityOnMap(Map& map_data);
    void UpdateImagePlayer(SDL_Renderer* des);
    void IncreaseMoney();
    SDL_Rect GetRectFrame();
    int GetMoneyCount() const { return money_count; }
    bool CheckDie() const { return is_die; }
    void SetBackTime(const int& cb_time) { come_back_time_ = cb_time; }

private:
    int money_count;
    float x_val_;
    float y_val_;

    float x_pos_;
    float y_pos_;

    int width_frame_;
    int height_frame_;

    SDL_Rect frame_clip_[NUM_FRAME];
    Input input_type_;
    int frame_;
    int status_;
    bool on_ground_;

    int map_x_;
    int map_y_;

    int come_back_time_;
    bool is_die;
};

#endif