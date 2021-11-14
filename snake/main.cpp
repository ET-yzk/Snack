/*******************************************/
//程序名称：贪吃蛇 V1.0
//编译环境：VS2019+EasyX_2020
//BY YZK
/*******************************************/
#include<Windows.h>// GetTickCount64()返回开机以来经过的毫秒数
#include<stdio.h>
#include<easyx.h> // 图形库
#include<conio.h> // _kbhit()  _getch()（非标准C语言头文件）
#include<time.h>  // 为随机生成函数提供（时间）种子
#include<mmsystem.h>
#pragma comment(lib,"WINMM.LIB") // music
//#include <string.h> //用于用户登入模块char与wchar_t数据类型的转换
//#include<stdlib.h> //qsort()快排用于加入用户后的排行榜

#define ROW 46             // 地图宽/10；若加入地图大小自定义，则需要注意初始蛇长与地图关系，可将判断加在Init()初始化蛇数据之前
#define COL 64              // 地图长/10,默认46*64（在后续显示函数中尽量使用COL,ROW，或许可以在一定程度上实现窗口自适应）
#define ROW_AI 20
#define COL_AI 20
#define KEY_UP 72         // 方向键↑
#define KEY_DOWN 80  // 方向键↓
#define KEY_LEFT 75      // 方向键←
#define KEY_RIGHT 77    // 方向键→
#define KEY_SPACE 32   // 空格键
#define KEY_ENTER 13   // 回车键
#define KEY_ESC 27       // 退出键

/***********ASTAR******************/
#define STARTNODE	1     // 起点
#define ENDNODE 2       // 终点
#define BARRIER 3          // 障碍

typedef struct AStarNode {
	int x;	                    // 坐标(最终输出路径需要)
	int y; 	                // 坐标(最终输出路径需要)
	int g;		                // 起点到此点的距离( 由g和h可以得到f，此处f省略，f=g+h )
	int h;		                // 启发函数预测的此点到终点的距离（采用曼哈顿距离）
	int style;	            // 结点类型：起始点，终点，障碍物
	struct AStarNode* parent;	// 父节点
	int in_closetable;	            // 是否在close表中
	int in_opentable;		        // 是否在open表中
}AStarNode, * pAStarNode;

AStarNode  map_maze[COL_AI - 2][ROW_AI - 2];		         // 结点顺序表，用来储存地图上该点的各项信息
pAStarNode open_table[(COL_AI - 2) * (ROW_AI - 2)];       // open表
pAStarNode close_table[(COL_AI - 2) * (ROW_AI - 2)];       // close表
int open_count = 0;                  // open表中节点数量
int close_count = 0;                  // close表中节点数量
pAStarNode path_stack[(COL_AI - 2) * (ROW_AI - 2)];      // 保存路径的栈
int top = -1;			                                                                // 栈顶
time_t start, end;


/****************全局变量*******************/
IMAGE img[2];              //定义图片指针等待调用
int mode = 0;               //游戏模式
int score = 0;               //记录分数
DWORD speed = 240; //控制蛇移动速度，初始为240较合适
char SnakeDir = 'D';    //记录蛇移动方向，初始方向向右

typedef struct Snake
{
	COORD body;            //蛇身		typedef struct _COORD {SHORT X;SHORT Y;} COORD, *PCOORD;  
	struct Snake* next;    //指向下一蛇身节点
}Snake;
Snake* head = NULL;    //表头，同时表示蛇头
Snake* tail = NULL;       //表尾
Snake* phead = NULL;  //指向各结点，用于遍历链表
COORD* food = NULL;  //食物

/****************全局函数*******************/
/*********基本功能**********/
void Go();                             //初始化功能函数
void Run(int row, int col);     //实现程序主体功能
void Music(int n);                 //播放背景音乐，输入n控制播放状态
void Start();                          //开始界面初始化
void Chose(int n);                //选择模式初始化，输入n代表模式类型
void DrawMap(int color, int row, int col);     //绘制地图，输入color表示蛇头颜色
void Init();                            //初始化游戏数据
void AddFood(int row, int col);//添加食物
char ChangeDir(char SnakeDir_t);//修改蛇方向，输入SnakeDir_t用于实现暂停功能，返回SnakeDir_t为蛇暂停前移动方向
int ChangeColor(int color); //修改蛇头颜色,用于后续积分模式，输入color控制蛇头颜色，返回改色需要的积分
void ChangeSpeed();          //随积分调整移动速度
int JudgeFood();                 //判断是否吃到食物，是返回1，否返回0
void JudgeWall(int row, int col);                //判断是否撞墙
int JudgeSnake(int row, int col);               //判断是否撞自身，是返回1，否返回0
int JudgeSnake_2(int row, int col);            //判断是否撞自身，是返回1，否返回0(无敌模式专用
void JudgeMalloc(Snake* p);       //判断malloc申请Snake*类型的内存空间是否成功
int MoveMode_0();                     //普通模式移动方式，返回当前状态，暂停为0，移动为1
int MoveMode_1_2();                  //穿墙及无敌模式移动方式，返回当前状态，暂停为0，移动为1
void Move(int row, int col);         //移动蛇
void GameOver();                       //游戏结束动画（仅失败）

/*********用户登入**********/
//int compDec();                 //用户删除
//int compInc();                  //用户添加
//void Login();                    //用户登陆
//void registers();                //用户注册
//void SaveData();               //保存游戏记录

/*********人工智障*********/
void DrawMap_AI(int color, int row, int col);
void Move_AI(int row, int col);
void Run_AI(int row, int col);
int JudgeSnake_AI(int row, int col);
void SwapNode(int index1, int index2);  //交换节点指针
void AdjustHeap(int index);                   //调整堆
void InsertOpentable(int x, int y, pAStarNode curr_node, pAStarNode end_node, int w);//输入当前位置(x,y)，需要的判断节点，节点的终点，移动的权值w
int FindWay(int x, int y, int row, int col);//输入终点坐标，耗时；寻找路径，同时反映到蛇的运动
void Wander();                                     //让蛇随机走一步
void GetNeightbors(pAStarNode cur_node, pAStarNode end_node);
void Translate(int top, int row, int col); //将储存在pack_stack栈里的路径数据翻译为蛇能够理解的数据；会在控制台输出每次寻找路径
//Run_AI()和Wander()逻辑还需要优化


