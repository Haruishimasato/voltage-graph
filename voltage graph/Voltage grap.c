
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

//void file_voltage_test(int**, int, int, float, int, int, int, int*);

int empty();
int enqueue(int);
int dequeue();
void voltage_make(int*, int*, int, int, int, int, int, int, int, int);
void voltage_make2(int*, int*, int, int, int, int, int, int, int, int);
float ASPL_voltage(int, int, int*, int*, int, int, int, int, int);
void file_voltage_test(int*, int*, int, int, int, int, int, int, int, float, int);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



main() {
	clock_t start, end;
	start = clock();
	srand(1);

	//宣言→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→
	int nodes = 2300, degree = 10, n = 2, pp = 3, pq = 4;//ノードと次数,ベースグラフの設定
	int x, y, z;//初期設定
	int i1, i2;//カウンタ
	float aspla, asplb = 0, MIN;//その他
	int check = 0, check2 = 0;


	//ファイル系→→→→→→→→→→→→→→→→→→→
	FILE *fp;
	char file[100];
	sprintf_s(file, 100, "/Users/b143471/source/repos/高速ボルテージ判断/高速ボルテージ判断/%d  %d",nodes ,n);

	int err = fopen_s(&fp, file, "r");
	if (err != 0)
		printf("aaa");//エラー処理

	while (fscanf_s(fp, "%d %d %d", &x, &y, &z) != EOF) {
		
		if (2 * x > y && z != 1) {
			printf("最初のx,y,zは%d %d %dです\n", x, y, z);
			break;
		}

	}
	/////////////////////////////////////////////////

	int *gyakugen_voltage = (int *)malloc(nodes * sizeof(int));
	int *voltage = (int *)malloc(degree * sizeof(int));//最初に割り振るボルテージのセット

	int *gyakugen_voltage2 = (int *)malloc(nodes * sizeof(int));
	int *voltage2 = (int *)malloc(degree * sizeof(int));//最初に割り振るボルテージのセット
	//////////////////////////////////////////////////////////////////////////////////////




	//voltage制作→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→
	voltage_make(voltage, gyakugen_voltage, nodes, degree, n, pp, pq, x, y, z);
	for (i1 = 0; i1 < degree;i1++) {
		voltage2[i1] = voltage[i1];
		gyakugen_voltage2[i1] = gyakugen_voltage[i1];
	}//////////////////////////////////////////////////////////////////////////////////////////


	//x = 550;y = 120;z = 13;
	 //初期グラフのaspl計算→→→→→→→→→→→→→→→→→→→→→→→→→→→→→																										
	aspla = ASPL_voltage(degree, nodes, voltage, gyakugen_voltage, x, y, z, pp, pq);
	printf("ランダムグラフのaspl = %f\n", aspla);
	MIN = aspla;
	/////////////////////////////////////////////////////////////////////////////////




	//焼きなまし部分→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→			
	i2 = 0;
	while (1) {
		i2++;
		voltage_make2(voltage2, gyakugen_voltage2, nodes, degree, n, pp, pq, x, y, z);
		aspla = ASPL_voltage(degree, nodes, voltage2, gyakugen_voltage2, x, y, z, pp, pq);

		//けっかはっぴょおおおおおおおおおおおおおおおおおおおおおおおおおおおおおおおおおおおおおおおお
		if (aspla < MIN) {
			MIN = aspla;
			printf("---------------------------------\n", aspla);
			printf("最小値更新 aspl = %f\n", aspla);
			check = i2;
			check2 = i2;
			file_voltage_test(voltage2, gyakugen_voltage2, nodes, degree, x, y, z, pp, pq, aspla, n);


			//ボルテージ反映→→→→→→→→→→→→→→→→
			for (i1 = 0; i1 < degree;i1++) {
				voltage[i1] = voltage2[i1];
				gyakugen_voltage[i1] = gyakugen_voltage2[i1];
			}
			/////////////////////////////////////////////////


			//表示→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→
			for (i1 = 0; i1 < degree;i1++) {
				//printf("(%2d %6d) ", i1, voltage[i1]);	
				printf("(%d %d)", voltage2[i1] % (x * y) / y, voltage2[i1] % y);
			}
			printf("\n");
			for (i1 = 0; i1 < degree;i1++) {
				//printf("(%2d %6d) ", i1, gyakugen_voltage[i1]);
				printf("(%d %d)", gyakugen_voltage2[i1] % (x * y) / y, gyakugen_voltage2[i1] % y);
			}
			printf("\n");
			////////////////////////////////////////////////////////////////////////////////////////////


		}
		else if (aspla < asplb) {
			
			//printf("改良できました aspl = %f\n", aspla);
			asplb = aspla;
			check = i2;

			//ボルテージ反映→→→→→→→→→→→→→→→→→
			for (i1 = 0; i1 < degree;i1++) {
				voltage[i1] = voltage2[i1];
				gyakugen_voltage[i1] = gyakugen_voltage2[i1];
			}/////////////////////////////////////////////////

		}////////////////////////////////////////////////////////////////////////////////////////////////



		 //できたグラフが前のよりしょぼかったら→→→→→→→→→→→→→→→→→→→→→→→→→
		else {
			for (i1 = 0; i1 < degree;i1++) {
				voltage2[i1] = voltage[i1];
				gyakugen_voltage2[i1] = gyakugen_voltage[i1];
			}
		}
		//////////////////////////////////////////////////////////////////////////////////////////



		//100個ごとにタイム更新→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→
		if (i2 % 10000 == 0) {
			end = clock();
			printf(" %d 個作るのに %.2f秒かかりました\n", i2, (double)(end - start) / CLOCKS_PER_SEC);
		}
		//////////////////////////////////////////////////////////////////////////////////////////////


		//nodes/4個変化しなければやり直し→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→
		if (i2 % ((nodes ) + check) == 0) {

			voltage_make(voltage, gyakugen_voltage, nodes, degree, n, pp, pq, x, y, z);
			asplb = ASPL_voltage(degree, nodes, voltage, gyakugen_voltage, x, y, z, pp, pq);
			printf("次のランダムグラフのaspl = %f\n", asplb);

			for (i1 = 0; i1 < degree;i1++) {
				voltage2[i1] = voltage[i1];
				gyakugen_voltage2[i1] = gyakugen_voltage[i1];
			}
		}
		//////////////////////////////////////////////////////////////////////////////////////////////

		
		//nodes*10でx,y,z交代→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→
		if (i2 % ((100000 ) + check2) == 0) {
			while (fscanf_s(fp, "%d %d %d", &x, &y, &z) != EOF) {
				if (2 * x > y && z != 1) {
					MIN = 100;
					aspla = 100;
					asplb = 0;
					printf("\n次のx,y,zは%d %d %dです-------------------------------------------------------------------------------------------------------------------------------\n", x, y, z);
					break;
				}
			}

			//voltage制作→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→
			voltage_make(voltage, gyakugen_voltage, nodes, degree, n, pp, pq, x, y, z);
			for (i1 = 0; i1 < degree;i1++) {
				voltage2[i1] = voltage[i1];
				gyakugen_voltage2[i1] = gyakugen_voltage[i1];
			}//////////////////////////////////////////////////////////////////////////////////////////

			 //初期グラフのaspl計算→→→→→→→→→→→→→→→→→→→→→→→→→→→→→																										
			aspla = ASPL_voltage(degree, nodes, voltage, gyakugen_voltage, x, y, z, pp, pq);
			printf("ランダムグラフのaspl = %f\n", aspla);
			MIN = aspla;
			/////////////////////////////////////////////////////////////////////////////////
		}
		//////////////////////////////////////////////////////////////////////////////////////////////
		
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




	//時間表示→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→
	end = clock();
	printf("%.2f秒かかりました\n", (double)(end - start) / CLOCKS_PER_SEC);
	//////////////////////////////////////////////////////////////////////
}

float ASPL_voltage(int degree, int nodes, int *voltage, int *gyakugen_voltage, int x, int y, int z, int pp, int pq) {
	//宣言
	//printf("作成します\n");
	int  v, u, j, t, o, w, yyy, i, i3, err, LA, yui = 0, max;
	float A = 0;
	int g1, g2, g3, a1, a2, a3, h1, h2 = 0, h3 = 0;
	int *s = (int *)malloc(nodes * sizeof(int));
	int *F = (int *)malloc(nodes * sizeof(int));

	//本文
	for (w = (int)(nodes / 2) - 1; w < (int)nodes / 2 + 1; w++) {
		//	for (w =  0; w < (int)nodes; w++) {
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
		yyy = 1;
		o = 0;
		err = 0;

		while (1) {
			//////////////////////////////////////////

			o++;
			v = dequeue();
			//printf("v = %d\n", v);

			if (v == -2)
				break;

			///	ｇのほう
			g1 = v / (x * y);
			g2 = v % (x * y) / y;
			g3 = v % y;


			LA = z % x;
			for (i3 = 0; i3 < g3; i3++)
				LA = (LA * z) % x;



			for (j = 0;j < degree;j++) {
				//頂点Aでループの線の計算→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→
				if (g1 == 0) {


					if (j < pp + pq) {
						a1 = voltage[j] / (x * y);
						a2 = voltage[j] % (x * y) / y;
						a3 = voltage[j] % y;
					}
					else {
						a1 = gyakugen_voltage[j - pp - pq] / (x * y);
						a2 = gyakugen_voltage[j - pp - pq] % (x * y) / y;
						a3 = gyakugen_voltage[j - pp - pq] % y;
					}

					if (a1 == 0) {
						h1 = 0;
					}
					else if (a1 == 1) {
						h1 = 1;
					}
					else if (a1 == 2) {
						continue;
					}

					h2 = (int)(g2 + a2 * LA) % x;
					h3 = (g3 + a3) % y;
					u = h1 * x*y + h2 * y + h3;

					//結果を格納→→→→→
					if (F[u] == 0) {
						//printf("%d\n", u);
						yui++;
						F[u] = 1;
						enqueue(u);
						A = A + i;
						t++;
						err++;
					}
					///////////////////////
				}////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



				 //頂点Bからのびる線の計算→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→
				else if (g1 == 1) {

					if (j < pp) {
						a1 = voltage[j + pp + pq] / (x * y);
						a2 = voltage[j + pp + pq] % (x * y) / y;
						a3 = voltage[j + pp + pq] % y;
					}
					else {
						a1 = gyakugen_voltage[j] / (x * y);
						a2 = gyakugen_voltage[j] % (x * y) / y;
						a3 = gyakugen_voltage[j] % y;
					}


					if (a1 == 0) {
						continue;
					}
					else if (a1 == 1) {
						h1 = 0;
					}
					else if (a1 == 2) {
						h1 = 1;
					}

					h2 = (int)(g2 + a2 * LA) % x;
					h3 = (g3 + a3) % y;
					u = h1 * x*y + h2 * y + h3;

					//結果を格納→→→→→
					//printf("%d\n", u);
					if (F[u] == 0) {
						yui++;
						F[u] = 1;
						enqueue(u);
						A = A + i;
						t++;
						err++;
					}
					////////////////////////
				}////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


























				 /*

				 printf("v=%d  u=%d \n", v, u);
				 //ここからループの逆を割り当てる工程
				 h1 = -2;
				 if (g1 == 0 && a1 == 0) {
				 h1 = 0;
				 }
				 else if (g1 == 1 && a1 == 2) {
				 h1 = 1;
				 }
				 if (h1 == -2)
				 continue;

				 printf("a");

				 for (ew = 0; ew < nodes; ew++) {
				 g12 = v / (x * y);
				 g22 = v % (x * y) / y;
				 g32 = v % y;

				 LA = z % x;
				 for (i2 = 0; i2 < g32; i2++)
				 LA = (LA * z) % x;

				 h2 = (g22 + LA * a2) % x;
				 h3 = (g32 + a3) % y;

				 if (h2 == g2 && h3 == g3) {
				 u = ew;
				 break;
				 }
				 }
				 */


				 /*
				 h3 = (g3 - a3)%y;
				 LA = z % x;
				 for (i2 = 0; i2 < h3; i2++)
				 LA = (LA * z) % x;
				 //printf("a%da\n", LA);
				 h2 = (g2 - z ^ LA * a2)%x;

				 u = h1 * x*y + h2 * y + h3;
				 */

				 //printf("%d %d %d %d %d %d %d %d %d \n", g1, g2, g3, a1, a2, a3, h1, h2, h3);
				 /*
				 //printf("v=%d  u=%d \n", v, u);
				 if (F[u] == 0) {
				 yui++;
				 F[u] = 1;
				 //printf(" u = %d \n", u);
				 enqueue(u);
				 A = A + i;
				 t++;
				 err++;
				 }

				 */
			}

			if (s[i] == yyy) {
				i++;
				s[i] = t;
				t = 0;
				yyy = 0;
			}
			yyy++;

		}







		//printf("A =%f\n", A);
		//繋がってないときのエラー処理
		if (err != (nodes - 1)) {
			//printf("繋がっていません\n");
			return 10000000;
		}


	}
	free(F);
	free(s);
	return A / (nodes - 1) / 2;
}

void voltage_make(int *voltage1, int *gyakugen_voltage, int nodes, int degree, int n, int pp, int pq, int x, int y, int z) {
	//printf("最初のボルテージ及びその逆玄\n");
	int g1, g2, g3, a1, a2, a3, h1, h2, h3;
	int i, i2, i3, i4, j, k, u;	//カウンタ置き場
	int LA;

	//動的確保//////////////////////////////////
	int *K = (int *)malloc(degree * sizeof(int));
	int *gyakugen = (int *)malloc(nodes * sizeof(int));
	int *gyakugen2 = (int *)malloc(nodes * sizeof(int));


	for (i4 = 0;i4 < degree;i4++)
	{
		gyakugen_voltage[i4] = -3;
	}

	//初期グラフ作成及びボルテージ→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→
	for (i = 0; i < degree;i++) {
		k = rand() % (nodes / 2);
		if (i < pp)
			j = 0;
		if (pp <= i && i < pp + pq)
			j = 1;
		if (pp + pq <= i && i < degree)
			j = 2;
		voltage1[i] = j * x*y + k / y * y + k % y;

		for (j = 0; j < i;j++) {
			if (K[j] == k)
				i--;
		}
	}
	/*
	for (i = 0; i < degree;i++) {
	printf("最初のボルテージ %d\n", voltage1[i]);
	}
	*/
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	for (i2 = 0; i2 < nodes; i2 = i2 + nodes / 2) {//頂点を一つ選ぶ

		g1 = i2 / (x * y);
		g2 = i2 % (x * y) / y;
		g3 = i2 % y;

		LA = z % x;
		for (i3 = 0; i3 < g3; i3++)
			LA = (LA * z) % x;
		/*
		printf("-----\n");
		printf("i2 = %d\n", i2);
		printf("-----\n");
		*/
		//逆玄を求めるにあたって前準備→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→
		for (j = 0;j < degree;j++) {

			if (g1 == 0) {
				a1 = voltage1[j] / (x * y);

				if (a1 == 0) {
					h1 = 0;
				}
				else if (a1 == 1) {
					h1 = 1;
				}
				else if (a1 == 2) {
					continue;
				}

				a2 = voltage1[j] % (x * y) / y;
				a3 = voltage1[j] % y;

				h2 = (g2 + LA * a2) % x;
				h3 = (g3 + a3) % y;
				gyakugen[j] = h1 * x*y + h2 * y + h3;//次の頂点を格納
													 //printf("a次の頂点%d %d %d\n", h1,h2,h3);
													 //printf("a次の頂点 %d\n", gyakugen[j]);
			}
			else if (g1 == 1) {

				a1 = voltage1[j] / (x * y);
				if (a1 == 0) {
					continue;
				}
				else if (a1 == 1) {
					continue;
				}
				else if (a1 == 2) {
					h1 = 1;
				}

				a2 = voltage1[j] % (x * y) / y;
				a3 = voltage1[j] % y;

				h2 = (int)(g2 + LA * a2) % x;
				h3 = (g3 + a3) % y;
				gyakugen[j] = h1 * x*y + h2 * y + h3;//次の頂点を格納
													 //printf("b次の頂点%d\n", gyakugen[j]);
													 //printf("b次の頂点 %d\n", gyakugen[j]);
			}
		}
		//printf("---------\n");
		///////////////////////////////////////////////////////////////////////////////////////////
	}



	//for (i2 = 0; i2 < nodes; i2 = i2 + nodes / 2) {//頂点を一つ選ぶ
	i2 = 0;
	//逆玄を求める→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→
	for (i = 0;i < degree;i++) {
		//次の頂点をgに格納する。

		g1 = gyakugen[i] / (x * y);
		g2 = gyakugen[i] % (x * y) / y;
		g3 = gyakugen[i] % y;
		//printf("%d %d\n",g1,gyakugen[i]);

		LA = z % x;
		for (i3 = 0; i3 < g3; i3++)
			LA = (LA * z) % x;

		//ボルテージがAでループしてる時→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→
		if (i < pp) {
			for (j = 0;j < 3 * x * y;j++) {
				a1 = j / (x * y);
				if (a1 == 0) {
					h1 = 0;
				}
				else if (a1 == 1) {
					continue;
				}
				else if (a1 == 2) {
					continue;
				}
				a2 = j % (x * y) / y;
				a3 = j % y;


				h2 = (int)(g2 + a2 * LA) % x;
				h3 = (g3 + a3) % y;
				u = h1 * x*y + h2 * y + h3;

				//i2がuと一致したやつらへ→→→→→→→→→→→→→→→→→
				if (i2 == u) {
					//printf("a前の頂点への逆玄のボルテージは%d\n", j);
					if (i2 < nodes / 2) {
						for (i4 = 0;i4 < degree;i4++)
						{
							if (gyakugen_voltage[i4] == -3) {
								gyakugen_voltage[i4] = j;
								break;
							}

						}
					}
				}
				///////////////////////////////////////////////////////////
			}
		}//////////////////////////////////////////////////////////////////////////////////////////////////
		else if (pp <= i && i < pp + pq) {
			for (j = 0;j < 3 * x * y;j++) {
				a1 = j / (x * y);
				if (a1 == 0) {
					continue;
				}
				else if (a1 == 1) {
					h1 = 0;
				}
				else if (a1 == 2) {
					continue;
				}
				a2 = j % (x * y) / y;
				a3 = j % y;


				h2 = (int)(g2 + a2 * LA) % x;
				h3 = (g3 + a3) % y;
				u = h1 * x*y + h2 * y + h3;

				//i2がuと一致したやつらへ→→→→→→→→→→→→→→→→→
				if (i2 == u) {
					//printf("a前の頂点への逆玄のボルテージは%d\n", j);
					if (i2 < nodes / 2) {
						for (i4 = 0;i4 < degree;i4++)
						{
							if (gyakugen_voltage[i4] == -3) {
								gyakugen_voltage[i4] = j;
								break;
							}

						}
					}
				}
				///////////////////////////////////////////////////////////
			}




		}
		//元の頂点がBの時→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→
		else if (i <= pp + pq) {
			i2 = nodes / 2;
			for (j = 0;j < 3 * x * y;j++) {
				a1 = j / (x * y);
				//printf("%d  \n", a1);
				if (a1 == 0) {
					continue;
				}
				else if (a1 == 1) {
					continue;
				}
				else if (a1 == 2) {
					h1 = 1;
				}
				a2 = j % (x * y) / y;
				a3 = j % y;

				h2 = (int)(g2 + a2 * LA) % x;
				h3 = (g3 + a3) % y;
				u = h1 * x*y + h2 * y + h3;

				//printf("j = %dのときの相方の値は%d \n", j, u);
				if (i2 == u) {
					//printf("b前の頂点への逆玄のボルテージは%d\n", j);
					for (i4 = 0;i4 < degree;i4++)
					{
						if (gyakugen_voltage[i4] == -3) {
							gyakugen_voltage[i4] = j;
							break;
						}
					}
				}

			}
		}

		//////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	}
	/*
	for (i4 = 0;i4 < degree;i4++)
	{
	if(i4 >= pp && i4 < pp + pq)
	gyakugen_voltage[i4] = voltage1[i4];
	}
	*/

	free(K);
	free(gyakugen);

	/*
	for (i = 0; i < degree;i++) {
		printf("(%d %d)", voltage1[i] % (x * y) / y, voltage1[i] % y);
	}
	printf("\n------------------\n");
	for (i = 0; i < degree;i++) {
		printf("(%d %d)", gyakugen_voltage[i] % (x * y) / y, gyakugen_voltage[i] % y);
	}
	printf("\n");
	*/
}

void voltage_make2(int *voltage1, int *gyakugen_voltage, int nodes, int degree, int n, int pp, int pq, int x, int y, int z) {

	int g1, g2, g3, a1, a2, a3, h1, h2, h3;
	int i, i2, i3, i4, j, k, u;	//カウンタ置き場
	int LA;

	//動的確保//////////////////////////////////
	int *K = (int *)malloc(degree * sizeof(int));
	int *gyakugen = (int *)malloc(nodes * sizeof(int));


	//iのボルテージを変更→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→

	i = rand() % degree;
	k = rand() % (nodes / 2);
	if (i < pp)
		j = 0;
	if (pp <= i && i < pp + pq)
		j = 1;
	if (pp + pq <= i && i < degree)
		j = 2;
	voltage1[i] = j * x*y + k / y * y + k % y;

	/*
	for (i = 0; i < degree;i++) {
	printf("最初のボルテージ %d\n", voltage1[i]);
	}
	*/
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	for (i2 = 0; i2 < nodes; i2 = i2 + nodes / 2) {//000と100について
		g1 = i2 / (x * y);
		g2 = i2 % (x * y) / y;
		g3 = i2 % y;
		LA = z % x;
		for (i3 = 0; i3 < g3; i3++)
			LA = (LA * z) % x;
		/*
		printf("-----\n");
		printf("i2 = %d\n", i2);
		printf("-----\n");
		*/
		//iの逆玄を求めるにあたって前準備→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→
		if (g1 == 0) {
			a1 = voltage1[i] / (x * y);
			if (a1 == 0) {
				h1 = 0;
			}
			else if (a1 == 1) {
				h1 = 1;
			}
			else if (a1 == 2) {
				continue;
			}
			a2 = voltage1[i] % (x * y) / y;
			a3 = voltage1[i] % y;
			h2 = (g2 + LA * a2) % x;
			h3 = (g3 + a3) % y;
			gyakugen[i] = h1 * x*y + h2 * y + h3;//次の頂点を格納
												 //printf("a次の頂点%d %d    %d\n", gyakugen[j],voltage1[j], z^LA);
		}
		else if (g1 == 1) {
			a1 = voltage1[i] / (x * y);
			if (a1 == 0) {
				continue;
			}
			else if (a1 == 1) {
				continue;
			}
			else if (a1 == 2) {
				h1 = 1;
			}

			a2 = voltage1[i] % (x * y) / y;
			a3 = voltage1[i] % y;

			h2 = (int)(g2 + LA * a2) % x;
			h3 = (g3 + a3) % y;
			gyakugen[i] = h1 * x*y + h2 * y + h3;//次の頂点を格納
												 //printf("b次の頂点%d\n", gyakugen[j]);
		}
	}


	//printf("---------\n");
	///////////////////////////////////////////////////////////////////////////////////////////



	//iの逆玄を求める→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→
	//for (i2 = 0; i2 < nodes; i2 = i2 + nodes / 2) {
	i2 = 0;
	//次の頂点をgに格納する。
	g1 = gyakugen[i] / (x * y);
	g2 = gyakugen[i] % (x * y) / y;
	g3 = gyakugen[i] % y;
	//printf("%d %d %d %d\n",g1,g2,g3,i);
	LA = z % x;
	for (i3 = 0; i3 < g3; i3++)
		LA = (LA * z) % x;
	//ボルテージがAでループしてる時→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→
	if (i < pp) {
		for (j = 0;j < 3 * x * y;j++) {
			a1 = j / (x * y);
			if (a1 == 0) {
				h1 = 0;
			}
			else if (a1 == 1) {
				continue;
			}
			else if (a1 == 2) {
				continue;
			}
			a2 = j % (x * y) / y;
			a3 = j % y;

			h2 = (int)(g2 + a2 * LA) % x;
			h3 = (g3 + a3) % y;
			u = h1 * x*y + h2 * y + h3;
			//i2がuと一致したやつらへ→→→→→→→→→→→→→→→→→
			if (i2 == u) {
				//printf("a前の頂点への逆玄のボルテージは%d\n", j)
				if (i2 < nodes / 2) {
					gyakugen_voltage[i] = j;
				}
			}
			///////////////////////////////////////////////////////////

		}
	}//////////////////////////////////////////////////////////////////////////////////////////////////

	 //ボルテージがA-Bの時→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→
	else if (pp <= i && i < pp + pq) {
		for (j = 0;j < 3 * x * y;j++) {
			a1 = j / (x * y);
			if (a1 == 0) {
				continue;
			}
			else if (a1 == 1) {
				h1 = 0;
			}
			else if (a1 == 2) {
				continue;
			}
			a2 = j % (x * y) / y;
			a3 = j % y;


			h2 = (int)(g2 + a2 * LA) % x;
			h3 = (g3 + a3) % y;
			u = h1 * x*y + h2 * y + h3;

			//i2がuと一致したやつらへ→→→→→→→→→→→→→→→→→
			if (i2 == u) {
				//printf("a前の頂点への逆玄のボルテージは%d\n", j)
				if (i2 < nodes / 2) {
					gyakugen_voltage[i] = j;
				}
			}
			///////////////////////////////////////////////////////////



		}
	}//////////////////////////////////////////////////////////////////////////////////////////////////

	 //ボルテージがBでループしてる時→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→→
	else if (i >= pp + pq) {
		i2 = nodes / 2;
		for (j = 0;j < 3 * x * y;j++) {
			a1 = j / (x * y);
			//printf("%d  \n", a1);
			if (a1 == 0) {
				continue;
			}
			else if (a1 == 1) {
				continue;
			}
			else if (a1 == 2) {
				h1 = 1;
			}

			a2 = j % (x * y) / y;
			a3 = j % y;

			h2 = (int)(g2 + a2 * LA) % x;
			h3 = (g3 + a3) % y;

			u = h1 * x*y + h2 * y + h3;
			//printf("j = %dのときの相方の値は%d \n", j, u);
			if (i2 == u) {
				//printf("a前の頂点への逆玄のボルテージは%d\n", j)
				//if (i2 < nodes / 2) {
				gyakugen_voltage[i] = j;
				//}
			}
		}
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	/*
	for (i4 = 0;i4 < degree;i4++)
	{
	if (i4 >= pp && i4 < pp + pq)
	gyakugen_voltage[i4] = voltage1[i4];
	}*/


	free(K);
	free(gyakugen);

}



///queueの関数群→→→→→→
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
////////////////////////////

void file_voltage_test(int *voltage, int *gyakugen_voltage, int nodes, int degree, int x, int y, int z, int pp, int pq, float aspla, int n) {
	FILE *outputfile;
	int i, j;
	char N[200];

	sprintf_s(N, 200, "/Users/b143471/source/repos/高速ボルテージ判断/高速ボルテージ判断/%d %d/%d %d %f (x = %d, y = %d, z = %d) (pp = %d, pq = %d) n = %d", nodes, degree, nodes, degree, aspla, x, y, z, pp, pq, n);
	fopen_s(&outputfile, N, "w");
	fprintf_s(outputfile, "%d %d  %d %d %d  %d %d\n", degree, nodes, x, y, z, pp, pq);
	for (i = 0;i < degree;i++) {
		fprintf_s(outputfile, "%d %d \n", voltage[i], gyakugen_voltage[i]);
	}
	fclose(outputfile);
}
