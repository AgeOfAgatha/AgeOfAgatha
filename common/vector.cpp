/*--------------------------------------------//
Vector definition
This is used to simplify definition of points
//--------------------------------------------*/
#ifndef VECTOR
#define VECTOR
class vector{
	public:
		double x;
		double y;
		double z; 
		/*--------------------------------------------//
		Default constructor
		//--------------------------------------------*/
		vector(){
			x = 0;
			y = 0;
			z = 0;
		};

		/*--------------------------------------------//
		Constuctor with positions specified
		//--------------------------------------------*/
		vector(double xi, double yi, double zi):vector(){
			x = xi;
			y = yi;
			z = zi;
		};

		/*--------------------------------------------//
		Destructor
		//--------------------------------------------*/
		~vector(){};

		/*--------------------------------------------//
		Overridden operators
		//--------------------------------------------*/
		bool operator==(const vector &other) const {
			return (this->x == other.x && this->y == other.y && this->z == other.z);
		};
		bool operator!=(const vector &other) const {
			return *this!=other;
		};
};
#endif