
void get_TS2(){
  counter=0;
  payload_size=0;
  for(int i=0; i<(sizeof(URL_TS2)-1); i++){
  payload[payload_size+i] = URL_TS2[i];
  counter++;
  }//for int
  payload_size = counter+payload_size;
  
  if(connect_ESP()){
      //ON OR OFF
      //the keyword we need to find first is b>, which is stored in a constant keyword_html_start_b
      if(read_until_ESP(keyword_html_start_b,sizeof(keyword_html_start_b),15000,0)){

        //FOUND b> LOOK FOR </b but store data during that
        if(read_until_ESP(keyword_html_end_b,sizeof(keyword_html_end_b),5000,1)){
        
            for(int i=1; i<=(scratch_data_from_ESP[0]-sizeof(keyword_html_end_b)+1); i++)
              state[i]=scratch_data_from_ESP[i];//store it all in
              state[0]=(scratch_data_from_ESP[0]-sizeof(keyword_html_end_b)+1);//set the length of data received at [0]
        }
      }

      //TIME
      //the keyword we need to find first is b>, which is stored in a constant keyword_html_start_b
      if(read_until_ESP(keyword_html_start_b,sizeof(keyword_html_start_b),15000,0)){

        //FOUND b> LOOK FOR </b but store data during that
        if(read_until_ESP(keyword_html_end_b,sizeof(keyword_html_end_b),5000,1)){
        
            for(int i=1; i<=(scratch_data_from_ESP[0]-sizeof(keyword_html_end_b)+1); i++)
              onTime[i]=scratch_data_from_ESP[i];//store it all in
              onTime[0]=(scratch_data_from_ESP[0]-sizeof(keyword_html_end_b)+1);//set the length of data received at [0]
        }
      }
      
      if(read_until_ESP(keyword_linkdisc,sizeof(keyword_linkdisc),15000,0)){
           Serial.println("FOUND DATA & DISCONNECTED FROM BURGLAR ALARM ON");
           serial_dump_ESP();//now we can clear out the buffer and read whatever is still there
              
            //let's see how the data looks
            int i=0;
            bTime=0;
            bFlag=0;
            for(i=1;i<=state[0];i++){
               bFlag=bFlag*10+state[i]-48;
            }
            for(i=1;i<=state[0];i++){
               bTime=bTime*10+onTime[i]-48;
            }
                          
       }//link


      
  }//connect ESP
  
  
  
  
  
}//get current temp
