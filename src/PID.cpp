#include "PID.h"

using namespace std;


PID::PID() {
	PID::error_initialized = false;
}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
	//initialize PID parameters
	PID::Kp = Kp;
	PID::Ki = Ki;
	PID::Kd = Kd;
}

void PID::UpdateError(double error) {
	//pdate error value
	PID::p_error = error;

	if (PID::error_initialized) {
		//if PID previously initialized

		//assuming delta_t = 1 second
		PID::d_error = error - PID::prev_error; //calculate error derivative
		PID::i_error += error; //calculate error integral
	}
	else {
		//if PID was not initialized

		PID::d_error = 0; 
		PID::i_error = error;
		PID::error_initialized = true;
	}

	//update previous error value
	PID::prev_error = error;
}

double PID::TotalError() {
	//return PID controller output
	return -PID::Kp * PID::p_error - PID::Kd * PID::d_error - PID::Ki * PID::i_error;
}

