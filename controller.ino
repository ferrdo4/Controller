#include <PS2KeyAdvanced.h>

/* Keyboard constants  Change to suit your Arduino
   define pins used for data and clock from keyboard */
#define DATAPIN 3
#define IRQPIN  2

uint16_t c;

//P1
bool IS_LEFT_1 = false;
bool IS_RIGHT_1 = false;
bool IS_UP_1 = false;
bool IS_DOWN_1 = false;
bool IS_FIRE_1 = false;

bool IS_LEFT_O_1 = true;
bool IS_RIGHT_O_1 = true;
bool IS_UP_O_1 = true;
bool IS_DOWN_O_1 = true;
bool IS_FIRE_O_1 = true;
uint8_t AX = 0;
uint8_t AY = 0;

const int J1_UP = 52;
const int J1_DOWN = 50;
const int J1_LEFT = 48;
const int J1_RIGHT = 46;
const int J1_FIRE = 44;
const int J1_AY = A14;
const int J1_AX = A15;

int T1_UP = -1;
int T1_DOWN = -1;
int T1_LEFT = -1;
int T1_RIGHT = -1;
int T1_FIRE = -1;

// P2
bool IS_LEFT_2 = false;
bool IS_RIGHT_2 = false;
bool IS_UP_2 = false;
bool IS_DOWN_2 = false;
bool IS_FIRE_2 = false;

bool IS_LEFT_O_2 = true;
bool IS_RIGHT_O_2 = true;
bool IS_UP_O_2 = true;
bool IS_DOWN_O_2 = true;
bool IS_FIRE_O_2 = true;

const int J2_UP = 13;
const int J2_DOWN = 12;
const int J2_LEFT = 11;
const int J2_RIGHT = 10;
const int J2_FIRE = 9;

int T2_UP = -1;
int T2_DOWN = -1;
int T2_LEFT = -1;
int T2_RIGHT = -1;
int T2_FIRE = -1;

//ANLG
bool IS_ANLG = false;
bool IS_ANLG_UP = false;
bool IS_ANGL_DOWN = false;
bool IS_ANALG_LEFT = false;
bool IS_ANALG_RIGHT = false;

bool IS_ANLG_O = false;
bool IS_ANLG_UP_O = false;
bool IS_ANGL_DOWN_O = false;
bool IS_ANALG_LEFT_O = false;
bool IS_ANALG_RIGHT_O = false;


PS2KeyAdvanced keyboard;

void setup( )
{
  // Configure the keyboard library
  keyboard.begin(DATAPIN, IRQPIN);
  keyboard.setNoRepeat(1);
  Serial.begin(115200);
  Serial.println("PS2 Advanced Key Simple Test:");

  T1_UP = J1_UP;
  T1_DOWN = J1_DOWN;
  T1_LEFT = J1_LEFT;
  T1_RIGHT = J1_RIGHT;
  T1_FIRE = J1_FIRE;

  T2_UP = J2_UP;
  T2_DOWN = J2_DOWN;
  T2_LEFT = J2_LEFT;
  T2_RIGHT = J2_RIGHT;
  T2_FIRE = J2_FIRE;

  pinMode(J1_UP, INPUT);
  pinMode(J1_DOWN, INPUT);
  pinMode(J1_LEFT, INPUT);
  pinMode(J1_RIGHT, INPUT);
  pinMode(J1_FIRE, INPUT);

  pinMode(J2_UP, INPUT);
  pinMode(J2_DOWN, INPUT);
  pinMode(J2_LEFT, INPUT);
  pinMode(J2_RIGHT, INPUT);
  pinMode(J2_FIRE, INPUT);

  pinMode(J1_AX, OUTPUT);
  pinMode(J1_AY, OUTPUT);
}

