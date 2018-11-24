
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

typedef struct llist {
	int value;
	struct llist *pointer;
} LLIST;

LLIST *e = NULL;
LLIST *d = NULL;

int empty();
int enqueue(int);
int dequeue();
float ASPL(int**, int, int);
void voltage_graph(int, int, int, int*, int*, int,float);
void file_voltage_test(int**, int, int, float, int, int, int);




main() {
	clock_t start, end;
	start = clock();
	//�錾����������������������������������������������������
	int degree,nodes, x, y, z, pp, pq;
	int i1, i2, i3;
	float aspl= 5.176015;
	///////////////////////////////////////////////////////////

	//�t�@�C���n��������������������������������������������������������������������������
	FILE *fp;
	char file[100];
	sprintf_s(file, 100, "20000 11 4.442472 (x = 100, y = 100, z = 23) (pp = 3, pq = 5) n = 2");
	int err = fopen_s(&fp, file, "r");
	if (err != 0)
		printf("aaa");
	
	fscanf_s(fp, "%d %d %d %d %d %d %d", &degree, &nodes, &x, &y, &z, &pp, &pq);
	
	int *gyakugen_voltage = (int *)malloc(nodes * sizeof(int));
	int *voltage = (int *)malloc(degree * sizeof(int));
	i3 = 0;
	printf("a");
	while (fscanf_s(fp, "%d %d", &i1, &i2) != EOF) {
		voltage[i3] = i1;
		gyakugen_voltage[i3] = i2;
		i3++;
	}
	printf("a");
	/*
	for (i1 = 0;i1 < degree;i1++) {
		printf("%d ", voltage[i1]);
	}printf("\n");*/
	for (i1 = 0;i1 < degree;i1++) {
		//if (i1 >= pp + pq)
			//gyakugen_voltage[i1] = gyakugen_voltage[i1] + nodes;
		printf("%6d ", gyakugen_voltage[i1]);
		if((i1+1) %9 == 0)
			printf("\n");
	}printf("\n");
	//////////////////////////////////////////////////////////////////////////////////////

	


	voltage_graph(x, y, z, gyakugen_voltage, voltage, degree,aspl);

	//���ԕ\��������������������������������������������������������������
	end = clock();
	printf("%.2f�b������܂���\n", (double)(end - start) / CLOCKS_PER_SEC);
	///////////////////////////////////////////////////////////////////////
}

void voltage_graph(int x, int y, int z,int* gyakugen_voltage, int *voltage, int degree,float aspl) {
	int n = 2, nodes;
	nodes = x * y * n;
	int uuu = 0, count = 0, LA, MOD, RAD;
	int i, j = 0, k = 0, l = 0, m = 0;
	//float aspl;
	//���I�m��

	int *pgqhp = (int *)malloc(x * y * degree * sizeof(int));//pgqh
	int *pgqhga = (int *)malloc(x * y * degree * sizeof(int));
	int *pgqhgb = (int *)malloc(x * y * degree * sizeof(int));
	int *pgqhq = (int *)malloc(x * y * degree * sizeof(int));
	int *pgqhha = (int *)malloc(x * y * degree * sizeof(int));
	int *pgqhhb = (int *)malloc(x * y * degree * sizeof(int));
	int **a = (int **)malloc(nodes * sizeof(int));
	for (i = 0; i < nodes; i++)
		a[i] = (int*)malloc(degree * sizeof(int));
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//E�{��
	for (i = 0;i < 3; i++) {//�S�Ă̕ӂ�T��
		for (j = 0; j < degree; j++) {//�S�Ẵ{���e�[�W��T��
			if (gyakugen_voltage[j]/(x*y) == i) {//�e�m�[�h�ɂ��Ă���{���e�[�W�����Z

				do {
					LA = z % x;
					for (MOD = 0; MOD < (count % y);MOD++)
						LA = (LA * z) % x;

					pgqhga[k] = count / y;    //Ga
					pgqhgb[k] = count % y;	  //Gb
					pgqhha[k] = (count / y + LA * (gyakugen_voltage[j]%(x*y)/y) % x) % x; //Ha
					pgqhhb[k] = (count % y + (gyakugen_voltage[j]%y)) % y;		  //Hb

					if (i == 0) {
						pgqhp[k] = 1;
						pgqhq[k] = 1;
					}

					else if (i == 1) {
						pgqhp[k] = 0;
						pgqhq[k] = 1;
					}
					else if (i == 2) {
						pgqhp[k] = 0;
						pgqhq[k] = 0;
					}

					k++;
					count++;
				} while (k % (x * y) != 0);
				count = 0;
			}
		}
	}

	for (i = 0;i < x*y*n;i++) {
		for (j = 0;j < degree;j++) {
			a[i][j] = -1;
		}
	}

	for (i = 0;i < x*y*degree; i++) {
		for (j = 0;j < x*y*n;j++) {
			if (pgqhp[i] == (int)(j / (x*y)) && pgqhga[i] == (j % (x*y) / y) && pgqhgb[i] == j % y) {

				for (RAD = 0; RAD < x*y*n; RAD++) {
					if (pgqhq[i] == (int)(RAD / (x*y)) && pgqhha[i] == (RAD % (x*y) / y) && pgqhhb[i] == RAD % y) {
						m = 0;

						while (a[j][m] != -1) {
							m++;
						}

						a[j][m] = RAD;
					}
				}
			}
		}
	}

	free(pgqhp);
	free(pgqhga);
	free(pgqhgb);
	free(pgqhq);
	free(pgqhha);
	free(pgqhhb);



	//���������邱����������
	int AK = -2, aw, qwe = 0;
	for (i = 0;i < x*y*n; i++) {
		for (j = 0;j < degree;j++) {
			if (a[i][j] == -1) {
				for (k = 0;k < x*y*n; k++) {
					for (m = 0;m < degree;m++) {
						if (a[k][m] == i) {

							for (aw = 0;aw < degree;aw++) {
								if (k == a[i][aw])
									qwe = 100;
							}
							if (qwe != 100) {
								a[i][j] = k;
							}
							qwe = 0;
						}
					}
				}
			}
		}


		/*
		for (i = 0;i < x*y*n; i++) {
			printf("%d ", i);
			for (j = 0;j < degree;j++) {
				printf("%d ", a[i][j]);
			}
			printf("\n");
		}*/
	}

	aspl = ASPL(a, degree, nodes);
	printf("%f\n",aspl);
	file_voltage_test(a, degree, nodes, aspl, x, y, z);

}

