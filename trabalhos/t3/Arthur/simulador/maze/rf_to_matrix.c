#include <stdio.h>

const char *pernalonga[7][5] = 
{
	{"pl_vazio", "pl_orelha", "pl_vazio", "pl_orelha", "pl_vazio" },
	{"pl_vazio", "pl_orelha", "pl_vazio", "pl_orelha", "pl_vazio" },
	{"pl_vazio", "pl_orelha", "pl_vazio", "pl_orelha", "pl_vazio" },
	{"pl_vazio", "pl_cabeca", "pl_cabeca", "pl_cabeca", "pl_vazio" },
	{"pl_vazio", "pl_olho", "pl_cabeca", "pl_olho", "pl_vazio" },
	{"pl_bigode", "pl_bigode", "pl_bigode", "pl_bigode", "pl_bigode" },
	{"pl_bigode", "pl_bigode", "pl_bigode", "pl_bigode", "pl_bigode" }
};

const char *cenoura[7] =
{
	"pl_vazio", "pl_vazio", "pl_cenoura_cabo", "pl_cenoura", "pl_cenoura", "pl_cenoura"
};

const char *jake[5][5] =
{
	{ "jake_cabeca", "jake_cabeca", "jake_cabeca", "jake_cabeca", "jake_cabeca" },
	{ "jake_cabeca", "jake_olho", "jake_cabeca", "jake_olho", "jake_cabeca" }, 
	{ "jake_cabeca", "jake_bigode", "jake_focinho", "jake_bigode", "jake_cabeca" },
	{ "jake_cabeca", "jake_bigode", "jake_cabeca", "jake_bigode", "jake_cabeca" },
	{ "jake_cabeca", "jake_cabeca", "jake_cabeca", "jake_cabeca", "jake_cabeca" }
};

#define LINES 39
#define COLS  37
int main() {

	FILE *f;
	
	f = fopen("rf", "r");
	
	int i, j;
	int pli, plj;
	int jki, jkj;
	int cni;
	
	pli = plj = jki = jkj = cni = 0;
	for(i = 0; i < LINES; i++) {
		printf("{");
		for(j = 0; j < COLS; j++) {
			switch(fgetc(f)) {
				case ' ' : printf("vazio");
					break;
				case 'R' : printf("red");
					break;
				case 'G' : printf("green");
					break;
				case 'B' : printf("blue");
					break;
				case 'K' : printf("gold");
					break;
				case 'P' : printf("purple");
					break;
				case 'r' : printf("weak_red");
					break;
				case 'g' : printf("weak_green");
					break;
				case 'b' : printf("weak_blue");
					break;
				case 'k' : printf("weak_gold");
					break;
				case 'p' : printf("weak_purple");
					break;
				case 'Q' : printf("purple_switch");
					break;
				case 'D' : printf("glider");
					break;
				case 'W' : printf("wall");
					break;
				case 'L' : printf("%s", pernalonga[pli][plj]);
					if(++plj == 5) { pli++; plj = 0; }
					break;
				case 'C' : printf("%s", cenoura[cni]);
					++cni;
					break;
				case 'J' : printf("%s", jake[jki][jkj]);
					if(++jkj == 5) { jki++; jkj = 0; }
					break;
				default : printf("vazio");
					break;
			}
			if(j != COLS-1) printf(",");
		}
		fgetc(f);
		printf("}");
		if(i != LINES-1) printf(",");
	} printf("\n");

	return 0;
}
