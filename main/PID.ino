void PID(){
  
  proportional=pos-setpoint;
  derivative=proportional-last_prop;
  integral=error1+error2+error3+error4+error5+error6;
  last_prop=proportional;
  
  error6=error5;
  error5=error4;
  error4=error3;
  error3=error2;
  error2=error1;
  error1=proportional;
  
  int differential=(proportional*(Kp/pow(10,multiP))) + (derivative*(Kd/pow(10,multiD))) + (integral*(Ki/pow(10,multiI)));
  
  if (differential > vel) differential=vel;
  else if (differential < -vel) differential=-vel;
  
  (differential < 0)?
  motor_start(vel, vel+differential):motor_start(vel-differential, vel);
  
}
