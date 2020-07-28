#include "Camera.h"

// Constructors
Camera::Camera() {};
Camera::Camera(nilkun::Position *position) { target = position; }

void Camera::setTarget(nilkun::Position* position) { target = position; }

void Camera::setLimits(float screenW, float screenH, nilkun::Point *dimensions) {
	// target = position;
	center.x = screenW  / 2;

	center.y = screenH / 2;	
	max_pos.x = 460;
	max_pos.y = 288;
	// max_pos.x = dimensions -> x - center.x - 1;
	
	// max_pos.y = dimensions -> y - center.y - 1;
	// -1 ??

};

void Camera::update() {
	position.x = target -> x - vV/2 < 0
		? 0 
		: target -> x + vV/2 > max_pos.x 
			? max_pos.x - vV 
			: target -> x - vV/2;
   //	- target -> w;
	position.y = target -> y - vH/2 < 0 
		? 0 
		: target -> y + vH/2 > max_pos.y 
			? max_pos.y - vH 
			: target -> y - vH/2;
};
