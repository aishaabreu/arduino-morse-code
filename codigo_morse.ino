// Main
int button = 7;
int led = 13;
char *morse_code;

void setup() {
  pinMode(button, INPUT_PULLUP);
  pinMode(led, OUTPUT);

  morse_code = text2morsecode(strdup("Hello World!!"));
  Serial.begin(9600);
  Serial.println(morse_code);
}

bool writing = false;
int index = 0;
int cicles = 0;

void loop() {
  if (pressed(button)) {
    index = 0;
    cicles = 0;
    if (writing) {
      writing = false;
    } else {
      writing = true;
    }
  }

  if (play_end()) {
    writing = false;
    index = 0;
    cicles = 0;
  }

  if (writing) {
    play_morse_code(led);
  } else {
    led_off(led);
  }
}

// Button
bool down = false;

bool pressed(int button) {
  if (digitalRead(button) == LOW) {
    if (!down) {
      down = true;
      return true;
    }
  } else {
    down = false;
  }
  return false;
}

// LED
float intensity = 2;
float cycle = 2;

void led_on(int led) {
  digitalWrite(led, HIGH);
  delay(intensity);
  digitalWrite(led, LOW);
  delay(cycle - intensity);
}

void led_off(int led) {
  digitalWrite(led, LOW);
  delay(cycle);
}

// Morse Code
bool play_end() {
  if (index >= strlen(morse_code)) {
    return true;
  }
  return false;
}

void play_morse_code(int led) {
  int range_on = 0;
  int range_off = 0;

  switch (morse_code[index]) {
    case '.':
      range_on = 40;
      range_off = 40;
      break;
    case '-':
      range_on = 80;
      range_off = 40;
      break;
    case ' ':
      range_on = 0;
      range_off = 120;
      break;
  }

  if (cicles < range_on) {
    led_on(led);
    cicles = cicles + 1;
  } else if (cicles < range_off) {
    led_off(led);
    cicles = cicles + 1;
  } else {
    index = index + 1;
    cicles = 0;
  }
}

char *text2morsecode(char *text) {
  char *result = strdup("");
  for (int i = 0; i < strlen(text); i++) {
    strcat(result, morse_char(text[i]));
    strcat(result, strdup(" "));
  }
  return result;
}

char *morse_char(char letter) {
  char *result = strdup(" ");
  switch (tolower(letter)) {
    case 'a':
      result = strdup(".-");
      break;
    case 'b':
      result = strdup("-...");
      break;
    case 'c':
      result = strdup("-.-.");
      break;
    case 'd':
      result = strdup("-..");
      break;
    case 'e':
      result = strdup(".");
      break;
    case 'f':
      result = strdup("..-.");
      break;
    case 'g':
      result = strdup("--.");
      break;
    case 'h':
      result = strdup("....");
      break;
    case 'i':
      result = strdup("..");
      break;
    case 'j':
      result = strdup(".---");
      break;
    case 'k':
      result = strdup("-.-");
      break;
    case 'l':
      result = strdup(".-..");
      break;
    case 'm':
      result = strdup(".-");
      break;
    case 'n':
      result = strdup("-.");
      break;
    case 'o':
      result = strdup("---");
      break;
    case 'p':
      result = strdup(".--.");
      break;
    case 'q':
      result = strdup("--.-");
      break;
    case 'r':
      result = strdup(".-.");
      break;
    case 's':
      result = strdup("...");
      break;
    case 't':
      result = strdup("-");
      break;
    case 'u':
      result = strdup("..-");
      break;
    case 'v':
      result = strdup("...-");
      break;
    case 'w':
      result = strdup(".--");
      break;
    case 'x':
      result = strdup("-..-");
      break;
    case 'y':
      result = strdup("-.--");
      break;
    case 'z':
      result = strdup("--..");
      break;
    case '1':
      result = strdup(".----");
      break;
    case '2':
      result = strdup("..---");
      break;
    case '3':
      result = strdup("...--");
      break;
    case '4':
      result = strdup("....-");
      break;
    case '5':
      result = strdup(".....");
      break;
    case '6':
      result = strdup(".....");
      break;
    case '7':
      result = strdup(".-...");
      break;
    case '8':
      result = strdup(".--..");
      break;
    case '9':
      result = strdup(".---.");
      break;
    case '0':
      result = strdup("-----");
      break;
    case '.':
      result = strdup(".-.-.-");
      break;
    case ',':
      result = strdup("--..--");
      break;
    case '?':
      result = strdup("..--..");
      break;
    case '\'':
      result = strdup(".----.");
      break;
    case '!':
      result = strdup("-.-.--");
      break;
    case '/':
      result = strdup("-..-.");
      break;
    case '(':
      result = strdup("-.--.");
      break;
    case ')':
      result = strdup("-.--.-");
      break;
    case '&':
      result = strdup(".-...");
      break;
    case ':':
      result = strdup("---...");
      break;
    case ';':
      result = strdup("-.-.-.");
      break;
    case '=':
      result = strdup("-...-");
      break;
    case '+':
      result = strdup(".-.-.");
      break;
    case '-':
      result = strdup("-....-");
      break;
    case '_':
      result = strdup("..--.-");
      break;
    case '"':
      result = strdup(".-..-.");
      break;
    case '$':
      result = strdup("...-..-");
      break;
    case '@':
      result = strdup(".--.-.");
      break;
  }
  return result;
}
