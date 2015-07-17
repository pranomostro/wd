#include <math.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

typedef unsigned long ulong;

void aninput(char* s);

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

void aninput(char* s)
{
	ulong year, month, day;
	long diff;
	errno=0;

	sscanf(s, "%lu-%lu-%lu", &year, &month, &day);

	if(errno||!year||!month||!day)
	{
		fprintf(stderr, "error: no date of format YEAR-MONTH-DAY found\n");
		return;
	}

	diff=daydiff(1, 1, year, dayofyear(year, month, day));

	if(diff<0)
	{
		fprintf(stderr, "error: bad date format\n");
		return;
	}

	printf("%lu-%lu-%lu:%s\n", year, month, day, dayname[diff%7]);
}

short isleap(ulong year)
{
	return ((year%4==0&&year%100!=0)||(year%400==0));
}

long dayofyear(ulong year, ulong month, ulong day)
{
	ulong i, leap;

	leap=isleap(year);

	if(day>daytab[leap][month]||month>12)
		return -1;

	for(i=1;i<month;i++)
		day+=daytab[leap][i];
	return day;
}

/*Negative dates are not handled yet*/

long daydiff(ulong orgyear, ulong orgday, ulong usryear, ulong usrday)
{
	if(!orgyear||!usryear||!orgday||!usrday)
		return -1;

	ulong leaps=(usryear/4)-(usryear/100)+(usryear/400)+isleap(usryear);
	ulong years=usryear-orgyear-leaps;
	ulong days=(years* 365)+(leaps*366)+usrday-orgday;

	return days;
}



int main(int argc, char** argv)
{
	long count;
	char input[16];

	if(argc>1)
	{
		for(count=1; count<argc; count++)
			aninput(argv[count]);
		return 0;
	}

	while(fgets(input, 16, stdin)!=NULL)
		aninput(input);

	return 0;
}
