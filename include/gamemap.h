
#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "CommonFunction.h"
#include "BaseObject.h"

#define MAX_KIND_TILE 10
class TileMap : public BaseObject
{
public :
    TileMap() {;}
    ~TileMap() {;}
};

class GameMap
{
public:
    GameMap() {;}
    ~GameMap() {;}

    void LoadMap(char* name);
    void LoadTiles(SDL_Renderer* screen);
    void DrawMap(SDL_Renderer* screen);
    Map getMap() const {return game_map;};
    void SetMap(Map& map_data) {game_map = map_data;};
private:
    Map game_map;
    TileMap tile_map[MAX_KIND_TILE];
};

#endif