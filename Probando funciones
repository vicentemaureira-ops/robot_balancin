//Módulo doble puente H L9110S
//Calibración corriente: En la corriente analogica de 0-255, recien a los 100 los motores empiezan a moverse.
//Por lo que para no avanzar poner un 0, para avanzar lento 100 y rápido 255.
//La configuración a1 = 0 será para avanzar y la b1 para retroceder.

/* ---------- PINES PUENTE H ---------- */
//Motor 1
int A1a = 6;
int A1b = 9;
//Motor 2
int B1b = 3; 
int B1a = 5;


/* ---------- CONFIGURACIONES INICIALES ---------- */
void setup() {
  //Motor 1
  pinMode(A1b,OUTPUT);
  pinMode(A1a, OUTPUT);
  //Motor 2
  pinMode(B1b,OUTPUT);
  pinMode(B1a, OUTPUT);
}


/* ---------- LOOP ---------- */
void loop() {

  /* Si ambos motores van a avanzar y a la misma velocidad: */
  //avanzar(150,1,1);

  /* Si ambos van a avanzar, pero a distintas velocidades: */
  //avanzar(150,1,0);
  //avanzar(150,0,1);
}


/* ---------- FUNCIONES ---------- */

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
}
