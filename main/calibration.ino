void backgrounds()
{ 
  for(int i=0;i<16;i++){
     digitalWrite(s0, i&0x01);
     digitalWrite(s1, i&0x02);
     digitalWrite(s2, i&0x04);
     digitalWrite(s3, i&0x08);
     readBG[i]=analogRead(AI);
//     Serial.print(readBG[i]);
//     Serial.print("\t");
  }
//  Serial.println(" ");
}

void lines()
{
  for(int i=0;i<16;i++){
     digitalWrite(s0, i&0x01);
     digitalWrite(s1, i&0x02);
     digitalWrite(s2, i&0x04);
     digitalWrite(s3, i&0x08);
     readLine[i]=analogRead(AI);
//     Serial.print(readLine[i]);
//     Serial.print("\t");
  }
//  Serial.println(" ");
}

void average()
{
  for(int i=0;i<16;i++){
     limits[i]=(readBG[i]+readLine[i])/2;
//     Serial.print(limits[i]);
//     Serial.print("\t");
  }
//  Serial.println(" ");
}

void calibrate_bg(){
  delay(100);
    u8g.firstPage();  
      do {
        u8g.setPrintPos(0, 10); 
        u8g.print("CALIBRATE BG");
        u8g.setPrintPos(0, 25); 
        u8g.print(". . . . . .");
      } while( u8g.nextPage() );
  
  for(int i=0;i<50;i++)
  {
    backgrounds();
    digitalWrite(LED_BUILTIN, 0);
    delay(20);
    digitalWrite(LED_BUILTIN, 1);
    delay(20);
  }
}

void calibrate_line(){
  delay(100);
      u8g.firstPage();
      do {
        u8g.setPrintPos(0, 10); 
        u8g.print("CALIBRATE LINE");
      } while( u8g.nextPage() ); 
  for(int i=0;i<50;i++)
  {
    lines();
    digitalWrite(LED_BUILTIN, 0);
    delay(20);
    digitalWrite(LED_BUILTIN, 1);
    delay(20);
  }
}
