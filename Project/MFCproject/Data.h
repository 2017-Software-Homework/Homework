#ifndef DATA_H
#define DATA_H
#include <set>
#include <iostream>
using namespace std;

extern COLORREF color,color1;
extern int color_status;
extern int red,green,blue;
extern set<COLORREF> color_to_show;
extern int color_select_status;
extern int operation;
extern int choose_status,choose_rect,choose_circle,load_status,show_status;
extern int temp_operation;
extern int temp_choose;


struct choose_array
{
	bool left_or_right;//ѡ�������ͼ�����ұ���ͼ ��-LEFT-0 ��-RIGHT-1
	bool change_color;//�Ƿ������ɫ
	COLORREF color_to_set;//���ĺ����ɫ

	int operation;//operation��ʾ��-1 ��-2 ��-3
	int choose;//choose��ʾѡ���-1 ����-2 Բ-3

	CPoint point1;
	int point1_z;
	
	CPoint point2;
	int point2_z;
	//z��ʾ��ά�����е�z����

	int radius;

	choose_array* next;
};

extern choose_array *choose_head,*choose_temp1,*choose_temp2,*choose_generate1,*choose_generate2;//generate��������������Ԫ��

#endif