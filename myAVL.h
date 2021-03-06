#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <conio.h>
#include <graphics.h>

typedef struct BalancedBinaryTree
{
	int data;
	int height;
	struct BalancedBinaryTree* lchild;
	struct BalancedBinaryTree* rchild;
} AVL;

void InsertFun(AVL** MyAVL);
void Insert(AVL** Head, int key);
AVL* ll(AVL* y);
AVL* rr(AVL* y);
int Height(AVL* Head);
int maxnum(int a, int b);
int GetBalence(AVL* Head);
void DeleteFun(AVL** MyAVL);
void Delete(AVL** Head, int key);
void ClearFun(AVL** MyAVL);
void mainprogram(void);
int input(int flag);
void refresh(AVL* MyAVL, int px, int py, int x, int y, int level);

void mainprogram(void)
{
	IMAGE img;
	MOUSEMSG m;
	AVL* MyAVL;

	loadimage(&img, _T("mainprogram.png"));
	putimage(0, 0, &img);
	MyAVL = NULL;
	while (1)
	{
		while (_kbhit())
		{
			_getch();
		}
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN && m.x > 608 && m.x < 783 && m.y > 565 && m.y < 668)
		{
			InsertFun(&MyAVL);
		}
		else if (m.uMsg == WM_LBUTTONDOWN && m.x > 840 && m.x < 1015 && m.y > 565 && m.y < 668)
		{
			DeleteFun(&MyAVL);
		}
		else if (m.uMsg == WM_LBUTTONDOWN && m.x > 1071 && m.x < 1246 && m.y > 565 && m.y < 668)
		{
			ClearFun(&MyAVL);
		}
		FlushMouseMsgBuffer();
	}
}

void InsertFun(AVL** MyAVL)
{
	AVL* Head;
	int key = 1;

	setbkcolor(WHITE);
	settextcolor(BLACK);
	settextstyle(25, 0, _T("黑体"));
	key = input(1);
	Head = *MyAVL;
	Insert(&Head, key);
	*MyAVL = Head;
	refresh(Head, 928, 132, 928, 132, 1);
}

void Insert(AVL** Head, int key)
{
	AVL* p = NULL;
	int balenceflag;
	IMAGE img;

	loadimage(&img, _T("mainprogram.png"));
	if (*Head == NULL)
	{
		p = ((AVL*)malloc(sizeof(AVL)));
		p->data = key;
		p->lchild = NULL;
		p->rchild = NULL;
		p->height = 1;
		*Head = p;
		setbkcolor(WHITE);
		putimage(0, 0, &img);
		settextcolor(BLACK);
		outtextxy(50, 530, _T("插入成功！"));
		outtextxy(50, 560, _T("单击下列功能继续"));
	}
	else if ((*Head)->data > key)
	{
		Insert(&(*Head)->lchild, key);
	}
	else if ((*Head)->data < key)
	{
		Insert(&(*Head)->rchild, key);
	}
	else
	{
		setbkcolor(WHITE);
		putimage(0, 0, &img);
		settextcolor(BLACK);
		outtextxy(50, 530, _T("已有此元素 无需插入！"));
		outtextxy(50, 560, _T("单击下列功能继续"));
	}
	(*Head)->height = 1 + maxnum(Height((*Head)->lchild), Height((*Head)->rchild));
	balenceflag = GetBalence(*Head);
	if (balenceflag > 1 && key < (*Head)->lchild->data)
	{
		*Head = ll(*Head);
	}
	else if (balenceflag < -1 && key >(*Head)->rchild->data)
	{
		*Head = rr(*Head);
	}
	else if (balenceflag > 1 && key > (*Head)->lchild->data)
	{
		(*Head)->lchild = rr((*Head)->lchild);
		*Head = ll(*Head);
	}
	else if (balenceflag < -1 && key < (*Head)->rchild->data)
	{
		(*Head)->rchild = ll((*Head)->rchild);
		*Head = rr(*Head);
	}
}

AVL* ll(AVL* y)
{
	AVL* x = y->lchild;
	y->lchild = x->rchild;
	x->rchild = y;

	y->height = maxnum(Height(y->lchild), Height(y->rchild)) + 1;
	x->height = maxnum(Height(x->lchild), Height(x->rchild)) + 1;

	return x;
}

