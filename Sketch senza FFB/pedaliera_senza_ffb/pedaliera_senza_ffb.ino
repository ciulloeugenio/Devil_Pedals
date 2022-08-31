#include "HX711.h"
#include <Joystick.h>

const int LOADCELL_DOUT_PIN1 = 2;
const int LOADCELL_SCK_PIN1 = 3;


long Acceleratore = 0;
long Freno = 0;
long Frizione = 0;

// Se volete calibrare il range degli assi, sostituire i seguenti valori
const long calibration_factor1 = 150;


Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  0, 0,                  // Button Count, Hat Switch Count
  false, false, false,     // X and Y, but no Z Axis
  true, true, true,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering

HX711 scale1;


void setup() {
  
  scale1.begin(LOADCELL_DOUT_PIN1, LOADCELL_SCK_PIN1);
  scale1.set_scale(calibration_factor1);
  Joystick.begin();


//decommentare eliminando i // nel prossimo valore se si vuole aprire la monitor seriale
//Serial.begin(9600);

}

const bool initAutoSendState = true;


void loop() {
    const int analog2 = analogRead(A2);
    const int analog6 = analogRead(A6);
	
	int analog2map = map(analog2, 0, 1023, 0, 4096);
	int analog6map = map(analog6, 0, 1023, 10240, 32768);
	
	const long ZonainferioreAcceleratore = analogRead(A8);
	const long ZonasuperioreAcceleratore = analogRead(A3);
	const long ZonainferioreFreno = analog2;
	const long ZonasuperioreFreno = analog6;
	const long ZonainferioreFrizione = analogRead(A7);
	const long ZonasuperioreFrizione = analogRead(A9);
	
  Acceleratore = analogRead(A0);
  Freno = scale1.get_units();
  Frizione = analogRead(A2);
  
  Joystick.setRxAxis(Acceleratore);
  Joystick.setRyAxis(Freno);
  Joystick.setRzAxis(Frizione);

  Joystick.setRxAxisRange(ZonainferioreAcceleratore, ZonasuperioreAcceleratore);
  Joystick.setRyAxisRange(ZonainferioreFreno, ZonasuperioreFreno);
  Joystick.setRzAxisRange(ZonainferioreFrizione, ZonasuperioreFrizione);
// Decommentare le seriali eliminando /* e */ alla fine dei Serial.print
/*
    Serial.print("Acceleratore : \t");
    Serial.print(Acceleratore);
    Serial.print("\t Freno: \t");
    Serial.print(Freno);
    Serial.print("\t Frizione : \t");
    Serial.print(Frizione);  
    Serial.print("\t Freno a mano: \t");
    Serial.println(Freno_a_mano);
*/
}
