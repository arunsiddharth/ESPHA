
//Found DATA,So dump next coming un-useful data
void serial_dump_ESP(){
  
  char temp;
  while(ESP8266.available()){
    temp =ESP8266.read();
    delay(1);//could play around with this value if buffer overflows are occuring
  }//while
  
  
}//serial dump
