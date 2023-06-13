**********OUTPUT TEST*********** 

I (772) LAB04: [APP] Startup.. 

I (772) LAB04: [APP] Free memory: 218732 bytes

I (782) LAB04: [APP] IDF version: v5.0.1-dirty

I (832) example_connect: Start example_connect.

I (842) wifi:wifi driver task: 3ffce8a8, prio:23, stack:6656, core=0

I (842) system_api: Base MAC address is not set

I (842) system_api: read default base MAC address from EFUSE

I (872) wifi:wifi firmware version: 17afb16

I (872) wifi:wifi certification version: v7.0

I (872) wifi:config NVS flash: enabled

I (872) wifi:config nano formating: disabled

I (872) wifi:Init data frame dynamic rx buffer num: 32

I (882) wifi:Init management frame dynamic rx buffer num: 32

I (882) wifi:Init management short buffer num: 32

I (892) wifi:Init dynamic tx buffer num: 32

I (892) wifi:Init static rx buffer size: 1600

I (892) wifi:Init static rx buffer num: 10

I (902) wifi:Init dynamic rx buffer num: 32

I (902) wifi_init: rx ba win: 6

I (902) wifi_init: tcpip mbox: 32

I (912) wifi_init: udp mbox: 6

I (912) wifi_init: tcp mbox: 6

I (922) wifi_init: tcp tx win: 5744

I (922) wifi_init: tcp rx win: 5744

I (922) wifi_init: tcp mss: 1440

I (932) wifi_init: WiFi IRAM OP enabled

I (932) wifi_init: WiFi RX IRAM OP enabled

I (942) phy_init: phy_version 4670,719f9f6,Feb 18 2021,17:07:07

I (1042) wifi:mode : sta (b8:d6:1a:a7:23:ec)

I (1042) wifi:enable tsf

I (1052) example_connect: Connecting to QiQi...

I (1052) example_connect: Waiting for IP(s)

I (3462) wifi:new:<1,0>, old:<1,0>, ap:<255,255>, sta:<1,0>, prof:1

I (4142) wifi:state: init -> auth (b0)

I (4142) wifi:state: auth -> assoc (0)

I (4152) wifi:state: assoc -> run (10)

I (4172) wifi:connected with QiQi, aid = 1, channel 1, BW20, bssid = ba:52:4d:d1:b2:34

I (4172) wifi:security: WPA2-PSK, phy: bgn, rssi: -57

I (4172) wifi:pm start, type: 1



I (4352) wifi:AP's beacon interval = 102400 us, DTIM period = 1

I (5182) esp_netif_handlers: example_netif_sta ip: 172.20.10.7, mask: 255.255.255.240, gw: 172.20.10.1

I (5182) example_connect: Got IPv4 event: Interface "example_netif_sta" address: 172.20.10.7

I (5832) example_connect: Got IPv6 event: Interface "example_netif_sta" address: fe80:0000:0000:0000:bad6:1aff:fea7:23ec, type: ESP_IP6_ADDR_IS_LINK_LOCALI (5832)
example_common: Connected to example_netif_sta

I (5842) example_common: - IPv4 address: 172.20.10.7,

I (5842) example_common: - IPv6 address: fe80:0000:0000:0000:bad6:1aff:fea7:23ec, type: ESP_IP6_ADDR_IS_LINK_LOCAL

I (5862) BTDM_INIT: BT controller compile version [60aae55]

I (6212) BLE_COMP: create attribute table successfully, the number handle = 11


I (6222) LAB04: Other event id:7

I (6232) BLE_COMP: (0) ***** advertising start successfully ***** 


I (6232) wifi:<ba-add>idx:0 (ifx:0, ba:52:4d:d1:b2:34), tid:0, ssn:2, winSize:64
	
I (6612) wifi:<ba-add>idx:1 (ifx:0, ba:52:4d:d1:b2:34), tid:1, ssn:0, winSize:64
	
I (8052) LAB04: MQTT_EVENT_CONNECTED
	
I (8052) LAB04: sent publish data, msg_id=0
	
I (8052) LAB04: sent subscribe successful, msg_id=43769
	
I (8872) LAB04: MQTT_EVENT_SUBSCRIBED, msg_id=43769
	
I (25052) BLE_COMP: ESP_GATTS_CONNECT_EVT, conn_id = 0
	
I (25302) BLE_COMP: (1) ***** pair status = success ***** 
	

E (28082) BLE_COMP: (2) ***** read char1 ***** 

	
E (30692) BLE_COMP: (5) ***** read char2 ***** 
	

I (62422) LAB04: MQTT_EVENT_DATA
	
TOPIC=topic/qos1
	
DATA=Hello ESP32, from laptop
	
