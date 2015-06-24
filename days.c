#include <math.h>
#include <stdio.h>

int isleap(int year);
int dayofyear(int year,int month,int day);
int daydiff(int orgyear,int orgday,int usryear,int usrday);
char* daynameof(int year,int day);

static char daytab[2][13]=
{
	{0,31,28,31,30,31,30,31,31,30,31,30,31},
	{0,31,29,31,30,31,30,31,31,30,31,30,31}
};

static char* dayname[7]=
{
	"Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"
};

int isleap(int year)
{
	return ((year%4==0&&year%100!=0)||(year%400==0));
}

int dayofyear(int year,int month,int day)
{
	int i,leap;

	leap=isleap(year);

	if(day>daytab[leap][month]||day<=0)
	{
		fprintf(stderr, "error: illegal date\n");
		return -1;
	}
	if(month>12||month<=0)
	{
		fprintf(stderr, "error: illegal month\n");
		return -1;
	}

	for(i=1;i<month;i++)
		day+=daytab[leap][i];
	return day;
}

/*Negative dates are not handled yet*/

int daydiff(int orgyear,int orgday,int usryear,int usrday)
{
	if(orgyear<=0||usryear<=0||orgday<=0||usrday<=0)
	{
		fprintf(stderr, "error: negative date");
		return -1;
	}

	int leaps=floor((float)usryear/4)-floor((float)usryear/100)+floor((float)usryear/400);
	int years=usryear-orgyear-(isleap(usryear) ? leaps-1 : leaps);
	int days=(years* 365)+((isleap(usryear) ? leaps-1 : leaps)*366)+usrday-orgday;

	return days;
}

char* daynameof(int year,int day)
{
	int diff=daydiff(1,1,year,day);	 /*The first january of the year 0 was a monday*/
	if(day<=0||year<=0||diff<0)
	{
		fprintf(stderr, "error: negative date");
		return "illegal date";
	}
	return dayname[diff%7];
}

int main(void)
{
	int year,month,day;

	/*scanf works perfectly here*/

	puts("year:");
	scanf("%i",&year);
	puts("month:");
	scanf("%i",&month);
	puts("day:");
	scanf("%i",&day);

	printf("%i.%i.%i:%s.\n",day,month,year,daynameof(year,dayofyear(year,month,day)));

	return 0;
}
