#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>

#define SSIZE 16

void printdate(int year, int month, int day);
int datefields(char* s, size_t len, int* year, int* month, int* day);
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

int datefields(char* s, size_t len, int* year, int* month, int* day)
{
	char* t;
	char* u;
	for(t=s;*t!='-'&&(unsigned)(t-s)<len;t++);
	u=t+3;

	if(*t!='-'||*u!='-')
		return 0;

	*t++=*u++='\0'; u[2]='\0';

	errno=0;

	*year=strtol(s, NULL, 10);
	*month=strtol(t, NULL, 10);
	*day=strtol(u, NULL, 10);

	if(errno||*year<=0||*month<=0||*day<=0)
	{
		fprintf(stderr, "error: no useful date found, continuing.\n");
		return 0;
	}
	return 1;
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

	printf("%i-%i-%i:%s\n", year, month, day, dname);
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

int main(int argc, char** argv)
{
	int year, month, day;
	int count;
	char input[SSIZE];

	if(argc>1)
	{
		for(count=1; count<argc; count++)
			if(datefields(argv[count], strlen(argv[count]), &year, &month, &day))
				printdate(year, month, day);
		return 0;
	}

	while(fgets(input, SSIZE, stdin)!=NULL)
		if(datefields(input, strlen(input), &year, &month, &day))
			printdate(year, month, day);

	return 0;
}