/*********具体函数**********/
int main()
{
	Go();                     //初始界面
	//游戏界面
	if (mode == 3)     //AISNAKE
	{
		Run_AI(ROW_AI, COL_AI);
	}
	else                     //普通模式
	{
		Run(ROW, COL);                  
	}
	closegraph();
	//printf("你的最终得分为%d!\n", score);//仅作ESC键退出图形窗口后操作结果示意
	return 0;
}

void Go()
{
	/*******进入初始界面*******/
	int n = 120;                                      //用于Chose()正确指示用户所选模式 
	Music(1);
	loadimage(&img[0], L"背景.png");  //初始化图片
	loadimage(&img[1], L"food.png");
	initgraph(640, 480);                        //初始界面大小
	Start();
	outtextxy(260, 120, L"-->");            //用于展示所选模式
	Chose(n);
	/*******进入游戏界面*******/
	Init();
}
void Music(int n)//实现音乐的暂停与播放
{
	switch (n)
	{
	case 1:
		if (mciSendString(L"open music.mp3 alias bgm", 0, 0, 0))//打开音乐
		{
			MessageBox(GetHWnd(), L"打开音乐文件music.mp3出错！", L"ERROR", MB_OK);
			exit(1);
		}
	case 2:
		mciSendString(L"play bgm repeat", 0, 0, 0);                 //播放音乐
		break;
	case 3:
		mciSendString(L"pause bgm", 0, 0, 0);                          //暂停播放
		//mciSendString(L"close bgm", 0,0,0);                             //停止播放
		break;
	}
}
void Start()//可以用个变量定义初始高度，实现窗口自适应
{
	cleardevice();			                    //刷新屏幕
	putimage(0, 0, &img[0]);            //设置背景图片
	
	setbkmode(TRANSPARENT);	    //设置字体背景色为透明
	settextcolor(RED);                   	//设置字体颜色
	/***************游戏规则说明***************/
	outtextxy(265, 40, L"欢迎来到贪吃蛇");
	settextcolor(RGB(80, 80, 80));
	outtextxy(560, 460, L"V1.0 by yzk");
	settextcolor(BLACK);
	outtextxy(290, 80, L"功能选择:");
	outtextxy(280, 120, L" 1.普通模式");
	outtextxy(280, 160, L" 2.穿墙模式");
	outtextxy(280, 200, L" 3.无敌模式");
	outtextxy(280, 240, L" 4.弱AI模式*Beta");
	outtextxy(180, 270, L"方向键 ↑, ↓ 选择模式，Enter键进入游戏");
	outtextxy(180, 300, L"字母键 W,S,A,D / 方向键 ↑, ↓, ←, → 控制方向");
	outtextxy(240, 340, L"游戏提示：");
	outtextxy(260, 360, L"         Space为暂停");
	outtextxy(260, 385, L"         ESC为强制退出");
	outtextxy(260, 410, L"         长按方向键可加速");
	outtextxy(260, 435, L"         当前界面←键暂停音乐，→键播放");
}
void Chose(int n)
{
	while (1)
	{
		switch (_getch())
		{
		case KEY_UP:      //方向上
			Start();
			if (n == 120) { //在最高点则回到底部
				n = 240;
			}
			else
			{
				n -= 40;
			}
			outtextxy(260, n, L"-->");
			switch (n)
			{
			case 120:
				mode = 0; break;
			case 160:
				mode = 1; break;
			case 200:
				mode = 2; break;
			case 240:
				mode = 3; break;
			}
			break;
		case KEY_DOWN:      //方向下
			Start();
			if (n == 240) {       //在最低点则回到顶部
				n = 120;
			}
			else
			{
				n += 40;
			}
			outtextxy(260, n, L"-->");
			switch (n)
			{
			case 120:
				mode = 0; break;
			case 160:
				mode = 1; break;
			case 200:
				mode = 2; break;
			case 240:
				mode = 3; break;
			}
			break;
		case KEY_RIGHT:
			Music(2); break;
		case KEY_LEFT:
			Music(3); break;
		case KEY_ENTER:
			return;
		}
	}
}
void AddFood(int row,int col)//逻辑不太合理，需要改进？
{
	food = (COORD*)malloc(sizeof(COORD));
	if (!food)
	{
		MessageBox(GetHWnd(), L"内存分配失败，请重试程序", L"SORRY", MB_OK);
		exit(0);
	}
	food->X = rand() % (col - 2) + 1;    //确保食物与墙不重叠
	food->Y = rand() % (row - 2) + 1;  //产生[m,n]随机数，int num=rand()%(n-m+1)+m;
	phead = head;
	while (phead->next != NULL)	       //判断蛇与食物是否重合；这里判断phead->next != NULL：1.上面程序确保了phead不会为NULL；
	{                                                      //2.当食物出现在尾节点而下一步尾节点会移开，所以该点食物的出现应当是合理的
		if (phead->body.X == food->X && phead->body.Y == food->Y)
		{
			free(food);                 //若提示food内存未初始化是因为这里的free()，实际不会出现该问题
			AddFood(row, col);
			break;                        //防止出递归时phead = nullptr，导致后续程序运行出错
		}
		phead = phead->next;//这里会出现调用phead = nullptr是因为递归的原因，若调用递归则必出现该问题，加入break可以避免
	}
	//如果设定了空的链表头节点，则可以改写为如下简单形式
	//phead = head;
	//while (phead->next != NULL)
	//{
	//	phead = phead->next;
	//	if (phead->body.X == food->X && phead->body.Y == food->Y)
	//	{
	//		food->X = rand() % (COL - 2) + 1;
	//		food->Y = rand() % (ROW - 2) + 1;
	//		phead = head;
	//	}
	//}
}
void Init()
{
	int len = 5;                                          //蛇初始长度5
	srand((unsigned int)time(NULL));      //生成随机种子用于随机生成食物
	setbkcolor(WHITE);                            //设置游戏界面背景颜色
	//初始化蛇
	tail = (Snake*)malloc(sizeof(Snake)); //头插法
	JudgeMalloc(tail);
	tail->body.X = 3;                                //初始化蛇位置
	tail->body.Y = 3;
	tail->next = NULL;
	for (int i = 1; i < len; i++)                   //设置蛇初始长度为5
	{
		head = (Snake*)malloc(sizeof(Snake));
		JudgeMalloc(head);
		head->next = tail;
		head->body.X = 3 + i;
		head->body.Y = 3;
		tail = head;
	}
}

