/*
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include "week1.h"

#include "psx/archive.h"
#include "psx/mem.h"
#include "stage/stage.h"

//Week 1 background structure
typedef struct
{
	//Stage background base structure
	StageBack back;
	
	//Textures
	Gfx_Tex tex_back0; //Stage back 1
	Gfx_Tex tex_back1; //Stage back 2
	Gfx_Tex tex_back2; //Stage front
	Gfx_Tex tex_bopper; //Boppers
} Back_Week1;

//Week 1 functions
void Back_Week1_Tick(StageBack *back)
{
	//Back_Week1 *this = (Back_Week1*)back;
	(void)back; //Only for remove warning

	//Stage specific events
	if (stage.flag & STAGE_FLAG_JUST_STEP)
	{
		switch (stage.stage_id)
		{
			case StageId_1_1:
				//BF peace
				if (stage.song_step >= 0 && (stage.song_step % 32) == 28)
					stage.player->set_anim(stage.player, PlayerAnim_Peace);
				break;
			case StageId_1_2:
				//GF bopping
				switch (stage.song_beat)
				{
					case 16:
						stage.gf_speed = 8;
						break;
					case 48:
						stage.gf_speed = 4;
						break;
					case 80:
						stage.gf_speed = 8;
						break;
					case 112:
						stage.gf_speed = 4;
						break;
				}
				break;
			case StageId_1_4:
				//BF and GF peace + cheer
				stage.gf_speed = 8;
				if (stage.song_step > 64 && stage.song_step < 192 && (stage.song_step % 64) == 60)
				{
					stage.player->set_anim(stage.player, PlayerAnim_Peace);
					stage.opponent->set_anim(stage.opponent, CharAnim_UpAlt);
				}
				break;
			default:
				break;
		}
	}
}
void Back_Week1_DrawFG(StageBack *back)
{
	Back_Week1 *this = (Back_Week1*)back;
	
	fixed_t fx, fy;

	fixed_t beat_bop;
	if ((stage.song_step % 0x4) == 0)
		beat_bop = FIXED_UNIT - ((stage.note_scroll / 24) & FIXED_LAND);
	else
		beat_bop = 0;

	fx = stage.camera.x;
	fy = stage.camera.y;

	//Draw Whitty and Carol
	RECT whirol_src = {0, 0, 252, 124};
	RECT_FIXED whirol_dst = {
			FIXED_DEC(-45,1) - fx - (beat_bop * 2),
			FIXED_DEC(40,1) -  fy + (beat_bop * 4),
			FIXED_DEC(252,1) + (beat_bop * 4),
			FIXED_DEC(124,1) - (beat_bop * 4),
  };
	Stage_DrawTex(&this->tex_bopper, &whirol_src, &whirol_dst, stage.camera.bzoom);

	//Draw Booper 2 (sorry, i don't have sure who are these guys)
	RECT bopper2_src = {0,130, 252, 107};
	RECT_FIXED bopper2_dst = {
			FIXED_DEC(-300,1) - fx - (beat_bop * 2),
			FIXED_DEC(58,1) -  fy + (beat_bop * 4),
			FIXED_DEC(252,1) + (beat_bop * 4),
			FIXED_DEC(107,1) - (beat_bop * 4),
  };
	Stage_DrawTex(&this->tex_bopper, &bopper2_src, &bopper2_dst, stage.camera.bzoom);
}

void Back_Week1_DrawBG(StageBack *back)
{
	Back_Week1 *this = (Back_Week1*)back;
	
	fixed_t fx, fy, fscroll;
	
	fscroll = FIXED_DEC(9,10);

	fx = FIXED_MUL(stage.camera.x, fscroll);
	fy = FIXED_MUL(stage.camera.y, fscroll);

	//Draw stage front
	RECT front_src = {0, 0, 224, 68};
	RECT_FIXED front_dst = {
		FIXED_DEC(-230,1) - fx,
		FIXED_DEC(60,1) - fy,
		FIXED_DEC(224,1),
		FIXED_DEC(68 + 8,1)
	};
	
	Stage_DrawTex(&this->tex_back2, &front_src, &front_dst, stage.camera.bzoom);

	//Draw the second part of stage front
	front_src.y += front_src.h;
	front_dst.x += front_dst.w;

	Stage_DrawTex(&this->tex_back2, &front_src, &front_dst, stage.camera.bzoom);
	
	//Draw stage back
	RECT back_src = {0, 0, 220, 248};
	RECT_FIXED back_dst = {
		FIXED_DEC(-230,1) - fx,
		FIXED_DEC(-160,1) - fy,
		FIXED_DEC(220,1),
		FIXED_DEC(248,1)
	};
	
	Stage_DrawTex(&this->tex_back0, &back_src, &back_dst, stage.camera.bzoom);

	//Draw the second part of stage back
	back_dst.x += back_dst.w;

	Stage_DrawTex(&this->tex_back1, &back_src, &back_dst, stage.camera.bzoom);
}

void Back_Week1_Free(StageBack *back)
{
	Back_Week1 *this = (Back_Week1*)back;
	
	//Free structure
	Mem_Free(this);
}

StageBack *Back_Week1_New(void)
{
	//Allocate background structure
	Back_Week1 *this = (Back_Week1*)Mem_Alloc(sizeof(Back_Week1));
	if (this == NULL)
		return NULL;
	
	//Set background functions
	this->back.tick = Back_Week1_Tick;
	this->back.draw_fg = (stage.darkstage) ? Back_Week1_DrawFG : NULL; //Draw bopper if it the dark stage
	this->back.draw_md = NULL;
	this->back.draw_bg =  Back_Week1_DrawBG;
	this->back.free = Back_Week1_Free;

	//Load HUD textures
	Gfx_LoadTex(&stage.tex_hud0, IO_Read("\\STAGE\\HUD0.TIM;1"), GFX_LOADTEX_FREE);
	Gfx_LoadTex(&stage.tex_hud1, IO_Read("\\STAGE\\HUD1.TIM;1"), GFX_LOADTEX_FREE);
	Gfx_LoadTex(&stage.tex_hud2, IO_Read("\\STAGE\\HUD2.TIM;1"), GFX_LOADTEX_FREE);
	
	IO_Data arc_back;

	//Load background textures
	if (stage.darkstage)
		arc_back = IO_Read("\\WEEK1\\DARKBACK.ARC;1"); //Use the dark variation
	else
		arc_back = IO_Read("\\WEEK1\\BACK.ARC;1");

	Gfx_LoadTex(&this->tex_back0, Archive_Find(arc_back, "back0.tim"), 0);
	Gfx_LoadTex(&this->tex_back1, Archive_Find(arc_back, "back1.tim"), 0);
	Gfx_LoadTex(&this->tex_back2, Archive_Find(arc_back, "back2.tim"), 0);

	if (stage.darkstage)
		Gfx_LoadTex(&this->tex_bopper, Archive_Find(arc_back, "bopper.tim"), 0);

	Mem_Free(arc_back);
	
	return (StageBack*)this;
}