AVL* rr(AVL* y)
{
	AVL* x = y->rchild;
	y->rchild = x->lchild;
	x->lchild = y;

	y->height = maxnum(Height(y->lchild), Height(y->rchild)) + 1;
	x->height = maxnum(Height(x->lchild), Height(x->rchild)) + 1;

	return x;
}

int Height(AVL* Head)
{
	if (Head == NULL)
		return 0;
	return Head->height;
}

int maxnum(int a, int b)
{
	return (a > b) ? a : b;
}

int GetBalence(AVL* Head)
{
	if (Head == NULL)
	{
		return 0;
	}
	else
	{
		return Height(Head->lchild) - Height(Head->rchild);
	}
}

void DeleteFun(AVL** MyAVL)
{
	int key;
	AVL* Head = *MyAVL;
	setbkcolor(WHITE);
	settextcolor(BLACK);
	settextstyle(25, 0, _T("黑体"));
	key = input(2);
	Delete(&Head, key);
	*MyAVL = Head;
	refresh(Head, 928, 132, 928, 132, 1);
}

void Delete(AVL** Head, int key)
{
	AVL* p, * temp;
	int balenceflag;
	IMAGE img;

	loadimage(&img, _T("mainprogram.png"));
	if ((*Head) == NULL)
	{
		setbkcolor(WHITE);
		putimage(0, 0, &img);
		settextcolor(BLACK);
		outtextxy(50, 530, _T("删除失败！"));
		outtextxy(50, 560, _T("单击下列功能继续"));
	}
	else
	{
		if ((*Head)->data == key)
		{
			if ((*Head)->lchild == NULL && (*Head)->rchild == NULL)
			{
				p = *Head;
				free(p);
				*Head = NULL;
				setbkcolor(WHITE);
				putimage(0, 0, &img);
				settextcolor(BLACK);
				outtextxy(50, 530, _T("删除成功！"));
				outtextxy(50, 560, _T("单击下列功能继续"));
			}
			else if ((*Head)->lchild != NULL && (*Head)->rchild == NULL)
			{
				p = (*Head)->lchild;
				**Head = *p;
				free(p);
				setbkcolor(WHITE);
				putimage(0, 0, &img);
				settextcolor(BLACK);
				outtextxy(50, 530, _T("删除成功！"));
				outtextxy(50, 560, _T("单击下列功能继续"));
			}
			else if ((*Head)->lchild == NULL && (*Head)->rchild != NULL)
			{
				p = (*Head)->rchild;
				**Head = *p;
				free(p);
				setbkcolor(WHITE);
				putimage(0, 0, &img);
				settextcolor(BLACK);
				outtextxy(50, 530, _T("删除成功！"));
				outtextxy(50, 560, _T("单击下列功能继续"));
			}
			else
			{
				temp = (*Head)->rchild;
				while (temp->lchild != NULL)
				{
					temp = temp->lchild;
				}
				p = temp;
				(*Head)->data = temp->data;
				Delete(&(*Head)->rchild, temp->data);
			}
		}
		else if ((*Head)->data >= key)
		{
			Delete(&(*Head)->lchild, key);
		}
		else if ((*Head)->data <= key)
		{
			Delete(&(*Head)->rchild, key);
		}
	}
	if (*Head != NULL)
	{
		(*Head)->height = 1 + maxnum(Height((*Head)->lchild), Height((*Head)->rchild));
		balenceflag = GetBalence(*Head);
		if (balenceflag > 1 && GetBalence((*Head)->lchild) >= 0) //LL
		{
			*Head = ll(*Head);
		}
		else if (balenceflag > 1 && GetBalence((*Head)->lchild) < 0) //LR
		{
			(*Head)->lchild = rr((*Head)->lchild);
			*Head = ll(*Head);
		}
		else if (balenceflag < -1 && GetBalence((*Head)->rchild) <= 0) //RR
		{
			*Head = rr(*Head);
		}
		else if (balenceflag < -1 && GetBalence((*Head)->rchild) > 0)  //Rl
		{
			(*Head)->rchild = ll((*Head)->rchild);
			*Head = rr(*Head);
		}
	}
}

