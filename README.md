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
|:----------:|:----------:|:-----:|:-----------------------:|:-------:|:-------:|:-----:|
| 2          | AxIN2      |       |                         |         |         |       |
| 5          |            |       | TxL                     |         |         |       |
| 6          |            |       | RxL                     |         |         |       |
| 7          | AxIN1      |       |                         |         |         |       |
| 8          |            |       |                         |         | 5       |       |
| 9          |            |       |                         |         | 14      |       |
| 10         |            |       |                         |         | 16      |       |
| 11         | Mode       |       |                         |         |         |       |
| 26         |            | Orange|                         |         |         |       |
| 36         | BxIN2      |       |                         |         |         |       |
| 37         | BxIN1      |       |                         |         |         |       |
|            |            |       | RxH                     | Trig    |         |       |         
|            |            |       | TxH                     | Echo    |         |       |         
|            | AOUT1      |       |                         |         |         | DC1   |         
|            | AOUT2      |       |                         |         |         | DC1   |         
|            | BOUT1      |       |                         |         |         | DC2   |         
|            | BOUT2      |       |                         |         |         | DC2   |        
| *+5V*      |*+3.3V, +6V*|*+5V*  |*+3.3V, +5V*             |*+5V*    |*+3.3V*  |*+6V*  |

## Controle by WiFi

In the first approach, I control the robot using a wifi network through the ESP8266 module 
and execute a given command (go ahead, turn, stand by 1 second) At first I tried to communicate 
between ESP8266 and TM4C123GXL via UART protocol, but the transmission did not go as I wanted, 
there were significant due to the fact that I had to send a few commands (exactly 8), I decided 
to use direct transmission. To encode 8 commands I needed 3 bits, which corresponds to the use of 
3 cables. Below is the truth table needed for coding and decoding commands.

|            | Bit 2 | Bit 1 | Bit 0 |
|:----------:|:-----:|:-----:|:-----:|
| No change  | 1     | 1     | 1     | 
| Forward    | 1     | 0     | 0     | 
| Backwards  | 1     | 0     | 1     | 
| Left       | 1     | 1     | 0     | 
| Right      | 0     | 1     | 1     | 
| Faster     | 0     | 1     | 0     | 
| Slower     | 0     | 0     | 1     | 
| Stop       | 0     | 0     | 0     | 

## Control by the robot

In this assumption the robot moves alone. He makes decisions in which direction he should go. 
Data needs to be done. It draws them from the distance sensor located on the front. If the robot 
approaches the bracket with a mite less than eg 20 cm. It stops, then rotates from the jail, until 
the distance from the obstacle is greater than 20 cm. Then continue to move forward as long as 
the distance is more than 20 cm.

It gives better results if the distance sensor turns around when the robot moves. You can say 
looks around. In this connection, the distance sensor is placed on the servomechanism, which during 
the movement of the robot spans the distance sensor from side to side and performs several measurements.

Below is a link to the video of how the robot moves https://youtu.be/uVNhvJOjNo0

