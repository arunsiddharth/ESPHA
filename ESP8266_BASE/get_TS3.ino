
void get_TS3(){
  counter=0;
  payload_size=0;
  for(int i=0; i<(sizeof(URL_TS3)-1); i++){
  payload[payload_size+i] = URL_TS3[i];
  counter++;

  //-------URL APPEND------
  
  //-----------------------
  }//for int
     payload_size = counter+payload_size;
     if(connect_ESP()){

      if(read_until_ESP(keyword_html_start_temp,sizeof(keyword_html_start_temp),20000,0)){
      if(read_until_ESP(keyword_html_end_temp,sizeof(keyword_html_end_temp),20000,1)){
      for(int i=1; i<=(scratch_data_from_ESP[0]-sizeof(keyword_html_end_temp)+1); i++)// i=0 is total lenght including key, so sub the key length-1, not < since we're not starting at 0
      current_temp[i]=scratch_data_from_ESP[i];
      current_temp[0]=(scratch_data_from_ESP[0]-sizeof(keyword_html_end_temp)+1);   
      
      if(read_until_ESP(keyword_linkdisc,sizeof(keyword_linkdisc),15000,0)){
      Serial.println("INFORMATION UPLOADED SUCCESSFULLY");
      serial_dump_ESP();
          
        }//link
       
     }//end  temp
     }//start temp
  }//connect ESP
  
  
  
  
  
}//DONE
