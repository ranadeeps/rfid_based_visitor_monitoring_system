#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10 //RX slave select
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.

byte card_ID[4]; //card UID size 4byte
byte Name1[4]={0xF9,0x04,0x2C,0xBF};//first UID card
byte Name2[4]={0x99,0x44,0xE7,0xD5};//second UID card
byte Name3[4]={0xD9,0x14,0x22,0xBD};//first UID card
byte Name4[4]={0x19,0x7A,0xE4,0xD5};
//if you want the arduino to detect the cards only once
//int NumbCard[5];//this array content the number of cards. in my case i have just two cards.
int j=0;        

int const RedLed=6;
int const GreenLed=5;
int const Buzzer=8;
int p[5]={0,0,0,0,0};
String Name;//user name
long Left_Time;
long Number;//user number
int n ;//The number of card you want to detect (optional)  
int flg=0;
void setup() {
  Serial.begin(9600); // Initialize serial communications with the PC
  SPI.begin();  // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522 card
  
  Serial.println("CLEARSHEET");                 // clears starting at row 1
  Serial.println("LABEL,Date,Entry Time,Name,Number,Time Spent(in sec),Warning");// make four columns (Date,Time,[Name:"user name"]line 48 & 52,[Number:"user number"]line 49 & 53)

  //pinMode(RedLed,OUTPUT);
  //pinMode(GreenLed,OUTPUT);
  //pinMode(Buzzer,OUTPUT);
    pinMode(8,OUTPUT);
    digitalWrite(8,LOW);
   }
int num[40]={0};
int c=0;
int w=0;
void loop() {
  flg=0;
delay(1000);
       //look for new card
 if ( ! mfrc522.PICC_IsNewCardPresent()) {
      return;//got to start of loop if there is no card present
 }
 // Select one of the cards
 if ( ! mfrc522.PICC_ReadCardSerial()) {
  return;//if read card serial(0) returns 1, the uid struct contians the ID of the read card.
 }
  card_ID[0]=mfrc522.uid.uidByte[0];
   if(card_ID[0]==Name1[0]){
   Name="Trolly_1";//user name
   Number=1;//user number
   j=1;//first number in the NumbCard array : NumbCard[j]
   num[c]=j;
   c=c+1;
   p[j]=p[j]+10;
  }
  else{

  }
  if(card_ID[0]==Name2[0]){
   Name="Trolly_2";//user name
   Number=2;//user number
   j=2;//Second number in the NumbCard array : NumbCard[j]
   num[c]=j;
   c=c+1;
   p[j]=p[j]+10;
  }
  else{
 
  }
  if(card_ID[0]==Name3[0]){
   Name="Trolly_3";//user name
   Number=3;//user number
   j=3;//Second number in the NumbCard array : NumbCard[j]
   num[c]=j;
   c=c+1;
   p[j]=p[j]+10;
  }
  else{

  }
  if(card_ID[0]==Name4[0]){
   Name="Trolly_4";//user name
   Number=4;//user number
   j=4;//Second number in the NumbCard array : NumbCard[j]
   num[c]=j;
   c=c+1;
   p[j]=p[j]+10;
  }
  else{

  }
  //else{
      //digitalWrite(GreenLed,LOW);
      //digitalWrite(RedLed,HIGH);
  //    goto cont;//go directly to line 85
  //}
  //if(NumbCard[j] == 1){//to check if the card already detect
  //if you want to use LCD
  //Serial.println("Already Exist");
  //}
  //else{
  //NumbCard[j] = 1;//put 1 in the NumbCard array : NumbCard[j]={1,1} to let the arduino know if the card was detecting 
  //n++;//(optional)
  //(num[c-1]!=num[c-2])||
  //if (p[Number]==0){
  Serial.print("DATA,DATE,TIME," + Name);//send the Name to excel
  Serial.print(",");
  Serial.print(Number);//send the Number to excel
  Serial.print(",");
  Serial.print(p[j]);
  Serial.print(",");
  if (c > 4)
  {
    for(int k=1;k<4;k++)
    {
      if((num[c-1]==num[c-k-1]))
      {
        w++; 
      }
    }
    if(w==3)
    {
      digitalWrite(8,HIGH);
      delay(1000);
      digitalWrite(8,LOW);
      delay(1000);
      Serial.println("Problem");
      flg=1;
    }
    w=0;
    
  }
    if (c > 8)
  {
    for(int k=1;k<4;k++)
    {
      if((num[c-1]==num[c-(2*k)-1]))
      {
        w++; 
      }
    }
    if(w==3)
    {
      digitalWrite(8,HIGH);
      delay(1000);
      digitalWrite(8,LOW);
      delay(1000);
      Serial.println("Problem");
      flg=1;
    }
    w=0;
  }
  if(flg!=1)
  {
    Serial.println("");
  }
 // }
  //digitalWrite(GreenLed,HIGH);
  //digitalWrite(RedLed,LOW);
  //digitalWrite(Buzzer,HIGH);
  //digitalWrite(Buzzer,LOW);
  //Serial.println("SAVEWORKBOOKAS,Names/WorkNames");
  //

//cont:
//digitalWrite(GreenLed,LOW);
//digitalWrite(RedLed,LOW);

//if you want to close the Excel when all card had detected and save Excel file in Names Folder. in my case i have just 2 card (optional)
//if(n==2){
    
  //  Serial.println("FORCEEXCELQUIT");
 //   }

}
