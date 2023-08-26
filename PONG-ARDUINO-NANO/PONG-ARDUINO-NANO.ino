#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//Definición de los pines
#define PlayerA A0  //jugador 1
#define PlayerB A1  // jugador 2
#define Sound 3     //sonido del juego
#define RST 4       //necesario para el contructor de la pantalla
#define START_B 5   //iniciar el juego

//graficos
#define FONT_SIZE 1
#define SCREEN_WIDHT 124
#define SCREEN_HEIGHT 30
#define PADDLE_WIDHT 4
#define PADDLE_HEIGHT 8
#define PADDLE_PADDING 5
#define BALL_SIZE 3
#define SCORE_PADDING 10

Adafruit_SSD1306 screen(RST);

//UBICACIÓN DE LAS PALETAS
int paddleLocationA = 0;
int paddleLocationB = 0;
int lastPaddleLocationA = 0;
int lastPaddleLocationB = 0;

//UBICAR LA PELOTA EN EL CENTRO DE LA PANTALLA
float ballX = SCREEN_WIDHT / 2;
float ballY = SCREEN_HEIGHT / 2;

//VELOCIDAD DE LA PELOTA
float ballSpeedX = 3;
float ballSpeedY = 2;

//puntajes
int scoreA = 0;
int scoreB = 0;

void (*resetFunc)(void) = 0;  //reset por software


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  screen.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  screen.clearDisplay();
  screen.display();
  screen.setTextWrap(false);
  pinMode(START_B, INPUT);

  start();

  screen.setTextColor(WHITE);
  screen.setTextSize(FONT_SIZE);
  screen.clearDisplay();
  
}

void start() {
  screen.clearDisplay();
  screen.setTextColor(WHITE);
  centerPrint((char *)"PONG", 0, 2);
  centerPrint((char *)"by: Julian S", 15, 1);
  screen.fillRect(0, SCREEN_HEIGHT - 7, SCREEN_WIDHT, 12, WHITE);
  screen.setTextColor(BLACK);
  centerPrint((char *)"PRESS START", SCREEN_HEIGHT - 6, 1);
  screen.display();
  while(digitalRead(START_B) == HIGH){    
        
  }
  
}

void loop() {
  Calculate_mov();
  draw();
  win_dect();  
}

//Agregar función para el sonido
void sound(){
  int volumen = 100;
  

}

void Calculate_mov() {

  int controlA = analogRead(PlayerA);
  int controlB = analogRead(PlayerB);

  paddleLocationA = map(controlA, 0, 1023, 0, SCREEN_HEIGHT - PADDLE_HEIGHT);
  paddleLocationB = map(controlB, 0, 1023, 0, SCREEN_HEIGHT - PADDLE_HEIGHT);

  ballX += ballSpeedX;
  ballY += ballSpeedY;

  //COLISIONES DE LA PELOTA

  if (ballY <= 0 || ballY >= SCREEN_HEIGHT - BALL_SIZE) {
    ballSpeedY *= -1;
  }

  //colision jugador A
  if (ballX >= PADDLE_PADDING && ballX <= PADDLE_PADDING + BALL_SIZE && ballSpeedX < 0) {
    if (ballY > paddleLocationA - BALL_SIZE && ballY < paddleLocationA + PADDLE_HEIGHT) {
      ballSpeedX *= -1;
    }
  }

  //COLISION JUGADOR B

  if (ballX >= SCREEN_WIDHT - PADDLE_WIDHT - PADDLE_PADDING - BALL_SIZE && ballX <= SCREEN_WIDHT - PADDLE_PADDING - BALL_SIZE && ballSpeedX > 0) {
    if (ballY > paddleLocationB - BALL_SIZE && ballY < paddleLocationB + PADDLE_HEIGHT) {
      ballSpeedX *= -1;
    }
  }

  //ANOTACIÓN

  if (ballX >= SCREEN_WIDHT - BALL_SIZE || ballX <= 0) {
    if (ballSpeedX > 0) {
      scoreA++;
    }
    if (ballSpeedX < 0) {
      scoreB++;
    }
    //dispone la pelota en el centro de nuevo
    ballX = SCREEN_WIDHT / 2;
    ballY = SCREEN_HEIGHT / 2;
  }

  
}

void win_dect(){
  
  if (scoreA >= 6) {
    screen.clearDisplay();
    centerPrint((char *)"PLAYER 1",0,2);
    centerPrint((char *)"WON!!",15,2);    
    screen.display();

    scoreA=0;
    scoreB=0;
        
    delay(5000);
    resetFunc();
        
  }

  if (scoreB >= 6) {
    screen.clearDisplay();
    centerPrint((char *)"PLAYER 2",0,2);
    centerPrint((char *)"WON!!",15,2);    
    screen.display();

    scoreA=0;
    scoreB=0;
        
    delay(5000);
    resetFunc();
        
  }

}

void draw() {
  screen.clearDisplay();

  //PALETA A
  screen.fillRect(PADDLE_PADDING, paddleLocationA, PADDLE_WIDHT, PADDLE_HEIGHT, WHITE);

  //PALETA B
  screen.fillRect(SCREEN_WIDHT - PADDLE_PADDING, paddleLocationB, PADDLE_WIDHT, PADDLE_HEIGHT, WHITE);

  //PELOTA
  screen.fillRect(ballX, ballY, BALL_SIZE, BALL_SIZE, WHITE);

  //lineas del centro

  for (int i = 0; i < SCREEN_HEIGHT; i += 4) {
    screen.drawFastVLine(SCREEN_WIDHT / 2, i, 2, WHITE);
  }

  //PUNTAJE A
  screen.setCursor(SCREEN_WIDHT / 2 - FONT_SIZE * 12, 0);
  screen.print(scoreA);

  //PUNTAJE B
  screen.setCursor(SCREEN_WIDHT / 2 + 1 + FONT_SIZE * 6, 0);
  screen.print(scoreB);


  screen.display();
}

void centerPrint(char *text, int y, int size) {
  screen.setTextSize(size);
  screen.setCursor(SCREEN_WIDHT / 2 - ((strlen(text)) * 6 * size) / 2, y);
  screen.print(text);
}