void updateStates()
{
  if (keyboard.available( ))
  {
    // read the next key
    c = keyboard.read( );

    uint8_t stat = c >> 8;
    uint8_t code = c & 0xFF;

    Serial.print("  Stat ");
    Serial.println(stat, HEX);

    Serial.print("  Code ");
    Serial.println(code, HEX);

    if (stat == 0 || stat == 0x1 || stat == 0x20 || stat == 0x21 || stat == 0x40 || stat == 0x41 || stat == 0x61)
    {
      Serial.println("press");

      //  P1
      if (code == 'a' || code == 'A' )
      {
        Serial.println("[LEFT]");
        IS_LEFT_1 = true;
      }
      if (code == 'd' || code == 'D')
      {
        Serial.println("[RIGHT]");
        IS_RIGHT_1 = true;
      }
      if (code == 'w' || code == 'W')
      {
        Serial.println("[UP]");
        IS_UP_1 = true;
      }
      if (code == 's' || code == 'S' || code == 'x' || code == 'X')
      {
        Serial.println("[DOWN]");
        IS_DOWN_1 = true;
      }
      if (code == PS2_KEY_L_CTRL || code == PS2_KEY_L_SHIFT)
      {
        Serial.println("[FIRE!]");
        IS_FIRE_1 = true;
      }

      //  P2
      if (code == PS2_KEY_L_ARROW)
      {
        Serial.println("[LEFT]");
        IS_LEFT_2 = true;
      }
      if (code == PS2_KEY_R_ARROW)
      {
        Serial.println("[RIGHT]");
        IS_RIGHT_2 = true;
      }
      if (code == PS2_KEY_UP_ARROW)
      {
        Serial.println("[UP]");
        IS_UP_2 = true;
      }
      if (code == PS2_KEY_DN_ARROW)
      {
        Serial.println("[DOWN]");
        IS_DOWN_2 = true;
      }
      if (code == PS2_KEY_R_CTRL || code == PS2_KEY_ENTER)
      {
        Serial.println("[FIRE!]");
        IS_FIRE_2 = true;
      }

      // ANALG
      if (code == PS2_KEY_KP4)
      {
        if (AX > 0)
          AX -= 5;
        Serial.print("[AX-]");
        Serial.println(AX, DEC);
      }
      if (code == PS2_KEY_KP6)
      {
        if (AX < 255)
        AX += 5;
        Serial.print("[AX+]");
        Serial.println(AX, DEC);
      }
      if (code == PS2_KEY_KP2)
      {
        if (AY > 0)
          AY -= 5;
        Serial.print("[AY-]");
        Serial.println(AY, DEC);
      }
      if (code == PS2_KEY_KP8)
      {
        if (AY < 255)
          AY += 5;
        Serial.print("[AY+]");
        Serial.println(AY, DEC);
      }
    }

    if (stat == 0x81 || stat == 0x80 || stat == 0xA0 || stat == 0xA1 || stat == 0xC0 || stat == 0xC1)
    {
      Serial.println("released");

      //  P1
      if (code == 'a' || code == 'A')
      {
        Serial.println("[left]");
        IS_LEFT_1 = false;
      }
      if (code == 'd' || code == 'D')
      {
        Serial.println("[right]");
        IS_RIGHT_1 = false;
      }
      if (code == 'w' || code == 'W')
      {
        Serial.println("[up]");
        IS_UP_1 = false;
      }
      if (code == 's' || code == 'S' || code == 'x' || code == 'X')
      {
        Serial.println("[down]");
        IS_DOWN_1 = false;
      }
      if (code == PS2_KEY_L_CTRL || code == PS2_KEY_L_SHIFT)
      {
        Serial.println("[fire!]");
        IS_FIRE_1 = false;
      }

      //  P2
      if (code == PS2_KEY_L_ARROW)
      {
        Serial.println("[left]");
        IS_LEFT_2 = false;
      }
      if (code == PS2_KEY_R_ARROW)
      {
        Serial.println("[right]");
        IS_RIGHT_2 = false;
      }
      if (code == PS2_KEY_UP_ARROW)
      {
        Serial.println("[up]");
        IS_UP_2 = false;
      }
      if (code == PS2_KEY_DN_ARROW)
      {
        Serial.println("[down]");
        IS_DOWN_2 = false;
      }
      if (code == PS2_KEY_R_CTRL || code == PS2_KEY_ENTER)
      {
        Serial.println("[fire!]");
        IS_FIRE_2 = false;
      }
    }
  }
}

