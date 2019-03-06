//未解决Bug，在满格但是只能使用固定方向键移动时，使用不恰当的方向键会使游戏结束



//BUG：无法进行相加，按方向键仍可以游戏
//解决方案：增加flag，在方向函数中增加数字函数



#include <stdio.h>
#include <stdlib.h>     // for rand() and srand() and exit()
#include <time.h>       // for time()
#include <conio.h>      // for getch()
#include <windows.h>    // for system()

#define N     4         //数组长度
#define ESC   0x1B      //ESC的ASCII码
#define UP    72        //方向键上的ASCII码
#define DOWN  80        //方向键下的ASCII码
#define LEFT  75        //方向键左的ASCII码
#define RIGHT 77        //方向键右的ASCII码

void Init(void);        // 初始化数组跟赋值第一个随机二维数组元素 
void Draw(void);        // 绘制4 * 4方格图 
void Play(void);        // 控制移动方向
void to_up(void);       // 向上移动 
void to_down(void);     // 向下移动 
void to_left(void);     // 向左移动 
void to_right(void);    // 向右移动 
void add_number(void);  // 加新的数

int arr[N][N];          //二维数组
int empty;              //当前空格数目
int flag = 0;           //是否出现数目相加

void Init()
{
	for(int i=0; i<N; i++)
	{
		for(int j=0; j<N; j++)
		{
			arr[i][j] = 0;
		}
	}
	
	srand((unsigned int)time(NULL));
	int i = rand()%N;
	int j = rand()%N;
	
	arr[i][j] = 2;
	empty = 15;
}

void Draw()
{
	// 一个方格由三根竖线组成 
	for(int i=0; i<N; i++)
	{
		int j = 0;
		
		// 第一排竖线 每个竖线之间占4个格
		for(j=0; j<N; j++)
		{
			printf("|    ");
		}
		printf("|\n");
		
		// 第二排竖线与数字
		for(j=0; j<N; j++)
		{
			if(0 == arr[i][j])
			{
				printf("|    ");
			}
			else
			{
				printf("|%4d", arr[i][j]);
			}
		}
		printf("|\n");
		
		 // 第三排竖线加底线 
		for(j=0; j<N; j++)
		{
			printf("|____");
		}
		printf("|\n");
	}
}

void Play()
{
	int ch1 = getch();
	int ch2 = getch();//方向键需要获取两次
	if(ESC == ch1)
	{
		exit(0);
	}
	switch(ch2)
	{
		case UP:
			to_up();
			system("cls");
			add_number();
			Draw();
			break;
		case DOWN:
			to_down();
			add_number();
			system("cls");
			Draw();
			break;
		case LEFT:
			to_left();
			add_number();
			system("cls");
			Draw();
			break;
		case RIGHT:
			to_right();
			add_number();
			system("cls");
			Draw();
			break;
		default:
			printf("\nwrong type!!!\n");
			printf("\nplease type :\n");
			printf("↑,↓,←,→ || ESC exit");
			break;
	}
}

void to_up()
{
	//先加后移
	//从列开始遍历
	for(int y=0; y<N; y++)
	{
		//行开始加运算，从上往下，最后一个不需考虑
		for(int x=0; x<N-1; x++)
		{
			if(0 == arr[x][y])
			{
				continue;
			}

			//本行与后面每行相加
			for(int i=x+1; i<N; i++)
			{
				if(0 == arr[i][y])
				{
					continue;
				}
				else if(arr[x][y] == arr[i][y])
				{
					arr[x][y] += arr[i][y];
					arr[i][y] = 0;
					++empty;
					x = i;
					break;
				}
				else
				{
					x = i-1;
					break;
				}
			}
		}
	}

	flag = 0;
	for(int y=0; y<N; y++)
	{
		for(int x=0; x<N; x++)
		{
			if(0 == arr[x][y])
			{
				continue;
			}
			else
			{
				int i = x;
				while(i>0 && 0==arr[i-1][y])
				{
					arr[i-1][y] = arr[i][y];
					arr[i][y] = 0;
					i--;
					flag = 1;
				}
			}
		}
	}
}

