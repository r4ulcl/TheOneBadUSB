#include "FingerprintUSBHost.h"
#include "HID-Project.h"

const int pinLed = LED_BUILTIN;
const int pinButton = 2;

char convert[4] = "000"; // do not change this
String os;


//write each letter with ALT+KEYPAD
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
    if (a == '2') {
      Keyboard.press(KEYPAD_2);
      Keyboard.release(KEYPAD_2);

    }
    if (a == '3') {
      Keyboard.press(KEYPAD_3);
      Keyboard.release(KEYPAD_3);

    }
    if (a == '4') {
      Keyboard.press(KEYPAD_4);
      Keyboard.release(KEYPAD_4);

    }
    if (a == '5') {
      Keyboard.press(KEYPAD_5);
      Keyboard.release(KEYPAD_5);

    }
    if (a == '6') {
      Keyboard.press(KEYPAD_6);
      Keyboard.release(KEYPAD_6);

    }
    if (a == '7') {
      Keyboard.press(KEYPAD_7);
      Keyboard.release(KEYPAD_7);

    }
    if (a == '8') {
      Keyboard.press(KEYPAD_8);
      Keyboard.release(KEYPAD_8);

    }
    if (a == '9') {
      Keyboard.press(KEYPAD_9);
      Keyboard.release(KEYPAD_9);

    }
    if (a == '0') {
      Keyboard.press(KEYPAD_0);
      Keyboard.release(KEYPAD_0);

    }

    //delay(50);
  }

  Keyboard.releaseAll();


}

//Write each letter with CTRL+SHIFT+'u' + unicode
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
    if (a == '2') {
      Keyboard.print("2");
    }
    if (a == '3') {
      Keyboard.print("3");
    }
    if (a == '4') {
      Keyboard.print("4");
    }
    if (a == '5') {
      Keyboard.print("5");
    }
    if (a == '6') {
      Keyboard.print("6");
    }
    if (a == '7') {
      Keyboard.print("7");
    }
    if (a == '8') {
      Keyboard.print("8");
    }
    if (a == '9') {
      Keyboard.print("9");
    }
    if (a == '0') {
      Keyboard.print("0");
    }
    if (a == 'A') {
      Keyboard.print("a");
    }
    if (a == 'B') {
      Keyboard.print("b");
    }
    if (a == 'C') {
      Keyboard.print("c");
    }
    if (a == 'D') {
      Keyboard.print("d");
    }
    if (a == 'E') {
      Keyboard.print("e");
    }
    if (a == 'F') {
      Keyboard.print("f");
    }


    //delay(50);
  }

  Keyboard.press(KEY_RETURN);       // Press the Enter key.
  delay(100);                       // Wait for the computer to register the press.
  Keyboard.releaseAll();            // Release the Enter key.

  //delay(100);
}


//Write each letter with CTRL+GUI + 'u' + unicode
void writeLetterMacOS(char *string)
{
  //CTRL+CMD+space to bring up the characters popover.
  //https://apple.stackexchange.com/questions/183045/how-can-i-type-unicode-characters-without-using-the-mouse

  int count, length;
  length = strlen(string);


  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press(KEY_SPACE);

  delay(300);

  Keyboard.releaseAll();

  //Keyboard.print("u+"); //english keyboard
  Keyboard.print("u"); //spanish keyboard
  Keyboard.press(KEYPAD_ADD);
  Keyboard.releaseAll();


  for (count = 0 ; count < length ; count++)
  {
    char a = string[count];
    if (a == '1') {
      Keyboard.print("1");
    }
    if (a == '2') {
      Keyboard.print("2");
    }
    if (a == '3') {
      Keyboard.print("3");
    }
    if (a == '4') {
      Keyboard.print("4");
    }
    if (a == '5') {
      Keyboard.print("5");
    }
    if (a == '6') {
      Keyboard.print("6");
    }
    if (a == '7') {
      Keyboard.print("7");
    }
    if (a == '8') {
      Keyboard.print("8");
    }
    if (a == '9') {
      Keyboard.print("9");
    }
    if (a == '0') {
      Keyboard.print("0");
    }
    if (a == 'A') {
      Keyboard.print("a");
    }
    if (a == 'B') {
      Keyboard.print("b");
    }
    if (a == 'C') {
      Keyboard.print("c");
    }
    if (a == 'D') {
      Keyboard.print("d");
    }
    if (a == 'E') {
      Keyboard.print("e");
    }
    if (a == 'F') {
      Keyboard.print("f");
    }


  }

  delay(300);

  Keyboard.press(KEY_DOWN_ARROW);       // Press the Down arrow key.
  delay(50);                       // Wait for the computer to register the press.
  Keyboard.press(KEY_RETURN);       // Press the Enter key.
  delay(50);
  Keyboard.releaseAll();            // Release the Enter key.

  delay(1000);
}

