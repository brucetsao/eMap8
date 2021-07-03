char iotserver[] = "ncnu.arduino.org.tw";    // name address for Google (using DNS)
int iotport = 9999 ;
// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
String strGet="GET /dhtdata/dhDatatadd.php";
String strHttp=" HTTP/1.1";
String strHost="Host: ncnu.arduino.org.tw:9999";  //OK
 String connectstr ;
