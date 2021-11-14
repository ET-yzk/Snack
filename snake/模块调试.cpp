////Astar
///****堆排序**用于实现最短路径回溯***/
//// 交换两个元素在open_table中的前后关系
//void swap(int idx1, int idx2)
//{
//	pAStarNode tmp = open_table[idx1];
//	open_table[idx1] = open_table[idx2];
//	open_table[idx2] = tmp;
//}
//// 调整为小根堆，试用于较大数据集
//void adjust_heap(int nIndex)
//{
//	int curr = nIndex;
//	int child = curr * 2 + 1;	// 得到左孩子idx( 下标从0开始，所有做孩子是curr*2+1 )
//	int parent = (curr - 1) / 2;	// 得到双亲idx
//
//	if (nIndex < 0 || nIndex >= open_node_count)//非法位置编号
//	{
//		return;
//	}
//
//	// 从curr位置往下调整( 要比较左右孩子和cuur parent )
//	while (child < open_node_count)
//	{
//		// 小根堆是双亲值小于孩子值
//		if (child + 1 < open_node_count && open_table[child]->s_g + open_table[child]->s_h > open_table[child + 1]->s_g + open_table[child + 1]->s_h)
//		{
//			++child;
//		}//匹配元素值较大孩子
//
//		if (open_table[curr]->s_g + open_table[curr]->s_h <= open_table[child]->s_g + open_table[child]->s_h)
//		{
//			break;
//		}
//		else
//		{                                      //由上至下
//			swap(child, curr);		   // 交换节点
//			curr = child;				   // 再判断当前孩子节点
//			child = curr * 2 + 1;	   // 再判断左孩子
//		}
//	}
//
//	if (curr != nIndex)//若已经进行过往下调整
//	{
//		return;
//	}
//
//	// 则往上调整( 只需要比较cuur child和parent )
//	while (curr != 0)
//	{
//		if (open_table[curr]->s_g + open_table[curr]->s_h >= open_table[parent]->s_g + open_table[parent]->s_h)
//		{
//			break;
//		}
//		else
//		{
//			swap(curr, parent);
//			curr = parent;
//			parent = (curr - 1) / 2;
//		}
//	}
//}
//
//// 判断邻居点是否可以进入open表
//void insert_to_opentable(int x, int y, pAStarNode curr_node, pAStarNode end_node, int w)
//{
//	int i;
//
//	if (map_maze[x][y].s_style != BARRIER)		// 不是障碍物
//	{
//		if (!map_maze[x][y].s_is_in_closetable)	// 不在闭表中
//		{
//			if (map_maze[x][y].s_is_in_opentable)	// 在open表中
//			{
//				// 需要判断是否是一条更优化的路径
//				if (map_maze[x][y].s_g > curr_node->s_g + w)	// 如果更优化
//				{
//					map_maze[x][y].s_g = curr_node->s_g + w;
//					map_maze[x][y].s_parent = curr_node;
//
//					for (i = 0; i < open_node_count; i++)
//					{
//						if (open_table[i]->s_x == map_maze[x][y].s_x && open_table[i]->s_y == map_maze[x][y].s_y)
//						{
//							break;
//						}
//					}
//					adjust_heap(i);			// 下面调整点
//				}
//			}
//			else									// 不在open中
//			{
//				map_maze[x][y].s_g = curr_node->s_g + w;
//				map_maze[x][y].s_h = abs(end_node->s_x - x) + abs(end_node->s_y - y);//曼哈顿距离
//				map_maze[x][y].s_parent = curr_node;
//				map_maze[x][y].s_is_in_opentable = 1;
//				open_table[open_node_count] = &(map_maze[x][y]);
//				open_node_count++;
//			}
//		}
//	}
//}
//
//// 查找邻居
//// 对上下左右4个邻居进行查找 
//void get_neighbors(pAStarNode curr_node, pAStarNode end_node)
//{
//	int x = curr_node->s_x;
//	int y = curr_node->s_y;
//
//	// 下面对于4个邻居进行处理，上下左右 
//	if ((x + 1) >= 0 && (x + 1) < COL_AI - 2 && y >= 0 && y < COL_AI - 2)
//	{
//		insert_to_opentable(x + 1, y, curr_node, end_node, COL_AI - 2);
//	}
//
//	if ((x - 1) >= 0 && (x - 1) < COL_AI - 2 && y >= 0 && y < COL_AI - 2)
//	{
//		insert_to_opentable(x - 1, y, curr_node, end_node, COL_AI - 2);
//	}
//
//	if (x >= 0 && x < COL_AI - 2 && (y + 1) >= 0 && (y + 1) < COL_AI - 2)
//	{
//		insert_to_opentable(x, y + 1, curr_node, end_node, COL_AI - 2);
//	}
//
//	if (x >= 0 && x < COL_AI - 2 && (y - 1) >= 0 && (y - 1) < COL_AI - 2)
//	{
//		insert_to_opentable(x, y - 1, curr_node, end_node, COL_AI - 2);
//	}
//}
//
//int find(int x, int y)
//{
//	printf("数组中1代表起点，2代表终点，0代表可以通过，3代表障碍物\n");
//	// 地图数组的定义
//	AStarNode* start_node = NULL;			// 起始点
//	AStarNode* end_node = NULL;			// 结束点
//	AStarNode* curr_node;			// 当前点
//	int maze[COL_AI - 2][COL_AI - 2] = { 0 };
//	int i, j;
//	phead = head->next;
//	while (phead != NULL)//要放在给起点赋值之前，因为在吃到食物时，食物位置将付给尾节点，导致起点被覆盖
//	{
//		maze[(phead->body.Y) - 1][(phead->body.X) - 1] = BARRIER;
//		phead = phead->next;
//	}
//	//maze[(food->Y) - 1][(food->X) - 1] = ENDNODE;
//	maze[y - 1][x - 1] = ENDNODE;
//	maze[(head->body.Y) - 1][(head->body.X) - 1] = STARTNODE;
//
//	// 下面准备点 
//	for (i = 0; i < COL_AI - 2; ++i)
//	{
//		for (j = 0; j < COL_AI - 2; ++j)
//		{
//			map_maze[i][j].s_g = 0;
//			map_maze[i][j].s_h = 0;
//			map_maze[i][j].s_is_in_closetable = 0;
//			map_maze[i][j].s_is_in_opentable = 0;
//			map_maze[i][j].s_style = maze[i][j];
//			map_maze[i][j].s_x = i;
//			map_maze[i][j].s_y = j;
//			map_maze[i][j].s_parent = NULL;
//
//			if (map_maze[i][j].s_style == STARTNODE)	// 起点
//			{
//				start_node = &(map_maze[i][j]);
//			}
//			else if (map_maze[i][j].s_style == ENDNODE)	// 终点
//			{
//				end_node = &(map_maze[i][j]);
//			}
//		}
//	}
//	open_node_count = 0;
//	close_node_count = 0;
//	top = -1;
//	// 下面使用A*算法得到路径
//	open_table[open_node_count] = start_node;			// 起始点加入open表
//	open_node_count++;
//	start_node->s_is_in_opentable = 1;	                			// 加入open表
//	start_node->s_g = 0;
//	start_node->s_h = abs(end_node->s_x - start_node->s_x) + abs(end_node->s_y - start_node->s_y);
//	start_node->s_parent = NULL;
//
//	while (1)
//	{
//		if (open_node_count < 0)
//		{
//			return 0;
//		}
//		curr_node = open_table[0];		// open表的第一个点一定是f值最小的点(通过堆排序得到的)
//		open_table[0] = open_table[--open_node_count];	// 最后一个点放到第一个点，然后进行堆调整
//		adjust_heap(0);				// 调整堆
//		close_table[close_node_count++] = curr_node;	// 当前点加入close表
//
//
//		if (curr_node == nullptr)//找不到路径
//		{
//			return 0;
//		}
//
//		//这里会出现curr_node为空的问题，是因为就目前静止状态下找不到出路了
//		//可以让蛇走几步
//		curr_node->s_is_in_closetable = 1;		// 已经在close表中了
//
//		if (curr_node->s_x == end_node->s_x && curr_node->s_y == end_node->s_y)// 终点在close中，结束
//		{
//			break;
//		}
//		get_neighbors(curr_node, end_node);			// 对邻居的处理
//	}
//	curr_node = end_node;
//
//
//
//	while (curr_node)//回溯
//	{
//		path_stack[++top] = curr_node;
//		curr_node = curr_node->s_parent;
//	}
//	//if (top == -1)
//	//{
//	//	printf("我找不到路啦~");
//	//	exit(0);
//	//}
//	while (top > 0)		// 输出路径，将top赋给path_stack[0]，然后返回该数组结构体地址
//	{
//		if (path_stack[top]->s_y - path_stack[top - 1]->s_y == -1 && path_stack[top]->s_x == path_stack[top - 1]->s_x)
//		{
//			SnakeDir = 'D';
//		}
//		else if (path_stack[top]->s_y - path_stack[top - 1]->s_y == 1 && path_stack[top]->s_x == path_stack[top - 1]->s_x)
//		{
//			SnakeDir = 'A';
//		}
//		else if (path_stack[top]->s_y == path_stack[top - 1]->s_y && path_stack[top]->s_x - path_stack[top - 1]->s_x == -1)
//		{
//			SnakeDir = 'S';
//		}
//		else if (path_stack[top]->s_y == path_stack[top - 1]->s_y && path_stack[top]->s_x - path_stack[top - 1]->s_x == 1)
//		{
//			SnakeDir = 'W';
//		}
//
//		printf("(%d,%d)-->", path_stack[top]->s_y, path_stack[top]->s_x);//x代表行，y代表列，所以输出坐标时两者要交换
//
//		Move_AI();
//		DrawMap_AI(3, 0);
//		Sleep(10);
//		top--;
//	}
//	printf("(%d,%d)\n", path_stack[top]->s_y, path_stack[top]->s_x);//终点
//	return 1;
//}
//
//
//
//
//
//
//
///******A*算法*******/
//#include<stdio.h>
//#include<stdlib.h>
//#define N 32
//#define W 10
//
//typedef struct STARNODE {
//    int x;//节点的x,y坐标
//    int y;
//    int G;//该节点的G, H值
//    int H;
//    int is_snakebody;//是否为蛇身，是为1，否则为0；
//    int in_open_table;//是否在open_table中，是为1，否则为0；
//    int in_close_table;//是否在close_table中，是为1，否则为0；
//    struct STARNODE* ParentNode;//该节点的父节点
//} starnode, * pstarnode;
//
//starnode mapnode[N / 2 + 2][N + 4];
//
//pstarnode opentable[N * N / 2];
//pstarnode closetable[N * N / 2];
//
//int opennode_count = 0;
//int closenode_count = 0;
//starnode food;
//
////根据指针所指向的节点的F值，按大顶堆进行调整
//void heapadjust(pstarnode a[], int m, int n)
//{
//    int i;
//    pstarnode temp = a[m];
//    for (i = 2 * m; i <= n; i *= 2)
//    {
//        if (i + 1 <= n && (a[i + 1]->G + a[i + 1]->H) > (a[i]->G + a[i]->H))
//        {
//            i++;
//        }
//        if ((temp->G + temp->H) > (a[i]->G + a[i]->H))
//        {
//            break;
//        }
//        a[m] = a[i];
//        m = i;
//    }
//    a[m] = temp;
//}
//
//void swap(pstarnode a[], int m, int n)
//{
//    pstarnode temp;
//    temp = a[m];
//    a[m] = a[n];
//    a[n] = temp;
//}
//
//
//void crtheap(pstarnode a[], int n)
//{
//    int i;
//    for (i = n / 2; i > 0; i--)
//    {
//        heapadjust(a, i, n);
//    }
//}
//
//void heapsort(pstarnode a[], int n)
//{
//    int i;
//    crtheap(a, n);
//    for (i = n; i > 1; i--)
//    {
//        swap(a, 1, i);
//        heapadjust(a, 1, i - 1);
//    }
//}
//
////x1, y1是邻域点坐标
////curtnode是当前点坐标
//void insert_opentable(int x1, int y1, pstarnode pcurtnode)
//{
//    int i;
//    if (!mapnode[x1][y1].is_snakebody && !mapnode[x1][y1].in_close_table)//如果不是蛇身也不在closetable中
//    {
//        if (mapnode[x1][y1].in_open_table && mapnode[x1][y1].G > pcurtnode->G + W)//如果已经在opentable中,但是不是最优路径
//        {
//            mapnode[x1][y1].G = pcurtnode->G + W;//把G值更新
//            mapnode[x1][y1].ParentNode = pcurtnode;//把该邻点的双亲节点更新
//            //由于改变了opentable中一个点的F值，需要对opentable中的点的顺序进行调整，以满足有序
//            for (i = 1; i <= opennode_count; i++)
//            {
//                if (opentable[i]->x == x1 && opentable[i]->y == y1)
//                {
//                    break;
//                }
//                heapsort(opentable, i);
//            }
//        }
//        else//把该点加入opentable中
//        {
//            opentable[++opennode_count] = &mapnode[x1][y1];
//
//            mapnode[x1][y1].G = pcurtnode->G + W;
//            mapnode[x1][y1].H = (abs(food.x - x1) + abs(food.y - y1)) * W;
//            mapnode[x1][y1].in_open_table = 1;
//            mapnode[x1][y1].ParentNode = pcurtnode;
//            heapsort(opentable, opennode_count);
//        }
//    }
//}
//
////寻找当前点的四邻域点，把符合条件的点加入opentable中
//void find_neighbor(pstarnode pcurtnode)
//{
//    int x = pcurtnode->x;
//    int y = pcurtnode->y;
//
//    if (x + 1 <= N / 2)
//    {
//        insert_opentable(x + 1, y, pcurtnode);
//    }
//    if (x - 1 >= 1)
//    {
//        insert_opentable(x - 1, y, pcurtnode);
//    }
//    if (y + 1 <= N + 1)
//    {
//        insert_opentable(x, y + 1, pcurtnode);
//    }
//    if (y - 1 >= 2)
//    {
//        insert_opentable(x, y - 1, pcurtnode);
//    }
//}
//
//int search_road(pstarnode startnode, pstarnode endnode)
//{
//    int is_search_road = 0;
//    opennode_count = 0;
//    closenode_count = 0;
//    pstarnode pcurtnode;
//
//    opentable[++opennode_count] = startnode;//起始点加入opentable中
//    startnode->in_open_table = 1;
//    startnode->ParentNode = NULL;
//    startnode->G = 0;
//    startnode->H = (abs(endnode->x - startnode->x) + abs(endnode->y - startnode->y)) * W;
//
//    if (startnode->x == endnode->x && startnode->y == endnode->y)//如果起点和终点重合
//    {
//        is_search_road = 1;
//        return is_search_road;
//    }
//
//    while (1)
//    {
//        //取出opentable中第1个节点加入closetable中
//        pcurtnode = opentable[1];
//        opentable[1] = opentable[opennode_count--];
//
//        closetable[++closenode_count] = pcurtnode;
//        pcurtnode->in_open_table = 0;
//        pcurtnode->in_close_table = 1;
//
//        if (pcurtnode->x == endnode->x && pcurtnode->y == endnode->y)
//        {
//            is_search_road = 1;
//            break;
//        }
//
//        find_neighbor(pcurtnode);
//
//        if (!opennode_count)//如果opentable已经为空，即没有找到路径
//        {
//            break;
//        }
//    }
//
//    return is_search_road;
//}
//
//int main(void)
//{
//    int i, j;
//    pstarnode startnode;
//
//    for (i = 0; i < N / 2 + 2; i++)
//        for (j = 0; j < N + 4; j++)
//        {
//            mapnode[i][j].G = 0;
//            mapnode[i][j].H = 0;
//            mapnode[i][j].in_close_table = 0;
//            mapnode[i][j].in_open_table = 0;
//            mapnode[i][j].is_snakebody = 0;
//            mapnode[i][j].ParentNode = NULL;
//            mapnode[i][j].x = i;
//            mapnode[i][j].y = j;
//        }
//
//    startnode = &mapnode[5][10];
//    food.x = 5;
//    food.y = 15;
//    mapnode[5][13].is_snakebody = 1;
//    mapnode[6][13].is_snakebody = 1;
//    mapnode[4][13].is_snakebody = 1;
//    mapnode[4][12].is_snakebody = 1;
//    mapnode[6][12].is_snakebody = 1;
//
//    int flag;
//    flag = search_road(startnode, &food);
//    pstarnode temp = &mapnode[5][15];
//
//    do {
//        printf("%d %d\n", temp->x, temp->y);
//        temp = temp->ParentNode;
//    } while (temp);
//
//    return 0;
//}
//
//
///********用户登入*********/
//int compDec();
//int compInc();
//void Login();
//void registers();
//#define N 4
//wchar_t s1[5], s2[5];
//wchar_t temp[20];
//FILE* fp;
//int m, n, s[N];
//typedef struct The_users //用于储存用户账号密码
//{
//    char id[11];//ID
//    char pwd[20];//password
//}users;
//users a, b;//成员变量,用来登陆与注册
////wchar_t 与 char数据类型转换
//char* wchar2char(const wchar_t* wchar)
//{
//    char* m_char;
//    int len = WideCharToMultiByte(CP_ACP, 0, wchar, wcslen(wchar), NULL, 0, NULL, NULL);
//    m_char = new char[len + 1];
//    WideCharToMultiByte(CP_ACP, 0, wchar, wcslen(wchar), m_char, len, NULL, NULL);
//    m_char[len] = '\0';
//    return m_char;
//}
//wchar_t* char2wchar(const char* cchar)
//{
//    wchar_t* m_wchar = new wchar_t[strlen(cchar) + 1];
//    MultiByteToWideChar(CP_ACP, 0, cchar, strlen(cchar), m_wchar, strlen(cchar));
//    m_wchar[strlen(cchar)] = L'\0';
//    return m_wchar;
//}
//
//void Menu()
//{
//B:
//    InputBox(s1, 5, L"请输入数字：1.开始游戏 2.排行榜 3.退出游戏");
//    int x, y[3];
//    x = _wtoi(s1);  //将输入转化为数字
//    if (x == 1)
//    {
//    A:
//        InputBox(s2, 5, L"请输入数字：1.登陆 2.注册");
//        x = _wtoi(s2);
//        if (x == 2)
//        {
//            registers();
//            Login();
//        }
//        else if (x == 1)
//        {
//            Login();
//        }
//        else
//        {
//            //请正确输入
//            MessageBox(GetHWnd(), L"请重新正确输入！", L"ERROR", MB_OK);
//            goto A;            //据说要尽量避免使用goto，但用得好效率高于break和continue
//        }
//    }
//    else if (x == 2)
//    {
//        printf("                    排行榜\n");
//        fopen_s(&fp, "scores.txt", "r");
//        for (x = 0; x < N - 1; x++) {
//            fscanf_s(fp, "%d", &y[x]);
//            printf("%d\n", y[x]);
//        }
//        fclose(fp);
//        //_getch();
//    }
//    else
//    {
//        MessageBox(GetHWnd(), L"请重新正确输入！", L"ERROR", MB_OK);
//        goto B;
//    }
//}
//void registers()//注册账号密码
//{
//    if (fopen_s(&fp, "Users1.txt", "r") != NULL)
//    {
//        MessageBox(GetHWnd(), L"Users1.txt读取失败，请确保当前目录存在该文件！", L"ERROR", MB_OK);
//        exit(1);
//    }
//    //fopen_s(&fp, "Users1.txt", "r");
//    fscanf_s(fp, "%s%s", b.id, sizeof(b.id), b.pwd, sizeof(b.pwd));
//    InputBox(temp, 11, L"请输入账号：");
//    strcpy_s(a.id, wchar2char(temp));
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
//    if ((fopen_s(&fp, "Users1.txt", "r")) != NULL)
//    {
//        MessageBox(GetHWnd(), L"Users1.txt读取失败，请确保当前目录存在该文件！", L"ERROR", MB_OK);
//        exit(1);
//    }
//    fscanf_s(fp, "%s%s", b.id, sizeof(b.id), b.pwd, sizeof(b.pwd));
//    InputBox(temp, 11, L"请输入账号：");
//    strcpy_s(a.id, wchar2char(temp));
//    while (1)
//    {
//        if (strcmp(a.id, b.id) == 0) break;//如果找到了这个用户名
//        else
//        {
//            if (!feof(fp))                              //如果文件未读完
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
//    if (strcmp(a.pwd, b.pwd) == 0)       //如果密码匹配
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
//void Score()
//{
//    if (fopen_s(&fp, "scores.txt", "r") == NULL)
//    {
//        MessageBox(GetHWnd(), L"scores.txt读取失败，请确保当前目录存在该文件！", L"ERROR", MB_OK);
//        exit(1);
//    }
//    //fopen_s(&fp, "scores.txt", "r");
//    for (n = 0; n < N - 1; n++)
//    {
//        fscanf_s(fp, "%d", &m);
//        s[n] = m;
//    }
//    s[N - 1] = score;
//    //qsort(s, N, sizeof(s[0]), compDec); //快速排序函数
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
//}//qsort()升序排序
//int compDec(const void* a, const void* b) {
//    return *(int*)b - *(int*)a;
//}//qsort()降序排序
//
//void main()
//{
//    Menu();
//}
//
//
//#include <stdio.h>
//#include<stdlib.h>
//struct cat
//{
//	int x;
//	struct cat* next;
//};
//cat* a;
//cat* b;
//
//int main()
//{
//	b = (cat*)malloc(sizeof(cat));
//	if (b)
//	{
//		b->x = -1;
//		b->next = NULL;
//	}
//	else
//	{
//		printf("分配内存失败");
//	}
//	for (int i = 0; i < 3; i++)
//	{
//		a = (cat*)malloc(sizeof(cat));
//		if (a)
//		{
//			a->x = i;
//			a->next = b;
//			b = a;
//		}
//		else
//		{
//			printf("分配内存失败");
//		}
//	}
//	while (a->next != NULL)
//	{
//		printf("yes");
//		a = a->next;
//	}
//	return 0;
//}
//
//#include <stdio.h>
//#include <string.h> 
//#include <windows.h> 
//struct student {
//	long int num; 
//	char name[20]; 
//	int age; char sex[4];
//	char b[30];
//	char p[15];
//};
// int n = 0; 
//struct student stu[100]; 
//struct student* p; 
//void lr(); 
//void ll(); 
//void cx(); 
//void xg();
// void sc(); 
// void main() {
//	 int z;
//	 printf("+---------------------------+\n");
//	 printf("| 欢迎使用学生bai信息管理系统 |\n");
//	 printf("+---------------------------+\n");
//	 printf("提示：为保证您的操作得到保存，请按正常顺序退出系统^_^\n");
//	 do {
//		 printf("\n\t\t\t--------------------------------\n");
//		 printf("\t\t\t+ 主菜单 |\n");
//		 printf("\t\t\t--------------------------------\n");
//		 printf("\t\t\t+ [1]----录入学生信息 |\n");
//		 printf("\t\t\t+ [2]----浏览学生信息 |\n");
//		 printf("\t\t\t+ [3]----查询学生信息 |\n");
//		 printf("\t\t\t+ [4]----删除学生信息 |\n");
//		 printf("\t\t\t+ [5]----修改学生信息 |\n");
//		 printf("\t\t\t+ [0]----退出系统 |\n");
//		 printf("\t\t\t--------------------------------\n");
//		 printf("请输入您的选择：");
//		 scanf_s("%d", &z);
//		 system("color 2f");
//		 switch (z)
//		 {
//		 case 0: break;
//		 case 1:lr(); break;
//		 case 2:ll(); break;
//		 case 3:cx(); break;
//		 case 4:sc(); break;
//		 case 5:xg(); break;
//		 default:printf("\n无效选项!");
//		 }
//	 } while (z != 0);
// }
// void lr()/*录入函数*/
// {
//	 int y; if (n == 0) p = stu; do {
//		 printf("--------------------\n");
//		 printf("请输入学生的学号:");
//		 scanf_s("%ld", &p->num);
//		 printf("请输入学生的姓名:");
//		 scanf_s("%s", p->name);
//		 printf("请输入学生的年龄:");
//		 scanf_s("%d", &p->age);
//		 printf("请输入学生的性别:");
//		 scanf_s("%s", p->sex);
//		 printf("请输入学生的地址:");
//		 scanf_s("%s", p->b);
//		 printf("请输入学生的电话:");
//		 scanf_s("%s", p->p);
//		 n++;
//		 p++;
//		 printf("\n1.继续输入.\n0.输入完毕.\n"); printf("请选择：");
//		 scanf_s("%d", &y);
//	 } while (y == 1); printf("提示：输入完毕!你一共输入%d个\n", n);
// }
// void ll()/*浏览函数*/ 
// {
//	 int i, j;
//	 if (n != 0)
//	 {
//		 printf("学生总数:%d\n", n);
//		 printf("学号\t姓名\t年龄\t性别\t地址\t\t电话\n");
//		 printf("-----------------------------------------------------\n");
//		 for (i = 0; i < n; i++)
//		 {
//			 printf("%ld\t%s\t%d\t%s\t%s\t\t%s\n", stu[i].num, stu[i].name, stu[i].age, stu[i].sex, stu[i].b, stu[i].p);
//		 }
//	 }
//	 else printf("提示:无学生数据，请输入数据！");
// } 
// void cx()/*查询函数*/
// {
//	 int c;
//	 int w, i, j = 0;
//	 char name[20];
//	 if (n != 0)
//	 {
//		 do {
//			 printf("\n"); printf("+--------------------+\n");
//			 printf("| 按学号查询 请按 1 |\n");
//			 printf("| 按姓名查询 请按 2 |\n");
//			 printf("| 取消 请按 0 |\n");
//			 printf("+--------------------+\n");
//			 printf("请输入您的选择：");
//			 scanf_s("%d", &c);
//			 switch (c)
//			 {
//			 case 0:break;
//			 case 1:
//				 printf("请输入学生的学号;");
//				 scanf_s("%ld", &w);
//				 printf("\n");
//				 for (i = 0; i < n; i++)
//					 if (stu[i].num == w)
//					 {
//						 printf("\n学号\t姓名\t年龄\t性别\t地址\t\t电话\n");
//						 printf("%ld\t%s\t%d\t%s\t%s\t\t%s\n", stu[i].num, stu[i].name, stu[i].age, stu[i].sex, stu[i].b, stu[i].p);
//						 j = 1;
//					 }
//				 if (j == 0) printf("提示:没有该学生记录，请核对！"); break;
//			 case 2:
//				 printf("请输入学生的姓名：");
//				 scanf_s("%s", name);
//				 printf("\n");
//				 for (i = 0; i < n; i++)
//					 if (strcmp(name, stu[i].name) == 0)
//					 {
//						 printf("\n学号\t姓名\t年龄\t性别\t地址\t\t电话\n");
//						 j = 1;
//						 printf("%ld\t%s\t%d\t%s\t%s\t\t%s\n", stu[i].num, stu[i].name, stu[i].age, stu[i].sex, stu[i].b, stu[i].p);
//					 }
//				 if (j == 0) printf("提示:没有该学生记录，请核对！"); break;
//			 default: printf("\n提示:无效选项!"); break;
//			 }
//		 } while (c != 0);
//	 }
//	 else printf("提示:无学生数据，请输入数据！");
//	 return;
// }
// void xg()/*修改函数*/
// {
//	 long int num;
//	 int i, j, c;
//	 if (n != 0)
//	 {
//		 printf("请输入您要修改的学生的学号：");
//		 scanf_s("%ld", &num); printf("\n");
//		 for (i = 0; i < n; i++)
//			 if (stu[i].num == num) j = i;
//		 do {
//			 printf("请选择您要修改的学生的信息内容：\n");
//			 printf("+----------------------+\n");
//			 printf("| 姓名 请按 1 |\n");
//			 printf("| 年龄 请按 2 |\n");
//			 printf("| 性别 请按 3 |\n");
//			 printf("| 学号 请按 4 |\n");
//			 printf("| 地址 请按 5 |\n");
//			 printf("| 电话 请按 6 |\n");
//			 printf("| 取消 请按 0 |\n");
//			 printf("+----------------------+\n");
//			 printf("请输入您的选择：");
//			 scanf_s("%d", &c);
//			 printf("\n");
//			 switch (c)
//			 {
//			 case 0:break;
//			 case 1:printf("请输入新姓名：");
//				 scanf_s("%s", stu[j].name); break;
//			 case 2:printf("请输入新年龄：");
//				 scanf_s("%d", &stu[j].age); break;
//			 case 3:printf("请输入新性别：");
//				 scanf_s("%s", stu[j].sex); break;
//			 case 4:printf("请输入新学号：");
//				 scanf_s("%ld", &stu[j].num); break;
//			 case 5:printf("请输入新地址：");
//				 scanf_s("%s", stu[j].b); break;
//			 case 6:printf("请输入新电话：");
//				 scanf_s("%s", stu[j].p); break;
//			 default: printf("\n无效选项!"); break;
//			 }
//		 } while (c != 0);
//	 }
//	 else printf("提示:无学生数据，请输入数据！");
// }
// void sc()/*删除函数*/
// {
//	 long int num;
//	 int i, j, e;
//	 if (n != 0)
//	 {
//		 printf("学号\t姓名\t年龄\t性别\t地址\t\t电话\n");
//		 printf("-----------------------------------------------------\n");
//		 for (i = 0; i < n; i++) printf("%ld\t%s\t%d\t%s\t%s\t\t%s\n", stu[i].num, stu[i].name, stu[i].age, stu[i].sex, stu[i].b, stu[i].p);
//		 printf("请输入您要删除的学生的学号：");
//		 scanf_s("%ld", &num); 
//		 printf("\n");
//		 for (i = 0; i < n; i++)
//			 if (num == stu[i].num) j = i;
//		 if (j != (n - 1))
//		 {
//			 for (e = i - 1; e < n; e++, j++)
//			 {
//				 stu[j].num = stu[j + 1].num;
//				 strcpy_s(stu[j].name, stu[j + 1].name);
//				 strcpy_s(stu[j].sex, stu[j + 1].sex);
//				 stu[j].age = stu[j + 1].age;
//				 strcpy_s(stu[j].b, stu[j + 1].b);
//				 strcpy_s(stu[j].p, stu[j + 1].p);
//				 n--;
//				 p--;
//			 }
//		 }
//		 else
//		 {
//			 n--;
//			 p--;
//		 }
//		 printf("提示:删除完毕！");
//	 }
//	 else printf("提示:无学生数据，请输入数据！");
// }
//
///**********ASTAR应用************/
//void AddFood_AI(int x1, int x2, int y1, int y2)//墙+障碍物
//{
//	food = (COORD*)malloc(sizeof(COORD));
//	if (!food)
//	{
//		MessageBox(GetHWnd(), L"内存分配失败，请重试程序", L"SORRY", MB_OK);
//		exit(0);
//	}
//A:
//	food->X = rand() % (COL_AI - 2) + 1;    //确保食物与墙不重叠
//	food->Y = rand() % (ROW_AI - 2) + 1;  //产生[m,n]随机数，int num=rand()%(n-m+1)+m;
//	if (food->X >= x1 && food->X <= x2 && food->Y >= y1 && food->Y <= y2)
//	{                                         //确保其不与障碍物重叠
//		goto A;                           //或者while循环
//	}
//	phead = head;
//	while (phead->next != NULL)	                  //判断蛇与食物是否重合；这里判断phead->next != NULL：1.上面程序确保了phead不会为NULL；
//	{                                                                 //2.当食物出现在尾节点而下一步尾节点会移开，所以该点食物的出现应当是合理的
//		if (phead->body.X == food->X && phead->body.Y == food->Y)
//		{
//			free(food);                 //若提示food内存未初始化是因为这里的free()，实际不会出现该问题
//			AddFood_AI(0,0,0,0);
//			break;                        //防止出递归时phead = nullptr，导致后续程序运行出错
//		}
//		phead = phead->next;//这里会出现调用phead = nullptr是因为递归的原因，若调用该递归则必出现该问题，加入break可以避免
//	}
//}
//void JudgeWall_AI(int x1, int x2, int y1, int y2)
//{
//	if (head->body.X == 0 || head->body.X == COL_AI - 1 ||
//		head->body.Y == 0 || head->body.Y == ROW_AI - 1 ||
//		(head->body.X >= x1 && head->body.X <= x2 &&
//		head->body.Y >= y1 && head->body.Y <= y2))
//	{
//		head = head->next;
//		DrawMap_AI(6,0,0,0,0);          //蛇头显示为紫色
//		GameOver();
//		MessageBox(GetHWnd(), L"你撞墙了，游戏结束", L"SORRY", MB_OK);
//		exit(0);
//	}
//}
//int JudgeSnake_AI()
//{
//	phead = head->next;     //蛇头不可能和蛇头相撞
//	while (phead != NULL)
//	{
//		if ((phead->body.X == head->body.X) &&
//			(phead->body.Y == head->body.Y))
//		{
//			head = head->next;
//			DrawMap_AI(6,0,0,0,0);          //蛇头显示为紫色
//			GameOver();
//			MessageBox(GetHWnd(), L"你撞到自己了，游戏结束", L"SORRY", MB_OK);
//			exit(0);
//		}
//		phead = phead->next;
//	}
//	return 1;
//}
//void DrawMap_AI(int color, int x1, int x2, int y1, int y2)
//{
//	int i, j;
//	BeginBatchDraw();                                 //开始绘图，绘制完整幅画面显示再，可避免闪烁
//	setbkcolor(WHITE);                                //设置背景色为白色
//	settextcolor(RGB(240, 0, 0));                   //红字
//	cleardevice();		                                    //清屏
//	WCHAR arr[10];		                                //保存成绩
//	putimage(75, 3, &img[1]);                      //食物图案
//	wsprintf(arr, L"积分：%d    ", score);       //将成绩格式化输出到字符串arr中 
//	outtextxy(0, 0, arr);			                     //显示成绩
//	wsprintf(arr, L"速度级别：%d", 9 - speed / 30);
//	outtextxy(200, 0, arr);                            //显示速度级别
//	settextcolor(RGB(160, 160, 160));           //淡灰字
//	outtextxy(575, 0, L"弱AI模式");
//	setlinecolor(BLACK);
//	setfillcolor(RGB(230, 230, 230));	   //深灰色
//	for (i = x1; i <= x2; i++)
//	{
//		for (j = y1; j <= y2; j++)
//		{
//			fillrectangle(i * 10, j *10, i * 10 + 10, j * 10 + 10);
//		}
//	}
//	for (i = 0; i < ROW_AI; i++)           //每一行的 第一个 和 最后一个 是墙
//	{
//		fillrectangle(0, i * 10 + 20, 10, i * 10 + 30);
//		fillrectangle((COL_AI - 1) * 10, i * 10 + 20, (COL_AI - 1) * 10 + 10, i * 10 + 30);
//	}
//
//	for (j = 1; j < COL_AI - 1; j++)	     //每一列的 第一个 和 倒数第一个 是墙
//	{
//		fillrectangle(j * 10, 20, j * 10 + 10, 30);
//		fillrectangle(j * 10, (ROW_AI - 1) * 10 + 20, j * 10 + 10, (ROW_AI - 1) * 10 + 30);
//	}
//	//绘制蛇，设置10像素为一帧
//	tail = head;
//	setlinecolor(RGB(0, 245, 255));		//淡蓝色框
//	switch (color)                                //绘制蛇头，预留7种颜色
//	{
//	case 0:
//		setfillcolor(RGB(255, 0, 0));		    //红 255 0 0
//		break;
//	case 3:
//		setfillcolor(RGB(0, 255, 0));		    //绿  0, 255, 0
//		break;
//	case 6:
//		setfillcolor(RGB(160, 32, 240));	//紫  160 32 240
//		break;
//	default:
//		break;
//	}
//	fillrectangle(tail->body.X * 10, tail->body.Y * 10 + 20, tail->body.X * 10 + 10, tail->body.Y * 10 + 30);
//	tail = tail->next;
//	while (tail->next != NULL)
//	{
//		setlinecolor(RGB(0, 245, 255));		//淡蓝色
//		setfillcolor(WHITE);
//		fillrectangle(tail->body.X * 10, tail->body.Y * 10 + 20, tail->body.X * 10 + 10, tail->body.Y * 10 + 30);
//		tail = tail->next;
//	}
//	//蛇尾
//	setlinecolor(RGB(0, 245, 255));		//淡蓝色
//	setfillcolor(BLUE);
//	fillrectangle(tail->body.X * 10, tail->body.Y * 10 + 20, tail->body.X * 10 + 10, tail->body.Y * 10 + 30);
//	//绘制食物
//	putimage(food->X * 10, food->Y * 10 + 20, &img[1]);//食物图案
//	EndBatchDraw();                                 //结束绘画
//}
//
//void Move_AI()
//{
//	if (Move_0())
//	{
//		JudgeWall_AI(0,0,0,0);
//		//if (JudgeSnake_AI())
//		//{
//		//	//去掉最后一节蛇节点
//		//	tail = head;
//		//	while (tail->next->next != NULL)
//		//	{
//		//		tail = tail->next;
//		//	}
//		//	free(tail->next);
//		//	tail->next = NULL;
//			if (JudgeFood())
//			{
//				AddFood_AI(0,0,0,0);
//				//ChangeSpeed();
//			}
//		//}
//	}
//	if (score == (COL - 1) * (ROW - 1) - 5)
//	{
//		MessageBox(GetHWnd(), L"恭喜你成功了！", L"VICTORY", MB_OK);
//		exit(0);
//	}
//}
//void Run_AI()
//{
//	int x1, x2, y1, y2;                 //障碍物坐标
//	ULONGLONG t1 = 0, t2;             //定义两个时间用于控制蛇移动速度
//	char SnakeDir_t = 'D';        //移动方向temp，用于ChangeDir()中实现暂停功能
//	int color = 0;                     //记录蛇头颜色
//	color = ChangeColor(color);
//	//while (1)
//	//{
//	//	t2 = GetTickCount64();
//	//	DrawMap_AI(color, 0, 0, 0, 0);
//	//	if (_kbhit() && SnakeDir != KEY_SPACE)//_kbhit()判断键盘是否有输入；实现长按方向键加速
//	//	{
//	//		SnakeDir_t = ChangeDir(SnakeDir_t);
//	//		Move_AI();
//	//		t2 = GetTickCount64();
//	//		t1 = t2;
//	//	}
//	//	else if (_kbhit() && SnakeDir == KEY_SPACE)//用于实现恢复暂停
//	//	{
//	//		SnakeDir_t = ChangeDir(SnakeDir_t);
//	//	}
//	//	else if (t2 - t1 > speed && SnakeDir != KEY_SPACE)//控制🐍速度，越大越慢
//	//	{
//	//		Move_AI();
//	//		t1 = t2;
//	//	}
//	//}
//	while (1)
//	{
//		DrawMap_AI(color, 0, 0, 0, 0);
//		find();
//	}
//}
//
//
///*****************************************************************************************************/
///****堆排序*****/
//// 交换两个元素在open_table中的前后关系
//void swap(int idx1, int idx2)
//{
//	pAStarNode tmp = open_table[idx1];
//	open_table[idx1] = open_table[idx2];
//	open_table[idx2] = tmp;
//}
//// 调整为小根堆，试用于较大数据集
//void adjust_heap(int nIndex)
//{
//	int curr = nIndex;
//	int child = curr * 2 + 1;	// 得到左孩子idx( 下标从0开始，所有做孩子是curr*2+1 )
//	int parent = (curr - 1) / 2;	// 得到双亲idx
//
//	if (nIndex < 0 || nIndex >= open_node_count)//非法位置编号
//	{
//		return;
//	}
//
//	// 从curr位置往下调整( 要比较左右孩子和cuur parent )
//	while (child < open_node_count)
//	{
//		// 小根堆是双亲值小于孩子值
//		if (child + 1 < open_node_count && open_table[child]->s_g + open_table[child]->s_h > open_table[child + 1]->s_g + open_table[child + 1]->s_h)
//		{
//			++child;
//		}//匹配元素值较大孩子
//
//		if (open_table[curr]->s_g + open_table[curr]->s_h <= open_table[child]->s_g + open_table[child]->s_h)
//		{
//			break;
//		}
//		else
//		{                                      //由上至下
//			swap(child, curr);		   // 交换节点
//			curr = child;				   // 再判断当前孩子节点
//			child = curr * 2 + 1;	   // 再判断左孩子
//		}
//	}
//
//	if (curr != nIndex)//若已经进行过往下调整
//	{
//		return;
//	}
//
//	// 则往上调整( 只需要比较cuur child和parent )
//	while (curr != 0)
//	{
//		if (open_table[curr]->s_g + open_table[curr]->s_h >= open_table[parent]->s_g + open_table[parent]->s_h)
//		{
//			break;
//		}
//		else
//		{
//			swap(curr, parent);
//			curr = parent;
//			parent = (curr - 1) / 2;
//		}
//	}
//}
//
//// 判断邻居点是否可以进入open表
//void insert_to_opentable(int x, int y, pAStarNode curr_node, pAStarNode end_node, int w)
//{
//	int i;
//
//	if (map_maze[x][y].s_style != BARRIER)		// 不是障碍物
//	{
//		if (!map_maze[x][y].s_is_in_closetable)	// 不在闭表中
//		{
//			if (map_maze[x][y].s_is_in_opentable)	// 在open表中
//			{
//				// 需要判断是否是一条更优化的路径
//				if (map_maze[x][y].s_g > curr_node->s_g + w)	// 如果更优化
//				{
//					map_maze[x][y].s_g = curr_node->s_g + w;
//					map_maze[x][y].s_parent = curr_node;
//
//					for (i = 0; i < open_node_count; i++)
//					{
//						if (open_table[i]->s_x == map_maze[x][y].s_x && open_table[i]->s_y == map_maze[x][y].s_y)
//						{
//							break;
//						}
//					}
//
//					adjust_heap(i);			// 下面调整点
//				}
//			}
//			else									// 不在open中
//			{
//				map_maze[x][y].s_g = curr_node->s_g + w;
//				map_maze[x][y].s_h = abs(end_node->s_x - x) + abs(end_node->s_y - y);//曼哈顿距离
//				map_maze[x][y].s_parent = curr_node;
//				map_maze[x][y].s_is_in_opentable = 1;
//				open_table[open_node_count++] = &(map_maze[x][y]);
//			}
//		}
//	}
//}
//
//// 查找邻居
//// 对上下左右4个邻居进行查找 
//void get_neighbors(pAStarNode curr_node, pAStarNode end_node)
//{
//	int x = curr_node->s_x;
//	int y = curr_node->s_y;
//
//	// 下面对于4个邻居进行处理，上下左右 
//	if ((x + 1) >= 0 && (x + 1) < 18 && y >= 0 && y < 18)
//	{
//		insert_to_opentable(x + 1, y, curr_node, end_node, 18);
//	}
//
//	if ((x - 1) >= 0 && (x - 1) < 18 && y >= 0 && y < 18)
//	{
//		insert_to_opentable(x - 1, y, curr_node, end_node, 18);
//	}
//
//	if (x >= 0 && x < 18 && (y + 1) >= 0 && (y + 1) < 18)
//	{
//		insert_to_opentable(x, y + 1, curr_node, end_node, 18);
//	}
//
//	if (x >= 0 && x < 18 && (y - 1) >= 0 && (y - 1) < 18)
//	{
//		insert_to_opentable(x, y - 1, curr_node, end_node, 18);
//	}
//}
//
//void find()
//{
//	open_node_count = 0;
//	printf("数组中1代表起点，2代表终点，0代表可以通过，3代表障碍物\n");
//	// 地图数组的定义
//	AStarNode* start_node = NULL;			// 起始点
//	AStarNode* end_node = NULL;			// 结束点
//	AStarNode* curr_node;			// 当前点
//	int maze[18][18] = { 0 };
//	int i, j;
//	maze[(food->Y) - 1][(food->X) - 1] = ENDNODE;
//	maze[(head->body.Y) - 1][(head->body.X) - 1] = STARTNODE;
//	// 下面准备点 
//	for (i = 0; i < 18; ++i)
//	{
//		for (j = 0; j < 18; ++j)
//		{
//			map_maze[i][j].s_g = 0;
//			map_maze[i][j].s_h = 0;
//			map_maze[i][j].s_is_in_closetable = 0;
//			map_maze[i][j].s_is_in_opentable = 0;
//			map_maze[i][j].s_style = maze[i][j];
//			map_maze[i][j].s_x = i;
//			map_maze[i][j].s_y = j;
//			map_maze[i][j].s_parent = NULL;
//
//			if (map_maze[i][j].s_style == STARTNODE)	// 起点
//			{
//				start_node = &(map_maze[i][j]);
//			}
//			else if (map_maze[i][j].s_style == ENDNODE)	// 终点
//			{
//				end_node = &(map_maze[i][j]);
//			}
//		}
//	}
//
//	// 下面使用A*算法得到路径
//	open_table[open_node_count++] = start_node;			// 起始点加入open表
//	start_node->s_is_in_opentable = 1;	                			// 加入open表
//	start_node->s_g = 0;
//	start_node->s_h = abs(end_node->s_x - start_node->s_x) + abs(end_node->s_y - start_node->s_y);
//	start_node->s_parent = NULL;
//
//	if (start_node->s_x == end_node->s_x && start_node->s_y == end_node->s_y)
//	{
//		printf("起点==终点！\n");
//		return;
//	}
//
//	while (1)
//	{
//		curr_node = open_table[0];		// open表的第一个点一定是f值最小的点(通过堆排序得到的)
//		open_table[0] = open_table[--open_node_count];	// 最后一个点放到第一个点，然后进行堆调整
//		adjust_heap(0);				// 调整堆
//		close_table[close_node_count++] = curr_node;	// 当前点加入close表
//		curr_node->s_is_in_closetable = 1;		// 已经在close表中了
//
//		if (curr_node->s_x == end_node->s_x && curr_node->s_y == end_node->s_y)// 终点在close中，结束
//		{
//			break;
//		}
//		get_neighbors(curr_node, end_node);			// 对邻居的处理
//	}
//	curr_node = end_node;
//
//	while (curr_node)//回溯
//	{
//		path_stack[++top] = curr_node;
//		curr_node = curr_node->s_parent;
//	}
//
//	while (top > 0)		// 输出路径
//	{
//		if (path_stack[top]->s_y - path_stack[top - 1]->s_y == -1 && path_stack[top]->s_x == path_stack[top - 1]->s_x)
//		{
//			SnakeDir = 'D';
//		}
//		else if (path_stack[top]->s_y - path_stack[top - 1]->s_y == 1 && path_stack[top]->s_x == path_stack[top - 1]->s_x)
//		{
//			SnakeDir = 'A';
//		}
//		else if (path_stack[top]->s_y == path_stack[top - 1]->s_y && path_stack[top]->s_x - path_stack[top - 1]->s_x == -1)
//		{
//			SnakeDir = 'S';
//		}
//		else
//		{
//			SnakeDir = 'W';
//		}
//
//		printf("(%d,%d)-->", path_stack[top]->s_y, path_stack[top]->s_x);//x代表行，y代表列，所以输出坐标时两者要交换
//
//		Move_AI();
//		DrawMap_AI(3, 0, 0, 0, 0);
//		Sleep(500);
//		top--;
//	}
//	printf("(%d,%d)\n", path_stack[top]->s_y, path_stack[top]->s_x);//终点
//	open_node_count = 0;
//}
//
//
///////
////// 程序名称：贪吃蛇AI
////// 编译环境：Visual Studio 2017，EasyX_2019测试版
////// 作　　者：柯西丶不是你 <591716377@qq.com>
//////
////#include <iostream>
////#include <conio.h>
////#include <ctime>
////#include <list>
////#include <queue>
////#include <set>
////#include <graphics.h>
////using namespace std;
////// 窗口参数
////const int WINDOW_WIDTH = 640;	// 窗口宽度
////const int WINDOW_HEIGHT = 480;	// 窗口高度
////
////// 游戏参数
////const int MAP_ROWNUM = 20;		// 地图行数
////const int MAP_COLNUM = 20;		// 地图列数
////const int GRIDGAP = 5;			// 格子间隙
////const int GRID = WINDOW_HEIGHT / MAP_COLNUM;	// 大格子宽度
////const int _GRID = GRID - 2 * GRIDGAP;			// 小格子宽度
////const int SPEED = 5;			// 蛇初始速度
////const int ACC = 0;				// 蛇加速度（其实是速度增量）
////
////// 游戏数据结构
////enum Direct { RIGHT = 77, DOWN = 80, LEFT = 75, UP = 72 };
////struct Coor {
////	int x, y, step;
////	Coor() { step = 0; }
////	Coor(int _x, int _y, int _step = 0) {
////		x = _x;
////		y = _y;
////		step = _step;
////	}
////	bool operator==(const Coor& t)const {
////		return (x == t.x) && (y == t.y);
////	}
////	bool operator!=(const Coor& t)const {
////		return (x != t.x) || (y != t.y);
////	}
////	bool operator<(const Coor& t)const {
////		return x == t.x ? y < t.y : x < t.x;
////	}
////};
////
////// 各类实现
////class Food {
////public:
////	Coor coor;			// 食物坐标
////	bool EXISTFOOD;		// 存在食物
////	Food() { EXISTFOOD = true; }
////	~Food() { EXISTFOOD = false; }
////	// 产生(0,0)~(limx,limy)的坐标
////	void RandCoor(int limx, int limy) {
////		coor.x = rand() % limx;
////		coor.y = rand() % limy;
////	}
////};
////
////class Snake {
////public:
////	int length;			// 蛇长度
////	int speed;			// 蛇速度
////	int acc;			// 加速度
////	list<Coor> coor;	// 蛇身坐标
////	Direct direct;		// 蛇当前方向
////	Snake() {}
////	~Snake() {}
////	// 蛇移动
////	void Move() {
////		Coor head = coor.front();
////		switch (direct) {
////		case UP:	head.y--;	break;
////		case DOWN:	head.y++;	break;
////		case LEFT:	head.x--;	break;
////		case RIGHT:	head.x++;	break;
////		}
////		coor.pop_back();		// 尾巴出列
////		coor.push_front(head);	// 新头入列
////	}
////	// 蛇转向
////	void TurnDirect(char cmd = 0x00) {
////		// 使用while而不是if
////		if (cmd == 0x00) {
////			while (_kbhit()) {
////				cmd = _getch();
////			}
////		}
////		// 两次方向相同设置加速度
////		if (cmd == direct)
////			acc = ACC;
////		else
////			acc = 0;
////		switch (cmd)
////		{
////		case UP:
////			if (direct != DOWN)
////				direct = UP;
////			break;
////		case DOWN:
////			if (direct != UP)
////				direct = DOWN;
////			break;
////		case LEFT:
////			if (direct != RIGHT)
////				direct = LEFT;
////			break;
////		case RIGHT:
////			if (direct != LEFT)
////				direct = RIGHT;
////			break;
////		}
////	}
////};
////
////class SnakeGame {
////private:
////	bool isAI;
////public:
////	Snake snake;
////	Food food;
////	SnakeGame() { GameInit(); }
////	~SnakeGame() {}
////	// 游戏初始化
////	void GameInit() {
////		isAI = false;
////		snake.length = 3;
////		snake.speed = SPEED;
////		snake.acc = 0;
////		snake.direct = UP;
////		while (!snake.coor.empty()) {
////			snake.coor.pop_back();
////		}
////		Coor body(MAP_ROWNUM / 2, MAP_COLNUM / 2);
////		for (int i = 0; i < snake.length; i++) {
////			snake.coor.push_back(body);
////			body.y++;
////		}
////		srand((unsigned)time(0));
////		food.RandCoor(MAP_COLNUM, MAP_ROWNUM);
////	}
////	// 画地图
////	void DrawMap() {
////		setfillcolor(DARKGRAY);
////		solidrectangle(0, 0, GRID * MAP_COLNUM, GRID * MAP_ROWNUM);
////		setcolor(LIGHTGRAY);
////		line(WINDOW_HEIGHT, 0, WINDOW_HEIGHT, WINDOW_HEIGHT);
////		// 画食物
////		setfillcolor(RED);
////		fillrectangle(food.coor.x * GRID + GRIDGAP, food.coor.y * GRID + GRIDGAP,
////			(food.coor.x + 1) * GRID - GRIDGAP, (food.coor.y + 1) * GRID - GRIDGAP);
////		// 画蛇
////		setfillcolor(WHITE);
////		Coor temp = snake.coor.front();
////		for (auto iter : snake.coor) {
////			solidrectangle(iter.x * GRID + GRIDGAP, iter.y * GRID + GRIDGAP,
////				(iter.x + 1) * GRID - GRIDGAP, (iter.y + 1) * GRID - GRIDGAP);
////			// 画缝隙
////			int iter_x = iter.x * GRID + GRIDGAP;
////			int iter_y = iter.y * GRID + GRIDGAP;
////			int temp_x = temp.x * GRID + GRIDGAP;
////			int temp_y = temp.y * GRID + GRIDGAP;
////			if (temp.x == iter.x) {
////				if (iter.y > temp.y) {
////					solidrectangle(temp_x, temp_y + _GRID, iter_x + _GRID, iter_y);
////				}
////				if (iter.y < temp.y) {
////					solidrectangle(iter_x, iter_y + _GRID, temp_x + _GRID, temp_y);
////				}
////			}
////			if (temp.y == iter.y) {
////				if (iter.x > temp.x) {
////					solidrectangle(temp_x + _GRID, temp_y, iter_x, iter_y + _GRID);
////				}
////				if (iter.x < temp.x) {
////					solidrectangle(iter_x + _GRID, iter_y, temp_x, temp_y + _GRID);
////				}
////			}
////			temp = iter;
////		}
////	}
////	// 处理吃食物
////	void EatFood() {
////		Coor head = snake.coor.front();
////		if (head == food.coor) {
////			food.EXISTFOOD = false;
////			snake.coor.push_back(snake.coor.back());
////			snake.length++;
////		}
////	}
////	// 产生食物
////	void CreatFood() {
////		if (food.EXISTFOOD == false) {
////			list<Coor>::const_iterator iter;
////			while (true) {
////				food.RandCoor(MAP_COLNUM, MAP_ROWNUM);
////				if (!onSnake(food.coor))
////					break;
////			}
////			food.EXISTFOOD = true;
////		}
////	}
////	// 判断游戏结束
////	bool GameOver() {
////		Coor head = snake.coor.front();
////		if (!inBorder(head) || onSnake_ExceptHead(head) || EatFullScreen()) {
////			return true;
////		}
////		return false;
////	}
////	// 是否吃满食物
////	bool EatFullScreen() {
////		return snake.length == MAP_COLNUM * MAP_ROWNUM;
////	}
////	// 游戏结束画面
////	void ShowGameEnd() {
////		setfillcolor(BLACK);
////		// 在屏幕中央输出字符串
////		TCHAR* str_end = (TCHAR*)("GAME OVER!");
////		if (EatFullScreen())
////			str_end = (TCHAR*)("YOU WIN!");
////		int Tstrlen = (int)_tcslen(str_end);
////		outtextxy(WINDOW_HEIGHT / 2 - Tstrlen * 20 / 4, WINDOW_HEIGHT / 2 - 20 / 4, str_end);
////	}
////	// 绘制游戏相关信息
////	void ShowGameInfo() {
////		// 填充黑色底
////		setfillcolor(BLACK);
////		solidrectangle(WINDOW_HEIGHT, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
////		// 尺寸信息
////		TCHAR str_mapsize[20];
////		swprintf_s(str_mapsize, _T("MAPSIZE:  %d×%d"), MAP_COLNUM, MAP_ROWNUM);
////		settextcolor(WHITE);
////		outtextxy(WINDOW_HEIGHT + 20, 20, str_mapsize);
////		// AI状态信息
////		TCHAR* str_ai = (TCHAR * )("AI:  OFF");
////		if (isAI == true)	str_ai = (TCHAR*)("AI:  ON");
////		outtextxy(WINDOW_HEIGHT + 20, 50, str_ai);
////		// 速度信息
////		TCHAR str_speed[20];
////		swprintf_s(str_speed, _T("SPEED:  %d"), snake.speed + snake.acc);
////		outtextxy(WINDOW_HEIGHT + 20, 80, str_speed);
////		// 加速度信息
////		TCHAR str_acc[20];
////		swprintf_s(str_acc, _T("ACC:  %d"), snake.acc);
////		outtextxy(WINDOW_HEIGHT + 20, 110, str_acc);
////		// 蛇长度信息
////		TCHAR str_life[20];
////		swprintf_s(str_life, _T("LIFE:  %d/%d"), snake.length, MAP_COLNUM * MAP_ROWNUM);
////		outtextxy(WINDOW_HEIGHT + 20, 140, str_life);
////		// 保存结点,使用引用是为了处理尾巴设置为可走结点
////		const Coor& snakeHead = snake.coor.front();
////		const Coor& snakeTail = snake.coor.back();
////		// 食物坐标信息
////		TCHAR str_food[20];
////		swprintf_s(str_food, _T("食物坐标:  (%d,%d)"), food.coor.x, food.coor.y);
////		outtextxy(WINDOW_HEIGHT + 20, 200, str_food);
////		// 蛇头坐标信息
////		TCHAR str_head[20];
////		swprintf_s(str_head, _T("蛇头坐标:  (%d,%d)"), snakeHead.x, snakeHead.y);
////		outtextxy(WINDOW_HEIGHT + 20, 230, str_head);
////		// 蛇尾坐标信息
////		TCHAR str_tail[20];
////		swprintf_s(str_tail, _T("蛇尾坐标:  (%d,%d)"), snakeTail.x, snakeTail.y);
////		outtextxy(WINDOW_HEIGHT + 20, 260, str_tail);
////		// 方向信息
////		TCHAR* str_dir;
////		switch (snake.direct) {
////		case RIGHT:	str_dir = (TCHAR*)("方向:  RIGHT");	break;
////		case DOWN:	str_dir = (TCHAR*)("方向:  DOWN");		break;
////		case LEFT:	str_dir = (TCHAR*)("方向:  LEFT"); 	break;
////		case UP:	str_dir = (TCHAR*)("方向:  UP");		break;
////		default:	str_dir = (TCHAR*)("方向:  None");
////		}
////		outtextxy(WINDOW_HEIGHT + 20, 290, str_dir);
////		// 游戏操作说明
////		outtextxy(WINDOW_HEIGHT + 20, 320, _T("操作说明:"));
////		outtextxy(WINDOW_HEIGHT + 20, 340, _T("使用方向键控制"));
////		outtextxy(WINDOW_HEIGHT + 20, 360, _T("长按方向键加速"));
////		outtextxy(WINDOW_HEIGHT + 20, 380, _T("上  :      ↑"));
////		outtextxy(WINDOW_HEIGHT + 20, 400, _T("下  :      ↓"));
////		outtextxy(WINDOW_HEIGHT + 20, 420, _T("左  :      ←"));
////		outtextxy(WINDOW_HEIGHT + 20, 440, _T("右  :      →"));
////	}
////
////	char getNextCmd() {
////		return _getch();
////	}
////
////	// 坐标在蛇上/包括蛇头蛇尾
////	bool onSnake(Coor coor) {
////		for (auto iter : snake.coor) {
////			if (coor == iter) {
////				return true;
////			}
////		}
////		return false;
////	}
////	// 坐标在蛇上/不包括蛇头
////	bool onSnake_ExceptHead(Coor coor) {
////		auto iter = snake.coor.begin();
////		for (iter++; iter != snake.coor.end(); iter++) {
////			if (coor == *iter) {
////				return true;
////			}
////		}
////		return false;
////	}
////	// 坐标在蛇上/不包括蛇尾
////	bool onSnake_ExceptTail(Coor coor) {
////		auto iter = snake.coor.begin();
////		auto flag = --snake.coor.end();
////		for (; iter != flag; iter++) {
////			if (coor == *iter) {
////				return true;
////			}
////		}
////		return false;
////	}
////	// 坐标在方框里
////	bool inBorder(Coor coor)const {
////		return (coor.x >= 0 && coor.x < MAP_COLNUM&& coor.y >= 0 && coor.y < MAP_ROWNUM);
////	}
////};
////
////// 程序入口
////int main() {
////	// 加参数, SHOWCONSOLE开启控制台
////	initgraph(WINDOW_WIDTH, WINDOW_HEIGHT);
////	// 开启双缓冲绘图
////	BeginBatchDraw();
////	SnakeGame SG;
////	_getch();
////	while (true) {
////		SG.EatFood();
////		SG.CreatFood();
////		SG.snake.TurnDirect(SG.getNextCmd());
////		SG.snake.Move();
////		SG.ShowGameInfo();
////		if (SG.GameOver()) {
////
////			_getch();
////			SG.GameInit();
////		}
////		SG.DrawMap();
////		FlushBatchDraw();
////		Sleep(1000 / (SG.snake.speed + SG.snake.acc));
////	}
////	EndBatchDraw();
////
////	closegraph();
////	return 0;
////}
//
//
//
////#include <easyx.h>      // 引用图形库头文件
////#include <conio.h>
////#include <stdio.h>
////#include <string.h>
////
////constexpr auto N = 4;
////
////FILE* fp;
////
//////声明
////void registers();
////void Login();
////void score();
////int compInc(const void* a, const void* b);
////int compDec(const void* a, const void* b);
////
//////结构体定义
////typedef struct The_users //用于储存用户账号密码
////{
////    char id[11];//ID
////    char pwd[20];//password
////}users;
////users a, b;
////
////
//////全局变量定义
////wchar_t temp[20];
////int i, j, k, m, n, s[N];
////wchar_t s1[5], s2[5];
////
////char* wchar2char(const wchar_t* wchar)
////{
////    char* m_char;
////    int len = WideCharToMultiByte(CP_ACP, 0, wchar, wcslen(wchar), NULL, 0, NULL, NULL);
////    m_char = new char[len + 1];
////    WideCharToMultiByte(CP_ACP, 0, wchar, wcslen(wchar), m_char, len, NULL, NULL);
////    m_char[len] = '\0';
////    return m_char;
////}
////
////void registers()//注册账号密码
////{
////    fopen_s(&fp, "Users1.txt", "r");
////    fscanf_s(fp, "%s%s", b.id, sizeof(b.id), b.pwd, sizeof(b.pwd));
////    InputBox(temp, 11, L"请输入账号");
////    strcpy_s(a.id, wchar2char(temp));
////    while (1)
////    {
////        if (strcmp(a.id, b.id) != 0)//如果两串字符串不相等
////        {
////            if (!feof(fp))//如果未至文件末尾
////            {
////                fscanf_s(fp, "%s%s", b.id, sizeof(b.id), b.pwd, sizeof(b.pwd));
////            }
////            else break;
////        }
////        else
////        {
////            outtextxy(220, 200, L"此用户名已被注册");
////            fclose(fp);
////            _getch();
////            exit(0);
////        }
////    }
////    fclose(fp);
////    InputBox(temp, 10, L"请输入密码");
////    strcpy_s(a.pwd, wchar2char(temp));
////    fopen_s(&fp, "Users1_test.txt", "a");
////    fprintf_s(fp, "%s %s\n", a.id, a.pwd);
////    outtextxy(220, 200, L"账号注册成功！");
////    fclose(fp);
////}
////void Login()//登陆账号密码
////{
////    fopen_s(&fp, "Users1_test.txt", "r");
////    fscanf_s(fp, "%s%s", b.id, sizeof(b.id), b.pwd, sizeof(b.pwd));
////    InputBox(temp, 11, L"请输入账号");
////    strcpy_s(a.id, wchar2char(temp));
////    while (1)
////    {
////        if (strcmp(a.id, b.id) == 0) break;//如果找到了这个用户名
////        else
////        {
////            if (!feof(fp))//如果文件未读完
////                fscanf_s(fp, "%s%s", b.id, sizeof(b.id), b.pwd, sizeof(b.pwd));
////            else
////            {
////                outtextxy(220, 200, L"此用户名不存在!");
////                fclose(fp);
////                _getch();
////                exit(0);
////            }
////        }
////    }
////    InputBox(temp, 20, L"请输入密码");
////    strcpy_s(a.pwd, wchar2char(temp));
////    if (strcmp(a.pwd, b.pwd) == 0)//如果密码匹配
////    {
////        fclose(fp);
////        outtextxy(250, 200, L"登陆成功！");
////        initgraph(640, 480);
////    }
////    else
////    {
////        outtextxy(220, 200, L"密码不正确");
////        _getch();
////        exit(0);
////    }
////}
////void score()
////{
////    fopen_s(&fp, "scores_test.txt", "r");
////    for (n = 0; n < N - 1; n++)
////    {
////        fscanf_s(fp, "%d", &m);
////        s[n] = m;
////    }
////    s[N - 1] = 250;//snake.len - 3;
////    qsort(s, N, sizeof(s[0]), compDec);
////    fclose(fp);
////    fopen_s(&fp, "scores_test.txt", "w");
////    for (n = 0; n < N - 1; n++)
////    {
////        fprintf_s(fp, "%d\n", s[n]);
////    }
////    fclose(fp);
////}
////int compInc(const void* a, const void* b)
////{
////    return *(int*)a - *(int*)b;
////}//升序排序
////int compDec(const void* a, const void* b) {
////    return *(int*)b - *(int*)a;
////}//降序排序
////
////int main()
////{
////    initgraph(640, 480);//创建绘图窗口
////    registers();
////    Login();
////    score();
////    return 0;
////}
////
