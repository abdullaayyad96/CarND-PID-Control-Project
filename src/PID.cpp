#include "PID.h"

using namespace std;


PID::PID() {
	PID::error_initialized = false;

	PID::p_error = 0;
	PID::d_error = 0;
	PID::i_error = 0;
	PID::prev_error = 0;

	PID::Kp = 0;
	PID::Ki = 0;
	PID::Kd = 0;
}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd, double filter_TC) {
	//initialize PID parameters
	PID::Kp = Kp;
	PID::Ki = Ki;
	PID::Kd = Kd;
	PID::filter_TC = filter_TC;
}

void PID::UpdateError(double error) {
	//update error value
	double filtered_error = PID::LP_error_filter(error); //filter error signal
	PID::p_error = filtered_error;

	if (PID::error_initialized) {
		//if PID previously initialized

		//assuming delta_t = 1 second
		PID::d_error = filtered_error - prev_error;
		PID::i_error += filtered_error; //calculate error integral
	}
	else {
		//if PID was not initialized

		PID::d_error = 0; 
		PID::i_error = filtered_error;
		PID::error_initialized = true;
	}

	//update previous error value
	PID::prev_error = filtered_error;
}

double PID::LP_error_filter(double error) {
	//low pass filter of the error signal
	return error - PID::filter_TC*(error - PID::prev_error);
}

double PID::TotalError() {
	//return PID controller output
	return -PID::Kp * PID::p_error - PID::Kd * PID::d_error - PID::Ki * PID::i_error;
}



