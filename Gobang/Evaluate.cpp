#include "head.h"

//单个位置棋子的评估分数
int pointScore(Board& b, int x, int y, int role, int dir = 0)//定义一个方向，便于进行单方向搜索来update，减少开销,等于0是四个方向都搜
{
	int result = 0;

	int count = 1;//有多少个棋子（最多包含一个空位
	int block = 0;//左右是否堵住
	int empty = -1;	//empty记录空位对于边界的位置
	int reverseCount = 0;//反向数数

	int num_three = 0;//用来记录活三数量

	int len = BOARD_SIZE;
	//需要考虑四个方向

	//——
	if (dir == 1 || dir == 0)
	{
		for (int s = x + 1; true; s++)
		{
			if (s >= len)
			{
				block++;
				break;
			}
			int status = b.board[s][y];
			//该位置是空
			if (status == EMP)
			{
				if (empty == -1 && s + 1 < len && b.board[s + 1][y] == role)
				{
					empty = count;
					continue;
				}
				else
					break;
			}
			else if (status == role)
			{
				count++;
				continue;
			}
			else
			{
				block++;
				break;
			}
		}
		//反向
		for (int s = x - 1; true; s--)
		{
			if (s < 0)
			{
				block++;
				break;
			}
			int status = b.board[s][y];
			if (status == EMP)
			{
				if (empty == -1 && s - 1 >= 0 && b.board[s - 1][y] == role)
				{
					empty = 0;
					continue;
				}
				else
					break;
			}
			else if (status == role)
			{
				reverseCount++;
				if (empty != -1)
					empty++;
			}
			else
			{
				block++;
				break;
			}
		}

		count += reverseCount;
		int k = countScore(count, block, empty);
		result += k;
		if (k == THREE)
			num_three++;

	}

	// |
	if (dir == 2 || dir == 0)
	{
		count = 1, empty = -1, block = 0;
		reverseCount = 0;

		for (int s = y + 1; true; s++)
		{
			if (s >= len)
			{
				block++;
				break;
			}
			int status = b.board[x][s];
			if (status == EMP)
			{
				if (empty == -1 && s + 1 < len && b.board[x][s + 1] == role)
				{
					empty = count;
					continue;
				}
				else
					break;
			}
			else if (status == role)
			{
				count++;
				continue;
			}
			else
			{
				block++;
				break;
			}
		}
		for (int s = y - 1; true; s--)
		{
			if (s < 0)
			{
				block++;
				break;
			}
			int status = b.board[x][s];
			if (status == EMP)
			{
				if (empty == -1 && s - 1 >= 0 && b.board[x][s - 1] == role)
				{
					empty = 0;
					continue;
				}
				else
					break;
			}
			else if (status == role)
			{
				reverseCount++;
				if (empty != -1)
					empty++;
			}
			else
			{
				block++;
				break;
			}
		}

		count += reverseCount;
		int k = countScore(count, block, empty);
		result += k;
		if (k == THREE)
			num_three++;

	}
	// \

	if (dir == 3 || dir == 0)
	{
		count = 1, empty = -1, block = 0;
		reverseCount = 0;
		for (int s = 1; true; s++)
		{
			int nx = x + s, ny = y + s;
			if (nx >= len || ny >= len)
			{
				block++;
				break;
			}
			int status = b.board[nx][ny];
			if (status == EMP)
			{
				if (empty == -1 && nx + 1 < len && ny + 1 < len && b.board[nx + 1][ny + 1] == role)
				{
					empty = count;
					continue;
				}
				else
					break;
			}
			else if (status == role)
			{
				count++;
				continue;
			}
			else
			{
				block++;
				break;
			}
		}
		for (int s = 1; true; s++)
		{
			int nx = x - s, ny = y - s;
			if (nx < 0 || ny < 0)
			{
				block++;
				break;
			}
			int status = b.board[nx][ny];
			if (status == EMP)
			{
				if (empty == -1 && nx - 1 >= 0 && ny - 1 >= 0 && b.board[nx - 1][ny - 1] == role)
				{
					empty = 0;
					continue;
				}
				else
					break;
			}
			else if (status == role)
			{
				reverseCount++;
				if (empty != -1)
					empty++;
			}
			else
			{
				block++;
				break;
			}
		}
		count += reverseCount;
		int k = countScore(count, block, empty);
		result += k;
		if (k == THREE)
			num_three++;
	}

	//  /
	if (dir == 4 || dir == 0)
	{
		count = 1, empty = -1, block = 0;
		reverseCount = 0;
		for (int s = 1; true; s++)
		{
			int nx = x + s, ny = y - s;
			if (nx >= len || ny >= len || nx < 0 || ny < 0)
			{
				block++;
				break;
			}
			int status = b.board[nx][ny];
			if (status == EMP)
			{
				if (empty == -1 && nx + 1 < len && ny - 1 >= 0 && b.board[nx + 1][ny - 1] == role)
				{
					empty = count;
					continue;
				}
				else
					break;
			}
			else if (status == role)
			{
				count++;
				continue;
			}
			else
			{
				block++;
				break;
			}
		}
		for (int s = 1; true; s++)
		{
			int nx = x - s, ny = y + s;
			if (nx >= len || ny >= len || nx < 0 || ny < 0)
			{
				block++;
				break;
			}
			int status = b.board[nx][ny];
			if (status == EMP)
			{
				if (empty == -1 && nx - 1 >= 0 && ny + 1 < len && b.board[nx - 1][ny + 1] == role)
				{
					empty = 0;
					continue;
				}
				else
					break;
			}
			else if (status == role)
			{
				reverseCount++;
				if (empty != -1)
					empty++;
			}
			else
			{
				block++;
				break;
			}
		}
		count += reverseCount;
		int k = countScore(count, block, empty);
		result += k;
		if (k == THREE)
			num_three++;
	}

	//双活三特判
	//if (num_three >= 2)
		//result = TWOTHREE;

	return result;
}

