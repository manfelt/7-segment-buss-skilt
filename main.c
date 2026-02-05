#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KVARTER 15
#define HALVTIME 30
#define KL_SIFF 4

enum Dag {
	MAN = 1,
	TIR,
	ONS, 
	TOR,
	FRE,
	LØR,
	SØN
};

struct Tidsintervaller {
	char* startTid[3];
	unsigned int intervall[2];
};

struct Timetabell {
	unsigned int ukedag[3];
	struct Tidsintervaller tidsintervall[3];
};

struct Rutetabell {
	unsigned int buss;
	enum Dag dag;
	char* stopp;	
};

// TODO idiomatisk c; understreker i funksjonsnavn function_name()

// kontrollerer klokketid.
void telleTid(int *kl) {
	if (kl[3]>=10) {
		kl[2]++;
		kl[3]=0;
	}
	if (kl[2]==6) {
		kl[1]++;
		kl[2]=0;
	}
	if (kl[2]>=10&&kl[0]==0) {
		kl[0]++;
		kl[2]=0;
	}
	if (kl[1]>=10) {
		kl[0]++;
		kl[1]=0;
	}
	if (kl[0]==2&&kl[1]==4) {
		kl[0]=0;
		kl[1]=0;
	}
}

// TODO check up mot busstabell
void sjekkBussStatus(struct Rutetabell rutetabell[]) {

}

/* void setup(struct Tidsintervaller t[]) {
//struct Tidsintervaller* t[2];
t = malloc((3) * sizeof(struct Tidsintervaller));

t = {
		1,{"0650","2220","0020"},{15,30},
		//{6,{"0750","0020"},{30,15}},
		//{7,{"0850","0020"},{30}}
	};

	printf("Timetabell: %i\n",timetabell->tidsintervall[0].intervall[1]);

}
*/

void error_exit(char *msg)  {
	perror(msg);
	exit(EXIT_FAILURE);
}


// TODO 
void init_klokke() {


}


int main (int argc, char* argv[]) {

	// Timetabeller: 
	// Dag 1-5
	// 0650 ~ 15 - 2220 ~ 30 til 0020.
	// Dag 6
	// 0750 ~ 30 - 1020 ~ 15 til 0020.
	// Dag 7
	// 0850 ~ 30 til 0020.

	struct Tidsintervaller t[3] = {
		{"0650","2220","0020",15,30},
		{"0750","1020","0020",30,15},	
		{"0850","0850","0020",30,30},	
	};

	printf("Tidsintervaller: %d \n",t[2].intervall[0]);

	struct Timetabell t_t[3] = {
		1,6,7,
		t[0],t[1],t[2],
	};

	printf("Timetabell: %i\n",t_t->tidsintervall[0].intervall[0]);
	printf("Ukedag: %i\n",t_t->ukedag[2]);

	unsigned int *kl = malloc(KL_SIFF*sizeof(unsigned int));

	enum Dag a;
	a = SØN;
	printf("SØN : %d",a);

	// TODO alternativt: 
	// if (argc == 1 || argc >2)usage();
	// else if (argv[1] <=0 || argv[1] >5)usage();
	for (int i = 0; i < argc; i++) {
		if (argc == 1 || argc >2) {
			if (strlen(argv[i])!=KL_SIFF) {
				error_exit("Argument 1 skal ha 4 siffere!");
			} else {
				char* arg = argv[i];
				for (int j=0;j<strlen(arg);j++) {
					//printf("arg: %c\n",arg[j]);
					kl[j] = arg[j] - '0';
					printf("kl: %d\n",kl[j]);
				}
			}
		}
		printf("%s\n", argv[i]);
	}

	// loop tid
	for (int i=0;i<6;i++) {
		kl[3]++;
		printf("Tid før: %d%d%d%d\n",kl[0],kl[1],kl[2],kl[3]);
		telleTid(kl);
		printf("Tid etter: %d%d%d%d\n",kl[0],kl[1],kl[2],kl[3]);
	} 


	free(kl);

	return 0;
}
