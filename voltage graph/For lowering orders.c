#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


typedef struct llist {
	int value;
	struct llist *pointer;
} LLIST;

LLIST *e = NULL;
LLIST *d = NULL;

//関数群
int empty();
int enqueue(int);
int dequeue();
float ASPL(int**, int, int);
void yaki(int**, int, int);

void file_voltage_test(int**, int, int,int*,float);

main() {
	//時間計測
	clock_t start, end;
	start = clock();
	///////////////////

	//宣言
	FILE *fp;
	int degree, nodes, reduce;
	float aspl, min = 1110;
	int D, ak, check = 0,ka = 0;
	int i = 0, j, m;
	int err = fopen_s(&fp, "4856 30 2.808915", "r");
	if (err != 0)
		printf("aaa");//エラー処理
	int w = 0;
	reduce = 1;

	//ファイルから次数とノード数を代入する。
	fscanf_s(fp, "%d %d", &degree, &nodes);


	//動的確保
	int *d = (int *)malloc(degree * sizeof(int));
	int *k = (int *)malloc(nodes * sizeof(int));
	int *kb = (int *)malloc(nodes * sizeof(int));
	int **a = (int **)malloc(nodes * sizeof(int));
	for (m = 0; m < nodes; m++)
		a[m] = (int*)malloc(degree * sizeof(int));
	int **b = (int **)malloc(nodes * sizeof(int));
	for (m = 0; m < nodes; m++)
		b[m] = (int*)malloc(degree * sizeof(int));
	int **c = (int **)malloc(nodes * sizeof(int));
	for (m = 0; m < nodes; m++)
		c[m] = (int*)malloc(degree * sizeof(int));

	while (fscanf_s(fp, "%d", &D) != EOF) {
		while (1) {
			if (i < degree) {
				fscanf_s(fp, "%d", &d[i]);
				a[D][i] = d[i];
				c[D][i] = d[i];
				i++;
			}
			else {
				i = 0;
				break;
			}
		}
	}
	fclose(fp);
	free(d);

	

	for (i = 0;i < reduce;i++) {
		k[i] = rand() % nodes;
		kb[i] = k[i];
		for (j = 0;j < i;j++) {
			if (k[j] == k[i]) {
				i = i - 1;
				break;
			}
		}
	}
	aspl = ASPL(a, degree, nodes );
	printf("%f\n", aspl );
	int tr = 0;
	min = aspl;
	while (1) {
	
		tr++;
		
		if (tr > 400) {
			tr = 0;
			for (i = 0;i < reduce;i++) {
				k[i] = rand() % nodes;
				kb[i] = k[i];
				for (j = 0;j < i;j++) {
					if (k[j] == k[i]) {
						i = i - 1;
						break;
					}
				}
			}
		}

		while (1) {
			i = rand() % reduce;
			k[i] = rand() % nodes;
			for (j = 0;j < i;j++) {
				if (k[j] == k[i]) {
					m = 12;
				}
			}
			if (m == 0)
				break;
			m = 0;
		}


		for (i = 0;i < reduce;i++) {
			printf("%d ", k[i]);
		}
		for (i = 0;i < nodes;i++) {
			for (j = 0; j < degree;j++) {
				for (m = 0; m < reduce;m++) {
					if (a[i][j] == k[m]) {
						a[i][j] = -1;
						//	printf("%d %d %d \n", i, j, a[i][j]);
					}
				}
			}
		}

		for (i = 0;i < nodes;i++) {
			for (j = 0;j < degree;j++) {
				if (a[i][j] == -1) {
					//printf("%d %d %d \n", i, j, a[i][j]);
					while (1) {
						ak = rand() % nodes;
						for (m = 0;m < degree;m++) {
							if (a[ak][m] == -1) {
								a[i][j] = ak;
								a[ak][m] = i;
								check = 5;
								break;
							}
						}
						if (check == 5)
							break;
					}
					check = 0;
				}
			}
		}

		w = 0;
		for (i = 0; i < nodes - reduce;i++) {
			for (m = 0;m < reduce;m++) {
				if (i == k[m])
					w++;
			}
			for (j = 0;j < degree;j++) {
				a[i][j] = a[i + w][j];
			}
		}


		for (i = 0; i < nodes;i++) {
			for (j = 0;j < degree;j++) {
				for (m = 0;m < reduce;m++) {
					if (a[i][j] > k[m])
						ka++;
				}
				a[i][j] = a[i][j] - ka;
				ka = 0;
			}
		}
		/*
		for (i = 0;i < nodes;i++) {
			printf("%d ", i);
			for (j = 0;j < degree;j++) {
				printf("%d ", a[i][j]);
			}
			printf("\n");
		}*/


		for (i = 0; i < nodes - reduce;i++) {
			for (m = 0;m < degree;m++) {
				b[i][m] = a[i][m];
			}
		}
		aspl = ASPL(b, degree, nodes - reduce);
		printf("%f\n", aspl);

		if (min > (aspl)) {
			min = aspl;
			printf("最小を更新しました\n", aspl );
			file_voltage_test(a, degree, nodes - reduce, k,min);
			for (i = 0;i < reduce;i++) {
				kb[i] = k[i];
			}
		}
		else{
			for (i = 0;i < reduce;i++) {
				k[i] = kb[i];
			}
		}

		for (i = 0;i < nodes;i++) {
			for (j = 0; j < degree;j++) {
				a[i][j] = c[i][j];
			}
		}


	}


}


