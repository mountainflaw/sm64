/*
 * obelisk sm64 decomp enhancements by mountainflaw
 * this file adds:
 * - basic lighting controls for mario and levels
 * - useful defines
 * these coded computer instructions are licensed under the bsd 3 license
 */

// if guards

#ifndef _OBELISK_H
#define _OBELISK_H

// includes

#include "area.h" // gCurrLevelNum

// define modes for setMarioLightShadingMode

#define SHADE_100    1
#define SHADE_75  0.75
#define SHADE_50  0.50
#define SHADE_25  0.25

/* 
 * common values for shading, which are manipulated with the SHADE_* defines
 * in combination with the setMarioLightShadingMode function.
 */

// mario light values

#define VAL1 0x7F
#define VAL2 0x39
#define VAL3 0X0E
#define VAL4 0x07
#define VAL5 0x3C
#define VAL6 0x60
#define VAL7 0x03

// level defines

#define UNUSED1           1
#define UNUSED2           2
#define UNUSED3           3
#define BBH               4
#define CCM               5
#define INSIDE_CASTLE     6
#define HMC               7
#define SSL               8
#define BOB               9
#define SL               10
#define WDW              11
#define JRB              12
#define THI              13
#define TTC              14
#define RR               15
#define CASTLE_GROUNDS   16
#define BITDW            17
#define VCUTM            18
#define BITFS            19
#define AQUARIUM         20
#define BITS             21
#define LLL              22
#define DDD              23
#define WF               24
#define CAKE             25
#define CASTLE_COURTYARD 26
#define PSS              27
#define COTMC            28
#define TOTWC            29
#define BOWSER1          30
#define WMOTR            31
#define UNUSED4          32
#define BOWSER2          33
#define BOWSER3          34
#define UNUSED5          35
#define TTM              36
#define UNUSED6          37
#define UNUSED7          38


// prototypes

void setMarioLightShadingMode(float mode);

// custom structs used for setting light values

typedef struct // used for regular lights
{
	unsigned char byte[7];
} Light2;

typedef struct // used for lighting data that are the size of 16 bytes
{
	unsigned char byte[15];
} Light3;

// make sure to glabel these in the actor file for mario

extern Light2 *mario_seg4_light_04000000;
extern Light2 *mario_seg4_light_04000018;
extern Light2 *mario_seg4_light_04000030;
extern Light2 *mario_seg4_light_04000048;
extern Light2 *mario_seg4_light_04000078;

// level lights; make sure to glabel these too if you use them



#define DEBUG
void setLevelShading(void) // sets the shading for mario based on level number
{
#ifdef DEBUG
	print_text_fmt_int(40, 60, "AREA: %d", gCurrAreaIndex);
#endif
	switch(gCurrLevelNum) 
	{
		case BBH:
		case HMC:
			setMarioLightShadingMode(SHADE_25);
			break;
		case INSIDE_CASTLE:
			setMarioLightShadingMode(SHADE_75);
			if (gCurrAreaIndex == 3)
				setMarioLightShadingMode(SHADE_50);
			break;
		case SSL:
			setMarioLightShadingMode(SHADE_100);
			if (gCurrAreaIndex == 2 || gCurrAreaIndex == 3) // both pyramid areas
				setMarioLightShadingMode(SHADE_25);
			break;
		case JRB:
		case DDD:
		case AQUARIUM:
			setMarioLightShadingMode(SHADE_50);
			break;
		case CCM:
		case SL:
		case PSS:
			setMarioLightShadingMode(SHADE_75);
			if (gCurrAreaIndex == 2)
				setMarioLightShadingMode(SHADE_50);
			break;
		default:
			setMarioLightShadingMode(SHADE_100);
			break;
	}
}

void setMarioLightShadingMode(float mode) // used to set mario's shading to one of the four predetermined modes
{
	Light2 *ptr;
	ptr = segmented_to_virtual(&mario_seg4_light_04000000);
	ptr->byte[2] = VAL1 * mode;
	ptr->byte[6] = VAL1 * mode;
	ptr = segmented_to_virtual(&mario_seg4_light_04000018);
	ptr->byte[0] = VAL1 * mode;
	ptr->byte[4] = VAL1 * mode;
	ptr = segmented_to_virtual(&mario_seg4_light_04000030);
	ptr->byte[0] = VAL1 * mode;
	ptr->byte[1] = VAL1 * mode;
	ptr->byte[2] = VAL1 * mode;
	ptr->byte[4] = VAL1 * mode;
	ptr->byte[5] = VAL1 * mode;
	ptr->byte[6] = VAL1 * mode;
	ptr = segmented_to_virtual(&mario_seg4_light_04000048);
	ptr->byte[0] = VAL2 * mode;
	ptr->byte[1] = VAL3 * mode;
	ptr->byte[2] = VAL4 * mode;
	ptr->byte[4] = VAL2 * mode;
	ptr->byte[5] = VAL3 * mode;
	ptr->byte[6] = VAL4 * mode;
	ptr = segmented_to_virtual(&mario_seg4_light_04000078);
	ptr->byte[0] = VAL2 * mode;
	ptr->byte[1] = VAL7 * mode;
	ptr->byte[4] = VAL2 * mode;
	ptr->byte[4] = VAL7 * mode;
}
#endif