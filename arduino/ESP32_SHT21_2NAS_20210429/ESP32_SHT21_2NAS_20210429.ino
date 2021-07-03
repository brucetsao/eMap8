//-----------------------
#include "arduino_secrets.h"
#include "MQTTLib.h" 

#include "crc16.h"
#include <ArduinoJson.h>





//char ssid[] = SECRET_SSID;        // your network SSID (name)
//char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;            // your network key Index number (needed only for WEP)
          // your network key Index number (needed only for WEP)

  IPAddress ip ;
  long rssi ;

int status = WL_IDLE_STATUS;
char iotserver[] = "ncnu.arduino.org.tw";    // name address for Google (using DNS)
int iotport = 9999 ;
// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
String strGet="GET /dhtdata/dhDatatadd.php";
String strHttp=" HTTP/1.1";
String strHost="Host: ncnu.arduino.org.tw:9999";  //OK
 String connectstr ;



//  control parameter 
boolean systemstatus = false ;
boolean Reading = false ;
boolean Readok = false ;
// int trycount = 0 ;
int wifierror = 0 ;
boolean btnflag = false ;





void printWiFiStatus() {
  // printStrTemp the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}







void initAll()
{
    Serial.begin(9600);
    myHardwareSerial.begin(9600, SERIAL_8N1, RXD2, TXD2);
    pinMode(AccessPin,OUTPUT) ;
    pinMode(WifiPin,OUTPUT) ;
    //pinMode(BeepPin,OUTPUT) ;
    Wifioff() ;
    Accessoff() ;  
   // Beepoff() ; 
  Serial.println("System Start") ;  

 
}








void setup() 
{
        
  //Initialize serial and wait for port to open:
    initAll() ;
  WiFi.disconnect(true);
  WiFi.setSleep(false);

  
    wifiMulti.addAP(AP1, PW1);
    wifiMulti.addAP(AP2, PW2);
    wifiMulti.addAP(AP3, PW3);
//    wifiMulti.addAP(AP4, PW4);

    Serial.println("Connecting Wifi...");
  //    TFTCPrint(30,60,"連線中...",TFT_WHITE);

    
    while(wifiMulti.run() != WL_CONNECTED) 
    {
          Serial.print("*");
              
    }
        Apname = WiFi.SSID();
        ip = WiFi.localIP();
        Serial.println("");
        Serial.print("Successful Connectting to Access Point:");
        Serial.println(WiFi.SSID());
        Serial.print("\n");
        
        Serial.println("WiFi connected");
        Serial.print("Access Point Name: ");
        Serial.println(Apname);
        Serial.print("IP address: ");
        Serial.println(ip);
        // ShowAP() ;

  MacData = GetMacAddress() ; 
  ShowInternet() ;
   Wifion() ;     
    phasestage=1 ;
    flag1 = false ;
    flag2 = false ;
    

} 
void requesttemperature()
{
    Serial.println("now send data to device") ;
    myHardwareSerial.write(Str1,8);
     Serial.println("end sending") ;      
}
void requesthumidity()
{
    Serial.println("now send data to device") ;
    myHardwareSerial.write(Str2,8);
     Serial.println("end sending") ;      
}

void requestdata()
{
  
    Serial.println("now send request to device") ;
    myHardwareSerial.write(StrTemp,8);

     Serial.println("end sending") ;      
}
int GetDHTdata(byte *dd)
{
  int count = 0 ;
  long strtime= millis() ;
  while ((millis() -strtime) < 2000)
    {
    if (myHardwareSerial.available()>0)
      {
        Serial.println("Controler Respones") ;
          while (myHardwareSerial.available()>0)
          {
             myHardwareSerial.readBytes(&cmd,1) ;
             Serial.print(print2HEX((int)cmd)) ;
              *(dd+count) =cmd ;
              count++ ;

          }
          Serial.print("\n---------\n") ;
      }
      return count ;
    }
  
}
void loop()   
{
  if ((phasestage==1) && flag1 && flag1)
  {
      Serial.print("From Device :(") ;
      Serial.print((float)temp/10) ;
      Serial.print(" .C / ") ;
      Serial.print((float)humid/10) ;
      Serial.print(")\n") ;
      // Senddata to nas here
      flag1 = false ;
      flag2 = false ;
      Accessing() ;
      SendtoNAS() ;
     delay(30000) ; 
     return ;     
  }
  if (phasestage == 1)
    {
        Accessing() ;
        requesttemperature() ;
    }
  if (phasestage == 2)
    {
        Accessing() ;
        requesthumidity() ;
    }

    delay(200);
    Accessing() ;
    receivedlen = GetDHTdata(receiveddata) ;
    if (receivedlen >2)
      {
              Serial.print("Data Len:") ;
              Serial.print(receivedlen) ;
              Serial.print("\n") ;
              Serial.print("CRC:") ;
              Serial.print(ModbusCRC16(receiveddata,receivedlen-2)) ;
              Serial.print("\n") ;
              for (int i = 0 ; i <receivedlen ; i++)
                {
                  Serial.print(receiveddata[i],HEX) ;
                  Serial.print("/") ;
                }
                  Serial.print("...\n") ;
              Serial.print("CRC Byte:") ;
              Serial.print(receiveddata[receivedlen-1],HEX) ;
              Serial.print("/") ;
              Serial.print(receiveddata[receivedlen-2],HEX) ;
              Serial.print("\n") ;
          if (CompareCRC16(ModbusCRC16(receiveddata,receivedlen-2),receiveddata[receivedlen-1],receiveddata[receivedlen-2]))
            {
                if (phasestage == 1)
                {
                    temp = receiveddata[3]*256+receiveddata[4] ;
                    flag1 = true ;
                    phasestage=2 ;
                    return ;
                }
                if (phasestage == 2)
                {
                    humid = receiveddata[3]*256+receiveddata[4] ;
                    flag2 = true ;
                    phasestage=1 ;
                    return ;
                }

            }
      }

//UartTest() ;
      delay(5000) ;
} // END Loop


void SendtoNAS()
{
  //http://ncnu.arduino.org.tw:9999/dhtdata/dhDatatadd.php?MAC=AABBCCDDEEFF&T=34&H=34   //AccessOn() ; 
  connectstr = "?MAC=" + MacData + "&T=" + String((double)temp/10) + "&H=" + String((double)humid/10);
  Serial.println(connectstr) ;
  if (client.connect(iotserver, iotport)) {
    Serial.println("Make a HTTP request ... ");
    //### Send to Server
    String strHttpGet = strGet + connectstr + strHttp;
    Serial.println(strHttpGet);

    client.println(strHttpGet);
    client.println(strHost);
    client.println();
  }

  if (client.connected())
  {
    client.stop();  // DISCONNECT FROM THE SERVER
  }

  //AccessOff() ;

}

void UartTest()
{
    myHardwareSerial .println("This is a Test!!!") ;
}
