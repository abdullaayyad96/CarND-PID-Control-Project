#ifndef PID_H
#define PID_H

class PID {
public:
  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;

  double prev_error;

  bool error_initialized;

  double filter_TC; //time constant for the low pass filter of the error signal

  /*
  * Coefficients
  */ 
  double Kp;
  double Ki;
  double Kd;

  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp, double Ki, double Kd, double filter_TC);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double error);

  /*
  * Calculate the total PID error.
  */
  double TotalError();

private:
  /* 
  * low pass filter fpr the error signal
  */
	double LP_error_filter(double error);
};

#endif /* PID_H */
