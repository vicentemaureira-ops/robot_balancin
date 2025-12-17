//Módulo doble puente H L9110S
//Calibración corriente: En la corriente analogica de 0-255, recien a los 150 los motores empiezan a moverse de manera segura.
//Por lo que para no avanzar poner un 0, para avanzar lento 150 y rápido 255.
//Cuando se deja un pin en valor 0 y el otro en pwm, el motor avanza hacía una dirección. Para la dirección contraria se hace lo mismo, pero con los pines invertidos.


/* ---------- FUNCIONES ---------- */

//Entrada: velocidad deseada, pin1 del motor, pin2 del motor.
//Salida: Nada.

void avanzar(int velocidad, int pin1, int pin2) {
  analogWrite(pin1, 0);
  analogWrite(pin2, velocidad);
}
void retroceder(int velocidad, int pin1, int pin2) {
  analogWrite(pin2, 0);
  analogWrite(pin1, velocidad);
}
