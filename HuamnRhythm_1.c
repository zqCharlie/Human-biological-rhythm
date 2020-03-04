//����������ɲ�ѯ
#include <stdio.h>
#include <malloc.h>		//���ڹ�����̬�ṹ�����ڵĿ⺯��

//������ڵĽṹ��
struct Date
{
	int year;
	int month;
	int day;
};

int main(void)
{
	//�����������������ǰ��������ȫ�Ǳ���ģ�eg:�ڶ����͵�������ɾ����Ϊ�˸������
	void Input(struct Date *pDa);	//�ú������ڼ�������
	int leap(struct Date *qDa);		//�����ж��ж��Ƿ�Ϊ����
	int mid_leap(int x);			//�ж��м��꣨�У��ǲ�������
	int timeD(struct Date *mDa, struct Date *nDa);	//����ʱ���
	void Check(int z, int w, int r);				//���ɲ�ѯ��������

	//��������Ҫ�Ļ�������
	int s, t;				//�ֱ����ڴ洢���ص�ʱ���sum������forѭ��
	int j[3] = {23, 28, 33};//һ������
	int k[3] = {12, 14, 17};//�ٽ��
	char ch_1[20] = "����";
	char ch_2[20] = "����";
	char ch_3[20] = "����";

	//�������ڶ�̬�ṹ�壬�ֱ�������ų�����(born)��Ԥ����(pred)
	struct Date *born, *pred;
	born = (struct Date *)malloc(3 * sizeof(int));
	pred = (struct Date *)malloc(3 * sizeof(int));
	
	//------------------------������������---------------------------------------------------------
	printf("When were you born?\n");
	Input(born);
	putchar('\n');

	printf("What is the day you want to predict?\n");
	Input(pred);
	putchar('\n');

	//------------------�ж������Ƿ���ȷ���в�ȫ�棬�����ƣ�---------------------------------------
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

	//----------------------------���ɲ�ѯ---------------------------------------------
	for (t=0; t<3; ++t)
	{
		if (0==t)
			printf("%s���ɣ�\n", ch_1);
		else if (1==t)
			printf("%s���ɣ�\n", ch_2);
		else
			printf("%s���ɣ�\n", ch_3);

		Check(j[t], s, k[t]);
	}

	free(born);	//�ͷŶ�̬�ṹ��
	free(pred);

	return 0;
}

//�ú���������������պ�Ԥ��������
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

//�ж���ĩ���ǲ�������
int leap(struct Date *qDa)
{
	if (((qDa->year%4==0) && (qDa->year%100!=0)) || (qDa->year%400==0))
		return 1;
	else
		return 0;
}

//�ж��м��꣨�У��ǲ�������
int mid_leap(int x)
{
	int y;

	if (((x%4==0) && (x%100!=0)) || (x%400==0))
		y = 366;
	else
		y = 365;

	return y;
}

//�����ף�ĩ���м�������������sum
int timeD(struct Date *mDa, struct Date *nDa)
{
	int first = leap(mDa);
	int last = leap(nDa);
	int a[15] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, 28, 29};//������ÿ�µ�����
	int sum = 0;	//����ʱ���
	int b = mDa->month;
	int c = nDa->month;
	int d = mDa->year;
	int e = nDa->year;
	int i, j, k, l, f, g;
	

	//ִ������ѭ�����ֱ����������������Ԥ���������
	for (j=0; j<2; ++j)
	{
		//if���������������Ԥ�������ͬ��
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
		
		//���if�����Ƿ�Ϊ���꣬�������µ�����
		if (0==k)
			a[2] = a[13];
		else
			a[2] = a[14];

		//�ֱ����������������Ԥ���������
		for(i=f; i<=l; ++i)
			{	
				printf("\n\n%d\n", a[i]);
				sum += a[i];
				printf("\n\t%d", sum);
			}
	}

	//��������ݵ�����������еĻ���
	for (d=d+1; d<e; ++d)
	{
		g = mid_leap(d);
		sum += g;
		printf("\n\t%d", sum);
	}

	return sum;	//����������
}

//���ɲ�ѯ��������
void Check(int z, int w, int r)
{
	int mod;
	mod = w%z;

	if ( mod>r )
		printf("\t���ڵ͹��ڵ�%d��\n", mod-r);
	else if ( r==mod )
		printf("\t�������ٽ���\t����Ϊ�߳������ŵ͹���ת�䣩\n");
	else if ( 0==mod )
		printf("\t������������\t����Ϊһ���������ڵĿ��ˣ�\n");
	else
		printf("\t���ڸ߳��ڵ�%d��\n", mod);

	return ;
}