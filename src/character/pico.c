/*
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include "pico.h"

#include "psx/mem.h"
#include "psx/archive.h"
#include "stage/stage.h"
#include "psx/main.h"

//Pico character structure
enum
{
	Pico_ArcMain_Idle0,
	Pico_ArcMain_Idle1,
	Pico_ArcMain_Hit0,
	Pico_ArcMain_Hit1,
	Pico_ArcMain_Hit2,
	
	Pico_Arc_Max,
};

typedef struct
{
	//Character base structure
	Character character;
	
	//Render data and state
	IO_Data arc_main;
	IO_Data arc_ptr[Pico_Arc_Max];
	
	Gfx_Tex tex;
	u8 frame, tex_Id;
} Char_Pico;

//Pico character definitions
static const CharFrame char_pico_frame[] = {
	{Pico_ArcMain_Idle0,{0,0,110,124},{64,104}},
	{Pico_ArcMain_Idle0,{115,0,135,124},{66,104}},
	{Pico_ArcMain_Idle0,{0,128,110,127},{64,108}},
	{Pico_ArcMain_Idle0,{127,128,128,127},{65,108}},
	{Pico_ArcMain_Idle1,{0,0,124,132},{69,110}},
	{Pico_ArcMain_Idle1,{124,0,124,132},{71,110}},
	
	{Pico_ArcMain_Hit0,{0,0,120,125},{83,103}},
	{Pico_ArcMain_Hit0,{120,0,120,125},{82,106}},

	{Pico_ArcMain_Hit0,{0,126,115,125},{68,90}},
	{Pico_ArcMain_Hit0,{115,126,115,125},{70,90}},
	
	{Pico_ArcMain_Hit1,{0,0,126,144},{52,124}},
	{Pico_ArcMain_Hit1,{128,0,126,144},{54,121}},

	{Pico_ArcMain_Hit2,{0,0,108,136},{58,112}},
	{Pico_ArcMain_Hit2,{108,0,108,136},{59,112}},
};

static const Animation char_pico_anim[CharAnim_Max] = {
	{1, (const u8[]){ 0,  0,  1,  1,  2,  3,  4,  4,  5,  5,  ASCR_BACK, 1}}, //CharAnim_Idle
	{2, (const u8[]){ 6,  7, ASCR_BACK, 1}},         //CharAnim_Left
	{0, (const u8[]){ASCR_CHGANI, CharAnim_Idle}},   //CharAnim_LeftAlt
	{2, (const u8[]){ 8,  9, ASCR_BACK, 1}},         //CharAnim_Down
	{0, (const u8[]){ASCR_CHGANI, CharAnim_Idle}},   //CharAnim_DownAlt
	{2, (const u8[]){10, 11, ASCR_BACK, 1}},         //CharAnim_Up
	{0, (const u8[]){ASCR_CHGANI, CharAnim_Idle}},   //CharAnim_UpAlt
	{2, (const u8[]){12, 13, ASCR_BACK, 1}},         //CharAnim_Right
	{0, (const u8[]){ASCR_CHGANI, CharAnim_Idle}},   //CharAnim_RightAlt
};

//Pico character functions
void Char_Pico_SetFrame(void *user, u8 frame)
{
	Char_Pico *this = (Char_Pico*)user;
	
	//Check if this is a new frame
	if (frame != this->frame)
	{
		//Check if new art shall be loaded
		const CharFrame *cframe = &char_pico_frame[this->frame = frame];
		if (cframe->tex != this->tex_Id)
			Gfx_LoadTex(&this->tex, this->arc_ptr[this->tex_Id = cframe->tex], 0);
	}
}

void Char_Pico_Tick(Character *character)
{
	Char_Pico *this = (Char_Pico*)character;
	
	//Perform idle dance
	if ((character->pad_held & (INPUT_LEFT | INPUT_DOWN | INPUT_UP | INPUT_RIGHT)) == 0)
		Character_PerformIdle(character);
	
	//Animate and draw
	Animatable_Animate(&character->animatable, (void*)this, Char_Pico_SetFrame);
	Character_Draw(character, &this->tex, &char_pico_frame[this->frame]);
}

void Char_Pico_SetAnim(Character *character, u8 anim)
{
	//Set animation
	Animatable_SetAnim(&character->animatable, anim);
	Character_CheckStartSing(character);
}

void Char_Pico_Free(Character *character)
{
	Char_Pico *this = (Char_Pico*)character;
	
	//Free art
	Mem_Free(this->arc_main);
}

Character *Char_Pico_New(fixed_t x, fixed_t y)
{
	//Allocate pico object
	Char_Pico *this = Mem_Alloc(sizeof(Char_Pico));
	if (this == NULL)
	{
		sprintf(error_msg, "[Char_Pico_New] Failed to allocate pico object");
		ErrorLock();
		return NULL;
	}
	
	//Initialize character
	this->character.tick = Char_Pico_Tick;
	this->character.set_anim = Char_Pico_SetAnim;
	this->character.free = Char_Pico_Free;
	
	Animatable_Init(&this->character.animatable, char_pico_anim);
	Character_Init((Character*)this, x, y);
	
	//Set character information
	this->character.spec = 0;
	
	//Health Icon
	this->character.health_i = 4;

	//Health Bar
	this->character.health_b = 0xFFB7D753;

	//Character scale
	this->character.scale = FIXED_DEC(1,1);
	
	this->character.focus_x = FIXED_DEC(65,1);
	this->character.focus_y = FIXED_DEC(-65,1);
	this->character.focus_zoom = FIXED_DEC(1,1);
	
	//Load art
	this->arc_main = IO_Read("\\CHAR\\PICO.ARC;1");
	
	const char **pathp = (const char *[]){
		"idle0.tim", //Pico_ArcMain_Idle0
		"idle1.tim", //Pico_ArcMain_Idle1
		"hit0.tim", //Pico_ArcMain_Hit0
		"hit1.tim", //Pico_ArcMain_Hit1
		"hit2.tim", //Pico_ArcMain_Hit2
		NULL
	};
	IO_Data *arc_ptr = this->arc_ptr;
	for (; *pathp != NULL; pathp++)
		*arc_ptr++ = Archive_Find(this->arc_main, *pathp);
	
	//Initialize render state
	this->tex_Id = this->frame = 0xFF;
	
	return (Character*)this;
}
