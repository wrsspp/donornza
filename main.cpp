#ifndef ___STDAFX_H
	#define ___STDAFX_H
	#include "stdafx.h"
#endif
#ifndef ___BOARD_H
	#define ___BOARD_H
    #include "board.h"
#endif
#ifndef ___CUI_H
	#define ___CUI_H
    #include "cui.h"
#endif
#ifndef ___AI_H
	#define ___AI_H
    #include "AI.h"
#endif

int main(){

	Board board;
	board.start_board();
	board.calc_attack();

	Move move[256];

	int player_b,player_w;   //���ƌ��̃v���[���[
	input_playmode(&player_b, &player_w);   //�v���C���[��l�Ԃɂ��邩�AAI�ɂ��邩
	int player_current;   //���݂̎�Ԃ̃v���[���[

	//�����̃��[�v
	while(1){
		//�`��
		print_board(&board);
		print_board_debug(&board);
		print_attack(&board);

		//�΋ǂ��I����Ă��邩�ǂ����̔���
		//��荇�����A�R�}���h�ő��s���ۂ������߂�
		//int flg_continue = -1;
		//while(flg_continue != 0 && flg_continue != 111){
		//	cout << "0:������ 111:��߂�\n";
		//	cin >> flg_continue;
		//}
		//if(flg_continue == 111) {break;}

		//���������̔���
		int flg_continue = board.check_win();
		if(flg_continue==BLACK || flg_continue==WHITE){
			if(flg_continue==BLACK){ cout << "BLACK�̏���\n"; }
			if(flg_continue==WHITE){ cout << "WHITE�̏���\n"; }
			break;
		}

		//��Ԃ̐ݒ�
		player_current = (board.turn%2==0 ? player_b : player_w );

		//�l�Ԃ��w��
		if(player_current = HUMAN){
			bool flg_undo;
			input_human_move(&board,&move[board.turn],&flg_undo);
			if(flg_undo == false){
			    board.do_move(&move[board.turn]);
			}else if(flg_undo == true){
				board.undo_move(&move[board.turn-1]);
			}
		//�R���s���[�^���w��
		}else if(player_current = COMPUTER){

		}
	}

	return 0;
}
