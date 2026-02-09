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
	char* stopp;
	struct Timetabell t_t;	
	// TODO Retning->||<-
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
	printf("Timetabell: %i\n",rutetabell->t_t.tidsintervall[0].intervall[0]);
	printf("Ukedag: %i\n",rutetabell->t_t.ukedag[2]);
}

void error_exit(char *msg)  {
	perror(msg);
	exit(EXIT_FAILURE);
}

void * init_klokke() {
	unsigned int *kl = malloc(KL_SIFF*sizeof(unsigned int));	
	return kl;
}

void * start_dag(int i) {
	int *dag = malloc(sizeof(int));
	*dag = i;
	return dag;
}

void loop_tid(unsigned int t[4]) {
	for (int i=0;i<6;i++) {
		t[3]++;
		printf("Tid før: %d%d%d%d\n",t[0],t[1],t[2],t[3]);
		telleTid(t);
		printf("Tid etter: %d%d%d%d\n",t[0],t[1],t[2],t[3]);
	} 
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

	struct Rutetabell rutetabell = {
		66,
		"Klosterheim",
		t_t[0],
	};

	sjekkBussStatus(&rutetabell);

	unsigned int *kl = init_klokke();
	int *dag = start_dag(4);
	if (kl==NULL||dag==NULL) error_exit("memory alloc failed");

	printf("Dag: %d\n",*dag);
	enum Dag a;
	a = SØN;
	printf("SØN : %d",a);

	for (int i = 0; i < argc; i++) {
		if (i == 1) {
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
		} else {printf("Kun 1 arg \n");}
		printf("argument in: %s\n", argv[i]);
	}

	loop_tid(kl);

	free(kl);
	free(dag);

	return 0;
}
