#ifndef ___CUI_H
	#define ___CUI_H
    #include "cui.h"
#endif

//盤の状態を表示
void print_board(const Board* board){
	clog << "後手の持ち駒 ";
	clog << "雛:"   << board->mochigoma[WHITE][HIYOKO] << "枚、";
	clog << "象:"   << board->mochigoma[WHITE][ZOU] << "枚、";
	clog << "麒麟:" << board->mochigoma[WHITE][KIRIN] << "枚\n";

	clog << "   A   B   C \n";
	clog << " +---+---+---+\n";
	clog << "1| "<<PRINT_BAN[board->ban[0]]<<"| "<<PRINT_BAN[board->ban[1]]<<"| "<<PRINT_BAN[board->ban[2]]<<"|\n";
	clog << " +---+---+---+\n";
	clog << "2| "<<PRINT_BAN[board->ban[3]]<<"| "<<PRINT_BAN[board->ban[4]]<<"| "<<PRINT_BAN[board->ban[5]]<<"|\n";
	clog << " +---+---+---+\n";
	clog << "3| "<<PRINT_BAN[board->ban[6]]<<"| "<<PRINT_BAN[board->ban[7]]<<"| "<<PRINT_BAN[board->ban[8]]<<"|\n";
	clog << " +---+---+---+\n";
	clog << "4| "<<PRINT_BAN[board->ban[9]]<<"| "<<PRINT_BAN[board->ban[10]]<<"| "<<PRINT_BAN[board->ban[11]]<<"|\n";
	clog << " +---+---+---+\n";

	clog << "先手の持ち駒 ";
	clog << "雛:"   << board->mochigoma[BLACK][HIYOKO] << "枚、";
	clog << "象:"   << board->mochigoma[BLACK][ZOU] << "枚、";
	clog << "麒麟:" << board->mochigoma[BLACK][KIRIN] << "枚\n";

	clog << board->turn << "手目終了時\n";
	
}

//盤の状態を表示(debug用)
void print_board_debug(const Board* board){
	clog << "pos_blion: " << board->pos_blion << endl;
	clog << "pos_wlion: " << board->pos_wlion << endl;
	if(DEBUG_MODE==true){
		clog << "pos_bp_check_wlion: " << board->pos_bp_check_wlion << endl;
		clog << "pos_wp_check_blion: " << board->pos_wp_check_blion << endl;
	}
}

//効きの状態を表示
void print_attack(const Board* board){
	clog << "先手の効き     後手の効き\n";
	clog << "  A  B  C       A  B  C \n";
	clog << " +--+--+--+    +--+--+--+\n";
	clog << "1| "<<board->attack[BLACK][0]<<"| "<<board->attack[BLACK][1]<<"| "<<board->attack[BLACK][2]<<"| " << "  1| "<<board->attack[WHITE][0]<<"| "<<board->attack[WHITE][1]<<"| "<<board->attack[WHITE][2]<<"|\n";
	clog << " +--+--+--+    +--+--+--+\n";
	clog << "2| "<<board->attack[BLACK][3]<<"| "<<board->attack[BLACK][4]<<"| "<<board->attack[BLACK][5]<<"| " << "  2| "<<board->attack[WHITE][3]<<"| "<<board->attack[WHITE][4]<<"| "<<board->attack[WHITE][5]<<"|\n";
	clog << " +--+--+--+    +--+--+--+\n";
	clog << "3| "<<board->attack[BLACK][6]<<"| "<<board->attack[BLACK][7]<<"| "<<board->attack[BLACK][8]<<"| " << "  3| "<<board->attack[WHITE][6]<<"| "<<board->attack[WHITE][7]<<"| "<<board->attack[WHITE][8]<<"|\n";
	clog << " +--+--+--+    +--+--+--+\n";
	clog << "4| "<<board->attack[BLACK][9]<<"| "<<board->attack[BLACK][10]<<"| "<<board->attack[BLACK][11]<<"| " << "  4| "<<board->attack[WHITE][9]<<"| "<<board->attack[WHITE][10]<<"| "<<board->attack[WHITE][11]<<"|\n";
	clog << " +--+--+--+    +--+--+--+\n";
	
}

//人間に指手を促す(正しく入力できたらtrue)
bool input_human_move(Board* board,Move* move,bool* flg_undo){
goto1:
	if(board->turn%2==0){
	    cout << "BLACK TURN\n";
	}else{
		cout << "WHITE TURN\n";
	}
	cout << "Input the move\n";
	cout << "from:";
	cin >> move->from;
	if(move->from == MATTA && board->turn >= 1){
		*flg_undo = true;
		move->from = NONE;
		return true;
	}
	*flg_undo = false;
	cout << "to:";
	cin >> move->to;
	
	if(board->is_legal_move(move) == false ){
		clog << "invalid move\n";
		goto goto1;
	}

	//駒を取る場合、取る駒の種類を記録
	if(board->ban[move->to] != EMPTY){
		move->capture = board->ban[move->to];
	}

	//成・不成りの選択
	int color = (board->turn%2==0 ? BLACK : WHITE);   //手番の色（先手はBLACK）
	if((board->ban[move->from] == B_HIYOKO && 3 <= move->from && move->from <= 5 && color == BLACK) ||
	   (board->ban[move->from] == W_HIYOKO && 6 <= move->from && move->from <= 8 && color == WHITE)){
		int flg = -1;
		while(flg!=0 && flg!=1){
		    cout << "0:promote ,1:not promote \n";
			cin >> flg;
		}
		if(flg == 0){
			move->is_NARI = true;
		}else{
			move->is_NARI = false;
		}
	}

	return true;
}

//プレイヤーを人間にするか、AIにするか
void input_playmode(int* player_b, int* player_w){
	int input;
goto2:
	cout << "Input game mode\n";
	cout << "0:HUMAN vs HUMAN\n";
	cout << "1:HUMAN vs COMPUTER\n";
	cout << "2:COMPUTER vs HUMAN\n";
	cout << "3:COMPUTER vs COMPUTER\n";
	cin >> input;
	if( input == 0 ){
		*player_b = HUMAN;
		*player_w = HUMAN;
	}else if( input == 1 ){
		*player_b = HUMAN;
		*player_w = COMPUTER;
	}else if( input == 2 ){
		*player_b = COMPUTER;
		*player_w = HUMAN;
	}else if( input == 3 ){
		*player_b = COMPUTER;
		*player_w = COMPUTER;
	}else{
		goto goto2;
	}
	
}
