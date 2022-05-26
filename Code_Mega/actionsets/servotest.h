#include "../include/goal.h"
#include "../include/goalslist.h"

#include <AX12A.h>
#include <XL320.h>

#define DirectionPin (10u) // set to TX
#define BaudRate (57600ul) // BaudRate
#define AXL (2u) // IDs of AX12A
#define AXR (1u)
#define speedAX 150 // const for speed of AX12A

#define topR 600 // 3 pos AX12A right arm
#define midR 300
#define botR 0
#define topL 600 // 3 pos AX12A left arm
#define midL 300
#define botL 0

#define XL1 1 // IDs of XL320
#define XL2 2
#define XL3 3
#define XL4 4
#define XLBroad 254
XL320 xl320; // object XL320
const char rgb[] = "rgbypcwo"; // for the LED
#define bas1 495 // pos limit right arm XL320
#define haut1 850
#define bas3 515
#define haut3 850
#define bas2 195 // pos limit left arm XL320
#define haut2 550
#define bas4 195
#define haut4 530

int mytimer = millis();

void InitServo() {
	goalsList.addGoal(new ax12a.begin(BaudRate, DirectionPin, &Serial1)); // init of Serial1 with BaudRate for AX12A
  	goalsList.addGoal(new Serial2.begin(115200)); // init of Serial2 com for XL320
  	goalsList.addGoal(new xl320.begin(Serial2)); // init of XL320 object on Serial2
  	goalsList.addGoal(new xl320.setJointSpeed(XLBroad, 200)); // set speed of all XL320
  	Packed(); // init pos of servos at beginning of match
}

void Packed() {
  	// position la plus compacte dans le robot possible (ie : non-déployé/transfert)
	goalsList.addGoal(new ax12a.moveSpeed(AXR, midR, speedAX));    
	goalsList.addGoal(new xl320.moveJoint(XL3, haut3));
	// delay(3);
	goalsList.addGoal(new xl320.moveJoint(XL1, haut1));
	// delay(3);
	goalsList.addGoal(new ax12a.moveSpeed(AXL, midL, speedAX));    
	goalsList.addGoal(new xl320.moveJoint(XL4, haut4));
	// delay(3);
	goalsList.addGoal(new xl320.moveJoint(XL2, haut2));
	// delay(3);
}

void PreTransfer() {
  	// position pré-transfert ventouse levée a 90°
    goalsList.addGoal(new ax12a.moveSpeed(AXR, midR, speedAX));
    goalsList.addGoal(new xl320.moveJoint(XL3, haut3));
    // delay(3);
    goalsList.addGoal(new xl320.moveJoint(XL1, bas1));
    // delay(3);
    goalsList.addGoal(new ax12a.moveSpeed(AXL, midL, speedAX));
    goalsList.addGoal(new xl320.moveJoint(XL4, haut4));
    // delay(3);
    goalsList.addGoal(new xl320.moveJoint(XL2, bas2));
  	// delay(3);
}

void TopOfHexa() {
  	// position prise hexagone au-dessus
    goalsList.addGoal(new ax12a.moveSpeed(AXR, midR, speedAX));
    goalsList.addGoal(new xl320.moveJoint(XL3, bas3));
    // delay(3);
    goalsList.addGoal(new xl320.moveJoint(XL1, bas1 + 205));
    // delay(3);
}

void BottomHexa() {
  	// position prise hexagone
    goalsList.addGoal(new ax12a.moveSpeed(AXR, botR, speedAX));
    goalsList.addGoal(new xl320.moveJoint(XL3, bas3));
    // delay(3);
    goalsList.addGoal(new xl320.moveJoint(XL1, bas1 + 205));
    // delay(3);
}

void TopStretched() {
  	// position pré-transfert ventouse baissée
    goalsList.addGoal(new ax12a.moveSpeed(AXR, midR, speedAX));
    goalsList.addGoal(new xl320.moveJoint(XL3, bas3));
    // delay(3);
    goalsList.addGoal(new xl320.moveJoint(XL1, bas1));
    // delay(3);
}

void PutDown() {
  // position dépose hexagone galerie
    goalsList.addGoal(new ax12a.moveSpeed(AXL, topL, speedAX));
    goalsList.addGoal(new xl320.moveJoint(XL4, bas4 + 245));
    // delay(3);
    goalsList.addGoal(new xl320.moveJoint(XL2, bas2));
    // delay(3);
}

void VacuumPump(char arm, int state) {
	if (arm == 'R') {
		goalsList.addGoal(new digitalWrite(VACUUM_PUMP_RIGHT, state));
	}
	else {
		goalsList.addGoal(new digitalWrite(VACUUM_PUMP_LEFT, state));
	}
}

void StratHexaServo() {
	// Goto pick up an hexagon
	PreTransfer();
	TopOfHexa();
	BottomHexa();
	VacuumPump('R', 1); // vacuum right arm ON
	TopOfHexa();
	TopStretched();
	PreTransfer();
	Packed();
	VacuumPump('L', 1); // vacuum left arm ON
	// Goto the galery
	VacuumPump('R', 0); // vacuum right arm OFF
	PreTransfer();
	PutDown();
	VacuumPump('L', 0); // vacuum left arm OFF
	Packed();
	// ready to go elsewhere
}

void fillGoals() {
	InitServo();
	StratHexaServo();
}
