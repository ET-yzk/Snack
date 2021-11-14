//// 程序名称：贪吃蛇AI
//// 编译环境：Visual Studio 2017，EasyX_2019测试版
//// 作　　者：柯西丶不是你 <591716377@qq.com>
//// 创建时间：2019-2-23
//// 最后修改：2019-3-8
//// 说明：使用Debug产生卡顿可以换Release。
////
//// 待改进产生食物算法，后期弃用最短距离，
//// 假设食物在右下角或许可以接近想要的效果,待解决回环问题即有多个解
//// 优化算法速度
////
//#include <iostream>
//#include <conio.h>
//#include <ctime>
//#include <list>
//#include <queue>
//#include <set>
//#include <graphics.h>
//using namespace std;
//// 窗口参数
//const int WINDOW_WIDTH = 640;	// 窗口宽度
//const int WINDOW_HEIGHT = 480;	// 窗口高度
//
//// 游戏参数
//const int MAP_ROWNUM = 20;		// 地图行数
//const int MAP_COLNUM = 20;		// 地图列数
//const int GRIDGAP = 5;			// 格子间隙
//const int GRID = WINDOW_HEIGHT / MAP_COLNUM;	// 大格子宽度
//const int _GRID = GRID - 2 * GRIDGAP;			// 小格子宽度
//const int SPEED = 50;			// 蛇初始速度
//const int ACC = 20;				// 蛇加速度（其实是速度增量）
//
//// 游戏数据结构
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
//// 各类实现
//class Food {
//public:
//	Coor coor;			// 食物坐标
//	bool EXISTFOOD;		// 存在食物
//	Food() { EXISTFOOD = true; }
//	~Food() { EXISTFOOD = false; }
//	// 产生(0,0)~(limx,limy)的坐标
//	void RandCoor(int limx, int limy) {
//		coor.x = rand() % limx;
//		coor.y = rand() % limy;
//	}
//};
//
//class Snake {
//public:
//	int length;			// 蛇长度
//	int speed;			// 蛇速度
//	int acc;			// 加速度
//	list<Coor> coor;	// 蛇身坐标
//	Direct direct;		// 蛇当前方向
//	Snake() {}
//	~Snake() {}
//	// 蛇移动
//	void Move() {
//		Coor head = coor.front();
//		switch (direct) {
//		case UP:	head.y--;	break;
//		case DOWN:	head.y++;	break;
//		case LEFT:	head.x--;	break;
//		case RIGHT:	head.x++;	break;
//		}
//		coor.pop_back();		// 尾巴出列
//		coor.push_front(head);	// 新头入列
//	}
//	// 蛇转向
//	void TurnDirect(char cmd = 0x00) {
//		// 使用while而不是if
//		if (cmd == 0x00) {
//			while (_kbhit()) {
//				cmd = _getch();
//			}
//		}
//		// 两次方向相同设置加速度
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
//	// 游戏初始化
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
//	// 画地图
//	void DrawMap() {
//		setfillcolor(DARKGRAY);
//		solidrectangle(0, 0, GRID * MAP_COLNUM, GRID * MAP_ROWNUM);
//		setcolor(LIGHTGRAY);
//		line(WINDOW_HEIGHT, 0, WINDOW_HEIGHT, WINDOW_HEIGHT);
//		// 画食物
//		setfillcolor(RED);
//		fillrectangle(food.coor.x * GRID + GRIDGAP, food.coor.y * GRID + GRIDGAP,
//			(food.coor.x + 1) * GRID - GRIDGAP, (food.coor.y + 1) * GRID - GRIDGAP);
//		// 画蛇
//		setfillcolor(WHITE);
//		Coor temp = snake.coor.front();
//		for (auto iter : snake.coor) {
//			solidrectangle(iter.x * GRID + GRIDGAP, iter.y * GRID + GRIDGAP,
//				(iter.x + 1) * GRID - GRIDGAP, (iter.y + 1) * GRID - GRIDGAP);
//			// 画缝隙
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
//	// 处理吃食物
//	void EatFood() {
//		Coor head = snake.coor.front();
//		if (head == food.coor) {
//			food.EXISTFOOD = false;
//			snake.coor.push_back(snake.coor.back());
//			snake.length++;
//		}
//	}
//	// 产生食物
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
//	// 判断游戏结束
//	bool GameOver() {
//		Coor head = snake.coor.front();
//		if (!inBorder(head) || onSnake_ExceptHead(head) || EatFullScreen()) {
//			return true;
//		}
//		return false;
//	}
//	// 是否吃满食物
//	bool EatFullScreen() {
//		return snake.length == MAP_COLNUM * MAP_ROWNUM;
//	}
//	// 游戏结束画面
//	void ShowGameEnd() {
//		setfillcolor(BLACK);
//		/*fillrectangle(0, WINDOW_HEIGHT / 4, WINDOW_HEIGHT, WINDOW_HEIGHT / 4 * 3);*/
//		// 在屏幕中央输出字符串
//		TCHAR* str_end = (TCHAR*)("GAME OVER!");
//		if (EatFullScreen())
//			str_end = (TCHAR*)("YOU WIN!");
//		// x64会报警告：“size_t”转换到“int”，可能丢失数据
//		int Tstrlen = (int)_tcslen(str_end);
//		outtextxy(WINDOW_HEIGHT / 2 - Tstrlen * 20 / 4, WINDOW_HEIGHT / 2 - 20 / 4, str_end);
//	}
//	// 绘制游戏相关信息
//	void ShowGameInfo() {
//		// 填充黑色底
//		setfillcolor(BLACK);
//		solidrectangle(WINDOW_HEIGHT, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
//		// 尺寸信息
//		TCHAR str_mapsize[20];
//		swprintf_s(str_mapsize, _T("MAPSIZE:  %d×%d"), MAP_COLNUM, MAP_ROWNUM);
//		settextcolor(WHITE);
//		outtextxy(WINDOW_HEIGHT + 20, 20, str_mapsize);
//		// AI状态信息
//		TCHAR* str_ai = (TCHAR*)("AI:  OFF");
//		if (isAI == true)	str_ai = (TCHAR*)("AI:  ON");
//		outtextxy(WINDOW_HEIGHT + 20, 50, str_ai);
//		// 速度信息
//		TCHAR str_speed[20];
//		swprintf_s(str_speed, _T("SPEED:  %d"), snake.speed + snake.acc);
//		outtextxy(WINDOW_HEIGHT + 20, 80, str_speed);
//		// 加速度信息
//		TCHAR str_acc[20];
//		swprintf_s(str_acc, _T("ACC:  %d"), snake.acc);
//		outtextxy(WINDOW_HEIGHT + 20, 110, str_acc);
//		// 蛇长度信息
//		TCHAR str_life[20];
//		swprintf_s(str_life, _T("LIFE:  %d/%d"), snake.length, MAP_COLNUM * MAP_ROWNUM);
//		outtextxy(WINDOW_HEIGHT + 20, 140, str_life);
//		// 保存结点,使用引用是为了处理尾巴设置为可走结点
//		const Coor& snakeHead = snake.coor.front();
//		const Coor& snakeTail = snake.coor.back();
//		// 测试
//		TCHAR str_test[20];
//		swprintf_s(str_test, _T("找尾巴步数:  %d"), canFindPath(snakeHead, snakeTail));
//		outtextxy(WINDOW_HEIGHT + 20, 170, str_test);
//		// 食物坐标信息
//		TCHAR str_food[20];
//		swprintf_s(str_food, _T("食物坐标:  (%d,%d)"), food.coor.x, food.coor.y);
//		outtextxy(WINDOW_HEIGHT + 20, 200, str_food);
//		// 蛇头坐标信息
//		TCHAR str_head[20];
//		swprintf_s(str_head, _T("蛇头坐标:  (%d,%d)"), snakeHead.x, snakeHead.y);
//		outtextxy(WINDOW_HEIGHT + 20, 230, str_head);
//		// 蛇尾坐标信息
//		TCHAR str_tail[20];
//		swprintf_s(str_tail, _T("蛇尾坐标:  (%d,%d)"), snakeTail.x, snakeTail.y);
//		outtextxy(WINDOW_HEIGHT + 20, 260, str_tail);
//		// 方向信息
//		TCHAR* str_dir;
//		switch (snake.direct) {
//		case RIGHT:	str_dir = (TCHAR*)("方向:  RIGHT");	break;
//		case DOWN:	str_dir = (TCHAR*)("方向:  DOWN");		break;
//		case LEFT:	str_dir = (TCHAR*)("方向:  LEFT"); 	break;
//		case UP:	str_dir = (TCHAR*)("方向:  UP");		break;
//		default:	str_dir = (TCHAR*)("方向:  None");
//		}
//		outtextxy(WINDOW_HEIGHT + 20, 290, str_dir);
//		// 游戏操作说明
//		outtextxy(WINDOW_HEIGHT + 20, 320, _T("操作说明:"));
//		outtextxy(WINDOW_HEIGHT + 20, 340, _T("使用方向键控制"));
//		outtextxy(WINDOW_HEIGHT + 20, 360, _T("长按方向键加速"));
//		outtextxy(WINDOW_HEIGHT + 20, 380, _T("上  :      ↑"));
//		outtextxy(WINDOW_HEIGHT + 20, 400, _T("下  :      ↓"));
//		outtextxy(WINDOW_HEIGHT + 20, 420, _T("左  :      ←"));
//		outtextxy(WINDOW_HEIGHT + 20, 440, _T("右  :      →"));
//	}
/******AI*******/
//	// AI相关
//	void OpenAI() { isAI = true; }
//	void CloseAI() { isAI = false; }
//	// 得到下一步AI指令--
//	char getNextCmd() {
//		if (isAI == false)
//			return 0x00;
//		char cmd = 0x00;
//		// 如果能找到食物
//		if (canFindFood(snake.coor.front())) {
//			// 模拟一条蛇
//			SnakeGame simulate = *this;
//			// 去吃食物
//			while (simulate.food.EXISTFOOD) {
//				simulate.snake.TurnDirect(simulate.NextCmdToFood());
//				simulate.snake.Move();
//				simulate.EatFood();
//			}
//			// 如果吃完还能找到尾巴/到尾巴的距离大于1
//			if (simulate.canFindPath(simulate.snake.coor.front(), simulate.snake.coor.back()) > 1) {
//				// 真正去吃
//				cmd = NextCmdToFood();
//			}
//			else {
//				// 吃完找不到
//				cmd = NextCmdToFarAway(snake.coor.front());
//			}
//		}
//		else {
//			// 找不到食物
//			cmd = NextCmdToFarAway(snake.coor.front());
//		}
//		return cmd;
//	}
//	// 存在路径返回步数，不存在返回-1
//	int canFindPath(const Coor& _start, const Coor& _end) {
//		if (_start == _end) {
//			return 0;
//		}
//		const int next[4][2] = { {1,0} ,{0,1}, {-1,0}, {0,-1} }; // 右下左上
//		queue<Coor> bfs_que;
//		set<Coor> snake_set;
//		Coor tcoor;
//		bfs_que.push(_start);
//		for (auto iter : snake.coor) {
//			snake_set.insert(iter);
//		}
//		// 如果终点是尾巴就把尾巴置为可走结点 *
//		// 调用时需要使用引用
//		if (&_end == &snake.coor.back()) {
//			snake_set.erase(_end);
//		}
//		while (!bfs_que.empty()) {
//			for (int k = 0; k < 4; k++) {
//				tcoor.x = bfs_que.front().x + next[k][0];
//				tcoor.y = bfs_que.front().y + next[k][1];
//				// 超出地图进入下次循环
//				if (!inBorder(tcoor)) {
//					continue;
//				}
//				// 无障碍没有走过的结点加入队列
//				if (!snake_set.count(tcoor)) {
//					tcoor.step = bfs_que.front().step + 1;
//					snake_set.insert(tcoor);
//					bfs_que.push(tcoor);
//				}
//				// 到达目标返回步数
//				if (tcoor == _end) {
//					return tcoor.step;
//				}
//			}
//			bfs_que.pop();
//		}
//		return -1;
//	}
//	// 存在到尾巴的路径
//	bool canFindTail(Coor _start) {
//		return canFindPath(_start, snake.coor.back()) >= 0 ? true : false;
//	}
//	// 存在到食物的路径
//	bool canFindFood(Coor _start) {
//		return canFindPath(_start, food.coor) >= 0 ? true : false;
//	}
//	// 最短距离吃食物
//	char NextCmdToFood() {
//		const int next[4][2] = { { 1,0 } ,{ 0,1 },{ -1,0 },{ 0,-1 } }; // 右下左上
//		// 得到头部周围4点
//		Coor aroundPoint[4];
//		for (int i = 0; i < 4; i++) {
//			aroundPoint[i].x = snake.coor.front().x + next[i][0];
//			aroundPoint[i].y = snake.coor.front().y + next[i][1];
//			if (!inBorder(aroundPoint[i]) || onSnake_ExceptTail(aroundPoint[i]))	// 特殊处理尾巴
//				aroundPoint[i].step = -1;
//			else
//				aroundPoint[i].step = canFindPath(aroundPoint[i], food.coor);
//		}
//		// 选出最近的走
//		int minstep_index = 0;
//		for (int i = 1; i < 4; i++) {
//			// 是0表示是食物直接走
//			// 如果是-1不参与比较
//			if (aroundPoint[minstep_index].step == -1)
//				minstep_index = i;
//			if (aroundPoint[i].step != -1) {
//				if (aroundPoint[i].step < aroundPoint[minstep_index].step) {
//					minstep_index = i;
//				}
//			}
//		}
//		char ret = 0x00;
//		// 返回操作，找不到食物就返回0x00什么都不做
//		if (aroundPoint[minstep_index].step != -1)
//			ret = RetCmd(aroundPoint[minstep_index]);
//		return ret;
//	}
//	// 后期吃食物用最远
//
//	// 远离食物--待改进**
//	char NextCmdToFarAway(const Coor& coor) {
//		const int next[4][2] = { { 1,0 } ,{ 0,1 },{ -1,0 },{ 0,-1 } }; // 右下左上
//		// 得到周围四点曼哈顿距离
//		Coor aroundPoint[4];
//		for (int i = 0; i < 4; i++) {
//			aroundPoint[i].x = snake.coor.front().x + next[i][0];
//			aroundPoint[i].y = snake.coor.front().y + next[i][1];
//			// 曼哈顿距离,有障碍的点置为-1
//			if (canFindTail(aroundPoint[i]) && inBorder(aroundPoint[i]) && !onSnake_ExceptTail(aroundPoint[i]))
//				aroundPoint[i].step = getManhattanDistance(aroundPoint[i], coor);
//			else // *这里蛇尾应设置为可行
//				aroundPoint[i].step = -1;
//		}
//		// 能到尾巴,远离食物
//		// 另一种策略是选离尾巴远的
//		int maxstep_index = 0;
//		for (int i = 1; i < 4; i++) {
//			// 等于号很重要
//			if ((aroundPoint[i].step >= aroundPoint[maxstep_index].step)) {
//				maxstep_index = i;
//			}
//		}
//		char cmd = 0x00;
//		if (aroundPoint[maxstep_index].step != -1)
//			cmd = RetCmd(aroundPoint[maxstep_index]);
//		return cmd;
//	}
//	// 最远距离追尾巴
//	char NextCmdToTail() {
//		const int next[4][2] = { { 1,0 } ,{ 0,1 },{ -1,0 },{ 0,-1 } }; // 右下左上
//		// 得到头部周围4点
//		Coor aroundPoint[4];
//		for (int i = 0; i < 4; i++) {
//			aroundPoint[i].x = snake.coor.front().x + next[i][0];
//			aroundPoint[i].y = snake.coor.front().y + next[i][1];
//			if (inBorder(aroundPoint[i]) && !onSnake_ExceptTail(aroundPoint[i]))	//	*特殊处理尾巴
//				aroundPoint[i].step = canFindPath(aroundPoint[i], snake.coor.back());
//			else
//				aroundPoint[i].step = -1;
//		}
//		// 选出最远的点
//		int maxstep_index = 0;
//		for (int i = 1; i < 4; i++) {
//			// 是0表示是食物直接走
//			// 如果是-1不参与比较
//			if (aroundPoint[maxstep_index].step == -1)
//				maxstep_index = i;
//			if (aroundPoint[i].step != -1) {
//				if (aroundPoint[i].step > aroundPoint[maxstep_index].step) {
//					maxstep_index = i;
//				}
//			}
//		}
//		char ret = 0x00;
//		// 返回操作，找不到食物就返回0x00什么都不做
//		if (aroundPoint[maxstep_index].step != -1)
//			ret = RetCmd(aroundPoint[maxstep_index]);
//		return ret;
//	}
//	// 返回可用的指令,必须是周围4点
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
//	// 两点曼哈顿距离
//	int getManhattanDistance(Coor _a, Coor _b) {
//		return abs(_a.x - _b.x) + abs(_a.y - _b.y);
//	}
//	// 坐标在蛇上/包括蛇头蛇尾
//	bool onSnake(Coor coor) {
//		for (auto iter : snake.coor) {
//			if (coor == iter) {
//				return true;
//			}
//		}
//		return false;
//	}
//	// 坐标在蛇上/不包括蛇头
//	bool onSnake_ExceptHead(Coor coor) {
//		auto iter = snake.coor.begin();
//		for (iter++; iter != snake.coor.end(); iter++) {
//			if (coor == *iter) {
//				return true;
//			}
//		}
//		return false;
//	}
//	// 坐标在蛇上/不包括蛇尾
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
//	// 坐标在方框里
//	bool inBorder(Coor coor)const {
//		return (coor.x >= 0 && coor.x < MAP_COLNUM&& coor.y >= 0 && coor.y < MAP_ROWNUM);
//	}
//};
//// 程序入口
//int main() {
//	// 加参数, SHOWCONSOLE开启控制台
//	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
//	// 开启双缓冲绘图
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
//			SG.ShowGameInfo();	//显示最终信息
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


