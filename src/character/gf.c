/*
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include "gf.h"

#include "psx/mem.h"
#include "psx/archive.h"
#include "stage/stage.h"
#include "psx/main.h"

#include "speaker.h"

//GF character structure
enum
{
	GF_ArcMain_GF0,
	GF_ArcMain_GF1,
	GF_ArcMain_GF2,
	GF_ArcMain_GF3,
	GF_ArcMain_GF4,
	
	GF_ArcScene_0, //tut0
	GF_ArcScene_1, //tut1
	
	GF_Arc_Max,
};

typedef struct
{
	//Character base structure
	Character character;
	
	//Render data and state
	IO_Data arc_main, arc_scene;
	IO_Data arc_ptr[GF_Arc_Max];
	
	Gfx_Tex tex;
	u8 frame, tex_id;
	
	//Speaker
	Speaker speaker;
} Char_GF;

//GF character definitions
static const CharFrame char_GF_frame[] = {
	{GF_ArcMain_GF0,{  0,  0, 85,112},{ 37, 72}}, // 0 Bop Left 1
	{GF_ArcMain_GF0,{ 85,  0, 85,112},{ 36, 72}}, // 1 Bop Left 2
	{GF_ArcMain_GF0,{170,  0, 85,110},{ 36, 71}}, // 2 Bop Left 3
	{GF_ArcMain_GF0,{  0,111, 85,108},{ 34, 70}}, // 3 Bop Left 4
	{GF_ArcMain_GF0,{ 84,111, 85,108},{ 34, 70}}, // 4 Bop Left 5
	{GF_ArcMain_GF0,{170,110, 85,109},{ 24, 71}}, // 5 Bop Left 6
	{GF_ArcMain_GF1,{  0,  0, 96,114},{ 35, 75}}, // 6 Bop Left 7
	{GF_ArcMain_GF1,{ 95,  0, 89,114},{ 26, 75}}, // 7 Bop Left 8
	
	{GF_ArcMain_GF2,{  0,  0, 95,117},{ 29, 77}}, // 8 Bop Right 1
	{GF_ArcMain_GF2,{ 95,  0, 91,117},{ 24, 77}}, // 9 Bop Right 2
	{GF_ArcMain_GF2,{  0,123, 98,116},{ 31, 76}}, //10 Bop Right 3
	{GF_ArcMain_GF2,{ 97,123, 90,116},{ 24, 77}}, //11 Bop Right 4
	{GF_ArcMain_GF3,{  0,  0, 95,114},{ 28, 74}}, //12 Bop Right 5
	{GF_ArcMain_GF3,{ 92,  0, 91,115},{ 29, 76}}, //13 Bop Right 6
	{GF_ArcMain_GF3,{  0,117, 95,110},{ 31, 71}}, //14 Bop Right 7
	{GF_ArcMain_GF3,{ 95,117, 88,110},{ 29, 68}}, //15 Bop Right 8
	
	{GF_ArcMain_GF2, {  0,   0,  73, 100}, { 34,  71}}, //12 cry 1
	{GF_ArcMain_GF2, { 74,   0,  73, 102}, { 35,  72}}, //13 cry 2
	{GF_ArcMain_GF2, {148,   0,  73, 102}, { 34,  72}}, //14 cry 3
	{GF_ArcMain_GF2, {  0, 101,  74, 102}, { 35,  72}}, //15 cry 4
	{GF_ArcMain_GF2, { 75, 102,  73, 102}, { 34,  72}}, //16 cry 5
	
	{GF_ArcScene_0, {  0,   0,  75, 102}, { 39,  71}}, //17 left 1
	{GF_ArcScene_0, { 76,   0,  77, 103}, { 41,  72}}, //18 left 2
	
	{GF_ArcScene_0, {154,   0,  79, 102}, { 37,  71}}, //19 down 1
	{GF_ArcScene_0, {  0, 103,  78, 104}, { 37,  72}}, //20 down 2
	
	{GF_ArcScene_0, { 79, 104,  79, 108}, { 39,  78}}, //21 up 1
	{GF_ArcScene_0, {159, 104,  79, 109}, { 39,  78}}, //22 up 2
	
	{GF_ArcScene_1, {  0,   0,  81, 102}, { 41,  71}}, //23 right 1
	{GF_ArcScene_1, { 81,   0,  76, 103}, { 36,  72}}, //24 right 2
	
	{GF_ArcScene_1, {158,   0,  75, 108}, { 36,  78}}, //25 cheer 1
	{GF_ArcScene_1, {  0, 103,  77, 107}, { 37,  77}}, //26 cheer 2
};

static const Animation char_GF_anim[CharAnim_Max] = {
	{  0, (const u8[]){ASCR_CHGANI, CharAnim_LeftAlt}},                        //CharAnim_Idle
	{2, (const u8[]){17, 18, ASCR_BACK, 1}},                                 //CharAnim_Left
	{1, (const u8[]){ 0,  0,  1,  2,  2,  3,  4,  5,  5,  5,  6,  7, ASCR_BACK, 1}}, //CharAnim_LeftAlt
	{2, (const u8[]){19, 20, ASCR_BACK, 1}},                                 //CharAnim_Down
	{1, (const u8[]){12, 13, 14, 15, 16, ASCR_REPEAT}},                      //CharAnim_DownAlt
	{2, (const u8[]){21, 22, ASCR_BACK, 1}},                                 //CharAnim_Up
	{2, (const u8[]){25, 26, ASCR_BACK, 1}},                                 //CharAnim_UpAlt
	{2, (const u8[]){23, 24, ASCR_BACK, 1}},                                 //CharAnim_Right
	{1, (const u8[]){ 8,  8,  9, 10, 10, 11, 12, 13, 13, 13, 14, 15, ASCR_BACK, 1}}, //CharAnim_RightAlt
};

//GF character functions
void Char_GF_SetFrame(void *user, u8 frame)
{
	Char_GF *this = (Char_GF*)user;
	
	//Check if this is a new frame
	if (frame != this->frame)
	{
		//Check if new art shall be loaded
		const CharFrame *cframe = &char_GF_frame[this->frame = frame];
		if (cframe->tex != this->tex_id)
			Gfx_LoadTex(&this->tex, this->arc_ptr[this->tex_id = cframe->tex], 0);
	}
}

void Char_GF_Tick(Character *character)
{
	Char_GF *this = (Char_GF*)character;
	
	if (stage.flag & STAGE_FLAG_JUST_STEP)
	{
		//Perform dance
		if (stage.note_scroll >= character->sing_end && (stage.song_step % stage.gf_speed) == 0)
		{
			//Switch animation
			if (character->animatable.anim == CharAnim_LeftAlt || character->animatable.anim == CharAnim_Right)
				character->set_anim(character, CharAnim_RightAlt);
			else
				character->set_anim(character, CharAnim_LeftAlt);
				
			//Bump speakers
			Speaker_Bump(&this->speaker);
		}
	}
	
	//Animate and draw
	Animatable_Animate(&character->animatable, (void*)this, Char_GF_SetFrame);
	Character_Draw(character, &this->tex, &char_GF_frame[this->frame]);
	
	//Tick speakers
	Speaker_Tick(&this->speaker, character->x + FIXED_DEC(8,1), character->y + FIXED_DEC(8,1));
}

void Char_GF_SetAnim(Character *character, u8 anim)
{
	//Set animation
	if (anim == CharAnim_Left || anim == CharAnim_Down || anim == CharAnim_Up || anim == CharAnim_Right || anim == CharAnim_UpAlt)
		character->sing_end = stage.note_scroll + FIXED_DEC(22,1); //Nearly 2 steps
	Animatable_SetAnim(&character->animatable, anim);
}

void Char_GF_Free(Character *character)
{
	Char_GF *this = (Char_GF*)character;
	
	//Free art
	Mem_Free(this->arc_main);
	Mem_Free(this->arc_scene);
}

Character *Char_GF_New(fixed_t x, fixed_t y)
{
	//Allocate gf object
	Char_GF *this = Mem_Alloc(sizeof(Char_GF));
	if (this == NULL)
	{
		sprintf(error_msg, "[Char_GF_New] Failed to allocate gf object");
		ErrorLock();
		return NULL;
	}
	
	//Initialize character
	this->character.tick = Char_GF_Tick;
	this->character.set_anim = Char_GF_SetAnim;
	this->character.free = Char_GF_Free;
	
	Animatable_Init(&this->character.animatable, char_GF_anim);
	Character_Init((Character*)this, x, y);
	
	//Set character information
	this->character.spec = 0;
	
	//Health Icon
	this->character.health_i = 2;

	//Health Bar
	this->character.health_b = 0xFFA4004A;

	//Character scale
	this->character.scale = FIXED_DEC(1,1);
	
	this->character.focus_x = FIXED_DEC(2,1);
	this->character.focus_y = FIXED_DEC(-40,1);
	this->character.focus_zoom = FIXED_DEC(2,1);
	
	//Load art
	this->arc_main = IO_Read("\\CHAR\\GF.ARC;1");
	
	const char **pathp = (const char *[]){
		"gf0.tim", //GF_ArcMain_GF0
		"gf1.tim", //GF_ArcMain_GF1
		"gf2.tim", //GF_ArcMain_GF2
		"gf3.tim", //GF_ArcMain_GF3
		"gf4.tim", //GF_ArcMain_GF4
		NULL
	};
	IO_Data *arc_ptr = this->arc_ptr;
	for (; *pathp != NULL; pathp++)
		*arc_ptr++ = Archive_Find(this->arc_main, *pathp);
	
	//Load scene specific art
	switch (stage.stage_id)
	{
		case StageId_1_4: //Tutorial
		{
			this->arc_scene = IO_Read("\\CHAR\\GFTUT.ARC;1");
			
			const char **pathp = (const char *[]){
				"tut0.tim", //GF_ArcScene_0
				"tut1.tim", //GF_ArcScene_1
				NULL
			};
			IO_Data *arc_ptr = &this->arc_ptr[GF_ArcScene_0];
			for (; *pathp != NULL; pathp++)
				*arc_ptr++ = Archive_Find(this->arc_scene, *pathp);
			break;
		}
		default:
			this->arc_scene = NULL;
			break;
	}
	
	//Initialize render state
	this->tex_id = this->frame = 0xFF;
	
	//Initialize speaker
	Speaker_Init(&this->speaker);
	
	return (Character*)this;
}
