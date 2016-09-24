#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define POT_MAX 6
#define N_SEQ 4
#define SEQ1 "0d1d2d3d4d5d6d7d8d9d"
#define SEQ2 "9e8e7e6e5e4e2e3e1e0e"
#define SEQ3 "4e3e2e1e0e5d6d7d8d9d"
#define SEQ4 "4e9d1e2d6e7d0e3d5e8d"
#define NME_ARQ1 "BDAlunos10e?v?.txt"
#define FMT_REG1 "%.?ld | Aluno mat. %.?ld | %.?ld@ffb.edu.br | 9%.3ld.%.4ld\n"
#define NME_ARQ2 "PesqAlunos10e?.txt"
#define FMT_REG2 "%.?ld\n"

int main() {
	FILE * f1, * f2;
	char nome1[] = NME_ARQ1, nome2[] = NME_ARQ2;
	char fmt1[] = FMT_REG1, fmt2[] = FMT_REG2;
	char *seq[] = {SEQ1, SEQ2, SEQ3, SEQ4};
	int i, p, s, dig, dir, inc[] = {1,-1};
	long j, n, mat, cpl[] = {0,0};
	fmt1[2] = fmt1[21] = fmt1[29] = fmt2[2] = '0'+POT_MAX+1;
	for (s = 0; s < N_SEQ; s++) {
		nome1[13] = '1'+s;
		for (p = 1, cpl[1]=0; p <= POT_MAX; p++, cpl[1]=cpl[1]*10+9) {
			nome1[11] = nome2[13] = '0'+p;
			f1 = fopen(nome1, "w");
			for (i=0, n=pow(10,p-1); i<20; i+=2) {
				for (j=0, dig=seq[s][i]-'0', dir=seq[s][i+1]-'d', mat = dig*n+cpl[dir]+1; j<n; j++, mat+=inc[dir]) {
					fprintf(f1, fmt1, mat, mat, mat, mat/(long)1e4, mat%(long)1e4);
				}
			}
			fclose(f1);
			f2 = fopen(nome2, "w");
			for (n=pow(10,p), mat = 1; mat<=n; mat++) {
				fprintf(f2, fmt2, mat);
			}
			fclose(f2);
		}
	}
}