void brake(){
  if(pos<=700){ //-------------------------------------- baca dari hasil kalibrasi pattern
    motor_start(vel_maju, -1*vel_mundur);
  }
  if(pos>=800){
    motor_start(-1*(vel_mundur), vel_maju);
  }
}
