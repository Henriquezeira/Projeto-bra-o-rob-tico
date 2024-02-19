#include <Servo.h>

Servo base;
Servo altura;
Servo angulo;
Servo garra;

int joystickXPin = A5; // Porta Analógica do joystick para controle do eixo X
int joystickYPin = A4; // Porta Analógica do joystick para controle do eixo Y
int botaoJoystickPin = 2; // Porta Digital do botão do joystick

int step = 1; // Passo de movimento para todos os servos

void setup() {
  base.attach(8);
  altura.attach(10);
  angulo.attach(9);
  garra.attach(11);
  pinMode(botaoJoystickPin, INPUT_PULLUP);
}

void loop() {
  int joystickXValue = analogRead(joystickXPin);
  int joystickYValue = analogRead(joystickYPin);
  int botaoJoystickState = digitalRead(botaoJoystickPin);

  // Mapeie os valores do joystick para os ângulos dos servos
  int baseAngle = map(joystickXValue, 0, 1023, 0, 180);
  int alturaAngle = map(joystickYValue, 0, 1023, 0, 180);

  // Controle da garra com o botão do joystick
  if (botaoJoystickState == LOW) {
    // Se o botão do joystick estiver pressionado, feche a garra
    garra.write(90); // Ângulo para fechar a garra (ajuste conforme necessário)
  } else {
    // Caso contrário, controle a garra com o joystick
    int garraAngle = map(joystickXValue, 0, 1023, 0, 180);
    moveServo(garra, garraAngle);
  }

  // Controle dos outros servos com o joystick
  moveServo(base, baseAngle);
  moveServo(altura, alturaAngle);
  moveServo(angulo, !alturaAngle);

  delay(10); // Pequeno atraso para estabilidade
}

// Função para mover um servo gradualmente para a posição desejada com controle de velocidade
void moveServo(Servo servo, int targetAngle) {
  int currentAngle = servo.read();

  // Verifique se o ângulo atual é diferente do ângulo desejado
  if (targetAngle != currentAngle) {
    // Determine a direção do movimento
    if (targetAngle > currentAngle) {
      currentAngle += step;
    } else {
      currentAngle -= step;
    }

    // Atualize a posição do servo
    servo.write(currentAngle);

    // Pequeno atraso para controlar a velocidade
    delay(10);
  }
}
