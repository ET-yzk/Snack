//// �������ƣ�̰����AI
//// ���뻷����Visual Studio 2017��EasyX_2019���԰�
//// �������ߣ�����ؼ������ <591716377@qq.com>
//// ����ʱ�䣺2019-2-23
//// ����޸ģ�2019-3-8
//// ˵����ʹ��Debug�������ٿ��Ի�Release��
////
//// ���Ľ�����ʳ���㷨������������̾��룬
//// ����ʳ�������½ǻ�����Խӽ���Ҫ��Ч��,������ػ����⼴�ж����
//// �Ż��㷨�ٶ�
////
//#include <iostream>
//#include <conio.h>
//#include <ctime>
//#include <list>
//#include <queue>
//#include <set>
//#include <graphics.h>
//using namespace std;
//// ���ڲ���
//const int WINDOW_WIDTH = 640;	// ���ڿ��
//const int WINDOW_HEIGHT = 480;	// ���ڸ߶�
//
//// ��Ϸ����
//const int MAP_ROWNUM = 20;		// ��ͼ����
//const int MAP_COLNUM = 20;		// ��ͼ����
//const int GRIDGAP = 5;			// ���Ӽ�϶
//const int GRID = WINDOW_HEIGHT / MAP_COLNUM;	// ����ӿ��
//const int _GRID = GRID - 2 * GRIDGAP;			// С���ӿ��
//const int SPEED = 50;			// �߳�ʼ�ٶ�
//const int ACC = 20;				// �߼��ٶȣ���ʵ���ٶ�������
//
//// ��Ϸ���ݽṹ
//enum Direct { RIGHT = 77, DOWN = 80, LEFT = 75, UP = 72 };
//struct Coor {
//	int x, y, step;
//	Coor() { step = 0; }
//	Coor(int _x, int _y, int _step = 0) {
//		x = _x;
//		y = _y;
//		step = _step;
//	}
//	bool operator==(const Coor& t)const {
//		return (x == t.x) && (y == t.y);
//	}
//	bool operator!=(const Coor& t)const {
//		return (x != t.x) || (y != t.y);
//	}
//	bool operator<(const Coor& t)const {
//		return x == t.x ? y < t.y : x < t.x;
//	}
//};
//
//// ����ʵ��
//class Food {
//public:
//	Coor coor;			// ʳ������
//	bool EXISTFOOD;		// ����ʳ��
//	Food() { EXISTFOOD = true; }
//	~Food() { EXISTFOOD = false; }
//	// ����(0,0)~(limx,limy)������
//	void RandCoor(int limx, int limy) {
//		coor.x = rand() % limx;
//		coor.y = rand() % limy;
//	}
//};
//
//class Snake {
//public:
//	int length;			// �߳���
//	int speed;			// ���ٶ�
//	int acc;			// ���ٶ�
//	list<Coor> coor;	// ��������
//	Direct direct;		// �ߵ�ǰ����
//	Snake() {}
//	~Snake() {}
//	// ���ƶ�
//	void Move() {
//		Coor head = coor.front();
//		switch (direct) {
//		case UP:	head.y--;	break;
//		case DOWN:	head.y++;	break;
//		case LEFT:	head.x--;	break;
//		case RIGHT:	head.x++;	break;
//		}
//		coor.pop_back();		// β�ͳ���
//		coor.push_front(head);	// ��ͷ����
//	}
//	// ��ת��
//	void TurnDirect(char cmd = 0x00) {
//		// ʹ��while������if
//		if (cmd == 0x00) {
//			while (_kbhit()) {
//				cmd = _getch();
//			}
//		}
//		// ���η�����ͬ���ü��ٶ�
//		if (cmd == direct)
//			acc = ACC;
//		else
//			acc = 0;
//		switch (cmd)
//		{
//		case UP:
//			if (direct != DOWN)
//				direct = UP;
//			break;
//		case DOWN:
//			if (direct != UP)
//				direct = DOWN;
//			break;
//		case LEFT:
//			if (direct != RIGHT)
//				direct = LEFT;
//			break;
//		case RIGHT:
//			if (direct != LEFT)
//				direct = RIGHT;
//			break;
//		}
//	}
//};
//
//class SnakeGame {
//private:
//	bool isAI;
//public:
//	Snake snake;
//	Food food;
//	SnakeGame() { GameInit(); }
//	~SnakeGame() {}
//	// ��Ϸ��ʼ��
//	void GameInit() {
//		isAI = false;
//		snake.length = 3;
//		snake.speed = SPEED;
//		snake.acc = 0;
//		snake.direct = UP;
//		while (!snake.coor.empty()) {
//			snake.coor.pop_back();
//		}
//		Coor body(MAP_ROWNUM / 2, MAP_COLNUM / 2);
//		for (int i = 0; i < snake.length; i++) {
//			snake.coor.push_back(body);
//			body.y++;
//		}
//		srand((unsigned)time(0));
//		food.RandCoor(MAP_COLNUM, MAP_ROWNUM);
//	}
//	// ����ͼ
//	void DrawMap() {
//		setfillcolor(DARKGRAY);
//		solidrectangle(0, 0, GRID * MAP_COLNUM, GRID * MAP_ROWNUM);
//		setcolor(LIGHTGRAY);
//		line(WINDOW_HEIGHT, 0, WINDOW_HEIGHT, WINDOW_HEIGHT);
//		// ��ʳ��
//		setfillcolor(RED);
//		fillrectangle(food.coor.x * GRID + GRIDGAP, food.coor.y * GRID + GRIDGAP,
//			(food.coor.x + 1) * GRID - GRIDGAP, (food.coor.y + 1) * GRID - GRIDGAP);
//		// ����
//		setfillcolor(WHITE);
//		Coor temp = snake.coor.front();
//		for (auto iter : snake.coor) {
//			solidrectangle(iter.x * GRID + GRIDGAP, iter.y * GRID + GRIDGAP,
//				(iter.x + 1) * GRID - GRIDGAP, (iter.y + 1) * GRID - GRIDGAP);
//			// ����϶
//			int iter_x = iter.x * GRID + GRIDGAP;
//			int iter_y = iter.y * GRID + GRIDGAP;
//			int temp_x = temp.x * GRID + GRIDGAP;
//			int temp_y = temp.y * GRID + GRIDGAP;
//			if (temp.x == iter.x) {
//				if (iter.y > temp.y) {
//					solidrectangle(temp_x, temp_y + _GRID, iter_x + _GRID, iter_y);
//				}
//				if (iter.y < temp.y) {
//					solidrectangle(iter_x, iter_y + _GRID, temp_x + _GRID, temp_y);
//				}
//			}
//			if (temp.y == iter.y) {
//				if (iter.x > temp.x) {
//					solidrectangle(temp_x + _GRID, temp_y, iter_x, iter_y + _GRID);
//				}
//				if (iter.x < temp.x) {
//					solidrectangle(iter_x + _GRID, iter_y, temp_x, temp_y + _GRID);
//				}
//			}
//			temp = iter;
//		}
//	}
//	// �����ʳ��
//	void EatFood() {
//		Coor head = snake.coor.front();
//		if (head == food.coor) {
//			food.EXISTFOOD = false;
//			snake.coor.push_back(snake.coor.back());
//			snake.length++;
//		}
//	}
//	// ����ʳ��
//	void CreatFood() {
//		if (food.EXISTFOOD == false) {
//			list<Coor>::const_iterator iter;
//			while (true) {
//				food.RandCoor(MAP_COLNUM, MAP_ROWNUM);
//				if (!onSnake(food.coor))
//					break;
//			}
//			food.EXISTFOOD = true;
//		}
//	}
//	// �ж���Ϸ����
//	bool GameOver() {
//		Coor head = snake.coor.front();
//		if (!inBorder(head) || onSnake_ExceptHead(head) || EatFullScreen()) {
//			return true;
//		}
//		return false;
//	}
//	// �Ƿ����ʳ��
//	bool EatFullScreen() {
//		return snake.length == MAP_COLNUM * MAP_ROWNUM;
//	}
//	// ��Ϸ��������
//	void ShowGameEnd() {
//		setfillcolor(BLACK);
//		/*fillrectangle(0, WINDOW_HEIGHT / 4, WINDOW_HEIGHT, WINDOW_HEIGHT / 4 * 3);*/
//		// ����Ļ��������ַ���
//		TCHAR* str_end = (TCHAR*)("GAME OVER!");
//		if (EatFullScreen())
//			str_end = (TCHAR*)("YOU WIN!");
//		// x64�ᱨ���棺��size_t��ת������int�������ܶ�ʧ����
//		int Tstrlen = (int)_tcslen(str_end);
//		outtextxy(WINDOW_HEIGHT / 2 - Tstrlen * 20 / 4, WINDOW_HEIGHT / 2 - 20 / 4, str_end);
//	}
//	// ������Ϸ�����Ϣ
//	void ShowGameInfo() {
//		// ����ɫ��
//		setfillcolor(BLACK);
//		solidrectangle(WINDOW_HEIGHT, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
//		// �ߴ���Ϣ
//		TCHAR str_mapsize[20];
//		swprintf_s(str_mapsize, _T("MAPSIZE:  %d��%d"), MAP_COLNUM, MAP_ROWNUM);
//		settextcolor(WHITE);
//		outtextxy(WINDOW_HEIGHT + 20, 20, str_mapsize);
//		// AI״̬��Ϣ
//		TCHAR* str_ai = (TCHAR*)("AI:  OFF");
//		if (isAI == true)	str_ai = (TCHAR*)("AI:  ON");
//		outtextxy(WINDOW_HEIGHT + 20, 50, str_ai);
//		// �ٶ���Ϣ
//		TCHAR str_speed[20];
//		swprintf_s(str_speed, _T("SPEED:  %d"), snake.speed + snake.acc);
//		outtextxy(WINDOW_HEIGHT + 20, 80, str_speed);
//		// ���ٶ���Ϣ
//		TCHAR str_acc[20];
//		swprintf_s(str_acc, _T("ACC:  %d"), snake.acc);
//		outtextxy(WINDOW_HEIGHT + 20, 110, str_acc);
//		// �߳�����Ϣ
//		TCHAR str_life[20];
//		swprintf_s(str_life, _T("LIFE:  %d/%d"), snake.length, MAP_COLNUM * MAP_ROWNUM);
//		outtextxy(WINDOW_HEIGHT + 20, 140, str_life);
//		// ������,ʹ��������Ϊ�˴���β������Ϊ���߽��
//		const Coor& snakeHead = snake.coor.front();
//		const Coor& snakeTail = snake.coor.back();
//		// ����
//		TCHAR str_test[20];
//		swprintf_s(str_test, _T("��β�Ͳ���:  %d"), canFindPath(snakeHead, snakeTail));
//		outtextxy(WINDOW_HEIGHT + 20, 170, str_test);
//		// ʳ��������Ϣ
//		TCHAR str_food[20];
//		swprintf_s(str_food, _T("ʳ������:  (%d,%d)"), food.coor.x, food.coor.y);
//		outtextxy(WINDOW_HEIGHT + 20, 200, str_food);
//		// ��ͷ������Ϣ
//		TCHAR str_head[20];
//		swprintf_s(str_head, _T("��ͷ����:  (%d,%d)"), snakeHead.x, snakeHead.y);
//		outtextxy(WINDOW_HEIGHT + 20, 230, str_head);
//		// ��β������Ϣ
//		TCHAR str_tail[20];
//		swprintf_s(str_tail, _T("��β����:  (%d,%d)"), snakeTail.x, snakeTail.y);
//		outtextxy(WINDOW_HEIGHT + 20, 260, str_tail);
//		// ������Ϣ
//		TCHAR* str_dir;
//		switch (snake.direct) {
//		case RIGHT:	str_dir = (TCHAR*)("����:  RIGHT");	break;
//		case DOWN:	str_dir = (TCHAR*)("����:  DOWN");		break;
//		case LEFT:	str_dir = (TCHAR*)("����:  LEFT"); 	break;
//		case UP:	str_dir = (TCHAR*)("����:  UP");		break;
//		default:	str_dir = (TCHAR*)("����:  None");
//		}
//		outtextxy(WINDOW_HEIGHT + 20, 290, str_dir);
//		// ��Ϸ����˵��
//		outtextxy(WINDOW_HEIGHT + 20, 320, _T("����˵��:"));
//		outtextxy(WINDOW_HEIGHT + 20, 340, _T("ʹ�÷��������"));
//		outtextxy(WINDOW_HEIGHT + 20, 360, _T("�������������"));
//		outtextxy(WINDOW_HEIGHT + 20, 380, _T("��  :      ��"));
//		outtextxy(WINDOW_HEIGHT + 20, 400, _T("��  :      ��"));
//		outtextxy(WINDOW_HEIGHT + 20, 420, _T("��  :      ��"));
//		outtextxy(WINDOW_HEIGHT + 20, 440, _T("��  :      ��"));
//	}
/******AI*******/
//	// AI���
//	void OpenAI() { isAI = true; }
//	void CloseAI() { isAI = false; }
//	// �õ���һ��AIָ��--
//	char getNextCmd() {
//		if (isAI == false)
//			return 0x00;
//		char cmd = 0x00;
//		// ������ҵ�ʳ��
//		if (canFindFood(snake.coor.front())) {
//			// ģ��һ����
//			SnakeGame simulate = *this;
//			// ȥ��ʳ��
//			while (simulate.food.EXISTFOOD) {
//				simulate.snake.TurnDirect(simulate.NextCmdToFood());
//				simulate.snake.Move();
//				simulate.EatFood();
//			}
//			// ������껹���ҵ�β��/��β�͵ľ������1
//			if (simulate.canFindPath(simulate.snake.coor.front(), simulate.snake.coor.back()) > 1) {
//				// ����ȥ��
//				cmd = NextCmdToFood();
//			}
//			else {
//				// �����Ҳ���
//				cmd = NextCmdToFarAway(snake.coor.front());
//			}
//		}
//		else {
//			// �Ҳ���ʳ��
//			cmd = NextCmdToFarAway(snake.coor.front());
//		}
//		return cmd;
//	}
//	// ����·�����ز����������ڷ���-1
//	int canFindPath(const Coor& _start, const Coor& _end) {
//		if (_start == _end) {
//			return 0;
//		}
//		const int next[4][2] = { {1,0} ,{0,1}, {-1,0}, {0,-1} }; // ��������
//		queue<Coor> bfs_que;
//		set<Coor> snake_set;
//		Coor tcoor;
//		bfs_que.push(_start);
//		for (auto iter : snake.coor) {
//			snake_set.insert(iter);
//		}
//		// ����յ���β�;Ͱ�β����Ϊ���߽�� *
//		// ����ʱ��Ҫʹ������
//		if (&_end == &snake.coor.back()) {
//			snake_set.erase(_end);
//		}
//		while (!bfs_que.empty()) {
//			for (int k = 0; k < 4; k++) {
//				tcoor.x = bfs_que.front().x + next[k][0];
//				tcoor.y = bfs_que.front().y + next[k][1];
//				// ������ͼ�����´�ѭ��
//				if (!inBorder(tcoor)) {
//					continue;
//				}
//				// ���ϰ�û���߹��Ľ��������
//				if (!snake_set.count(tcoor)) {
//					tcoor.step = bfs_que.front().step + 1;
//					snake_set.insert(tcoor);
//					bfs_que.push(tcoor);
//				}
//				// ����Ŀ�귵�ز���
//				if (tcoor == _end) {
//					return tcoor.step;
//				}
//			}
//			bfs_que.pop();
//		}
//		return -1;
//	}
//	// ���ڵ�β�͵�·��
//	bool canFindTail(Coor _start) {
//		return canFindPath(_start, snake.coor.back()) >= 0 ? true : false;
//	}
//	// ���ڵ�ʳ���·��
//	bool canFindFood(Coor _start) {
//		return canFindPath(_start, food.coor) >= 0 ? true : false;
//	}
//	// ��̾����ʳ��
//	char NextCmdToFood() {
//		const int next[4][2] = { { 1,0 } ,{ 0,1 },{ -1,0 },{ 0,-1 } }; // ��������
//		// �õ�ͷ����Χ4��
//		Coor aroundPoint[4];
//		for (int i = 0; i < 4; i++) {
//			aroundPoint[i].x = snake.coor.front().x + next[i][0];
//			aroundPoint[i].y = snake.coor.front().y + next[i][1];
//			if (!inBorder(aroundPoint[i]) || onSnake_ExceptTail(aroundPoint[i]))	// ���⴦��β��
//				aroundPoint[i].step = -1;
//			else
//				aroundPoint[i].step = canFindPath(aroundPoint[i], food.coor);
//		}
//		// ѡ���������
//		int minstep_index = 0;
//		for (int i = 1; i < 4; i++) {
//			// ��0��ʾ��ʳ��ֱ����
//			// �����-1������Ƚ�
//			if (aroundPoint[minstep_index].step == -1)
//				minstep_index = i;
//			if (aroundPoint[i].step != -1) {
//				if (aroundPoint[i].step < aroundPoint[minstep_index].step) {
//					minstep_index = i;
//				}
//			}
//		}
//		char ret = 0x00;
//		// ���ز������Ҳ���ʳ��ͷ���0x00ʲô������
//		if (aroundPoint[minstep_index].step != -1)
//			ret = RetCmd(aroundPoint[minstep_index]);
//		return ret;
//	}
//	// ���ڳ�ʳ������Զ
//
//	// Զ��ʳ��--���Ľ�**
//	char NextCmdToFarAway(const Coor& coor) {
//		const int next[4][2] = { { 1,0 } ,{ 0,1 },{ -1,0 },{ 0,-1 } }; // ��������
//		// �õ���Χ�ĵ������پ���
//		Coor aroundPoint[4];
//		for (int i = 0; i < 4; i++) {
//			aroundPoint[i].x = snake.coor.front().x + next[i][0];
//			aroundPoint[i].y = snake.coor.front().y + next[i][1];
//			// �����پ���,���ϰ��ĵ���Ϊ-1
//			if (canFindTail(aroundPoint[i]) && inBorder(aroundPoint[i]) && !onSnake_ExceptTail(aroundPoint[i]))
//				aroundPoint[i].step = getManhattanDistance(aroundPoint[i], coor);
//			else // *������βӦ����Ϊ����
//				aroundPoint[i].step = -1;
//		}
//		// �ܵ�β��,Զ��ʳ��
//		// ��һ�ֲ�����ѡ��β��Զ��
//		int maxstep_index = 0;
//		for (int i = 1; i < 4; i++) {
//			// ���ںź���Ҫ
//			if ((aroundPoint[i].step >= aroundPoint[maxstep_index].step)) {
//				maxstep_index = i;
//			}
//		}
//		char cmd = 0x00;
//		if (aroundPoint[maxstep_index].step != -1)
//			cmd = RetCmd(aroundPoint[maxstep_index]);
//		return cmd;
//	}
//	// ��Զ����׷β��
//	char NextCmdToTail() {
//		const int next[4][2] = { { 1,0 } ,{ 0,1 },{ -1,0 },{ 0,-1 } }; // ��������
//		// �õ�ͷ����Χ4��
//		Coor aroundPoint[4];
//		for (int i = 0; i < 4; i++) {
//			aroundPoint[i].x = snake.coor.front().x + next[i][0];
//			aroundPoint[i].y = snake.coor.front().y + next[i][1];
//			if (inBorder(aroundPoint[i]) && !onSnake_ExceptTail(aroundPoint[i]))	//	*���⴦��β��
//				aroundPoint[i].step = canFindPath(aroundPoint[i], snake.coor.back());
//			else
//				aroundPoint[i].step = -1;
//		}
//		// ѡ����Զ�ĵ�
//		int maxstep_index = 0;
//		for (int i = 1; i < 4; i++) {
//			// ��0��ʾ��ʳ��ֱ����
//			// �����-1������Ƚ�
//			if (aroundPoint[maxstep_index].step == -1)
//				maxstep_index = i;
//			if (aroundPoint[i].step != -1) {
//				if (aroundPoint[i].step > aroundPoint[maxstep_index].step) {
//					maxstep_index = i;
//				}
//			}
//		}
//		char ret = 0x00;
//		// ���ز������Ҳ���ʳ��ͷ���0x00ʲô������
//		if (aroundPoint[maxstep_index].step != -1)
//			ret = RetCmd(aroundPoint[maxstep_index]);
//		return ret;
//	}
//	// ���ؿ��õ�ָ��,��������Χ4��
//	char RetCmd(Coor nextPoint) {
//		char cmd = 0x00;
//		int dx = nextPoint.x - snake.coor.front().x;
//		int dy = nextPoint.y - snake.coor.front().y;
//		if (dx == 0 && dy < 0)
//			cmd = UP;
//		if (dx == 0 && dy > 0)
//			cmd = DOWN;
//		if (dx < 0 && dy == 0)
//			cmd = LEFT;
//		if (dx > 0 && dy == 0)
//			cmd = RIGHT;
//		return cmd;
//	}
//	// ���������پ���
//	int getManhattanDistance(Coor _a, Coor _b) {
//		return abs(_a.x - _b.x) + abs(_a.y - _b.y);
//	}
//	// ����������/������ͷ��β
//	bool onSnake(Coor coor) {
//		for (auto iter : snake.coor) {
//			if (coor == iter) {
//				return true;
//			}
//		}
//		return false;
//	}
//	// ����������/��������ͷ
//	bool onSnake_ExceptHead(Coor coor) {
//		auto iter = snake.coor.begin();
//		for (iter++; iter != snake.coor.end(); iter++) {
//			if (coor == *iter) {
//				return true;
//			}
//		}
//		return false;
//	}
//	// ����������/��������β
//	bool onSnake_ExceptTail(Coor coor) {
//		auto iter = snake.coor.begin();
//		auto flag = --snake.coor.end();
//		for (; iter != flag; iter++) {
//			if (coor == *iter) {
//				return true;
//			}
//		}
//		return false;
//	}
//	// �����ڷ�����
//	bool inBorder(Coor coor)const {
//		return (coor.x >= 0 && coor.x < MAP_COLNUM&& coor.y >= 0 && coor.y < MAP_ROWNUM);
//	}
//};
//// �������
//int main() {
//	// �Ӳ���, SHOWCONSOLE��������̨
//	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
//	// ����˫�����ͼ
//	BeginBatchDraw();
//	SnakeGame SG;
//	SG.OpenAI();
//	_getch();
//	while (true) {
//		SG.EatFood();
//		SG.CreatFood();
//		SG.snake.TurnDirect(SG.getNextCmd());
//		SG.snake.Move();
//		if (SG.GameOver()) {
//			SG.DrawMap();
//			SG.ShowGameEnd();
//			SG.ShowGameInfo();	//��ʾ������Ϣ
//			FlushBatchDraw();
//			_getch();
//			SG.GameInit();
//			SG.OpenAI();
//		}
//		SG.ShowGameInfo();
//		SG.DrawMap();
//		FlushBatchDraw();
//		Sleep(1000 / (SG.snake.speed + SG.snake.acc));
//	}
//	EndBatchDraw();
//	closegraph();
//	return 0;
//}