void Run(int row, int col)
{
	ULONGLONG t1= 0, t2;             //定义两个时间用于控制蛇移动速度
	char SnakeDir_t = 'D';               //移动方向temp，用于ChangeDir()中实现暂停功能
	int color = 0;                             //记录蛇头颜色
	color = ChangeColor(color);
	AddFood(row, col);
	while (1)
	{
		t2 = GetTickCount64();
		DrawMap(color, row, col);
		if (_kbhit() && SnakeDir != KEY_SPACE)//_kbhit()判断键盘是否有输入；实现长按方向键加速
		{//思考了很久移动延时的问题，还以为是逻辑问题，最终发现问题出在了方向键的_getch()返回值上(在其帮助文档有注明)
         //按一次方向键得两个字符信号，调用_getch()第一次返回值为0或0xE0，第二次才是其对应ascll码（因为该码与其它按键重复）
			SnakeDir_t = ChangeDir(SnakeDir_t);
			Move(row, col);
			t2 = GetTickCount64();
			t1 = t2;
		}
		else if (SnakeDir == KEY_SPACE)//用于实现恢复暂停
		{
			SnakeDir_t = ChangeDir(SnakeDir_t);
		}
		else if (t2 - t1 > speed && SnakeDir != KEY_SPACE)//控制🐍速度，越大越慢
		{
			Move(row, col);
			t1 = t2;
		}
	}
}
void DrawMap(int color, int row, int col)
{
	BeginBatchDraw();                                   //开始绘图，绘制完整幅画面显示再，可避免闪烁
	setbkcolor(WHITE);                                  //设置背景色为白色
	//putimage(0, 0, &img[0]);                        //设置图片背景
	settextcolor(RGB(240, 0, 0));                   //红字
	cleardevice();		                                    //清屏
	WCHAR arr[14];		                                //保存成绩
	putimage(80, 3, &img[1]);                      //食物图案
	wsprintf(arr, L"积分：%d    ", score);      //将成绩格式化输出到字符串arr中 
	outtextxy(0, 0, arr);			                       //显示成绩
	wsprintf(arr, L"速度级别：%d", 9 - speed/30);
	outtextxy(200, 0, arr);                            //显示速度级别
	settextcolor(RGB(160, 160, 160));         //淡灰字
	switch (mode)                                       //显示所选模式
	{
	case 0:outtextxy(575, 0, L"普通模式"); break;
	case 1:outtextxy(575, 0, L"穿墙模式"); break;
	case 2:outtextxy(575, 0, L"无敌模式"); break;
	//case 3:outtextxy(575, 0, L"弱AI模式"); break;
	}
	//绘制墙，修改该段及JudgeWall可实现不同障碍，甚至是移动的墙，单向墙（判断前两节蛇即可）等
	//根据积分改变墙分布，比如可以将墙也定义为和蛇一样的结构体，虽然链表顺序读取性能不好，但在这种规模上倒也应该无伤大雅。
	setlinecolor(BLACK);
	setfillcolor(RGB(230, 230, 230));	   //深灰色
	for (int i = 0; i < row; i++)           //每一行的 第一个 和 最后一个 是墙
	{
		fillrectangle(0, i * 10 + 20, 10, i * 10 + 30);
		fillrectangle((col - 1) * 10, i * 10 + 20, (col - 1) * 10 + 10, i * 10 + 30);
	}

	for (int j = 1; j < col - 1; j++)	     //每一列的 第一个 和 倒数第一个 是墙
	{
		fillrectangle(j * 10, 20, j * 10 + 10, 30);
		fillrectangle(j * 10, (row - 1) * 10 + 20, j * 10 + 10, (row - 1) * 10 + 30);
	}
	//绘制蛇，设置10像素为一帧
	tail = head;
	setlinecolor(RGB(0, 245, 255));		//淡蓝色框
	switch (color)                                  //绘制蛇头，预留7种颜色
	{
	case 0:
		setfillcolor(RGB(255, 0, 0));		    //红 255 0 0
		break;
	case 1:
		setfillcolor(RGB(255, 165, 0));		//橙  255 165 0 
		break;
	case 2:
		setfillcolor(RGB(255, 255, 0));		//黄  255 255 0
		break;
	case 3:
		setfillcolor(RGB(0, 255, 0));		    //绿  0, 255, 0
		break;
	case 4:
		setfillcolor(RGB(0, 255, 255));		//青  0 255 255
		break;
	case 5:
		setfillcolor(RGB(0, 0, 255));		    //蓝  0 0 255
		break;
	case 6:
		setfillcolor(RGB(160, 32, 240));	//紫  160 32 240
		break;
	default:
		break;
	}
	fillrectangle(tail->body.X * 10, tail->body.Y * 10 + 20, tail->body.X * 10 + 10, tail->body.Y * 10 + 30);
	tail = tail->next;
	while (tail->next != NULL)
	{
		setlinecolor(RGB(0, 245, 255));		//淡蓝色
		setfillcolor(WHITE);
		fillrectangle(tail->body.X * 10, tail->body.Y * 10 + 20, tail->body.X * 10 + 10, tail->body.Y * 10 + 30);
		tail = tail->next;
	}
	//蛇尾
	setlinecolor(RGB(0, 245, 255));		//淡蓝色
	setfillcolor(BLUE);
	fillrectangle(tail->body.X * 10, tail->body.Y * 10 + 20, tail->body.X * 10 + 10, tail->body.Y * 10 + 30);
	//绘制食物
	putimage(food->X * 10, food->Y * 10 + 20, &img[1]);//食物图案
	//setfillcolor(RGB(255, 0, 0));		    //红 255 0 0
	//fillrectangle(food->X * 10, food->Y * 10 + 20, food->X * 10 + 10, food->Y * 10 + 30);//方框
	EndBatchDraw();                                 //结束绘画
}

