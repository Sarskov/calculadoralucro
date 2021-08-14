#include <Servo.h>
#include <AFMotor.h>

#define LINE_BUFFER_LENGTH 512

char step = MICROSTEP ;

// Posiçoes do motor serva para cima e para baixo::
const int penZUp = 95;
const int penZDown = 83;

// Servo on PWN pin 10 ( Nao entendi direito mas acho q o servo esta conectado na porta 10)
const int penServoPin =10;

// Should be right for DVD steppers, but is not too important here
const int stepsPerRevolution = 48;

//Criando um objeto para controlar o servo motor 
Servo penServo;

//Inicializando os motores de passo para as cordenadas z e y usando o os pinos do arduino com o l293d ponte h
AF_Stepper myStepperY(stepsPerRevolution,1);
AF_Stepper myStepperX(stepsPerRevolution,2);

// Estruturas e variaveis globais 
struct point {
  float x;
  float y;
  float z;
};

// Current position of plothead (nao consegui traduzir de cabeça
struct point actuatorPos;

// Configuracoes de desenho, should be OK
float StepInc = 1;
int StepDelay = 0;
int LineDelay =0;
int penDelay = 50;

// Motor steps to go 1 millimeter.
// Use test sketch to go 100 steps. Measure the lenght of line 
// Calcule os passos por minuto e coloque aqui
float StepsPerMillimeterX = 100.0;
float StepsPerMillimeterY = 100.0;

// Drawing robot limits, in mm
// Ok to start with. could go up to 50 mm if calibrated well.
float Xmin = 0;
float Xmax = 40;
float Ymin = 0;
float Ymax = 40;
float Zmin = 0;
float Zmax = 1;

float Xpos = Xmin;
float Ypos = Ymin;
float Zpos = Zmax;

// Set to true to get debug output
boolean verbose = false;

//Needs to unterpret 
// G1 for mooving
// G4 P300 (wait 150ms)
// M300 S30 (pen down)
// M300 S50 (pen up)
// discard anything with a (
// Discard any other command!


// Incializacoes do void setup()

void setup() {
  // setup 

  Serial.begin( 9600 );

  penServo.attach(penServoPin);
  penServo.write(penZUp);
  delay(100);

  // Decrease if necessary 
  myStepperX.setSpeed(600);

  myStepperY.setSpeed(600);


  //Set e move to initial default position
  // TBD

  //Notifications!!!
  Serial.println("Mini CNC caseira");
  Serial.print("X range is from ");
  Serial.print(Xmin);
  Serial.print(" to ");
  Serial.print(Xmax);
  Serial.println(" mm.");
  Serial.print("Y range is from ");
  Serial.print(Ymin);
  Serial.print(" to ");
  Serial.print(Ymax);
  Serial.println(" mm.");
  
  
}


// Void loop() Main loop


void loop()
{

  delay(100);
  char line[ LINE_BUFFER_LENGTH ];
  char c;
  int lineIndex;
  bool lineIsComment, lineSemiColon;

  lineIndex = 0;
  lineSemiColon = false;
  lineIsComment = false;

  while (1) {

    // Serial reception - Mostly from Grbl added semicolon suport
    while (Serial.available()>0 ) {
      c = Serial.read();
      if ((c == '\n') || (c == '\r') ) {
        if (lineIndex > 0 ) {
          line[ lineIndex ] = '\0';
          if (verbose) {
            Serial.print("Received : ");
            Serial.println( line );
          }
          processIncomingLine( line, lineIndex );
          lineIndex = 0;
        }
        else {
          //Empty ir comment line. skip block.
        }
        lineIsComment = false;
        lineSemiColon = false;
        Serial.println("ok");
    }
    else {
      if ( (lineIsComment) || (lineSemiColon) ) {
        if ( c == ')') lineIsComment = false;
      }
      else {
        if (c <= ' ' ) {
        }
        else if (c == '/') {
        }
        else if (c == '(') {
          lineIsComment = true;
        }
        else if ( c == ';' ) {
          lineSemiColon = true;
        }
        else if ( lineIndex >= LINE_BUFFER_LENGTH-1 ) {
          Serial.println("ERROR - lineBuffer overflow");
          lineIsComment = false;
          lineSemiColon = false;
        }
        else if ( c >= 'a' && c <= 'z' ) {
          line[ lineIndex++ ] = c-'a'+'A';
        }
        else {
          line[ lineIndex++ ] = c;
        }
      } 
     }
    }
   }
  }


