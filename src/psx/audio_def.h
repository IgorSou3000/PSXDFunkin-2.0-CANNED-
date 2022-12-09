#define XA_LENGTH(x) (((u64)(x) * 75) / 100 * IO_SECT_SIZE) //Centiseconds to sectors in bytes (w)

typedef struct
{
	XA_File file;
	u32 length;
} XA_TrackDef;

static const XA_TrackDef xa_tracks[] = {
	//MENU.XA
	{XA_Menu, XA_LENGTH(11295)}, //XA_GettinFreaky
	{XA_Menu, XA_LENGTH(3840)},  //XA_GameOver
	//WEEK1A.XA
	{XA_Week1A, XA_LENGTH(8400)}, //XA_Bopeebo
	{XA_Week1A, XA_LENGTH(10200)}, //XA_Fresh
	//WEEK1B.XA
	{XA_Week1B, XA_LENGTH(11300)}, //XA_Dadbattle
	{XA_Week1B, XA_LENGTH(6200)}, //XA_Tutorial
	//WEEK2A.XA
	{XA_Week2A, XA_LENGTH(9100)}, //XA_Spookeez
	{XA_Week2A, XA_LENGTH(9000)}, //XA_South
	//WEEK2B.XA
	{XA_Week2B, XA_LENGTH(11200)}, //XA_Ghastly
	{XA_Week2B, XA_LENGTH(14800)}, //XA_Monster
	//WEEK3A.XA
	{XA_Week3A, XA_LENGTH(8800)},  //XA_Pico
	{XA_Week3A, XA_LENGTH(10300)}, //XA_Philly
	//WEEK3B.XA
	{XA_Week3B, XA_LENGTH(10300)}, //XA_Blammed
	//WEEK4A.XA
	{XA_Week4A, XA_LENGTH(10500)},  //XA_SatinPanties
	{XA_Week4A, XA_LENGTH(12900)}, //XA_High
	//WEEK4B.XA
	{XA_Week4B, XA_LENGTH(11600)}, //XA_Awooga
	{XA_Week4B, XA_LENGTH(11800)}, //XA_MILF
	//WEEK5A.XA
	{XA_Week5A, XA_LENGTH(13300)}, //XA_Green_Eggs
	{XA_Week5A, XA_LENGTH(12200)},  //XA_Ham
	//WEEK5B.XA
	{XA_Week5B, XA_LENGTH(19800)}, //XA_Feaster
	//WEEK6A.XA
	{XA_Week6A, XA_LENGTH(10000)}, //XA_Senpai
	{XA_Week6A, XA_LENGTH(8928)}, //XA_Roses
	//WEEK6B.XA
	{XA_Week6B, XA_LENGTH(10298)}, //XA_Thorns
	//BONUSA.XA
	{XA_BonusA, XA_LENGTH(14300)}, //XA_Too_Slow
	{XA_BonusA, XA_LENGTH(14900)}, //XA_Endless
	//BONUSB.XA
	{XA_BonusB, XA_LENGTH(32400)}, //XA_Cycles
	{XA_BonusB, XA_LENGTH(15500)}, //XA_Milk
	//BONUSC.XA
	{XA_BonusC, XA_LENGTH(12000)}, //XA_DGuy
	{XA_BonusC, XA_LENGTH(18900)}, //XA_Lore
	//BONUSD.XA
	{XA_BonusD, XA_LENGTH(18700)}, //XA_God_Feast
};

static const char *xa_paths[] = {
	"\\SONGS\\MENU.XA;1",   //XA_Menu
	"\\SONGS\\WEEK1A.XA;1", //XA_Week1A
	"\\SONGS\\WEEK1B.XA;1", //XA_Week1B
	"\\SONGS\\WEEK2A.XA;1", //XA_Week2A
	"\\SONGS\\WEEK2B.XA;1", //XA_Week2B
	"\\SONGS\\WEEK3A.XA;1", //XA_Week3A
	"\\SONGS\\WEEK3B.XA;1", //XA_Week3B
	"\\SONGS\\WEEK4A.XA;1", //XA_Week4A
	"\\SONGS\\WEEK4B.XA;1", //XA_Week4B
	"\\SONGS\\WEEK5A.XA;1", //XA_Week5A
	"\\SONGS\\WEEK5B.XA;1", //XA_Week5B
	"\\SONGS\\WEEK6A.XA;1", //XA_Week6A
	"\\SONGS\\WEEK6B.XA;1", //XA_Week6B
	"\\SONGS\\BONUSA.XA;1", //XA_BonusA
	"\\SONGS\\BONUSB.XA;1", //XA_BonusB
	"\\SONGS\\BONUSC.XA;1", //XA_BonusC
	"\\SONGS\\BONUSD.XA;1", //XA_BonusD
	NULL,
};
