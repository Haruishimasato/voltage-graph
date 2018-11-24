
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

//�֐��Q

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

	//�錾��������������������������������������������������������������������������������
	int nodes = 2300, degree = 10, n = 2, pp = 3, pq = 4;//�m�[�h�Ǝ���,�x�[�X�O���t�̐ݒ�
	int x, y, z;//�����ݒ�
	int i1, i2;//�J�E���^
	float aspla, asplb = 0, MIN;//���̑�
	int check = 0, check2 = 0;


	//�t�@�C���n��������������������������������������
	FILE *fp;
	char file[100];
	sprintf_s(file, 100, "/Users/b143471/source/repos/�����{���e�[�W���f/�����{���e�[�W���f/%d  %d",nodes ,n);

	int err = fopen_s(&fp, file, "r");
	if (err != 0)
		printf("aaa");//�G���[����

	while (fscanf_s(fp, "%d %d %d", &x, &y, &z) != EOF) {
		
		if (2 * x > y && z != 1) {
			printf("�ŏ���x,y,z��%d %d %d�ł�\n", x, y, z);
			break;
		}

	}
	/////////////////////////////////////////////////

	int *gyakugen_voltage = (int *)malloc(nodes * sizeof(int));
	int *voltage = (int *)malloc(degree * sizeof(int));//�ŏ��Ɋ���U��{���e�[�W�̃Z�b�g

	int *gyakugen_voltage2 = (int *)malloc(nodes * sizeof(int));
	int *voltage2 = (int *)malloc(degree * sizeof(int));//�ŏ��Ɋ���U��{���e�[�W�̃Z�b�g
	//////////////////////////////////////////////////////////////////////////////////////




	//voltage���쁨��������������������������������������������������������������������������
	voltage_make(voltage, gyakugen_voltage, nodes, degree, n, pp, pq, x, y, z);
	for (i1 = 0; i1 < degree;i1++) {
		voltage2[i1] = voltage[i1];
		gyakugen_voltage2[i1] = gyakugen_voltage[i1];
	}//////////////////////////////////////////////////////////////////////////////////////////


	//x = 550;y = 120;z = 13;
	 //�����O���t��aspl�v�Z����������������������������������������������������������																										
	aspla = ASPL_voltage(degree, nodes, voltage, gyakugen_voltage, x, y, z, pp, pq);
	printf("�����_���O���t��aspl = %f\n", aspla);
	MIN = aspla;
	/////////////////////////////////////////////////////////////////////////////////




	//�Ă��Ȃ܂���������������������������������������������������������������������������������������������������������������������			
	i2 = 0;
	while (1) {
		i2++;
		voltage_make2(voltage2, gyakugen_voltage2, nodes, degree, n, pp, pq, x, y, z);
		aspla = ASPL_voltage(degree, nodes, voltage2, gyakugen_voltage2, x, y, z, pp, pq);

		//�������͂��҂储������������������������������������������������������������������������������
		if (aspla < MIN) {
			MIN = aspla;
			printf("---------------------------------\n", aspla);
			printf("�ŏ��l�X�V aspl = %f\n", aspla);
			check = i2;
			check2 = i2;
			file_voltage_test(voltage2, gyakugen_voltage2, nodes, degree, x, y, z, pp, pq, aspla, n);


			//�{���e�[�W���f��������������������������������
			for (i1 = 0; i1 < degree;i1++) {
				voltage[i1] = voltage2[i1];
				gyakugen_voltage[i1] = gyakugen_voltage2[i1];
			}
			/////////////////////////////////////////////////


			//�\����������������������������������������������������������������������������������������
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
			
			//printf("���ǂł��܂��� aspl = %f\n", aspla);
			asplb = aspla;
			check = i2;

			//�{���e�[�W���f����������������������������������
			for (i1 = 0; i1 < degree;i1++) {
				voltage[i1] = voltage2[i1];
				gyakugen_voltage[i1] = gyakugen_voltage2[i1];
			}/////////////////////////////////////////////////

		}////////////////////////////////////////////////////////////////////////////////////////////////



		 //�ł����O���t���O�̂�肵��ڂ������灨������������������������������������������������
		else {
			for (i1 = 0; i1 < degree;i1++) {
				voltage2[i1] = voltage[i1];
				gyakugen_voltage2[i1] = gyakugen_voltage[i1];
			}
		}
		//////////////////////////////////////////////////////////////////////////////////////////



		//100���ƂɃ^�C���X�V����������������������������������������������������������������������
		if (i2 % 10000 == 0) {
			end = clock();
			printf(" %d ���̂� %.2f�b������܂���\n", i2, (double)(end - start) / CLOCKS_PER_SEC);
		}
		//////////////////////////////////////////////////////////////////////////////////////////////


		//nodes/4�ω����Ȃ���΂�蒼������������������������������������������������������������������������
		if (i2 % ((nodes ) + check) == 0) {

			voltage_make(voltage, gyakugen_voltage, nodes, degree, n, pp, pq, x, y, z);
			asplb = ASPL_voltage(degree, nodes, voltage, gyakugen_voltage, x, y, z, pp, pq);
			printf("���̃����_���O���t��aspl = %f\n", asplb);

			for (i1 = 0; i1 < degree;i1++) {
				voltage2[i1] = voltage[i1];
				gyakugen_voltage2[i1] = gyakugen_voltage[i1];
			}
		}
		//////////////////////////////////////////////////////////////////////////////////////////////

		
		//nodes*10��x,y,z��と��������������������������������������������������������������������
		if (i2 % ((100000 ) + check2) == 0) {
			while (fscanf_s(fp, "%d %d %d", &x, &y, &z) != EOF) {
				if (2 * x > y && z != 1) {
					MIN = 100;
					aspla = 100;
					asplb = 0;
					printf("\n����x,y,z��%d %d %d�ł�-------------------------------------------------------------------------------------------------------------------------------\n", x, y, z);
					break;
				}
			}

			//voltage���쁨��������������������������������������������������������������������������
			voltage_make(voltage, gyakugen_voltage, nodes, degree, n, pp, pq, x, y, z);
			for (i1 = 0; i1 < degree;i1++) {
				voltage2[i1] = voltage[i1];
				gyakugen_voltage2[i1] = gyakugen_voltage[i1];
			}//////////////////////////////////////////////////////////////////////////////////////////

			 //�����O���t��aspl�v�Z����������������������������������������������������������																										
			aspla = ASPL_voltage(degree, nodes, voltage, gyakugen_voltage, x, y, z, pp, pq);
			printf("�����_���O���t��aspl = %f\n", aspla);
			MIN = aspla;
			/////////////////////////////////////////////////////////////////////////////////
		}
		//////////////////////////////////////////////////////////////////////////////////////////////
		
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




	//���ԕ\��������������������������������������������������������������
	end = clock();
	printf("%.2f�b������܂���\n", (double)(end - start) / CLOCKS_PER_SEC);
	//////////////////////////////////////////////////////////////////////
}

