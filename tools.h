#include <sys/time.h>
#include <time.h>
#include <stdio.h>

long time_diff(struct timeval start, struct timeval end);
void str_time(struct timeval * tv, char * output);