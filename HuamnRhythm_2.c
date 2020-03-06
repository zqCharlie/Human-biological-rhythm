//人体生物节律查询
#include <stdio.h>
#include <malloc.h>		//用于构建动态结构体所在的库函数
#include <time.h>		//获取当前时间

//存放日期的结构体
struct Date
{
	int year;
	int month;
	int day;
};

	int v;	//全局变量，用于循环和检测数据规范

int main(void)
{
	//声明：以下五个函数前置声明不全是必须的（eg:第二个可删），为了更好理解
	int Input(struct Date *pDa);	//该函数用于键入日期
	int leap(struct Date *qDa);		//用于判断判断是否为闰年
	int timeD(struct Date *mDa, struct Date *nDa);	//计算时间差
	void Check(int z, int w, int r);				//节律查询并输出结果
	int Worn(void);								//提示错误（警告作用）
	int timeBack(struct Date *tDa);		//获取当前的日期及时间并出做出初步判断

	//定义所需要的基本变量
	int s, t;				//分别用于存储返回的时间差sum；用于for循环
	int j[3] = {23, 28, 33};//一个周期
	int k[3] = {12, 14, 17};//临界点
	int back;
	char ch;

	//构建日期动态结构体，分别用来存放出生日(born)和预测日(pred)
	struct Date *born, *pred;
	born = (struct Date *)malloc(3 * sizeof(int));
	pred = (struct Date *)malloc(3 * sizeof(int));	
	
	do{
		//------------------------键入两个日期---------------------------------------------------------
		printf("\t\t\t\t\tHuman biorhythm inquiry\n");	//提示部分
		printf("\t\tINSTRUCTION: 测算必须使用公历(阳历)\n");

		for (v=0; v<2; ++v)
		{
			if (0==v)
			{
				printf("When were you born?\n");
				back = Input(born);
			}
			if (1==v)
			{
				printf("What is the day you want to predict?\n");
				back = Input(pred);
			}
			
			putchar('\n');

			//判断数据是否正确（主体部分）
			if (0==back)
				return 0;	//如果错误即终止
		}

		//判断数据是否正确（精细部分）
		back = timeD(born, pred);

		if (0==back)
			return 0;	//如果错误即终止

		s = back;
		putchar('\n');

		//----------------------------节律查询---------------------------------------------
		for (t=0; t<3; ++t)
		{
			if (0==t)
				printf("体力节律：\n");
			else if (1==t)
				printf("情绪节律：\n");
			else
				printf("智力节律：\n");

			Check(j[t], s, k[t]);
		}

		printf("\t\t\tWould you want to again ?(y/n): _\b");
		scanf(" %c", &ch);

		putchar('\n');
		putchar('\n');
		
	} while(('y'==ch) || ('Y'==ch));


	free(born);	//释放动态结构体
	free(pred);

	return 0;
}

//该函数输入出生年月日和预测年月日
int Input(struct Date *pDa)
{
	printf("year: ____\b\b\b\b");
	scanf("%d", &pDa->year);

	printf("month: __\b\b");
	scanf("%d", &pDa->month);

	printf("day: __\b\b");
	scanf("%d", &pDa->day);

	return timeBack(pDa);	//返回真假判断值
}

//判断首末年是不是闰年
int leap(struct Date *qDa)
{
	if (((qDa->year%4==0) && (qDa->year%100!=0)) || (qDa->year%400==0))
		return 1;
	else
		return 0;
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
	int p = mDa->day;
	int q = nDa->day;
	int i, j, k, l, g, o, yea;
	int f = -1;

	//执行两次循环，分别计算出生年的天数和预测年的天数
	for (j=0; j<2; ++j)
	{
		//if用来调整出生年和预测年的异同点
		if (0==j)	
		{
			k = first;
			l = b;
			o = p;
			yea = d;
		}
		else
		{
			k = last;
			l = c;
			o = q;
			f = 1;
			yea = e;
		}
		
		//这个if根据是否为闰年，决定二月的天数
				if (0==k)
					a[2] = a[13];
				else
					a[2] = a[14];

		//------------------判断数据是否正确（次要部分，精细(日)判断）--------------------------
		if ( (d+120)<e )
		{
			printf("\aYou are a short-lived ghost. Stop dreaming of a long life\n");
			return 0;
		}
		else if (o > a[l])
		{
			Worn();
			printf("%d年 %d月份 有%d天\n", yea, l,a[l]);
			return 0;
		}

		//分别计算出生年的天数和预测年的天数
		for(i=1; i<l; ++i)
			{	
				printf("\n\n%d\n", a[i]);
				sum += a[i]*f;
				printf("\n\t%d", sum);
			}
		sum += o*f; 
		printf("\n\t%d", sum);
	}

	//求其他年份的天数（如果有的话）
	sum = sum + (nDa->year-mDa->year)*365;
	printf("\n\t\t%d, %d, %d", sum, nDa->year, mDa->year);

	for (d=d+1; d<e; ++d)
	{
		mDa->year += 1;
		g = leap(mDa);
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

//提示错误（警告作用）
int Worn(void)
{
		printf("\a\nYou must be dreaming!\n\tWake up now!!\n");
		return 0;
}

//获取当前的日期及时间并出做出初步判断
int timeBack(struct Date *tDa)
{
	int bac = 1;
	int a = tDa->year;
	int b = tDa->month;
	int c = tDa->day;
	int d, e, f;
	int i;
	
	//获取当前时间
	time_t timep;
	struct tm *p;
	time (&timep);
	p=gmtime(&timep);

	d = 1900+p->tm_year;	//获取当前年月日
	e = 1+p->tm_mon;
	f = p->tm_mday;

	//打印当前时间
	printf("\n\t\tGMT+8:00 中国标准时间:\t%d/%d/%d", e, f, d);
	printf("\n\t\t\t\t\t\t%d: %d\' %d\"\n",
				8+p->tm_hour, p->tm_min, p->tm_sec);	//获取当前时分秒

	//第二次输入数据时对预测日和当前时间进行交换
	if (1==v)
	{
		i = a;	//分别交换年月日
		a = d;
		d = i;

		i = b;
		b = e;
		e = i;

		i = c;
		c = f;
		f = i;	
	}
	
	//------------------判断数据是否正确（主要部分，大致判断）---------------------------------------
	if ( (a<1900) || (a>2200) ||(b>12) || (b<1) || (c<1)|| (c>31) )
		bac = Worn();	
	else if ( a > d)
		bac = Worn();	
	else if (a == d)
	{
		if (b > e)
			bac = Worn();
		else if (b == e)
			{
				if (c > f)
					bac = Worn();
			}
	}

	return bac;	//真
}