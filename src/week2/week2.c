/*
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include "week2.h"

#include "psx/mem.h"
#include "psx/archive.h"
#include "psx/timer.h"

//Week 2 background structure
typedef struct
{
	//Stage background base structure
	StageBack back;
	
	//Textures
	Gfx_Tex tex_back0; //Background 1
	Gfx_Tex tex_back1; //Background 2

	//Week 2 Sound
	SFX sounds[3];

	//Week 2 Thunder/monster jumpscare
	fixed_t thunder, thunderspd;

	//Check if it the monster stage
	boolean is_monster;
} Back_Week2;

void Back_Week2_Tick(StageBack *back)
{
	Back_Week2 *this = (Back_Week2*)back;
	
	//Monster "jumpscare"
	if (stage.story && this->is_monster && stage.song_step == -29 && stage.flag & STAGE_FLAG_JUST_STEP)
	{
		//Play Jumpscare Sound
		Audio_PlaySFX(this->sounds[2], 80);

		//Set thunder stuff
		this->thunder = FIXED_DEC(255,1);
		this->thunderspd = FIXED_DEC(160,1);
	}
}

void Back_Week2_DrawFG(StageBack *back)
{
	Back_Week2 *this = (Back_Week2*)back;
	
	//Draw Thunder
	if (this->thunder > 0)
	{
		static const RECT flash = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
		u8 flash_col = this->thunder / FIXED_UNIT;
		Gfx_BlendRect(&flash, flash_col, flash_col, flash_col, 1);
		this->thunder -= FIXED_MUL(this->thunderspd, timer_dt);
	}
}

//Week 2 background functions
void Back_Week2_DrawBG(StageBack *back)
{
	Back_Week2 *this = (Back_Week2*)back;
	
	fixed_t fx, fy;
	fx = stage.camera.x;
	fy = stage.camera.y;
	
	//Draw background
	RECT back_src = {0, 0, 255, 250};
	RECT_FIXED back_dst = {
		FIXED_DEC(-205,1) - fx,
		FIXED_DEC(-115,1) - fy,
		FIXED_DEC(255,1),
		FIXED_DEC(250,1)
	};
	
	Stage_DrawTex(&this->tex_back0, &back_src, &back_dst, stage.camera.bzoom);

	back_dst.x += back_dst.w;
	
	Stage_DrawTex(&this->tex_back1, &back_src, &back_dst, stage.camera.bzoom);

	back_dst.x -= back_dst.w;
	back_src.h = 1;
	back_dst.y -= back_dst.h;

	Stage_DrawTex(&this->tex_back0, &back_src, &back_dst, stage.camera.bzoom);

	back_dst.x += back_dst.w;
	Stage_DrawTex(&this->tex_back1, &back_src, &back_dst, stage.camera.bzoom);
}

void Back_Week2_Free(StageBack *back)
{
	Back_Week2 *this = (Back_Week2*)back;
	
	//Free structure
	Mem_Free(this);
}

StageBack *Back_Week2_New(void)
{
	//Allocate background structure
	Back_Week2 *this = (Back_Week2*)Mem_Alloc(sizeof(Back_Week2));
	if (this == NULL)
		return NULL;

	//Check if it the monster stage
	this->is_monster = (stage.stage_id == StageId_2_4);
	
	//Set background functions
	this->back.tick = Back_Week2_Tick;
	this->back.draw_fg = Back_Week2_DrawFG;
	this->back.draw_md = NULL;
	this->back.draw_bg = Back_Week2_DrawBG;
	this->back.free = Back_Week2_Free;

	//Set stage timer color
	if (this->is_monster)
	{
	stage.timercolor.r = 198;
	stage.timercolor.g = 18;
	stage.timercolor.b = 52;
	}
	else
	{
		stage.timercolor.r = 119;
		stage.timercolor.g = 242;
		stage.timercolor.b = 251;
	}
	
	//Load HUD textures
	Gfx_LoadTex(&stage.tex_hud0, IO_Read("\\STAGE\\HUD0.TIM;1"), GFX_LOADTEX_FREE);
	Gfx_LoadTex(&stage.tex_hud1, IO_Read("\\STAGE\\HUD1.TIM;1"), GFX_LOADTEX_FREE);
	Gfx_LoadTex(&stage.tex_hud2, IO_Read("\\STAGE\\HUD2.TIM;1"), GFX_LOADTEX_FREE);
	
	//Load background textures
	IO_Data arc_back;

	//Use Monster variation
	if (this->is_monster)
		arc_back = IO_Read("\\WEEK2\\MONSBACK.ARC;1");
	//Use normal variation
	else
		arc_back = IO_Read("\\WEEK2\\BACK.ARC;1");

	Gfx_LoadTex(&this->tex_back0, Archive_Find(arc_back, "back0.tim"), 0);
	Gfx_LoadTex(&this->tex_back1, Archive_Find(arc_back, "back1.tim"), 0);
	Mem_Free(arc_back);

	//Load Sounds
	this->sounds[2] = Audio_LoadSFX("\\WEEK2\\MONSTER.VAG;1");

	//Initialize thunder state
	this->thunder = this->thunderspd = 0;
	
	return (StageBack*)this;
}
