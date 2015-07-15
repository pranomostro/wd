#include <math.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <inttypes.h>

void ainput(char* s);
void printdate(uint64_t year, uint64_t month, uint64_t day);

int64_t dayofyear(uint64_t year,uint64_t month,uint64_t day);
uint64_t isleap(uint64_t year);
uint64_t daydiff(uint64_t orgyear,uint64_t orgday,uint64_t usryear,uint64_t usrday);

char* daynameof(uint64_t year,uint64_t day);

static uint64_t daytab[2][13]=
{
	{0,31,28,31,30,31,30,31,31,30,31,30,31},
	{0,31,29,31,30,31,30,31,31,30,31,30,31}
};

static char* dayname[7]=
{
	"Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"
};

void ainput(char* s)
{
	uint64_t year, month, day;
	errno=0;
	sscanf(s, "%lu-%lu-%lu", &year, &month, &day);

	if(errno)
	{
		fprintf(stderr, "error: no date of format YEAR-MONTH-DAY found");
		return;
	}

	printdate(year, month, day);
}

void printdate(uint64_t year, uint64_t month, uint64_t day)
{
	char* dname;

	dname=daynameof(year,dayofyear(year,month,day));

	if(strncmp(dname, "illegal date", strlen(dname))==0)
	{
		fprintf(stderr, "error: bad date format\n");
		return;
	}

	printf("%lu-%lu-%lu:%s\n", year, month, day, dname);
}

uint64_t isleap(uint64_t year)
{
	return ((year%4==0&&year%100!=0)||(year%400==0));
}

int64_t dayofyear(uint64_t year,uint64_t month,uint64_t day)
{
	uint64_t i,leap;

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

uint64_t daydiff(uint64_t orgyear,uint64_t orgday,uint64_t usryear,uint64_t usrday)
{
	if(!orgyear||!usryear||!orgday||!usrday)
		return -1;

	uint64_t leaps=floor((float)usryear/4)-floor((float)usryear/100)+floor((float)usryear/400);
	uint64_t years=usryear-orgyear-(isleap(usryear) ? leaps-1 : leaps);
	uint64_t days=(years* 365)+((isleap(usryear) ? leaps-1 : leaps)*366)+usrday-orgday;

	return days;
}

char* daynameof(uint64_t year,uint64_t day)
{
	uint64_t diff=daydiff(1,1,year,day);	 /*The first january of the year 1 was a monday*/

	if(day<=0||year<=0)
		return "illegal date";

	return dayname[diff%7];
}

int main(int argc, char** argv)
{
	int64_t count;
	char input[16];

	if(argc>1)
	{
		for(count=1; count<argc; count++)
			ainput(argv[count]);
		return 0;
	}

	while(fgets(input, 16, stdin)!=NULL)
		ainput(input);

	return 0;
}
