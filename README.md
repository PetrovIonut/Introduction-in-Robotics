# Introduction-in-Robotics
Introduction in Robotics Arduino

Charging Station Project in Arduino 

  Task description :
  In this task I had to simulate a charging station for an electric vehicle, using some LEDs and buttons. In this task I had to take into account the state of buttons and to implement debounce.
 
  Components used :
  -4 BLUE LEDs
  -1 RGB LED to indicate charging station state (occupied/free)
  -2 Buttons (Start/Stop)
  -8 Resistors(6x220 ohm & 2x1K ohm for Buttons)
  -Breadboard
  -Wires

  Technical description:
    The RGB led represemts the station status (occupied/free). If the station is free the LED will be Green, and if the station is occupied the LED will be Red.
    The simple LEDs represent the charging percentage of the battery (LED1 = 25%, LED2 = 50% and so on). The LEDs will illuminate one by one at a fixed 3s interval.
  The LED that shows the current charging percentage will blink, the LEDs for the previous charging percentages will stay ON, the others OFF.
    A short press of the START button will start the charging process. Pressing this button during this process will do nothing.
    A long press of the STOP button will force stop the charging process and will reset the station to the initial state(free). Pressing this button while the station is free won't do anything.
    
  Functionality:
    Charging station state is 'Free'. The RGB status LED is Green.
    The START button is pressed.
    Status LED will be Red, and the charging process will start by turning ON the first LED.
    The first LED will blink for 3s, the others being off.
    After charging the first 25%, the first LED will stay ON, and the second LED will start blinking.
    After charging finishes, all LEDs will blink simultaneously and then they will turn OFF, to signal the end of the charging process.
    The status LED will be Green.
    If the STOP button is pressed at anytime during the charging process for more than 2s, charging will be stopped, all LEDs will blink 3 times, and the status     Led will be Green.
    

  Pictures with setup:
  ![IMG20241021222533](https://github.com/user-attachments/assets/91394540-44e4-47c0-9bbe-2b3874185a0a)
  ![IMG20241021222520](https://github.com/user-attachments/assets/cbfd9485-80c0-49e9-ba6b-66d3f6e82e6d)
  ![IMG20241021222506](https://github.com/user-attachments/assets/a7a4875a-8dd2-423a-9548-0029eee54919)

  Video testing functionality : https://youtu.be/YnEYB3pL970
  
  Electrical scheme in Tinkercad : https://www.tinkercad.com/things/562FGQMi8ND/editel?sharecode=QGSDz74NoYW0Xm4GzCPRkDmwgFd_ROyZJrkqKlnHQYk

  
  
  
  
