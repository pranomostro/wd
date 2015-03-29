#include <stdio.h>
#include <string.h>

static char* dayname[7]=
{
    "Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday"
};

int getline(char line[],int lim);

int main(void)
{
    int i=0,count=1;
    char day[16];

    while(getline(day,15)>0)
    {
        if(i>=7)
            i=0;
        if(strncmp(day,dayname[i],16))
        {
            printf("error: daynames don't match,line %i\n",count);
            return 1;
        }
        count++;
        i++;
    }
    return 0;
}

int getline(char line[],int lim)
{
    int c,i;
    i=c=0;
    while(--lim>0&&(c=getchar())!=EOF&&c!='\n')
        line[i++]=c;\
    line[i]='\0';
    return i;
}
