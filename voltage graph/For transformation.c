#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>



main() {
	//���Ԍv��
	clock_t start, end;
	start = clock();
	///////////////////

	//�錾
	FILE *fp;
	int degree, nodes;
	int D;
	float aspl = 3.234786;
	int i = 0,j = 0, m;
	int err = fopen_s(&fp, "20000 11 0.000444 100 100 23", "r");
	if (err != 0)
		printf("aaa");//�G���[����




					  //�t�@�C�����玟���ƃm�[�h����������B
	fscanf_s(fp, "%d %d", &degree, &nodes);


	//���I�m��
	int *d = (int *)malloc(degree * sizeof(int));
	int **a = (int **)malloc(nodes * sizeof(int));
	for (m = 0; m < nodes; m++)
		a[m] = (int*)malloc(degree * sizeof(int));
	int **b = (int **)malloc(nodes * sizeof(int));
	for (m = 0; m < nodes; m++)
		b[m] = (int*)malloc(degree * sizeof(int));

	//�t�@�C������e�m�[�h�Ƃ��̕ӂ�������B
	while (fscanf_s(fp, "%d", &D) != EOF) {
		while (1) {
			if (i < degree) {
				fscanf_s(fp, "%d", &d[i]);
				a[D][i] = d[i];
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

	for (i = 0;i < nodes;i++) {
		for (j = 0; j < degree; j++) {
			b[i][j] = -1;
		}
	}

	int l,awa = 0;
	//�t�@�C�����͕��@���Ԃ��t�@�C�����ɓ���
	FILE *outputfile;
	char N[100];
	sprintf_s(N, 100, "/Users/b143471/Desktop/���e���ĂȂ����/%d %d %f toukouyou", nodes ,degree,aspl);
	fopen_s(&outputfile,N, "w");
	//fprintf_s(outputfile, "%d %d\n", degree, nodes);
	for (i = 0;i < nodes;i++) {
		for (j = 0; j < degree; j++) {
			b[i][j] = a[i][j];

			for (l = 0;l < nodes;l++) {
				for (m = 0; m < degree; m++) {
					if (i == b[l][m] && a[i][j] == l)
						awa = 100;
				}
			}

			if (awa != 100)
				fprintf_s(outputfile, "%d %d\n", i, a[i][j]);
			awa = 0;

		}
	}
	fclose(outputfile);


	end = clock();
	printf("%.2f�b������܂���\n", (double)(end - start) / CLOCKS_PER_SEC);
}