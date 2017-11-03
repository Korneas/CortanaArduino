/*
  Conexion Android-Lilypad
  por: Camilo Montoya
  fecha: Noviembre 2, 2017
  licencia: Dominio publico

  En el codigo a continuacion, se hara
  una conexion bluetooth con un modulo RN-41
  a un dispositivo android con el fin de identificar
  mensajes de este para el uso de actuadroes

  Se utiliza la libreria SoftwareSerial para conocer mas
  En el link:
  https://www.arduino.cc/en/Reference/SoftwareSerialRead
*/
#include <SoftwareSerial.h>

int bluetoothTx = 2; //Puerto de salida de data
int bluetoothRx = 3; //Puerto de entrada de data

String msg; //Mensaje completo enviado
char cmd;

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

void setup()
{
  Serial.begin(9600);  // El monitor del serial empieza en 9600

  bluetooth.begin(115200);  // El modulo Bluetooth comienza por defecto en 115200bps
  bluetooth.print("$");  // Printea 3 veces individualmente
  bluetooth.print("$");
  bluetooth.print("$");  // Entra al modo de comandos
  delay(100);  // Delay para enviar al serial el String CMD
  bluetooth.println("U,9600,N");  // Se cambia en la informacion del modulo el serial del bluetooth
  //Ya que puede ser rapido para algunos tipos de conexion nuevos
  bluetooth.begin(9600);  // Comienza el serial del Bluetooth en 9600

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  if (bluetooth.available()) {// Si el bluetooth envia data
    if (msg.length() < 4) {
      // Imprime en el monitor serial los caracteres enviados uno por uno
      //Serial.print((char)bluetooth.read());
      cmd = (char)bluetooth.read();
      msg += cmd;
      Serial.println("/" + msg + ":" + cmd);
    } else {
      if (msg == "VIBF") {
        Serial.println("Vibracion frontal");
        digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
        delay(1000);                       // wait for a second
        digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
        delay(1000);
      }
    }
  }

  /*
    if(Serial.available())  // If stuff was typed in the serial monitor
    {
    // Send any characters the Serial monitor prints to the bluetooth
    bluetooth.print((char)Serial.read());
    bluetooth.print(" serial");
    }*/
}

