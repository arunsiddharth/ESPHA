/*
 
 *****FETCH DATA BETWEEN <b> </b> ******
  if(read_until_ESP(keyword_html_start_b,sizeof(keyword_html_start_b),15000,0)){

      //FOUND b> LOOK FOR </b but store data during that
      if(read_until_ESP(keyword_html_end_b,sizeof(keyword_html_end_b),5000,1)){
        
        for(int i=1; i<=(scratch_data_from_ESP[0]-sizeof(keyword_html_end_b)+1); i++)
          red[i]=scratch_data_from_ESP[i];//store it all in
        
          red[0]=(scratch_data_from_ESP[0]-sizeof(keyword_html_end_b)+1);//set the length of data received at [0]
      }
   }
   
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 */
