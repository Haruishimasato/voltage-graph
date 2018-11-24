
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>


main() {
	srand(212);
	//���ԑ���
	clock_t start, end;
	start = clock();

	//�錾//////////////////////////////////////

	int nodes = 2300,  n = 2;//�m�[�h�Ǝ���,�x�[�X�O���t�̐ݒ�
	int i, j , k ,m = 0 ;	//�J�E���^�u����
	int voltage_count;
	int *xyzx = (int *)malloc(nodes * sizeof(int));//z^y=1modx�̑g�ݍ��킹
	int *xyzy = (int *)malloc(nodes * sizeof(int));
	int *xyzz = (int *)malloc(nodes * sizeof(int));
	FILE *outputfile;


	//x,y,z�̏����ݒ�/////////////////////////�l�̎�ł��ق����ǂ�����
	int ta,l;
	for (i = 1;i <(int)nodes /n ; i++) {
		if (nodes % (n *i) == 0)
		{
			j = nodes / (n *i);

			for (k = 0; k < j; k++) {
				l = k % i;
				for (ta = 0; ta < j - 1;ta++) {
					l = (l*k) % i;
				}
				if (l == 1) {
					xyzx[m] = i;
					xyzy[m] = j;
					xyzz[m] = k;
					m++;
				}
			}
		}
		printf("%d\n", i);
	}

	for (i = 0; i < m; i++) {
		printf("%d %d %d\n", xyzx[i], xyzy[i], xyzz[i]);
	}
	fopen_s(&outputfile, "xyz", "w");
	for (i = 0;i < m;i++) {
		fprintf_s(outputfile, "%d ", xyzx[i]);
		fprintf_s(outputfile, "%d ", xyzy[i]);
		fprintf_s(outputfile, "%d \n", xyzz[i]);
	}
	fclose(outputfile);
	


	//���ԕ\��
	end = clock();
	printf("%.2f�b������܂���\n", (double)(end - start) / CLOCKS_PER_SEC);


	

	FILE *timep;
	char N[300];
	//time_t time(time_t *t);
	time_t t = time(NULL);
	struct tm local;
	localtime_s(&local, &t);

	sprintf_s(N, 300, "/Users/b143471/source/repos/�����{���e�[�W���f/�����{���e�[�W���f/%d  %d",nodes,n);
	fopen_s(&timep, N, "w");
	for (i = 0;i < m;i++) {
		fprintf_s(timep, "%d ", xyzx[i]);
		fprintf_s(timep, "%d ", xyzy[i]);
		fprintf_s(timep, "%d \n", xyzz[i]);
	}

	fclose(timep);

	
}