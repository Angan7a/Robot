# Robot

## Goal
The goal of this project is to create a traveling robot that will:
- driving the front / back
- turned left / right
- detected obstacles
- stopped before the "safe" distance
- rotated in place in a clockwise and counterclockwise direction
- be looking for a new direction

![alt text](https://github.com/Angan7a/Robot/blob/master/picture.png)

## Bill of material
- Texas Instruments Tiva C Series EK-TM4C123GXL - Launchpad evaluation board ([https://botland.com.pl/pl/texas-instruments/3684-texas-instruments-tiva-c-series-ek-tm4c123gxl-launchpad-evaluation-board.html](https://botland.com.pl/pl/texas-instruments/3684-texas-instruments-tiva-c-series-ek-tm4c123gxl-launchpad-evaluation-board.html))
- Chassis Rectangle 2WD ([https://botland.com.pl/pl/podwozia-robotow/7283-chassis-rectangle-2wd-2-kolowe-podwozie-robota-z-napedem.html](https://botland.com.pl/pl/podwozia-robotow/7283-chassis-rectangle-2wd-2-kolowe-podwozie-robota-z-napedem.html))
- DRV8835 two-channel motor controller 11V/1.2A ([https://botland.com.pl/pl/sterowniki-silnikow-dc/851-pololu-drv8835-dwukanalowy-sterownik-silnikow-11v12a.html](https://botland.com.pl/pl/sterowniki-silnikow-dc/851-pololu-drv8835-dwukanalowy-sterownik-silnikow-11v12a.html))
- SG90 servo motor ([https://botland.com.pl/pl/serwomechanizmy/484-serwo-towerpro-sg-90-micro-180.html](https://botland.com.pl/pl/serwomechanizmy/484-serwo-towerpro-sg-90-micro-180.html))
- HC-SR04 ultrasonic distance sensor ([https://botland.com.pl/pl/ultradzwiekowe-czujniki-odleglosci/1420-ultradzwiekowy-czujnik-odleglosci-hc-sr04-2-200cm.html](https://botland.com.pl/pl/ultradzwiekowe-czujniki-odleglosci/1420-ultradzwiekowy-czujnik-odleglosci-hc-sr04-2-200cm.html))
- Logic level converter ([https://botland.com.pl/pl/konwertery-napiec/2259-konwerter-poziomow-logicznych-dwukierunkowy-4-kanalowy-sparkfun.html](https://botland.com.pl/pl/konwertery-napiec/2259-konwerter-poziomow-logicznych-dwukierunkowy-4-kanalowy-sparkfun.html))
- ESP8266 module WiFi Witty ([https://botland.com.pl/pl/produkty-wycofane/7446-modul-wifi-esp8266-witty-mini-nodemcu.html](https://botland.com.pl/pl/produkty-wycofane/7446-modul-wifi-esp8266-witty-mini-nodemcu.html))
- Some jumper wires

## Connection
| TM4C123GXL | DRV8835    | SV90  | Logical level converter | HC-SR04 | ESP8266 | Motors|
|:----------:|:----------:|:-----:|:-----------------------:|: ------:|:-------:|:-----:|
| 2          | AxIN2      |       |                         |         |         |       |
| 5          |            |       | TXL                     |         |         |       |
| 6          |            |       | RXL                     |         |         |       |
| 5          |            |       | TXH                     | Trig    |         |       |
| 6          |            |       | RXH                     | Echo    |         |       |
| 7          | AxIN1      |       |                         |         |         |       |
| 8          |            |       |                         |         | 5       |       |
| 9          |            |       |                         |         | 14      |       |
| 10         |            |       |                         |         | 16      |       |
| 11         | Mode       |       |                         |         |         |       |
| 26         |            | Orange|                         |         |         |       |
| 36         | BxIN2      |       |                         |         |         |       |
| 37         | BxIN1      |       |                         |         |         |       |
|            | AOUT1      |       |                         |         |         | DC1   |         
|            | AOUT2      |       |                         |         |         | DC1   |         
|            | BOUT1      |       |                         |         |         | DC2   |         
|            | BOUT2      |       |                         |         |         | DC2   |        
| *+5V*      |*+3.3V, +6V*|*+5V*  |*+3.3V, +5V*             |*+5V*    |*+3.3V*  |*+6V*  |

