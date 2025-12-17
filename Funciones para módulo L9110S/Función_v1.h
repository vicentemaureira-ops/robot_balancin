//Módulo doble puente H L9110S
//Calibración corriente: En la corriente analogica de 0-255, recien a los 100 los motores empiezan a moverse. Por lo que para no avanzar poner un 0, para avanzar lento 100 y rápido 255.
//La configuración a1 = 0 será para avanzar y la b1 = 0 para retroceder.
//En las entradas de motor1 y motor2 poner un 1 corresponde a activar el motor y un 0 a no considerarlo.

void avanzar(int velocidad,int motor1,int motor2){
  //Motor 1:
  if (motor1 == 1){
    analogWrite(A1a,0);
    analogWrite(A1b,velocidad);
  }
  //Motor 2:
  if (motor2 == 1){
    analogWrite(B1a,0);
    analogWrite(B1b,velocidad);
  }
}

void retroceder(int velocidad,int motor1,int motor2){
  //Motor 1:
  if (motor1 == 1){
    analogWrite(A1a,velocidad);
    analogWrite(A1b,0);
  }
  //Motor 2:
  if (motor2 == 1){
    analogWrite(B1a,velocidad);
    analogWrite(B1b,0);
  }
