# ESP32Game
A simple game made using ESP32



# How to make
Componenets:
- ESP32-WROOM32
- 3 pushbuttons
- 1.77 TFT
- Protoboard
- Wires

For the code check the file name "espGame.ino", then you flash your esp32 with the code.

| ESP32 Pin  | TFT Pin  | Button1 Pin   | Button2 Pin   | Button3 Pin   |
|------------|----------|---------------|---------------|---------------|
| GND        | GND      | 1 LEG         | 1 LEG         | 1 LEG         |
| 5V         | VCC      |               |               |               |
| G4         | SCK      |               |               |               |
| G23        | SDA      |               |               |               |
| G16        | RES      |               |               |               |
| G5         | RS       |               |               |               |
| G18        | CS       |               |               |               |
| 5V/3.3V    | LEDA     |               |               |               |
| G12        |          | OPPOSITE LEG  |               |               |
| G13        |          |               | OPPOSITE LEG  |               |
| G14        |          |               |               | OPPOSITE LEG  |