char ChangeDir(char SnakeDir_t)
{
	switch (_getch())//蛇不能后退
	{
	case 0xE0:
	case 0:
		switch (_getch())
		{
		case KEY_LEFT:
			if (SnakeDir != 'D' && SnakeDir != KEY_SPACE) SnakeDir = 'A';
			break;
		case KEY_RIGHT:
			if (SnakeDir != 'A' && SnakeDir != KEY_SPACE) SnakeDir = 'D';
			break;
		case KEY_UP:
			if (SnakeDir != 'S' && SnakeDir != KEY_SPACE) SnakeDir = 'W';
			break;
		case KEY_DOWN:
			if (SnakeDir != 'W' && SnakeDir != KEY_SPACE) SnakeDir = 'S';
			break;
		default:
			break;
		}break;
	case'A':
	case'a':
		if (SnakeDir != 'D' && SnakeDir != KEY_SPACE) SnakeDir = 'A';
		break;
	case'D':
	case'd':
		if (SnakeDir != 'A' && SnakeDir != KEY_SPACE) SnakeDir = 'D';
		break;
	case'W':
	case'w':
		if (SnakeDir != 'S' && SnakeDir != KEY_SPACE) SnakeDir = 'W';
		break;
	case'S':
	case's':
		if (SnakeDir != 'W' && SnakeDir != KEY_SPACE) SnakeDir = 'S';
		break;
	case KEY_SPACE:
		if (SnakeDir != KEY_SPACE) {
			SnakeDir_t = SnakeDir;
			SnakeDir = KEY_SPACE;        //暂停
		}
		else SnakeDir = SnakeDir_t;
		break;
	case KEY_ESC:
		SnakeDir = KEY_ESC;                 //退出
		break;
	default:
		break;
	}
	return SnakeDir_t;
}
int ChangeColor(int color)//期望整合进控制颜色的方式
{
	//return rand() % 7;
	return 3;//返回需要减少的积分
}
void ChangeSpeed()
{
		if (score < 80 && score % 10 == 0 && speed > 30)//根据积分增加(10分一档)难度，考虑GetTickCount64()函数精度，保险起见规定speed不得小于30
		{
			speed -= 30;
		}
		else if (score % 10 ==0 && speed < 150)                    //在蛇较长时降低速度，提高游戏体验
		{
			speed += 30;
		}
}

int JudgeFood()
{
	tail = head;
	Snake* pphead;
	if (head->body.X == food->X && head->body.Y == food->Y)
	{
		score++;
		pphead = (Snake*)malloc(sizeof(Snake));
		JudgeMalloc(pphead);
		pphead->body.X = food->X;
		pphead->body.Y = food->Y;
		//pphead->next = head;
		//head = pphead;//这里之所以加在链尾而不是链头，是因为链头与食物位置已经重叠；而move()可以改变链尾为蛇尾，即去蛇尾操作，在吃食物之后实则为去链尾，从而再次使得链尾即蛇尾
		pphead->next = NULL;
		while (tail->next != NULL)      //往链表尾部添加新结点
		{
			tail = tail->next;
		}
		tail->next = pphead;
		//Move();//启用该Move()在蛇吃到食物时蛇头不会消失一下，个人认为消失一下给用户反馈更好；后来偶然发现在吃食物的瞬间暂停，会出现撞到自身的误判，而启用后不会，原因在于changedir后snakedir=key_space而实际蛇已经移动，蛇头与新加蛇尾即食物位置重叠了--解决方法：在move函数中将snakedir=key_space的判断提到judgesnake()之前即可；后来对move_0_1_2函数添加了返回值处理就不需要顾虑了
		return 1;
	}
	return 0;
}
void JudgeWall(int row, int col)
{
	if (head->body.X == 0 || head->body.X == col - 1 ||
		head->body.Y == 0 || head->body.Y == row - 1)
	{
		head = head->next;
		DrawMap(6, row, col);          //蛇头显示为紫色
		GameOver();
		MessageBox(GetHWnd(), L"你撞墙了，游戏结束", L"SORRY", MB_OK);
		exit(0);
	}
}
int JudgeSnake(int row, int col)
{
	phead = head->next;     //蛇头不可能和蛇头相撞
	while (phead != NULL)
	{
		if ((phead->body.X == head->body.X) &&
			(phead->body.Y == head->body.Y))
		{
			head = head->next;
			DrawMap(6, row, col);          //蛇头显示为紫色
			GameOver();
			MessageBox(GetHWnd(), L"你撞到自己了，游戏结束", L"SORRY", MB_OK);
			exit(0);
		}
		phead = phead->next;
	}
	return 1;
}
int JudgeSnake_2(int row, int col)
{
	int n = 0;
	phead = head->next;                     //蛇头不可能和蛇头相撞
	/*for (int i = 0; i < 8; i++)//当蛇长度小于9时，蛇不可能无路可走。考虑不一定能优化性能，先注释了
	{
		if (phead)
		{
			phead = phead->next;
		}
		else
		{
			break;
		}
	}*/
	while (phead != NULL)                   //判断前后左右是否是蛇身，是则无路可走
	{
		if ((phead->body.X == head->next->body.X + 1) && (phead->body.Y == head->next->body.Y)
			|| (phead->body.X == head->next->body.X - 1) && (phead->body.Y == head->next->body.Y)
			|| (phead->body.X == head->next->body.X) && (phead->body.Y == head->next->body.Y - 1)
			|| (phead->body.X == head->next->body.X) && (phead->body.Y == head->next->body.Y + 1))//这里选择对head->next节点进行判断，是为了避免因未显示的蛇头（即下一帧即将打印的蛇头）进入前后左右都有蛇身的位置造成游戏错误结束
			n++;
		phead = phead->next;
	}
	if (n == 4)
	{
		head = head->next;
		DrawMap(6, row, col);                              //蛇头显示为紫色
		GameOver();
		MessageBox(GetHWnd(), L"你已经无路可走了，游戏结束", L"SORRY", MB_OK);
		exit(0);
	}
	phead = head->next;                    //蛇头不可能和蛇头相撞
	while (phead != NULL)                  //如果蛇头撞到蛇身则停止移动
	{
		if ((phead->body.X == head->body.X) &&
			phead->body.Y == head->body.Y)
		{
			/*phead = head;
			head = phead->next;*/
			head = head->next;            //回溯？
			return 0;
		}
		phead = phead->next;
	}
	return 1;
}
void JudgeMalloc(Snake* p)
{
	if (!p)
	{
		MessageBox(GetHWnd(), L"内存分配失败，请重试程序", L"SORRY", MB_OK);
		exit(1);
	}
}

