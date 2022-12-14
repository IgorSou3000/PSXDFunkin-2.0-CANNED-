	{ //StageId_1_1 (Bopeebo)
		//Characters
		{Char_BF_New,    FIXED_DEC(60,1),  FIXED_DEC(80,1)},
		{Char_Dad_New, FIXED_DEC(-120,1),  FIXED_DEC(100,1)},
		{Char_GF_New,     FIXED_DEC(0,1),  FIXED_DEC(-12,1)},
		
		//Stage background
		Back_Week1_New,
		
		//Song info
		1, 1,
		XA_Bopeebo, 0,
		
		StageId_1_2, STAGE_LOAD_FLAG
	},
	{ //StageId_1_2 (Fresh)
		//Characters
		{Char_BF_New,    FIXED_DEC(60,1),  FIXED_DEC(80,1)},
		{Char_Dad_New, FIXED_DEC(-120,1),  FIXED_DEC(100,1)},
		{Char_GF_New,     FIXED_DEC(0,1),  FIXED_DEC(-12,1)},
		
		//Stage background
		Back_Week1_New,
		
		//Song info
		1, 2,
		XA_Fresh, 2,
		
		StageId_1_3, STAGE_LOAD_FLAG | STAGE_LOAD_STAGE
	},
	{ //StageId_1_3 (Dadbattle)
		//Characters
		{Char_BF_New,    FIXED_DEC(60,1),  FIXED_DEC(80,1)},
		{Char_Dad_New, FIXED_DEC(-120,1),  FIXED_DEC(100,1)},
		{NULL},
		
		//Stage background
		Back_Week1_New,
		
		//Song info
		1, 3,
		XA_Dadbattle, 0,
		
		StageId_1_3, 0
	},
	{ //StageId_1_4 (Tutorial)
		//Characters
		{Char_BF_New, FIXED_DEC(60,1),  FIXED_DEC(80,1)},
		{Char_GF_New,  FIXED_DEC(0,1),  FIXED_DEC(-15,1)}, //TODO
		{NULL,           FIXED_DEC(0,1),  FIXED_DEC(-12,1)},
		
		//Stage background
		Back_Week1_New,
		
		//Song info
		1, 4,
		XA_Tutorial, 2,
		
		StageId_1_4, 0
	},
	
	{ //StageId_2_1 (Spookeez)
		//Characters
		{Char_BF_New,      FIXED_DEC(56,1),   FIXED_DEC(75,1)},
		{Char_Spook_New,  FIXED_DEC(-90,1),   FIXED_DEC(90,1)},
		{Char_GF_New,       FIXED_DEC(0,1),  FIXED_DEC(-15,1)},
		
		//Stage background
		Back_Week2_New,
		
		//Song info
		2, 1,
		XA_Spookeez, 0,
		
		StageId_2_2, STAGE_LOAD_FLAG
	},
	{ //StageId_2_2 (South)
		//Characters
		{Char_BF_New,      FIXED_DEC(56,1),   FIXED_DEC(75,1)},
		{Char_Spook_New,  FIXED_DEC(-90,1),   FIXED_DEC(90,1)},
		{Char_GF_New,       FIXED_DEC(0,1),  FIXED_DEC(-15,1)},
		
		//Stage background
		Back_Week2_New,
		
		//Song info
		2, 2,
		XA_South, 2,
		
		StageId_2_3, STAGE_LOAD_FLAG 
	},
	{ //StageId_2_3 (Ghastly)
		//Characters
		{Char_BF_New,      FIXED_DEC(56,1),   FIXED_DEC(75,1)},
		{Char_Spook_New,  FIXED_DEC(-90,1),   FIXED_DEC(90,1)},
		{Char_GF_New,       FIXED_DEC(0,1),  FIXED_DEC(-15,1)},
		
		//Stage background
		Back_Week2_New,
		
		//Song info
		2, 3,
		XA_Ghastly, 0,
		
		StageId_2_4, STAGE_LOAD_FLAG | STAGE_LOAD_OPPONENT  | STAGE_LOAD_STAGE | STAGE_LOAD_NOTRANS
	},
	{ //StageId_2_4 (Monster)
		//Characters
		{Char_BF_New,      FIXED_DEC(56,1),   FIXED_DEC(75,1)},
		{Char_Monster_New,  FIXED_DEC(-160,1),   FIXED_DEC(85,1)},
		{Char_GF_New,       FIXED_DEC(0,1),  FIXED_DEC(-15,1)},
		
		//Stage background
		Back_Week2_New,
		
		//Song info
		2, 4,
		XA_Monster, 2,
		
		StageId_2_4, 0
	},
	
	{ //StageId_3_1 (Pico)
		//Characters
		{Char_BF_New,     FIXED_DEC(56,1),   FIXED_DEC(85,1)},
		{Char_Pico_New, FIXED_DEC(-85,1),   FIXED_DEC(85,1)},
		{Char_GF_New,      FIXED_DEC(0,1),  FIXED_DEC(-15,1)},
		
		//Stage background
		Back_Week3_New,
		
		//Song info
		3, 1,
		XA_Pico, 0,
		
		StageId_3_2, STAGE_LOAD_FLAG
	},
	{ //StageId_3_2 (Philly)
		//Characters
		{Char_BF_New,     FIXED_DEC(56,1),   FIXED_DEC(85,1)},
		{Char_Pico_New, FIXED_DEC(-85,1),   FIXED_DEC(85,1)},
		{Char_GF_New,      FIXED_DEC(0,1),  FIXED_DEC(-15,1)},
		
		//Stage background
		Back_Week3_New,
		
		//Song info
		3, 2,
		XA_Philly, 2,
		
		StageId_3_3, STAGE_LOAD_FLAG
	},
	{ //StageId_3_3 (Blammed)
		//Characters
		{Char_BF_New,     FIXED_DEC(56,1),   FIXED_DEC(85,1)},
		{Char_Pico_New, FIXED_DEC(-85,1),   FIXED_DEC(85,1)},
		{Char_GF_New,      FIXED_DEC(0,1),  FIXED_DEC(-15,1)},
		
		//Stage background
		Back_Week3_New,
		
		//Song info
		3, 3,
		XA_Blammed, 0,
		
		StageId_3_3, 0
	},
	
	{ //StageId_4_1 (Satin Panties)
		//Characters
		{Char_BF_New,   FIXED_DEC(120,1),   FIXED_DEC(40,1)},
		{Char_Mom_New, FIXED_DEC(-120,1),  FIXED_DEC(100,1)},
		{Char_GF_New,    FIXED_DEC(-6,1),   FIXED_DEC(-5,1)},
		
		//Stage background
		Back_Week4_New,
		
		//Song info
		4, 1,
		XA_SatinPanties, 0,
		
		StageId_4_2, STAGE_LOAD_FLAG
	},
	{ //StageId_4_2 (High)
		//Characters
		{Char_BF_New,   FIXED_DEC(120,1),   FIXED_DEC(40,1)},
		{Char_Mom_New, FIXED_DEC(-120,1),  FIXED_DEC(100,1)},
		{Char_GF_New,    FIXED_DEC(-6,1),   FIXED_DEC(-5,1)},
		
		//Stage background
		Back_Week4_New,
		
		//Song info
		4, 2,
		XA_High, 2,
		
		StageId_4_3, STAGE_LOAD_FLAG | STAGE_LOAD_OPPONENT | STAGE_LOAD_STAGE | STAGE_LOAD_GIRLFRIEND
	},
	{ //StageId_4_3 (Awooga)
		//Characters
		{Char_BF_New,   FIXED_DEC(120,1),   FIXED_DEC(40,1)},
		{Char_Mom_New, FIXED_DEC(-120,1),  FIXED_DEC(100,1)},
		{Char_GF_New,    FIXED_DEC(-6,1),   FIXED_DEC(-5,1)},
		
		//Stage background
		Back_Week4_New,
		
		//Song info
		4, 3,
		XA_Awooga, 0,
		
		StageId_4_4, STAGE_LOAD_FLAG
	},
	{ //StageId_4_4 (MILF)
		//Characters
		{Char_BF_New,   FIXED_DEC(120,1),   FIXED_DEC(40,1)},
		{Char_Mom_New, FIXED_DEC(-120,1),  FIXED_DEC(100,1)},
		{Char_GF_New,    FIXED_DEC(-6,1),   FIXED_DEC(-5,1)},
		
		//Stage background
		Back_Week4_New,
		
		//Song info
		4, 4,
		XA_MILF, 2,
		
		StageId_4_4, 0
	},
	
	{ //StageId_5_1 (Green Eggs)
		//Characters
		{Char_XmasBF_New,  FIXED_DEC(90,1),   FIXED_DEC(85,1)},
		{Char_XmasP_New, FIXED_DEC(-190,1),   FIXED_DEC(90,1)},
		{NULL,              FIXED_DEC(0,1),  FIXED_DEC(-15,1)},
		
		//Stage background
		Back_Week5_New,
		
		//Song info
		5, 1,
		XA_Green_Eggs, 0,
		
		StageId_5_2, STAGE_LOAD_FLAG
	},
	{ //StageId_5_2 (Ham)
		//Characters
		{Char_XmasBF_New,  FIXED_DEC(90,1),   FIXED_DEC(85,1)},
		{Char_XmasP_New, FIXED_DEC(-190,1),   FIXED_DEC(90,1)},
		{NULL,              FIXED_DEC(0,1),  FIXED_DEC(-15,1)},
		
		//Stage background
		Back_Week5_New,
		
		//Song info
		5, 2,
		XA_Ham, 2,
		
		StageId_5_3, STAGE_LOAD_FLAG | STAGE_LOAD_OPPONENT | STAGE_LOAD_STAGE
	},
	{ //StageId_5_3 (Feaster)
		//Characters
		{Char_XmasBF_New, FIXED_DEC(105,1),  FIXED_DEC(100,1)},
		{Char_MonsterX_New,   FIXED_DEC(-120,1),  FIXED_DEC(100,1)},
		{NULL,              FIXED_DEC(0,1),  FIXED_DEC(-15,1)},
		
		//Stage background
		Back_Week5_New,
		
		//Song info
		5, 3,
		XA_Feaster, 0,
		
		StageId_5_3, 0
	},
	
	{ //StageId_6_1 (Senpai)
		//Characters
		{Char_BFWeeb_New,  FIXED_DEC(52,1),  FIXED_DEC(50,1)},
		{Char_Senpai_New, FIXED_DEC(-60,1),  FIXED_DEC(50,1)},
		{Char_GFWeeb_New,   FIXED_DEC(0,1),  FIXED_DEC(39,1)},
		
		//Stage background
		Back_Week6_New,
		
		//Song info
		6, 1,
		XA_Senpai, 0,
		
		StageId_6_2, STAGE_LOAD_FLAG | STAGE_LOAD_OPPONENT
	},
	{ //StageId_6_2 (Roses)
		//Characters
		{Char_BFWeeb_New,   FIXED_DEC(52,1),  FIXED_DEC(50,1)},
		{Char_SenpaiM_New, FIXED_DEC(-60,1),  FIXED_DEC(50,1)},
		{Char_GFWeeb_New,    FIXED_DEC(0,1),  FIXED_DEC(39,1)},
		
		//Stage background
		Back_Week6_New,
		
		//Song info
		6, 2,
		XA_Roses, 2,
		
		StageId_6_3, STAGE_LOAD_FLAG | STAGE_LOAD_OPPONENT | STAGE_LOAD_STAGE
	},
	{ //StageId_6_3 (Thorns)
		//Characters
		{Char_BFWeeb_New,  FIXED_DEC(52,1),  FIXED_DEC(50,1)},
		{Char_Spirit_New, FIXED_DEC(-60,1),  FIXED_DEC(50,1)},
		{Char_GFWeeb_New,   FIXED_DEC(0,1),  FIXED_DEC(39,1)},
		
		//Stage background
		Back_Week6_New,
		
		//Song info
		6, 3,
		XA_Thorns, 0,
		
		StageId_6_3, 0
	},
	{ //StageId_Bonus1_1 (Too Slow)
		//Characters
		{Char_BF_New,   FIXED_DEC(120,1),   FIXED_DEC(40,1)},
		{Char_Mom_New, FIXED_DEC(-120,1),  FIXED_DEC(100,1)},
		{Char_GF_New,    FIXED_DEC(-6,1),   FIXED_DEC(-5,1)},
		
		//Stage background
		Back_Week4_New,
		
		//Song info
		0x80, 1,
		XA_Too_Slow, 0,
		
		StageId_Bonus1_1, 0
	},
	{ //StageId_Bonus1_2 (Endless)
		//Characters
		{Char_BF_New,   FIXED_DEC(120,1),   FIXED_DEC(40,1)},
		{Char_Mom_New, FIXED_DEC(-120,1),  FIXED_DEC(100,1)},
		{Char_GF_New,    FIXED_DEC(-6,1),   FIXED_DEC(-5,1)},
		
		//Stage background
		Back_Week4_New,
		
		//Song info
		0x80, 2,
		XA_Endless, 2,
		
		StageId_Bonus1_2, 0
	},
	{ //StageId_Bonus1_3 (Cycles)
		//Characters
		{Char_BF_New,   FIXED_DEC(120,1),   FIXED_DEC(40,1)},
		{Char_Mom_New, FIXED_DEC(-120,1),  FIXED_DEC(100,1)},
		{Char_GF_New,    FIXED_DEC(-6,1),   FIXED_DEC(-5,1)},
		
		//Stage background
		Back_Week4_New,
		
		//Song info
		0x80, 3,
		XA_Cycles, 0,
		
		StageId_Bonus1_3, 0
	},
	{ //StageId_Bonus1_4 (Milk)
		//Characters
		{Char_BF_New,   FIXED_DEC(120,1),   FIXED_DEC(40,1)},
		{Char_Mom_New, FIXED_DEC(-120,1),  FIXED_DEC(100,1)},
		{Char_GF_New,    FIXED_DEC(-6,1),   FIXED_DEC(-5,1)},
		
		//Stage background
		Back_Week4_New,
		
		//Song info
		0x80, 4,
		XA_Milk, 2,
		
		StageId_Bonus1_4, 0
	},
	{ //StageId_Bonus2_1 (DGuy)
		//Characters
		{Char_BF_New,   FIXED_DEC(120,1),   FIXED_DEC(40,1)},
		{Char_Mom_New, FIXED_DEC(-120,1),  FIXED_DEC(100,1)},
		{Char_GF_New,    FIXED_DEC(-6,1),   FIXED_DEC(-5,1)},
		
		//Stage background
		Back_Week4_New,
		
		//Song info
		0x81, 1,
		XA_DGuy, 0,
		
		StageId_Bonus2_1, 0
	},
	{ //StageId_Bonus2_2 (Lore)
		//Characters
		{Char_BF_New,   FIXED_DEC(120,1),   FIXED_DEC(40,1)},
		{Char_Mom_New, FIXED_DEC(-120,1),  FIXED_DEC(100,1)},
		{Char_GF_New,    FIXED_DEC(-6,1),   FIXED_DEC(-5,1)},
		
		//Stage background
		Back_Week4_New,
		
		//Song info
		0x81, 2,
		XA_Lore, 2,
		
		StageId_Bonus2_2, 0
	},
	{ //StageId_Bonus3_1 (God Feast)
		//Characters
		{Char_BF_New,   FIXED_DEC(120,1),   FIXED_DEC(40,1)},
		{Char_Mom_New, FIXED_DEC(-120,1),  FIXED_DEC(100,1)},
		{Char_GF_New,    FIXED_DEC(-6,1),   FIXED_DEC(-5,1)},
		
		//Stage background
		Back_Week4_New,
		
		//Song info
		0x82, 1,
		XA_God_Feast, 0,
		
		StageId_Bonus3_1, 0
	},