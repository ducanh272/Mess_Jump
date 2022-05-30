#ifndef THREAT_OBJECT_H
#define THREAT_OBJECT_H

#include "CommonFunction.h"
#include "BaseObject.h"

#define THREAT_MAX_FALL_SPEED 10
#define THREAT_GRAVITY_SPEED 0.8
#define THREAT_FRAME_NUM 8
#define THREAT_SPEED 3
class ThreatObject : public BaseObject
{
public:
    ThreatObject();
    ~ThreatObject();

    enum TypeMove
    {
        STATIC_THREAT = 0,
        MOVE_IN_SPACE_THREAT = 1,
    };

    void set_x_val(const float& xVal) {x_val_ = xVal;}
    void set_y_val(const float& yVal) {y_val_ = yVal;}

    void set_x_pos(const float& xp) {x_pos_ = xp;}
    void set_y_pos(const float& yp) {y_pos_ = yp;}
    float get_x_pos() const {return x_pos_;}
    float get_y_pos() const {return y_pos_;}
    void SetMapXY(const int& mp_x, const int& mp_y) {map_x_ = mp_x; map_y_ = mp_y;}

    void set_clips();
    bool LoadImg(std::string path, SDL_Renderer* screen);
    SDL_Rect GetRectFrame();
    void Show(SDL_Renderer* des);
    int get_width_frame() const {return width_frame_;}
    int get_height_frame() const {return height_frame_;}
    void DoPlayer(Map& gMap);
    void CheckToMap(Map& gMap);
    void InitThreats();

    void set_type_move(const int& typeMove) {type_move_ = typeMove;}
    void SetAnimationPos(const int& pos_a, const int& pos_b) {animation_a = pos_a; animation_b = pos_b;}
    void set_input_left(const int& ip_left) {input_type_.left = ip_left;}
    void ImpMoveType(SDL_Renderer* screen);

private:

    int map_x_;
    int map_y_;
    float x_val_;
    float y_val_;
    float x_pos_;
    float y_pos_;
    bool on_ground_;
    int come_back_time_;
    SDL_Rect frame_clip_[THREAT_FRAME_NUM];
    int width_frame_;
    int height_frame_;
    int frame_;

    int type_move_;
    int animation_a;
    int animation_b;
    Input input_type_;
};

#endif