/******用户登入界面******/
//#include <easyx.h>      // 引用图形库头文件
//#include <conio.h>
//#include <stdio.h>
////#include <windows.h>
//#include <time.h>
//#include <stdlib.h>
//#include <string.h>
//
////wchar_t 与 char数据类型转换
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
//    //int color;    //积分商店颜色
//}snake; //snake[0] is head
//typedef struct The_users //用于储存用户账号密码
//{
//    char id[11];//ID
//    char pwd[20];//password
//}users;
//users a, b;//成员变量,用来登陆与注册
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
//    initgraph(640, 480);//创建绘图窗口
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
//    //防止蛇原路返回导致失败
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
//    InputBox(s1, 5, L"请输入数字：1.开始游戏 2.高分榜 3.退出游戏");
//    int x, y[3];
//    //sscanf_s(s1, "%d", &x);//将用户输入转化为数字
//    x = _wtoi(s1);
//    if (x == 1)
//    {
//        InputBox(s2, 5, L"请输入数字：1.注册2.登陆");
//        x = _wtoi(s2);
//        if (x == 1) {
//            registers();
//            Login();
//        }
//        else if (x == 2) {
//            Login();
//        }
//        init_map(); //初始化地图
//        while (1)
//        {
//            update_food();
//            //是否产生食物
//            get_speed();  //获取速度
//            move_snake();  //移动蛇身
//            redraw_map();//重绘地图
//            Sleep(snake.speed);
//            //移动速度
//            if (!(is_alive()))
//                //蛇的死活(撞墙或自食)
//                break;
//        }
//        closegraph();//关闭绘图窗口
//        printf("Game Over!\n");
//        printf("你的得分：%d", snake.len - 3);
//        _getch();
//    }
//    else if (x == 2)
//    {
//        closegraph();
//        printf("                    排行榜\n");
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
//void registers()//注册账号密码
//{
//    fopen_s(&fp, "Users1.txt", "r");
//    fscanf_s(fp, "%s%s", b.id, sizeof(b.id), b.pwd, sizeof(b.pwd));
//    InputBox(temp, 11, L"请输入账号");
//    strcpy_s(a.id,wchar2char(temp));
//    while (1)
//    {
//        if (strcmp(a.id, b.id) != 0)//如果两串字符串不相等
//        {
//            if (!feof(fp))//如果未至文件末尾
//            {
//                fscanf_s(fp, "%s%s", b.id, sizeof(b.id), b.pwd, sizeof(b.pwd));
//            }
//            else break;
//        }
//        else
//        {
//            outtextxy(220, 200, L"此用户名已被注册");
//            fclose(fp);
//            _getch();
//            exit(0);
//        }
//    }
//    fclose(fp);
//    InputBox(temp, 10, L"请输入密码");
//    strcpy_s(a.pwd, wchar2char(temp));
//    fopen_s(&fp, "Users1.txt", "a");
//    fprintf_s(fp, "%s %s\n", a.id, a.pwd);
//    outtextxy(220, 200, L"账号注册成功！");
//    fclose(fp);
//}
//void Login()//登陆账号密码
//{
//    fopen_s(&fp, "Users1.txt", "r");
//    fscanf_s(fp, "%s%s", b.id, sizeof(b.id), b.pwd, sizeof(b.pwd));
//    InputBox(temp, 11, L"请输入账号");
//    strcpy_s(a.id, wchar2char(temp));
//    while (1)
//    {
//        if (strcmp(a.id, b.id) == 0) break;//如果找到了这个用户名
//        else
//        {
//            if (!feof(fp))//如果文件未读完
//                fscanf_s(fp, "%s%s", b.id, sizeof(b.id), b.pwd, sizeof(b.pwd));
//            else
//            {
//                outtextxy(220, 200, L"此用户名不存在!");
//                fclose(fp);
//                _getch();
//                exit(0);
//            }
//        }
//    }
//    InputBox(temp, 20, L"请输入密码");
//    strcpy_s(a.pwd, wchar2char(temp));
//    if (strcmp(a.pwd, b.pwd) == 0)//如果密码匹配
//    {
//        fclose(fp);
//        outtextxy(250, 200, L"登陆成功！");
//        initgraph(640, 480);
//    }
//    else
//    {
//        outtextxy(220, 200, L"密码不正确");
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
//}//升序排序
//int compDec(const void* a, const void* b) {
//    return *(int*)b - *(int*)a;
//}//降序排序



