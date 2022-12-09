/*
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#ifndef PSXF_GUARD_AUDIO_H
#define PSXF_GUARD_AUDIO_H

#include "psx.h"

typedef u32 SFX;

//XA enumerations
typedef enum
{
	XA_Menu,   //MENU.XA
	XA_Week1A, //WEEK1A.XA
	XA_Week1B, //WEEK1B.XA
	XA_Week2A, //WEEK2A.XA
	XA_Week2B, //WEEK2B.XA
	XA_Week3A, //WEEK3A.XA
	XA_Week3B, //WEEK3B.XA
	XA_Week4A, //WEEK4A.XA
	XA_Week4B, //WEEK4B.XA
	XA_Week5A, //WEEK5A.XA
	XA_Week5B, //WEEK5B.XA
	XA_Week6A, //WEEK6A.XA
	XA_Week6B, //WEEK6B.XA
	XA_BonusA, //BONUSA.XA
	XA_BonusB, //BONUSB.XA
	XA_BonusC, //BONUSC.XA
	XA_BonusD, //BONUSD.XA
	
	XA_Max,
} XA_File;

typedef enum
{
	//MENU.XA
	XA_GettinFreaky, //Gettin' Freaky
	XA_GameOver,     //Game Over
	//WEEK1A.XA
	XA_Bopeebo, //Bopeebo
	XA_Fresh,   //Fresh
	//WEEK1B.XA
	XA_Dadbattle, //DadBattle
	XA_Tutorial,  //Tutorial
	//WEEK2A.XA
	XA_Spookeez, //Spookeez
	XA_South,    //South
	//WEEK2B.XA
	XA_Ghastly, //Ghastly
	XA_Monster, //Monster
	//WEEK3A.XA
	XA_Pico,   //Pico
	XA_Philly, //Philly
	//WEEK3B.XA
	XA_Blammed, //Blammed
	//WEEK4A.XA
	XA_SatinPanties, //Satin Panties
	XA_High,         //High
	//WEEK4B.XA
	XA_Awooga, //Awooga
	XA_MILF, //M.I.L.F
	//WEEK5A.XA
	XA_Green_Eggs,  //Green Eggs
	XA_Ham, //Ham
	//WEEK5B.XA
	XA_Feaster, //Feaster
	//WEEK6A.XA
	XA_Senpai, //Senpai
	XA_Roses,  //Roses
	//WEEK6B.XA
	XA_Thorns, //Thorns
	//BONUSA.XA
	XA_Too_Slow, //Too Slow
	XA_Endless,  //Endless
	//BONUSB.XA
	XA_Cycles, //Cycles
	XA_Milk, //Milk
	//BONUSC.XA
	XA_DGuy, //DGuy
	XA_Lore, //Lore
	//BONUSD.XA
	XA_God_Feast, //God Feast
	
	XA_TrackMax,
} XA_Track;

//Audio functions
void Audio_Init(void);
void Audio_Quit(void);
void Audio_PlayXA_Track(XA_Track track, u8 volume, u8 channel, boolean loop);
void Audio_SeekXA_Track(XA_Track track);
void Audio_PauseXA(void);
void Audio_ResumeXA(void);
void Audio_StopXA(void);
void Audio_ChannelXA(u8 channel);
s32 Audio_TellXA_Sector(void);
s32 Audio_TellXA_Milli(void);
boolean Audio_PlayingXA(void);
void Audio_WaitPlayXA(void);
void Audio_ProcessXA(void);
u16 Audio_GetLength(XA_Track track);

void Audio_ClearAlloc(void);
u32 Audio_LoadSFX(const char* path);
void Audio_PlaySFX(SFX addr, u16 volume);

#endif