int MoveMode_0()
{
	if (SnakeDir == KEY_SPACE)//暂停
	{
		return 0;
	}
	Snake* pphead = (Snake*)malloc(sizeof(Snake));
	JudgeMalloc(pphead);
	switch (SnakeDir)
	{
	case 'A':
		pphead->body.Y = head->body.Y;
		pphead->body.X = head->body.X - 1;
		break;
	case 'D':
		pphead->body.Y = head->body.Y;
		pphead->body.X = head->body.X + 1;
		break;
	case 'W':
		pphead->body.Y = head->body.Y - 1;
		pphead->body.X = head->body.X;
		break;
	case 'S':
		pphead->body.Y = head->body.Y + 1;
		pphead->body.X = head->body.X;
		break;
	case KEY_ESC:
		MessageBox(GetHWnd(), L"你已退出，游戏结束", L"EXIT", MB_OK);
		exit(0);
	}
	pphead->next = head;
	head = pphead;
	return 1;
}
int MoveMode_1_2()
{
	if (SnakeDir == KEY_SPACE)//暂停
	{
		return 0;
	}
	Snake* pphead = (Snake*)malloc(sizeof(Snake));
	JudgeMalloc(pphead);
	switch (SnakeDir)
	{
	case 'A':
		pphead->body.Y = head->body.Y;
		pphead->body.X = head->body.X - 1; 
		if (pphead->body.X == 0)
		{
			pphead->body.X = COL - 2;
		}
		break;
	case 'D':
		pphead->body.Y = head->body.Y;
		pphead->body.X = head->body.X + 1;
		if (pphead->body.X == COL - 1)
		{
			pphead->body.X = 1;
		}
		break;
	case 'W':
		pphead->body.Y = head->body.Y - 1;
		pphead->body.X = head->body.X;
		if (pphead->body.Y == 0)
		{
			pphead->body.Y = ROW - 2;
		}
		break;
	case 'S':
		pphead->body.Y = head->body.Y + 1;
		pphead->body.X = head->body.X;
		if (pphead->body.Y == ROW - 1)
		{
			pphead->body.Y = 1;
		}
		break;
	case KEY_ESC:
		MessageBox(GetHWnd(), L"你已退出，游戏结束", L"EXIT", MB_OK);
		exit(0);
	}
	pphead->next = head;
	head = pphead;
	return 1;
}
void Move(int row, int col)
{
	if (mode)
	{
		if (MoveMode_1_2())
		{
			switch (mode)
			{
			case 1:
				if (JudgeSnake(row, col))//SnakeDir != KEY_SPACE && JudgeSnake())
				{
					tail = head;
					while (tail->next->next != NULL)//判断tail等不为空
					{
						tail = tail->next;
					}
					free(tail->next);
					tail->next = NULL;                    //去掉最后一节蛇节点
					if (JudgeFood())
					{
						AddFood(row, col);
						ChangeSpeed();
					}
				}break;
			case 2:
				if (JudgeSnake_2(row, col))
				{
					tail = head;
					while (tail->next->next != NULL)//要求链表长度>=2
					{
						tail = tail->next;
					}
					free(tail->next);
					tail->next = NULL;                     //去掉最后一节蛇节点
					if (JudgeFood())
					{
						AddFood(row, col);
						ChangeSpeed();
					}
				}break;
			default:
				break;
			}
		}
	}
	else
	{
		if (MoveMode_0())
		{
			JudgeWall(row, col);
			if (JudgeSnake(row, col))
			{
				//去掉最后一节蛇节点
				tail = head;
				while (tail->next->next != NULL)
				{
					tail = tail->next;
				}
				free(tail->next);
				tail->next = NULL;
				if (JudgeFood())
				{
					AddFood(row, col);
					ChangeSpeed();
				}
			}
		}
	}
	if (score == (COL - 1) * (ROW - 1) - 5)
	{
		MessageBox(GetHWnd(), L"恭喜你成功了！", L"VICTORY", MB_OK);
		exit(0);
	}
}

