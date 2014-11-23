#pragma once

#ifndef ___STDAFX_H
	#define ___STDAFX_H
	#include "stdafx.h"
#endif

//指し手クラス
class Move{
public:
	int from;		//元の場所
	int to;			//動かす場所
	int capture;	//取った駒  何も取らなかった場合はNONEが入る

	bool is_NARI; //成・不成の識別

	//コンストラクタ
	Move() {
		from = to = capture = NONE;
		is_NARI = false;
	};
};

//着手可能手クラスを作る？
class Moves{
public:
	Move *moves;
	Moves(int size) { moves = new Move[size]; }
	~Moves() {delete[] moves;}
};

//局面のクラス(stdafx.hのenumを参考)
class Board{
public:
	//局面
	int ban[NUM_MASU];		//盤[各マス]駒の種類を格納
	int mochigoma[2][4];	//持ち駒[手番][駒の種類]の枚数
	int turn;				//ターン数、初期局面は0手目、順に1手目、2手目、,,,
	int attack[2][NUM_MASU];    //各マスの効きの数(王手の判定やSEEに使う予定)[手番][マス]

	//ハッシュ値、そのうちハッシュ表に使うかも
	__int64 hashval;

	//LIONの位置(王手やトライの判定に使う)
	int pos_blion;
	int pos_wlion;
	//LIONをcheckしている駒の位置(pos_p_check_lionで計算する)
	int pos_bp_check_wlion;  //白ライオンをcheckしている先手の駒
	int pos_wp_check_blion;  //黒ライオンをcheckしている後手の駒

	//空のコンストラクタ
	Board(){};
	//初期局面を作る
	void start_board();
	//途中からの局面を作る
	void make_board(const int* banmen,const int* mochigoma,const int* turn_num);

	//do(1手進める) undo(1手戻る)
	void do_move(const Move* move);
	void undo_move(const Move* move);

	//合法手の生成(返り値は合法手の数)(テストしてない。AIクラスに置いた方が良いかも)
	int make_moves(Move* move);
	//合法手のチェック(ルール上動けるところならライオンが相手の効きに入っても良い)
	bool is_legal_move(const Move* move);
	//attack(利き)を計算する
	void calc_attack();

	//簡単な勝負けの判定(返り値：BLACK黒勝ち、WHITE白勝ち、ANYCOLORどちらでもない)
	int easy_check_win();
	//勝負けの判定(返り値：BLACK黒勝ち、WHITE白勝ち、ANYCOLORどちらでもない)
	int check_win();
	//トライしているかどうかの判定
	int check_try();

	//LIONをcheckしている駒の位置の計算
	void pos_p_check_lion();  //ライオンをcheckしている駒の位置の計算
};