/******�û��������******/
//#include <easyx.h>      // ����ͼ�ο�ͷ�ļ�
//#include <conio.h>
//#include <stdio.h>
////#include <windows.h>
//#include <time.h>
//#include <stdlib.h>
//#include <string.h>
//
////wchar_t �� char��������ת��
//char * wchar2char(const wchar_t* wchar)
//{
//    char * m_char;
//    int len = WideCharToMultiByte(CP_ACP, 0, wchar, wcslen(wchar), NULL, 0, NULL, NULL);
//    m_char = new char[len + 1];
//    WideCharToMultiByte(CP_ACP, 0, wchar, wcslen(wchar), m_char, len, NULL, NULL);
//    m_char[len] = '\0';
//    return m_char;
//}
//wchar_t * char2wchar(const char* cchar)
//{
//    wchar_t *m_wchar = new wchar_t[strlen(cchar) + 1];
//    MultiByteToWideChar(CP_ACP, 0, cchar, strlen(cchar), m_wchar, strlen(cchar));
//    m_wchar[strlen(cchar)] = L'\0';
//    return m_wchar;
//}
//
//#define frame_height 30 //define map size
//#define frame_width 30
//#define UP 'w' //define operate key
//#define DOWN 's'
//#define LEFT 'a'
//#define RIGHT 'd'
//#define SIZE 16
//#define N 4
//FILE* fp;
//int i, j, k, m, n, s[N];
//wchar_t s1[5], s2[5];
//char ch = UP; //initial direction
//int grow = 0; //flag: if snake grow
//wchar_t temp[20];
//struct Food {
//    int x;
//    int y;
//}food;
//struct Snake {
//    int x[50];
//    int y[50];
//    int len;
//    int speed;
//    //int color;    //�����̵���ɫ
//}snake; //snake[0] is head
//typedef struct The_users //���ڴ����û��˺�����
//{
//    char id[11];//ID
//    char pwd[20];//password
//}users;
//users a, b;//��Ա����,������½��ע��
//void init_map(void);
//void update_food(void);
//void move_snake(void);
//int is_alive(void);
//void get_speed(void);
//void gotoxy(int x, int y);
//void redraw_map(void);
//void menu();
//void registers();
//void Login();
////void Create_File();
//void score();
//int compInc(const void* a, const void* b);
//int compDec(const void* a, const void* b);
//int main()
//{
//    initgraph(640, 480);//������ͼ����
//    menu();
//    score();
//    return 0;
//}
//void redraw_map(void)
//{
//    //initial bar
//    for (j = 0; j < frame_width; j++)
//    {
//        moveto(j * SIZE, 0);
//        setfillcolor(BLUE);
//        fillrectangle(j * SIZE, 0, j * SIZE + SIZE, SIZE);
//        moveto(j * SIZE, (frame_height - 1) * SIZE);
//        setfillcolor(BLUE);
//        fillrectangle(j * SIZE, (frame_height - 1) * SIZE, j * SIZE + SIZE, (frame_height - 1) * SIZE + SIZE);
//    }
//    for (i = 1; i < frame_height - 1;)
//    {
//        moveto(0, i * SIZE);
//        setfillcolor(BLUE);
//        fillrectangle(0, i * SIZE, 0 + SIZE, i * SIZE + SIZE);
//        moveto((frame_width - 1) * SIZE, i * SIZE);
//        setfillcolor(BLUE);
//        fillrectangle((frame_width - 1) * SIZE, i * SIZE, (frame_width - 1) * SIZE + SIZE, i * SIZE + SIZE);
//        i = i + 1;
//    }
//}
//void init_map(void)
//{
//    //initial food
//    srand((unsigned int)time(NULL));
//    food.x = rand() % (frame_height - 2) + 1;
//    food.y = rand() % (frame_width - 2) + 1;
//    moveto(food.y * SIZE, food.x * SIZE);
//    setfillcolor(RED);
//    fillcircle(food.y * SIZE + SIZE / 2, food.x * SIZE + SIZE / 2, SIZE / 2);
//    //initial snake
//    snake.x[0] = (frame_height) / 2;
//    snake.y[0] = (frame_width) / 2;
//    moveto(snake.y[0] * SIZE, snake.x[0] * SIZE);
//    setfillcolor(GREEN);
//    fillcircle(snake.y[0] * SIZE + SIZE / 2, snake.x[0] * SIZE + SIZE / 2, SIZE / 2);
//    snake.len = 3;
//    snake.speed = 200;
//    for (k = 1; k < snake.len; k++)
//    {
//        snake.x[k] = snake.x[k - 1] + 1;
//        snake.y[k] = snake.y[k - 1];
//        moveto(snake.y[k] * SIZE, snake.x[k] * SIZE);
//        setfillcolor(GREEN);
//        fillcircle(snake.y[k] * SIZE + SIZE / 2, snake.x[k] * SIZE + SIZE / 2, SIZE / 2);
//    }
//    //initial bar
//    for (j = 0; j < frame_width; j++)
//    {
//        moveto(j * SIZE, 0);
//        setfillcolor(BLUE);
//        fillrectangle(j * SIZE, 0, j * SIZE + SIZE, SIZE);
//        moveto(j * SIZE, (frame_height - 1) * SIZE);
//        setfillcolor(BLUE);
//        fillrectangle(j * SIZE, (frame_height - 1) * SIZE, j * SIZE + SIZE, (frame_height - 1) * SIZE + SIZE);
//    }
//    for (i = 1; i < frame_height - 1;)
//    {
//        moveto(0, i * SIZE);
//        setfillcolor(BLUE);
//        fillrectangle(0, i * SIZE, 0 + SIZE, i * SIZE + SIZE);
//        moveto((frame_width - 1) * SIZE, i * SIZE);
//        setfillcolor(BLUE);
//        fillrectangle((frame_width - 1) * SIZE, i * SIZE, (frame_width - 1) * SIZE + SIZE, i * SIZE + SIZE);
//        i = i + 1;
//    }
//}
////generate food
//void update_food()
//{
//    if (snake.x[0] == food.x && snake.y[0] == food.y)
//    {
//        food.x = rand() % (frame_height - 2) + 1;
//        food.y = rand() % (frame_width - 2) + 1;
//        for (k = 1; k < snake.len; k++)
//        {
//            if (snake.x[k] == food.x && snake.y[k] == food.y)
//            {
//                food.x = rand() % (frame_height - 2) + 1;
//                food.y = rand() % (frame_width - 2) + 1;
//            }
//        }
//        moveto(food.y * SIZE, food.x * SIZE);
//        setfillcolor(RED);
//        fillcircle(food.y * SIZE + SIZE / 2, food.x * SIZE + SIZE / 2, SIZE / 2);
//        snake.len++;
//        grow = 1;
//    }
//}
////move snake
//
//void move_snake()
//{
//    char ch1 = ch;
//    if (_kbhit())
//    {
//        ch1 = _getch();
//    }
//    //��ֹ��ԭ·���ص���ʧ��
//    if ((ch == UP && ch1 == DOWN) || (ch1 == UP && ch == DOWN) \
//        || (ch == LEFT && ch1 == RIGHT) || (ch1 == LEFT && ch == RIGHT))
//    {
//        ch1 = ch;
//    }
//    else
//    {
//        ch = ch1;
//    }
//    if (!grow)
//    {
//        moveto(snake.y[snake.len - 1] * SIZE, snake.x[snake.len - 1] * SIZE);
//        setfillcolor(BLACK);
//        solidrectangle(snake.y[snake.len - 1] * SIZE, snake.x[snake.len - 1] * SIZE, snake.y[snake.len - 1] * SIZE + SIZE, snake.x[snake.len - 1] * SIZE + SIZE);
//    }
//    for (k = snake.len - 1; k > 0; k--)
//    {
//        snake.x[k] = snake.x[k - 1];
//        snake.y[k] = snake.y[k - 1];
//    }
//    switch (ch)
//    {
//    case UP:  snake.x[0]--; break;
//    case DOWN: snake.x[0]++; break;
//    case LEFT:  snake.y[0]--; break;
//    case RIGHT:  snake.y[0]++; break;
//    default:  break;
//    }
//    moveto(snake.y[0] * SIZE, snake.x[0] * SIZE);
//    setfillcolor(GREEN);
//    fillcircle(snake.y[0] * SIZE + SIZE / 2, snake.x[0] * SIZE + SIZE / 2, SIZE / 2);
//    grow = 0;
//}
////is alive
//int is_alive(void)
//{
//    if (snake.x[0] == 0 || snake.x[0] == frame_height - 1 || snake.y[0] == frame_width - 1 || snake.y[0] == 0)
//        return 0;
//    for (k = 1; k < snake.len; k++)
//        if (snake.x[k] == snake.x[0] && snake.y[k] == snake.y[0])
//            return 0;
//    return 1;
//}
////speed up
//void get_speed(void)
//{
//    if (snake.len <= 6)
//        snake.speed = 200;
//    else if (snake.len <= 10)
//        snake.speed = 100;
//    else if (snake.len <= 20)
//        snake.speed = 50;
//    else if (snake.len <= 30)
//        snake.speed = 30;
//    else snake.speed = 20;
//}
////move cursor
//void gotoxy(int x, int y)
//{
//    HANDLE hout;
//    COORD cor;
//    hout = GetStdHandle(STD_OUTPUT_HANDLE);
//    cor.X = y;
//    cor.Y = x;
//    SetConsoleCursorPosition(hout, cor);
//}
//void menu()
//{
//    InputBox(s1, 5, L"���������֣�1.��ʼ��Ϸ 2.�߷ְ� 3.�˳���Ϸ");
//    int x, y[3];
//    //sscanf_s(s1, "%d", &x);//���û�����ת��Ϊ����
//    x = _wtoi(s1);
//    if (x == 1)
//    {
//        InputBox(s2, 5, L"���������֣�1.ע��2.��½");
//        x = _wtoi(s2);
//        if (x == 1) {
//            registers();
//            Login();
//        }
//        else if (x == 2) {
//            Login();
//        }
//        init_map(); //��ʼ����ͼ
//        while (1)
//        {
//            update_food();
//            //�Ƿ����ʳ��
//            get_speed();  //��ȡ�ٶ�
//            move_snake();  //�ƶ�����
//            redraw_map();//�ػ��ͼ
//            Sleep(snake.speed);
//            //�ƶ��ٶ�
//            if (!(is_alive()))
//                //�ߵ�����(ײǽ����ʳ)
//                break;
//        }
//        closegraph();//�رջ�ͼ����
//        printf("Game Over!\n");
//        printf("��ĵ÷֣�%d", snake.len - 3);
//        _getch();
//    }
//    else if (x == 2)
//    {
//        closegraph();
//        printf("                    ���а�\n");
//        fopen_s(&fp, "scores.txt", "r");
//        for (x = 0; x < N - 1; x++) {
//            fscanf_s(fp, "%d", &y[x]);
//            printf("%d\n", y[x]);
//        }
//        fclose(fp);
//        _getch();
//
//    }
//    else
//    {
//        closegraph();
//    }
//}
//void registers()//ע���˺�����
//{
//    fopen_s(&fp, "Users1.txt", "r");
//    fscanf_s(fp, "%s%s", b.id, sizeof(b.id), b.pwd, sizeof(b.pwd));
//    InputBox(temp, 11, L"�������˺�");
//    strcpy_s(a.id,wchar2char(temp));
//    while (1)
//    {
//        if (strcmp(a.id, b.id) != 0)//��������ַ��������
//        {
//            if (!feof(fp))//���δ���ļ�ĩβ
//            {
//                fscanf_s(fp, "%s%s", b.id, sizeof(b.id), b.pwd, sizeof(b.pwd));
//            }
//            else break;
//        }
//        else
//        {
//            outtextxy(220, 200, L"���û����ѱ�ע��");
//            fclose(fp);
//            _getch();
//            exit(0);
//        }
//    }
//    fclose(fp);
//    InputBox(temp, 10, L"����������");
//    strcpy_s(a.pwd, wchar2char(temp));
//    fopen_s(&fp, "Users1.txt", "a");
//    fprintf_s(fp, "%s %s\n", a.id, a.pwd);
//    outtextxy(220, 200, L"�˺�ע��ɹ���");
//    fclose(fp);
//}
//void Login()//��½�˺�����
//{
//    fopen_s(&fp, "Users1.txt", "r");
//    fscanf_s(fp, "%s%s", b.id, sizeof(b.id), b.pwd, sizeof(b.pwd));
//    InputBox(temp, 11, L"�������˺�");
//    strcpy_s(a.id, wchar2char(temp));
//    while (1)
//    {
//        if (strcmp(a.id, b.id) == 0) break;//����ҵ�������û���
//        else
//        {
//            if (!feof(fp))//����ļ�δ����
//                fscanf_s(fp, "%s%s", b.id, sizeof(b.id), b.pwd, sizeof(b.pwd));
//            else
//            {
//                outtextxy(220, 200, L"���û���������!");
//                fclose(fp);
//                _getch();
//                exit(0);
//            }
//        }
//    }
//    InputBox(temp, 20, L"����������");
//    strcpy_s(a.pwd, wchar2char(temp));
//    if (strcmp(a.pwd, b.pwd) == 0)//�������ƥ��
//    {
//        fclose(fp);
//        outtextxy(250, 200, L"��½�ɹ���");
//        initgraph(640, 480);
//    }
//    else
//    {
//        outtextxy(220, 200, L"���벻��ȷ");
//        _getch();
//        exit(0);
//    }
//}
//void score()
//{
//    fopen_s(&fp, "scores.txt", "r");
//    for (n = 0; n < N - 1; n++)
//    {
//        fscanf_s(fp, "%d", &m);
//        s[n] = m;
//    }
//    s[N - 1] = snake.len - 3;
//    qsort(s, N, sizeof(s[0]), compDec);
//    fclose(fp);
//    fopen_s(&fp, "scores.txt", "w");
//    for (n = 0; n < N - 1; n++)
//    {
//        fprintf_s(fp, "%d\n", s[n]);
//    }
//    fclose(fp);
//}
//int compInc(const void* a, const void* b)
//{
//    return *(int*)a - *(int*)b;
//}//��������
//int compDec(const void* a, const void* b) {
//    return *(int*)b - *(int*)a;
//}//��������



//////#include<stdio.h>
//////#include<easyx.h>
//////#include<conio.h>
//////
//////int main()
//////{
//////	// ��ʼ����ͼ����
//////	initgraph(640, 480);
//////
//////	// �����ַ������������������û�����
//////	wchar_t s[10];
//////	char str[20];
//////	InputBox(s, 10, L"������뾶");
//////
//////	// ���û�����ת��Ϊ����
//////	int r = _wtoi(s);
//////
//////	// ��Բ
//////	circle(320, 240, r);
//////
//////	// ��������˳�
//////	_getch();
//////	closegraph();
//////
//////	return 0;
//////}


//////// �Թ�.cpp : �������̨Ӧ�ó������ڵ㡣
////////#include "stdafx.h"
//////#include <graphics.h>
//////#include <stack>
//////#include <vector>
//////using std::stack;				// ʹ��STL��ջ
//////using std::vector;				// ʹ��STL����������
//////
//////								// ��Ϸ��Ϣ
//////#define WIN_WIDTH	400			// ���ڵĿ��(��λ������)
//////#define WIN_HEIGHT	300			// ���ڵĸ߶�(��λ������)
//////								// !!ע��������������㷨��ԭ�򣬵�ͼ���ֻ��Ϊ����
//////#define GAME_WIDTH	41			// ��ͼ�Ŀ��(��λ����)
//////#define GAME_HEIGHT	51			// ��ͼ�ĸ߶�(��λ����)
//////
//////#define WALL		1			// ǽ�ڵ����ֱ��
//////#define GROUND		0			// ��������ֱ��
//////#define FILLSTATE	2			// ����վ�����ֱ��
//////#define ENDPOS		3			// �յ�����ֱ��
//////
//////#define MAXVIEW		8.0			// ������Ұ
//////#define MINVIEW		1			// ��С����Ұ
//////#define FILLNUM		10			// ����վ������
//////#define DARKTIME	12			// ��Ұ�½�1ͼ�������ʱ��
//////
//////								// ȫ�ֱ����б�
//////int		g_BlockSize;			// ���С
//////int		g_GameMap[GAME_HEIGHT][GAME_WIDTH];	// ��ͼ(��ߵ�λΪ��)
//////POINT	g_EndPos;				// �յ�λ��
//////POINT   g_PlayerPos;			// ����ڵ�ͼ�ϵ�λ��
//////POINT	g_CameraPos;			// �����(��Ļ���Ͻ�)�ڵ�ͼ�ϵ�λ��
//////IMAGE	g_MapImage;				// ��ͼ��ͼƬ(���ڵ�ͼ�ǹ̶��ģ��ڲ��ı����ŵ������ֻ��Ҫ����һ��)
//////double	g_ViewArray;			// ��Ұ
//////UINT	g_BeginTime;			// ��Ϸ��ʼʱ��ʱ��
//////UINT	g_LastFillTime;			// �ϴ�Ϊ�͵Ƽ��͵�ʱ��
//////
//////
//////								// �����б�
//////void initGame();				// ��ʼ����Ϸ
//////void endGame();					// ������Ϸ
//////void draw();					// ���ƺ���
//////bool upDate();					// ���ݸ��º���
//////void absDelay(int delay);		// �����ӳ�
//////
//////bool canMove(POINT pos);		// �ж�ĳ��λ���Ƿ�����ƶ�
//////void computeCameraPos();		// ����������ڵ�ͼ�ϵ�λ��
//////void rePaintMap();				// �ػ��ͼ
//////
//////void drawWall(POINT pos);		// ����ǽ��ͼ��ĺ���
//////void drawGround(POINT pos);		// ���Ƶ���ͼ��ĺ���
//////void drawFillState(POINT pos);	// �����͵�ͼ��ĺ���
//////void drawEndPos(POINT pos);		// �����յ�
//////void drawPlayer();				// ��������ĺ���
//////void drawView();				// ������Ұ
//////
//////int main()
//////{
//////	initGame();
//////
//////	while (1)
//////	{
//////		if (!upDate()) break;	// ����
//////		draw();					// ����
//////		absDelay(16);			// �����ӳ� 16 ���룬����ÿ�� 60 ֡
//////	}
//////
//////	endGame();
//////	return 0;
//////}
//////
//////void initGame()
//////{
//////	g_BlockSize = 32;			// ��ʼͼ���СΪ 32 ������
//////	srand(GetTickCount());		// ��ʼ�����������
//////
//////								// ��ʼ�������
//////	for (int i = 0; i < GAME_HEIGHT; i++)
//////	{
//////		for (int j = 0; j < GAME_WIDTH; j++)
//////		{
//////			if (i % 2 == 0 || j % 2 == 0)	// ��������������Ϊǽ��
//////				g_GameMap[i][j] = WALL;
//////			else
//////				g_GameMap[i][j] = GROUND;
//////		}
//////	}
////
//////	// ������ɵ�ͼ(ʹ��������ȱ���)
//////	stack<POINT> stepStack;		// ����ջ
//////	vector<POINT>  stepPoint;	// ���ܵĵ�
//////	POINT nowPoint;				// ��ǰ�������ڵ�
//////	stepStack.push({ 1,1 });	// д���ʼ�� (1,1) ��Ϊ���
//////	nowPoint = { 1,1 };
//////	g_GameMap[1][1] = 0xFFFF;	// ��������
//////	while (!stepStack.empty())	// ֻҪ����ջ���վͼ���ѭ��
//////	{
//////		// �õ����ܵĵ�
//////		POINT tempPoint;
//////		for (int i = -1; i <= 1; i += 2)
//////		{
//////			tempPoint = { nowPoint.x,nowPoint.y + i * 2 };	// �����
//////															// �ж������Ƿ�Ϸ�
//////			if (tempPoint.x >= 0 && tempPoint.x <= GAME_WIDTH - 1 &&
//////				tempPoint.y >= 0 && tempPoint.y <= GAME_HEIGHT - 1 &&
//////				g_GameMap[tempPoint.y][tempPoint.x] != 0xFFFF)
//////			{
//////				stepPoint.push_back(tempPoint);
//////			}
//////			tempPoint = { nowPoint.x + i * 2 ,nowPoint.y };	// �����
//////															// �ж������Ƿ�Ϸ�
//////			if (tempPoint.x >= 0 && tempPoint.x <= GAME_WIDTH - 1 &&
//////				tempPoint.y >= 0 && tempPoint.y <= GAME_HEIGHT - 1 &&
//////				g_GameMap[tempPoint.y][tempPoint.x] != 0xFFFF)
//////			{
//////				stepPoint.push_back(tempPoint);
//////			}
//////		}
//////
//////		// ������Χ�����ѡ�����
//////		if (stepPoint.empty())				// �����Χ�㶼����������
//////		{
//////			stepStack.pop();				// ��ջ��ǰ��
//////			if (!stepStack.empty())
//////				nowPoint = stepStack.top();	// ���µ�ǰ��
//////		}
//////		else
//////		{
//////			stepStack.push(stepPoint[rand() % stepPoint.size()]);	// ��ջ��ǰ��
//////			g_GameMap[(nowPoint.y + stepStack.top().y) / 2][(nowPoint.x + stepStack.top().x) / 2] = 0;	// ��ͨǽ��
//////			nowPoint = stepStack.top();		// ���µ�ǰ��
//////			g_GameMap[nowPoint.y][nowPoint.x] = 0xFFFF;				// ��ǵ�ǰ��
//////		}
//////		stepPoint.clear();					// �����Χ���Ա���һ��ѭ��
//////	}
//////
//////	// ��ϴ��ǵ�
//////	for (int i = 0; i < GAME_HEIGHT; i++)
//////	{
//////		for (int j = 0; j < GAME_WIDTH; j++)
//////		{
//////			if (g_GameMap[i][j] == 0xFFFF)
//////				g_GameMap[i][j] = 0;
//////		}
//////	}
//////
//////	// ������ɼ���վ��λ��
//////	for (int i = 0; i < FILLNUM; i++)
//////	{
//////		POINT fillPoint = { rand() % GAME_WIDTH,rand() % GAME_HEIGHT };
//////		// ��֤�ڿյ����ɼ���վ
//////		while (g_GameMap[fillPoint.y][fillPoint.x] != GROUND)
//////			fillPoint = { rand() % GAME_WIDTH,rand() % GAME_HEIGHT };
//////		// ����͵�
//////		g_GameMap[fillPoint.y][fillPoint.x] = FILLSTATE;
//////	}
//////
//////	g_GameMap[GAME_HEIGHT - 2][GAME_WIDTH - 2] = ENDPOS;		// ����յ�
//////	g_EndPos = { GAME_WIDTH - 2,GAME_HEIGHT - 2 };				// ȷ���յ�λ��
//////	g_ViewArray = MAXVIEW;				// ��ʼ��Ұ������
//////	g_BeginTime = GetTickCount();		// ��ʼ��ʱ
//////	g_LastFillTime = GetTickCount();	// �͵Ƽ��͵�ʱ��
//////	rePaintMap();						// ���Ƶ�ͼ
//////	g_PlayerPos = { g_BlockSize * 3 / 2,g_BlockSize * 3 / 2 };	// ��ʼ���˵�λ��
//////	computeCameraPos();					// �����������λ��
//////	initgraph(WIN_WIDTH, WIN_HEIGHT);	// ��ʼ������
//////	setbkmode(TRANSPARENT);				// ���ñ���Ϊ͸��
//////	BeginBatchDraw();					// ��ʼ�������
//////}
//////
//////void endGame()
//////{
//////	EndBatchDraw();						// �����������
//////	closegraph();						// �رջ���
//////}
//////
//////void draw()
//////{
//////	// ����豸
//////	cleardevice();
//////	// ������Ұ
//////	drawView();
//////	// ������
//////	drawPlayer();
//////	// ����ʱ��
//////	TCHAR timeStr[256];
//////	int loseTime = GetTickCount() - g_BeginTime;	// ������ʧ��ʱ��
//////	_stprintf_s(timeStr, _T("��Ϸʱ��:%02d:%02d"), loseTime / 1000 / 60, loseTime / 1000 % 60);
//////	settextcolor(RGB(140, 140, 140));
//////	outtextxy((WIN_WIDTH - textwidth(timeStr)) / 2, 3, timeStr);
//////
//////	FlushBatchDraw();	// ˢ����Ļ
//////}
//////
//////bool upDate()
//////{
//////	POINT nextPos = g_PlayerPos;		// ��һ��λ��
//////
//////										// ������һ��λ��
//////	if (GetKeyState(VK_UP) & 0x8000)	nextPos.y -= 2;
//////	if (GetKeyState(VK_DOWN) & 0x8000)	nextPos.y += 2;
//////	if (GetKeyState(VK_LEFT) & 0x8000)	nextPos.x -= 2;
//////	if (GetKeyState(VK_RIGHT) & 0x8000)	nextPos.x += 2;
//////
//////	// �����һ��λ�ò��Ϸ�
//////	if (!canMove(nextPos))
//////	{
//////		if (canMove({ g_PlayerPos.x, nextPos.y }))		// y ���ƶ��Ϸ�
//////			nextPos = { g_PlayerPos.x, nextPos.y };
//////		else if (canMove({ nextPos.x, g_PlayerPos.y }))	// x ���ƶ��Ϸ�
//////			nextPos = { nextPos.x, g_PlayerPos.y };
//////		else											// �����Ϸ�
//////			nextPos = g_PlayerPos;
//////	}
//////
//////	// ������͵������ʱ��
//////	if (g_GameMap[nextPos.y / g_BlockSize][nextPos.x / g_BlockSize] == FILLSTATE)
//////		g_LastFillTime = GetTickCount();
//////	// ������յ���ͨ��
//////	else if (g_GameMap[nextPos.y / g_BlockSize][nextPos.x / g_BlockSize] == ENDPOS)
//////	{
//////		outtextxy(WIN_WIDTH / 2 - 40, WIN_HEIGHT / 2 - 12, _T("��ϲ���أ�"));
//////		FlushBatchDraw();
//////		Sleep(1000);
//////		return false;
//////	}
//////	g_PlayerPos = nextPos;						// ����λ��
//////	computeCameraPos();					    // �����������λ��
//////
//////												// ����ʱ��������Ұ
//////	static unsigned int lastTime = GetTickCount();
//////	int loseTime = GetTickCount() - g_LastFillTime;			// ������ʧ��ʱ��
//////	g_ViewArray = MAXVIEW - loseTime / 1000.0 / DARKTIME;	// ÿһ��ʱ���͵Ƶ����������½�һ��ͼ��
//////	if (g_ViewArray < MINVIEW) g_ViewArray = MINVIEW;
//////
//////	// ���������Ϣ
//////	MOUSEMSG mouseMsg;							// �����Ϣ
//////	int lastBlockSize = g_BlockSize;			// ����ԭ���Ĵ�С
//////	while (MouseHit())
//////	{
//////		mouseMsg = GetMouseMsg();
//////		if (mouseMsg.uMsg = WM_MOUSEWHEEL)		// ������Ϣ
//////		{
//////			g_BlockSize += mouseMsg.wheel / 120;
//////		}
//////	}
//////
//////	// ���û�й�����Ϣ���˳�
//////	if (lastBlockSize == g_BlockSize) return true;
//////	// ���������Ϣ
//////	if (g_BlockSize >= 10 && g_BlockSize <= 50)	// ���Сû�дﵽ����ֵ
//////	{
//////		// ��֤���ź�ĵ�ͼ����ȴ���С
//////		if (GAME_WIDTH * g_BlockSize < WIN_WIDTH ||
//////			GAME_HEIGHT * g_BlockSize < WIN_HEIGHT)
//////			g_BlockSize = lastBlockSize;
//////		rePaintMap();							// �ػ��ͼ
//////												// ���¼�������ڵ�ͼ�ϵ�λ��
//////		POINT mapPos = { g_PlayerPos.x / lastBlockSize,g_PlayerPos.y / lastBlockSize };	// �����ڵ�ͼ�ϵ�λ��
//////		g_PlayerPos.x = mapPos.x * g_BlockSize + g_BlockSize / 2;	// ����ӳ����λ��
//////		g_PlayerPos.y = mapPos.y * g_BlockSize + g_BlockSize / 2;	// ����ӳ����λ��
//////		computeCameraPos();						// ���¼��������λ��
//////	}
//////	// ��֤ͼ�鲻�����͹�С
//////	if (g_BlockSize < 10) g_BlockSize = 10;
//////	if (g_BlockSize > 50) g_BlockSize = 50;
//////
//////	return true;
//////}
//////
//////void absDelay(int delay)
//////{
//////	static int curtime = GetTickCount();
//////	static int pretime = GetTickCount();
//////	while (curtime - pretime < delay)
//////	{
//////		curtime = GetTickCount();
//////		Sleep(1);
//////	}
//////	pretime = curtime;
//////}
//////
//////bool canMove(POINT pos)
//////{
//////	// ֻҪ��Ӿ��ε��ĸ����㲻��ǽ���ھͱض��Ϸ�
//////	return	g_GameMap[(pos.y - 3) / g_BlockSize][(pos.x - 3) / g_BlockSize] != WALL &&
//////		g_GameMap[(pos.y + 3) / g_BlockSize][(pos.x + 3) / g_BlockSize] != WALL &&
//////		g_GameMap[(pos.y - 3) / g_BlockSize][(pos.x + 3) / g_BlockSize] != WALL &&
//////		g_GameMap[(pos.y + 3) / g_BlockSize][(pos.x - 3) / g_BlockSize] != WALL;
//////}
//////
//////void computeCameraPos()
//////{
//////	// ������λ��Ϊ���ļ��������������λ��
//////	g_CameraPos.x = g_PlayerPos.x - WIN_WIDTH / 2;
//////	g_CameraPos.y = g_PlayerPos.y - WIN_HEIGHT / 2;
//////
//////	// ��ֹ�����Խ��
//////	if (g_CameraPos.x < 0)										g_CameraPos.x = 0;
//////	if (g_CameraPos.y < 0)										g_CameraPos.y = 0;
//////	if (g_CameraPos.x > GAME_WIDTH * g_BlockSize - WIN_WIDTH)	g_CameraPos.x = GAME_WIDTH * g_BlockSize - WIN_WIDTH;
//////	if (g_CameraPos.y > GAME_HEIGHT * g_BlockSize - WIN_HEIGHT)	g_CameraPos.y = GAME_HEIGHT * g_BlockSize - WIN_HEIGHT;
//////}
//////
//////void rePaintMap()
//////{
//////	g_MapImage.Resize(GAME_WIDTH * g_BlockSize, GAME_HEIGHT * g_BlockSize);	// ���õ�ͼͼƬ��С
//////	SetWorkingImage(&g_MapImage);								// ���õ�ͼͼƬΪ��ǰ����ͼƬ
//////	for (int i = 0; i < GAME_HEIGHT; i++)
//////	{
//////		for (int j = 0; j < GAME_WIDTH; j++)
//////		{
//////			switch (g_GameMap[i][j])
//////			{
//////			case WALL:
//////				drawWall({ j * g_BlockSize,i * g_BlockSize });		// ����ǽ��
//////				break;
//////			case FILLSTATE:
//////				drawFillState({ j * g_BlockSize,i * g_BlockSize });	// ���Ƽ���վ
//////				break;
//////			case GROUND:
//////				drawGround({ j * g_BlockSize,i * g_BlockSize });	// ���Ƶ���
//////				break;
//////			case ENDPOS:
//////				drawEndPos({ j * g_BlockSize,i * g_BlockSize });
//////				break;
//////			}
//////		}
//////	}
//////	SetWorkingImage();	// ��λ����ͼƬ
//////}
//////
//////void drawWall(POINT pos)
//////{
//////	setfillcolor(RGB(254, 109, 19));
//////	solidrectangle(pos.x, pos.y, pos.x + g_BlockSize, pos.y + g_BlockSize);
//////}
//////
//////void drawGround(POINT pos)
//////{
//////	setfillcolor(RGB(255, 255, 255));
//////	solidrectangle(pos.x, pos.y, pos.x + g_BlockSize, pos.y + g_BlockSize);
//////}
//////
//////void drawFillState(POINT pos)
//////{
//////	drawGround(pos);
//////
//////	// ����Բ�Ǿ���
//////	pos.x += g_BlockSize / 5;
//////	pos.y += g_BlockSize / 5;
//////	setfillcolor(RGB(252, 213, 11));
//////	solidroundrect(pos.x, pos.y, pos.x + g_BlockSize / 5 * 3, pos.y + g_BlockSize / 5 * 3, g_BlockSize / 8, g_BlockSize / 8);
//////}
//////
//////void drawEndPos(POINT pos)
//////{
//////	drawGround(pos);
//////
//////	// ����Բ�Ǿ���
//////	pos.x += g_BlockSize / 5;
//////	pos.y += g_BlockSize / 5;
//////	setfillcolor(RGB(87, 116, 48));
//////	solidroundrect(pos.x, pos.y, pos.x + g_BlockSize / 5 * 3, pos.y + g_BlockSize / 5 * 3, g_BlockSize / 8, g_BlockSize / 8);
//////}
//////
//////void drawPlayer()
//////{
//////	setfillcolor(RGB(252, 213, 11));
//////	solidcircle(g_PlayerPos.x - g_CameraPos.x, g_PlayerPos.y - g_CameraPos.y, 3);
//////}
//////
//////void drawView()
//////{
//////	// ������Ұ
//////	HRGN viewArr;
//////	int r = int(g_BlockSize * g_ViewArray + 0.5);	// ������Ұ�뾶
//////	POINT orgin = g_PlayerPos;
//////	orgin.x -= g_CameraPos.x;						// ��������Ļ�ϵ�λ��
//////	orgin.y -= g_CameraPos.y;						// ��������Ļ�ϵ�λ��
//////	viewArr = CreateEllipticRgn(orgin.x - r, orgin.y - r, orgin.x + r, orgin.y + r);	// ����һ��Բ�ε�����
//////	setcliprgn(viewArr);							// ��������
//////
//////													// ���Ƶ�ͼ
//////	putimage(0, 0, WIN_WIDTH, WIN_HEIGHT, &g_MapImage, g_CameraPos.x, g_CameraPos.y);
//////
//////	// ɾ������
//////	DeleteObject(viewArr);
//////	// ��������
//////	setcliprgn(NULL);
//////}



