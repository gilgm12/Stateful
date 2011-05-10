//-----------------------------------------------------------------------------

#include <unistd.h>
#include <stdio.h>
#include <cstdlib>
#include "example.h"
#include "time_state.h"
#include "point_state.h"

//-----------------------------------------------------------------------------

int main(int argc, char **argv){
	
	// Execute only every 1/100 of a second
	// so that we don't busy-loop.  This 'resolution' will
	// have an effect on the accuracy of the state updates,
	// and effectively lets the program trade accuracy 
	// for CPU time.	
	int ms_resolution = 10;
	fprintf(stderr, "\nLaunching with an update resolution of %d ms.\n",ms_resolution);
	
	time_state * timer = new time_state();
	point_state * point = new point_state();
	
	while(1){		
		timer->run();
		point->run();
		usleep(ms_resolution * 1000);
	}

	free(timer);
	free(point);	
	return 0;
}
