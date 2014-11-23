#pragma once
#ifndef ___BOARD_H
	#define ___BOARD_H
    #include "board.h"
#endif

//盤の状態を表示
void print_board(const Board* board);
//盤の状態を表示(debug用)
void print_board_debug(const Board* board);
//効きの状態を表示
void print_attack(const Board* board);
//人間に指手を促す(正しく入力できたらtrue)
bool input_human_move(Board* board,Move* move,bool* flg_undo);
//プレイヤーを人間にするか、AIにするか
void input_playmode(int* player_b, int* player_w);


