void get_TS1(){

  /****Building Up URL******/
  counter=0;//keeps track of the payload size
  payload_size=0;
  for(int i=0; i<(sizeof(URL_TS1)-1); i++){
    payload[payload_size+i] = URL_TS1[i];
    counter++;
  }//for
  
  payload_size = counter+payload_size;
  /*******Useful for sending Data to Website*******/

  //NOW CONNECT TO THAT URL AND GET DATA
  if(connect_ESP()){
  
  //CONNECTED AND DATA IS COMING
  //Parse the returned data,look like <b>205</b>
  
  //the keyword we need to find first is b>, which is stored in a constant keyword_html_start_b
   if(read_until_ESP(keyword_html_start_b,sizeof(keyword_html_start_b),15000,0)){

      //FOUND b> LOOK FOR </b but store data during that
      if(read_until_ESP(keyword_html_end_b,sizeof(keyword_html_end_b),5000,1)){
        
        for(int i=1; i<=(scratch_data_from_ESP[0]-sizeof(keyword_html_end_b)+1); i++)
          red[i]=scratch_data_from_ESP[i];//store it all in
        
          red[0]=(scratch_data_from_ESP[0]-sizeof(keyword_html_end_b)+1);//set the length of data received at [0]
      }
    }
           
    //we still have more data to get out of this stream
    if(read_until_ESP(keyword_html_start_b,sizeof(keyword_html_start_b),15000,0)){
          
       if(read_until_ESP(keyword_html_end_b,sizeof(keyword_html_end_b),5000,1)){
         
         for(int i=1; i<=(scratch_data_from_ESP[0]-sizeof(keyword_html_end_b)+1); i++)
           blue[i]=scratch_data_from_ESP[i];//store it in
            
           blue[0]=(scratch_data_from_ESP[0]-sizeof(keyword_html_end_b)+1);//length     
        }
     }
    
     //we still have more data to get out of this stream, now we want the views, which looks like <b>4,492,026</b>
    if(read_until_ESP(keyword_html_start_b,sizeof(keyword_html_start_b),15000,0)){//same as before - first b
                  
       if(read_until_ESP(keyword_html_end_b,sizeof(keyword_html_end_b),15000,1)){//now second b and mode=1
                  
         for(int i=1; i<=(scratch_data_from_ESP[0]-sizeof(keyword_html_end_b)+1); i++)
            green[i]=scratch_data_from_ESP[i];//store it in
                    
            green[0]=(scratch_data_from_ESP[0]-sizeof(keyword_html_end_b)+1);//length     
        }
     }

     
      //now that we have our data, go wait for the connection to disconnect - the ESP willreturn 'Unlink'
             
                   if(read_until_ESP(keyword_linkdisc,sizeof(keyword_linkdisc),15000,0)){
                       Serial.println("FOUND DATA & DISCONNECTED");
                        serial_dump_ESP();//now we can clear out the buffer and read whatever is still there
              
                        //let's see how the data looks
              
                          int i=0;
                          r=0;
                          for(i=1;i<=red[0];i++){
                            r=r*10+red[i]-48;
                          }
                          b=0;
                          for(i=1;i<=blue[0];i++){
                            b=b*10+blue[i]-48;
                          }
                          g=0;
                          for(i=1;i<=green[0];i++){
                            g=g*10+green[i]-48;
                          }
                          Serial.print("RED : ");
                          Serial.println(r);
                          Serial.print("GREEN : ");
                          Serial.println(g); 
                          Serial.print("BLUE : ");
                          Serial.println(b);
                           
                          //that's it!!
              
                          analogWrite(redPin,r);
                          analogWrite(greenPin,g);
                          analogWrite(bluePin,b);
                     }//link
            
 
    
}//connect ESP

}//get TS1