void GameOver()
{
	phead = head->next;
	while (phead->next != NULL)
	{
		BeginBatchDraw();
		setlinecolor(RGB(0, 245, 255));
		setfillcolor(RGB(255, 0, 0));
		fillrectangle(phead->body.X * 10, phead->body.Y * 10 + 20, phead->body.X * 10 + 10, phead->body.Y * 10 + 30);
		phead = phead->next;
		EndBatchDraw();
		Sleep(60);//预期实现当蛇身越长，停顿越小。
	}
	BeginBatchDraw();      //蛇尾
	setlinecolor(RGB(0, 245, 255));
	setfillcolor(RGB(0, 0, 0));
	fillrectangle(phead->body.X * 10, phead->body.Y * 10 + 20, phead->body.X * 10 + 10, phead->body.Y * 10 + 30);
	EndBatchDraw();
}

/********AISnake******/
void DrawMap_AI(int color, int row, int col)
{
	end = time(NULL);
	BeginBatchDraw();                                   //开始绘图，绘制完整幅画面显示再，可避免闪烁
	setbkcolor(WHITE);                                  //设置背景色为白色
	//putimage(0, 0, &img[0]);                        //设置图片背景
	settextcolor(RGB(240, 0, 0));                   //红字
	cleardevice();		                                    //清屏
	WCHAR arr[14];		                                //保存成绩
	putimage(80, 3, &img[1]);                      //食物图案
	wsprintf(arr, L"积分：%d", score);      //将成绩格式化输出到字符串arr中 
	outtextxy(0, 0, arr);			                       //显示成绩
	wsprintf(arr, L"用时：%ds", (int)(end - start));
	outtextxy(200, 0, arr);                            //显示速度级别
	settextcolor(RGB(160, 160, 160));         //淡灰字
	outtextxy(575, 0, L"弱AI模式");
	//绘制墙，修改该段及JudgeWall可实现不同障碍，甚至是移动的墙，单向墙（判断前两节蛇即可）等
	//根据积分改变墙分布，比如可以将墙也定义为和蛇一样的结构体，虽然链表顺序读取性能不好，但在这种规模上倒也应该无伤大雅。
	setlinecolor(BLACK);
	setfillcolor(RGB(230, 230, 230));	   //深灰色
	for (int i = 0; i < ROW_AI; i++)           //每一行的 第一个 和 最后一个 是墙
	{
		fillrectangle(0, i * 10 + 20, 10, i * 10 + 30);
		fillrectangle((COL_AI - 1) * 10, i * 10 + 20, (COL_AI - 1) * 10 + 10, i * 10 + 30);
	}

	for (int j = 1; j < COL_AI - 1; j++)	     //每一列的 第一个 和 倒数第一个 是墙
	{
		fillrectangle(j * 10, 20, j * 10 + 10, 30);
		fillrectangle(j * 10, (ROW_AI - 1) * 10 + 20, j * 10 + 10, (ROW_AI - 1) * 10 + 30);
	}
	//绘制蛇，设置10像素为一帧
	tail = head;
	setlinecolor(RGB(0, 245, 255));		//淡蓝色框
	switch (color)                                  //绘制蛇头，预留7种颜色
	{
	case 0:
		setfillcolor(RGB(255, 0, 0));		    //红 255 0 0
		break;
	case 1:
		setfillcolor(RGB(255, 165, 0));		//橙  255 165 0 
		break;
	case 2:
		setfillcolor(RGB(255, 255, 0));		//黄  255 255 0
		break;
	case 3:
		setfillcolor(RGB(0, 255, 0));		    //绿  0, 255, 0
		break;
	case 4:
		setfillcolor(RGB(0, 255, 255));		//青  0 255 255
		break;
	case 5:
		setfillcolor(RGB(0, 0, 255));		    //蓝  0 0 255
		break;
	case 6:
		setfillcolor(RGB(160, 32, 240));	//紫  160 32 240
		break;
	default:
		break;
	}
	fillrectangle(tail->body.X * 10, tail->body.Y * 10 + 20, tail->body.X * 10 + 10, tail->body.Y * 10 + 30);
	tail = tail->next;
	while (tail->next != NULL)
	{
		setlinecolor(RGB(0, 245, 255));		//淡蓝色
		setfillcolor(WHITE);
		fillrectangle(tail->body.X * 10, tail->body.Y * 10 + 20, tail->body.X * 10 + 10, tail->body.Y * 10 + 30);
		tail = tail->next;
	}
	//蛇尾
	setlinecolor(RGB(0, 245, 255));		//淡蓝色
	setfillcolor(BLUE);
	fillrectangle(tail->body.X * 10, tail->body.Y * 10 + 20, tail->body.X * 10 + 10, tail->body.Y * 10 + 30);
	//绘制食物
	putimage(food->X * 10, food->Y * 10 + 20, &img[1]);//食物图案
	EndBatchDraw();                                 //结束绘画
}
int JudgeSnake_AI(int row, int col)
{
	phead = head->next;     //蛇头不可能和蛇头相撞
	while (phead != NULL)
	{
		if ((phead->body.X == head->body.X) &&
			(phead->body.Y == head->body.Y))
		{
			head = head->next;
			DrawMap_AI(6, row, col);          //蛇头显示为紫色
			GameOver();
			MessageBox(GetHWnd(), L"你撞到自己了，游戏结束", L"SORRY", MB_OK);
			exit(0);
		}
		phead = phead->next;
	}
	return 1;
}
void Move_AI(int row, int col)
{
	if (MoveMode_0())
	{
		JudgeWall(row, col);
		if (JudgeSnake_AI(row, col))
		{
			//去掉最后一节蛇节点
			tail = head;
			while (tail->next->next != NULL)
			{
				tail = tail->next;
			}
			free(tail->next);
			tail->next = NULL;
			if (JudgeFood())
			{
				AddFood(row,col);
			}
		}
	}
	if (score == (COL_AI - 1) * (ROW_AI - 1) - 5)
	{
		MessageBox(GetHWnd(), L"恭喜你成功了！", L"VICTORY", MB_OK);
		exit(0);
	}
}
void Wander()
{
	int n, m;
A:
	n = 1;
	m = rand() % (4) + 1;
	switch (m)
	{
	case 1:
		//如果不能就随机走/非死路
		phead = head->next;
		while (phead != NULL)//预判下一步是否会撞到自己，但下下步就不能保证了
		{
			if ((head->body.X + 1 == phead->body.X && head->body.Y == phead->body.Y) || head->body.X + 1 == COL_AI - 1)
			{
				n = 0;
				break;
			}
			phead = phead->next;
		}
		if (n)
		{
			SnakeDir = 'D';
		}
		else
		{
			goto A;
		}
		break;
	case 2:
		phead = head->next;
		while (phead != NULL)
		{
			if ((head->body.X - 1 == phead->body.X && head->body.Y == phead->body.Y) || head->body.X - 1 == 0)
			{
				n = 0;
				break;
			}
			phead = phead->next;
		}
		if (n)
		{
			SnakeDir = 'A';
		}
		else
		{
			goto A;
		}
		break;
	case 3:
		phead = head->next;
		while (phead != NULL)
		{
			if ((head->body.X == phead->body.X && head->body.Y - 1 == phead->body.Y) || head->body.Y - 1 == 0)
			{
				n = 0;
				break;
			}
			phead = phead->next;
		}
		if (n)
		{
			SnakeDir = 'W';
		}
		else
		{
			goto A;
		}
		break;
	case 4:
		phead = head->next;
		while (phead != NULL)
		{
			if ((head->body.X == phead->body.X && head->body.Y + 1 == phead->body.Y) || head->body.Y + 1 == ROW_AI - 1)
			{
				n = 0;
				break;
			}
			phead = phead->next;
		}
		if (n)
		{
			SnakeDir = 'S';
		}
		else
		{
			goto A;
		}
		break;
	}
}
void Run_AI(int row, int col)
{
	initgraph(640, 480);             //初始界面大小
	char SnakeDir_t = 'D';        //移动方向temp，用于ChangeDir()中实现暂停功能
	int color = 3;                     //记录蛇头颜色
	int flag = 1;
	Init();
	AddFood(row, col);
	start = time(NULL);
	while (1)
	{
		DrawMap_AI(color, row, col);
		if (!FindWay(food->X, food->Y, row, col))
		{
			//如果能找到尾巴就找尾巴
			tail = head;
			while (tail->next->next != NULL)//确保其不为空；这里为倒数第二节蛇，是因为刚吃到食物又没进行Move_AI()则蛇尾为刚吃的食物位置，而我们需要查找的蛇尾在倒数第二个位置
			{
				tail = tail->next;
			}
			//去掉最后一节蛇节点
			free(tail->next);
			tail->next = NULL;
			if (!FindWay(tail->body.X, tail->body.Y, row, col))//至少预判2次?
			{
				Wander();
				Move_AI(row, col);
				DrawMap_AI(color, row, col);
				Sleep(120);
			}
		}
	}
	closegraph();
}

