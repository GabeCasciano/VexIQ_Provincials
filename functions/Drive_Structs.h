//Written by Vincent liu
//Debugged by Vincent liu

enum arm_def {Nothing, BTOM = 0, YELO = 790, TOP = 934, BARM = -140, lvl2 = 380, lvl3 = 590};
enum spike_def {Nothing, Spike1 = -280, Spike2 = -130, Spike3 = 0};
enum TN_urbo {Fast, Slow};
enum NURBO {Angry, Sad, Unused, OK, Good, Liked, Happy};

typedef struct{
	int Lspiker;
	int Rspiker;
	bool yesL;
	bool yesL2;
	bool yesR;
	bool yesR2;
	spike_def spikes;
}Spike_def;

typedef struct{
	int x;
	int y;
	int left;
	int right;
	arm_def arms;
	TN_urbo speed;
	NURBO TURBO;
}Control_def;

typedef struct{
	int lspik;
	int rspik;
	bool Sped;
	float mult;
}Calc_def;

Spike_def *spik;
Control_def *cntrl;
Calc_def *values;