int countScore(int count, int block, int empty)
{

	if (empty <= 0)
	{
		if (count >= 5)
			return FIVE;
		if (block == 0) {
			switch (count) {
			case 1:return ONE;
			case 2:return TWO;
			case 3:return THREE;
			case 4:return FOUR;
			}
		}
		else if (block == 1) {
			switch (count) {
			case 1:return BLOCKED_ONE;
			case 2:return BLOCKED_TWO;
			case 3:return BLOCKED_THREE;
			case 4:return BLOCKED_FOUR;
			}
		}
	}
	else if (empty == 1 || empty == count - 1) {
		//第1个是空位
		if (count >= 6) {//右边或左边已经连成了5个
			return FIVE;
		}
		if (block == 0) {
			switch (count) {
			case 2: return BLOCKED_TWO;  //两个分隔的单个棋子
			case 3: return BLOCKED_THREE;
			case 4: return BLOCKED_FOUR;
			case 5: return FOUR;
			}
		}

		if (block == 1) {
			switch (count) {
			case 2: return BLOCKED_TWO / 2;
			case 3: return BLOCKED_THREE / 2;
			case 4: return BLOCKED_FOUR / 2;
			case 5: return BLOCKED_FOUR / 2;
			}
		}
	}
	else if (empty == 2 || empty == count - 2) {
		//第二个是空位
		if (count >= 7) {
			return FIVE;
		}
		if (block == 0) {
			switch (count) {
			case 3: return THREE;
			case 4:;
			case 5: return BLOCKED_FOUR;
			case 6: return FOUR;
			}
		}

		if (block == 1) {
			switch (count) {
			case 3: return BLOCKED_THREE;
			case 4: return BLOCKED_FOUR;
			case 5: return BLOCKED_FOUR;
			case 6: return FOUR;
			}
		}

		//堵两边，有四个及以上就可以拼起来
		if (block == 2) {
			switch (count) {
			case 4:;
			case 5:;
			case 6: return BLOCKED_FOUR;
			}
		}
	}
	else if (empty == 3 || empty == count - 3) {
		if (count >= 8) {
			return FIVE;
		}
		if (block == 0) {
			switch (count) {
			case 4:;
			case 5: return THREE;
			case 6: return BLOCKED_FOUR;
			case 7: return FOUR;
			}
		}

		if (block == 1) {
			switch (count) {
			case 4:;
			case 5:;
			case 6: return BLOCKED_FOUR;
			case 7: return FOUR;
			}
		}

		if (block == 2) {
			switch (count) {
			case 4:;
			case 5:;
			case 6:;
			case 7: return BLOCKED_FOUR;
			}
		}
	}
	else if (empty == 4 || empty == count - 4) {
		if (count >= 9) {
			return FIVE;
		}
		if (block == 0) {
			switch (count) {
			case 5:;
			case 6:;
			case 7:;
			case 8: return FOUR;
			}
		}

		if (block == 1) {
			switch (count) {
			case 4:;
			case 5:;
			case 6:;
			case 7: return BLOCKED_FOUR;
			case 8: return FOUR;
			}
		}

		if (block == 2) {
			switch (count) {
			case 5:;
			case 6:;
			case 7:;
			case 8: return BLOCKED_FOUR;
			}
		}
	}
	else if (empty == 5 || empty == count - 5) {
		return FIVE;
	}

	return 0;
}

