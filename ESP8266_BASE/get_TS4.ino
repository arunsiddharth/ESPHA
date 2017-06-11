void get_TS4(){

  /****Building Up URL******/
  counter=0;//keeps track of the payload size
  payload_size=0;
  for(int i=0; i<(sizeof(URL_TS4)-1); i++){
    payload[payload_size+i] = URL_TS4[i];
    counter++;
  }//for

  
  payload_size = counter+payload_size;
  counter=0;
  
  for(int i=0; i<(Sense_Values.length()); i++){
    payload[payload_size+i] = Sense_Values[i];
    counter++;
  }//for
  
  payload_size = counter+payload_size;
  counter=0;
  for(int i=0; i<(sizeof(append)-1); i++){
    payload[payload_size+i] = append[i];
    counter++;
  }//for
  payload_size = counter+payload_size;
  /*******PRINT URL********/
Serial.println("*-*-*-*-*-STATUS CHECKER-*-*-*-*-*");
  for(int i=0; i<payload_size+1; i++){
    
    Serial.print(payload[i]);
  }
  Serial.println();
  //NOW CONNECT TO THAT URL AND GET DATA
  if(connect_ESPHA()){

                   if(read_until_ESP(keyword_html_start_b,sizeof(keyword_html_start_b),15000,0)){

      //FOUND b> LOOK FOR </b but store data during that
      if(read_until_ESP(keyword_html_end_b,sizeof(keyword_html_end_b),5000,1)){
        
        for(int i=1; i<=(scratch_data_from_ESP[0]-sizeof(keyword_html_end_b)+1); i++)
          data[i]=scratch_data_from_ESP[i];//store it all in
        
          data[0]=(scratch_data_from_ESP[0]-sizeof(keyword_html_end_b)+1);//set the length of data received at [0]
      }
      Serial.print(data[1]);
      Serial.println("we have got");
   }
                   if(read_until_ESP(keyword_linkdisc,sizeof(keyword_linkdisc),15000,0)){
                       Serial.println("FOUND DATA & DISCONNECTED");
                        serial_dump_ESP();
                        
                   }//link
            
 
    
}//connect ESP

}//get TS4
