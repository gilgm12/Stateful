//-----------------------------------------------------------------------------

#include "point_state.h"

//-----------------------------------------------------------------------------


/* STATIC */
double point_state::conversion_ratio = (atan(1.0)*4) / 180; //(atan(1.0)*4 == PI)


//-----------------------------------------------------------------------------


/* STATIC */ 
double point_state::deg_to_radians(double degrees){
	return degrees * point_state::conversion_ratio;
}


//-----------------------------------------------------------------------------


point_state::point_state(){
  this->current_state = DEG_ONE;
  this->reset();
  this->run();
}


//-----------------------------------------------------------------------------


void point_state::reset(){
	gettimeofday(&this->last_exec_time, NULL);	
}


//-----------------------------------------------------------------------------


void point_state::run(){
	struct timeval current_time;
	gettimeofday(&current_time, NULL);

	long diff_usec = time_diff(this->last_exec_time,current_time);
	float diff_sec = diff_usec / 1000000.0;
	if (diff_sec >= 1.2){
		this->reset();
		this->handle_state();
		this->advance();
	}
}


//-----------------------------------------------------------------------------


void point_state::advance(){	
	if (this->current_state < (NUM_STATES-1)) this->current_state++;
	else this->current_state = DEG_ONE;
}


//-----------------------------------------------------------------------------


void point_state::get_point(int degrees, point_t * point){
	// Convert input degrees to radians.
	double radians = deg_to_radians(degrees);
	
	// Predefined radius of 1.
	double radius = 1.0;	
	
	// Calculate Coordinates.
	float x = radius * cos(radians);
	float y = radius * sin(radians);	
	point->x = x;
	point->y = y;
}


//-----------------------------------------------------------------------------


void point_state::handle_state(){
	char time_buf[100];
	char point_buf[100];
	str_time(&this->last_exec_time,time_buf);
	point_t point;
	int degrees;
	
	switch(this->current_state){
		case DEG_ONE:
			degrees = 1;		
			break;	
		case DEG_FOUR:
			degrees = 4;
			break;
		case DEG_THIRTEEN:
			degrees = 13;
			break;
		case DEG_SEVEN:
			degrees = 7;			
			break;
		case DEG_TWENTY:
			degrees = 20;
			break;
		default: 
			printf("\n  Unknown State.");
			return;
	}
		
	get_point(degrees,&point);
	
	// Send to standard error.
	fprintf(stderr, "  Point: %f,%f,<%s>\n",point.x,point.y,time_buf);	
}


//-----------------------------------------------------------------------------
