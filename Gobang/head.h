#pragma once

//ͷ�ļ�
#include <iostream>
#include <vector>
#include <map>
#include <graphics.h>
#include <algorithm>
#include <chrono>
#include <random>
using namespace std;
//����һЩȫ��const����


//���̴�С
#define BOARD_SIZE 15

//���������ӽ�ɫrole�趨
#define EMP 0
#define COM 1
#define HUM 2

//һЩ����趨
#define ONE 10		//����
#define TWO 100		//���
#define THREE 1000	//����
#define TWOTHREE 60000 //˫����  ˫��������Ӧ��Ҫ�Ȼ���С
#define FOUR 100000	//����
#define FIVE 10000000	//���壨win
#define BLOCKED_ONE 1	//��סһ�˵�
#define BLOCKED_TWO 10	//��סһ�˵�
#define BLOCKED_THREE 100	//��סһ�˵�
#define BLOCKED_FOUR 10000	//��סһ�˵� ����

//ÿ�����������Ľ�����
#define COUNT_LIMIT 20   //��������ƺ�Ӱ�첻��  20->15  60s->50s
						//COUNT_LIMIT=10  18s����COUNT_LIMIT=5 1.8s
						// 7�ǿ��Խ��ܵ� 8Ҳ������  12 ��Ӧ34s

//�������
#define DEPTH 4

//���ݽṹ

class Step {
public:
	pair<int, int>p;
	int role;
};

class Board {
public:
	vector<vector<int>> board;//��¼������������λ�úͽ�ɫ	
	vector<vector<int>> comScore;//��¼ÿ��λ�õļ�����������ô��Ǻ�����Ϊ0
	vector<vector<int>> humScore;//��¼ÿ��λ�õ��˵ķ������ô�Ϊ������Ϊ0

	int comSum;
	int humSum;

	int length;//���岽��
	vector<Step>record;//��¼ÿ�����λ�úͲ�����

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

//��������ĳһ���̶��ĵ�λ��������,��������ֵ
int pointScore(Board& b, int x, int y, int role, int dir);
//����pointScore����������ֵ�������ض�Ӧ�ķ���
int countScore(int count, int block, int empty);
//���ص�ǰ��������ֵ
int evaluate(Board& b);
//�����ھ��淢���ı䣨���壬���壬�ؿ��ȣ�ʱ������λ����Χ9*9���������ӵ���������ֵ��
void update(Board& b, int x, int y, int dir);
void updateScore(Board& b, int x0, int y0);
//��ʼ��Zobrist�û���
void InitZobrist(Board* b);
//�ж�λ����Χdis�Ƿ���count������
bool hasNeighors(Board& b, int x, int y, int dis, int count);
//���������������
vector<pair<int, int>> generate(Board& b, int role);

//��ʼ������
void initScore(Board& b);

//����
void putGo(Board& b, int x, int y, int role);

//����,����Ļ���Ҫɾ���������
void offGo(Board& b);

//�ؿ�
void remake(Board& b);

//alpha_beta������ʹ��Minimax�㷨����Ϧ�-�¼�֦�㷨�γɵݹ��㷨��Ѱ����һ��������λ�á�
int alpha_beta(Board b, int alpha, int beta, int role, int depth, int sd, pair<int, int>& p, map<int, z_cache>& Cache);

bool is_end(Board& b);

void win(int role);

void InitialWindow(Board& b);