void update(Board& b, int x, int y, int dir)
{
	b.comSum -= b.comScore[x][y];
	b.humSum -= b.humScore[x][y];
	if (b.board[x][y] == HUM)
	{
		b.humScore[x][y] = pointScore(b, x, y, HUM, 0);
		b.comScore[x][y] = 0;
		b.humSum += b.humScore[x][y];
	}
	else if (b.board[x][y] == COM)
	{
		b.comScore[x][y] = pointScore(b, x, y, COM, 0);
		b.humScore[x][y] = 0;
		b.comSum += b.comScore[x][y];
	}
	else//空  计算机和人都有分数
	{
		b.comScore[x][y] = pointScore(b, x, y, COM, 0);
		b.humScore[x][y] = pointScore(b, x, y, HUM, 0);
		b.comSum += b.comScore[x][y];
		b.humSum += b.humScore[x][y];
	}
}

void updateScore(Board& b, int x0, int y0)
{
	int radius = 4;//更新周围两侧4个棋子的位置

	//——
	for (int i = -radius; i <= radius; i++)
	{
		int x = x0 + i, y = y0;
		if (x < 0)continue;
		if (x >= BOARD_SIZE)break;
		update(b, x, y, 1);
	}

	// |
	for (int i = -radius; i <= radius; i++)
	{
		int x = x0, y = y0 + i;
		if (y < 0)continue;
		if (y >= BOARD_SIZE)break;
		update(b, x, y, 2);
	}

	// 右下
	for (int i = -radius; i <= radius; i++)
	{
		int x = x0 + i, y = y0 + i;
		if (x < 0 || y < 0)continue;
		if (x >= BOARD_SIZE || y >= BOARD_SIZE)break;
		update(b, x, y, 3);
	}

	// /
	for (int i = -radius; i <= radius; i++)
	{
		int x = x0 + i, y = y0 - i;
		if (x < 0 || y < 0)continue;
		if (x >= BOARD_SIZE || y >= BOARD_SIZE)continue;
		update(b, x, y, 4);
	}
}

//不能每次都重新算一遍，太慢，应当用数组去保存，之后update周围的
int evaluate(Board& b)
{
	//返回当前分数，都是机器的分数，没必要分人和机器
	return b.comSum - b.humSum;
}

//判断某位置周围dis的方格内是否有count个非空位
//限制落子范围
bool hasNeighors(Board& b, int x, int y, int dis, int count)
{
	for (int i = x - dis; i <= x + dis; i++)
	{
		if (i < 0)
			continue;
		if (i >= BOARD_SIZE)
			break;
		for (int j = y - dis; j <= y + dis; j++)
		{
			if (j < 0)
				continue;
			if (j >= BOARD_SIZE)
				break;
			if (i == x && j == y)
				continue;
			if (b.board[i][j] != EMP)
				count--;
		}
	}
	return count <= 0 ? true : false;
}