float ASPL(int **a, int degree, int nodes) {
	//�錾
	int  v, u, j, t, y, o, w, i = 0, err;
	double A = 0, B = 0;
	int *s = (int *)malloc(nodes * sizeof(int));
	int *F = (int *)malloc(nodes * sizeof(int));

	//�{��
	//for (w = 0;w < nodes; w = w + (int)(nodes / 3)) {
	for (w = (int)(nodes / 2) - 1; w < (int)nodes / 2 + 1; w++) {
		//for (w = 0; w < nodes; w++) {
		//�e�m�[�h�ɑ΂��鏉����
		for (j = 0; j < nodes; j++) {
			F[j] = 0;
			s[j] = 0;
		}
		enqueue(w);
		F[w] = 1;
		
		i = 1;
		s[1] = 1;
		v = 0;
		u = 0;
		t = 0;
		y = 1;
		o = 0;
		err = 0;
		while (o != nodes) {
			o++;
			v = dequeue();
			for (j = 0;j < degree;j++) {
				u = a[v][j];
				if (F[u] == 0) {
					F[u] = 1;
					enqueue(u);
					A = A + i;
					B = B + i;
					t++;
					err++;

				}
			}
			if (s[i] == y) {
				i++;
				s[i] = t;
				t = 0;
				y = 0;
			}
			y++;
		}
		if (err != (nodes - 1)) {
			printf("�q�����Ă��܂���");
			return 10000000;
		}

		printf("%d \n", i);
	}
	free(F);
	free(s);

	return A/nodes/(nodes-1);
}

void file_voltage_test(int **a, int degree, int nodes, float aspl, int x, int y, int z) {
	FILE *outputfile;
	int i, j;
	char N[50];
	sprintf_s(N, 50, "%d %d %f %d %d %d", nodes, degree,aspl,  x, y, z);
	fopen_s(&outputfile, N, "w");
	fprintf_s(outputfile, "%d %d\n", degree, nodes);
	for (i = 0;i < nodes;i++) {
		fprintf_s(outputfile, "%d ", i);

		for (j = 0; j < degree; j++) {
			if (j == degree - 1) {
				fprintf_s(outputfile, "%d \n", a[i][j]);
			}
			else {
				fprintf_s(outputfile, "%d ", a[i][j]);
			}
		}
	}
	fclose(outputfile);
}

///queue�̊֐��Q��������������������
//enqueue�̊֐�
int enqueue(int x) {
	LLIST* next;
	next = (LLIST *)malloc(sizeof(LLIST));
	if (next != NULL) { /* ���������m�ۂł��Ȃ��� NULL ���Ԃ���� */
		next->value = x;
		next->pointer = NULL;
		if (d == NULL) {
			d = next;
		}
		else {
			e->pointer = next;
		}
		e = next;
		return 1;
	}
	else {
		return 0;
	}
}
//depueue�̊֐�
int dequeue() {
	int x;
	LLIST *next;
	if (!empty()) {
		x = d->value;
		next = d->pointer;
		free(d);
		d = next;
		return x;
	}
	else {
		/* �v�f���Ȃ��̂ɗv�f�����o�����Ƃ����� */
		return -2; /* C++ �Ȃ�G���[�𔭐��ł���̂����c�c */
	}
}

//dequeue�ɂȂ����̊֐�
int empty() {
	return d == NULL;
}
/////////////////////////////////////