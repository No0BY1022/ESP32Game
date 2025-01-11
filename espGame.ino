#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <Bounce2.h>

#define TFT_CS     18 //GPIO18 - CS
#define TFT_RST    16 //GPIO16 - Reset
#define TFT_DC     5  //GPIO5 - RS
#define TFT_SCK    4 //GPIO4 - SCK
#define TFT_MOSI   23 //GPIO23 - SDA

#define BUTTON_UP    12
#define BUTTON_DOWN  13
#define BUTTON_START 14

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

Bounce debouncerUp = Bounce();
Bounce debouncerDown = Bounce();
Bounce debouncerStart = Bounce();

int playerY = 60;  //vertical position
int playerHeight = 10;
int playerWidth = 10;
int playerSpeed = 3;

int obstacleX = 140;  //horizontal position
int obstacleY = 60;   //vertical position
int obstacleWidth = 10;
int obstacleHeight = 10;
int obstacleSpeed = 2;

bool gameRunning = true;

void setup() {
  SPI.begin(TFT_SCK, -1, TFT_MOSI, TFT_CS);
  tft.initR(INITR_BLACKTAB);
  tft.setRotation(3);
  tft.fillScreen(ST7735_BLACK);

  pinMode(BUTTON_UP, INPUT_PULLUP);
  pinMode(BUTTON_DOWN, INPUT_PULLUP);
  pinMode(BUTTON_START, INPUT_PULLUP);

  debouncerUp.attach(BUTTON_UP);
  debouncerUp.interval(25);
  debouncerDown.attach(BUTTON_DOWN);
  debouncerDown.interval(25);
  debouncerStart.attach(BUTTON_START);
  debouncerStart.interval(25);

  Serial.begin(115200);
  drawGame();
}

void loop() {
  if (!gameRunning) {
    //start button to reset the game
    debouncerStart.update();
    if (debouncerStart.fell()) {
      resetGame(); //Reset the game
    }
    return; //Stop the game logic if the game is over
  }

  //debouncer 
  debouncerUp.update();
  debouncerDown.update();

  //Move player based on button press
  if (debouncerUp.fell()) {
    playerY -= playerSpeed;  //Move up
    Serial.println("UP button pressed!");
  }
  if (debouncerDown.fell()) {
    playerY += playerSpeed;  //Move down
    Serial.println("DOWN button pressed!");
  }

  playerY = constrain(playerY, 0, tft.height() - playerHeight);

  //Move obstacle
  obstacleX -= obstacleSpeed;
  if (obstacleX < -obstacleWidth) {
    obstacleX = tft.width();
    obstacleY = random(20, tft.height() - obstacleHeight);
  }

  //Check for collision
  if (obstacleX < playerWidth && 
      obstacleX + obstacleWidth > 0 &&
      playerY < obstacleY + obstacleHeight && 
      playerY + playerHeight > obstacleY) {
    gameOver();
  }

  //Redraw the game
  drawGame();
  delay(30);  //game speed
}

void gameOver() {
  gameRunning = false;  // Stop the game
  tft.fillScreen(ST7735_RED);
  tft.setCursor(20, 60);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(1);
  tft.print("Game Over");

  tft.setCursor(10, 80);
  tft.print("Press START to Retry");

  Serial.println("Game Over!");

  delay(1000);
}

void resetGame() {
  //Reset game
  gameRunning = true;

  playerY = tft.height() / 2 - playerHeight / 2;  //Center player
  obstacleX = tft.width();
  obstacleY = random(20, tft.height() - obstacleHeight);

  tft.fillScreen(ST7735_BLACK);
  drawGame();
  Serial.println("Game Reset!");
}

void drawGame() {
  //clear the screen
  tft.fillScreen(ST7735_BLACK);

  //Draw player
  tft.fillRect(0, playerY, playerWidth, playerHeight, ST7735_BLUE);

  //Draw obstacle
  tft.fillRect(obstacleX, obstacleY, obstacleWidth, obstacleHeight, ST7735_RED);

  //Debugging output
  Serial.print("Player Y: ");
  Serial.print(playerY);
  Serial.print(", Obstacle X: ");
  Serial.print(obstacleX);
  Serial.print(", Obstacle Y: ");
  Serial.println(obstacleY);
}