//每次生成下面要搜索的节点
//因为要考虑双方的下棋，所以需要设置role
//还是会有的时候对面已经快成5了但是不去堵（不符合周围有2个邻居的要求，所以该节点就没有被考虑进去。。。。）
vector<pair<int, int>> generate(Board& b, int role)
{
	vector<pair<int, int>> comfives;
	vector<pair<int, int>> humfives;
	vector<pair<int, int>> comfours;//电脑活四
	vector<pair<int, int>> humfours;
	vector<pair<int, int>> comblockedfours;//电脑冲四
	vector<pair<int, int>> humblockedfours;

	vector<pair<int, int>> comtwothrees;
	vector<pair<int, int>> humtwothrees;

	//这里的双三判断方式？？？不如直接改返回的result
	vector<pair<int, int>> comthrees;//电脑活三
	vector<pair<int, int>> humthrees;
	vector<MyStruct> comtwos;
	vector<MyStruct> humtwos;
	vector<MyStruct> neighbors;//周围的邻居

	vector<MyStruct> trial;

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			//只对空位进行判断
			if (b.board[i][j] != EMP)
				continue;

			//如果周围两个方格(4*4)内没有2个子，则直接过

			if (b.length < 6)
				if (!hasNeighors(b, i, j, 1, 1))
					continue;
			if (b.length >= 6)
				if (!hasNeighors(b, i, j, 2, 2))//这个不能都是(2,2)，如果刚没下几步，就都不会满足
					continue;

			pair<int, int>p(i, j);

			//空位的人机分值可以认为是下在这里之后会有多少分
			int Hum_score = b.humScore[i][j];
			int Com_score = b.comScore[i][j];
			int Max_score = max(Hum_score, Com_score);

			//对冲三的判断,看需不需要
			//if (onlyThrees && maxScore < S.THREE) continue

			//五个子为什么要考虑对手
			//不管哪一方下在该位置成为5个子，都是关键位置，比如电脑，既想要下成5连，又要阻止人5连
			
			
			//trial.push_back(MyStruct(p, Max_score));

			if (Com_score >= FIVE)//先看电脑能不能连成5
				comfives.push_back(p);
			else if (Hum_score >= FIVE)//再看玩家能不能连成5
				humfives.push_back(p);
			else if (Com_score >= FOUR)
				comfours.push_back(p);
			else if (Hum_score >= FOUR)
				humfours.push_back(p);
			else if (Com_score >= BLOCKED_FOUR)
				comblockedfours.push_back(p);
			else if (Hum_score >= BLOCKED_FOUR)
				humblockedfours.push_back(p);
			else if (Com_score >= 2 * THREE)
				comtwothrees.push_back(p);
			else if (Hum_score >= 2 * THREE)
				humtwothrees.push_back(p);
			else if (Com_score >= THREE)
				comthrees.push_back(p);
				//trial.push_back(MyStruct(p, Max_score));
			else if (Hum_score >= THREE)
				humthrees.push_back(p);
			else if (Com_score >= TWO)
				comtwos.push_back(MyStruct(p, Max_score));
			else if (Hum_score >= TWO)
				humtwos.push_back(MyStruct(p, Max_score));
			else
				neighbors.push_back(MyStruct(p, Max_score));

		}
	}

	//看一下返回什么

	//下面考虑的是下完这个棋之后Com_score是如果下白棋，Hum_score是下黑棋

	//最主要的是双方都要考虑到，攻防都要有

	//如果成五，是必杀棋，直接返回
	if (role == COM)
	{
		if (!comfives.empty())
		{
			comfives.insert(comfives.end(), humfives.begin(), humfives.end());
			return comfives;
		}
		else if (!humfives.empty())
			return humfives;
	}
	if (role == HUM)
	{
		if (!humfives.empty())
		{
			humfives.insert(humfives.end(), comfives.begin(), comfives.end());
			return humfives;
		}
		else if (!comfives.empty())
			return comfives;
	}

	// 自己能活四，则直接活四，不考虑冲四
	if (role == COM && !comfours.empty())
		return comfours;
	if (role == HUM && !humfours.empty())
		return humfours;

	//对面有活四冲四，自己冲四都没，则只考虑对面活四（堵对面） （此时对面冲四就不用考虑了)
	if (role == COM && !humfours.empty() && comblockedfours.empty())
		return humfours;
	if (role == HUM && !comfours.empty() && humblockedfours.empty())
		return comfours;

	//双三需要考虑
	// 对面没有活四，我们有双活三，则优先考虑双三
	//如果对面也有双三，则先攻击，先构成双三
	
	//我们有双活三，对面没有活四
	//if (role == COM && humfours.empty() && !comtwothrees.empty())
	//	return comtwothrees;
	//if (role == HUM && comfours.empty() && !humtwothrees.empty())
	//	return humtwothrees;
	 
	//对面有双活三，我们没有，则先考虑对面
	//if (role == COM && comtwothrees.empty() && !humtwothrees.empty())
	//	return humtwothrees;
	//if (role == HUM && humtwothrees.empty() && !comtwothrees.empty())
	//	return comtwothrees;


	// 对面有活四自己有冲四，则都考虑下
	vector<pair<int, int>>fours, blockedfours;
	if (role == COM)
	{
		fours.insert(fours.end(), comfours.begin(), comfours.end());
		fours.insert(fours.end(), humfours.begin(), humfours.end());
		blockedfours.insert(blockedfours.end(), comblockedfours.begin(), comblockedfours.end());
		blockedfours.insert(blockedfours.end(), humblockedfours.begin(), humblockedfours.end());
	}
	else if (role == HUM)
	{
		fours.insert(fours.end(), humfours.begin(), humfours.end());
		fours.insert(fours.end(), comfours.begin(), comfours.end());
		blockedfours.insert(blockedfours.end(), humblockedfours.begin(), humblockedfours.end());
		blockedfours.insert(blockedfours.end(), comblockedfours.begin(), comblockedfours.end());
	}
	fours.insert(fours.end(), blockedfours.begin(), blockedfours.end());
	if (!fours.empty())
		return fours;

	//剩下这些都需要考虑
	vector<pair<int, int>> res;
	if (role == COM)
	{
		res.insert(res.end(), comtwothrees.begin(), comtwothrees.end());
		res.insert(res.end(), humtwothrees.begin(), humtwothrees.end());
		res.insert(res.end(), comblockedfours.begin(), comblockedfours.end());
		res.insert(res.end(), humblockedfours.begin(), humblockedfours.end());
		res.insert(res.end(), comthrees.begin(), comthrees.end());
		res.insert(res.end(), humthrees.begin(), humthrees.end());
	}
	if (role == HUM)
	{
		res.insert(res.end(), humtwothrees.begin(), humtwothrees.end());
		res.insert(res.end(), comtwothrees.begin(), comtwothrees.end());
		res.insert(res.end(), humblockedfours.begin(), humblockedfours.end());
		res.insert(res.end(), comblockedfours.begin(), comblockedfours.end());
		res.insert(res.end(), humthrees.begin(), humthrees.end());
		res.insert(res.end(), comthrees.begin(), comthrees.end());
	}

	if (!comtwothrees.empty() || !humtwothrees.empty())
	{
		return res;
	}

	vector<MyStruct> two;
	if (role == COM)
	{
		two.insert(two.end(), comtwos.begin(), comtwos.end());
		two.insert(two.end(), humtwos.begin(), humtwos.end());
	}
	else
	{
		two.insert(two.end(), humtwos.begin(), humtwos.end());
		two.insert(two.end(), comtwos.begin(), comtwos.end());
	}
	sort(two.begin(), two.end());

	for (int i = 0; i < two.size(); i++)
		res.push_back(two[i].p);

	if (res.size() > COUNT_LIMIT)
		return vector<pair<int, int>>(res.begin(), res.begin() + COUNT_LIMIT - 1);

	return res;

//sort(trial.begin(), trial.end());
//vector<pair<int, int>> res;
//int lt = trial.size();
//int loop = min(lt, COUNT_LIMIT);
//for (int i = 0; i < loop; i++)
//{
//	res.push_back(trial[i].p);
//}

}

