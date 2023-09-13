int baca(void)
{
  for(int i=0;i<16;i++){
     digitalWrite(s0, i&0x01);
     digitalWrite(s1, i&0x02);
     digitalWrite(s2, i&0x04);
     digitalWrite(s3, i&0x08);
     sensor[i]=analogRead(AI);
     if(line==0){
      if(sensor[i]<=limits[i]-approximate){
        digital[i]=false;
//        digital[0]=digital[2];digital[1]=digital[2];
//        digital[14]=digital[13];digital[15]=digital[13];
      }
      else{
        digital[i]=true;
//        digital[0]=digital[2];digital[1]=digital[2];
//        digital[14]=digital[13];digital[15]=digital[13];
      }
     }
     if(line==1){
      if(sensor[i]<=limits[i]-approximate){
        digital[i]=true;
//        digital[0]=digital[2];digital[1]=digital[2];
//        digital[14]=digital[13];digital[15]=digital[13];
      }
      else{
        digital[i]=false;
//        digital[0]=digital[2];digital[1]=digital[2];
//        digital[14]=digital[13];digital[15]=digital[13];
      }
     }
     
//     for (byte i=0; i<=15; i++) {
//       bitWrite(bin_Sensor, i, digital[15-i]);
//     }
//     Serial.print(digital[i]);
//     Serial.print("\t");
  }
//  Serial.println(" ");
  if(pattern==0){sumap=(1500*digital[0]+1400*digital[1]+1300*digital[2]+1200*digital[3]+
                      1100*digital[4]+1000*digital[5]+900*digital[6]+800*digital[7]+
                      700*digital[8]+600*digital[9]+500*digital[10]+400*digital[11]+
                      300*digital[12]+200*digital[13]+100*digital[14]+0*digital[15]);}
  if(pattern==1){sumap=(1500*digital[15]+1400*digital[14]+1300*digital[13]+1200*digital[12]+
                      1100*digital[11]+1000*digital[10]+900*digital[9]+800*digital[8]+
                      700*digital[7]+600*digital[6]+500*digital[5]+400*digital[4]+
                      300*digital[3]+200*digital[2]+100*digital[1]+0*digital[0]);}
  sum=(digital[0]+digital[1]+digital[2]+digital[3]+
       digital[4]+digital[5]+digital[6]+digital[7]+
       digital[8]+digital[9]+digital[10]+digital[11]+
       digital[12]+digital[13]+digital[14]+digital[15]);
  pos=(sumap/sum);
  if(poslast<=100 && pos==1)
  {
    pos=0;
  }
  if(poslast<=1400 && pos==-1)
  {
    pos=1500;
  }
  poslast=pos;
  
  return pos;
}
