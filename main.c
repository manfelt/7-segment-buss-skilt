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
	char* startTid;
	unsigned int intervall;
};

struct Timetabell {
	unsigned int ukedag;
	struct Tidsintervaller tidsintervaller[3];
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

int main (int argc, char* argv[]) {

	// Timetabeller: 
	// Dag 1-5
	// 0650 ~ 15 - 2220 ~ 30 til 0020.
	// Dag 6
	// 0750 ~ 30 - 1020 ~ 15 til 0020.
	// Dag 7
	// 0850 ~ 30 til 0020.

	struct  Timetabell timetabell[] = {
		{
			1, 
			{"0650", 15, "2220", 30, "0020"}
		},
		{
			6,
			{"0750", 30}
		},
		{
			7,
			{"0850", 30}
		}
	};

	printf("Timetabell: %s\n",timetabell->tidsintervaller[2].startTid);


	//printf("time_table_entries: %d\n",time_table_entries[1]);

	unsigned int *kl = malloc(KL_SIFF*sizeof(unsigned int));

	enum Dag a;
	a = FRE;
	printf("Dag 5: %d",a);

	for (int i = 0; i < argc; i++) {
		if (i==1) {
			if (strlen(argv[i])!=KL_SIFF) {
				printf("Argumentet skal ha 4 siffer %s\n",argv[i]);
				//continue;
				exit(EXIT_FAILURE);
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
