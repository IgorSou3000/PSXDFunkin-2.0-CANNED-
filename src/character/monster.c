/*
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include "monster.h"

#include "psx/mem.h"
#include "psx/archive.h"
#include "stage/stage.h"
#include "psx/main.h"

//Monster character structure
enum
{
	Monster_ArcMain_Idle0,
	Monster_ArcMain_Idle1,
	Monster_ArcMain_Idle2,
	Monster_ArcMain_Idle3,
	Monster_ArcMain_Idle4,
	Monster_ArcMain_Idle5,
	Monster_ArcMain_Idle6,
	Monster_ArcMain_Idle7,
	Monster_ArcMain_Left0,
	Monster_ArcMain_Left1,
	Monster_ArcMain_Left2,
	Monster_ArcMain_Down0,
	Monster_ArcMain_Down1,
	Monster_ArcMain_Down2,
	Monster_ArcMain_Up0,
	Monster_ArcMain_Up1,
	Monster_ArcMain_Up2,
	Monster_ArcMain_Up3,
	Monster_ArcMain_Up4,
	Monster_ArcMain_Right0,
	Monster_ArcMain_Right1,
	Monster_ArcMain_Right2,
	Monster_ArcMain_Right3,
	Monster_ArcMain_Right4,
	Monster_ArcMain_Right5,
	
	Monster_Arc_Max,
};

typedef struct
{
	//Character base structure
	Character character;
	
	//Render data and state
	IO_Data arc_main;
	IO_Data arc_ptr[Monster_Arc_Max];
	
	Gfx_Tex tex;
	u8 frame, tex_Id;
} Char_Monster;

//Monster character definitions
static const CharFrame char_monster_frame[] = {
	{Monster_ArcMain_Idle0,{0,0,200,180},{52,159}},
	{Monster_ArcMain_Idle1,{0,0,200,180},{52,159}},
	{Monster_ArcMain_Idle2,{0,0,200,180},{52,159}},
	{Monster_ArcMain_Idle3,{0,0,200,180},{53,164}},
	{Monster_ArcMain_Idle4,{0,0,200,200},{55,178}},
	{Monster_ArcMain_Idle5,{0,0,200,200},{56,178}},
	{Monster_ArcMain_Idle6,{0,0,200,200},{56,178}},
	{Monster_ArcMain_Idle7,{0,0,200,200},{56,178}},
	
	{Monster_ArcMain_Left0,{0,0,200,200},{57,178}},
	{Monster_ArcMain_Left1,{0,0,200,200},{57,178}},
	{Monster_ArcMain_Left2,{0,0,200,200},{57,178}},
	
	{Monster_ArcMain_Down0,{0,0,200,200},{55,176}},
	{Monster_ArcMain_Down1,{0,0,200,200},{55,176}},
	{Monster_ArcMain_Down2,{0,0,200,200},{55,176}},
	
	{Monster_ArcMain_Up0,{0,0,200,200},{57,189}},
	{Monster_ArcMain_Up1,{0,0,200,210},{57,197}},
	{Monster_ArcMain_Up2,{0,0,200,210},{57,197}},
	{Monster_ArcMain_Up3,{0,0,200,210},{57,198}},
	{Monster_ArcMain_Up4,{0,0,200,210},{57,198}},
	
	{Monster_ArcMain_Right0,{0,0,200,200},{49,179}},
	{Monster_ArcMain_Right1,{0,0,200,200},{49,179}},
	{Monster_ArcMain_Right2,{0,0,200,200},{49,179}},
	{Monster_ArcMain_Right3,{0,0,200,200},{49,179}},
	{Monster_ArcMain_Right4,{0,0,200,200},{49,179}},
	{Monster_ArcMain_Right5,{0,0,200,200},{49,179}},
};

static const Animation char_monster_anim[CharAnim_Max] = {
	{1, (const u8[]){ 0,  0,  1,  1,  2,  3,  4,  4,  5,  5,  6,  6,  7,  7,  7,  6,  6, ASCR_BACK, 4}}, //CharAnim_Idle
	{2, (const u8[]){ 8,  9, 10,  ASCR_BACK, 2}},         //CharAnim_Left
	{0, (const u8[]){ASCR_CHGANI, CharAnim_Idle}},   //CharAnim_LeftAlt
	{2, (const u8[]){11, 12, 13, ASCR_BACK, 2}},         //CharAnim_Down
	{0, (const u8[]){ASCR_CHGANI, CharAnim_Idle}},   //CharAnim_DownAlt
	{2, (const u8[]){14, 15, 16, 17, 18, ASCR_BACK, 1}},         //CharAnim_Up
	{0, (const u8[]){ASCR_CHGANI, CharAnim_Idle}},   //CharAnim_UpAlt
	{2, (const u8[]){19, 20, 21, 22, 23, ASCR_BACK, 2}},         //CharAnim_Right
	{0, (const u8[]){ASCR_CHGANI, CharAnim_Idle}},   //CharAnim_RightAlt
};

//Monster character functions
void Char_Monster_SetFrame(void *user, u8 frame)
{
	Char_Monster *this = (Char_Monster*)user;
	
	//Check if this is a new frame
	if (frame != this->frame)
	{
		//Check if new art shall be loaded
		const CharFrame *cframe = &char_monster_frame[this->frame = frame];
		if (cframe->tex != this->tex_Id)
			Gfx_LoadTex(&this->tex, this->arc_ptr[this->tex_Id = cframe->tex], 0);
	}
}

void Char_Monster_Tick(Character *character)
{
	Char_Monster *this = (Char_Monster*)character;
	
	//Perform idle dance
	if ((character->pad_held & (INPUT_LEFT | INPUT_DOWN | INPUT_UP | INPUT_RIGHT)) == 0)
		Character_PerformIdle(character);
	
	//Animate and draw
	Animatable_Animate(&character->animatable, (void*)this, Char_Monster_SetFrame);
	Character_Draw(character, &this->tex, &char_monster_frame[this->frame]);
}

void Char_Monster_SetAnim(Character *character, u8 anim)
{
	//Set animation
	Animatable_SetAnim(&character->animatable, anim);
	Character_CheckStartSing(character);
}

void Char_Monster_Free(Character *character)
{
	Char_Monster *this = (Char_Monster*)character;
	
	//Free art
	Mem_Free(this->arc_main);
}

Character *Char_Monster_New(fixed_t x, fixed_t y)
{
	//Allocate monster object
	Char_Monster *this = Mem_Alloc(sizeof(Char_Monster));
	if (this == NULL)
	{
		sprintf(error_msg, "[Char_Monster_New] Failed to allocate monster object");
		ErrorLock();
		return NULL;
	}
	
	//Initialize character
	this->character.tick = Char_Monster_Tick;
	this->character.set_anim = Char_Monster_SetAnim;
	this->character.free = Char_Monster_Free;
	
	Animatable_Init(&this->character.animatable, char_monster_anim);
	Character_Init((Character*)this, x, y);
	
	//Set character information
	this->character.spec = 0;
	
	//Health Icon
	this->character.health_i = 4;

	//Health Bar
	this->character.health_b = 0xFFD32648;

	//Character scale
	this->character.scale = FIXED_DEC(1,1);
	
	this->character.focus_x =  FIXED_DEC(135,1);
	this->character.focus_y = FIXED_DEC(-100,1);
	this->character.focus_zoom = FIXED_DEC(1,1);
	
	//Load art
	this->arc_main = IO_Read("\\CHAR\\MONSTER.ARC;1");
		
	const char **pathp = (const char *[]){
		"idle0.tim", //Monster_ArcMain_Idle0
		"idle1.tim", //Monster_ArcMain_Idle1
		"idle2.tim", //Monster_ArcMain_Idle2
		"idle3.tim", //Monster_ArcMain_Idle3
		"idle4.tim", //Monster_ArcMain_Idle4
		"idle5.tim", //Monster_ArcMain_Idle5
		"idle6.tim", //Monster_ArcMain_Idle6
		"idle7.tim", //Monster_ArcMain_Idle7
		"left0.tim",  //Monster_ArcMain_Left0
		"left1.tim",  //Monster_ArcMain_Left1
		"left2.tim",  //Monster_ArcMain_Left2
		"down0.tim",  //Monster_ArcMain_Down0
		"down1.tim",  //Monster_ArcMain_Down1
		"down2.tim",  //Monster_ArcMain_Down2
		"up0.tim",    //Monster_ArcMain_Up0
		"up1.tim",    //Monster_ArcMain_Up1
		"up2.tim",    //Monster_ArcMain_Up2
		"up3.tim",    //Monster_ArcMain_Up3
		"up4.tim",    //Monster_ArcMain_Up4
		"right0.tim", //Monster_ArcMain_Right0
		"right1.tim", //Monster_ArcMain_Right1
		"right2.tim", //Monster_ArcMain_Right2
		"right3.tim", //Monster_ArcMain_Right3
		"right4.tim", //Monster_ArcMain_Right4
		"right5.tim", //Monster_ArcMain_Right5
		NULL
	};

	IO_Data *arc_ptr = this->arc_ptr;
	for (; *pathp != NULL; pathp++)
		*arc_ptr++ = Archive_Find(this->arc_main, *pathp);

	//Initialize render state
	this->tex_Id = this->frame = 0xFF;
	
	return (Character*)this;
}
