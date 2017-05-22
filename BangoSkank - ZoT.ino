/* Alright so this borrows *heavily* from https://github.com/kripthor/WiFiBeaconJam/blob/master/WiFiBeaconJam.ino so all credit to kripthor.
 *  other useful shit at https://mrncciew.com/2014/10/08/802-11-mgmt-beacon-frame/
 *  
 *  
  */
#include <ESP8266WiFi.h>

extern "C" {
  #include "user_interface.h"
}

byte channel;

// Beacon Packet buffer
uint8_t packet[128] /*frame control and duration*/ = { 0x80, 0x00, 0x00, 0x00, 
                /*4 - d mac bcast*/   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
                /*10 - s mac add*/  0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
                /*16 - bssid*/  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 
                /*22 seq ctl*/  0xc0, 0x6c, 
                /*24 time stamp*/  0x83, 0x51, 0xf7, 0x8f, 0x0f, 0x00, 0x00, 0x00, 
                /*32 beacon interval*/  0x64, 0x00, 
                /*34 capability*/  0x01, 0x04, 
                /* SSID */
                /*36*/  0x00/*element id*/, 0x20/*len*/, 0x72, 0x72, 0x72, 0x72, 0x72, 
                                                         0x72, 0x72, 0x72, 0x72, 0x72,
                                                         0x72, 0x72, 0x72, 0x72, 0x72,
                                                         0x72, 0x72, 0x72, 0x72, 0x72,
                                                         0x72, 0x72, 0x72, 0x72, 0x72,
                                                         0x72, 0x72, 0x72, 0x72, 0x72,
                                                         0x72, 0x72,
                /*doesntmatterhadsex*/        0x01, 0x08, 0x82, 0x84,
                /*doesntmatterhadsex*/        0x8b, 0x96, 0x24, 0x30, 0x48, 0x6c, 0x03, 0x01, 
                /*82 - channel*/  0x04};                       

int i = 0;

String alfa = "1234567890qwertyuiopasdfghjkklzxcvbnm QWERTYUIOPASDFGHJKLZXCVBNM_";
//what you want to broadcast goes here. It's an array of strings yo.
String stringus[] = {"Bango Skank was here.   "};
//set this as the number of items in stringus since we're here to have fun, not fix core deficencies of the Arduino language
int girth = 1;

void setup() {
  delay(500);
  wifi_set_opmode(STATION_MODE);
  wifi_promiscuous_enable(1); 
}



void loop() {
    // Randomize channel //
   
    channel = random(1,12); 
    wifi_set_channel(channel);

    // Randomize SRC MAC
    packet[10] = packet[16] = random(256);
    packet[11] = packet[17] = random(256);
    packet[12] = packet[18] = random(256);
    packet[13] = packet[19] = random(256);
    packet[14] = packet[20] = random(256);
    packet[15] = packet[21] = random(256);

    // Go for broke, max SSID length yo
    packet[38] = asdf(i, 0);
    packet[39] = asdf(i, 1);
    packet[40] = asdf(i, 2);
    packet[41] = asdf(i, 3);
    packet[42] = asdf(i, 4);/*5*/
    packet[43] = asdf(i, 5);
    packet[44] = asdf(i, 6);
    packet[45] = asdf(i, 7);
    packet[46] = asdf(i, 8);
    packet[47] = asdf(i, 9);/*10*/
    packet[48] = asdf(i, 10);
    packet[49] = asdf(i, 11);
    packet[50] = asdf(i, 12);
    packet[51] = asdf(i, 13);
    packet[52] = asdf(i, 14);/*15*/
    packet[53] = asdf(i, 15);
    packet[54] = asdf(i, 16);
    packet[55] = asdf(i, 17);
    packet[56] = asdf(i, 18);
    packet[57] = asdf(i, 19);/*20*/
    packet[58] = asdf(i, 20);
    packet[59] = asdf(i, 21);
    packet[60] = asdf(i, 22);
    packet[61] = asdf(i, 23);
    packet[62] = asdf(i, 24);/*25*/
    packet[63] = asdf(i, 25);
    packet[64] = asdf(i, 26);
    packet[65] = asdf(i, 27);
    packet[66] = asdf(i, 28);
    packet[67] = asdf(i, 29);/*30*/
    packet[68] = asdf(i, 30);
    packet[69]/*nice*/ = asdf(i, 31);/*max len*/
    
    packet[82] = channel;
    
    wifi_send_pkt_freedom(packet, 83, 0);
    wifi_send_pkt_freedom(packet, 83, 0);
    wifi_send_pkt_freedom(packet, 83, 0);
    delay(1);
    if (i == girth) {
      i=0;
    }
    else {
      i = i+1;
    }
}

char asdf(int x, int y) {
  if (y < stringus[x].length()) {
    return stringus[x][y];
  }
  else {
    return alfa[random(65)];
  }
}