void updateJoy()
{
  //  P1
  if (IS_LEFT_1 != IS_LEFT_O_1)
  {
    if (IS_LEFT_1)
    {
      pinMode(T1_LEFT, OUTPUT);
      digitalWrite(T1_LEFT, LOW);
      Serial.println("[L]");
    }
    else
    {
      pinMode(T1_LEFT, INPUT);
      Serial.println("[l]");
    }
    Serial.println("[set]");
    IS_LEFT_O_1 = IS_LEFT_1;
  }

  if (IS_RIGHT_1 != IS_RIGHT_O_1)
  {
    if (IS_RIGHT_1)
    {
      pinMode(T1_RIGHT, OUTPUT);
      digitalWrite(T1_RIGHT, LOW);
      Serial.println("[R]");
    }
    else
    {
      pinMode(T1_RIGHT, INPUT);
      Serial.println("[r]");
    }
    IS_RIGHT_O_1 = IS_RIGHT_1;
  }

  if (IS_UP_1 != IS_UP_O_1)
  {
    if (IS_UP_1)
    {
      pinMode(T1_UP, OUTPUT);
      digitalWrite(T1_UP, LOW);
      Serial.println("[R]");
    }
    else
    {
      pinMode(T1_UP, INPUT);
      Serial.println("[r]");
    }
    IS_UP_O_1 = IS_UP_1;
  }

  if (IS_DOWN_1 != IS_DOWN_O_1)
  {
    if (IS_DOWN_1)
    {
      pinMode(T1_DOWN, OUTPUT);
      digitalWrite(T1_DOWN, LOW);
      Serial.println("[R]");
    }
    else
    {
      pinMode(T1_DOWN, INPUT);
      Serial.println("[r]");
    }
    IS_DOWN_O_1 = IS_DOWN_1;
  }

  if (IS_FIRE_1 != IS_FIRE_O_1)
  {
    if (IS_FIRE_1)
    {
      pinMode(T1_FIRE, OUTPUT);
      digitalWrite(T1_FIRE, LOW);
      Serial.println("[R]");
    }
    else
    {
      pinMode(T1_FIRE, INPUT);
      Serial.println("[r]");
    }
    IS_FIRE_O_1 = IS_FIRE_1;
  }
  
  //  P2
  if (IS_LEFT_2 != IS_LEFT_O_2)
  {
    if (IS_LEFT_2)
    {
      pinMode(T2_LEFT, OUTPUT);
      digitalWrite(T2_LEFT, LOW);
      Serial.println("[L]");
    }
    else
    {
      pinMode(T2_LEFT, INPUT);
      Serial.println("[l]");
    }
    Serial.println("[set]");
    IS_LEFT_O_2 = IS_LEFT_2;
  }

  if (IS_RIGHT_2 != IS_RIGHT_O_2)
  {
    if (IS_RIGHT_2)
    {
      pinMode(T2_RIGHT, OUTPUT);
      digitalWrite(T2_RIGHT, LOW);
      Serial.println("[R]");
    }
    else
    {
      pinMode(T2_RIGHT, INPUT);
      Serial.println("[r]");
    }
    IS_RIGHT_O_2 = IS_RIGHT_2;
  }

  if (IS_UP_2 != IS_UP_O_2)
  {
    if (IS_UP_2)
    {
      pinMode(T2_UP, OUTPUT);
      digitalWrite(T2_UP, LOW);
      Serial.println("[R]");
    }
    else
    {
      pinMode(T2_UP, INPUT);
      Serial.println("[r]");
    }
    IS_UP_O_2 = IS_UP_2;
  }

  if (IS_DOWN_2 != IS_DOWN_O_2)
  {
    if (IS_DOWN_2)
    {
      pinMode(T2_DOWN, OUTPUT);
      digitalWrite(T2_DOWN, LOW);
      Serial.println("[R]");
    }
    else
    {
      pinMode(T2_DOWN, INPUT);
      Serial.println("[r]");
    }
    IS_DOWN_O_2 = IS_DOWN_2;
  }

  if (IS_FIRE_2 != IS_FIRE_O_2)
  {
    if (IS_FIRE_2)
    {
      pinMode(T2_FIRE, OUTPUT);
      digitalWrite(T2_FIRE, LOW);
      Serial.println("[R]");
    }
    else
    {
      pinMode(T2_FIRE, INPUT);
      Serial.println("[r]");
    }
    IS_FIRE_O_2 = IS_FIRE_2;
  }
}

void loop( )
{
  updateStates();
  updateJoy();

  analogWrite(J1_AX, AX);
  analogWrite(J1_AY, AY);
}
