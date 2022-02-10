/*
 * This program is an attempt to make a device-agnostic WiFi test tool.
 */
//#include <SPI.h>
#include <ESP8266WiFi.h>
#include "privateInfo.h"


//const char* wifiSsid = "<change or use privateInfo.h>";
//const char* wifiPassword = "<change or use privateInfo.h>";
String sketchName = "WiFiScratchPad.ino";
String ipString = "127.0.0.1";
String macString = "00:00:00:00:00:00";
char ipCharArray[16];
char macCharArray[18];
byte macByteArray[6];


void setup() 
{
	Serial.begin( 115200 );
	while ( !Serial )
		delay( 100 );
//	Serial.setDebugOutput( true );
	Serial.println();
	Serial.println( "Running setup() in " + sketchName );

	// Get the MAC address.
	snprintf( macCharArray, 18, "%s", WiFi.macAddress().c_str() );		// Read the MAC address into a character array.
	macString = WiFi.macAddress().c_str();										// Read the MAC address into a String.
	WiFi.macAddress( macByteArray );

	Serial.println( "" );
	Serial.print( "MAC char array: " );
	Serial.println( macCharArray );
	Serial.print( "MAC byte array: " );
	Serial.printf( "%02X:%02X:%02X:%02X:%02X:%02X\n", macByteArray[0], macByteArray[1], macByteArray[2], macByteArray[3], macByteArray[4], macByteArray[5] );
	Serial.println( "MAC String: " + macString );

	// Set the ipCharArray char array to a default value.
	snprintf( ipCharArray, 16, "127.0.0.1" );

//	Serial.print( "Auto-reconnect = " );
//	Serial.println( WiFi.getAutoReconnect() );

	// Try to connect to the configured WiFi network, up to 20 times.
	wifiConnect( 20 );
	Serial.println( "Exiting setup()\n" );
} // End of setup() function.


void wifiConnect( int attemptCount )
{
	Serial.println( "\nEntering wifiConnect()" );
	// Announce WiFi parameters.
	Serial.print( "WiFi connecting to SSID \"" );
	Serial.print( wifiSsid );
	Serial.println( "\"" );

	// Connect to the WiFi network.
	Serial.printf( "Wi-Fi mode set to WIFI_STA %s\n", WiFi.mode( WIFI_STA ) ? "" : "Failed!" );
	WiFi.begin( wifiSsid, wifiPassword );

	int i = 0;
	/*
     WiFi.status() return values:
     0 : WL_IDLE_STATUS when WiFi is in process of changing between statuses
     1 : WL_NO_SSID_AVAIL in case configured SSID cannot be reached
     3 : WL_CONNECTED after successful connection is established
     4 : WL_CONNECT_FAILED if wifiPassword is incorrect
     6 : WL_DISCONNECTED if module is not configured in station mode
  */
	// Loop until WiFi has connected.
	while( WiFi.status() != WL_CONNECTED && i < attemptCount )
	{
		delay( 1000 );
		Serial.println( "Waiting for a connection..." );
		Serial.print( "WiFi status: " );
		Serial.println( WiFi.status() );
		Serial.print( ++i );
		Serial.println( " seconds" );
	}

	// Print that WiFi has connected.
	Serial.println( '\n' );
	Serial.println( "WiFi connection established!" );
	snprintf( ipCharArray, 16, "%d.%d.%d.%d", WiFi.localIP()[0], WiFi.localIP()[1], WiFi.localIP()[2], WiFi.localIP()[3] );		// Read the IP address into a character array.
	ipString = WiFi.localIP().toString();																													// Read the IP address into a String.
	Serial.print( "IP address character array: " );
	Serial.println( ipCharArray );
	Serial.println( "IP address String: " + ipString );
	Serial.println( "Exiting wifiConnect()\n" );
} // End of wifiConnect() function.


void printWifiData()
{
	Serial.println( "\nEntering printWifiData()" );

	// print your WiFi shield's IP address:
	IPAddress ip = WiFi.localIP();
	Serial.print("IP Address: ");
	Serial.println(ip);

	// print your MAC address:
	byte mac[6];
	WiFi.macAddress(mac);
	Serial.print("MAC address: ");
	Serial.print(mac[5], HEX);
	Serial.print(":");
	Serial.print(mac[4], HEX);
	Serial.print(":");
	Serial.print(mac[3], HEX);
	Serial.print(":");
	Serial.print(mac[2], HEX);
	Serial.print(":");
	Serial.print(mac[1], HEX);
	Serial.print(":");
	Serial.println(mac[0], HEX);

	Serial.println( "End of  printWifiData()\n" );
} // End of printWifiData() function.


void printCurrentNet()
{
	Serial.println( "\nEntering printCurrentNet()" );

	// print the SSID of the network you're attached to:
	Serial.print("SSID: ");
	Serial.println(WiFi.SSID());

	// print the MAC address of the router you're attached to:
	byte bssid[6];
//	WiFi.BSSID(bssid);
//	Serial.print("BSSID: ");
//	Serial.print(bssid[5], HEX);
//	Serial.print(":");
//	Serial.print(bssid[4], HEX);
//	Serial.print(":");
//	Serial.print(bssid[3], HEX);
//	Serial.print(":");
//	Serial.print(bssid[2], HEX);
//	Serial.print(":");
//	Serial.print(bssid[1], HEX);
//	Serial.print(":");
//	Serial.println(bssid[0], HEX);

	// print the received signal strength:
	long rssi = WiFi.RSSI();
	Serial.print("signal strength (RSSI):");
	Serial.println(rssi);

	// print the encryption type:
//	byte encryption = WiFi.encryptionType();
//	Serial.print("Encryption Type:");
//	Serial.println(encryption, HEX);

	Serial.println( "End of printCurrentNet()\n" );
} // End of printCurrentNet() function.


void loop() 
{
	Serial.println();
	Serial.println( sketchName );
	Serial.print( "MAC char array: " );
	Serial.println( macCharArray );
	Serial.println( "MAC String: " + macString );
	Serial.print( "IP char array: " );
	Serial.println( ipCharArray );
	Serial.println( "IP String: " + ipString );

	printCurrentNet();
	printWifiData();

	Serial.println( "Delaying 10 seconds...\n" );
	delay( 10000 );
} // End of loop() function.
