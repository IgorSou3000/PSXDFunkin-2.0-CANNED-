/*
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include "spook.h"

#include "psx/mem.h"
#include "psx/archive.h"
#include "stage/stage.h"
#include "psx/main.h"

//Spook character structure
enum
{
	Spook_ArcMain_Idle0,
	Spook_ArcMain_Idle1,
	Spook_ArcMain_Idle2,
	Spook_ArcMain_Idle3,
	Spook_ArcMain_Left0,
	Spook_ArcMain_Left1,
	Spook_ArcMain_Down0,
	Spook_ArcMain_Down1,
	Spook_ArcMain_Up0,
	Spook_ArcMain_Up1,
	Spook_ArcMain_Right,
	
	Spook_Arc_Max,
};

typedef struct
{
	//Character base structure
	Character character;
	
	//Render data and state
	IO_Data arc_main;
	IO_Data arc_ptr[Spook_Arc_Max];
	
	Gfx_Tex tex;
	u8 frame, tex_Id;
} Char_Spook;

//Spook character definitions
static const CharFrame char_spook_frame[] = {
	{Spook_ArcMain_Idle0,{  0,  0,144,134},{ 61,132}}, // 0 idle 1
	{Spook_ArcMain_Idle1,{  0,  0,144,134},{ 61,131}}, // 1 idle 2
	{Spook_ArcMain_Idle2,{  0,  0,110,132},{ 50,124}}, // 2 idle 3
	{Spook_ArcMain_Idle2,{110,  0,110,132},{ 51,125}}, // 3 idle 4
	{Spook_ArcMain_Idle3,{  0,  0,127,134},{ 61,131}}, // 4 idle 5
	{Spook_ArcMain_Idle3,{127,  0,127,134},{ 61,131}}, // 5 idle 6
	
	{Spook_ArcMain_Left0,{  0,  0,125,160},{ 59,152}}, // 6 left 1
	{Spook_ArcMain_Left0,{125,  0,125,160},{ 60,152}}, // 7 left 2
	{Spook_ArcMain_Left1,{  0,  0,125,160},{ 59,152}}, // 8 left 3
	{Spook_ArcMain_Left1,{125,  0,125,160},{ 60,152}}, // 9 left 4
	
	{Spook_ArcMain_Down0,{  0,  0,140,140},{ 35,137}}, //10 down 1
	{Spook_ArcMain_Down1,{  0,  0,140,140},{ 35,136}}, //11 down 2
	
	{Spook_ArcMain_Up0,{  0,  0,140,160},{ 54,155}}, //12 up 1
	{Spook_ArcMain_Up1,{  0,  0,140,160},{ 54,154}}, //13 up 2
	
	{Spook_ArcMain_Right,{  0,  0,126,140},{ 45,135}}, //14 right 1
	{Spook_ArcMain_Right,{128,  0,126,140},{ 41,136}}, //15 right 2
};

static const Animation char_spook_anim[CharAnim_Max] = {
	{2, (const u8[]){ASCR_CHGANI, CharAnim_LeftAlt}}, //CharAnim_Idle
	{2, (const u8[]){ 6,  7,  8,  9, ASCR_BACK, 1}},          //CharAnim_Left
	{2, (const u8[]){ 0,  1,  2,  3, ASCR_BACK, 1}},  //CharAnim_LeftAlt
	{2, (const u8[]){10, 11, ASCR_BACK, 1}},          //CharAnim_Down
	{0, (const u8[]){ASCR_CHGANI, CharAnim_LeftAlt}}, //CharAnim_DownAlt
	{2, (const u8[]){12, 13, ASCR_BACK, 1}},          //CharAnim_Up
	{0, (const u8[]){ASCR_CHGANI, CharAnim_LeftAlt}}, //CharAnim_UpAlt
	{2, (const u8[]){14, 15, ASCR_BACK, 1}},          //CharAnim_Right
	{2, (const u8[]){ 4,  5,  2,  3, ASCR_BACK, 1}},  //CharAnim_RightAlt
};

//Spook character functions
void Char_Spook_SetFrame(void *user, u8 frame)
{
	Char_Spook *this = (Char_Spook*)user;
	
	//Check if this is a new frame
	if (frame != this->frame)
	{
		//Check if new art shall be loaded
		const CharFrame *cframe = &char_spook_frame[this->frame = frame];
		if (cframe->tex != this->tex_Id)
			Gfx_LoadTex(&this->tex, this->arc_ptr[this->tex_Id = cframe->tex], 0);
	}
}

void Char_Spook_Tick(Character *character)
{
	Char_Spook *this = (Char_Spook*)character;
	
	//Perform spooky dance
	if ((character->pad_held & (INPUT_LEFT | INPUT_DOWN | INPUT_UP | INPUT_RIGHT)) == 0)
	{
		Character_CheckEndSing(character);
		
		if (stage.flag & STAGE_FLAG_JUST_STEP)
		{
			if ((Animatable_Ended(&character->animatable) || character->animatable.anim == CharAnim_LeftAlt || character->animatable.anim == CharAnim_RightAlt) &&
				(character->animatable.anim != CharAnim_Left &&
				 character->animatable.anim != CharAnim_Down &&
				 character->animatable.anim != CharAnim_Up &&
				 character->animatable.anim != CharAnim_Right) &&
				(stage.song_step % 4) == 0)
				character->set_anim(character, CharAnim_Idle);
		}
	}
	//Animate and draw
	Animatable_Animate(&character->animatable, (void*)this, Char_Spook_SetFrame);
	Character_Draw(character, &this->tex, &char_spook_frame[this->frame]);
}

void Char_Spook_SetAnim(Character *character, u8 anim)
{
	//Set animation
	if (anim == CharAnim_Idle)
	{
		if (character->animatable.anim == CharAnim_LeftAlt)
			anim = CharAnim_RightAlt;
		else
			anim = CharAnim_LeftAlt;
		character->sing_end = FIXED_DEC(0x7FFF,1);
	}
	else
	{
		Character_CheckStartSing(character);
	}
	Animatable_SetAnim(&character->animatable, anim);
}

void Char_Spook_Free(Character *character)
{
	Char_Spook *this = (Char_Spook*)character;
	
	//Free art
	Mem_Free(this->arc_main);
}

Character *Char_Spook_New(fixed_t x, fixed_t y)
{
	//Allocate spook object
	Char_Spook *this = Mem_Alloc(sizeof(Char_Spook));
	if (this == NULL)
	{
		sprintf(error_msg, "[Char_Spook_New] Failed to allocate spook object");
		ErrorLock();
		return NULL;
	}
	
	//Initialize character
	this->character.tick = Char_Spook_Tick;
	this->character.set_anim = Char_Spook_SetAnim;
	this->character.free = Char_Spook_Free;
	
	Animatable_Init(&this->character.animatable, char_spook_anim);
	Character_Init((Character*)this, x, y);
	
	//Set character information
	this->character.spec = 0;
	
	//Health Icon
	this->character.health_i = 3;

	//Health Bar
	this->character.health_b = 0xFFFFFFFF;

	//Character scale
	this->character.scale = FIXED_DEC(1,1);
	
	this->character.focus_x =  FIXED_DEC(65,1);
	this->character.focus_y = FIXED_DEC(-80,1);
	this->character.focus_zoom = FIXED_DEC(1,1);
	
	//Load art
	this->arc_main = IO_Read("\\CHAR\\SPOOK.ARC;1");
	
	const char **pathp = (const char *[]){
		"idle0.tim", //Spook_ArcMain_Idle0
		"idle1.tim", //Spook_ArcMain_Idle1
		"idle2.tim", //Spook_ArcMain_Idle2
		"idle3.tim", //Spook_ArcMain_Idle3
		"left0.tim",  //Spook_ArcMain_Left0
		"left1.tim",  //Spook_ArcMain_Left1
		"down0.tim",  //Spook_ArcMain_Down0
		"down1.tim",  //Spook_ArcMain_Down1
		"up0.tim",    //Spook_ArcMain_Up0
		"up1.tim",    //Spook_ArcMain_Up1
		"right.tim", //Spook_ArcMain_Right
		NULL
	};
	IO_Data *arc_ptr = this->arc_ptr;
	for (; *pathp != NULL; pathp++)
		*arc_ptr++ = Archive_Find(this->arc_main, *pathp);
	
	//Initialize render state
	this->tex_Id = this->frame = 0xFF;
	
	return (Character*)this;
}
