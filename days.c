#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SSIZE 16

/*Sorry for the long function, but unfortunately C does not allow multiple return values.*/
void parseisodate(char* s, size_t len, int* year, int* month, int* day);
void printdate(int year, int month, int day);

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

void parseisodate(char* s, size_t len, int* year, int* month, int* day)
{
	/*not written yet*/
}

void printdate(int year, int month, int day)
{
	char* dname;

	dname=daynameof(year,dayofyear(year,month,day));

	if(strncmp(dname, "illegal date", strlen(dname))==0)
	{
		fprintf(stderr, "error: bad date format\n");
		exit (1);
	}

	printf("%i-%i-%i:%s\n", year, day, month, dname);
}

int isleap(int year)
{
	return ((year%4==0&&year%100!=0)||(year%400==0));
}

int dayofyear(int year,int month,int day)
{
	int i,leap;

	leap=isleap(year);

	if(day>daytab[leap][month]||day<=0)
		return -1;

	if(month>12||month<=0)
		return -1;

	for(i=1;i<month;i++)
		day+=daytab[leap][i];
	return day;
}

/*Negative dates are not handled yet*/

int daydiff(int orgyear,int orgday,int usryear,int usrday)
{
	if(orgyear<=0||usryear<=0||orgday<=0||usrday<=0)
		return -1;

	int leaps=floor((float)usryear/4)-floor((float)usryear/100)+floor((float)usryear/400);
	int years=usryear-orgyear-(isleap(usryear) ? leaps-1 : leaps);
	int days=(years* 365)+((isleap(usryear) ? leaps-1 : leaps)*366)+usrday-orgday;

	return days;
}

char* daynameof(int year,int day)
{
	int diff=daydiff(1,1,year,day);	 /*The first january of the year 1 was a monday*/

	if(day<=0||year<=0||diff<0)
		return "illegal date";

	return dayname[diff%7];
}

int main(void)
{
	int year,month,day;
	int count;
	char input[SSIZE];

	if(argc>1)
		for(count=1; count<argc; count++)
		{
			parseisodate(argv[count], strlen(argv[count]), &year, &month, &day);
			printdate(year, month, day);
		}

	while(fgets(input, SSIZE, stdin)!=NULL)
	{
		parseisodate(input, strlen(input), &year, &month, &day);
		printdate(year, month, day);
	}

	return 0;
}
