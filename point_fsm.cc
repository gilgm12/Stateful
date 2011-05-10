//-----------------------------------------------------------------------------

#include "point_fsm.h"

//-----------------------------------------------------------------------------


/* STATIC */
double point_fsm::conversion_ratio = (atan(1.0)*4) / 180; //(atan(1.0)*4 == PI)


//-----------------------------------------------------------------------------


/* STATIC */ 
double point_fsm::deg_to_radians(double degrees){
	return degrees * point_fsm::conversion_ratio;
}


//-----------------------------------------------------------------------------


point_fsm::point_fsm(){
  this->current_state = DEG_ONE;
  this->reset();
  this->run();
}


//-----------------------------------------------------------------------------


void point_fsm::reset(){
	gettimeofday(&this->last_exec_time, NULL);	
}


//-----------------------------------------------------------------------------


void point_fsm::run(){
	struct timeval current_time;
	gettimeofday(&current_time, NULL);

	long diff_usec = time_diff(this->last_exec_time,current_time);
	float diff_sec = diff_usec / 1000000.0;
	if (diff_sec >= 1.2){
		this->reset();
		this->update_with_event( TIMER_EXPIRED );
	}
}


//-----------------------------------------------------------------------------


void point_fsm::get_point(int degrees, point_t * point){
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


void point_fsm::update_with_event(event_t event){
	state_t prev_state = this->current_state;
	this->update_machine_internal( event );
	
	while (prev_state != this->current_state){
		// if we switched to a different state, or the new state 
		// the new state changed our state again, we process the 
		// 'ENTERING_STATE' event for that state.  If we get two states 
		// that switch back and forth in the ENTERING_STATE handler
		// this could ping-pong forever.  This little example
		// doesn't require or use this event, but it is a good
		// example of a traditional finite state machine.
		prev_state = this->current_state;
		update_with_event( ENTERING_STATE );
	}
}


//-----------------------------------------------------------------------------


void point_fsm::update_machine_internal(event_t event){	
	
	// Write the time whenever we update the state machine.
	char time_buf[100];
	str_time(&this->last_exec_time,time_buf);
	
	
	switch( this->current_state ){
	
	case DEG_ONE:
		switch(event){
		case ENTERING_STATE: break;
		case TIMER_EXPIRED:
			get_point(1,&this->point);
			fprintf(stderr, "  Point: %f,%f,<%s>\n",point.x,point.y,time_buf);
			this->current_state = DEG_FOUR;
			break;
		}
		break;
		
	case DEG_FOUR:
		switch(event){
		case ENTERING_STATE: break;
		case TIMER_EXPIRED:
			get_point(4,&this->point);
			fprintf(stderr, "  Point: %f,%f,<%s>\n",point.x,point.y,time_buf);			
			this->current_state = DEG_THIRTEEN;
			break;
		}
		break;
		
	case DEG_THIRTEEN:
		switch(event){
		case ENTERING_STATE: break;
		case TIMER_EXPIRED:
			get_point(13,&this->point);
			fprintf(stderr, "  Point: %f,%f,<%s>\n",point.x,point.y,time_buf);			
			this->current_state = DEG_SEVEN;
			break;
		}
		break;
		
	case DEG_SEVEN:
		switch(event){
		case ENTERING_STATE: break;
		case TIMER_EXPIRED:
			get_point(7,&this->point);
			fprintf(stderr, "  Point: %f,%f,<%s>\n",point.x,point.y,time_buf);			
			this->current_state = DEG_TWENTY;
			break;
		}
		break;
		
	case DEG_TWENTY:
		switch(event){
		case ENTERING_STATE: break;
		case TIMER_EXPIRED:
			get_point(20,&this->point);
			fprintf(stderr, "  Point: %f,%f,<%s>\n",point.x,point.y,time_buf);			
			this->current_state = DEG_ONE;
			break;
		}
		break;				
	}
}


//-----------------------------------------------------------------------------
