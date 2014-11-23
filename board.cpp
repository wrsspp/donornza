#ifndef ___BOARD_H
	#define ___BOARD_H
    #include "board.h"
#endif

//�����ǖʂ����
void Board::start_board(){
	if(DEBUG_MODE==false){
		ban[0] = W_KIRIN;
		ban[1] = W_LION;
		ban[2] = W_ZOU;
		ban[3] = EMPTY;
		ban[4] = W_HIYOKO;
		ban[5] = EMPTY;
		ban[6] = EMPTY;
		ban[7] = B_HIYOKO;
		ban[8] = EMPTY;
		ban[9] = B_ZOU;
		ban[10] =B_LION;
		ban[11] =B_KIRIN;

		turn = 0;

		for(int i=0;i<4;i++){
			mochigoma[BLACK][i] = 0;
			mochigoma[WHITE][i] = 0;
		}
		for(int i=0;i<NUM_MASU;i++){
			attack[BLACK][i] = 0;
			attack[WHITE][i] = 0;
		}
		pos_blion = 10;
		pos_wlion = 1;
		pos_bp_check_wlion = NONE;
		pos_wp_check_blion = NONE;
	}else if(DEBUG_MODE==true){
		ban[0] = W_LION;
		ban[1] = EMPTY;
		ban[2] = W_ZOU;
		ban[3] = W_KIRIN;
		ban[4] = B_HIYOKO;
		ban[5] = EMPTY;
		ban[6] = EMPTY;
		ban[7] = EMPTY;
		ban[8] = B_KIRIN;
		ban[9] = B_ZOU;
		ban[10] =B_LION;
		ban[11] =EMPTY;

		turn = 0;

		for(int i=0;i<4;i++){
			mochigoma[BLACK][i] = 0;
			mochigoma[WHITE][i] = 0;
		}
		mochigoma[WHITE][HIYOKO] = 1;
		for(int i=0;i<NUM_MASU;i++){
			attack[BLACK][i] = 0;
			attack[WHITE][i] = 0;
		}
		pos_blion = 10;
		pos_wlion = 0;
		pos_bp_check_wlion = NONE;
		pos_wp_check_blion = NONE;
	}
}

