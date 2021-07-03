#include <String.h>
#include <WiFi.h>
#include <WiFiMulti.h>
uint8_t connectstatus ;
int keyIndex = 0;            // your network key Index number (needed only for WEP)
          // your network key Index number (needed only for WEP)

  IPAddress ip ;
  long rssi ;
String ipdata ;
int status = WL_IDLE_STATUS;
WiFiMulti wifiMulti;
String MacData ;
WiFiClient client;

#include <PubSubClient.h>

WiFiClient mqclient;
PubSubClient mqttclient(mqclient) ;

HardwareSerial myHardwareSerial(2); //ESP32可宣告需要一個硬體序列，軟體序列會出錯
#define Ledon HIGH
#define Ledoff LOW

#define RXD2 16
#define TXD2 17
String Apname;
#define AccessPin 15
#define WifiPin 2
#define BeepPin 4



char* AP3 = "lab309" ;
char* PW3 = "";
char* AP2 = "NCNUIOT" ;
char* PW2 = "12345678";
char* AP1 = "BrucetsaoXR" ;
char* PW1 = "12345678";


#define maxfeekbacktime 5000
long temp , humid ;
byte cmd ;
byte receiveddata[250] ;
int receivedlen = 0 ;
byte StrTemp[] = {0x01,0x04,0x00,0x01,0x00,0x02,0x20,0x0B}  ;
byte Str1[] = {0x01,0x04,0x00,0x01,0x00,0x01,0x60,0x0A}  ;
byte Str2[] = {0x01,0x04,0x00,0x02,0x00,0x01,0x90,0x0A}  ;
int phasestage=1 ;
boolean flag1 = false ;
boolean flag2 = false ;

//------------------
#include <Wire.h>     //I2C 基本函式 (必要)
#include <LiquidCrystal_I2C.h>    //LCD 1602/2004 的函式 

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
// 產生lcd 螢幕物件(I2C使用位址，幾行(縱向)，幾列(橫向))

String ChartoString(const char* cc)
{
    int count= 0 ;
    String tmp ;
    while (cc[count] != 0x00)
      {
        tmp.concat(cc[count]) ;
        count++ ;
      }
   return tmp ;
}

//---------------

String  print2HEX(int number) {
  String ttt ;
  if (number >= 0 && number < 16)
  {
    ttt = String("0") + String(number,HEX);
  }
  else
  {
      ttt = String(number,HEX);
  }
  ttt.toUpperCase() ;
  return ttt ;
}


//-------------------
 void Beepon()
 {
  digitalWrite(BeepPin,Ledon) ;
 }
 void Beepoff()
 {
  digitalWrite(BeepPin,Ledoff) ;
 }
 void Accesson()
 {
  digitalWrite(AccessPin,Ledon) ;
 }
 void Accessoff()
 {
  digitalWrite(AccessPin,Ledoff) ;
 }
 void Accessing()
 {
  for(int i = 0 ; i <3;i++)
    {
      Accesson() ;
      delay(30) ;
      Accessoff() ;
      delay(30) ;
          
    }
 }

  void Wifion()
 {
  digitalWrite(WifiPin,Ledon) ;
 }
 void Wifioff()
 {
  digitalWrite(WifiPin,Ledoff) ;
 }
String IpAddress2String(const IPAddress& ipAddress)
{
  return String(ipAddress[0]) + String(".") +\
  String(ipAddress[1]) + String(".") +\
  String(ipAddress[2]) + String(".") +\
  String(ipAddress[3])  ; 
}

 String GetMacAddress() {
  // the MAC address of your WiFi shield
  String Tmp = "" ;
  byte mac[6];
  
  // print your MAC address:
  WiFi.macAddress(mac);
  for (int i=0; i<6; i++)
    {
        Tmp.concat(print2HEX(mac[i])) ;
    }
    Tmp.toUpperCase() ;
  return Tmp ;
}

long POW(long num, int expo)
{
  long tmp =1 ;
  if (expo > 0)
  { 
        for(int i = 0 ; i< expo ; i++)
          tmp = tmp * num ;
         return tmp ; 
  } 
  else
  {
   return tmp ; 
  }
}

String SPACE(int sp)
{
    String tmp = "" ;
    for (int i = 0 ; i < sp; i++)
      {
          tmp.concat(' ')  ;
      }
    return tmp ;
}


String strzero(long num, int len, int base)
{
  String retstring = String("");
  int ln = 1 ;
    int i = 0 ; 
    char tmp[10] ;
    long tmpnum = num ;
    int tmpchr = 0 ;
    char hexcode[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'} ;
    while (ln <= len)
    {
        tmpchr = (int)(tmpnum % base) ;
        tmp[ln-1] = hexcode[tmpchr] ;
        ln++ ;
         tmpnum = (long)(tmpnum/base) ;
 
        
    }
    for (i = len-1; i >= 0 ; i --)
      {
          retstring.concat(tmp[i]);
      }
    
  return retstring;
}

unsigned long unstrzero(String hexstr, int base)
{
  String chkstring  ;
  int len = hexstr.length() ;
  
    unsigned int i = 0 ;
    unsigned int tmp = 0 ;
    unsigned int tmp1 = 0 ;
    unsigned long tmpnum = 0 ;
    String hexcode = String("0123456789ABCDEF") ;
    for (i = 0 ; i < (len ) ; i++)
    {
  //     chkstring= hexstr.substring(i,i) ; 
      hexstr.toUpperCase() ;
           tmp = hexstr.charAt(i) ;   // give i th char and return this char
           tmp1 = hexcode.indexOf(tmp) ;
      tmpnum = tmpnum + tmp1* POW(base,(len -i -1) )  ;
 
        
    }
  return tmpnum;
}

void InitLcd()
{
 
    lcd.init();                      // initialize the lcd 
    //cd 螢幕物件 初始化  lcd.init()
  // Print a message to the LCD.
  lcd.backlight();    //開啟背光
  lcd.clear() ;   //清除螢幕
  lcd.setCursor(0,0);   //設定游標位置(行數、列數)

}

void ShowAP(String apname)
{
  lcd.setCursor(0,1);
  lcd.print("                    ");  
  lcd.setCursor(0,1);
  lcd.print("AP:");  
  lcd.print(apname);  

}
void ClearShow()
{
    lcd.setCursor(0,0);
    lcd.clear() ;
    lcd.setCursor(0,0);
}

void ShowMAC()
{
  lcd.setCursor(0,0);
  lcd.print("                    ");  
  lcd.setCursor(0,0);
  lcd.print("MAC:");  
  lcd.print(MacData);  
  Serial.print("MAC:");  
  Serial.print(MacData);  
  Serial.print("\n");  

}
void ShowIP()
{
  lcd.setCursor(0,2);
  lcd.print("                    ");  
  lcd.setCursor(0,2);
  lcd.print("IP:");  
  lcd.print(ip);  
  Serial.print("IP:");  
  Serial.print(MacData);  
  Serial.print("\n");  

}




void ShowString(String ss)
{
  lcd.setCursor(0,3);
  lcd.print("                    ");  
  lcd.setCursor(0,3);
  lcd.print(ss.substring(0,19)); 
}


void ShowInternet()
{
    ShowMAC() ;
    ShowIP()  ;
}