//ASTAR
/***堆排序**用于实现最短路径回溯***/
// 交换两个元素在open_table中的前后关系
void SwapNode(int index1, int index2)
{
	pAStarNode tmp = open_table[index1];
	open_table[index1] = open_table[index2];
	open_table[index2] = tmp;
}

// 将opentable表调整为小根堆排列，堆排序试用于较大数据集
void AdjustHeap(int index)
{
	int cur = index;
	int child = cur * 2 + 1;    //首先得到左孩子( 下标从0开始，所有做孩子是cur*2+1 )
	int parent = (cur - 1) / 2;//整除，得到双亲

	if (index < 0 || index >= open_count)//若为非法位置编号
	{
		return;
	}
	//从cur位置往下调整( 比较左右孩子和双亲 )，相当于排序前初始化堆
	while (child < open_count)
	{   
		//比较左右孩子f值大小，选择较小者
		if (child + 1 < open_count && open_table[child]->g + open_table[child]->h > open_table[child + 1]->g + open_table[child + 1]->h)
		{
			child++;
		}
		//比较cur与child，若前者小则符合，若前者大则交换
		if (open_table[cur]->g + open_table[cur]->h <= open_table[child]->g + open_table[child]->h)
		{
			break;
		}
		else
		{
			SwapNode(child, cur);    //交换节点
			cur = child;                    //将指向从当前节点移至其较小孩子节点
			child = cur * 2 + 1;         //再次指向左孩子
		}
	}
    //若进行过向下调整
	if (cur != index)
	{
		return;
	}

	//向上调整
	while (cur != 0)
	{
		if (open_table[cur]->g + open_table[cur]->h >= open_table[parent]->g + open_table[parent]->h)
		{
			//若双亲节点值大
			break;
		}
		else
		{
			SwapNode(cur,parent);    //交换节点
			cur = parent;                   //将指向从当前节点移至其双亲
			parent = (cur - 1) / 2;       //再次指向其双亲
		}
	}
}

//判断邻居点是否可以进入open_table表
void InsertOpentable(int x, int y, pAStarNode cur_node, pAStarNode end_node, int w)
{
	int i;
	if (map_maze[x][y].style != BARRIER) //若该点不代表障碍物
	{
		if (!map_maze[x][y].in_closetable)  //若不在close_table表中
		{
			if (map_maze[x][y].in_opentable)//若在open_table表中
			{
				//判断是否为更优化路径
				if (map_maze[x][y].g > cur_node->g + w)
				{
					//如果更优化，将该点置为查找节点
					map_maze[x][y].g = cur_node->g + w;
					map_maze[x][y].parent = cur_node;
                    //找到查找点在open_table中位置
					for (i = 0; i < open_count; i++)
					{
						if (open_table[i]->x == map_maze[x][y].x && open_table[i]->y == map_maze[x][y].y)
						{
							break;
						}
					}
					AdjustHeap(i);//调整各点
				}
			}
			else//不在open_tablde中，则调整后加入
			{
				map_maze[x][y].g = cur_node->g + w;
				map_maze[x][y].h = abs(end_node->x - x) + abs(end_node->y - y);//曼哈顿距离
				map_maze[x][y].parent = cur_node;
				map_maze[x][y].in_opentable = 1;
				open_table[open_count] = &(map_maze[x][y]);
				open_count++;
			}
		}
	}
}

