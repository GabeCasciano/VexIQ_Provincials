//Written by Vincent liu
//Debugged by Vincent liu

typedef struct{
	int Lspiker;
	int Rspiker;
	bool yesL;
	bool yesL2;
	bool yesR;
	bool yesR2;
}Spike_def;

typedef struct{
	string TURBO;
	int x;
	int y;
	int left;
	int right;
}Control_def;

Spike_def *spik;
Control_def *cntrl;
