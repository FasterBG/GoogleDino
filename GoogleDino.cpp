#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <winuser.h>
#include <stdlib.h>
#include "COLOR.h"
#include "CObstacle.h"
#include "CPlayer.h"

using namespace std;

const int MAX_STONES = 30;

const int STONE_HEALTH = 10;

const char STONE_CH = '#';
const char PLAYER_CH = 'D';

bool end_game = false;

CObstacle* tilemap[SCREEN_HEIGHT][SCREEN_WIDTH] = {NULL};

CPlayer* pDino = new CPlayer(PLAYER_CH, 100, 0, BLACK);

void init(CObstacle* tilemap[SCREEN_HEIGHT][SCREEN_WIDTH]){
    srand(time(0));
    int rnd;
    int br = 0;
    while(br < MAX_STONES){
        rnd = (rand() % (SCREEN_WIDTH - 10)) + 10;
        if(tilemap[0][rnd] == NULL){
            tilemap[0][rnd] = new CObstacle(STONE_CH, STONE_HEALTH, 0, BLACK);
            br++;
        }
    }
    for(int r = 0; r < SCREEN_HEIGHT; r++){
        for(int c = 0; c < SCREEN_WIDTH; c++){
            if(tilemap[r][c] != NULL){
                draw_char(tilemap[r][c]->screen_ch, r, c, BLACK, backgroundColor);
            }
        }
    }
    if(tilemap[pDino->r][pDino->c] != NULL){
        delete tilemap[pDino->r][pDino->c];
        tilemap[pDino->r][pDino->c] = NULL;
    }
    draw_char(PLAYER_CH, pDino->r, pDino->c, pDino->screen_color, backgroundColor);
}
void moveStones(){
    for(int i = 0; i < SCREEN_WIDTH; i++){
        if(tilemap[0][i] != NULL){
            draw_char(tilemap[0][i]->screen_ch, 0, i - 1, tilemap[0][i]->screen_color, backgroundColor);
            draw_char(' ', 0, i, tilemap[0][i]->screen_color, backgroundColor);
            tilemap[0][i-1] = tilemap[0][i];
            tilemap[0][i] = NULL;
            int propability = rand()%(128 - MAX_STONES);
            if(propability == 1){
                tilemap[0][127] = new CObstacle(STONE_CH, STONE_HEALTH, 0, BLACK);
                draw_char(tilemap[0][127]->screen_ch, 0, i - 1, tilemap[0][127]->screen_color, backgroundColor);
            }
        }
    }
}
int main(){
    init_console();
    init(tilemap);
    while (!end_game){
            draw_char(' ', pDino->r, pDino->c, backgroundColor, backgroundColor);
            if(GetAsyncKeyState(' ') && pDino->canJump == true){
                if(pDino->r > SCREEN_HEIGHT * 3/4){
                    pDino->canJump = false;
                }
                pDino->r++;
            }else if(pDino->r == 0){
                pDino->canJump = true;
            }else {
                pDino->r--;
                pDino->canJump = false;
            }
            if(tilemap[pDino->r][pDino->c] != NULL){
                pDino->health -= tilemap[pDino->r][pDino->c]->damage;
                delete tilemap[pDino->r][pDino->c];
                tilemap[pDino->r][pDino->c];
            }
            if(pDino->health <= 0){
                end_game = true;
            }
            moveStones();
            draw_char(pDino->screen_ch, pDino->r, pDino->c, pDino->screen_color, backgroundColor);
        Sleep(180);
    }
    Sleep(2000);
    return 0;
}
