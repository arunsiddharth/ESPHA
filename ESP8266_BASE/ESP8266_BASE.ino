#include <SoftwareSerial.h>

#define ESP8266_rxPin 4
#define ESP8266_txPin 5
int cost=0;
//SSID + KEY
const char SSID_ESP[] = "sdik";
const char SSID_KEY[] = "1234567890a";

/**************VARIABLES FOR PROJECT*****************/
int redPin=11;
int greenPin=10;
int bluePin=6;
int brightness=75;
int r=0,b=0,g=0;//rgb

/*****************************************************/

/****************Variable For Burglar Alarm**********/
int trigPin=12;
int echoPin=8;
float distance;
float pingTime;
float speedOfSound=347.22;
int led=13;
int count=0;
int flag=0;
int bFlag=0;
long bTime=0;
long bTimeStart=0;
int roomWidth=80;
/*****************************************************/

// URLs
const char URL_TS1[] = "GET https://api.thingspeak.com/apps/thinghttp/send_request?api_key=IFTYYI9UTMVVSIG6 HTTP/1.0\r\n\r\n";
const char URL_TS2[] = "GET https://api.thingspeak.com/apps/thinghttp/send_request?api_key=G84JF7LLVHY5YULD HTTP/1.0\r\n\r\n";
const char URL_TS3[] = "GET https://api.thingspeak.com/apps/thinghttp/send_request?api_key=R5F0GRQ2JTSG160Z HTTP/1.0\r\n\r\n";

//MODES
const char CWMODE = '1';//CWMODE 1=STATION, 2=APMODE, 3=BOTH
const char CIPMUX = '1';//CWMODE 0=Single Connection, 1=Multiple Connections

SoftwareSerial ESP8266(ESP8266_rxPin, ESP8266_txPin);// rx tx

//DEFINE ALL FUNCTIONS HERE
boolean setup_ESP();
boolean read_until_ESP(const char keyword1[], int key_size, int timeout_val, byte mode);
void timeout_start();
boolean timeout_check(int timeout_ms);
void serial_dump_ESP();
boolean connect_ESP();
void get_TS1();
void get_TS2();
void get_hilo_temp();
void get_TS3();

//DEFINE ALL GLOBAL VAARIABLES HERE
unsigned long timeout_start_val;
char scratch_data_from_ESP[20];//first byte is the length of bytes
char payload[150];
byte payload_size=0, counter=0;
char ip_address[16];
char red[10];
char blue[10];
char green[10];
char state[3];
char onTime[12];
char current_temp[5];
char hi_temp[5];
char lo_temp[5];

//DEFINE KEYWORDS HERE
const char keyword_OK[] = "OK";
const char keyword_Ready[] = "Ready";
const char keyword_no_change[] = "no change";
const char keyword_blank[] = "#&";
const char keyword_ip[] = "192.";
const char keyword_rn[] = "\r\n";
const char keyword_quote[] = "\"";
const char keyword_carrot[] = ">";
const char keyword_sendok[] = "SEND OK";
const char keyword_linkdisc[] = "Unlink";



//keywords for youtube
const char keyword_html_start_b[] = "b>";
const char keyword_html_end_b[] = "</b";

//keywords for current temp
const char keyword_html_start_temp[] = "\"{";
const char keyword_html_end_temp[] = "}\"";

void setup(){
  
  //Pin Modes for ESP TX/RX
  pinMode(ESP8266_rxPin, INPUT);
  pinMode(ESP8266_txPin, OUTPUT);
  
  ESP8266.begin(9600);//default baudrate for ESP
  ESP8266.listen();//not needed unless using other software serial instances
  Serial.begin(9600); //for status and debug
  delay(2500);//delay before kicking things off
  
  //SET PINS FOR US
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(led,OUTPUT);
  digitalWrite(led,LOW);
  setup_ESP();//go setup the ESP 
}


void loop(){
  //RGB MVC
  //get_TS1(); // get LED DATA
  //delay(15000);
  //LATEST
  //delay(10000);

  //US MVC -----------------------------------------------------------
  get_TS2();//Know about bTime and bFlag
  if(bFlag==1){
  bTimeStart=millis();//get current Time;
  bTime=bTime*60*1000;//Convert Into Milliseconds
  Serial.println("BURGLAR ALARM ACTIVATED");
  
  while(millis()-bTimeStart < bTime){
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2000);
  
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  
  digitalWrite(trigPin,LOW);

  pingTime=pulseIn(echoPin,HIGH);
  distance=(speedOfSound*pingTime)/2;
  distance=distance/10000;
  //Serial.print("Distance in centimetre is ");
  //Serial.println(distance);
  if(distance!=0 && distance<roomWidth && cost <5)
  {
    if(flag!=1){
    digitalWrite(led,HIGH);
    Serial.println("Intruder Detected");
    count=count+1;
    Serial.print("Total passes are ");
    Serial.println(count);
    flag=1;
    //CALL FOR ESPHA
    get_TS3();
    cost=cost+1;
    }
  }
  else{
    flag=0;
  }
  delay(100);
  }
  }
  Serial.println("OUT OF LOOP");
  
  //US MVC -----------------------------------------------------------
  
  //get_TS2();//current temperature
  //delay(15000);
}

