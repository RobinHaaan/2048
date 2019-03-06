//δ���Bug����������ֻ��ʹ�ù̶�������ƶ�ʱ��ʹ�ò�ǡ���ķ������ʹ��Ϸ����



//BUG���޷�������ӣ���������Կ�����Ϸ
//�������������flag���ڷ��������������ֺ���



#include <stdio.h>
#include <stdlib.h>     // for rand() and srand() and exit()
#include <time.h>       // for time()
#include <conio.h>      // for getch()
#include <windows.h>    // for system()

#define N     4         //���鳤��
#define ESC   0x1B      //ESC��ASCII��
#define UP    72        //������ϵ�ASCII��
#define DOWN  80        //������µ�ASCII��
#define LEFT  75        //��������ASCII��
#define RIGHT 77        //������ҵ�ASCII��

void Init(void);        // ��ʼ���������ֵ��һ�������ά����Ԫ�� 
void Draw(void);        // ����4 * 4����ͼ 
void Play(void);        // �����ƶ�����
void to_up(void);       // �����ƶ� 
void to_down(void);     // �����ƶ� 
void to_left(void);     // �����ƶ� 
void to_right(void);    // �����ƶ� 
void add_number(void);  // ���µ���

int arr[N][N];          //��ά����
int empty;              //��ǰ�ո���Ŀ
int flag = 0;           //�Ƿ������Ŀ���

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
	// һ������������������� 
	for(int i=0; i<N; i++)
	{
		int j = 0;
		
		// ��һ������ ÿ������֮��ռ4����
		for(j=0; j<N; j++)
		{
			printf("|    ");
		}
		printf("|\n");
		
		// �ڶ�������������
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
		
		 // ���������߼ӵ��� 
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
	int ch2 = getch();//�������Ҫ��ȡ����
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
			printf("��,��,��,�� || ESC exit");
			break;
	}
}

void to_up()
{
	//�ȼӺ���
	//���п�ʼ����
	for(int y=0; y<N; y++)
	{
		//�п�ʼ�����㣬�������£����һ�����迼��
		for(int x=0; x<N-1; x++)
		{
			if(0 == arr[x][y])
			{
				continue;
			}

			//���������ÿ�����
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
    printf("Control by:��,��,��,��\n"); 
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