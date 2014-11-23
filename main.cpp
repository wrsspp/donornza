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

	int player_b,player_w;   //先手と後手のプレーヤー
	input_playmode(&player_b, &player_w);   //プレイヤーを人間にするか、AIにするか
	int player_current;   //現在の手番のプレーヤー

	//試合のループ
	while(1){
		//描画
		print_board(&board);
		print_board_debug(&board);
		print_attack(&board);

		//対局が終わっているかどうかの判定
		//取り合えず、コマンドで続行か否かを決める
		//int flg_continue = -1;
		//while(flg_continue != 0 && flg_continue != 111){
		//	cout << "0:続ける 111:やめる\n";
		//	cin >> flg_continue;
		//}
		//if(flg_continue == 111) {break;}

		//勝ち負けの判定
		int flg_continue = board.check_win();
		if(flg_continue==BLACK || flg_continue==WHITE){
			if(flg_continue==BLACK){ cout << "BLACKの勝ち\n"; }
			if(flg_continue==WHITE){ cout << "WHITEの勝ち\n"; }
			break;
		}

		//手番の設定
		player_current = (board.turn%2==0 ? player_b : player_w );

		//人間が指す
		if(player_current = HUMAN){
			bool flg_undo;
			input_human_move(&board,&move[board.turn],&flg_undo);
			if(flg_undo == false){
			    board.do_move(&move[board.turn]);
			}else if(flg_undo == true){
				board.undo_move(&move[board.turn-1]);
			}
		//コンピュータが指す
		}else if(player_current = COMPUTER){

		}
	}

	return 0;
}