//查找上下左右4个邻居
void GetNeightbors(pAStarNode cur_node, pAStarNode end_node)
{
	int x = cur_node->x;
	int y = cur_node->y;

	//对4个邻居节点进行处理，判断是否需要加入open_table
	if ((x + 1) >= 0 && (x + 1) < COL_AI - 2 && y >= 0 && y < COL_AI - 2)
	{
		InsertOpentable(x + 1, y, cur_node, end_node, 1);
	}

	if ((x - 1) >= 0 && (x - 1) < COL_AI - 2 && y >= 0 && y < COL_AI - 2)
	{
		InsertOpentable(x - 1, y, cur_node, end_node, 1);
	}

	if (x >= 0 && x < COL_AI - 2 && (y + 1) >= 0 && (y + 1) < COL_AI - 2)
	{
		InsertOpentable(x, y + 1, cur_node, end_node, 1);
	}

	if (x >= 0 && x < COL_AI - 2 && (y - 1) >= 0 && (y - 1) < COL_AI - 2)
	{
		InsertOpentable(x, y - 1, cur_node, end_node, 1);
	}
}

int FindWay(int x, int y, int row, int col)
{
	//地图数组定义
	AStarNode* start_node = NULL;	    // 起始点
	AStarNode* end_node = NULL;			// 结束点
	AStarNode* cur_node;			            // 当前点
	int maze[ROW_AI - 2][COL_AI - 2] = { 0 };
	int i, j;
	phead = head->next;
	while (phead != NULL)//要放在给起点赋值之前，因为在吃到食物时，食物位置将赋值给尾节点，导致起点被覆盖
	{
		maze[(phead->body.Y) - 1][(phead->body.X) - 1] = BARRIER;
		phead = phead->next;
	}
	maze[y - 1][x - 1] = ENDNODE;
	maze[(head->body.Y) - 1][(head->body.X) - 1] = STARTNODE;

	//初始化各点数据
	for (i = 0; i < ROW_AI - 2; ++i)
	{
		for (j = 0; j < COL_AI - 2; ++j)
		{
			map_maze[i][j].g = 0;
			map_maze[i][j].h = 0;
			map_maze[i][j].in_closetable = 0;
			map_maze[i][j].in_opentable = 0;
			map_maze[i][j].style = maze[i][j];
			map_maze[i][j].x = i;
			map_maze[i][j].y = j;
			map_maze[i][j].parent = NULL;

			if (map_maze[i][j].style == STARTNODE)	   // 起点
			{
				start_node = &(map_maze[i][j]);
			}
			else if (map_maze[i][j].style == ENDNODE)	// 终点
			{
				end_node = &(map_maze[i][j]);
			}
		}
	}
	open_count = 0;
	close_count = 0;
	top = -1;//初始化top
	//用ASTAR算法得到路径
	//初始化起点
	open_table[open_count++] = start_node;			// 起始点加入open表
	start_node->in_opentable = 1;	                		// 加入open表
	start_node->g = 0;
	start_node->h = abs(end_node->x - start_node->x) + abs(end_node->y - start_node->y);
	start_node->parent = NULL;
	//开始寻找路径
	while (1)
	{
		if (open_count < 0)//若open_table中已经没有节点
		{
			return 0;
		}
		cur_node = open_table[0];		                        //open表的第一个点一定是f值最小的点(通过堆排序得到的)
		open_table[0] = open_table[--open_count];	//最后一个点放到第一个点，然后进行堆调整
		AdjustHeap(0);			                                	    //调整堆
		close_table[close_count++] = cur_node;	    //当前点加入close表

		if (cur_node == nullptr)//找不到路径
		{
			return 0;
		}

		//这里会出现curr_node为空的问题，是因为就目前静止状态下找不到出路了
		//可以让蛇走几步（随机或某种规律）
		cur_node->in_closetable = 1;		//将当前点放入close_table

		if (cur_node->x == end_node->x && cur_node->y == end_node->y)//若终点在close中，结束
		{
			break;
		}
		GetNeightbors(cur_node, end_node);			//对邻居处理
	}
	cur_node = end_node;//寻路成功，蛇吃到食物，当前节点到达终点

	//回溯得到路径
	while (cur_node)
	{
		path_stack[++top] = cur_node;
		cur_node = cur_node->parent;
	}
	Translate(top, row, col);
	return 1;
}

void Translate(int top, int row, int col)
{
	while (top > 0)
	{
		if (path_stack[top]->y - path_stack[top - 1]->y == -1 && path_stack[top]->x == path_stack[top - 1]->x)
		{
			SnakeDir = 'D';
		}
		else if (path_stack[top]->y - path_stack[top - 1]->y == 1 && path_stack[top]->x == path_stack[top - 1]->x)
		{
			SnakeDir = 'A';
		}
		else if (path_stack[top]->y == path_stack[top - 1]->y && path_stack[top]->x - path_stack[top - 1]->x == -1)
		{
			SnakeDir = 'S';
		}
		else if (path_stack[top]->y == path_stack[top - 1]->y && path_stack[top]->x - path_stack[top - 1]->x == 1)
		{
			SnakeDir = 'W';
		}

		printf("(%d,%d)-->", path_stack[top]->y, path_stack[top]->x);//x代表行，y代表列，所以输出坐标时两者要交换

		Move_AI(row, col);
		DrawMap_AI(3, row, col);
		Sleep(50);
		top--;
	}
	printf("(%d,%d)\n", path_stack[top]->y, path_stack[top]->x);//终点，最终输出在控制台
}