float ASPL_voltage(int degree, int nodes, int *voltage, int *gyakugen_voltage, int x, int y, int z, int pp, int pq) {
	//�錾
	//printf("�쐬���܂�\n");
	int  v, u, j, t, o, w, yyy, i, i3, err, LA, yui = 0, max;
	float A = 0;
	int g1, g2, g3, a1, a2, a3, h1, h2 = 0, h3 = 0;
	int *s = (int *)malloc(nodes * sizeof(int));
	int *F = (int *)malloc(nodes * sizeof(int));

	//�{��
	for (w = (int)(nodes / 2) - 1; w < (int)nodes / 2 + 1; w++) {
		//	for (w =  0; w < (int)nodes; w++) {
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

			///	���̂ق�
			g1 = v / (x * y);
			g2 = v % (x * y) / y;
			g3 = v % y;


			LA = z % x;
			for (i3 = 0; i3 < g3; i3++)
				LA = (LA * z) % x;



			for (j = 0;j < degree;j++) {
				//���_A�Ń��[�v�̐��̌v�Z������������������������������������������������������������������������������������
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

					//���ʂ��i�[����������
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



				 //���_B����̂т���̌v�Z������������������������������������������������������������������������������������
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

					//���ʂ��i�[����������
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
				 //�������烋�[�v�̋t�����蓖�Ă�H��
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
		//�q�����ĂȂ��Ƃ��̃G���[����
		if (err != (nodes - 1)) {
			//printf("�q�����Ă��܂���\n");
			return 10000000;
		}


	}
	free(F);
	free(s);
	return A / (nodes - 1) / 2;
}

void voltage_make(int *voltage1, int *gyakugen_voltage, int nodes, int degree, int n, int pp, int pq, int x, int y, int z) {
	//printf("�ŏ��̃{���e�[�W�y�т��̋t��\n");
	int g1, g2, g3, a1, a2, a3, h1, h2, h3;
	int i, i2, i3, i4, j, k, u;	//�J�E���^�u����
	int LA;

	//���I�m��//////////////////////////////////
	int *K = (int *)malloc(degree * sizeof(int));
	int *gyakugen = (int *)malloc(nodes * sizeof(int));
	int *gyakugen2 = (int *)malloc(nodes * sizeof(int));


	for (i4 = 0;i4 < degree;i4++)
	{
		gyakugen_voltage[i4] = -3;
	}

	//�����O���t�쐬�y�у{���e�[�W��������������������������������������������������������������������������������������������������������������
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
	printf("�ŏ��̃{���e�[�W %d\n", voltage1[i]);
	}
	*/
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	for (i2 = 0; i2 < nodes; i2 = i2 + nodes / 2) {//���_����I��

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
		//�t�������߂�ɂ������đO������������������������������������������������������������������������������������������������������������������
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
				gyakugen[j] = h1 * x*y + h2 * y + h3;//���̒��_���i�[
													 //printf("a���̒��_%d %d %d\n", h1,h2,h3);
													 //printf("a���̒��_ %d\n", gyakugen[j]);
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
				gyakugen[j] = h1 * x*y + h2 * y + h3;//���̒��_���i�[
													 //printf("b���̒��_%d\n", gyakugen[j]);
													 //printf("b���̒��_ %d\n", gyakugen[j]);
			}
		}
		//printf("---------\n");
		///////////////////////////////////////////////////////////////////////////////////////////
	}



	//for (i2 = 0; i2 < nodes; i2 = i2 + nodes / 2) {//���_����I��
	i2 = 0;
	//�t�������߂遨����������������������������������������������������������������������������������
	for (i = 0;i < degree;i++) {
		//���̒��_��g�Ɋi�[����B

		g1 = gyakugen[i] / (x * y);
		g2 = gyakugen[i] % (x * y) / y;
		g3 = gyakugen[i] % y;
		//printf("%d %d\n",g1,gyakugen[i]);

		LA = z % x;
		for (i3 = 0; i3 < g3; i3++)
			LA = (LA * z) % x;

		//�{���e�[�W��A�Ń��[�v���Ă鎞������������������������������������������������������������������������������������
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

				//i2��u�ƈ�v�������ց���������������������������������
				if (i2 == u) {
					//printf("a�O�̒��_�ւ̋t���̃{���e�[�W��%d\n", j);
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

				//i2��u�ƈ�v�������ց���������������������������������
				if (i2 == u) {
					//printf("a�O�̒��_�ւ̋t���̃{���e�[�W��%d\n", j);
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
		//���̒��_��B�̎�������������������������������������������������������������������������������������
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

				//printf("j = %d�̂Ƃ��̑����̒l��%d \n", j, u);
				if (i2 == u) {
					//printf("b�O�̒��_�ւ̋t���̃{���e�[�W��%d\n", j);
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
	int i, i2, i3, i4, j, k, u;	//�J�E���^�u����
	int LA;

	//���I�m��//////////////////////////////////
	int *K = (int *)malloc(degree * sizeof(int));
	int *gyakugen = (int *)malloc(nodes * sizeof(int));


	//i�̃{���e�[�W��ύX��������������������������������������������������������������������������������������������������������������

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
	printf("�ŏ��̃{���e�[�W %d\n", voltage1[i]);
	}
	*/
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	for (i2 = 0; i2 < nodes; i2 = i2 + nodes / 2) {//000��100�ɂ���
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
		//i�̋t�������߂�ɂ������đO������������������������������������������������������������������������������������������������������������������
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
			gyakugen[i] = h1 * x*y + h2 * y + h3;//���̒��_���i�[
												 //printf("a���̒��_%d %d    %d\n", gyakugen[j],voltage1[j], z^LA);
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
			gyakugen[i] = h1 * x*y + h2 * y + h3;//���̒��_���i�[
												 //printf("b���̒��_%d\n", gyakugen[j]);
		}
	}


	//printf("---------\n");
	///////////////////////////////////////////////////////////////////////////////////////////



	//i�̋t�������߂遨����������������������������������������������������������������������������������
	//for (i2 = 0; i2 < nodes; i2 = i2 + nodes / 2) {
	i2 = 0;
	//���̒��_��g�Ɋi�[����B
	g1 = gyakugen[i] / (x * y);
	g2 = gyakugen[i] % (x * y) / y;
	g3 = gyakugen[i] % y;
	//printf("%d %d %d %d\n",g1,g2,g3,i);
	LA = z % x;
	for (i3 = 0; i3 < g3; i3++)
		LA = (LA * z) % x;
	//�{���e�[�W��A�Ń��[�v���Ă鎞������������������������������������������������������������������������������������
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
			//i2��u�ƈ�v�������ց���������������������������������
			if (i2 == u) {
				//printf("a�O�̒��_�ւ̋t���̃{���e�[�W��%d\n", j)
				if (i2 < nodes / 2) {
					gyakugen_voltage[i] = j;
				}
			}
			///////////////////////////////////////////////////////////

		}
	}//////////////////////////////////////////////////////////////////////////////////////////////////

	 //�{���e�[�W��A-B�̎�������������������������������������������������������������������������������������
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

			//i2��u�ƈ�v�������ց���������������������������������
			if (i2 == u) {
				//printf("a�O�̒��_�ւ̋t���̃{���e�[�W��%d\n", j)
				if (i2 < nodes / 2) {
					gyakugen_voltage[i] = j;
				}
			}
			///////////////////////////////////////////////////////////



		}
	}//////////////////////////////////////////////////////////////////////////////////////////////////

	 //�{���e�[�W��B�Ń��[�v���Ă鎞������������������������������������������������������������������������������������
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
			//printf("j = %d�̂Ƃ��̑����̒l��%d \n", j, u);
			if (i2 == u) {
				//printf("a�O�̒��_�ւ̋t���̃{���e�[�W��%d\n", j)
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



///queue�̊֐��Q������������
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
////////////////////////////

void file_voltage_test(int *voltage, int *gyakugen_voltage, int nodes, int degree, int x, int y, int z, int pp, int pq, float aspla, int n) {
	FILE *outputfile;
	int i, j;
	char N[200];

	sprintf_s(N, 200, "/Users/b143471/source/repos/�����{���e�[�W���f/�����{���e�[�W���f/%d %d/%d %d %f (x = %d, y = %d, z = %d) (pp = %d, pq = %d) n = %d", nodes, degree, nodes, degree, aspla, x, y, z, pp, pq, n);
	fopen_s(&outputfile, N, "w");
	fprintf_s(outputfile, "%d %d  %d %d %d  %d %d\n", degree, nodes, x, y, z, pp, pq);
	for (i = 0;i < degree;i++) {
		fprintf_s(outputfile, "%d %d \n", voltage[i], gyakugen_voltage[i]);
	}
	fclose(outputfile);
}