//////#include<stdio.h>
//////#include<easyx.h>
//////#include<conio.h>
//////
//////int main()
//////{
//////	// 初始化绘图窗口
//////	initgraph(640, 480);
//////
//////	// 定义字符串缓冲区，并接收用户输入
//////	wchar_t s[10];
//////	char str[20];
//////	InputBox(s, 10, L"请输入半径");
//////
//////	// 将用户输入转换为数字
//////	int r = _wtoi(s);
//////
//////	// 画圆
//////	circle(320, 240, r);
//////
//////	// 按任意键退出
//////	_getch();
//////	closegraph();
//////
//////	return 0;
//////}


//////// 迷宫.cpp : 定义控制台应用程序的入口点。
////////#include "stdafx.h"
//////#include <graphics.h>
//////#include <stack>
//////#include <vector>
//////using std::stack;				// 使用STL的栈
//////using std::vector;				// 使用STL的数组容器
//////
//////								// 游戏信息
//////#define WIN_WIDTH	400			// 窗口的宽度(单位：像素)
//////#define WIN_HEIGHT	300			// 窗口的高度(单位：像素)
//////								// !!注：由于随机生成算法的原因，地图宽高只能为奇数
//////#define GAME_WIDTH	41			// 地图的宽度(单位：块)
//////#define GAME_HEIGHT	51			// 地图的高度(单位：块)
//////
//////#define WALL		1			// 墙壁的数字标记
//////#define GROUND		0			// 地面的数字标记
//////#define FILLSTATE	2			// 加油站的数字标记
//////#define ENDPOS		3			// 终点的数字标记
//////
//////#define MAXVIEW		8.0			// 最大的视野
//////#define MINVIEW		1			// 最小的视野
//////#define FILLNUM		10			// 加油站的数量
//////#define DARKTIME	12			// 视野下降1图块所需的时间
//////
//////								// 全局变量列表
//////int		g_BlockSize;			// 块大小
//////int		g_GameMap[GAME_HEIGHT][GAME_WIDTH];	// 地图(宽高单位为块)
//////POINT	g_EndPos;				// 终点位置
//////POINT   g_PlayerPos;			// 玩家在地图上的位置
//////POINT	g_CameraPos;			// 摄像机(屏幕左上角)在地图上的位置
//////IMAGE	g_MapImage;				// 地图的图片(由于地图是固定的，在不改变缩放的情况下只需要绘制一次)
//////double	g_ViewArray;			// 视野
//////UINT	g_BeginTime;			// 游戏开始时的时间
//////UINT	g_LastFillTime;			// 上次为油灯加油的时间
//////
//////
//////								// 函数列表
//////void initGame();				// 初始化游戏
//////void endGame();					// 结束游戏
//////void draw();					// 绘制函数
//////bool upDate();					// 数据更新函数
//////void absDelay(int delay);		// 绝对延迟
//////
//////bool canMove(POINT pos);		// 判断某个位置是否可以移动
//////void computeCameraPos();		// 计算摄像机在地图上的位置
//////void rePaintMap();				// 重绘地图
//////
//////void drawWall(POINT pos);		// 绘制墙壁图块的函数
//////void drawGround(POINT pos);		// 绘制地面图块的函数
//////void drawFillState(POINT pos);	// 绘制油灯图块的函数
//////void drawEndPos(POINT pos);		// 绘制终点
//////void drawPlayer();				// 绘制人物的函数
//////void drawView();				// 绘制视野
//////
//////int main()
//////{
//////	initGame();
//////
//////	while (1)
//////	{
//////		if (!upDate()) break;	// 更新
//////		draw();					// 绘制
//////		absDelay(16);			// 绝对延迟 16 毫秒，控制每秒 60 帧
//////	}
//////
//////	endGame();
//////	return 0;
//////}
//////
//////void initGame()
//////{
//////	g_BlockSize = 32;			// 初始图块大小为 32 个像素
//////	srand(GetTickCount());		// 初始化随机数生成
//////
//////								// 初始化间隔室
//////	for (int i = 0; i < GAME_HEIGHT; i++)
//////	{
//////		for (int j = 0; j < GAME_WIDTH; j++)
//////		{
//////			if (i % 2 == 0 || j % 2 == 0)	// 奇数行奇数列设为墙壁
//////				g_GameMap[i][j] = WALL;
//////			else
//////				g_GameMap[i][j] = GROUND;
//////		}
//////	}
////
//////	// 随机生成地图(使用深度优先遍历)
//////	stack<POINT> stepStack;		// 步骤栈
//////	vector<POINT>  stepPoint;	// 四周的点
//////	POINT nowPoint;				// 当前步的所在点
//////	stepStack.push({ 1,1 });	// 写入初始点 (1,1) 作为起点
//////	nowPoint = { 1,1 };
//////	g_GameMap[1][1] = 0xFFFF;	// 标记这个点
//////	while (!stepStack.empty())	// 只要步骤栈不空就继续循环
//////	{
//////		// 得到四周的点
//////		POINT tempPoint;
//////		for (int i = -1; i <= 1; i += 2)
//////		{
//////			tempPoint = { nowPoint.x,nowPoint.y + i * 2 };	// 计算点
//////															// 判断坐标是否合法
//////			if (tempPoint.x >= 0 && tempPoint.x <= GAME_WIDTH - 1 &&
//////				tempPoint.y >= 0 && tempPoint.y <= GAME_HEIGHT - 1 &&
//////				g_GameMap[tempPoint.y][tempPoint.x] != 0xFFFF)
//////			{
//////				stepPoint.push_back(tempPoint);
//////			}
//////			tempPoint = { nowPoint.x + i * 2 ,nowPoint.y };	// 计算点
//////															// 判断坐标是否合法
//////			if (tempPoint.x >= 0 && tempPoint.x <= GAME_WIDTH - 1 &&
//////				tempPoint.y >= 0 && tempPoint.y <= GAME_HEIGHT - 1 &&
//////				g_GameMap[tempPoint.y][tempPoint.x] != 0xFFFF)
//////			{
//////				stepPoint.push_back(tempPoint);
//////			}
//////		}
//////
//////		// 根据周围点的量选择操作
//////		if (stepPoint.empty())				// 如果周围点都被遍历过了
//////		{
//////			stepStack.pop();				// 出栈当前点
//////			if (!stepStack.empty())
//////				nowPoint = stepStack.top();	// 更新当前点
//////		}
//////		else
//////		{
//////			stepStack.push(stepPoint[rand() % stepPoint.size()]);	// 入栈当前点
//////			g_GameMap[(nowPoint.y + stepStack.top().y) / 2][(nowPoint.x + stepStack.top().x) / 2] = 0;	// 打通墙壁
//////			nowPoint = stepStack.top();		// 更新当前点
//////			g_GameMap[nowPoint.y][nowPoint.x] = 0xFFFF;				// 标记当前点
//////		}
//////		stepPoint.clear();					// 清空周围点以便下一次循环
//////	}
//////
//////	// 清洗标记点
//////	for (int i = 0; i < GAME_HEIGHT; i++)
//////	{
//////		for (int j = 0; j < GAME_WIDTH; j++)
//////		{
//////			if (g_GameMap[i][j] == 0xFFFF)
//////				g_GameMap[i][j] = 0;
//////		}
//////	}
//////
//////	// 随机生成加油站的位置
//////	for (int i = 0; i < FILLNUM; i++)
//////	{
//////		POINT fillPoint = { rand() % GAME_WIDTH,rand() % GAME_HEIGHT };
//////		// 保证在空地生成加油站
//////		while (g_GameMap[fillPoint.y][fillPoint.x] != GROUND)
//////			fillPoint = { rand() % GAME_WIDTH,rand() % GAME_HEIGHT };
//////		// 标记油灯
//////		g_GameMap[fillPoint.y][fillPoint.x] = FILLSTATE;
//////	}
//////
//////	g_GameMap[GAME_HEIGHT - 2][GAME_WIDTH - 2] = ENDPOS;		// 标记终点
//////	g_EndPos = { GAME_WIDTH - 2,GAME_HEIGHT - 2 };				// 确定终点位置
//////	g_ViewArray = MAXVIEW;				// 初始视野是最大的
//////	g_BeginTime = GetTickCount();		// 开始计时
//////	g_LastFillTime = GetTickCount();	// 油灯加油的时间
//////	rePaintMap();						// 绘制地图
//////	g_PlayerPos = { g_BlockSize * 3 / 2,g_BlockSize * 3 / 2 };	// 初始化人的位置
//////	computeCameraPos();					// 计算摄像机的位置
//////	initgraph(WIN_WIDTH, WIN_HEIGHT);	// 初始化画布
//////	setbkmode(TRANSPARENT);				// 设置背景为透明
//////	BeginBatchDraw();					// 开始缓冲绘制
//////}
//////
//////void endGame()
//////{
//////	EndBatchDraw();						// 结束缓冲绘制
//////	closegraph();						// 关闭画布
//////}
//////
//////void draw()
//////{
//////	// 清空设备
//////	cleardevice();
//////	// 绘制视野
//////	drawView();
//////	// 绘制人
//////	drawPlayer();
//////	// 绘制时间
//////	TCHAR timeStr[256];
//////	int loseTime = GetTickCount() - g_BeginTime;	// 计算流失的时间
//////	_stprintf_s(timeStr, _T("游戏时间:%02d:%02d"), loseTime / 1000 / 60, loseTime / 1000 % 60);
//////	settextcolor(RGB(140, 140, 140));
//////	outtextxy((WIN_WIDTH - textwidth(timeStr)) / 2, 3, timeStr);
//////
//////	FlushBatchDraw();	// 刷新屏幕
//////}
//////
//////bool upDate()
//////{
//////	POINT nextPos = g_PlayerPos;		// 下一个位置
//////
//////										// 计算下一个位置
//////	if (GetKeyState(VK_UP) & 0x8000)	nextPos.y -= 2;
//////	if (GetKeyState(VK_DOWN) & 0x8000)	nextPos.y += 2;
//////	if (GetKeyState(VK_LEFT) & 0x8000)	nextPos.x -= 2;
//////	if (GetKeyState(VK_RIGHT) & 0x8000)	nextPos.x += 2;
//////
//////	// 如果下一个位置不合法
//////	if (!canMove(nextPos))
//////	{
//////		if (canMove({ g_PlayerPos.x, nextPos.y }))		// y 轴移动合法
//////			nextPos = { g_PlayerPos.x, nextPos.y };
//////		else if (canMove({ nextPos.x, g_PlayerPos.y }))	// x 轴移动合法
//////			nextPos = { nextPos.x, g_PlayerPos.y };
//////		else											// 都不合法
//////			nextPos = g_PlayerPos;
//////	}
//////
//////	// 如果是油灯则更新时间
//////	if (g_GameMap[nextPos.y / g_BlockSize][nextPos.x / g_BlockSize] == FILLSTATE)
//////		g_LastFillTime = GetTickCount();
//////	// 如果是终点则通关
//////	else if (g_GameMap[nextPos.y / g_BlockSize][nextPos.x / g_BlockSize] == ENDPOS)
//////	{
//////		outtextxy(WIN_WIDTH / 2 - 40, WIN_HEIGHT / 2 - 12, _T("恭喜过关！"));
//////		FlushBatchDraw();
//////		Sleep(1000);
//////		return false;
//////	}
//////	g_PlayerPos = nextPos;						// 更新位置
//////	computeCameraPos();					    // 计算摄像机的位置
//////
//////												// 根据时间缩减视野
//////	static unsigned int lastTime = GetTickCount();
//////	int loseTime = GetTickCount() - g_LastFillTime;			// 计算流失的时间
//////	g_ViewArray = MAXVIEW - loseTime / 1000.0 / DARKTIME;	// 每一段时间油灯的照明力会下降一个图块
//////	if (g_ViewArray < MINVIEW) g_ViewArray = MINVIEW;
//////
//////	// 处理鼠标消息
//////	MOUSEMSG mouseMsg;							// 鼠标信息
//////	int lastBlockSize = g_BlockSize;			// 保存原本的大小
//////	while (MouseHit())
//////	{
//////		mouseMsg = GetMouseMsg();
//////		if (mouseMsg.uMsg = WM_MOUSEWHEEL)		// 滚轮消息
//////		{
//////			g_BlockSize += mouseMsg.wheel / 120;
//////		}
//////	}
//////
//////	// 如果没有滚轮消息就退出
//////	if (lastBlockSize == g_BlockSize) return true;
//////	// 处理滚轮消息
//////	if (g_BlockSize >= 10 && g_BlockSize <= 50)	// 块大小没有达到极限值
//////	{
//////		// 保证缩放后的地图不会比窗口小
//////		if (GAME_WIDTH * g_BlockSize < WIN_WIDTH ||
//////			GAME_HEIGHT * g_BlockSize < WIN_HEIGHT)
//////			g_BlockSize = lastBlockSize;
//////		rePaintMap();							// 重绘地图
//////												// 重新计算玩家在地图上的位置
//////		POINT mapPos = { g_PlayerPos.x / lastBlockSize,g_PlayerPos.y / lastBlockSize };	// 计算在地图上的位置
//////		g_PlayerPos.x = mapPos.x * g_BlockSize + g_BlockSize / 2;	// 计算映射后的位置
//////		g_PlayerPos.y = mapPos.y * g_BlockSize + g_BlockSize / 2;	// 计算映射后的位置
//////		computeCameraPos();						// 重新计算摄像机位置
//////	}
//////	// 保证图块不会过大和过小
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
//////	// 只要外接矩形的四个顶点不在墙壁内就必定合法
//////	return	g_GameMap[(pos.y - 3) / g_BlockSize][(pos.x - 3) / g_BlockSize] != WALL &&
//////		g_GameMap[(pos.y + 3) / g_BlockSize][(pos.x + 3) / g_BlockSize] != WALL &&
//////		g_GameMap[(pos.y - 3) / g_BlockSize][(pos.x + 3) / g_BlockSize] != WALL &&
//////		g_GameMap[(pos.y + 3) / g_BlockSize][(pos.x - 3) / g_BlockSize] != WALL;
//////}
//////
//////void computeCameraPos()
//////{
//////	// 以人物位置为中心计算摄像机的理论位置
//////	g_CameraPos.x = g_PlayerPos.x - WIN_WIDTH / 2;
//////	g_CameraPos.y = g_PlayerPos.y - WIN_HEIGHT / 2;
//////
//////	// 防止摄像机越界
//////	if (g_CameraPos.x < 0)										g_CameraPos.x = 0;
//////	if (g_CameraPos.y < 0)										g_CameraPos.y = 0;
//////	if (g_CameraPos.x > GAME_WIDTH * g_BlockSize - WIN_WIDTH)	g_CameraPos.x = GAME_WIDTH * g_BlockSize - WIN_WIDTH;
//////	if (g_CameraPos.y > GAME_HEIGHT * g_BlockSize - WIN_HEIGHT)	g_CameraPos.y = GAME_HEIGHT * g_BlockSize - WIN_HEIGHT;
//////}
//////
//////void rePaintMap()
//////{
//////	g_MapImage.Resize(GAME_WIDTH * g_BlockSize, GAME_HEIGHT * g_BlockSize);	// 重置地图图片大小
//////	SetWorkingImage(&g_MapImage);								// 设置地图图片为当前工作图片
//////	for (int i = 0; i < GAME_HEIGHT; i++)
//////	{
//////		for (int j = 0; j < GAME_WIDTH; j++)
//////		{
//////			switch (g_GameMap[i][j])
//////			{
//////			case WALL:
//////				drawWall({ j * g_BlockSize,i * g_BlockSize });		// 绘制墙壁
//////				break;
//////			case FILLSTATE:
//////				drawFillState({ j * g_BlockSize,i * g_BlockSize });	// 绘制加油站
//////				break;
//////			case GROUND:
//////				drawGround({ j * g_BlockSize,i * g_BlockSize });	// 绘制地面
//////				break;
//////			case ENDPOS:
//////				drawEndPos({ j * g_BlockSize,i * g_BlockSize });
//////				break;
//////			}
//////		}
//////	}
//////	SetWorkingImage();	// 复位工作图片
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
//////	// 绘制圆角矩形
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
//////	// 绘制圆角矩形
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
//////	// 锁定视野
//////	HRGN viewArr;
//////	int r = int(g_BlockSize * g_ViewArray + 0.5);	// 计算视野半径
//////	POINT orgin = g_PlayerPos;
//////	orgin.x -= g_CameraPos.x;						// 计算在屏幕上的位置
//////	orgin.y -= g_CameraPos.y;						// 计算在屏幕上的位置
//////	viewArr = CreateEllipticRgn(orgin.x - r, orgin.y - r, orgin.x + r, orgin.y + r);	// 创建一个圆形的区域
//////	setcliprgn(viewArr);							// 锁定区域
//////
//////													// 绘制地图
//////	putimage(0, 0, WIN_WIDTH, WIN_HEIGHT, &g_MapImage, g_CameraPos.x, g_CameraPos.y);
//////
//////	// 删除区域
//////	DeleteObject(viewArr);
//////	// 消除区域
//////	setcliprgn(NULL);
//////}