//////̰����
////////�����̫�У�����˫����Ϸ�뷨����
//////#include<stdio.h>
//////#include<time.h>
//////#include<conio.h>
//////#include<stdlib.h>
//////#include<windows.h>
//////
//////char qipan[20][80];
//////int snake = 1;
//////
//////int change(int* head, int* tail, int* score, char* direction, int zuobiao[2][80])
//////{
//////    int x, y;
//////    switch (*direction)
//////    {
//////    case 72:
//////        x = zuobiao[0][*head] - 1;
//////        y = zuobiao[1][*head];
//////        break;
//////    case 87:
//////        x = zuobiao[0][*head] - 1;
//////        y = zuobiao[1][*head];
//////        break;
//////    case 80:
//////        x = zuobiao[0][*head] + 1;
//////        y = zuobiao[1][*head];
//////        break;
//////    case 83:
//////        x = zuobiao[0][*head] + 1;
//////        y = zuobiao[1][*head];
//////        break;
//////    case 75:
//////        x = zuobiao[0][*head];
//////        y = zuobiao[1][*head] - 1;
//////        break;
//////    case 65:
//////        x = zuobiao[0][*head];
//////        y = zuobiao[1][*head] - 1;
//////        break;
//////    case 68:
//////        x = zuobiao[0][*head];
//////        y = zuobiao[1][*head] + 1;
//////        break;
//////    default:
//////        x = zuobiao[0][*head];
//////        y = zuobiao[1][*head] + 1;
//////    }
//////    if (qipan[x][y] == '_' || qipan[x][y] == '|' || qipan[x][y] == '*')
//////        return 1;
//////    if (qipan[x][y] == ' ')
//////    {
//////        qipan[zuobiao[0][*tail]][zuobiao[1][*tail]] = ' ';
//////        *tail = (*tail + 1) % 80;
//////        qipan[zuobiao[0][*head]][zuobiao[1][*head]] = '*';
//////        *head = (*head + 1) % 80;
//////        zuobiao[0][*head] = x;
//////        zuobiao[1][*head] = y;
//////        qipan[x][y] = '#';
//////        return 0;
//////    }
//////    if (qipan[x][y] == '@')
//////    {
//////        qipan[zuobiao[0][*head]][zuobiao[1][*head]] = '*';
//////        *head = (*head + 1) % 80;
//////        zuobiao[0][*head] = x;
//////        zuobiao[1][*head] = y;
//////        qipan[x][y] = '#';
//////        *score += 1;
//////        return 0;
//////    }
//////}
//////void gotoxy(int x, int y)//λ�ú���
//////{
//////    COORD pos;
//////
//////    pos.X = x;
//////
//////    pos.Y = y;
//////
//////    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
//////}
//////void color(int a)//��ɫ����
//////{
//////
//////    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), a);
//////
//////}
//////void show_start()
//////{
//////
//////    gotoxy(20, 0);
//////    color(1);
//////    int u;
//////    for (u = 0; u < 18; u++)
//////        printf("* ");
//////    gotoxy(20, 12);
//////    for (u = 0; u < 18; u++)
//////        printf("* ");
//////    gotoxy(28, 2);
//////    color(13);
//////    printf("S N A K E  G A M E");
//////    gotoxy(31, 5);
//////    color(14);
//////    printf("#");
//////    gotoxy(34, 5);
//////    color(11);
//////    printf("One  snake");
//////    gotoxy(34, 7);
//////    printf("Two  snakes");
//////    gotoxy(28, 9);
//////    printf("The speed you want: ");
//////
//////    gotoxy(31, 5);
//////    char temp = 'a';
//////    color(14);
//////    while (1)
//////    {
//////        while (!_kbhit());
//////        temp = _getch();
//////        if (temp == 72 || temp == 80)
//////        {
//////            gotoxy(31, 5 + 2 * (snake - 1));
//////            printf(" ");
//////            snake = snake % 2 + 1;
//////            gotoxy(31, 5 + 2 * (snake - 1));
//////            printf("#");
//////            gotoxy(31, 5 + 2 * (snake - 1));
//////        }
//////        if (temp == 13)
//////            break;
//////    }
//////
//////    gotoxy(27, 10);
//////    color(10);
//////    printf("GOOD  LUCK  TO  YOU  !");
//////}
//////
//////int main()
//////{
//////    srand(time(0));
//////
//////    int head1 = 3, tail1 = 0, score1 = 0;
//////    int head2 = 3, tail2 = 0, score2 = 0;
//////    int zuobiao1[2][80];
//////    int zuobiao2[2][80];
//////
//////    /*���� 20��80 ��ʼ��*/
//////    for (int i = 0; i < 20; i++)
//////    {
//////        for (int j = 0; j < 80; j++)
//////        {
//////            qipan[i][j] = ' ';
//////        }
//////    }
//////    for (int i = 0; i < 20; i++)
//////    {
//////        qipan[i][0] = qipan[i][79] = '|';//��һ�С����һ����ǽ20*1
//////    }
//////    for (int i = 0; i < 80; i++)
//////    {
//////        qipan[0][i] = qipan[19][i] = '_';//��һ�С����һ����ǽ1*80
//////    }
//////
//////    /*�ߵ����� 2��8 ��ʼ��, ���߷ŵ�������*/
//////    int x1 = 1, x2 = 18, y, temp = 0;
//////
//////    for (int m = tail1; m < head1; m++)
//////    {
//////        zuobiao1[0][m] = x1;//��ʼ�к�
//////        y = zuobiao1[1][m] = ++temp;//��ʼ�к�
//////        qipan[x1][y] = '*';
//////    }
//////    zuobiao1[0][head1] = x1;//��ʼ�к�
//////    y = zuobiao1[1][head1] = ++temp;//��ʼ�к�
//////    qipan[x1][y] = '#';//��ͷ
//////
//////    show_start();
//////
//////    if (snake == 2)
//////    {
//////        temp = 0;
//////        for (int m = tail2; m < head2; m++)
//////        {
//////            zuobiao2[0][m] = x2;//��ʼ�к�
//////            y = zuobiao2[1][m] = ++temp;//��ʼ�к�
//////            qipan[x2][y] = '*';
//////        }
//////        zuobiao2[0][head2] = x2;//��ʼ�к�
//////        y = zuobiao2[1][head2] = ++temp;//��ʼ�к�
//////        qipan[x2][y] = '#';//��ͷ
//////    }
//////
//////    clock_t start;
//////    int timeover;
//////    char direction1 = 77;//72 88 75 77
//////    char direction2 = 68;//87 83 65 68
//////    char new_direction;
//////    char new_direction1;
//////    char new_direction2;
//////
//////    int gamespeed;
//////    gotoxy(48, 9);
//////    color(14);
//////    scanf_s("%d", &gamespeed);
//////    int rand_i = rand() % 18 + 1;
//////    int rand_j = rand() % 78 + 1;
//////    qipan[rand_i][rand_j] = '@';
//////
//////    system("cls");
//////    gotoxy(10, 1);
//////    color(10);
//////    printf("Your present score: ");
//////    gotoxy(30, 1);
//////    color(11);
//////    printf("%d", score1);
//////    gotoxy(0, 4);
//////    for (int i = 0; i < 20; i++)//��ӡ������
//////        for (int j = 0; j < 80; j++)
//////        {
//////            if (qipan[i][j] == '*' || qipan[i][j] == '#')
//////                color(13);
//////            else if (qipan[i][j] == '@')
//////                color(12);
//////            else
//////                color(15);
//////            printf("%c", qipan[i][j]);
//////        }
//////    while (1)//87 83 65 68
//////    {
//////        for (int i = 0; i < 20; i++)//��ӡ������
//////            for (int j = 0; j < 80; j++)
//////            {
//////                if (qipan[i][j] == '*' || qipan[i][j] == '#')
//////                {
//////                    gotoxy(j, i + 4);
//////                    color(13);
//////                }
//////                if (qipan[i][j] == '@')
//////                {
//////                    gotoxy(j, i + 4);
//////                    color(12);
//////                }
//////                if (qipan[i][j] == '_' || qipan[i][j] == '|')
//////                {
//////                    gotoxy(j, i + 4);
//////                    color(15);
//////                }
//////                printf("%c", qipan[i][j]);
//////            }
//////        for (int q = 0; q < 3; q++)
//////        {
//////            gotoxy(rand() % 78 + 1, rand() % 18 + 5);
//////            color(14);
//////            printf("+");
//////        }
//////        start = clock();
//////        timeover = 1;
//////        while (!_kbhit() && (timeover = clock() - start / CLOCKS_PER_SEC <= gamespeed));
//////        if (timeover)//�а���
//////        {
//////            if (snake == 1)
//////                _getch();
//////            new_direction = _getch();
//////            if (snake == 2)
//////            {
//////                if (new_direction == 87 || new_direction == 83 || new_direction == 65 || new_direction == 68)
//////                {
//////                    new_direction2 = new_direction;
//////                    new_direction1 = direction1;
//////                    if (new_direction2 + direction2 == 170 || new_direction2 + direction2 == 133)
//////                    {
//////                        change(&head1, &tail1, &score1, &direction1, zuobiao1);
//////                        change(&head2, &tail2, &score2, &direction2, zuobiao2);
//////                        continue;
//////                    }
//////                }
//////                if (new_direction == 72 || new_direction == 80 || new_direction == 75 || new_direction == 77)
//////                {
//////                    new_direction1 = new_direction;
//////                    new_direction2 = direction2;
//////                    if (new_direction1 + direction1 == 152)
//////                    {
//////                        change(&head1, &tail1, &score1, &direction1, zuobiao1);
//////                        change(&head2, &tail2, &score2, &direction2, zuobiao2);
//////                        continue;
//////                    }
//////                }
//////            }
//////            if (snake == 1 && (new_direction == 72 || new_direction == 80 || new_direction == 75 || new_direction == 77))
//////            {
//////                new_direction1 = new_direction;
//////                if (new_direction1 + direction1 == 152)
//////                {
//////                    change(&head1, &tail1, &score1, &direction1, zuobiao1);
//////                    continue;
//////                }
//////            }
//////        }
//////        else
//////        {
//////            if (snake == 2)
//////            {
//////                new_direction2 = direction2;
//////                new_direction1 = direction1;
//////            }
//////            else
//////            {
//////                new_direction1 = direction1;
//////            }
//////        }
//////        if (snake == 1)
//////        {
//////            direction1 = new_direction1;
//////            if (change(&head1, &tail1, &score1, &direction1, zuobiao1) == 1)
//////            {
//////                system("cls");
//////                gotoxy(30, 10);
//////                color(7);
//////                printf("G A M E  O V E R !");
//////                gotoxy(0, 20);
//////                color(1);
//////                return 0;
//////            }
//////        }
//////        if (snake == 2)
//////        {
//////            direction1 = new_direction1;
//////            if (change(&head1, &tail1, &score1, &direction1, zuobiao1) == 1)
//////            {
//////                system("cls");
//////                gotoxy(30, 8);
//////                color(7);
//////                printf("G A M E  O V E R !");
//////                gotoxy(30, 10);
//////                printf("Snake Two is the Hero!");
//////                gotoxy(0, 20);
//////                color(1);
//////                return 0;
//////            }
//////
//////            direction2 = new_direction2;
//////            if (change(&head2, &tail2, &score2, &direction2, zuobiao2) == 1)
//////            {
//////                system("cls");
//////                gotoxy(30, 8);
//////                color(7);
//////                printf("G A M E  O V E R !");
//////                gotoxy(30, 10);
//////                printf("Snake One is the Hero!");
//////                gotoxy(0, 20);
//////                color(1);
//////                return 0;
//////            }
//////
//////        }
//////
//////        int randnew = 0;
//////        for (int i = 0; i < 20; i++)//��ӡ������
//////            for (int j = 0; j < 80; j++)
//////                if (qipan[i][j] == '@')
//////                {
//////                    randnew++;
//////                }
//////        if (randnew == 0)
//////        {
//////            rand_i = rand() % 18 + 1;
//////            rand_j = rand() % 78 + 1;
//////            qipan[rand_i][rand_j] = '@';
//////        }
//////        if (snake == 2 && randnew == 1)
//////        {
//////            rand_i = rand() % 18 + 1;
//////            rand_j = rand() % 78 + 1;
//////            qipan[rand_i][rand_j] = '@';
//////        }
//////
//////        gotoxy(30, 1);
//////        printf("%d", score1);
//////        if (snake == 2)
//////        {
//////            gotoxy(30, 2);
//////            printf("%d", score2);
//////        }
//////    }
//////}


