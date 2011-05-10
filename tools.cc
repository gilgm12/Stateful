#include "tools.h"

long time_diff(struct timeval start, struct timeval end){
	
	// Convert both start and end time to microseconds.
	long start_usec = (start.tv_sec*1000000) + start.tv_usec;
	long end_usec = (end.tv_sec*1000000) + end.tv_usec;		
	
	// Calculate difference and return.
	long micro_diff = end_usec - start_usec;
	return micro_diff;	
}

void str_time(struct timeval * tv, char * output){
	struct tm *ts;	
	char buf[100];

	// Get milliseconds.
	int msec = tv->tv_usec / 1000L;
	time_t now = tv->tv_sec;
		
	ts = localtime(&now);
	strftime(buf,sizeof(buf),"%Y-%m-%d %H:%M:%S", ts);
	sprintf(output,"%s.%03d",buf,msec);
}