#ifndef ___CUI_H
	#define ___CUI_H
    #include "cui.h"
#endif

//�Ղ̏�Ԃ�\��
void print_board(const Board* board){
	clog << "���̎����� ";
	clog << "��:"   << board->mochigoma[WHITE][HIYOKO] << "���A";
	clog << "��:"   << board->mochigoma[WHITE][ZOU] << "���A";
	clog << "�i��:" << board->mochigoma[WHITE][KIRIN] << "��\n";

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

	clog << "���̎����� ";
	clog << "��:"   << board->mochigoma[BLACK][HIYOKO] << "���A";
	clog << "��:"   << board->mochigoma[BLACK][ZOU] << "���A";
	clog << "�i��:" << board->mochigoma[BLACK][KIRIN] << "��\n";

	clog << board->turn << "��ڏI����\n";
	
}

//�Ղ̏�Ԃ�\��(debug�p)
void print_board_debug(const Board* board){
	clog << "pos_blion: " << board->pos_blion << endl;
	clog << "pos_wlion: " << board->pos_wlion << endl;
	if(DEBUG_MODE==true){
		clog << "pos_bp_check_wlion: " << board->pos_bp_check_wlion << endl;
		clog << "pos_wp_check_blion: " << board->pos_wp_check_blion << endl;
	}
}

//�����̏�Ԃ�\��
void print_attack(const Board* board){
	clog << "���̌���     ���̌���\n";
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

//�l�ԂɎw��𑣂�(���������͂ł�����true)
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

	//������ꍇ�A����̎�ނ��L�^
	if(board->ban[move->to] != EMPTY){
		move->capture = board->ban[move->to];
	}

	//���E�s����̑I��
	int color = (board->turn%2==0 ? BLACK : WHITE);   //��Ԃ̐F�i����BLACK�j
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

//�v���C���[��l�Ԃɂ��邩�AAI�ɂ��邩
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
