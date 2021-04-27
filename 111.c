#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#include<string.h>


int _(void)    // 普通数据输入
{
	char val[11] = {0};  				  // 把数组初始化为'\0' ，（
	int temp;
	int key = 1;
	key = scanf("%[9-0]", val); 	      // 不能有空格

	while(key == 0 || getchar() != '\n')  // 利用返回值判断是否正确输入（读取失败返回0），如果不是读取失败，就判断是否有非法输入（前后关系不能乱）
	{
		if(key == 0 || getchar() != '\n') // 空输入或非法输入时清除缓存（空输入时就不可能是非法输入）
		{
			key = 1;
			while(getchar() != '\n');
		}
		printf("\t输入错误，请重新输入：");
		key = scanf("%[9-0]", val);
	}
	temp = atoi(val);
	return temp;
}

void show(void)          // 主菜单显示
{
	printf("\n\n\n\t\t     ************************************\n");
	printf("\t\t     *  万年历，可按以下方法进行查询：  *\n");
	printf("\t\t     *  1、判断该年是否是闰年。         *\n");
	printf("\t\t     *  2、求该日是当年的第多少天。     *\n");
        printf("\t\t     *  3、按年份查看日历。             *\n");
	printf("\t\t     *  0、退出程序。                   *\n");
	printf("\t\t     ************************************\n");
	printf("\n\t################################################################\n\t请输入选项：");
	return;
}

void judge()
{
        int year,leap;
        printf("\t请输入年份：");
        scanf("%d",&year);
        if(year%4==0)
        {
                if(year%100==0)
                {
                        if(year%400==0)
                                leap=1;
                        else
                                leap=0;
                }else
                        leap=1;
        }
        else
                leap=0;

        if(leap)
        {
                printf("\t%d年是",year);
        }else
                printf("\t%d年不是",year);

        printf("闰年.\n");
        return ;
}

int MaxDay(int year, int month)      // 返回该月最大天数
{
	int day;
	if(((month>0) && (month<8) && (month%2 != 0)) || ((month>7) && (month<13) && (month%2 == 0)))
	{
		day = 31;
	}
	else if(month == 2)
	{
		if(((year%4 == 0) && (year%100 !=0)) || (year%400 == 0))
		{
			day = 29;
		}
		else
		{
			day = 28;
		}
	}
	else
	{
		day = 30;
	}
	return day;
}

int ScanfYear(void)        // 输入年份
{
	int year;
	printf("\t请输入年份：");
	year = _();
	while((year<1) || (year>10000))
	{
		printf("\t年份输入有误，重新输入：");
		year = _();
	}
	return year;
}

int ScanfMonth(void)        // 输入月份
{
	int month;
	printf("\t请输入月份：");
	month = _();
	while((month<1) || (month>12))
	{
		printf("\t月份输入有误，重新输入：");
		month = _();
	}
	return month;
}




int ScanfDay(int year, int month)     // 输入天数
{
	int day;
	int max;
	max = MaxDay(year, month);
	printf("\t请输入日数：");
	day = _();
	while((day<1) || (day>max))
	{
		printf("\t日数输入有误，重新输入：");
		day = _();
	}
	return day;
}


int SumDay(int year, int month, int day)       // 求总天数 并返回
{
	int SumLeapYear;
	int SumCommonYear;
	int Sumday;
	int i;
	SumLeapYear = ((year-1) / 4) - ((year-1) / 100) + ((year-1) / 400);  // 因为要求的年份还没过去，所以要减1
	SumCommonYear = year - SumLeapYear - 1;
	Sumday = (SumLeapYear * 366) + (SumCommonYear * 365) + day;
	for(i=1; i<month; ++i)
	{
		Sumday = Sumday + MaxDay(year, i);
	}
	return Sumday;
}


int Week(int Sumday)     // 求该天是星期几 并返回
{
	Sumday = Sumday % 7;
	return Sumday;
}

char *ShowWeek(int week)    // 返回星期显示
{
	static char *p[7] = {"日", "一", "二", "三", "四", "五", "六"};
	return p[week];
}

char *ShowMonth(int month)    // 返回月份显示
{
	static char *p[12] = {"一", "二", "三", "四", "五", "六", "七", "八", "九", "十", "十一", "十二"};
	return p[month-1];
}


void ExactSearch2(void)     // 该日是当年的第%d天
{
	int year;
	int month;
	int day;
	int Sumday;
	int week;
	year = ScanfYear();
	month = ScanfMonth();
	day = ScanfDay(year, month);
	Sumday = SumDay(year, month, day)-SumDay(year,1,0);
	printf("\t该日是当年的第%d天",Sumday);
	return;
}

void IntermediateFunction(int day, int len)  // 输出结果
{
	int i;

	printf("\t");
	for(i=0; i<7; ++i)
	{
		printf("%s\t", ShowWeek(i));
	}
	printf("\n");
	i = 0;
	printf("\t");
	while(i < len)
	{
		++i;
		printf(" \t");
	}
	for(i=0; i<day; ++i)
	{
		printf("%d\t", i+1);
		if((i+len+1)%7 == 0)
		{
			printf("\n\t");
		}
	}
	return;
}


void YearExactSearch(void)  // 按年份查找
{
	int year;
	int month;
	int day;
	int sumday;
	int i;
	int len;
	year = ScanfYear();
	printf("\n\t查询结果：\n\t%d年", year);
	for(month=1; month<13; ++month)
	{
		day = MaxDay(year, month);
		sumday = SumDay(year, month, 1);
		len = Week(sumday);
		printf("\n\n\t\t\t\t*** %s月 ***\n\n", ShowMonth(month));
		IntermediateFunction(day, len);
		printf("\n\n");
	}
	return;
}
void Switch(void)        // 主菜单选择
{
	int val;
	val = _();
	switch(val)
	{
		case 0:
				printf("\t请按任意键结束程序...\n");
				getch();
				exit(EXIT_SUCCESS);
                case 1:
				judge();
				getch();
				return;
                case 2:
				ExactSearch2();
				getch();
				return;
	        case 3:
				YearExactSearch();
				getch();
				return;
		default :
				  printf("\t无该选项，请按任意键后重新输入...\n");
			 	  getch();
				  return;
	}
}

int main(int argc, char *argv[])
{
	while(1)
	{
		system("cls");
		system("color f");  // 运行到该处时，全屏文字变成亮白色
		show();
		Switch();
	}
	return EXIT_SUCCESS;
}