void ClearFun(AVL** MyAVL)
{
	AVL* Head = *MyAVL;
	IMAGE img;

	loadimage(&img, _T("mainprogram.png"));
	free(*MyAVL);
	*MyAVL = NULL;
	setbkcolor(WHITE);
	putimage(0, 0, &img);
	setbkcolor(WHITE);
	settextcolor(BLACK);
	settextstyle(25, 0, _T("黑体"));
	outtextxy(50, 530, _T("清空完成！"));
	outtextxy(50, 560, _T("单击下列功能继续"));
	refresh(*MyAVL, 928, 132, 928, 132, 1);
}

int input(int flag)
{
	int n = 0, sum = 0, i = 0, cha = 1;
	TCHAR s[5];
	char ch;
	IMAGE img;

	setbkcolor(WHITE);
	settextcolor(BLACK);
	settextstyle(25, 0, _T("黑体"));
	loadimage(&img, _T("inputp.png"));
	putimage(37, 512, &img);
	s[0] = s[1] = s[2] = s[3] = s[4] = '\0';
	settextcolor(RED);
	outtextxy(50, 590, '+');
	outtextxy(65, 590, '0');
	while (1)
	{
		if (flag == 1)
		{
			settextcolor(BLACK);
			outtextxy(50, 530, _T("插入(最多三位数,按+-修改符号)"));
			outtextxy(50, 560, _T("Input your data:"));
		}
		else if (flag == 2)
		{
			settextcolor(BLACK);
			outtextxy(50, 530, _T("删除(最多三位数,按+-修改符号)"));
			outtextxy(50, 560, _T("Input your data:"));
		}
		ch = _getch();
		if (ch >= '0' && ch <= '9' && sum <= 99)
		{
			if (!(sum == 0 && ch == '0'))
			{
				s[i] = ch;
				i++;
			}
			sum = sum * 10 + ch - 48;

		}
		else if (ch == 8)
		{
			sum = sum / 10;
			if (i > 0)
			{
				i--;
				s[i] = '\0';
			}
		}
		else if (ch == 13)
		{
			n = sum * cha;
			s[i] = '\0';
			break;
		}
		else if (ch == '+')
		{
			cha = 1;
		}
		else if (ch == '-')
		{
			cha = -1;
		}
		putimage(37, 512, &img);
		if (cha == -1)
		{
			settextcolor(RED);
			outtextxy(50, 590, '-');
		}
		else
		{
			settextcolor(RED);
			outtextxy(50, 590, '+');
		}
		if (sum != 0)
		{
			settextcolor(RED);
			outtextxy(65, 590, s);
		}
		else
		{
			settextcolor(RED);
			outtextxy(65, 590, '0');
		}
		if (flag == 1)
		{
			settextcolor(BLACK);
			outtextxy(50, 530, _T("插入(最多三位数,按B修改符号)"));
			outtextxy(50, 560, _T("Input your data:"));
		}
		else if (flag == 2)
		{
			settextcolor(BLACK);
			outtextxy(50, 530, _T("删除(最多三位数,按B修改符号)"));
			outtextxy(50, 560, _T("Input your data:"));
		}
	}
	return n;
}

void refresh(AVL* MyAVL, int px, int py, int x, int y, int level)
{
	int tx;
	TCHAR s[5];
	char ss[5];
	int i;

	s[0] = s[1] = s[2] = s[3] = s[4] = '\0';
	if (level == 1)
	{
		tx = 150;
	}
	else if (level == 2)
	{
		tx = 75;
	}
	else if (level == 3)
	{
		tx = 37;
	}
	else
	{
		tx = 18;
	}
	setbkcolor(0x673500);
	setfillcolor(0x673500);
	setlinecolor(0x673500);
	setlinestyle(PS_SOLID | PS_ENDCAP_FLAT, 4);
	settextcolor(WHITE);
	settextstyle(25, 0, _T("黑体"));
	if (MyAVL != NULL)
	{
		line(px, py, x, y);
		fillcircle(x, y, 30);
		refresh(MyAVL->lchild, x, y, x - tx, y + 98, level + 1);
		refresh(MyAVL->rchild, x, y, x + tx, y + 98, level + 1);
		sprintf_s(ss, "%d", MyAVL->data);
		for (i = 0; i < 5; i++)
		{
			s[i] = ss[i];
		}
		if (MyAVL->data < 0)
		{
			outtextxy(x - 22, y - 10, s);
		}
		else
		{
			outtextxy(x - 15, y - 10, s);
		}
	}
}