//char to ascii (Windows)
char* ascii_convert(char string)
{
  if (string == ' ') return "32";
  if (string == '!') return "33";
  if (string == '\"') return "34";
  if (string == '#') return "35";
  if (string == '$') return "36";
  if (string == '%') return "37";
  if (string == '&') return "38";
  if (string == '\'') return "39";
  if (string == '(') return "40";
  if (string == ')') return "41";
  if (string == '*') return "42";
  if (string == '+') return "43";
  if (string == ',') return "44";
  if (string == '-') return "45";
  if (string == '.') return "46";
  if (string == '/') return "47";
  if (string == '0') return "48";
  if (string == '1') return "49";
  if (string == '2') return "50";
  if (string == '3') return "51";
  if (string == '4') return "52";
  if (string == '5') return "53";
  if (string == '6') return "54";
  if (string == '7') return "55";
  if (string == '8') return "56";
  if (string == '9') return "57";
  if (string == ':') return "58";
  if (string == ';') return "59";
  if (string == '<') return "60";
  if (string == '=') return "61";
  if (string == '>') return "62";
  if (string == '?') return "63";
  if (string == '@') return "64";
  if (string == 'A') return "65";
  if (string == 'B') return "66";
  if (string == 'C') return "67";
  if (string == 'D') return "68";
  if (string == 'E') return "69";
  if (string == 'F') return "70";
  if (string == 'G') return "71";
  if (string == 'H') return "72";
  if (string == 'I') return "73";
  if (string == 'J') return "74";
  if (string == 'K') return "75";
  if (string == 'L') return "76";
  if (string == 'M') return "77";
  if (string == 'N') return "78";
  if (string == 'O') return "79";
  if (string == 'P') return "80";
  if (string == 'Q') return "81";
  if (string == 'R') return "82";
  if (string == 'S') return "83";
  if (string == 'T') return "84";
  if (string == 'U') return "85";
  if (string == 'V') return "86";
  if (string == 'W') return "87";
  if (string == 'X') return "88";
  if (string == 'Y') return "89";
  if (string == 'Z') return "90";
  if (string == '[') return "91";
  if (string == '\\') return "92";
  if (string == ']') return "93";
  if (string == '^') return "94";
  if (string == '_') return "95";
  if (string == '`') return "96";
  if (string == 'a') return "97";
  if (string == 'b') return "98";
  if (string == 'c') return "99";
  if (string == 'd') return "100";
  if (string == 'e') return "101";
  if (string == 'f') return "102";
  if (string == 'g') return "103";
  if (string == 'h') return "104";
  if (string == 'i') return "105";
  if (string == 'j') return "106";
  if (string == 'k') return "107";
  if (string == 'l') return "108";
  if (string == 'm') return "109";
  if (string == 'n') return "110";
  if (string == 'o') return "111";
  if (string == 'p') return "112";
  if (string == 'q') return "113";
  if (string == 'r') return "114";
  if (string == 's') return "115";
  if (string == 't') return "116";
  if (string == 'u') return "117";
  if (string == 'v') return "118";
  if (string == 'w') return "119";
  if (string == 'x') return "120";
  if (string == 'y') return "121";
  if (string == 'z') return "122";
  if (string == '{') return "123";
  if (string == '|') return "124";
  if (string == '}') return "125";
  if (string == '~') return "126";
  Keyboard.print(string);
  return "000";
}


//char to unicode (Linux + MacOS)
char* unicode_convert(char string)
{
  if (string == ' ') return "20";
  if (string == '!') return "21";
  if (string == '\"') return "22";
  if (string == '#') return "23";
  if (string == '$') return "24";
  if (string == '%') return "25";
  if (string == '&') return "26";
  if (string == '\'') return "27";
  if (string == '(') return "28";
  if (string == ')') return "29";
  if (string == '*') return "2A";
  if (string == '+') return "2B";
  if (string == ',') return "2C";
  if (string == '-') return "2D";
  if (string == '.') return "2E";
  if (string == '/') return "2F";


  if (string == '0') return "30";
  if (string == '1') return "31";
  if (string == '2') return "32";
  if (string == '3') return "33";
  if (string == '4') return "34";
  if (string == '5') return "35";
  if (string == '6') return "36";
  if (string == '7') return "37";
  if (string == '8') return "38";
  if (string == '9') return "39";

  if (string == ':') return "3A";
  if (string == ';') return "3B";
  if (string == '<') return "3C";
  if (string == '=') return "3D";
  if (string == '>') return "3E";
  if (string == '?') return "3F";
  if (string == '@') return "40";

  if (string == 'A') return "41";
  if (string == 'B') return "42";
  if (string == 'C') return "43";
  if (string == 'D') return "44";
  if (string == 'E') return "45";
  if (string == 'F') return "46";
  if (string == 'G') return "47";
  if (string == 'H') return "48";
  if (string == 'I') return "49";
  if (string == 'J') return "4A";
  if (string == 'K') return "4B";
  if (string == 'L') return "4C";
  if (string == 'M') return "4D";
  if (string == 'N') return "4E";
  if (string == 'O') return "4F";
  if (string == 'P') return "50";
  if (string == 'Q') return "51";
  if (string == 'R') return "52";
  if (string == 'S') return "53";
  if (string == 'T') return "54";
  if (string == 'U') return "55";
  if (string == 'V') return "56";
  if (string == 'W') return "57";
  if (string == 'X') return "58";
  if (string == 'Y') return "59";
  if (string == 'Z') return "5A";

  if (string == '[') return "5B";
  if (string == '\\') return "5C";
  if (string == ']') return "5D";
  if (string == '^') return "5E";
  if (string == '_') return "5F";
  if (string == '`') return "60";


  if (string == 'a') return "61";
  if (string == 'b') return "62";
  if (string == 'c') return "63";
  if (string == 'd') return "64";
  if (string == 'e') return "65";
  if (string == 'f') return "66";
  if (string == 'g') return "67";
  if (string == 'h') return "68";
  if (string == 'i') return "69";
  if (string == 'j') return "6A";
  if (string == 'k') return "6B";
  if (string == 'l') return "6C";
  if (string == 'm') return "6D";
  if (string == 'n') return "6E";
  if (string == 'o') return "6F";
  if (string == 'p') return "70";
  if (string == 'q') return "71";
  if (string == 'r') return "72";
  if (string == 's') return "73";
  if (string == 't') return "74";
  if (string == 'u') return "75";
  if (string == 'v') return "76";
  if (string == 'w') return "77";
  if (string == 'x') return "78";
  if (string == 'y') return "79";
  if (string == 'z') return "7A";


  if (string == '{') return "7B";
  if (string == '|') return "7C";
  if (string == '}') return "7D";
  if (string == '~') return "7E";

  Keyboard.print(string);
  return "000";
}