void processIncomingLine( char* line, int charNB ){
  int currentIndex = 0;
  char buffer[ 64 ];
  struct point newPos;

  newPos.x = 0.0;
  newPos.y = 0.0;


  while( currentIndex < charNB ) {
    switch ( line[ currentIndex++ ] ) {
    case 'U':
      penUp();
      break;
    case 'D':
      penDown();
      break;
    case 'G':
      buffer[0] = line[ currentIndex++ ];
      //adead
      // adade
      buffer[1] = '\0';

    switch ( atoi( buffer ) ) {
    case 0:
    case 1:
    char* indexX = strchr ( line+currentIndex, 'X' );
    char* indexY = strchr ( line+currentIndex, 'Y' );
    if ( indexY <=0 ) {
      newPos.x = atof( indexX + 1);
      newPos.y = actuatorPos.y;
    }
    else if ( indexX <= 0 ) {
      newPos.y = atof ( indexY + 1);
      newPos.x = actuatorPos.x;
    }
    else {
      newPos.y = atof( indexY + 1);
      indexY = '\0';
      newPos.x = atof( indexX + 1);
    }
    drawLine(newPos.x, newPos.y );
    actuatorPos.x = newPos.x;
    actuatorPos.y - newPos.y;
    break;
    }
    break;
  case 'M':
    buffer[0] = line[ currentIndex++];
    buffer[1] = line[ currentIndex++];
    buffer[2] = line[ currentIndex++];
    buffer[3] = line[ currentIndex++];
    switch ( atoi( buffer ) ){
      case 300:
        {
          char* indexS = strchr( line+currentIndex, 'S' );
          float Spos = atof( indexS + 1);
          //
          if (Spos == 30) {
            penDown();
          }
          if (Spos == 50) {
            penUp();
          }
          break;
        }
    
     case 114:
      Serial.print("Absolute position: x = " );
      Serial.print(actuatorPos.x);
      Serial.print("  - Y = ");
      Serial.println(actuatorPos.y);
      break;
    default:
      Serial.print("command not reconized : M ");
      Serial.println( buffer );
     }
      
    }
  }
}


void drawLine(float x1, float y1) {
  if (verbose)
  {
    Serial.print("fx1,fy1: ");
    Serial.print(x1);
    Serial.print(",");
    Serial.print(y1);
    Serial.println("");
  }

  if (x1 >= Xmax){
    x1 = Xmax;
  }
  if (x1 <= Xmin){
    x1 = Xmin;
  }
  if (y1 >= Ymax) {
    y1 = Ymax;
  }
  if (y1 <= Ymin) {
    y1 = Ymin;
  }

  if (verbose)
  {
    Serial.print("Xpos, Ypos: ");
    Serial.print(Xpos);
    Serial.print(",");
    Serial.print(Ypos);
    Serial.println("");
  }
  if (verbose)
  {
    Serial.print("x1, y1: ");
    Serial.print(x1);
    Serial.print(",");
    Serial.print(y1);
    Serial.println("");
  }


  x1 = (int)(x1*StepsPerMillimeterX);
  y1 = (int)(y1*StepsPerMillimeterY);
  float x0 = Xpos;
  float y0 = Ypos;


  long dx = abs(x1-x0);
  long dy = abs(y1-y0);
  int sx = x0<x1 ? StepInc : -StepInc;
  int sy = y0<y1 ? StepInc : -StepInc;

  long i;
  long over = 0;


  if (dx > dy) {
    for (i=0; i<dx; ++i) {
      myStepperX.onestep(sx,SPE);
      over+=dy;
      if (over>=dx) {
        over-=dx;
        myStepperY.onestep(sy,SPE);
      }
      delay(StepDelay);
    }
  }
  else {
    for (i=0; i<dy; ++i) {
      myStepperY.onestep(sy,SPE);
      over+=dx;
      if (over>=dy) {
        over-=dy;
        myStepperX.onestep(sx,SPE);
      }
      delay(StepDelay);
    }
  }

  if (verbose)
  {
    Serial.print("dx, dy:");
    Serial.print(dx);
    Serial.print(",");
    Serial.print(dy);
    Serial.println("");
  }

  if (verbose)
  {
    Serial.print("Going to (");
    Serial.print(x0);
    Serial.print(",");
    Serial.print(y0);
    Serial.println(")");
  }

  //Delay before any lines are submited
  delay(LineDelay);
  // Update the positions 
  Xpos = x1;
  Ypos = y1;
  
}



//Raise pen

void penUp() {
  penServo.write(penZUp);
  delay(penDelay);
  Zpos=Zmax;
  digitalWrite(15, LOW);
    digitalWrite(16, HIGH);
  if (verbose) {
    Serial.println("Pen Up!");
  }
}

// Lowers pen
void penDown() {
  penServo.write(penZDown);
  delay(penDelay);
  Zpos=Zmin;
  digitalWrite(15, HIGH);
    digitalWrite(16, LOW);
  if (verbose) {
    Serial.println("Pen down");
  }
}









   
