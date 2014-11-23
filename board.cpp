#ifndef ___BOARD_H
	#define ___BOARD_H
    #include "board.h"
#endif

//初期局面を作る
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

//合法手の生成(返り値は合法手の数) (2014/11/16動作未確認)
int Board::make_moves(Move* move){
	int count_move = -1;  //moveの配列の要素数(合法手のカウント)
	int color = (turn%2==0 ? BLACK : WHITE);   //手番の色（先手はBLACK）
	
	//盤上に持ち駒を置く
	//駒のいるマスには置かない
	for(int ip=HIYOKO;ip<=KIRIN;ip++){
		if(mochigoma[color][ip] > 0){
			for(int masu=0;masu<NUM_MASU;masu++){
				if(ban[masu] == EMPTY){
					count_move++;
					move[count_move].from = NUM_MASU + ip;  //雛は12,像は13,キリンは14
					move[count_move].to   = masu;           //打った先のマス
					move[count_move].capture = NONE;        //持ち駒を打つときは駒は取らない
					move[count_move].is_NARI = false;
				}
			}
		}
	}

	//手番側の駒がいるマスについて、サーチ
	//その駒が動けるマスに、手番側の駒がいない&&ライオンの場合、相手の利きがいない
	calc_attack();   //LIONの動きのために、効きを調べる
	for(int from=0;from<NUM_MASU;from++){
		if(ban[from] /= EMPTY){
			if(color==BLACK && ban[from]<WHP){
				for(int to=0;to<CANMOVE[ban[from]][from][8];to++){
					if(ban[to] == EMPTY){   //移動先が何もなかった場合
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
					}else if(ban[to] >=WHP ){   //移動先が白（駒が取れる）場合
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
					if(ban[to] == EMPTY){   //移動先が何もなかった場合
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
					}else if(ban[to] <WHP ){   //移動先が黒（駒が取れる）場合
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

//attack(利き)を計算する
void Board::calc_attack(){
	//初期化
	for(int i=0;i<NUM_MASU;i++){
		attack[BLACK][i] = 0;
		attack[WHITE][i] = 0;
	}
	
	int masu_attack;  //効きがあるマスの数え上げに使用
	//各マス毎に計算
	for(int from=0;from<NUM_MASU;from++){
		//そのマスに駒がいる=EMPTYでない
		if(ban[from]!=EMPTY){
			//その駒が動ける範囲に効きの数を足しあげる
			for(int to=0;to<CANMOVE[ban[from]][from][8];to++){
				masu_attack = CANMOVE[ban[from]][from][to];
				if(ban[from]<WHP){  //先手番の駒の時
				    attack[BLACK][masu_attack]++;
				} else {            //後手番の駒の時
					attack[WHITE][masu_attack]++;
				}
			}
		}
	}
}

//合法手のチェック(ルール上動けるところならライオンが相手の効きに入っても良い)
bool Board::is_legal_move(const Move* move){
	int color = (turn%2==0 ? BLACK : WHITE);   //手番の色（先手はBLACK）

	//盤上の駒を動かす場合
	if(0 <= move->from && move->from <= 11 ){
		if(ban[move->from] != EMPTY){
			//敵の駒を動かしていたらダメ
			if(color == BLACK && ban[move->from] >= WHP){
				return false;
			} else if(color == WHITE && ban[move->from] < WHP){
				return false;
			}
			//動かせない位置に駒を動かしたらダメ
			bool is_check = false;
			for(int im=0;im<CANMOVE[ban[move->from]][move->from][8];im++){
				if(CANMOVE[ban[move->from]][move->from][im] == move->to){
					is_check = true;
				}
			}
			if(is_check == false){
				return false;
			}
			//動かした先の位置に自分の駒がいるとダメ
			if(ban[move->to]==EMPTY){
				return true;
			}else if(color == BLACK && ban[move->to] >= WHP){
				return true;
			}else if(color == WHITE && ban[move->to] <WHP){
				return true;
			}
		}
	//持ち駒を使う場合
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

//簡単な勝負けの判定(返り値：BLACK黒勝ち、WHITE白勝ち、ANYCOLORどちらでもない)
int Board::easy_check_win(){
	int color = (turn%2==0 ? BLACK : WHITE);   //手番の色（先手はBLACK）
	int anti_color = (turn%2==0 ? WHITE : BLACK);   //相手の色（先手はBLACK）

	int flg_try = check_try();
	if(flg_try == BLACK){
		return BLACK;
	}else if(flg_try == WHITE){
		return WHITE;
	}

	//LIONをcheckしている駒の位置の計算
    pos_p_check_lion();

	//王がチェックメイトされていて、その駒を取り返せず逃げることが出来ない場合
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

//勝負けの判定(返り値：BLACK黒勝ち、WHITE白勝ち、ANYCOLORどちらでもない)
int Board::check_win(){
	int flg_try = check_try();
	if(flg_try == BLACK){
		return BLACK;
	}else if(flg_try == WHITE){
		return WHITE;
	}

	bool is_bl = false, is_wl = false;  //黒、白のライオンがいるかどうかに使用
	//盤上にライオンがいるかどうか?
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

//トライしているかどうかの判定(返り値：BLACK黒勝ち、WHITE白勝ち、ANYCOLORどちらでもない)
int Board::check_try(){
	//トライしているかどうか
	if(pos_blion==1 && attack[WHITE][pos_blion] == 0 ){
		return BLACK;
	}
	if(pos_wlion==10 && attack[BLACK][pos_wlion] == 0){
		return WHITE;
	}
	return ANYCOLOR;
};

//do(1手進める)
void Board::do_move(const Move* move){
	int color = (turn%2==0 ? BLACK : WHITE);   //手番の色（先手はBLACK）
	int anti_color = (turn%2==0 ? WHITE : BLACK);   //相手の色（先手はBLACK）
	int koma_move;   //動かす駒の種類
	int koma_capt;     //取られる駒の種類(mochigomaの要素に適応させるため、途中で値が変わる)

	//盤上の駒を動かす場合
	if(0 <= move->from && move->from <= 11){
		koma_move = ban[move->from];
		//attackの再計算
		for(int im=0;im<CANMOVE[koma_move][move->from][8];im++){  //動かす前の効きを消す
			attack[color][CANMOVE[koma_move][move->from][im]] --;
		}
		//LIONの場合はpositionの変更
		if(koma_move == B_LION){
			pos_blion = move->to;
		}else if(koma_move == W_LION){
			pos_wlion = move->to;
		}
		//駒を取らない時
		if(ban[move->to] == EMPTY){
			ban[move->to]   = koma_move;
			ban[move->from] = EMPTY;
		//駒を取る時
		} else {
			koma_capt = ban[move->to];
			//attackの再計算
			for(int im=0;im<CANMOVE[koma_capt][move->to][8];im++){  //取られた駒の効きを消す
				attack[anti_color][CANMOVE[koma_capt][move->to][im]] --;
			}
			if(koma_capt == B_CHICKEN || koma_capt == W_CHICKEN){  //CHICKENを取った時はHIYOKOにする。これ以降、koma_captは使わない
				koma_capt -= (CHICKEN);
			}
			if(color == BLACK){
				koma_capt -= WHP;
			}
			ban[move->to]   = koma_move;
			ban[move->from] = EMPTY;
			mochigoma[color][koma_capt]++;
		}
		//成るとき
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
	
	//attackの再計算
	for(int im=0;im<CANMOVE[koma_move][move->to][8];im++){   //動かした後の効きを足す
		attack[color][CANMOVE[koma_move][move->to][im]] ++;
	}
	
	//手番を進める
	turn = turn + 1;
}

//undo(1手戻る)
void Board::undo_move(const Move* move){
	int color = (turn%2==1 ? BLACK : WHITE);   //手番の色（先手はBLACK）他の関数のcolorと逆なのに注意
	int anti_color = (turn%2==1 ? WHITE : BLACK);   //相手の色（先手はBLACK）手番がWHITEでも、戻すのはBLACKの手番なので
	int koma_move = ban[move->to];;   //動かした駒の種類
	int koma_capt;     //取られた駒の種類(mochigomaの要素に適応させるため、途中で値が変わる)

	//attackの再計算
	for(int im=0;im<CANMOVE[koma_move][move->to][8];im++){  //動かした先の効きを消す
		attack[color][CANMOVE[koma_move][move->to][im]] --;
	}

	//盤上の駒を動かした場合
	if(0<=move->from && move->from<=11){
		//LIONの場合はposition変更
		if(koma_move == B_LION){
			pos_blion = move->from;
		}else if(koma_move == W_LION){
			pos_wlion = move->from;
		}
		//駒を取らなかった時
		if(move->capture == NONE){
			ban[move->to] = EMPTY;
			ban[move->from] = koma_move;
		//駒を取ったとき
		}else{
			koma_capt = move->capture;
			ban[move->to] = move->capture;
			ban[move->from] = koma_move;
			if(koma_capt == B_CHICKEN || koma_capt == W_CHICKEN){  //CHICKENを取った時はHIYOKOにする。これ以降、koma_captは使わない
				koma_capt -= (CHICKEN);
			}
			if(color == BLACK){
				koma_capt -= WHP;
			}
			mochigoma[color][koma_capt]--;
			//attackの再計算
			for(int im=0;im<CANMOVE[move->capture][move->to][8];im++){  //取られた駒の効きを足す
				attack[anti_color][CANMOVE[move->capture][move->to][im]] ++;
			}
		}
		//駒を成ったとき、雛に戻す
		if(move->is_NARI==true){
			ban[move->from] -= CHICKEN;
			koma_move = ban[move->from];
		}
		//attackの再計算
		for(int im=0;im<CANMOVE[koma_move][move->from][8];im++){  //動かす前の効きを足す
			attack[color][CANMOVE[koma_move][move->from][im]] ++;
		}

	//持ち駒を使った場合
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

	//手番を戻す
	turn = turn - 1;
}

//LIONをcheckしている駒の位置の計算
void Board::pos_p_check_lion(){  //ライオンをcheckしている駒の位置の計算
	if(attack[WHITE][pos_blion] >= 1){
		int pos;      //相手の位置
		int koma;     //相手の駒
		int pos_relative; //相手の位置-自分の位置+OFSET_SRRNDを入れる
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
		int pos;      //相手の位置
		int koma;     //相手の駒
		int pos_relative; //相手の位置-自分の位置+OFSET_SRRNDを入れる
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