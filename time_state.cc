//-----------------------------------------------------------------------------

#include <time.h>
#include "tools.h"
#include "time_state.h"

//-----------------------------------------------------------------------------


time_state::time_state(){
  this->run();  	
}


//-----------------------------------------------------------------------------


void time_state::reset(){
	gettimeofday(&this->last_exec_time, NULL);	
}


//-----------------------------------------------------------------------------


void time_state::run(){
	struct timeval current_time;
	gettimeofday(&current_time, NULL);

	long diff_usec = time_diff(this->last_exec_time,current_time);
	float diff_sec = diff_usec / 1000000.0;
	if (diff_sec >= 1.4){
		this->reset();
		this->show_time();
	}
}


//-----------------------------------------------------------------------------


void time_state::show_time(){
	struct tm *ts;	
	char buf[100];

	// Get centiseconds.
	int csec = this->last_exec_time.tv_usec / 10000L;
	time_t now = this->last_exec_time.tv_sec;
		
	ts = localtime(&now);
	strftime(buf,sizeof(buf),"%Y-%m-%d %H:%M:%S", ts);
	printf("\n  Clock: %s.%02d",buf,csec);
}


//-----------------------------------------------------------------------------

