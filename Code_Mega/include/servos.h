/**
 * \file servos.h
 * \brief XL320 + AX12-A
**/

#ifndef SERVOS_H
#define SERVOS_H

#include <Arduino.h>

#include <AX12A.h>
#include <XL320.h>

#include "pins.h"

#define DirectionPin (10u) // set to TX
#define BaudRate (57600ul) // BaudRate
#define AXL (2u) // IDs of AX12A
#define AXR (1u)
#define speedAX 150 // const for speed of AX12A

#define topR 0 // 2 pos AX12A right arm fake values
#define midR 300
#define botR 600
#define topL 600 // 2 pos AX12A left arm fake values
#define midL 300
#define botL 0

#define basR 780 // pos limit right arm AX12A
#define hexaR 760
#define milR 430
#define hautR 0
#define basL 0 // pos limit left arm AX12A
#define hexaL 20
#define milL 350
#define hautL 750

#define XL1 1 // IDs of XL320
#define XL2 2
#define XL3 3
#define XL4 4

const char rgb[] = "rgbypcwo"; // for the LED
#define bas1 550 // pos limit right arm XL320
#define haut1 220
#define bas3 525
#define haut3 825
#define bas2 195 // pos limit left arm XL320
#define haut2 550
#define bas4 840
#define haut4 470

#define PumpR 7 // Pins of pumps
#define PumpL 6

#define timen 2000


class Servos  {
public:
    void init();
    void setPosXL320(uint8_t XL, int position);

    // void ax12a_set(int pos);
    // void packed(char arm);
    // void pretransfer(char arm);
    // void topofhexa(char arm);
    // void bottomhexa(char arm);
    // void topstretched(char arm);
    // void putdown(char arm);
    // void vacuum(char arm, int state);
    // void ActionPacked();
    // void ActionPreTransfer();
    // void PriseHexagone(); // fonction en fabrication

private:

};


#endif // SERVOS_H
