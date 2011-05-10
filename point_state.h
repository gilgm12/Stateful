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


class point_state{	
	/*----------------------------------
	 *    Values
	 *--------------------------------*/	
	public:
		static double conversion_ratio;
		
	private:
		struct 		timeval last_exec_time;
		int 		current_state;
		
	/*----------------------------------
	 *    Methods
	 *--------------------------------*/	
	public:
						point_state();	
		void 			run();
		void			reset();
		static double 	deg_to_radians(double degrees);
		
	private:
		void 		get_point(int degrees, point_t * point);
		void    	point_str(point_t point, char * buf);
		void 		advance();
		void		handle_state();
};

//-----------------------------------------------------------------------------

