//����������ɲ�ѯ
#include <stdio.h>
#include <malloc.h>		//���ڹ�����̬�ṹ�����ڵĿ⺯��
#include <time.h>		//��ȡ��ǰʱ��

//������ڵĽṹ��
struct Date
{
	int year;
	int month;
	int day;
};

	int v;	//ȫ�ֱ���������ѭ���ͼ�����ݹ淶

int main(void)
{
	//�����������������ǰ��������ȫ�Ǳ���ģ�eg:�ڶ�����ɾ����Ϊ�˸������
	int Input(struct Date *pDa);	//�ú������ڼ�������
	int leap(struct Date *qDa);		//�����ж��ж��Ƿ�Ϊ����
	int timeD(struct Date *mDa, struct Date *nDa);	//����ʱ���
	void Check(int z, int w, int r);				//���ɲ�ѯ��������
	int Worn(void);								//��ʾ���󣨾������ã�
	int timeBack(struct Date *tDa);		//��ȡ��ǰ�����ڼ�ʱ�䲢�����������ж�

	//��������Ҫ�Ļ�������
	int s, t;				//�ֱ����ڴ洢���ص�ʱ���sum������forѭ��
	int j[3] = {23, 28, 33};//һ������
	int k[3] = {12, 14, 17};//�ٽ��
	int back;
	char ch;

	//�������ڶ�̬�ṹ�壬�ֱ�������ų�����(born)��Ԥ����(pred)
	struct Date *born, *pred;
	born = (struct Date *)malloc(3 * sizeof(int));
	pred = (struct Date *)malloc(3 * sizeof(int));	
	
	do{
		//------------------------������������---------------------------------------------------------
		printf("\t\t\t\t\tHuman biorhythm inquiry\n");	//��ʾ����
		printf("\t\tINSTRUCTION: �������ʹ�ù���(����)\n");

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

			//�ж������Ƿ���ȷ�����岿�֣�
			if (0==back)
				return 0;	//���������ֹ
		}

		//�ж������Ƿ���ȷ����ϸ���֣�
		back = timeD(born, pred);

		if (0==back)
			return 0;	//���������ֹ

		s = back;
		putchar('\n');

		//----------------------------���ɲ�ѯ---------------------------------------------
		for (t=0; t<3; ++t)
		{
			if (0==t)
				printf("�������ɣ�\n");
			else if (1==t)
				printf("�������ɣ�\n");
			else
				printf("�������ɣ�\n");

			Check(j[t], s, k[t]);
		}

		printf("\t\t\tWould you want to again ?(y/n): _\b");
		scanf(" %c", &ch);

		putchar('\n');
		putchar('\n');
		
	} while(('y'==ch) || ('Y'==ch));


	free(born);	//�ͷŶ�̬�ṹ��
	free(pred);

	return 0;
}

//�ú���������������պ�Ԥ��������
int Input(struct Date *pDa)
{
	printf("year: ____\b\b\b\b");
	scanf("%d", &pDa->year);

	printf("month: __\b\b");
	scanf("%d", &pDa->month);

	printf("day: __\b\b");
	scanf("%d", &pDa->day);

	return timeBack(pDa);	//��������ж�ֵ
}

//�ж���ĩ���ǲ�������
int leap(struct Date *qDa)
{
	if (((qDa->year%4==0) && (qDa->year%100!=0)) || (qDa->year%400==0))
		return 1;
	else
		return 0;
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
	int p = mDa->day;
	int q = nDa->day;
	int i, j, k, l, g, o, yea;
	int f = -1;

	//ִ������ѭ�����ֱ����������������Ԥ���������
	for (j=0; j<2; ++j)
	{
		//if���������������Ԥ�������ͬ��
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
		
		//���if�����Ƿ�Ϊ���꣬�������µ�����
				if (0==k)
					a[2] = a[13];
				else
					a[2] = a[14];

		//------------------�ж������Ƿ���ȷ����Ҫ���֣���ϸ(��)�жϣ�--------------------------
		if ( (d+120)<e )
		{
			printf("\aYou are a short-lived ghost. Stop dreaming of a long life\n");
			return 0;
		}
		else if (o > a[l])
		{
			Worn();
			printf("%d�� %d�·� ��%d��\n", yea, l,a[l]);
			return 0;
		}

		//�ֱ����������������Ԥ���������
		for(i=1; i<l; ++i)
			{	
				printf("\n\n%d\n", a[i]);
				sum += a[i]*f;
				printf("\n\t%d", sum);
			}
		sum += o*f; 
		printf("\n\t%d", sum);
	}

	//��������ݵ�����������еĻ���
	sum = sum + (nDa->year-mDa->year)*365;
	printf("\n\t\t%d, %d, %d", sum, nDa->year, mDa->year);

	for (d=d+1; d<e; ++d)
	{
		mDa->year += 1;
		g = leap(mDa);
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

//��ʾ���󣨾������ã�
int Worn(void)
{
		printf("\a\nYou must be dreaming!\n\tWake up now!!\n");
		return 0;
}

//��ȡ��ǰ�����ڼ�ʱ�䲢�����������ж�
int timeBack(struct Date *tDa)
{
	int bac = 1;
	int a = tDa->year;
	int b = tDa->month;
	int c = tDa->day;
	int d, e, f;
	int i;
	
	//��ȡ��ǰʱ��
	time_t timep;
	struct tm *p;
	time (&timep);
	p=gmtime(&timep);

	d = 1900+p->tm_year;	//��ȡ��ǰ������
	e = 1+p->tm_mon;
	f = p->tm_mday;

	//��ӡ��ǰʱ��
	printf("\n\t\tGMT+8:00 �й���׼ʱ��:\t%d/%d/%d", e, f, d);
	printf("\n\t\t\t\t\t\t%d: %d\' %d\"\n",
				8+p->tm_hour, p->tm_min, p->tm_sec);	//��ȡ��ǰʱ����

	//�ڶ�����������ʱ��Ԥ���պ͵�ǰʱ����н���
	if (1==v)
	{
		i = a;	//�ֱ𽻻�������
		a = d;
		d = i;

		i = b;
		b = e;
		e = i;

		i = c;
		c = f;
		f = i;	
	}
	
	//------------------�ж������Ƿ���ȷ����Ҫ���֣������жϣ�---------------------------------------
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

	return bac;	//��
}