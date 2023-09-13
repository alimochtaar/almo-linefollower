void printText1(String message, int x, int y){
  u8g.firstPage();  
  do{
    u8g.setPrintPos(x, y); 
    u8g.print(message);
  }while( u8g.nextPage() );
}
