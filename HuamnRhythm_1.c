//人体生物节律查询
#include <stdio.h>
#include <malloc.h>		//用于构建动态结构体所在的库函数

//存放日期的结构体
struct Date
{
	int year;
	int month;
	int day;
};

int main(void)
{
	//声明：以下五个函数前置声明不全是必须的（eg:第二个和第三个可删），为了更好理解
	void Input(struct Date *pDa);	//该函数用于键入日期
	int leap(struct Date *qDa);		//用于判断判断是否为闰年
	int mid_leap(int x);			//判断中间年（有）是不是闰年
	int timeD(struct Date *mDa, struct Date *nDa);	//计算时间差
	void Check(int z, int w, int r);				//节律查询并输出结果

	//定义所需要的基本变量
	int s, t;				//分别用于存储返回的时间差sum；用于for循环
	int j[3] = {23, 28, 33};//一个周期
	int k[3] = {12, 14, 17};//临界点
	char ch_1[20] = "节律";
	char ch_2[20] = "情绪";
	char ch_3[20] = "智力";

	//构建日期动态结构体，分别用来存放出生日(born)和预测日(pred)
	struct Date *born, *pred;
	born = (struct Date *)malloc(3 * sizeof(int));
	pred = (struct Date *)malloc(3 * sizeof(int));
	
	//------------------------键入两个日期---------------------------------------------------------
	printf("When were you born?\n");
	Input(born);
	putchar('\n');

	printf("What is the day you want to predict?\n");
	Input(pred);
	putchar('\n');

	//------------------判断数据是否正确（尚不全面，待完善）---------------------------------------
	if ( ((born->month)>12) || ((born->month)<1) || ((born->day)<1)|| ((born->day)>31) )
	{
		printf("\aYou must be dreaming!\n\tWake up now!!\n");
		return 0;
	}
	else if ( ((pred->month)>12) || ((pred->month)<1) || ((pred->day)<1)|| ((pred->day)>31) )
	{
		printf("\aYou must be dreaming!\n\tWake up now!!\n");
		return 0;
	}	
	
	else if ((born->year) > (pred->year))
	{
		printf("\aYou must be dreaming!\n\tWake up now!!\n");
		return 0;
	}
	else if ((born->year) == (pred->year))
	{
		if ((born->month) > (pred->month))
			{
				printf("\aYou must be dreaming!\n\tWake up now!!\n");
				return 0;
			}
		else if ((born->month) == (pred->month))
			{
				if ((born->day) >= (pred->day))
					{
						printf("\aYou must be dreaming!\n\tWake up now!!\n");
						return 0;
					}
			}
	}
	
	s = timeD(born, pred);
	putchar('\n');

	//----------------------------节律查询---------------------------------------------
	for (t=0; t<3; ++t)
	{
		if (0==t)
			printf("%s节律：\n", ch_1);
		else if (1==t)
			printf("%s节律：\n", ch_2);
		else
			printf("%s节律：\n", ch_3);

		Check(j[t], s, k[t]);
	}

	free(born);	//释放动态结构体
	free(pred);

	return 0;
}

//该函数输入出生年月日和预测年月日
void Input(struct Date *pDa)
{
	printf("year: ____\b\b\b\b");
	scanf("%d", &pDa->year);

	printf("month: __\b\b");
	scanf("%d", &pDa->month);

	printf("day: __\b\b");
	scanf("%d", &pDa->day);

	return ;
}

//判断首末年是不是闰年
int leap(struct Date *qDa)
{
	if (((qDa->year%4==0) && (qDa->year%100!=0)) || (qDa->year%400==0))
		return 1;
	else
		return 0;
}

//判断中间年（有）是不是闰年
int mid_leap(int x)
{
	int y;

	if (((x%4==0) && (x%100!=0)) || (x%400==0))
		y = 366;
	else
		y = 365;

	return y;
}

//计算首，末，中间的天数差，并返回sum
int timeD(struct Date *mDa, struct Date *nDa)
{
	int first = leap(mDa);
	int last = leap(nDa);
	int a[15] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, 28, 29};//非闰年每月的天数
	int sum = 0;	//计算时间差
	int b = mDa->month;
	int c = nDa->month;
	int d = mDa->year;
	int e = nDa->year;
	int i, j, k, l, f, g;
	

	//执行两次循环，分别计算出生年的天数和预测年的天数
	for (j=0; j<2; ++j)
	{
		//if用来调整出生年和预测年的异同点
		if (0==j)	
		{
			k = first;
			l = 12;
			f = b;
			a[b] -= mDa->day;
		}
		else
		{
			k = last;
			l = c;
			f = 1;
			a[c] = nDa->day;
		}
		
		//这个if根据是否为闰年，决定二月的天数
		if (0==k)
			a[2] = a[13];
		else
			a[2] = a[14];

		//分别计算出生年的天数和预测年的天数
		for(i=f; i<=l; ++i)
			{	
				printf("\n\n%d\n", a[i]);
				sum += a[i];
				printf("\n\t%d", sum);
			}
	}

	//求其他年份的天数（如果有的话）
	for (d=d+1; d<e; ++d)
	{
		g = mid_leap(d);
		sum += g;
		printf("\n\t%d", sum);
	}

	return sum;	//返回天数差
}

//节律查询并输出结果
void Check(int z, int w, int r)
{
	int mod;
	mod = w%z;

	if ( mod>r )
		printf("\t处于低谷期第%d天\n", mod-r);
	else if ( r==mod )
		printf("\t正处于临界日\t（即为高潮期向着低谷期转变）\n");
	else if ( 0==mod )
		printf("\t正处于周期日\t（即为一个完整周期的开端）\n");
	else
		printf("\t处于高潮期第%d天\n", mod);

	return ;
}