//���@��̐���(�Ԃ�l�͍��@��̐�) (2014/11/16���얢�m�F)
int Board::make_moves(Move* move){
	int count_move = -1;  //move�̔z��̗v�f��(���@��̃J�E���g)
	int color = (turn%2==0 ? BLACK : WHITE);   //��Ԃ̐F�i����BLACK�j
	
	//�Տ�Ɏ������u��
	//��̂���}�X�ɂ͒u���Ȃ�
	for(int ip=HIYOKO;ip<=KIRIN;ip++){
		if(mochigoma[color][ip] > 0){
			for(int masu=0;masu<NUM_MASU;masu++){
				if(ban[masu] == EMPTY){
					count_move++;
					move[count_move].from = NUM_MASU + ip;  //����12,����13,�L������14
					move[count_move].to   = masu;           //�ł�����̃}�X
					move[count_move].capture = NONE;        //�������łƂ��͋�͎��Ȃ�
					move[count_move].is_NARI = false;
				}
			}
		}
	}

	//��ԑ��̋����}�X�ɂ��āA�T�[�`
	//���̋������}�X�ɁA��ԑ��̋���Ȃ�&&���C�I���̏ꍇ�A����̗��������Ȃ�
	calc_attack();   //LION�̓����̂��߂ɁA�����𒲂ׂ�
	for(int from=0;from<NUM_MASU;from++){
		if(ban[from] /= EMPTY){
			if(color==BLACK && ban[from]<WHP){
				for(int to=0;to<CANMOVE[ban[from]][from][8];to++){
					if(ban[to] == EMPTY){   //�ړ��悪�����Ȃ������ꍇ
						if(ban[from]==B_LION){
							if(attack[WHITE][to]<=0){
								count_move++;
								move[count_move].from = from;
								move[count_move].to   = to;
								move[count_move].capture = NONE;
								move[count_move].is_NARI = false;
							}
						}else {
							count_move++;
							move[count_move].from = from;
							move[count_move].to   = to;
							move[count_move].capture = NONE;
							if(ban[to]==B_HIYOKO && 0<=to && to<=2){
								move[count_move].is_NARI = true;
							}else{
								move[count_move].is_NARI = false;
							}
						}
					}else if(ban[to] >=WHP ){   //�ړ��悪���i�����j�ꍇ
						if(ban[from]==B_LION){
							if(attack[WHITE][to]<=0){
								count_move++;
								move[count_move].from = from;
								move[count_move].to   = to;
								move[count_move].capture = ban[to];
								move[count_move].is_NARI = false;
							}
						}else {
							count_move++;
							move[count_move].from = from;
							move[count_move].to   = to;
							move[count_move].capture = ban[to];
							if(ban[to]==B_HIYOKO && 0<=to && to<=2){
								move[count_move].is_NARI = true;
							}else{
								move[count_move].is_NARI = false;
							}
						}
					}
				}
			} else if(color==WHITE && ban[from]>=WHP){
				for(int to=0;to<CANMOVE[ban[from]][from][8];to++){
					if(ban[to] == EMPTY){   //�ړ��悪�����Ȃ������ꍇ
						if(ban[from]==W_LION){
							if(attack[BLACK][to]<=0){
								count_move++;
								move[count_move].from = from;
								move[count_move].to   = to;
								move[count_move].capture = NONE;
								move[count_move].is_NARI = false;
							}
						}else {
							count_move++;
							move[count_move].from = from;
							move[count_move].to   = to;
							move[count_move].capture = NONE;
							if(ban[to]==W_HIYOKO && 9<=to && to<=11){
								move[count_move].is_NARI = true;
							}else{
								move[count_move].is_NARI = false;
							}
						}
					}else if(ban[to] <WHP ){   //�ړ��悪���i�����j�ꍇ
						if(ban[from]==W_LION){
							if(attack[BLACK][to]<=0){
								count_move++;
								move[count_move].from = from;
								move[count_move].to   = to;
								move[count_move].capture = ban[to];
								move[count_move].is_NARI = false;
							}
						}else {
							count_move++;
							move[count_move].from = from;
							move[count_move].to   = to;
							move[count_move].capture = ban[to];
							if(ban[to]==W_HIYOKO && 9<=to && to<=11){
								move[count_move].is_NARI = true;
							}else{
								move[count_move].is_NARI = false;
							}
						}
					}
				}
			}
		}
	}

	return count_move;
}

//attack(����)���v�Z����
void Board::calc_attack(){
	//������
	for(int i=0;i<NUM_MASU;i++){
		attack[BLACK][i] = 0;
		attack[WHITE][i] = 0;
	}
	
	int masu_attack;  //����������}�X�̐����グ�Ɏg�p
	//�e�}�X���Ɍv�Z
	for(int from=0;from<NUM_MASU;from++){
		//���̃}�X�ɋ����=EMPTY�łȂ�
		if(ban[from]!=EMPTY){
			//���̋������͈͂Ɍ����̐��𑫂�������
			for(int to=0;to<CANMOVE[ban[from]][from][8];to++){
				masu_attack = CANMOVE[ban[from]][from][to];
				if(ban[from]<WHP){  //���Ԃ̋�̎�
				    attack[BLACK][masu_attack]++;
				} else {            //���Ԃ̋�̎�
					attack[WHITE][masu_attack]++;
				}
			}
		}
	}
}

