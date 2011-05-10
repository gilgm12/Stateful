//-----------------------------------------------------------------------------

#include <math.h>
#include <stdio.h>
#include "tools.h"

//-----------------------------------------------------------------------------


typedef struct point{
	float x;
	float y;
} point_t;


//-----------------------------------------------------------------------------


typedef enum{
	DEG_ONE,
	DEG_FOUR,
	DEG_THIRTEEN,
	DEG_SEVEN,
	DEG_TWENTY,
	NUM_STATES	
} state_t;


//-----------------------------------------------------------------------------


typedef enum{
	ENTERING_STATE,
	TIMER_EXPIRED,	
	NUM_EVENTS	
} event_t;


//-----------------------------------------------------------------------------


class point_fsm{	
	/*----------------------------------
	 *    Values
	 *--------------------------------*/	
	public:
		static double conversion_ratio;
		
	private:
		struct 		timeval last_exec_time;
		state_t		current_state;
		point_t     point;
	/*----------------------------------
	 *    Methods
	 *--------------------------------*/	
	public:
						point_fsm();	
		void 			run();
		void			reset();
		static double 	deg_to_radians(double degrees);
		void 			update_with_event(event_t event);
		
	private:
		void 		update_machine_internal(event_t event);		
		void 		get_point(int degrees, point_t * point);
		void    	point_str(point_t point, char * buf);
};

//-----------------------------------------------------------------------------

