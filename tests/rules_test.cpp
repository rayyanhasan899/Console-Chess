#define main original_game_main
#include "../Chess.cpp"
#undef main
#include <cassert>
int main() {
    int board[8][8] = {};
    board[1][0] = 11;
    assert(isValid_Play(0,1,0,2,1,board));
    assert(!isValid_Play(0,1,1,2,1,board));
    assert(!isValid_Play(-1,1,0,2,1,board));
    assert(!isValid_Play(0,1,8,2,1,board));
    board[1][0]=0; board[3][3]=14;
    assert(isValid_Play(3,3,5,5,1,board));
    board[4][4]=21;
    assert(!isValid_Play(3,3,5,5,1,board));
    board[3][3]=12;
    assert(!isValid_Play(3,3,5,5,1,board));
    assert(isValid_Play(3,3,3,5,1,board));
    int invalid[8][8]={};
    assert(check_White_King(invalid)==-1 && check_Black_King(invalid)==-1);
    assert(callCheck(1,invalid,-1,-1));
}