//���@��̃`�F�b�N(���[���㓮����Ƃ���Ȃ烉�C�I��������̌����ɓ����Ă��ǂ�)
bool Board::is_legal_move(const Move* move){
	int color = (turn%2==0 ? BLACK : WHITE);   //��Ԃ̐F�i����BLACK�j

	//�Տ�̋�𓮂����ꍇ
	if(0 <= move->from && move->from <= 11 ){
		if(ban[move->from] != EMPTY){
			//�G�̋�𓮂����Ă�����_��
			if(color == BLACK && ban[move->from] >= WHP){
				return false;
			} else if(color == WHITE && ban[move->from] < WHP){
				return false;
			}
			//�������Ȃ��ʒu�ɋ�𓮂�������_��
			bool is_check = false;
			for(int im=0;im<CANMOVE[ban[move->from]][move->from][8];im++){
				if(CANMOVE[ban[move->from]][move->from][im] == move->to){
					is_check = true;
				}
			}
			if(is_check == false){
				return false;
			}
			//����������̈ʒu�Ɏ����̋����ƃ_��
			if(ban[move->to]==EMPTY){
				return true;
			}else if(color == BLACK && ban[move->to] >= WHP){
				return true;
			}else if(color == WHITE && ban[move->to] <WHP){
				return true;
			}
		}
	//��������g���ꍇ
	} else if(move->from==12){
		if(mochigoma[color][HIYOKO] >= 1 && ban[move->to]==EMPTY){
			return true;
		}
	} else if(move->from==13){
		if(mochigoma[color][ZOU] >= 1 && ban[move->to]==EMPTY){
			return true;
		}
	} else if(move->from==14){
		if(mochigoma[color][KIRIN] >= 1 && ban[move->to]==EMPTY){
			return true;
		}
	}
	return false;
}

//�ȒP�ȏ������̔���(�Ԃ�l�FBLACK�������AWHITE�������AANYCOLOR�ǂ���ł��Ȃ�)
int Board::easy_check_win(){
	int color = (turn%2==0 ? BLACK : WHITE);   //��Ԃ̐F�i����BLACK�j
	int anti_color = (turn%2==0 ? WHITE : BLACK);   //����̐F�i����BLACK�j

	int flg_try = check_try();
	if(flg_try == BLACK){
		return BLACK;
	}else if(flg_try == WHITE){
		return WHITE;
	}

	//LION��check���Ă����̈ʒu�̌v�Z
    pos_p_check_lion();

	//�����`�F�b�N���C�g����Ă��āA���̋�����Ԃ��������邱�Ƃ��o���Ȃ��ꍇ
	if(color == BLACK){
		if(attack[BLACK][pos_wlion]>=1 && attack[WHITE][pos_bp_check_wlion] <= 1){
			for(int im=0;im<CANMOVE[W_LION][pos_wlion][8];im++){
				if(attack[BLACK][CANMOVE[W_LION][pos_wlion][im]] >= 1 || ban[CANMOVE[W_LION][pos_wlion][im]] >= WHP ){

				} else {
					break;
				}
				return BLACK;
			}
		}
	}else if(color == WHITE){
		if(attack[WHITE][pos_blion]>=1 && attack[BLACK][pos_wp_check_blion] <= 1){
			for(int im=0;im<CANMOVE[B_LION][pos_blion][8];im++){
				if(attack[WHITE][CANMOVE[B_LION][pos_blion][im]] >= 1 || ban[CANMOVE[B_LION][pos_wlion][im]] < WHP ){

				} else {
					break;
				}
				return WHITE;
			}
		}
	}
	return ANYCOLOR;
}

//�������̔���(�Ԃ�l�FBLACK�������AWHITE�������AANYCOLOR�ǂ���ł��Ȃ�)
int Board::check_win(){
	int flg_try = check_try();
	if(flg_try == BLACK){
		return BLACK;
	}else if(flg_try == WHITE){
		return WHITE;
	}

	bool is_bl = false, is_wl = false;  //���A���̃��C�I�������邩�ǂ����Ɏg�p
	//�Տ�Ƀ��C�I�������邩�ǂ���?
	for(int mc=0;mc<NUM_MASU;mc++){
		if(ban[mc] == B_LION){
			is_bl = true;
		}else if(ban[mc] == W_LION){
			is_wl = true;
		}
	}

	if(is_bl==true && is_wl==false){
		return BLACK;
	}else if(is_bl==false && is_wl== true){
		return WHITE;
	}

	return ANYCOLOR;
};