void file_voltage_test(int **a, int degree, int nodes,int *k,float min) {
	FILE *outputfile;
	int i, j,reduce =4,m;

	char N[90];
	sprintf_s(N, 90, "%d %d %f", nodes, degree,min);
	fopen_s(&outputfile, N, "w");
	fprintf_s(outputfile, "%d %d\n", degree, nodes);

	int y = 0;
	for (i = 0;i < nodes;i++) {
/*		for (m = 0;m < reduce;m++) {
			if (i == k[m]) {
				i++;
				break;
			}
		}*/
		fprintf_s(outputfile, "%d ", i);

		for (j = 0;j < degree;j++) {
			fprintf_s(outputfile, "%d ", a[i][j]);
		}
		fprintf_s(outputfile, "\n", a[i][j]);
		y++;
	}
	fclose(outputfile);

	FILE *outputfil;
	sprintf_s(N, 90, "%d %d", nodes, degree);
	fopen_s(&outputfil, N, "w");
	fprintf_s(outputfil, "%d %d\n", degree, nodes);

	y = 0;
	for (i = 0;i < nodes;i++) {
		/*		for (m = 0;m < reduce;m++) {
		if (i == k[m]) {
		i++;
		break;
		}
		}*/
		fprintf_s(outputfil, "%d ", i);

		for (j = 0;j < degree;j++) {
			fprintf_s(outputfil, "%d ", a[i][j]);
		}
		fprintf_s(outputfil, "\n", a[i][j]);
		y++;
	}
	fclose(outputfil);


}



///queueの関数群//////////////////////////////////
//enqueueの関数
int enqueue(int x) {
	LLIST* next;
	next = (LLIST *)malloc(sizeof(LLIST));
	if (next != NULL) { /* メモリが確保できないと NULL が返される */
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
//depueueの関数
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
		/* 要素がないのに要素を取り出そうとした時 */
		return -2; /* C++ ならエラーを発生できるのだが…… */
	}
}

//dequeueにない時の関数
int empty() {
	return d == NULL;
}
///queueの関数群//////////////////////////////////

