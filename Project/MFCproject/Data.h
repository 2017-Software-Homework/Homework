#ifndef DATA_H
#define DATA_H

extern COLORREF color;
extern int color_status;
extern int red,green,blue;


struct choose_array
{
	bool change_color;
	COLORREF color_to_set;


	int operation;
	int choose;
	CPoint point1;
	CPoint point2;
	int radius;

	choose_array* next;
};

extern choose_array *choose_head,*choose_temp1,*choose_temp2,*choose_generate1,*choose_generate2;//generate仅适用于生成新元素

#endif