#pragma once

//头文件
#include <iostream>
#include <vector>
#include <map>
#include <graphics.h>
#include <algorithm>
#include <chrono>
#include <random>
using namespace std;
//设置一些全局const变量


//棋盘大小
#define BOARD_SIZE 15

//棋盘上棋子角色role设定
#define EMP 0
#define COM 1
#define HUM 2

//一些棋局设定
#define ONE 10		//单个
#define TWO 100		//活二
#define THREE 1000	//活三
#define TWOTHREE 60000 //双活三  双活三分数应该要比活四小
#define FOUR 100000	//活四
#define FIVE 10000000	//活五（win
#define BLOCKED_ONE 1	//堵住一端的
#define BLOCKED_TWO 10	//堵住一端的
#define BLOCKED_THREE 100	//堵住一端的
#define BLOCKED_FOUR 10000	//堵住一端的 冲四

//每次搜索的最多的结点个数
#define COUNT_LIMIT 20   //调整这个似乎影响不大  20->15  60s->50s
						//COUNT_LIMIT=10  18s，，COUNT_LIMIT=5 1.8s
						// 7是可以接受的 8也还可以  12 对应34s

//搜索深度
#define DEPTH 4

//数据结构

class Step {
public:
	pair<int, int>p;
	int role;
};

class Board {
public:
	vector<vector<int>> board;//记录整个棋盘棋子位置和角色	
	vector<vector<int>> comScore;//记录每个位置的计算机分数（该处是黑子则为0
	vector<vector<int>> humScore;//记录每个位置的人的分数（该处为白子则为0

	int comSum;
	int humSum;

	int length;//下棋步数
	vector<Step>record;//记录每步棋的位置和操作方

	int Zobrist_black[225];
	int Zobrist_white[225];
	int Zobrist_code;

	double x0 = 192.9;
	double y0 = 65.8;
	double t = 29.5;
	double half = 14.75;

	Board();
};

struct MyStruct
{
	pair<int, int>p;
	int score;
	MyStruct(pair<int, int>py, int s)
	{
		p = py;
		score = s;
	}

	bool operator<(const MyStruct s)const
	{
		return score > s.score;
	}
};

class z_cache {
public:
	int alpha;
	int beta;
	int depth;

	z_cache(int a,int b,int d)
	{
		alpha = a;
		beta = b;
		depth = d;
	}
};

//对棋盘上某一个固定的点位进行评估,返回特征值
int pointScore(Board& b, int x, int y, int role, int dir);
//接受pointScore传来的特征值，并返回对应的分数
int countScore(int count, int block, int empty);
//返回当前局面评估值
int evaluate(Board& b);
//用于在局面发生改变（下棋，悔棋，重开等）时，更新位置周围9*9方格内棋子的评估函数值。
void update(Board& b, int x, int y, int dir);
void updateScore(Board& b, int x0, int y0);
//初始化Zobrist置换表
void InitZobrist(Board* b);
//判断位置周围dis是否有count个棋子
bool hasNeighors(Board& b, int x, int y, int dis, int count);
//生成搜索结点序列
vector<pair<int, int>> generate(Board& b, int role);

//初始化分数
void initScore(Board& b);

//下棋
void putGo(Board& b, int x, int y, int role);

//悔棋,悔棋的话需要删除最后两个
void offGo(Board& b);

//重开
void remake(Board& b);

//alpha_beta函数，使用Minimax算法并结合α-β剪枝算法形成递归算法，寻找下一步的落子位置。
int alpha_beta(Board b, int alpha, int beta, int role, int depth, int sd, pair<int, int>& p, map<int, z_cache>& Cache);

bool is_end(Board& b);

void win(int role);

void InitialWindow(Board& b);
