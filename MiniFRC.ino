//instructions for downloading and installing libraries can be found here: https://www.instructables.com/id/Downloading-All-the-Software-Youll-Need-for-MiniFR/
#include <SoftwareSerial.h>         //this library is part of Arduino by default
#include <AFMotor.h>                //you must download and install this library: https://drive.google.com/file/d/1zsMywqJjvzgMBoVZyrYly-2hXePFXFzw/view?usp=sharing

/* <==============================================================>
 *  You will need to change the following variables depending on what
 *  analog pins on your motor shield you are using, which motor goes to
 *  which port, and if your drive logic is flipped. */

//change A0 and A1 to match whatever pins you are useing for your bluetooth chip
SoftwareSerial bluetooth(A0, A1); //RX,TX

AF_DCMotor mLeft(1);
AF_DCMotor mRight(2);
AF_DCMotor launcher(3);

int f = 0;
int s = 0;
int r = 0;
int l = 0;
int e = 0;

// In setup, we tell bluetooth communication to start and set all of our motors to not move
void setup() {
  bluetooth.begin(9600);
  launcher.run(FORWARD);
}

void loop() {
  while(bluetooth.available() > 0) {
    switch(bluetooth.read()) {
      case 'w': 
      case 'S':
        f++;
        break;
      case 'a':
      case 'D':
        s--;
        break;
      case 's':
      case 'W':
        f--;
        break;
      case 'd':
      case 'A':
        s++;
        break;
      case 'x':
        f = 0;
        s = 0;
        break;
      case 'e':
        e = e == 1 ? 0 : 1;
        break;
    }
    r = range(f - s, -1, 1);
    l = range(f + s, -1, 1);
    mRight.run((r >= 0) ? FORWARD : BACKWARD);
    mRight.setSpeed(abs(r*255));
    mLeft.run((l <= 0) ? FORWARD : BACKWARD);
    mLeft.setSpeed(abs(l*255));
    launcher.setSpeed(abs(e*255));
  }
}
double range(double n, double mn, double mx) {
  if(n < mn) return mn;
  else if(n > mx) return mx;
  else return n;
}

