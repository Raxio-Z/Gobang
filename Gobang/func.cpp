#include "head.h"
using namespace std;

Board::Board()
{
	comSum = 0;
	humSum = 0;
	length = 0;

	board.resize(BOARD_SIZE);
	comScore.resize(BOARD_SIZE);
	humScore.resize(BOARD_SIZE);
	//InitZobrist(this);


	while (1)
	{
		unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
		std::mt19937 g1(seed1);  // mt19937 is a standard mersenne_twister_engine

		int k = g1();
		if (k > 0)
		{
			Zobrist_code = k;
			break;
		}
	}

	for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++)
	{
		while (1)
		{
			unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
			std::mt19937 g1(seed1);  // mt19937 is a standard mersenne_twister_engine

			int s1 = g1(), s2 = g1();
			if (s1 > 0 && s2 > 0)
			{
				Zobrist_black[i] = s1;
				Zobrist_white[i] = s2;
				break;
			}
		}

	}


	for (int i = 0; i < BOARD_SIZE; i++)
	{
		board[i].resize(BOARD_SIZE);
		comScore[i].resize(BOARD_SIZE);
		humScore[i].resize(BOARD_SIZE);
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			board[i][j] = EMP;
			comScore[i][j] = 0;
			humScore[i][j] = 0;
		}
	}
}

void InitZobrist(Board* b)
{
	while (1)
	{
		unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
		std::mt19937 g1(seed1);  // mt19937 is a standard mersenne_twister_engine

		int k = g1();
		if (k > 0)
		{
			b->Zobrist_code = k;
			break;
		}
	}

	for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++)
	{
		while (1)
		{
			unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
			std::mt19937 g1(seed1);  // mt19937 is a standard mersenne_twister_engine

			int s1 = g1(), s2 = g1();
			if (s1 > 0 && s2 > 0)
			{
				b->Zobrist_black[i] = s1;
				b->Zobrist_white[i] = s2;
				break;
			}
		}

	}

}

void initScore(Board& b)
{
	b.comSum = 0;
	b.humSum = 0;
	b.length = 0;
	b.record.clear();

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			b.board[i][j] = EMP;
			b.comScore[i][j] = 0;
			b.humScore[i][j] = 0;
		}
	}


}

//得标记一下下在了哪里，要不容易看不出来
void putGo(Board& b, int x, int y, int role)
{

	IMAGE img;
	if (role == HUM)
	{
		loadimage(&img, L"black.jpg", 22, 22, true);
		putimage(b.x0 + x * b.t - 11, b.y0 + y * b.t - 11, &img);//显示图片
		b.board[x][y] = HUM;
		b.Zobrist_code ^= b.Zobrist_black[x * BOARD_SIZE + y];
	}
	else if (role == COM)
	{
		loadimage(&img, L"white.jpg", 22, 22, true);
		putimage(b.x0 + x * b.t - 11, b.y0 + y * b.t - 11, &img);//显示图片
		b.board[x][y] = COM;
		b.Zobrist_code ^= b.Zobrist_white[x * BOARD_SIZE + y];
	}
	Step s;
	s.p = pair<int, int>(x, y);
	s.role = role;
	b.record.push_back(s);
	b.length++;
	updateScore(b, x, y);
}