//write a line in any keyboard mode
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

//write a line in any language mode (qwerty only)
void writeLineLinux(char *string)
{
  int count, length;
  length = strlen(string);
  for (count = 0 ; count < length ; count++)
  {
    char a = string[count];
    writeLetterLinux(unicode_convert(a));
  }
}

//write a line in any language mode (qwerty only)
void writeLineMacOS(char *string) {
  //
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press(KEY_SPACE);

  delay(300);

  Keyboard.releaseAll();

  int count, length;
  length = strlen(string);
  for (count = 0 ; count < length ; count++)
  {
    char a = string[count];
    writeLetterMacOS(unicode_convert(a));
  }
}

//Payload to exec in terminal
void execWindows(char *string)
{
  Keyboard.press(KEY_LEFT_GUI);     // Press and hold the Windows key.
  delay(200);                       // Wait for the computer to register the press.
  Keyboard.releaseAll();            // Release both of the above keys.

  delay(1200);                     // Wait for the Windows Run Dialog to open.
  writeLineWindows("run");           // Type "run".
  delay(200);                      // Wait for the Windows Run Dialog to open.

  Keyboard.press(KEY_RIGHT_ARROW); // Press right because enter alone doesnt work, idk
  delay(400);
  Keyboard.releaseAll();
  Keyboard.press(KEY_RETURN);       // Press the Enter key.
  delay(100);                       // Wait for the computer to register the press.
  Keyboard.releaseAll();            // Release the Enter key.
  delay(500);                       // Wait for the computer to register the press.

  writeLineWindows(string);

  Keyboard.press(KEY_RETURN);       // Press the Enter key.
  delay(100);                       // Wait for the computer to register the press.
  Keyboard.releaseAll();            // Release the Enter key.

}

//Payload to exec in Bash (ubuntu)
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

}

//Payload to exec in terminal MacOS
void execMacOS(char *string) {
  /*
    GUI SPACE
    DELAY 500
    STRING terminal
    DELAY 500
    ENTER
  */
  
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

//Setup the USB
void setup() {
  pinMode(pinLed, OUTPUT);
  pinMode(pinButton, INPUT_PULLUP);

  // Sends a clean report to the host. This is important on any Arduino type.
  BootKeyboard.begin();

  Keyboard.begin();

  delay(1000); // Take a moment to let things settle

  // Get OS
  FingerprintUSBHost.guessHostOS(os); 
  //String stuff = "I think the Host OS is " + os;

}


void loop() {
  delay(1000);

  // LED ON.
  digitalWrite(pinLed, HIGH);


  if (os == "Windows") {
    // Get block Number status and activate if needed
    if (BootKeyboard.getLeds() & LED_NUM_LOCK) {
      //Keyboard.println(LED_NUM_LOCK);
    } else {
      Keyboard.press(KEY_NUM_LOCK);
      Keyboard.releaseAll();
    }

    execWindows("powershell.exe ipconfig /all ; sleep 60 ");
    //writeLineWindows("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890-=;'./<>;'<>!@#$%^&*()_+");
  } else if (os == "Linux") {
    execLinux("hostname ; ip a");
    //writeLineLinux("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890-=;'./<>;'<>!@#$%^&*()_+");
  } else { //mac
    execMacOS("hostname ; ipconfig ; sleep 60 ; exit");
    //writeLineMacOS("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890-=;'./<>;'<>!@#$%^&*()_+");
  }


  digitalWrite(pinLed, LOW); //turn off led

  delay(10000);


}