//asplの関数
float ASPL(int **a, int degree, int nodes) {
	//宣言
	int  v, u, j, t, y, o, w, i, err;
	double A = 0;
	int *s = (int *)malloc(nodes * sizeof(int));
	int *F = (int *)malloc(nodes * sizeof(int));

	//本文
	//for (w = 0;w < nodes; w = w + (int)(nodes / 3)) {
	//for (w = (int)(nodes / 2) - 1; w < (int)nodes / 2 + 1; w++) {
	for (w = 0; w < nodes; w++) {
		//各ノードに対する初期化
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
			//if (v == -2)
			//break;
			for (j = 0;j < degree;j++) {
				u = a[v][j];
				if (F[u] == 0) {
					F[u] = 1;
					enqueue(u);
					A = A + i;
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
		//printf("%f\ %d \n", A, w);
		//A = 0;
		//繋がってないときのエラー処理
		if (err != (nodes - 1)) {
			printf("繋がっていません");
			return 10000000;
		}
	}
	free(F);
	free(s);

	return A/nodes/(nodes-1);
}





//焼きなまし法
void yaki(int **a, int degree, int nodes) {

	//宣言
	int i, j, m, changes, trials, freeze = 0;	//カウンタ
	int A1, B1, A2, B2, x, y, a1, b1;			//局所探索法
	double aspl, aspl1, aspl2;					//平均最短経路長
	double INTPROB, TEMPFACRTOR, FREEZELIM, SIZEFACTOR, CUTOFF, MINPERCENT;		//パラメータ
	double min, CUT, SIZ, T, average_N, average_delta;		//パラメータから生み出されるもの
	float  RAN;
	int **MIN = (int **)malloc(nodes * sizeof(int));//最小の値を保存
	for (m = 0; m < nodes; m++)
		MIN[m] = (int*)malloc(degree * sizeof(int));
	int **b = (int **)malloc(nodes * sizeof(int));//局所探索法のbパート
	for (m = 0; m < nodes; m++)
		b[m] = (int*)malloc(degree * sizeof(int));
	int **c = (int **)malloc(nodes * sizeof(int));//局所探索法のcパート
	for (m = 0; m < nodes; m++)
		c[m] = (int*)malloc(degree * sizeof(int));







	//パラメータに手動で入れる
	INTPROB = 0.1;
	TEMPFACRTOR = 0.9;
	FREEZELIM = 100;
	SIZEFACTOR = 30000;
	CUTOFF = 30;
	MINPERCENT = 0.3;
	//パラメータによって生み出されたもの
	average_N = 3.036515388;
	average_delta = -0.001799687010;
	CUT = CUTOFF * average_N;
	SIZ = SIZEFACTOR * average_N;
	T = (-1)*average_delta / INTPROB;

	//最初のasplを計算する。
	aspl = ASPL(a, degree, nodes);
	for (i = 0;i < nodes;i++) {
		for (j = 0; j < degree; j++) {
			b[i][j] = a[i][j];
			c[i][j] = a[i][j];
		}
	}

	printf("最初の温度 : %lf    ASPL : %f\n", T, aspl);//初期値
	min = aspl;

	for (i = 0;i < nodes;i++) {
		for (j = 0; j < degree; j++) {
			MIN[i][j] = a[i][j];
		}
	}




	//本文
	while (freeze < FREEZELIM) {
		changes = 0;
		trials = 0;
		while (trials < SIZ && changes < CUT) {
			trials++;

			//交換する準備
			A1 = rand() % nodes;
			B1 = rand() % degree;
			A2 = rand() % nodes;
			B2 = rand() % degree;
			a1 = a[A1][B1];
			b1 = a[A2][B2];
			for (i = 0;i < degree;i++) {
				if (a[a1][i] == A1)
					x = i;
				if (a[b1][i] == A2)
					y = i;
			}


			//bパートの交換
			b[A1][B1] = A2;
			b[a1][x] = b1;
			b[b1][y] = a1;
			b[A2][B2] = A1;
			aspl1 = ASPL(b, degree, nodes);



			//cパートの交換
			c[A1][B1] = b1;
			c[b1][y] = A1;
			c[A2][B2] = a1;
			c[a1][x] = A2;
			aspl2 = ASPL(c, degree, nodes);

			//printf("%f %f %f\n", aspl, aspl1, aspl2);

			//交換部分
			if (aspl < aspl1 && aspl < aspl2) {
				/*
				if (exp(((aspl - aspl1)/(nodes*(nodes-1))) / T) >(float)rand() / RAND_MAX){
				changes++;
				printf("更新されましたa : %f 差 : %f\n", aspl1, aspl1-aspl);
				aspl = aspl1;


				for (i = 0;i < nodes;i++) {
				for (j = 0; j < degree; j++){
				c[i][j] = b[i][j];
				a[i][j] = b[i][j];
				}
				}


				}else if (exp(((aspl - aspl2) / (nodes*(nodes - 1))) / T) >(float)rand() / RAND_MAX){
				changes++;
				printf("更新されましたb : %f 差 : %f \n", aspl2, aspl2 - aspl);
				aspl = aspl2;

				for (i = 0;i < nodes;i++) {
				for (j = 0; j < degree; j++) {
				a[i][j] = c[i][j];
				b[i][j] = c[i][j];
				}
				}
				}

				else*/ {


					for (i = 0;i < nodes;i++) {
						for (j = 0; j < degree; j++) {
							c[i][j] = a[i][j];
							b[i][j] = a[i][j];
						}
					}

				}

			}
			else if (aspl1 < aspl && aspl1 < aspl2) {

				changes++;
				printf("更新されましたc : %f 差 : %f\n", aspl1, aspl1 - aspl);
				aspl = aspl1;
				/*
				memcpy_s(*c, sizeof(c), *b, sizeof(b));
				memcpy_s(*a, sizeof(a), *b, sizeof(b));
				*/
				for (i = 0;i < nodes;i++) {
					for (j = 0; j < degree; j++) {
						a[i][j] = b[i][j];
						c[i][j] = b[i][j];
					}
				}

			}
			else if (aspl2 < aspl && aspl2 < aspl1) {

				changes++;
				printf("更新されましたd : %f 差 : %f %f\n", aspl2, aspl2 - aspl, T);
				aspl = aspl2;
				/*
				memcpy_s(*b, sizeof(b), *c, sizeof(c));
				memcpy_s(*a, sizeof(a), *c, sizeof(c));
				*/
				for (i = 0;i < nodes;i++) {
					for (j = 0; j < degree; j++) {
						a[i][j] = c[i][j];
						b[i][j] = c[i][j];
					}
				}
			}
			else {
				for (i = 0;i < nodes;i++) {
					for (j = 0; j < degree; j++) {
						c[i][j] = a[i][j];
						b[i][j] = a[i][j];
					}
				}


			}

		}
		T = T * TEMPFACRTOR;

		if (aspl < min) {
			min = aspl;
			printf("最小値は現在 %f です\n\n", min);

			for (i = 0;i < nodes;i++) {
				for (j = 0; j < degree; j++) {
					MIN[i][j] = a[i][j];
				}
			}
			///////FILE_MAKE////////////////////////////////////////////////////////////////
			FILE *timep;
			char n[30];
			//time_t time(time_t *t);

			sprintf_s(n, 30, " %d %d %d", (int)min, nodes, degree);
			fopen_s(&timep, n, "w");
			fprintf(timep, "%d %d\n", degree, nodes);
			for (i = 0;i < nodes;i++) {
				fprintf(timep, "%d ", i);
				for (j = 0; j < degree; j++) {
					if (j == degree - 1) {
						fprintf(timep, "%d \n", MIN[i][j]);
					}
					else {
						fprintf(timep, "%d ", MIN[i][j]);
					}
				}
			}
			fclose(timep);
			///////FILE_MAKE////////////////////////////////////////////////////////////////

		}

		if (((float)changes / (float)trials) < MINPERCENT) {
			freeze++;
			printf("\n\nfreezeの値が上がりました : %d\n", freeze);


		}
	}





	////////////////表示部/////////////////////////////
	printf("%f\n", min / (nodes*(nodes - 1)));
	printf("%f\n", min);


	//ファイル入力部　時間をファイル名に入力
	FILE *outputfile;
	fopen_s(&outputfile, "test", "w");
	fprintf_s(outputfile, "%d %d\n", degree, nodes);
	for (i = 0;i < nodes;i++) {
		fprintf_s(outputfile, "%d ", i);
		for (j = 0; j < degree; j++) {
			if (j == degree - 1) {
				fprintf_s(outputfile, "%d \n", MIN[i][j]);
			}
			else {
				fprintf_s(outputfile, "%d ", MIN[i][j]);
			}
		}
	}
	fclose(outputfile);


	FILE *timep;
	char n[30];
	//time_t time(time_t *t);
	time_t t = time(NULL);
	struct tm local;
	localtime_s(&local, &t);

	sprintf_s(n, 30, "%4d %02d %02d %02d %02d %d %d %d", local.tm_year + 1900, local.tm_mon + 1, local.tm_mday, local.tm_hour, local.tm_min, (int)min, nodes, degree);
	fopen_s(&timep, n, "w");
	fprintf(timep, "%d %d\n", degree, nodes);
	for (i = 0;i < nodes;i++) {
		fprintf(timep, "%d ", i);
		for (j = 0; j < degree; j++) {
			if (j == degree - 1) {
				fprintf(timep, "%d \n", MIN[i][j]);
			}
			else {
				fprintf(timep, "%d ", MIN[i][j]);
			}
		}
	}
	fclose(timep);





	free(b);
	free(c);
	free(MIN);
}