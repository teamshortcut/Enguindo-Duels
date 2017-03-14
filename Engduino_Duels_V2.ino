// Include Enguino libraries
#include <EngduinoLEDs.h>
#include <EngduinoButton.h>
#include <EngduinoIR.h>

// Variables to define what LEDs are lit initially
int  b=9;  
int r=8;

// Variables to define ammo and health values initially
int ammo = 11;
int health = 5;

void setup()
{
  startup();
}

void loop() {
  // Declares an integer to be sent with an IR signal (the value to be recieved) and a buffer to recieve a signal from other Engduinos
  int len = 0;
  uint8_t buf[IRBUFSZ];
  
  // Checks if a button has been pressed
  if (EngduinoButton.wasPressed()) {
    // If it has, send a signal with the value of len + 1
    EngduinoIR.send(len, +1);
    // It then lowers ammo and b by one, and sets the corresponding LED off, then delays 200 milliseconds.
    ammo = ammo -1;
    b = (b-1);
    EngduinoLEDs.setLED(b, OFF);
    delay(200);
  }
  // Assigns a value of whatever the Engduino recieves via IR to len, then checks if that value is less than 0.
  len = EngduinoIR.recv(buf, 1000);
  if (len > 0) {
    // If it is, than it lowers health by one and raises r by one, than sets the LED corresponding to r off.
    health = health - 1; 
    r = (r+1);
    EngduinoLEDs.setLED(r, OFF);
  }
  // Checks if the player is out of ammo, if so calls ammoFlash
  if(ammo < 1)
  {
    ammoFlash();
    startup();
  }
  
  // Checks if the player is out of health, if so calls healthFlash
  if(health < 1)
  {
    healthFlash();
    startup();
  } 
}

void startup(){
  // Begins the Engduino libraries, enabling us to use LEDs, Buttons and IR
  EngduinoLEDs.begin();
  EngduinoButton.begin();  
  EngduinoIR.begin();
  // Makes sure variables are set to starting values.
  ammo = 11;
  health = 5;
  b = 9;
  r = 8;
  // Sets the LEDs to starting values
  EngduinoLEDs.setLED(0, BLUE); 
  EngduinoLEDs.setLED(1, BLUE); 
  EngduinoLEDs.setLED(2, BLUE); 
  EngduinoLEDs.setLED(3, BLUE); 
  EngduinoLEDs.setLED(4, BLUE); 
  EngduinoLEDs.setLED(5, BLUE); 
  EngduinoLEDs.setLED(6, BLUE); 
  EngduinoLEDs.setLED(7, BLUE); 
  EngduinoLEDs.setLED(8, BLUE); 
  EngduinoLEDs.setLED(9, RED); 
  EngduinoLEDs.setLED(10, RED); 
  EngduinoLEDs.setLED(11, RED); 
  EngduinoLEDs.setLED(12, RED); 
  EngduinoLEDs.setLED(13, RED); 
  EngduinoLEDs.setLED(14, BLUE); 
  EngduinoLEDs.setLED(15, BLUE); 
}

void ammoFlash(){
    // Called when the player is out of ammo. Will flash the LEDs blue at least once, then continues doing so until the player holds down the button. It then calls startup to reset the game.
    do{
      EngduinoLEDs.setAll(BLUE);
      delay(500);
      EngduinoLEDs.setAll(OFF);
      delay(500);
    } while (EngduinoButton.isPressed() == false);
    startup();
}

void healthFlash(){
  // Called when the player is out of health. Will flash the LEDs red at least once, then continues doing so until the player holds down the button. It then calls startup to reset the game.
  do{
    EngduinoLEDs.setAll(RED);
    delay(500);
    EngduinoLEDs.setAll(OFF);
    delay(500);
  } while (EngduinoButton.isPressed() == false);
  startup();
}
