/* ---------- LIBRERÍAS ---------- */
#include "I2Cdev.h"                                                       //Libreria auxiliar para I2C
#include "MPU6050_6Axis_MotionApps20.h"                                   //Libreria particular de la libreria MPU6050 que activa al DMP
#include "Wire.h"                                                         //Libreria estandar para comunicación I2C 


// --- SECCIÓN 2: OBJETO E INSTANCIA ---
MPU6050 mpu(0x68);                                                        //Objeto y su dirección.


// --- SECCIÓN 3: VARIABLES DE CONTROL ---
uint8_t devStatus;                                                        //Variable para guardar el estado. 
uint16_t packetSize;                                                      //Tamaño de cada paquete que envíe el DMP
uint16_t fifoCount;                                                       //Bytes guardados esperando a ser leidos. (FIFO, first in, first out. Cola de supermercado).
uint8_t fifoBuffer[64];                                                   //Lista donde se guardarán los datos crudos del sensor.
// uint8_t significa variable entera pequeña de 8 bits (para ahorrar memoria).


// --- SECCIÓN 4: VARIABLES DE ORIENTACIÓN ---
Quaternion q;                                                               //Cuaternión: Paquete de datos de orientación.  
VectorFloat gravity;                                                        //Dirección hacía donde está la gravedad.
float ypr[3];                                                               //Lista para 3 valores: Yaw, Pitch y Roll.
VectorInt16 aa;                                                             // Contenedor para la aceleración bruta (con gravedad)
VectorInt16 aaReal;                                                         // Contenedor para la aceleración real (sin gravedad)
//Las palabras iniciales son tipos de datos de la libreria llamados así con typedef. VectorInt16 guarda 3 valores. X,Y,Z.

// --- SECCIÓN 5: CONFIGURACIÓN (SETUP) ---
void setup() {
    Wire.begin();                                                           //Inicia el I2C.
    Wire.setClock(400000);                                                  //Aumenta la velocidad de la comunicación I2C porque el DMP envía demasiados datos.
    Serial.begin(115200);                                                   //Inicia la comunicación Serial.

    mpu.initialize();                                                       //Inicia el mpu (pero el DMP aún no).
    
    devStatus = mpu.dmpInitialize();                                        //Carga el código al DMP. Si tuvo éxito devuelve 0.

    // Calibración manual (Opcional pero recomendada)
    //Los números interiores son para compensar errores o desviaciones que tiene el sensor de fábrica.
    //Hay que medir esas desviaciones primero*.
    mpu.setXGyroOffset(152);
    mpu.setYGyroOffset(-54);
    mpu.setZGyroOffset(19);

    mpu.setXAccelOffset(4843);
    mpu.setYAccelOffset(-4599);
    mpu.setZAccelOffset(9616);

    if (devStatus == 0) {
        mpu.setDMPEnabled(true);                                            //Si la inicialización resultó, el activa el DMP.
        packetSize = mpu.dmpGetFIFOPacketSize();                            //Pregunta cual será el tamaño de los paquetes que enviará el DMP.
    } else {
        Serial.print("Error DMP");
    }
}

// --- SECCIÓN 6: BUCLE PRINCIPAL (LOOP) ---
void loop() {
    fifoCount = mpu.getFIFOCount();                                         //Leer cuantos bytes hay acumulados en el DMP.

    if (fifoCount < packetSize) {                                           //Si los bytes acumulados aún no llena un paquete:
        // No hacer nada, esperar más datos (se reunicia el loop).
    } 
    else {
        if (fifoCount == 1024) {                                            //Si se llenó la memoria (1024)
            mpu.resetFIFO();                                                //Borramos toda la memoria.
            Serial.println("FIFO Overflow!");
        } 
        else {
            while (fifoCount >= packetSize) {                               //Si tenemos datos disponibles:
                mpu.getFIFOBytes(fifoBuffer, packetSize);                   //Arg1: Donde se guardarán los datos. Arg2: Cuantos leo? (tamaño del paquete).
                fifoCount -= packetSize;                                    //Restamos lo que leimos.
            }

            //PROCESAMIENTO:
            mpu.dmpGetQuaternion(&q, fifoBuffer);                           //Tomar datos crudos y guardar en q.
            mpu.dmpGetGravity(&gravity, &q);                                //Usa los datos guardados en q para saber donde está la gravedad y guardarla en la variable gravity.
            mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);                      //Usa la gravedad y q para calcular Yaw, Pitch, Roll y guardalos en ypr.
            mpu.dmpGetAccel(&aa, fifoBuffer);                               //Extrae los datos brutos de la FIFO y los guarda en aa.
            mpu.dmpGetLinearAccel(&aaReal, &aa, &gravity);                  //Toma los datos brutos, le resta la gravedad para obtener la aceleración real (estado base 0,0,0).

            Serial.print("Y(z): "); Serial.print(ypr[0] * 180/M_PI); Serial.print(" \t");
            Serial.print(" P(y): "); Serial.print(ypr[1] * 180/M_PI); Serial.print(" \t");
            Serial.print(" R(x): "); Serial.print(ypr[2] * 180/M_PI); Serial.print(" \t\t");
            Serial.print("A(x): "); Serial.print(aaReal.x); Serial.print(" \t");
            Serial.print(" A(y): "); Serial.print(aaReal.y); Serial.print(" \t");
            Serial.print(" A(z): "); Serial.println(aaReal.z);
        }
    }
}
//Yaw: Gira respecto al eje Z.
//Pitch: Gira respecto al eje Y.
//Roll: Gira respecto al eje X.
