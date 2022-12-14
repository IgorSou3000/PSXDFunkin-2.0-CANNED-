/*
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include "week3.h"

#include "psx/mem.h"
#include "psx/archive.h"
#include "psx/random.h"
#include "psx/timer.h"

//Week 3 background structure
typedef struct
{
	//Stage background base structure
	StageBack back;
	
	//Textures
	Gfx_Tex tex_back0; //Buildings
	Gfx_Tex tex_back1; //Lights
	Gfx_Tex tex_back2; //Rooftop 1
	Gfx_Tex tex_back3; //Rooftop 2
	Gfx_Tex tex_back4; //Sky
	Gfx_Tex tex_back5; //Background 1
	Gfx_Tex tex_back6; //Background 2
	
	//Window state
	u8 win_r, win_g, win_b;
	fixed_t win_time;
	
	//Train state
	fixed_t train_x;
	u8 train_timer;
} Back_Week3;

//Week 3 background functions
static const u8 win_cols[][3] = {
	{ 49, 162, 253},
	{ 49, 253, 140},
	{251,  51, 245},
	{253,  69,  49},
	{251, 166,  51},
};

#define TRAIN_START_X FIXED_DEC(500,1)
#define TRAIN_END_X    FIXED_DEC(-8000,1)
#define TRAIN_TIME_A 6
#define TRAIN_TIME_B 14

void Back_Week3_Window(Back_Week3 *this)
{
	const u8 *win_col = win_cols[RandomRange(0, COUNT_OF(win_cols) - 1)];
	this->win_r = win_col[0];
	this->win_g = win_col[1];
	this->win_b = win_col[2];
	this->win_time = FIXED_DEC(3,1);
}

void Back_Week3_DrawBG(StageBack *back)
{
	Back_Week3 *this = (Back_Week3*)back;
	
	fixed_t fx, fy, fscroll;
	
	//Draw background
	fx = stage.camera.x;
	fy = stage.camera.y;

	RECT back_src = {0, 0, 216, 220};
	RECT_FIXED back_dst = {
		FIXED_DEC(-205,1) - fx,
		FIXED_DEC(-80,1) - fy,
		FIXED_DEC(216,1),
		FIXED_DEC(220,1)
	};

	Stage_DrawTex(&this->tex_back5, &back_src, &back_dst, stage.camera.bzoom);

	back_dst.x += back_dst.w;

	Stage_DrawTex(&this->tex_back6, &back_src, &back_dst, stage.camera.bzoom);

	//Update window
	fscroll = FIXED_DEC(3,10);
	fx = FIXED_MUL(stage.camera.x, fscroll);
	fy = FIXED_MUL(stage.camera.y, fscroll);

	if (this->win_time > 0)
	{
		this->win_time -= timer_dt;
		if (this->win_time < 0)
			this->win_time = 0;
	}
	if (stage.note_scroll >= 0 && (stage.flag & STAGE_FLAG_JUST_STEP) && (stage.song_step & 0xF) == 0)
		Back_Week3_Window(this);
	
	if (this->win_time >= 0)
	{
		RECT lightl_src = {0, 0, 148, 74};
		RECT_FIXED lightl_dst = {
			FIXED_DEC(-165,1) - fx,
			FIXED_DEC(-80,1) - fy,
			FIXED_DEC(148,1),
			FIXED_DEC(74,1)
		};
		
		RECT lightr_src = {0, 90, 148, 74};
		RECT_FIXED lightr_dst = {
			FIXED_DEC(50,1) - fx,
			FIXED_DEC(-80,1) - fy,
			FIXED_DEC(148,1),
			FIXED_DEC(74,1)
		};
		
		u8 win_r = (((fixed_t)this->win_r * this->win_time) >> FIXED_SHIFT) / 6;
		u8 win_g = (((fixed_t)this->win_g * this->win_time) >> FIXED_SHIFT) / 6;
		u8 win_b = (((fixed_t)this->win_b * this->win_time) >> FIXED_SHIFT) / 6;
		
		Stage_DrawTexCol(&this->tex_back1, &lightl_src, &lightl_dst, stage.camera.bzoom, win_r, win_g, win_b);
		Stage_DrawTexCol(&this->tex_back1, &lightr_src, &lightr_dst, stage.camera.bzoom, win_r, win_g, win_b);
	}


	//Draw Buildings
	RECT build_src = {0, 0, 184, 126};
	RECT_FIXED build_dst = {
		FIXED_DEC(-175,1) - fx,
		FIXED_DEC(-120,1) - fy,
		FIXED_DEC(184,1),
		FIXED_DEC(126,1)
	};

	Stage_DrawTex(&this->tex_back0, &build_src, &build_dst, stage.camera.bzoom);

	build_src.y += build_src.h;
	build_dst.x += build_dst.w;

	Stage_DrawTex(&this->tex_back0, &build_src, &build_dst, stage.camera.bzoom);

	build_dst.x -= build_dst.w;
	build_dst.w *= 2;
	build_src.y = 125;
	build_src.h = 1;
	build_dst.y += build_dst.h;

	Stage_DrawTex(&this->tex_back0, &build_src, &build_dst, stage.camera.bzoom);

	//Draw Sky
	fscroll = FIXED_DEC(1,10);
	fx = FIXED_MUL(stage.camera.x, fscroll);
	fy = FIXED_MUL(stage.camera.y, fscroll);

	RECT sky_src = {0, 0, 168, 126};
	RECT_FIXED sky_dst = {
		FIXED_DEC(-175,1) - fx,
		FIXED_DEC(-140,1) - fy,
		FIXED_DEC(168,1),
		FIXED_DEC(126,1)
	};

	Stage_DrawTex(&this->tex_back4, &sky_src, &sky_dst, stage.camera.bzoom);

	sky_src.y += sky_src.h;
	sky_dst.x += sky_dst.w;

	Stage_DrawTex(&this->tex_back4, &sky_src, &sky_dst, stage.camera.bzoom);
}

void Back_Week3_Free(StageBack *back)
{
	Back_Week3 *this = (Back_Week3*)back;
	
	//Free structure
	Mem_Free(this);
}

StageBack *Back_Week3_New(void)
{
	//Allocate background structure
	Back_Week3 *this = (Back_Week3*)Mem_Alloc(sizeof(Back_Week3));
	if (this == NULL)
		return NULL;
	
	//Set background functions
	this->back.tick = NULL;
	this->back.draw_fg = NULL;
	this->back.draw_md = NULL;
	this->back.draw_bg = Back_Week3_DrawBG;
	this->back.free = Back_Week3_Free;

	//Load HUD textures
	Gfx_LoadTex(&stage.tex_hud0, IO_Read("\\STAGE\\HUD0.TIM;1"), GFX_LOADTEX_FREE);
	Gfx_LoadTex(&stage.tex_hud1, IO_Read("\\STAGE\\HUD1.TIM;1"), GFX_LOADTEX_FREE);
	Gfx_LoadTex(&stage.tex_hud2, IO_Read("\\STAGE\\HUD2.TIM;1"), GFX_LOADTEX_FREE);
	
	//Load background textures
	IO_Data arc_back = IO_Read("\\WEEK3\\BACK.ARC;1");
	Gfx_LoadTex(&this->tex_back0, Archive_Find(arc_back, "back0.tim"), 0);
	Gfx_LoadTex(&this->tex_back1, Archive_Find(arc_back, "back1.tim"), 0);
	Gfx_LoadTex(&this->tex_back2, Archive_Find(arc_back, "back2.tim"), 0);
	Gfx_LoadTex(&this->tex_back3, Archive_Find(arc_back, "back3.tim"), 0);
	Gfx_LoadTex(&this->tex_back4, Archive_Find(arc_back, "back4.tim"), 0);
	Gfx_LoadTex(&this->tex_back5, Archive_Find(arc_back, "back5.tim"), 0);
	Gfx_LoadTex(&this->tex_back6, Archive_Find(arc_back, "back6.tim"), 0);
	Mem_Free(arc_back);
	
	//Initialize window state
	this->win_time = -1;
	
	//Initialize train state
	this->train_x = TRAIN_END_X;
	this->train_timer = RandomRange(TRAIN_TIME_A, TRAIN_TIME_B);
	
	return (StageBack*)this;
}
