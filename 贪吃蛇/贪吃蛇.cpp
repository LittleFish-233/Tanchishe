// 贪吃蛇.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#pragma warning(disable : 4996)
#pragma warning(disable : 6031)

#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>
#include<conio.h>


//屏幕大小
int x_s = 40, y_s = 20;
//苹果位置
int pingguo_x = 0, pingguo_y = 0;
//显示缓冲区
char a[100][100];
//记录蛇的位置 
char she[10000][2];
//上一次方向
int fangxiang_s = 1;
//蛇的长度
int she_chang = 0;
void weiqiang();
void pingguo();
void qingkong();
void xianshi();
void tangchishe();
void goto_xy(int x, int y);//定位光标位置到指定坐标
void HideCursor();
void yidong(int fangxiang);
void chuli_shuru(char x);
void tuichu();
void jieshu();
void gengxin_she_houyi(int x_n, int y_n, bool shifou_zenjia);
void chongzhi_pingguo();
void piliang(int n, char s);
void jieshu(int r);
void chushihua();

/// <summary>
/// 主函数
/// </summary>
/// <returns></returns>
int main()
{
	
	//隐藏光标
	HideCursor();
	//初始化
	chushihua();
    //循环
	while (true)
	{
		//清空数组
		qingkong();
		//显示围墙
		weiqiang();
		//显示苹果
		pingguo();
		//显示蛇
		tangchishe();

		//真实显示
		//system("CLS");
		goto_xy(0, 0);
		xianshi();

		//获取用户输入 非缓存
		char x = getch();
		//处理输入并更新蛇的位置
		chuli_shuru(x);

	}
}
/// <summary>
/// 初始化 第一个调用 配置游戏参数
/// </summary>
void chushihua()
{
	//第一个蛇的位置
	she[0][0] = x_s / 2;
	she[0][1] = y_s / 2;
	//蛇的长度
	she_chang = 1;
}
/// <summary>
/// 处理用户输入 调用蛇的移动函数
/// </summary>
/// <param name="x">用户输入的字符</param>
void chuli_shuru(char x)
{
	switch (x)
	{
	case 'Q':
		tuichu();

		break;
	case 'q':
		tuichu();

		break;
	case 'W':
		yidong(1);
		break;
	case 'S':
		yidong(2);
		break;
	case 'A':
		yidong(3);
		break;
	case 'D':
		yidong(4);
		break;
	case 'w':
		yidong(1);
		break;
	case 's':
		yidong(2);
		break;
	case 'a':
		yidong(3);
		break;
	case 'd':
		yidong(4);
		break;
	default:
		break;
	}
}
/// <summary>
/// 退出游戏
/// </summary>
void tuichu()
{
	system("CLS");
	piliang(y_s / 2, '\n');
	printf("再见\n\n");
	printf("2021年4月12日 17：40\n");
	printf("\nPowered By LittleFishTeam\n\n");
	Sleep(3000);
	exit(0);
}
/// <summary>
/// 结束游戏
/// </summary>
/// <param name="r">1撞到墙 2撞到自己</param>
void jieshu(int r)
{
	system("CLS");
	piliang(y_s / 2, '\n');
	printf("游戏结束\n");
	switch (r)
	{
	case 1:
		printf("死因：撞到墙\n");
		break;
	case 2:
		printf("死因：撞到自己\n");
		break;
	default:
		break;
	}
	printf("分数：%d\n",she_chang);
	printf("\n\nPowered By LittleFishTeam\n\n");
	Sleep(1000);
	system("PAUSE");

	//恢复初始状态
	chushihua();
}
/// <summary>
/// 批量显示字符
/// </summary>
/// <param name="n">显示的次数</param>
/// <param name="s">显示的字符</param>
void piliang(int n, char s)
{
	for (int i = 0; i < n; i++)
	{
		printf("%c", s);
	}
}
/// <summary>
/// 贪吃蛇移动
/// </summary>
/// <param name="fangxiang">1上 2下 3左 4右</param>
void yidong(int fangxiang)
{
	//记录当前方向
	fangxiang_s = fangxiang;
	//当前位置
	int x_linshi = she[0][0];
	int y_linshi = she[0][1];
	//移动
	switch (fangxiang)
	{
	case 1:
		y_linshi--;
		break;
	case 2:
		y_linshi++;
		break;
	case 3:
		x_linshi--;
		break;
	case 4:
		x_linshi++;
		break;
	default:
		break;
	}
	//判断是否有问题 撞墙
	if (x_linshi == 0 || x_linshi == x_s - 1 || y_linshi == 0 || y_linshi == y_s-1)
	{
		//游戏结束
		jieshu(1);
		return;
	}
	//撞到自己
	for (int i = 1; i < she_chang; i++)
	{
		if (she[i][0] == x_linshi && she[i][1] == y_linshi)
		{
			jieshu(2);
			return;
		}
	}
	//判断是否吃到苹果
	if (x_linshi == pingguo_x && y_linshi == pingguo_y)
	{
		//更新蛇的身体坐标记录
		gengxin_she_houyi(x_linshi, y_linshi, true);
		//苹果被吃后重置
		chongzhi_pingguo();
	}
	else
	{
		//更新蛇的身体坐标记录
		gengxin_she_houyi(x_linshi, y_linshi, false);
	}
}
/// <summary>
/// 更新蛇的身体坐标记录
/// </summary>
/// <param name="x_n">当前x坐标</param>
/// <param name="y_n">当前y坐标</param>
/// <param name="shifou_zenjia">是否吃到苹果，长度+1</param>
void gengxin_she_houyi(int x_n,int y_n,bool shifou_zenjia)
{
	//整体后移一格
	for (int i = she_chang-1; i>=0; i--)
	{
		she[i + 1][0] = she[i][0];
		she[i + 1][1] = she[i][1];
	}
	//将新的坐标插入
	she[0][0] = x_n;
	she[0][1] = y_n;
	//如果吃到苹果则整个长度加1，否则后移的最后一个数据会被忽略
	if (shifou_zenjia == true)
	{
		she_chang++;
	}
}
/// <summary>
/// 重置苹果的坐标
/// </summary>
void chongzhi_pingguo()
{
	//随机数种子
	srand(unsigned(time(NULL)));
	pingguo_x = 1 + rand() % (x_s - 2);
	pingguo_y = 1 + rand() % (y_s - 2);
}
/// <summary>
/// 清空显示缓冲区
/// </summary>
void qingkong()
{
	//清空数组
	for (int i = 0; i < x_s; i++)
	{
		for (int j = 0; j < y_s; j++)
		{
			a[i][j] = ' ';
		}
	}
}
/// <summary>
/// 显示围墙
/// </summary>
void weiqiang()
{
	for (int i = 0; i < x_s; i++)
	{
		a[i][0] = '#';
		a[i][y_s - 1] = '#';
	}
	for (int i = 0; i < y_s; i++)
	{
		a[0][i] = '#';
		a[x_s-1][i] = '#';
	}
}
/// <summary>
/// 显示苹果
/// </summary>
void pingguo()
{
	if (pingguo_x == 0 || pingguo_y == 0)
	{
		chongzhi_pingguo();
	}
	a[pingguo_x][pingguo_y] = '@';
}
/// <summary>
/// 显示贪吃蛇
/// </summary>
void tangchishe()
{
	//显示第一个蛇的格子  根据方向不同显示不同的字符
	switch (fangxiang_s)
	{
	case 1:
		a[she[0][0]][she[0][1]] = '+';
		break;
	case 2:
		a[she[0][0]][she[0][1]] = '+';
		break;
	case 3:
		a[she[0][0]][she[0][1]] = '<';
		break;
	case 4:
		a[she[0][0]][she[0][1]] = '>';
		break;
	default:
		break;
	}
	//遍历剩余的记录 显示
	for (int i = 1; i < she_chang; i++)
	{
		a[she[i][0]][she[i][1]] = '-';
	}
}
/// <summary>
/// 根据缓冲区数据输出到屏幕
/// </summary>
void xianshi()
{
	for (int i = 0; i < y_s; i++)
	{
		for (int j = 0; j < x_s; j++)
		{
			printf("%c",a[j][i]);
		}
		printf("\n");
	}
	//显示信息
	printf("按Q退出       分数：%d", she_chang);
}
//定位光标位置到指定坐标
void goto_xy(int x, int y)
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { x,y };
	SetConsoleCursorPosition(hOut, pos);
}

//定义隐藏光标函数
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor;
	cursor.bVisible = FALSE;
	cursor.dwSize = sizeof(cursor);
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorInfo(handle, &cursor);
}


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