void offGo(Board& b)
{
	if (b.length < 2)
		return;
	IMAGE img;
	for (int i = 0; i < 2; i++)
	{
		Step s = b.record.back();
		b.record.pop_back();
		int x = s.p.first, y = s.p.second;
		b.board[x][y] = EMP;
		b.length--;
		if (s.role == HUM)
			b.Zobrist_code ^= b.Zobrist_black[x * BOARD_SIZE + y];
		else if (s.role == COM)
			b.Zobrist_code ^= b.Zobrist_white[x * BOARD_SIZE + y];
		updateScore(b, x, y);
	}

	loadimage(&img, L"bg.png", 800, 544, false);
	putimage(0, 0, &img);//显示图片
	//显示悔棋和重开 11 13
	loadimage(&img, L"back.png", 80, 40, true);
	putimage(650, 390, &img);//显示图片
	loadimage(&img, L"remake.png", 80, 40, true);
	putimage(650, 450, &img);//显示图片


	for (int i = 0; i < b.record.size(); i++)
	{
		if (b.record[i].role == HUM)
		{
			loadimage(&img, L"black.jpg", 22, 22, true);
			putimage(b.x0 + b.record[i].p.first * b.t - 11, b.y0 + b.record[i].p.second * b.t - 11, &img);//显示图片
			b.board[b.record[i].p.first][b.record[i].p.second] = HUM;
		}
		else if (b.record[i].role == COM)
		{
			loadimage(&img, L"white.jpg", 22, 22, true);
			putimage(b.x0 + b.record[i].p.first * b.t - 11, b.y0 + b.record[i].p.second * b.t - 11, &img);//显示图片
			b.board[b.record[i].p.first][b.record[i].p.second] = COM;
		}

	}

}

void remake(Board& b)
{
	IMAGE img;
	loadimage(&img, L"bg.png", 800, 544, false);
	putimage(0, 0, &img);//显示图片
	//显示悔棋和重开 11 13
	loadimage(&img, L"back.png", 80, 40, true);
	putimage(650, 390, &img);//显示图片
	loadimage(&img, L"remake.png", 80, 40, true);
	putimage(650, 450, &img);//显示图片

	initScore(b);

}

//是否胜利只考虑最后一步是否成5即可
bool is_end(Board& b)
{
	Step s = b.record.back();
	int x = s.p.first, y = s.p.second;
	int role = s.role;

	//进行四个方向的搜索
	int count = 1;
	//——
	for (int s = x + 1; true; s++)
	{
		if (s >= BOARD_SIZE)
			break;
		if (b.board[s][y] != role)
			break;
		count++;
	}
	for (int s = x - 1; true; s--)
	{
		if (s < 0)
			break;
		if (b.board[s][y] != role)
			break;
		count++;
	}
	if (count >= 5)
		return true;

	// |
	count = 1;
	for (int s = y + 1; true; s++)
	{
		if (s >= BOARD_SIZE)break;
		if (b.board[x][s] != role)break;
		count++;
	}
	for (int s = y - 1; true; s--)
	{
		if (s < 0)break;
		if (b.board[x][s] != role)break;
		count++;
	}
	if (count >= 5)
		return true;

	// \

	count = 1;
	for (int s = 1; true; s++)
	{
		if (x + s >= BOARD_SIZE || y + s >= BOARD_SIZE)
			break;
		if (b.board[x + s][y + s] != role)
			break;
		count++;
	}
	for (int s = 1; true; s++)
	{
		if (x - s < 0 || y - s < 0)
			break;
		if (b.board[x - s][y - s] != role)
			break;
		count++;
	}
	if (count >= 5)
		return true;

	// /
	count = 1;
	for (int s = 1; true; s++)
	{
		if (x + s >= BOARD_SIZE || y - s < 0)
			break;
		if (b.board[x + s][y - s] != role)
			break;
		count++;
	}
	for (int s = 1; true; s++)
	{
		if (x - s < 0 || y + s >= BOARD_SIZE)
			break;
		if (b.board[x - s][y + s] != role)
			break;
		count++;
	}
	if (count >= 5)
		return true;

	return false;
}

void win(int role)
{
	IMAGE img;
	if (role == HUM)
	{
		loadimage(&img, L"user_win.png", 400, 300, false);
		putimage(200, 100, &img);//显示图片
	}
	else if (role == COM)
	{
		loadimage(&img, L"com_win.png", 400, 300, false);
		putimage(200, 100, &img);//显示图片

	}

}

//四层很快，是否可以迭代加深，先搜两层，四层，六层，当小层数已经有必胜的棋就不向下搜索了

