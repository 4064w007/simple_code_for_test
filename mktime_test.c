/*************************************************************************
    > File Name: test_mktime.c
    > Author: dingzhengsheng
    > Mail: dingzs3@asiainfo.com 
    > Created Time: 2015年04月08日 星期三 11时21分09秒
 ************************************************************************/

#include<stdio.h>
#include<time.h>
#include<string.h>
#include<sys/time.h>
#include<sys/resource.h>
#define SECTOUSEC 1000000



int get_diff_time(struct timeval *start, struct timeval *end)
{
                long int ts = 0;
                if(!start || !end)
                        return -1;       
                ts = end->tv_sec*SECTOUSEC +end->tv_usec - start->tv_sec*SECTOUSEC - start->tv_usec;
                return (int)ts;
}

void main(int argc, char *argv[])
{
        time_t timep;
        struct tm *p;
        int n;
        struct rusage dusage, zusage;
        int i=0;

        if(argv[1] == NULL)
                return;
        n = atoi(argv[1]);


        time(&timep);
        printf("time():%d\n", timep);

        p = localtime(&timep);
        getrusage(RUSAGE_SELF, &dusage);
        for(i=0;i<n;i++)
        {
                p->tm_isdst = 1;
                timep = mktime(p);
                printf("*** %d ***\n", p->tm_isdst);
        }
        getrusage(RUSAGE_SELF, &zusage);
        printf("tm_isdst=1:user_cpu_time=%d sys_cpu_time=%d \n", get_diff_time(&dusage.ru_utime, &zusage.ru_utime),
                        get_diff_time(&dusage.ru_stime,&zusage.ru_stime));

        getrusage(RUSAGE_SELF, &dusage);
        for(i=0;i<n;i++)
        {
                p->tm_isdst = 0;
                timep = mktime(p);
        }
        getrusage(RUSAGE_SELF, &zusage);
        printf("tm_isdst=0:user_cpu_time=%d sys_cpu_time=%d \n", get_diff_time(&dusage.ru_utime, &zusage.ru_utime),
                        get_diff_time(&dusage.ru_stime,&zusage.ru_stime));


        getrusage(RUSAGE_SELF, &dusage);
        for(i=0;i<n;i++)
        {
                p->tm_isdst = -1;
                timep = mktime(p);
        }
        getrusage(RUSAGE_SELF, &zusage);
        printf("tm_isdst=-1:user_cpu_time=%d sys_cpu_time=%d \n", get_diff_time(&dusage.ru_utime, &zusage.ru_utime),
                        get_diff_time(&dusage.ru_stime,&zusage.ru_stime));
}