////////#include<stdio.h>
////////#include<easyx.h>
////////#include<conio.h>
////////
////////#include<time.h>
////////#define ROW 46
////////#define COL 64
//////////ö��
////////enum game
////////{
////////	SPACE, WALL, SNAKE, FOOD, HEAD//�յ�  ǽ  ��  ʳ��
////////};
/////////************ȫ�ֱ���************/
////////int mode = 0;			//��Ϸģʽ
////////int score = 0;			//����
////////DWORD t1, t2;			//��������ʱ������ƶ��ٶ�
////////int map[ROW][COL];		//��ͼ��С
////////COORD snake[1024];		//��			typedef struct _COORD {SHORT X;SHORT Y;} COORD, *PCOORD;
////////size_t SnakeSize;		//�ߵĳ߶�		typedef unsigned int     size_t;
////////char SnakeDir;			//���ƶ�����
/////////************ȫ�ֺ���************/
////////void start();	//��ʼ����
////////void chose();	//ѡ��ģʽ  0:��ͨģʽ  1����ǽģʽ  2���޵�ģʽ
////////void DrawMap();	//��ͼ
////////void init();	//��ʼ����Ϸ����
////////void addfood();	//���ʳ��
////////void ChangeDir();	//�޸��ߵķ���
////////void move();//�ߵ��ƶ�
////////int main()
////////{
////////	initgraph(640, 480);
////////	start();
////////	outtextxy(260, 150, "->");		//��ʼĬ��ģʽһ
////////	chose();
////////	init();
////////	while (1)
////////	{
////////		t2 = GetTickCount();
////////		DrawMap();
////////		if (kbhit())
////////		{
////////			ChangeDir();
////////			move();
////////
////////			t2 = GetTickCount();
////////			t1 = t2;
////////		}
////////		if (t2 - t1 > 50)
////////		{
////////			move();
////////			t1 = t2;
////////		}
////////	}
////////	getchar();
////////	closegraph();
////////	return 0;
////////}
////////void init()
////////{
////////	srand((unsigned)time(NULL));	//�������
////////	setbkcolor(WHITE);				//���ñ�����ɫ
////////
////////	memset(map, SPACE, sizeof(map));//��ʼ��map����Ϊ0��SPACE
////////	//ÿһ�е� ��һ�� �� ���һ�� ��ǽ
////////	for (int i = 0; i < ROW; i++)
////////	{
////////		map[i][0] = map[i][COL - 1] = WALL;
////////	}
////////	//ÿһ�е� �ڶ��� �� �����ڶ� ����ǽ
////////	for (int j = 1; j < COL - 1; j++)
////////	{
////////		map[0][j] = map[ROW - 1][j] = WALL;
////////	}
////////	//������ͷ���ߵ�����
////////	map[3][5] = HEAD;
////////	map[3][4] = map[3][3] = SNAKE;
////////	//��ʼ����
////////	SnakeSize = 3;	//�� ��
////////	SnakeDir = 'D';	//�߷�������
////////	snake[0].X = 3;
////////	snake[0].Y = 5;
////////	snake[1].X = 3;
////////	snake[1].Y = 4;
////////	snake[2].X = 3;
////////	snake[2].Y = 3;
////////	addfood();
////////}
////////void start()
////////{
////////	setbkcolor(WHITE);		//���ô��ڱ���ɫΪ��ɫ
////////	cleardevice();			//ˢ����Ļ
////////
////////	setbkmode(TRANSPARENT);	//�������屳��ɫΪ͸��
////////	settextcolor(BLACK);		//����������ɫΪ��ɫ
////////	/*****************��Ϸ����*****************/
////////	outtextxy(290, 80, "����ѡ��:");
////////	outtextxy(280, 150, "1.��ͨģʽ");
////////	outtextxy(280, 200, "2.��ǽģʽ");
////////	outtextxy(280, 250, "3.�޵�ģʽ");
////////	outtextxy(200, 280, "���ּ� 1,2,3 ѡ��ģʽ��Enter��������Ϸ");
////////	outtextxy(200, 300, "��ĸ�� W,S,A,D ����� �������� ���Ʒ���");
////////	outtextxy(130, 350, "������ݣ�");
////////	outtextxy(160, 380, "��ע΢�Ź��ں�: ���ѧϰ���� ��ȡԴ��");
////////	outtextxy(160, 410, "���ѧϰ��Ⱥ:  879098023");
////////}
////////void chose()
////////{
////////	while (1)
////////	{
////////		switch (getch())
////////		{
////////		case '1':
////////			start();
////////			outtextxy(260, 150, "->");
////////			mode = 0;
////////			break;
////////		case '2':
////////			start();
////////			outtextxy(260, 200, "->");
////////			mode = 1;
////////			break;
////////		case '3':
////////			start();
////////			outtextxy(260, 250, "->");
////////			mode = 2;
////////			break;
////////		case 13:
////////			return;
////////			break;
////////		}
////////	}
////////}
////////void DrawMap()
////////{
////////	BeginBatchDraw();	//��ʼ��ͼ
////////	setbkcolor(WHITE);	//���ñ�����ɫΪ��ɫ
////////	settextcolor(RGB(238,0,0));
////////	cleardevice();		//����
////////	char arr[10];		//����ɼ�
////////	sprintf(arr, "�ܷ֣�%d", score);	//���ɼ���ʽ��������ַ���arr�� 
////////	outtextxy(0, 0, arr);				//��ʾ�ɼ�
////////	for (int y = 0; y < ROW; y++)		//y�᷽������
////////	{
////////		for (int x = 0; x < COL; x++)	//x�᷽������
////////		{
////////			switch (map[y][x])
////////			{
////////			case SPACE:
////////				break;
////////			case WALL:
////////				setlinecolor(BLACK);	
////////				setfillcolor(RGB(238, 233, 233));	//��ɫ
////////				fillrectangle(x * 10, y * 10 + 20, x * 10 + 10, y * 10 + 30);
////////				break;
////////			case SNAKE:
////////				setlinecolor(RGB(0, 245, 255));		//��ɫ 
////////				setfillcolor(WHITE);
////////				fillrectangle(x * 10, y * 10 + 20, x * 10 + 10, y * 10 + 30);
////////				break;
////////			case HEAD:
////////				//���߲���ͷ
////////				switch (rand() % 7)
////////				{
////////				case 0:
////////					setfillcolor(RGB(255, 0, 0));		//��ɫ 255 0 0
////////					solidrectangle(x * 10, y * 10 + 20, x * 10 + 10, y * 10 + 30);
////////					break;
////////				case 1:
////////					setfillcolor(RGB(255, 165, 0));		//��  255 165 0 
////////					solidrectangle(x * 10, y * 10 + 20, x * 10 + 10, y * 10 + 30);
////////					break;
////////				case 2:
////////					setfillcolor(RGB(255, 255, 0));		//��  255 255 0
////////					solidrectangle(x * 10, y * 10 + 20, x * 10 + 10, y * 10 + 30);
////////					break;
////////				case 3:
////////					setfillcolor(RGB(0, 255, 0));		//��ɫ  0, 255, 0
////////					solidrectangle(x * 10, y * 10 + 20, x * 10 + 10, y * 10 + 30);
////////					break;
////////				case 4:
////////					setfillcolor(RGB(0, 255, 255));		//��  0 255 255
////////					solidrectangle(x * 10, y * 10 + 20, x * 10 + 10, y * 10 + 30);
////////					break;
////////				case 5:
////////					setfillcolor(RGB(0, 0, 255));		//��  0 0 255
////////					solidrectangle(x * 10, y * 10 + 20, x * 10 + 10, y * 10 + 30);
////////					break;
////////				case 6:
////////					setfillcolor(RGB(160, 32, 240));	//��  160 32 240
////////					solidrectangle(x * 10, y * 10 + 20, x * 10 + 10, y * 10 + 30);
////////					break;
////////				default:
////////					break;
////////				}
////////				break;
////////			case FOOD:
////////				setfillcolor(RGB(255, 0, 0));			//��ɫ
////////				solidrectangle(x * 10, y * 10 + 20, x * 10 + 10, y * 10 + 30);
////////				break;
////////			default:
////////				break;
////////			}
////////		}
////////	}
////////	EndBatchDraw();
////////}
////////void addfood()
////////{
////////	int row, col;
////////	do
////////	{	
////////		row = rand() % (ROW - 1) + 1;
////////		col = rand() % (COL - 1) + 1;
////////	} while (map[row][col] != SPACE);
////////	map[row][col] = FOOD;
////////}
////////void ChangeDir()
////////{
////////	switch (getch())
////////	{
////////	case'A':
////////	case'a':
////////	case 75:
////////		if (SnakeDir != 'D') SnakeDir = 'A';	//�߲��ܺ���
////////		break;
////////	case'D':
////////	case'd':
////////	case 77:
////////		if (SnakeDir != 'A') SnakeDir = 'D';
////////		break;
////////	case'W':
////////	case'w':
////////	case 72:
////////		if (SnakeDir != 'S') SnakeDir = 'W';
////////		break;
////////	case'S':
////////	case's':
////////	case 80:
////////		if (SnakeDir != 'W') SnakeDir = 'S';
////////		break;
////////	case 32:
////////		getch();
////////		break;
////////	default:
////////		break;
////////	}
////////}
////////void move()
////////{
////////	COORD next;		//��ͷ����һ��λ��
////////	int i;
////////	switch (SnakeDir)
////////	{
////////	case'A':
////////		next.X = snake[0].X;
////////		next.Y = snake[0].Y - 1;
////////		break;
////////	case'W':
////////		next.X = snake[0].X - 1;
////////		next.Y = snake[0].Y;
////////		break;
////////	case'D':
////////		next.X = snake[0].X;
////////		next.Y = snake[0].Y + 1;
////////		break;
////////	case'S':
////////		next.X = snake[0].X + 1;
////////		next.Y = snake[0].Y;
////////		break;
////////	default:
////////		break;
////////	}
////////
////////	switch (map[next.X][next.Y])
////////	{
////////	case SPACE://ֱ���ƶ�
////////		map[snake[SnakeSize - 1].X][snake[SnakeSize - 1].Y] = SPACE;//��ͼ��β���ڵ��ÿ�
////////		for (i = SnakeSize - 1; i > 0; i--)						//��β����ͷ�����ƶ�һλ
////////		{
////////			snake[i] = snake[i - 1];
////////		}
////////		map[snake[0].X][snake[0].Y] = SNAKE;						//��ͷ�� ��
////////		snake[0] = next;											//����һ��λ�ø�ֵ����ͷ
////////		map[snake[0].X][snake[0].Y] = HEAD;							//����ͷ
////////		break;
////////	case WALL:
////////		if (mode)		//ģʽ1ģʽ2�ɴ�ǽ
////////		{
////////			map[snake[SnakeSize - 1].X][snake[SnakeSize - 1].Y] = SPACE;//��β�ÿ�
////////			for (i = SnakeSize - 1; i > 0; i--)						//��β����ͷ�����ƶ�һλ
////////			{
////////				snake[i] = snake[i - 1];
////////			}
////////			map[snake[0].X][snake[0].Y] = SNAKE;						//��ͷ�� ��
////////			switch (SnakeDir)											//��ǽ
////////			{
////////			case'A':next.Y = COL - 2; break;
////////			case 'D':next.Y = 1; break;
////////			case 'W': next.X = ROW - 2; break;
////////			case 'S':next.X = 1; break;
////////			default:
////////				break;
////////			}
////////			snake[0] = next;											//��ͷ�ƶ�����λ��
////////			map[snake[0].X][snake[0].Y] = HEAD;		//�µ���ͷ���ڵ�λ��
////////		}
////////		else {
////////			MessageBox(GetHWnd(), "��Ϸ����", "SORRY", MB_OK);
////////			exit(0);
////////		}
////////		break;
////////	case SNAKE:
////////		if (mode == 2)		//ģʽ���޵�
////////		{
////////			break;
////////		}
////////		else {
////////			MessageBox(GetHWnd(), "��Ϸ����", "SORRY", MB_OK);
////////			exit(0);
////////		}
////////		break;
////////	case FOOD://ʳ��				��β����
////////		for (i = SnakeSize; i > 0; i--)							//��β����ͷ�����ƶ�һλ
////////		{
////////			snake[i] = snake[i - 1];								
////////		}
////////		map[snake[0].X][snake[0].Y] = SNAKE;						//��ͷ �� ��
////////		snake[0] = next;											//����һ��λ�ø�ֵ����ͷ
////////		score++;			//������һ				
////////		(SnakeSize)++;		//�߳߶ȼ�һ
////////		map[snake[0].X][snake[0].Y] = HEAD;							//��ͼ��������ͷ
////////		addfood();
////////		break;
////////	default:break;
////////	}
////////}
