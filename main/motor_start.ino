void motor_start(int left, int right){
// LEFT MOTOR
  if(left>=0){
    digitalWrite(left1,LOW);
    digitalWrite(left2,HIGH);
  }
  else{left=left*(-1);
    digitalWrite(left1,HIGH);
    digitalWrite(left2,LOW);
  }
  analogWrite(pwm_left,left);
  
// RIGHT MOTOR
  if(right>=0){
    digitalWrite(right1,HIGH);
    digitalWrite(right2,LOW);
  }
  else{right=right*(-1);
    digitalWrite(right1,LOW);
    digitalWrite(right2,HIGH);
  }
  analogWrite(pwm_right,right);
  
}

void FAN(int pwm_speed){
  analogWrite(fan_pinout, pwm_speed);
}
