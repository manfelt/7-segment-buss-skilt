#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

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

// TODO idiomatisk c: understreker i funksjonsnavn function_name()

/* oppdaterer numeriske verdier til klokketid i mente.
 * dvs at f.eks at om siffer 3 kl[3] = 10 
 * bærer verdien av sifferet over og inkrementerer siffer 2
 * slik at når kl er inkrementert til 13310 blir kl skrudd til 1340.
 */
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

// for testing på at kl inkrementerer slik den skal.
void loop_tid(unsigned int* kl, int i) {
	for (int j=0;j<i;j++) {
		kl[3]++;
		//printf("Tid før: %d%d%d%d\n",kl[0],kl[1],kl[2],kl[3]);
		telleTid(kl);
		//printf("Tid etter: %d%d%d%d\n",kl[0],kl[1],kl[2],kl[3]);
	} 
}

// TODO body for denne funksjonen
void neste_buss(unsigned int* kl, int dag) {

}

// Bygger array av timetabeller gitt oppstartstid og intervaller.
void bygg_timetabeller() {
	unsigned int intervall;
	unsigned int n = 0;
	int dag = MAN;
	unsigned int *st_t = init_klokke();
	unsigned int *sl_t = init_klokke();
	char* start_tid = "0650";
	char* slutt_tid = "2200";

	intervall = 15;

	// konvertere tid fra st_tid/sl_tid til kl
	// -0 char er alternativ for atoi(), manipulerer HEX
	for (int i=0;i<KL_SIFF;i++) {
		st_t[i] = start_tid[i] - '0';
		sl_t[i] = slutt_tid[i] - '0';
	}

	while(st_t[0]<sl_t[0] || st_t[1]<sl_t[1]) {
		n++;
		st_t[3]++;
		telleTid(st_t);
		if (n==intervall) {
			n = 0;
			printf("Bussen går kl: %d%d%d%d\n",st_t[0],st_t[1],st_t[2],st_t[3]);
		}
	}	

	// Konvertere fra kl format til char
	int a[4] = {1,7,4,5};
	int l;
	int index = 0;
	const int len_a = sizeof(a) / sizeof(*a);
	char astr[len_a * 10];
	for (int i=0;i<len_a;i++) {
		index += sprintf( &astr[index], "%d", a[i]);
	}
	printf("ASTR %s\n", astr);

	//loop_tid(st_t);

	free(st_t);
	free(sl_t);
}

// TODO check for dag, for kveldstid.
int sjekkBussStatus(struct Rutetabell rutetabell[], unsigned int* kl, int* dag) {
	unsigned int n = 0;
	unsigned int intervall;

	char* start_tid;
	char* slutt_tid;
	/*
	printf("Timetabell: %i\n",rutetabell->t_t.tidsintervall[0].intervall[0]);
	printf("Start tid: %s\n",rutetabell->t_t.tidsintervall[0].startTid[0]);
	printf("Slutt tid: %s\n",rutetabell->t_t.tidsintervall[0].startTid[1]);
	printf("Ukedag: %i\n",rutetabell->t_t.ukedag[2]);
	printf("Dag: %d\n",*dag);
	*/


	unsigned int *st_t = init_klokke();
	unsigned int *sl_t = init_klokke();

	start_tid = rutetabell->t_t.tidsintervall[0].startTid[0];
	slutt_tid = rutetabell->t_t.tidsintervall[0].startTid[1];

	intervall = rutetabell->t_t.tidsintervall[0].intervall[0];

	// konvertere tid fra st_tid/sl_tid til kl
	// -0 char er alternativ for atoi(), manipulerer HEX
	for (int i=0;i<KL_SIFF;i++) {
		st_t[i] = start_tid[i] - '0';
		sl_t[i] = slutt_tid[i] - '0';
	}

	n = intervall;	
	while(st_t[0]<sl_t[0] || st_t[1]<sl_t[1]) {
		n--;
		st_t[3]++;
		telleTid(st_t);

		if(st_t[0]>=kl[0] && st_t[1]>=kl[1] && st_t[2]>=kl[2] && st_t[3]>=kl[3]) {	
			/*if (st_t[3]==kl[3]) {
				//nedtelling = 		
				printf("klokken er %d%d%d%d, bussen går om %i min, st: %d%d%d%d\n",kl[0],kl[1],kl[2],kl[3], intervall, st_t[0],st_t[1],st_t[2],st_t[3]);
				break;
			} */
			//unsigned int res = 0;
			//if (st_t[3]>=kl[3]) {
			//	res = st_t[3]-kl[3];
			//} else res = 10-kl[3];
			//res = (intervall-kl[3]);
			//printf("klokken er %d%d%d%d, bussen går om %i min, %d%d%d%d\n",kl[0],kl[1],kl[2],kl[3], n, st_t[0],st_t[1],st_t[2],st_t[3]);
			//printf("n: %i\n",n);
			break;
		}

		if (n==0) {
			n = intervall;
		}
	}

	//printf("kl: %d%d%d%d\n",kl[0],kl[1],kl[2],kl[3]);

	free(st_t);
	free(sl_t);

	return n;
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

	loop_tid(kl, 5);

	bygg_timetabeller();

	int ank;
	for(int i=0;i<30;i++) {
		ank = sjekkBussStatus(&rutetabell, kl, dag);
		printf("klokken er %d%d%d%d, bussen går om %i min\n",kl[0],kl[1],kl[2],kl[3], ank);
		sleep(1);
		loop_tid(kl, 1);
	}

	free(kl);
	free(dag);

	return 0;
}
