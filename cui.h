#pragma once
#ifndef ___BOARD_H
	#define ___BOARD_H
    #include "board.h"
#endif

//�Ղ̏�Ԃ�\��
void print_board(const Board* board);
//�Ղ̏�Ԃ�\��(debug�p)
void print_board_debug(const Board* board);
//�����̏�Ԃ�\��
void print_attack(const Board* board);
//�l�ԂɎw��𑣂�(���������͂ł�����true)
bool input_human_move(Board* board,Move* move,bool* flg_undo);
//�v���C���[��l�Ԃɂ��邩�AAI�ɂ��邩
void input_playmode(int* player_b, int* player_w);


