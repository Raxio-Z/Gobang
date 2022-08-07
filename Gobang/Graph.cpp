//本文件用于生成图形化界面

#include "head.h"
#include <time.h>
#include <fstream>

void InitialWindow(Board& b)
{
	initgraph(800, 544);
	IMAGE img;
	loadimage(&img, L"bg.png", 800, 544, false);
	putimage(0, 0, &img);//显示图片

	//显示悔棋和重开 11 13
	loadimage(&img, L"back.png", 80, 40, true);
	putimage(650, 390, &img);//显示图片
	loadimage(&img, L"remake.png", 80, 40, true);
	putimage(650, 450, &img);//显示图片


	MOUSEMSG m;
	int x, y;
	int num_x, num_y;
	
	ofstream ofs;
	ofs.open("time.txt", ios::out);


	while (1)
	{
		//黑子落棋

		while (1)
		{
			m = GetMouseMsg();
			if (m.mkLButton)
			{
				//悔棋
				if (m.x >= 650 && m.x <= 730 && m.y >= 390 && m.y <= 430)
				{
					offGo(b);
					continue;
				}
				else if (m.x >= 650 && m.x <= 730 && m.y >= 450 && m.y <= 490)
				{
					remake(b);
					continue;
				}

				x = (int)((m.x - b.x0) / b.half);
				y = (int)((m.y - b.y0) / b.half);
				num_x = (x % 2 == 0) ? x : x + 1;
				num_y = (y % 2 == 0) ? y : y + 1;

				if (num_x >= 0 && num_y >= 0 && num_x < 30 && num_y < 30)
				{
					//判断一下该位置是否已经有棋子
					int put_x = num_x / 2, put_y = num_y / 2;
					if (b.board[put_x][put_y] != EMP)
						continue;

					putGo(b, put_x, put_y, HUM);
					break;
				}
			}

		}

		if (is_end(b))
		{
			win(HUM);
			break;
		}

		loadimage(&img, L"searching.png", 80, 25, true);
		putimage(650, 500, &img);//显示图片


		double st = clock();

		//评估局势
		int alpha = INT_MIN, beta = INT_MAX;
		int depth = DEPTH;//还是得优化，这个地方才到4层
		pair<int, int>p;
		map<int, z_cache>Cache;//还得存一下深度，要不然没有意义
		alpha_beta(b, alpha, beta, COM, depth, depth, p, Cache);//该计算机下棋
		//能得到最优的结果，但是落子点怎么返回

		double no = clock();

		ofs << no - st <<"ms" << endl;

		loadimage(&img, L"whole_white.png", 80, 25, true);
		putimage(650, 500, &img);//显示图片
		
		//电脑下棋
		putGo(b, p.first, p.second, COM);
		//需要判断输赢
		if (is_end(b))
		{
			win(COM);
			break;
		}

	}
	while(1){}

	ofs.close();
	closegraph();
}
