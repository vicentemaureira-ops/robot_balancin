/* ---------- LIBRERIAS ---------- */
#include "L9110S_v2.h"


/* ---------- PINES PUENTE H ---------- */
//Motor 1
int A1a = 3;
int A1b = 5;
//Motor 2
int B1b = 6;
int B1a = 9;


/* ---------- CONFIGURACIONES INICIALES ---------- */
void setup() {
  //Motor 1
  pinMode(A1b, OUTPUT);
  pinMode(A1a, OUTPUT);
  //Motor 2
  pinMode(B1b, OUTPUT);
  pinMode(B1a, OUTPUT);
}


/* ---------- LOOP ---------- */
void loop() {
  //avanzar(150, A1a,A1b);
  //avanzar(150, B1a,B1b);
}