//�g���C���Ă��邩�ǂ����̔���(�Ԃ�l�FBLACK�������AWHITE�������AANYCOLOR�ǂ���ł��Ȃ�)
int Board::check_try(){
	//�g���C���Ă��邩�ǂ���
	if(pos_blion==1 && attack[WHITE][pos_blion] == 0 ){
		return BLACK;
	}
	if(pos_wlion==10 && attack[BLACK][pos_wlion] == 0){
		return WHITE;
	}
	return ANYCOLOR;
};

//do(1��i�߂�)
void Board::do_move(const Move* move){
	int color = (turn%2==0 ? BLACK : WHITE);   //��Ԃ̐F�i����BLACK�j
	int anti_color = (turn%2==0 ? WHITE : BLACK);   //����̐F�i����BLACK�j
	int koma_move;   //��������̎��
	int koma_capt;     //������̎��(mochigoma�̗v�f�ɓK�������邽�߁A�r���Œl���ς��)

	//�Տ�̋�𓮂����ꍇ
	if(0 <= move->from && move->from <= 11){
		koma_move = ban[move->from];
		//attack�̍Čv�Z
		for(int im=0;im<CANMOVE[koma_move][move->from][8];im++){  //�������O�̌���������
			attack[color][CANMOVE[koma_move][move->from][im]] --;
		}
		//LION�̏ꍇ��position�̕ύX
		if(koma_move == B_LION){
			pos_blion = move->to;
		}else if(koma_move == W_LION){
			pos_wlion = move->to;
		}
		//������Ȃ���
		if(ban[move->to] == EMPTY){
			ban[move->to]   = koma_move;
			ban[move->from] = EMPTY;
		//�����鎞
		} else {
			koma_capt = ban[move->to];
			//attack�̍Čv�Z
			for(int im=0;im<CANMOVE[koma_capt][move->to][8];im++){  //���ꂽ��̌���������
				attack[anti_color][CANMOVE[koma_capt][move->to][im]] --;
			}
			if(koma_capt == B_CHICKEN || koma_capt == W_CHICKEN){  //CHICKEN�����������HIYOKO�ɂ���B����ȍ~�Akoma_capt�͎g��Ȃ�
				koma_capt -= (CHICKEN);
			}
			if(color == BLACK){
				koma_capt -= WHP;
			}
			ban[move->to]   = koma_move;
			ban[move->from] = EMPTY;
			mochigoma[color][koma_capt]++;
		}
		//����Ƃ�
		if(move->is_NARI==true && 
			((ban[move->to] == B_HIYOKO && color == BLACK) || (ban[move->to] == W_HIYOKO && color == WHITE))){
			ban[move->to] = ( color==BLACK ? B_CHICKEN : W_CHICKEN );
			koma_move = ban[move->to];
		}
	} else if(move->from == 12){
		koma_move = (color==BLACK ? B_HIYOKO : W_HIYOKO);
		mochigoma[color][HIYOKO] --;
		ban[move->to] = koma_move;
	} else if(move->from == 13){
		koma_move = (color==BLACK ? B_ZOU : W_ZOU);
		mochigoma[color][ZOU] --;
		ban[move->to] = koma_move;
	} else if(move->from == 14){
		koma_move = (color==BLACK ? B_KIRIN : W_KIRIN);
		mochigoma[color][KIRIN] --;
		ban[move->to] = koma_move;
	}
	
	//attack�̍Čv�Z
	for(int im=0;im<CANMOVE[koma_move][move->to][8];im++){   //����������̌����𑫂�
		attack[color][CANMOVE[koma_move][move->to][im]] ++;
	}
	
	//��Ԃ�i�߂�
	turn = turn + 1;
}

