Finaly I could make an ESP32 controller for my Cambridge Audio CXA81 mk2 amplifier to control my amp from Homeassistant without using custom component.
This project using RS232 and Cambridge control bus too, beacuse the volume control is not possible over RS232.

<img width="377" height="1151" alt="HA dashboard" src="https://github.com/user-attachments/assets/e68ffb2e-ec02-49c9-b978-61ca212ca768" />

Working commands:
  RS232:
  
    Power ON and OFF
    Mute
    Input select
    FW version / Protocol version / Error state
    Raw RS232 string for debug purposes

  CTRL BUS:
  
    Power ON and OFF
    Volume +
    Volume -

RS232 commands have feedback to HA no matter you commanded from HA or with the IR remote control. CTRL BUS have no feedback, just sending the commands.
Volume control is not possible over RS232 so ctrl bus used for Vol up and down. I sniffed the volume commands from Cambridge streamer and repoduced with ESP. The ctrl bus useing manchaster codes at 0-5V level but the ESP GPIO is working on 3,3V so a level shifter will be needed.

Part list:

    ESP32 board
    MAX3232 RS232 to TTL Serial Port Converter Module DB9 Connector
    TXS0108E 8 Channel Logic Level Converter Module
    Optional temperature sensor
    RS232 male to male cross cable

Installation:
Just copy/paste the yaml to Homeassistant ESPHome builder and install it.

Connections:

    GPIO16 - RS232 board
    GPIO17 - RS232 board
    GPIO21 - TXS0108E level shifter (GND, 3,3V and 5V!)

![vol up](https://github.com/user-attachments/assets/105c4b0a-1a1b-4f40-8a94-7caa99686a62)

