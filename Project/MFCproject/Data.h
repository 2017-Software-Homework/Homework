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
	bool left_or_right;//选择左边视图还是右边视图 左-LEFT-0 右-RIGHT-1
	bool change_color;//是否更改颜色
	COLORREF color_to_set;//更改后的颜色

	int operation;//operation表示交-1 并-2 差-3
	int choose;//choose表示选择点-1 矩形-2 圆-3

	CPoint point1;
	int point1_z;
	
	CPoint point2;
	int point2_z;
	//z表示三维坐标中的z坐标

	int radius;

	choose_array* next;
};

extern choose_array *choose_head,*choose_temp1,*choose_temp2,*choose_generate1,*choose_generate2;//generate仅适用于生成新元素

#endif