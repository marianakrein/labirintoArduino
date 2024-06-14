#include <Servo.h> //biblioteca necessária para a programação dos servos.

Servo myServoX; //declaração da variável do servo no eixo X.
Servo myServoY; //declaração da variável do servo no eixo Y.

int ServoXPin = 8; //pino em que o servo no eixo X irá ficar.

int ServoYPin = 9; //pino em que o servo no eixo Y irá ficar.

int ServoXHomePos = 90; //ângulo em que o servo irá iniciar no eixo X.

int ServoYHomePos = 80; //ângulo em que o servo irá iniciar no eixo Y.

int ServoXPos = 103; //posição atual do servo no eixo X (irá variar).

int ServoYPos = 135; //posição atual do servo no eixo Y (irá variar).

int XAxlePin = A0; //pino para a movimentação X do joystick.

int YAxlePin = A1; //pino para a movimentação Y do joystick.

int XAxleValue = 0; //valor de inicialização do eixo X do joystick.

int YAxleValue = 0; //valor de inicialização do eixo Y do joystick.

int Direction = 0; //variável para controlar a sensibilidade e direção de movimento.

int range = 12; //variável para controlar a sensibilidade e direção de movimento.

int center = range / 2; //variável para controlar a sensibilidade e direção de movimento.

int threshold = range / 4; //variável para controlar a sensibilidade e direção de movimento. 

void setup() {
  //configuração inicial, onde os servos são inicializados aos pinos especificados.
  myServoX.attach(ServoXPin);

  myServoY.attach(ServoYPin);

  myServoX.write(ServoXPos);

  myServoY.write(ServoYPos);

  Serial.begin(9600); // inicialização do monitor serial.
}

void loop(){
  XAxleValue = readAxis(XAxlePin);
  YAxleValue = readAxis(YAxlePin);

  Serial.print(XAxleValue, DEC);
  Serial.print(" - ");
  Serial.println(YAxleValue, DEC);
  //leitura dos valores do joystick e mostrado no monitor serial.

  if (XAxleValue > 0) { //condição para mover o servo X para a esquerda.
    ServoXPos--;
    myServoX.write(ServoXPos);
    delay(1 * (7 - XAxleValue));
  }

  if (XAxleValue < 0) { //condição para mover o servo X para a direita.
    ServoXPos++;
    myServoX.write(ServoXPos);
    delay(1 * (7 + XAxleValue));
  }

  if (YAxleValue > 0) { //condição para mover o servo Y para cima.
    ServoYPos++;
    myServoY.write(ServoYPos);
    delay(1 * (7 - YAxleValue));
  }

  if (YAxleValue < 0) { //condição para mover o servo Y para baixo.
    ServoYPos--;
    myServoY.write(ServoYPos);
    delay(1 * (7 + YAxleValue));
  }
}

int readAxis(int thisAxis) {
  // essa função lê o valor do joystick e o mapeia para o intervalo específico dos servo.
  // a distância do valor lido ao centro do intervalo é calculada.
  // se a distância estiver dentro de um limite específico, a distância é considerada zero para evitar movimentos não intencionais. 
  int reading = analogRead(thisAxis);

  reading = map(reading, 0, 1023, 0, range);

  int distance = reading - center;
  if (abs(distance) < threshold) {
    distance = 0;
  }

  return distance;
}
