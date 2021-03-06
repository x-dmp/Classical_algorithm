#include "myAVL.h"

int main(void)
{
	IMAGE img;
	MOUSEMSG m;

	loadimage(&img, _T("welcome.png"));
	initgraph(1280, 720);
	putimage(0, 0, &img);
	while (1)
	{
		FlushMouseMsgBuffer();
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN && m.x > 130 && m.x < 464 && m.y > 299 && m.y < 422)
		{
			mainprogram();
		}
	}
	closegraph();

	return 0;
}