//////贪吃蛇
////////这个不太行，但是双人游戏想法不错
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
//////void gotoxy(int x, int y)//位置函数
//////{
//////    COORD pos;
//////
//////    pos.X = x;
//////
//////    pos.Y = y;
//////
//////    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
//////}
//////void color(int a)//颜色函数
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
//////    /*棋盘 20×80 初始化*/
//////    for (int i = 0; i < 20; i++)
//////    {
//////        for (int j = 0; j < 80; j++)
//////        {
//////            qipan[i][j] = ' ';
//////        }
//////    }
//////    for (int i = 0; i < 20; i++)
//////    {
//////        qipan[i][0] = qipan[i][79] = '|';//第一列、最后一列是墙20*1
//////    }
//////    for (int i = 0; i < 80; i++)
//////    {
//////        qipan[0][i] = qipan[19][i] = '_';//第一行、最后一行是墙1*80
//////    }
//////
//////    /*蛇的坐标 2×8 初始化, 将蛇放到棋盘上*/
//////    int x1 = 1, x2 = 18, y, temp = 0;
//////
//////    for (int m = tail1; m < head1; m++)
//////    {
//////        zuobiao1[0][m] = x1;//初始行号
//////        y = zuobiao1[1][m] = ++temp;//初始列号
//////        qipan[x1][y] = '*';
//////    }
//////    zuobiao1[0][head1] = x1;//初始行号
//////    y = zuobiao1[1][head1] = ++temp;//初始列号
//////    qipan[x1][y] = '#';//蛇头
//////
//////    show_start();
//////
//////    if (snake == 2)
//////    {
//////        temp = 0;
//////        for (int m = tail2; m < head2; m++)
//////        {
//////            zuobiao2[0][m] = x2;//初始行号
//////            y = zuobiao2[1][m] = ++temp;//初始列号
//////            qipan[x2][y] = '*';
//////        }
//////        zuobiao2[0][head2] = x2;//初始行号
//////        y = zuobiao2[1][head2] = ++temp;//初始列号
//////        qipan[x2][y] = '#';//蛇头
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
//////    for (int i = 0; i < 20; i++)//打印出棋盘
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
//////        for (int i = 0; i < 20; i++)//打印出棋盘
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
//////        if (timeover)//有按键
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
//////        for (int i = 0; i < 20; i++)//打印出棋盘
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
//////////枚举
////////enum game
////////{
////////	SPACE, WALL, SNAKE, FOOD, HEAD//空地  墙  蛇  食物
////////};
/////////************全局变量************/
////////int mode = 0;			//游戏模式
////////int score = 0;			//分数
////////DWORD t1, t2;			//定义两个时间控制移动速度
////////int map[ROW][COL];		//地图大小
////////COORD snake[1024];		//蛇			typedef struct _COORD {SHORT X;SHORT Y;} COORD, *PCOORD;
////////size_t SnakeSize;		//蛇的尺度		typedef unsigned int     size_t;
////////char SnakeDir;			//蛇移动方向
/////////************全局函数************/
////////void start();	//开始界面
////////void chose();	//选择模式  0:普通模式  1：穿墙模式  2：无敌模式
////////void DrawMap();	//画图
////////void init();	//初始化游戏数据
////////void addfood();	//添加食物
////////void ChangeDir();	//修改蛇的方向
////////void move();//蛇的移动
////////int main()
////////{
////////	initgraph(640, 480);
////////	start();
////////	outtextxy(260, 150, "->");		//初始默认模式一
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
////////	srand((unsigned)time(NULL));	//随机种子
////////	setbkcolor(WHITE);				//设置背景颜色
////////
////////	memset(map, SPACE, sizeof(map));//初始化map数组为0即SPACE
////////	//每一行的 第一个 和 最后一个 是墙
////////	for (int i = 0; i < ROW; i++)
////////	{
////////		map[i][0] = map[i][COL - 1] = WALL;
////////	}
////////	//每一列的 第二个 和 倒数第二 个是墙
////////	for (int j = 1; j < COL - 1; j++)
////////	{
////////		map[0][j] = map[ROW - 1][j] = WALL;
////////	}
////////	//定义蛇头和蛇的身体
////////	map[3][5] = HEAD;
////////	map[3][4] = map[3][3] = SNAKE;
////////	//初始化蛇
////////	SnakeSize = 3;	//蛇 长
////////	SnakeDir = 'D';	//蛇方向向右
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
////////	setbkcolor(WHITE);		//设置窗口背景色为白色
////////	cleardevice();			//刷新屏幕
////////
////////	setbkmode(TRANSPARENT);	//设置字体背景色为透明
////////	settextcolor(BLACK);		//设置字体颜色为红色
////////	/*****************游戏规则*****************/
////////	outtextxy(290, 80, "功能选择:");
////////	outtextxy(280, 150, "1.普通模式");
////////	outtextxy(280, 200, "2.穿墙模式");
////////	outtextxy(280, 250, "3.无敌模式");
////////	outtextxy(200, 280, "数字键 1,2,3 选择模式，Enter键进入游戏");
////////	outtextxy(200, 300, "字母键 W,S,A,D 方向键 上下左右 控制方向");
////////	outtextxy(130, 350, "相关内容：");
////////	outtextxy(160, 380, "关注微信公众号: 编程学习基地 获取源码");
////////	outtextxy(160, 410, "编程学习加群:  879098023");
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
////////	BeginBatchDraw();	//开始绘图
////////	setbkcolor(WHITE);	//设置背景颜色为白色
////////	settextcolor(RGB(238,0,0));
////////	cleardevice();		//清屏
////////	char arr[10];		//保存成绩
////////	sprintf(arr, "总分：%d", score);	//将成绩格式化输出到字符串arr中 
////////	outtextxy(0, 0, arr);				//显示成绩
////////	for (int y = 0; y < ROW; y++)		//y轴方向向下
////////	{
////////		for (int x = 0; x < COL; x++)	//x轴方向下上
////////		{
////////			switch (map[y][x])
////////			{
////////			case SPACE:
////////				break;
////////			case WALL:
////////				setlinecolor(BLACK);	
////////				setfillcolor(RGB(238, 233, 233));	//灰色
////////				fillrectangle(x * 10, y * 10 + 20, x * 10 + 10, y * 10 + 30);
////////				break;
////////			case SNAKE:
////////				setlinecolor(RGB(0, 245, 255));		//绿色 
////////				setfillcolor(WHITE);
////////				fillrectangle(x * 10, y * 10 + 20, x * 10 + 10, y * 10 + 30);
////////				break;
////////			case HEAD:
////////				//画七彩蛇头
////////				switch (rand() % 7)
////////				{
////////				case 0:
////////					setfillcolor(RGB(255, 0, 0));		//红色 255 0 0
////////					solidrectangle(x * 10, y * 10 + 20, x * 10 + 10, y * 10 + 30);
////////					break;
////////				case 1:
////////					setfillcolor(RGB(255, 165, 0));		//橙  255 165 0 
////////					solidrectangle(x * 10, y * 10 + 20, x * 10 + 10, y * 10 + 30);
////////					break;
////////				case 2:
////////					setfillcolor(RGB(255, 255, 0));		//黄  255 255 0
////////					solidrectangle(x * 10, y * 10 + 20, x * 10 + 10, y * 10 + 30);
////////					break;
////////				case 3:
////////					setfillcolor(RGB(0, 255, 0));		//绿色  0, 255, 0
////////					solidrectangle(x * 10, y * 10 + 20, x * 10 + 10, y * 10 + 30);
////////					break;
////////				case 4:
////////					setfillcolor(RGB(0, 255, 255));		//青  0 255 255
////////					solidrectangle(x * 10, y * 10 + 20, x * 10 + 10, y * 10 + 30);
////////					break;
////////				case 5:
////////					setfillcolor(RGB(0, 0, 255));		//蓝  0 0 255
////////					solidrectangle(x * 10, y * 10 + 20, x * 10 + 10, y * 10 + 30);
////////					break;
////////				case 6:
////////					setfillcolor(RGB(160, 32, 240));	//紫  160 32 240
////////					solidrectangle(x * 10, y * 10 + 20, x * 10 + 10, y * 10 + 30);
////////					break;
////////				default:
////////					break;
////////				}
////////				break;
////////			case FOOD:
////////				setfillcolor(RGB(255, 0, 0));			//红色
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
////////		if (SnakeDir != 'D') SnakeDir = 'A';	//蛇不能后退
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
////////	COORD next;		//蛇头的下一个位置
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
////////	case SPACE://直接移动
////////		map[snake[SnakeSize - 1].X][snake[SnakeSize - 1].Y] = SPACE;//地图蛇尾所在地置空
////////		for (i = SnakeSize - 1; i > 0; i--)						//蛇尾到蛇头整体移动一位
////////		{
////////			snake[i] = snake[i - 1];
////////		}
////////		map[snake[0].X][snake[0].Y] = SNAKE;						//蛇头置 蛇
////////		snake[0] = next;											//将下一个位置赋值给蛇头
////////		map[snake[0].X][snake[0].Y] = HEAD;							//设置头
////////		break;
////////	case WALL:
////////		if (mode)		//模式1模式2可穿墙
////////		{
////////			map[snake[SnakeSize - 1].X][snake[SnakeSize - 1].Y] = SPACE;//蛇尾置空
////////			for (i = SnakeSize - 1; i > 0; i--)						//蛇尾到蛇头整体移动一位
////////			{
////////				snake[i] = snake[i - 1];
////////			}
////////			map[snake[0].X][snake[0].Y] = SNAKE;						//蛇头置 蛇
////////			switch (SnakeDir)											//穿墙
////////			{
////////			case'A':next.Y = COL - 2; break;
////////			case 'D':next.Y = 1; break;
////////			case 'W': next.X = ROW - 2; break;
////////			case 'S':next.X = 1; break;
////////			default:
////////				break;
////////			}
////////			snake[0] = next;											//蛇头移动到新位置
////////			map[snake[0].X][snake[0].Y] = HEAD;		//新的蛇头所在的位置
////////		}
////////		else {
////////			MessageBox(GetHWnd(), "游戏结束", "SORRY", MB_OK);
////////			exit(0);
////////		}
////////		break;
////////	case SNAKE:
////////		if (mode == 2)		//模式二无敌
////////		{
////////			break;
////////		}
////////		else {
////////			MessageBox(GetHWnd(), "游戏结束", "SORRY", MB_OK);
////////			exit(0);
////////		}
////////		break;
////////	case FOOD://食物				蛇尾不变
////////		for (i = SnakeSize; i > 0; i--)							//蛇尾到蛇头整体移动一位
////////		{
////////			snake[i] = snake[i - 1];								
////////		}
////////		map[snake[0].X][snake[0].Y] = SNAKE;						//蛇头 置 蛇
////////		snake[0] = next;											//将下一个位置赋值给蛇头
////////		score++;			//分数加一				
////////		(SnakeSize)++;		//蛇尺度加一
////////		map[snake[0].X][snake[0].Y] = HEAD;							//地图上重置蛇头
////////		addfood();
////////		break;
////////	default:break;
////////	}
////////}