//alpha_beta剪枝算法，最后结果在返回的alpha和beta区间
//如何得到最后的落点位置
//加入了Zobrist置换表之后6层效率有较大提升，减少重复搜索，以空间换时间。90s->60s
int alpha_beta(Board b, int alpha, int beta, int role, int depth, int sd, pair<int, int>& p, map<int,z_cache>& Cache)
{
	if (depth == 0)
		return evaluate(b);

	if (role == COM)
	{
		vector<pair<int, int>>kl = generate(b, COM);
		for (int i = 0; i < kl.size(); i++)
		{
			int x = kl[i].first, y = kl[i].second;

			Board temp(b);
			temp.Zobrist_code ^= temp.Zobrist_white[x * BOARD_SIZE + y];
			temp.board[x][y] = COM;
			temp.length++;
			Step s;
			s.p = pair<int, int>(x, y);
			s.role = role;
			temp.record.push_back(s);
			updateScore(temp, x, y);
			//应该是使用Zobrist置换表减少a-b剪枝次数
			//那Cache该存什么，alpha，beta？
			int m;//alpha

			//m = alpha_beta(temp, alpha, beta, HUM, depth - 1, sd, p, Cache);
			map<int, z_cache>::iterator iter;
			iter = Cache.find(temp.Zobrist_code);
			if (iter == Cache.end())//没找见
			{
				m = alpha_beta(temp, alpha, beta, HUM, depth - 1, sd, p, Cache);
				Cache.insert(pair<int, z_cache>(b.Zobrist_code, z_cache(m, INT_MAX, sd - depth)));//在原来没有的时候beta先存INT_MAX
			}
			else//找到了
			{
				if (iter->second.depth >= sd - depth)
				{
					if (iter->second.alpha != INT_MIN)
						m = iter->second.alpha;
					else
					{
						m = alpha_beta(temp, alpha, beta, HUM, depth - 1, sd, p, Cache);
						iter->second.alpha = m;
						iter->second.depth = sd - depth;
						iter->second.beta = INT_MAX;//beta也要改
					}
				}
				else//深度不够的点，则加深深度
				{
					m = alpha_beta(temp, alpha, beta, HUM, depth - 1, sd, p, Cache);
					iter->second.alpha = m;
					iter->second.depth = sd - depth;
					iter->second.beta = INT_MAX;//beta也要改
				}
			}

			if (m > alpha)
			{
				alpha = m;
				if (depth == sd)
					p = pair<int, int>(x, y);
			}
			if (alpha > beta)
				return alpha;

		}
		return alpha;
	}
	else //if (role == HUM)
	{
		vector<pair<int, int>>kl = generate(b, HUM);

		for (int i = 0; i < kl.size(); i++)
		{
			int x = kl[i].first, y = kl[i].second;

			Board temp(b);
			temp.Zobrist_code ^= temp.Zobrist_black[x * BOARD_SIZE + y];
			temp.board[x][y] = HUM;
			temp.length++;
			Step s;
			s.p = pair<int, int>(x, y);
			s.role = role;
			temp.record.push_back(s);

			updateScore(temp, x, y);

			int m;//beta

			//m = alpha_beta(temp, alpha, beta, COM, depth - 1, sd, p, Cache);
			map<int, z_cache>::iterator iter;
			iter = Cache.find(temp.Zobrist_code);
			if (iter == Cache.end())//没找见
			{
				m = alpha_beta(temp, alpha, beta, COM, depth - 1, sd, p, Cache);
				Cache.insert(pair<int, z_cache>(b.Zobrist_code, z_cache(INT_MIN, m, sd - depth)));//在原来没有的时候beta先存INT_MAX
			}
			else//找到了
			{
				if (iter->second.depth >= sd - depth)
				{
					if (iter->second.beta != INT_MAX)
						m = iter->second.beta;
					else
					{
						m = alpha_beta(temp, alpha, beta, COM, depth - 1, sd, p, Cache);
						iter->second.beta = m;
						iter->second.depth = sd - depth;
						iter->second.alpha = INT_MIN;
					}
				}
				else//深度不够的点，则加深深度
				{
					m = alpha_beta(temp, alpha, beta, COM, depth - 1, sd, p, Cache);
					iter->second.beta = m;
					iter->second.depth = sd - depth;
					iter->second.alpha = INT_MIN;
				}
			}

			if (m < beta)
				beta = m;
			if (beta < alpha)
				return beta;

		}

		return beta;
	}

}