void to_down()
{
	for(int y=0; y<N; y++)
	{
		for(int x=N-1; x>0; x--)
		{
			if(0 == arr[x][y])
			{
				continue;
			}

			for(int i=x-1; i>=0; i--)
			{
				if(0 == arr[i][y])
				{
					continue;
				}
				else if(arr[i][y] == arr[x][y])
				{
					arr[x][y] += arr[i][y];
					arr[i][y] = 0;
					empty++;
					x = i;
					break;
				}
				else
				{
					break;
				}
			}
		}
	}

	flag = 0;
	for(int y=0; y<N; y++)
	{
		for(int x=N-1; x>=0; x--)
		{
			if(0 == arr[x][y])
			{
				continue;
			}
			else
			{
				int i = x;
				while(i<N-1 && 0==arr[i+1][y])
				{
					arr[i+1][y] = arr[i][y];
					arr[i][y] = 0;
					i++;
					flag = 1;
				}
			}
		}
	}
}

void to_left()
{
	for(int x=0; x<N; x++)
	{
		for(int y=0; y<N-1; y++)
		{
			if(0 == arr[x][y])
			{
				continue;
			}

			for(int i=y+1; i<N; i++)
			{
				if(0 == arr[x][i])
				{
					continue;
				}
				else if(arr[x][i] == arr[x][y])
				{
					arr[x][y] += arr[x][i];
					arr[x][i] = 0;
					empty++;
					y = i;
					break;
				}
				else
				{
					break;
				}
			}
		}
	}

	flag = 0;
	for(int x=0; x<N; x++)
	{
		for(int y=0; y<N; y++)
		{
			if(arr[x][y] == 0)
			{
				continue;
			}
			else
			{
				int i = y;
				while(i>0 && 0 == arr[x][i-1])
				{
					arr[x][i-1] += arr[x][i];
					arr[x][i] = 0;
					i--;
					flag = 1;
				}
			}
		}
	}
}

void to_right()
{
	for(int x=0; x<N; x++)
	{
		for(int y=N-1; y>0; y--)
		{
			if(0 == arr[x][y])
			{
				continue;
			}

			for(int i=y-1; i>=0; i--)
			{
				if(0 == arr[x][i])
				{
					continue;
				}
				else if(arr[x][i] == arr[x][y])
				{
					arr[x][y] += arr[x][i];
					arr[x][i] = 0;
					empty++;
					y = i;
					break;
				}
				else
				{
					break;
				}
			}
		}
	}

	flag = 0;
	for(int x=0; x<N; x++)
	{
		for(int y=N-1; y>=0; y--)
		{
			if(0 == arr[x][y])
			{
				continue;
			}
			else
			{
				int i = y;
				while(i<N-1 && 0 == arr[x][i+1])
				{
					arr[x][i+1] = arr[x][i];
					arr[x][i] = 0;
					i++;
					flag = 1;
				}
			}
		}
	}
}

void add_number()
{
	if(empty <= 0)
	{
		exit(0);
	}

	if(0 == flag)
	{
		return ;
	}

	if(empty > 0)
	{
		srand((unsigned)time(NULL));
		int x = 0;
		int y = 0;
		do
		{
			x = rand()%N;
			y = rand()%N;
		}while(arr[x][y] != 0);

		int number = rand();
		int temp = number%3;
		if(2 == temp)
		{
			arr[x][y] = 4;
			empty--;
		}
		else
		{
			arr[x][y] = 2;
			empty--;
		}
	}

}



int main()
{
	printf("****************************\n"); 
    printf("            2048            \n\n"); 
    printf("Control by:↑,↓,←,→\n"); 
    printf("press ESC quit game!\n");
    printf("****************************\n"); 
    printf("Press any key to continue . . .\n"); 
    getch();
    system("cls"); 

	Init();
	Draw();
	while(1)
	{
		Play();
	}
	return 0;
}