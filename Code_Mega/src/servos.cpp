

#include "../include/servos.h"

XL320 xl320; // object XL320

Servos servos;

void Servos::setPosXL320(uint8_t XL, int position) {
	switch (XL) {
		case 1:
			xl320.moveJoint(XL1, position);
			break;
		case 2:
			xl320.moveJoint(XL2, position);
			break;
		case 3:
			xl320.moveJoint(XL3, position);
			break;
		case 4:
			xl320.moveJoint(XL4, position);
			break;
	}
}


void Servos::init() {
	ax12a.begin(BaudRate, DirectionPin, &SERIAL_AX12A);
	SERIAL_XL320.begin(115200); // init of SERIAL_XL320 com for XL320
	xl320.begin(SERIAL_XL320); // init of XL320 object on SERIAL_XL320
	xl320.setJointSpeed(XL1, 200); // set speed of all XL320
	delay(3);
	xl320.setJointSpeed(XL2, 200);
	delay(3);
	xl320.setJointSpeed(XL3, 200);
	delay(3);
	xl320.setJointSpeed(XL4, 200);
	delay(3);
	// xl320.setJointTorque(XL4, 1023);
	delay(100);
	xl320.moveJoint(XL1, 750);
	delay(2000);
	xl320.moveJoint(XL2, 300);
	delay(2000);
	xl320.moveJoint(XL3, 825);
	delay(2000);
	xl320.moveJoint(XL4, 470);
	delay(2000);
	xl320.moveJoint(XL1, 200);
	delay(2000);
	xl320.moveJoint(XL2, 810);
	delay(2000);
}

/*
void Servos::ax12a_set(int pos) {
  ax12a.moveSpeed(AXR, pos, speedAX);
  ax12a.moveSpeed(AXL, pos, speedAX);
}

// Strategy with asserv

void Servos::packed(char arm) {
  // position la plus compacte dans le robot possible (ie : non-déployé/transfert)
  if (arm == 'R') {
    ax12a.moveSpeed(AXR, milR, speedAX);    
    xl320.moveJoint(XL3, haut3);
    delay(3);
    xl320.moveJoint(XL1, haut1);
  }
  else {
    ax12a.moveSpeed(AXL, milL, speedAX);    
    xl320.moveJoint(XL4, haut4);
    delay(3);
    xl320.moveJoint(XL2, haut2);
  }
  delay(3);
}

void Servos::pretransfer(char arm) {
  // position pré-transfert ventouse levée a 90°
  if (arm == 'R') {
    ax12a.moveSpeed(AXR, milR, speedAX);
    xl320.moveJoint(XL3, haut3+100);
    delay(3);
    xl320.moveJoint(XL1, bas1);
  }
  else {
    ax12a.moveSpeed(AXL, milL, speedAX);
    xl320.moveJoint(XL4, haut4);
    delay(3);
    xl320.moveJoint(XL2, bas2);
  }
  delay(3);
}

void Servos::topofhexa(char arm) {
  // position prise hexagone au-dessus
  if (arm == 'R') {
    ax12a.moveSpeed(AXR, milR, speedAX);
    xl320.moveJoint(XL3, bas3);
    delay(3);
    xl320.moveJoint(XL1, bas1 - 235);
  }
  else {
    ax12a.moveSpeed(AXL, milL, speedAX);
    xl320.moveJoint(XL4, bas4);
    delay(3);
    xl320.moveJoint(XL2, bas2 + 205);
  }
  delay(3);
}

void Servos::bottomhexa(char arm) {
  // position prise hexagone
  if (arm == 'R') {
    ax12a.moveSpeed(AXR, hexaR, speedAX);
    xl320.moveJoint(XL3, bas3);
    delay(3);
    xl320.moveJoint(XL1, bas1 - 235);
  }
  else {
    ax12a.moveSpeed(AXL, botL, speedAX);
    xl320.moveJoint(XL4, bas4);
    delay(3);
    xl320.moveJoint(XL2, bas2 + 205);
  }
  delay(3);
}

void Servos::topstretched(char arm) {
  // position pré-transfert ventouse baissée
  if (arm == 'R') {
    ax12a.moveSpeed(AXR, midR, speedAX);
    xl320.moveJoint(XL3, bas3);
    delay(3);
    xl320.moveJoint(XL1, bas1);
  }
  else {
    ax12a.moveSpeed(AXL, midL, speedAX);
    xl320.moveJoint(XL4, bas4);
    delay(3);
    xl320.moveJoint(XL2, bas2);
  }
  delay(3);
}

void Servos::putdown(char arm) {
  // position dépose hexagone galerie
  if (arm == 'R') {
    ax12a.moveSpeed(AXR, topR, speedAX);
    xl320.moveJoint(XL3, bas3 + 245);
    delay(3);
    xl320.moveJoint(XL1, bas1);
  }
  else {
    ax12a.moveSpeed(AXL, topL, speedAX);
    xl320.moveJoint(XL4, bas4 + 245);
    delay(3);
    xl320.moveJoint(XL2, bas2);
  }
  delay(3);
}

void Servos::vacuum(char arm, int state) {
  // function taking the arm and state you want to set the pump to
  if (arm == 'R') {
    digitalWrite(PumpR, state);
  }
  else {
    digitalWrite(PumpL, state);
  }
}

void Servos::ActionPacked() {
  packed('R');
  packed('L');
}

void Servos::ActionPreTransfer() {
  pretransfer('R');
  pretransfer('L');
}


void Servos::PriseHexagone() { // fonction en fabrication
  // pre packed already dans le setup
  // mise en place prise hexa
  // orientation

  
}
*/