//undo(1��߂�)
void Board::undo_move(const Move* move){
	int color = (turn%2==1 ? BLACK : WHITE);   //��Ԃ̐F�i����BLACK�j���̊֐���color�Ƌt�Ȃ̂ɒ���
	int anti_color = (turn%2==1 ? WHITE : BLACK);   //����̐F�i����BLACK�j��Ԃ�WHITE�ł��A�߂��̂�BLACK�̎�ԂȂ̂�
	int koma_move = ban[move->to];;   //����������̎��
	int koma_capt;     //���ꂽ��̎��(mochigoma�̗v�f�ɓK�������邽�߁A�r���Œl���ς��)

	//attack�̍Čv�Z
	for(int im=0;im<CANMOVE[koma_move][move->to][8];im++){  //����������̌���������
		attack[color][CANMOVE[koma_move][move->to][im]] --;
	}

	//�Տ�̋�𓮂������ꍇ
	if(0<=move->from && move->from<=11){
		//LION�̏ꍇ��position�ύX
		if(koma_move == B_LION){
			pos_blion = move->from;
		}else if(koma_move == W_LION){
			pos_wlion = move->from;
		}
		//������Ȃ�������
		if(move->capture == NONE){
			ban[move->to] = EMPTY;
			ban[move->from] = koma_move;
		//���������Ƃ�
		}else{
			koma_capt = move->capture;
			ban[move->to] = move->capture;
			ban[move->from] = koma_move;
			if(koma_capt == B_CHICKEN || koma_capt == W_CHICKEN){  //CHICKEN�����������HIYOKO�ɂ���B����ȍ~�Akoma_capt�͎g��Ȃ�
				koma_capt -= (CHICKEN);
			}
			if(color == BLACK){
				koma_capt -= WHP;
			}
			mochigoma[color][koma_capt]--;
			//attack�̍Čv�Z
			for(int im=0;im<CANMOVE[move->capture][move->to][8];im++){  //���ꂽ��̌����𑫂�
				attack[anti_color][CANMOVE[move->capture][move->to][im]] ++;
			}
		}
		//��𐬂����Ƃ��A���ɖ߂�
		if(move->is_NARI==true){
			ban[move->from] -= CHICKEN;
			koma_move = ban[move->from];
		}
		//attack�̍Čv�Z
		for(int im=0;im<CANMOVE[koma_move][move->from][8];im++){  //�������O�̌����𑫂�
			attack[color][CANMOVE[koma_move][move->from][im]] ++;
		}

	//��������g�����ꍇ
	} else if(move->from==12){
		mochigoma[color][HIYOKO]++;
		ban[move->to] = EMPTY;
	}else if(move->from==13){
		mochigoma[color][ZOU]++;
		ban[move->to] = EMPTY;
	}else if(move->from==14){
		mochigoma[color][KIRIN]++;
		ban[move->to] = EMPTY;
	}

	//��Ԃ�߂�
	turn = turn - 1;
}

//LION��check���Ă����̈ʒu�̌v�Z
void Board::pos_p_check_lion(){  //���C�I����check���Ă����̈ʒu�̌v�Z
	if(attack[WHITE][pos_blion] >= 1){
		int pos;      //����̈ʒu
		int koma;     //����̋�
		int pos_relative; //����̈ʒu-�����̈ʒu+OFSET_SRRND������
		for(int im=0;im<CANMOVE[B_LION][pos_blion][8];im++){
			pos = CANMOVE[B_LION][pos_blion][im];
			koma= ban[pos];
			pos_relative = pos - pos_blion + OFSET_SRRND;
			if(koma >= WHP && koma != EMPTY){
				if(IS_CHECK[BLACK][pos_relative][koma]==true){
					pos_wp_check_blion = pos;
				}
			}
		}
	}else{
		pos_wp_check_blion = NONE;
	}
	if(attack[BLACK][pos_wlion] >= 1){
		int pos;      //����̈ʒu
		int koma;     //����̋�
		int pos_relative; //����̈ʒu-�����̈ʒu+OFSET_SRRND������
		for(int im=0;im<CANMOVE[W_LION][pos_wlion][8];im++){
			pos = CANMOVE[W_LION][pos_wlion][im];
			koma= ban[pos];
			pos_relative = pos - pos_wlion + OFSET_SRRND;
			if(koma < WHP && koma != EMPTY){
				if(IS_CHECK[WHITE][pos_relative][koma]==true){
					pos_bp_check_wlion = pos;
				}
			}
		}
	}else{
		pos_bp_check_wlion = NONE;
	}
}