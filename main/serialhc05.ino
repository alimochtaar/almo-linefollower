void readhc05(){
  if (Serial.available()) {
    while(Serial.available() == 0);
    valuesread();
    processing();
  }
}
