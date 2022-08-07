#include "head.h"

//����λ�����ӵ���������
int pointScore(Board& b, int x, int y, int role, int dir = 0)//����һ�����򣬱��ڽ��е�����������update�����ٿ���,����0���ĸ�������
{
	int result = 0;

	int count = 1;//�ж��ٸ����ӣ�������һ����λ
	int block = 0;//�����Ƿ��ס
	int empty = -1;	//empty��¼��λ���ڱ߽��λ��
	int reverseCount = 0;//��������

	int num_three = 0;//������¼��������

	int len = BOARD_SIZE;
	//��Ҫ�����ĸ�����

	//����
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
			//��λ���ǿ�
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
		//����
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

	//˫��������
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
		//��1���ǿ�λ
		if (count >= 6) {//�ұ߻�����Ѿ�������5��
			return FIVE;
		}
		if (block == 0) {
			switch (count) {
			case 2: return BLOCKED_TWO;  //�����ָ��ĵ�������
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
		//�ڶ����ǿ�λ
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

		//�����ߣ����ĸ������ϾͿ���ƴ����
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
	else//��  ��������˶��з���
	{
		b.comScore[x][y] = pointScore(b, x, y, COM, 0);
		b.humScore[x][y] = pointScore(b, x, y, HUM, 0);
		b.comSum += b.comScore[x][y];
		b.humSum += b.humScore[x][y];
	}
}

void updateScore(Board& b, int x0, int y0)
{
	int radius = 4;//������Χ����4�����ӵ�λ��

	//����
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

	// ����
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

//����ÿ�ζ�������һ�飬̫����Ӧ��������ȥ���棬֮��update��Χ��
int evaluate(Board& b)
{
	//���ص�ǰ���������ǻ����ķ�����û��Ҫ���˺ͻ���
	return b.comSum - b.humSum;
}

//�ж�ĳλ����Χdis�ķ������Ƿ���count���ǿ�λ
//�������ӷ�Χ
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

//ÿ����������Ҫ�����Ľڵ�
//��ΪҪ����˫�������壬������Ҫ����role
//���ǻ��е�ʱ������Ѿ����5�˵��ǲ�ȥ�£���������Χ��2���ھӵ�Ҫ�����Ըýڵ��û�б����ǽ�ȥ����������
vector<pair<int, int>> generate(Board& b, int role)
{
	vector<pair<int, int>> comfives;
	vector<pair<int, int>> humfives;
	vector<pair<int, int>> comfours;//���Ի���
	vector<pair<int, int>> humfours;
	vector<pair<int, int>> comblockedfours;//���Գ���
	vector<pair<int, int>> humblockedfours;

	vector<pair<int, int>> comtwothrees;
	vector<pair<int, int>> humtwothrees;

	//�����˫���жϷ�ʽ����������ֱ�Ӹķ��ص�result
	vector<pair<int, int>> comthrees;//���Ի���
	vector<pair<int, int>> humthrees;
	vector<MyStruct> comtwos;
	vector<MyStruct> humtwos;
	vector<MyStruct> neighbors;//��Χ���ھ�

	vector<MyStruct> trial;

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			//ֻ�Կ�λ�����ж�
			if (b.board[i][j] != EMP)
				continue;

			//�����Χ��������(4*4)��û��2���ӣ���ֱ�ӹ�

			if (b.length < 6)
				if (!hasNeighors(b, i, j, 1, 1))
					continue;
			if (b.length >= 6)
				if (!hasNeighors(b, i, j, 2, 2))//������ܶ���(2,2)�������û�¼������Ͷ���������
					continue;

			pair<int, int>p(i, j);

			//��λ���˻���ֵ������Ϊ����������֮����ж��ٷ�
			int Hum_score = b.humScore[i][j];
			int Com_score = b.comScore[i][j];
			int Max_score = max(Hum_score, Com_score);

			//�Գ������ж�,���費��Ҫ
			//if (onlyThrees && maxScore < S.THREE) continue

			//�����ΪʲôҪ���Ƕ���
			//������һ�����ڸ�λ�ó�Ϊ5���ӣ����ǹؼ�λ�ã�������ԣ�����Ҫ�³�5������Ҫ��ֹ��5��
			
			
			//trial.push_back(MyStruct(p, Max_score));

			if (Com_score >= FIVE)//�ȿ������ܲ�������5
				comfives.push_back(p);
			else if (Hum_score >= FIVE)//�ٿ�����ܲ�������5
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

	//��һ�·���ʲô

	//���濼�ǵ������������֮��Com_score������°��壬Hum_score���º���

	//����Ҫ����˫����Ҫ���ǵ���������Ҫ��

	//������壬�Ǳ�ɱ�壬ֱ�ӷ���
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

	// �Լ��ܻ��ģ���ֱ�ӻ��ģ������ǳ���
	if (role == COM && !comfours.empty())
		return comfours;
	if (role == HUM && !humfours.empty())
		return humfours;

	//�����л��ĳ��ģ��Լ����Ķ�û����ֻ���Ƕ�����ģ��¶��棩 ����ʱ������ľͲ��ÿ�����)
	if (role == COM && !humfours.empty() && comblockedfours.empty())
		return humfours;
	if (role == HUM && !comfours.empty() && humblockedfours.empty())
		return comfours;

	//˫����Ҫ����
	// ����û�л��ģ�������˫�����������ȿ���˫��
	//�������Ҳ��˫�������ȹ������ȹ���˫��
	
	//������˫����������û�л���
	//if (role == COM && humfours.empty() && !comtwothrees.empty())
	//	return comtwothrees;
	//if (role == HUM && comfours.empty() && !humtwothrees.empty())
	//	return humtwothrees;
	 
	//������˫����������û�У����ȿ��Ƕ���
	//if (role == COM && comtwothrees.empty() && !humtwothrees.empty())
	//	return humtwothrees;
	//if (role == HUM && humtwothrees.empty() && !comtwothrees.empty())
	//	return comtwothrees;


	// �����л����Լ��г��ģ��򶼿�����
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

	//ʣ����Щ����Ҫ����
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

