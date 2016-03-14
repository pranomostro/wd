#include <math.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

typedef unsigned long ulong;

short isleap(ulong year);
long dayofyear(ulong year, ulong month, ulong day);
long daydiff(ulong orgyear, ulong orgday, ulong usryear, ulong usrday);

static unsigned daytab[2][13]=
{
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

static char* dayname[7]=
{
	"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"
};

short isleap(ulong year)
{
	return ((year%4==0&&year%100!=0)||(year%400==0));
}

long daydiff(ulong orgyear, ulong orgday, ulong usryear, ulong usrday)
{
	ulong leaps, years, days;

	leaps=((usryear-1)/4)-((usryear-1)/100)+((usryear-1)/400);
	years=usryear-orgyear-leaps;
	days=(years* 365)+(leaps*366)+usrday-orgday;

	return days;
}

long dayofyear(ulong year, ulong month, ulong day)
{
	ulong i;

	for(i=1;i<month;i++)
		day+=daytab[isleap(year)][i];
	return day;
}

int main(int argc, char** argv)
{
	int i;
	char c;
	ulong year, day, month;

	if(argc>1)
		for(i=1; i<argc; i++)
		{
			errno=0;
			sscanf(argv[i], "%lu-%lu-%lu", &year, &month, &day);
			if(errno||!year||!month||month>12||!day||day>daytab[isleap(year)][month])
			{
				fprintf(stderr, "error: no date of format YEAR-MONTH-DAY found\n");
				continue;
			}
			printf("%lu-%lu-%lu:%s\n", year, month, day,
				dayname[daydiff(1, 1, year, dayofyear(year, month, day))%7]);
		}
	else
		while(scanf("%lu-%lu-%lu", &year, &month, &day)!=EOF)
		{
			if(errno||!year||!month||month>12||!day||day>daytab[isleap(year)][month])
			{
				fprintf(stderr, "error: no date of format YEAR-MONTH-DAY found\n");
				while((c=fgetc(stdin))!=EOF&&c!='\n');
				continue;
			}
			printf("%lu-%lu-%lu:%s\n", year, month, day,
				dayname[daydiff(1, 1, year, dayofyear(year, month, day))%7]);
			errno=0;
		}

	return 0;
}
