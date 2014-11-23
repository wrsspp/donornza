#pragma once

#ifndef ___STDAFX_H
	#define ___STDAFX_H
	#include "stdafx.h"
#endif

//�w����N���X
class Move{
public:
	int from;		//���̏ꏊ
	int to;			//�������ꏊ
	int capture;	//�������  �������Ȃ������ꍇ��NONE������

	bool is_NARI; //���E�s���̎���

	//�R���X�g���N�^
	Move() {
		from = to = capture = NONE;
		is_NARI = false;
	};
};

//����\��N���X�����H
class Moves{
public:
	Move *moves;
	Moves(int size) { moves = new Move[size]; }
	~Moves() {delete[] moves;}
};

//�ǖʂ̃N���X(stdafx.h��enum���Q�l)
class Board{
public:
	//�ǖ�
	int ban[NUM_MASU];		//��[�e�}�X]��̎�ނ��i�[
	int mochigoma[2][4];	//������[���][��̎��]�̖���
	int turn;				//�^�[�����A�����ǖʂ�0��ځA����1��ځA2��ځA,,,
	int attack[2][NUM_MASU];    //�e�}�X�̌����̐�(����̔����SEE�Ɏg���\��)[���][�}�X]

	//�n�b�V���l�A���̂����n�b�V���\�Ɏg������
	__int64 hashval;

	//LION�̈ʒu(�����g���C�̔���Ɏg��)
	int pos_blion;
	int pos_wlion;
	//LION��check���Ă����̈ʒu(pos_p_check_lion�Ōv�Z����)
	int pos_bp_check_wlion;  //�����C�I����check���Ă�����̋�
	int pos_wp_check_blion;  //�����C�I����check���Ă�����̋�

	//��̃R���X�g���N�^
	Board(){};
	//�����ǖʂ����
	void start_board();
	//�r������̋ǖʂ����
	void make_board(const int* banmen,const int* mochigoma,const int* turn_num);

	//do(1��i�߂�) undo(1��߂�)
	void do_move(const Move* move);
	void undo_move(const Move* move);

	//���@��̐���(�Ԃ�l�͍��@��̐�)(�e�X�g���ĂȂ��BAI�N���X�ɒu���������ǂ�����)
	int make_moves(Move* move);
	//���@��̃`�F�b�N(���[���㓮����Ƃ���Ȃ烉�C�I��������̌����ɓ����Ă��ǂ�)
	bool is_legal_move(const Move* move);
	//attack(����)���v�Z����
	void calc_attack();

	//�ȒP�ȏ������̔���(�Ԃ�l�FBLACK�������AWHITE�������AANYCOLOR�ǂ���ł��Ȃ�)
	int easy_check_win();
	//�������̔���(�Ԃ�l�FBLACK�������AWHITE�������AANYCOLOR�ǂ���ł��Ȃ�)
	int check_win();
	//�g���C���Ă��邩�ǂ����̔���
	int check_try();

	//LION��check���Ă����̈ʒu�̌v�Z
	void pos_p_check_lion();  //���C�I����check���Ă����̈ʒu�̌v�Z
};