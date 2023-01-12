#define _CRT_SECURE_NO_DEPRECATE
#define _USE_MATH_DEFINES

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<locale.h>

#define pust_zn - 858993460
#define HEIGHT 6
#define WIDTH 8
#define WIDTH2 9


int** arr_memory();
int** arr_memory_fl();
int file(int** points);

int tabl(int** points);//вывод таблицы с очками игроков
int tabl2(int** points, int maxpoint[WIDTH], float sum, float** res);//заполнение массива результирующими значениями 
int printf_funct(int** points, int maxpoint[WIDTH], float sum, float** res, int c);//вывод результирующей таблицы
int no_tour(float** res);//вывод результирующей таблицы без учёта какого-либо турнира
int maximum(float** res); //поиск лучшего участника
int minimum(float** res);// поиск худшего участника
int kol_och(float** res, int arr[HEIGHT]);// поиск спортсменов, набравших более введенного количества очков
int kol_och1(float** res, int arr1[HEIGHT]);// поис спортсменов, набравших менее введеного количества 
void sort(int** points, int maxpoint[WIDTH], float sum, float** res, int numbigrok[HEIGHT]);//сортировка спортсменов по рейтингу по возрастанию
void sort1(int** points, int maxpoint[WIDTH], float sum, float** res, int numbigrok[HEIGHT]); //сортировка спорстменов по убыванию
float sr_och(float** res); // вычисляет среднее количество очков
float ob_och(float** res); // вычисляет общее количество очков
int zamena(int** points);//заменяет значения в ячейках 

int main() {
	setlocale(LC_ALL, "RUS");

	int maxpoint[WIDTH] = { 800,900,750,700,750,500,700,600 };
	int numbigrok[HEIGHT] = { 1,2,3,4,5,6 };
	int arr[HEIGHT];
	int arr1[HEIGHT];

	int c = 0;
	int k = 0;
	int x = 0;
	float sum = 0.0;

	int** points = arr_memory();
	float** res = arr_memory_fl();

	file(points);
	tabl2(points, maxpoint, sum, res);

	while (c != 13) {
		puts("Выберите пункт из представленного списка : \n1)Вывод таблицы рейтинга спортсменов\n2)Результирующая таблица\n3)Результирующая таблица без какого-либо турнира\n4)Лучший спортсмен \n5)Худший спортсмен\n6)Спортсмены, набравшие более введенного количества очков\n7)Спортсмены, набравшие менее введеного количества очков\n8)Рейтинг спортсменов по возрастанию\n9)Рейтинг спортсменов по убыванию\n10)Среднее количество очков среди спортсменов\n11)Общее количества очков всех спортсменов\n12)Замена очков\n13)Выход из программы");
		scanf("%d", &c);
		getchar();
		switch (c)
		{
		case 1:
			puts("\t\t Таблица рейтинга в 'Большем теннисе'");
			puts("   Участник|  ATP  |  WTA  |   AO   |  GS  |  RG  |  Wd  |  US OP  |  ITF |");
			tabl(points);

			break;

		case 2:

			puts("\t\t Результирующая таблица рейтинга в 'Большем теннисе'");
			puts("    Участник|    ATP  |   WTA  |   AO   |  GS  |  RG  |  Wd  |  US OP  |  ITF | Сумма очков|");
			printf_funct(points, maxpoint, sum, res, c);

			break;
		case 3:
			system("cls");
			puts("Введите номер турнира, который не будет учитываться");
			puts(" ATP - 1| WTA - 2| AO - 3| GS - 4| RG - 5| Wd - 6| US OP - 7| ITF - 8|");
			no_tour(res);

			break;

		case 4:
			puts("\n");
			printf("Лучший спортсмен %d\n", maximum(res));
			puts("\n");
			break;
		case 5:
			puts("\n");
			printf("Худший спортсмен %d\n", minimum(res));
			puts("\n");
			break;
		case 6:
			puts("\n");
			puts("Введите количество очков ");
			kol_och(res, arr);
			for (int i = 0; i < HEIGHT; i++) {
				if (arr[i] != pust_zn) {
					printf("Спортсмен %d\n", arr[i]);
				}
			}
			puts("\n");
			break;

		case 7:
			puts("\n");
			kol_och1(res, arr1);
			for (int i = 0; i < HEIGHT; i++) {
				if (arr1[i] != pust_zn) {
					printf("Спортсмен %d\n", arr1[i]);
				}
			}
			puts("\n");
			break;

		case 8:

			puts("\n");
			sort(points, maxpoint, sum, res, numbigrok);

			break;

		case 9:

			puts("\n");

			sort1(points, maxpoint, sum, res, numbigrok);

			break;

		case 10:
			puts("\n");
			printf("Среднее количество очков, набранное спортсменами : %4.2f\n", sr_och(res));
			puts("\n");
			break;

		case 11:
			puts("\n");
			printf("Общее количество очков, набранное спортсменами : %4.2f\n", ob_och(res));
			puts("\n");

		case 12:

			zamena(points);
			break;
		case 13:
			exit(EXIT_SUCCESS);
			break;

		}
	}
}

int** arr_memory()
{
	int** array = (int**)malloc(HEIGHT * sizeof(int*));
	for (int i = 0; i < HEIGHT; i++) {
		array[i] = (int*)malloc(30 * sizeof(int));
	}
	return array;
}

int** arr_memory_fl()
{
	float** array = (float**)malloc(HEIGHT * sizeof(float*));
	for (int i = 0; i < HEIGHT; i++) {
		array[i] = (float*)malloc(30 * sizeof(float));
	}
	return array;
}

int file(int** points) {
	FILE* pog;
	pog = fopen("point.txt", "r");
	if (pog == NULL) {
		printf("ERROR");
	}
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			fscanf(pog, "%d", &points[i][j]);
		}
	}
	fclose(pog);
	return points;
}


int tabl(int** points) {

	for (int i = 0; i < HEIGHT; i++)
	{
		printf("Спортсмен %d|", i + 1);
		for (int j = 0; j < WIDTH; j++) {
			printf(" %5d  ", points[i][j]);
		}puts("\n");
	}

	return points;

}

int tabl2(int** points, int maxpoint[WIDTH], float sum, float** res) {
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++) {
			res[i][j] = (float)points[i][j] / maxpoint[j];
			sum += res[i][j];
		}
		res[i][WIDTH] = sum;
		sum = 0;
	}

	return res;
}

int printf_funct(int** points, int maxpoint[WIDTH], float sum, float** res) {
	tabl2(points, maxpoint, sum, res);
	for (int i = 0; i < HEIGHT; i++)
	{
		printf("Спортсмен %d |", i + 1);
		for (int j = 0; j < WIDTH2; j++) {
			printf(" %7.2f", res[i][j]);
		}
		puts("\n");
	}
}
int no_tour(float** res) {

	int u = 0;
	puts("\n");

	scanf("%d", &u);
	getchar();

	puts("\t\t Результирующая таблица рейтинга в 'Большем теннисе'");
	puts("    Участник|     ATP    |    WTA    |    AO    |    GS   |   RG    |   Wd   |   US OP   |   ITF  | Сумма очков|");

	for (int i = 0; i < HEIGHT; i++)
	{
		printf("Спортсмен %d |", i + 1);
		for (int j = 0; j < WIDTH; j++) {
			if (j + 1 == u)  printf("         ");
			else {
				printf("   %7.2f ", res[i][j]);
			}
		} printf(" %8.2f", res[i][WIDTH] - res[i][u - 1]);
		puts("\n");
	}
}
int maximum(float** res) {
	int index = 0;
	float max = -10000.0;
	for (int i = 0; i < HEIGHT; i++) {
		if (res[i][WIDTH] > max) {
			index = i;
			max = res[i][WIDTH];

		}
	}
	return index + 1;
}


int minimum(float** res) {
	float min = 100000.0;
	int index1 = 0;
	for (int i = 0; i < HEIGHT; i++) {
		if (res[i][WIDTH] < min) {
			index1 = i;
			min = res[i][WIDTH];
		}
	}
	return index1 + 1;
}

int kol_och(float** res, int arr[HEIGHT]) {

	int x1 = 0;
	scanf("%d", &x1);

	for (int i = 0; i < HEIGHT; i++) {
		if (res[i][WIDTH] > x1) {
			arr[i] = i + 1;

		}
	}
	return;
}

int kol_och1(float** res, int arr1[HEIGHT]) {
	puts("Введите количество очков ");
	int x1 = 0;
	scanf("%d", &x1);
	for (int i = 0; i < HEIGHT; i++) {
		if (res[i][WIDTH] < x1) {
			arr1[i] = i + 1;
		}
	}
	return arr1;
}




void sort(int** points, int maxpoint[WIDTH], float sum, float** res, int numbigrok[HEIGHT]) {
	tabl2(points, maxpoint, sum, res);
	puts("\t\t Таблица рейтинга в 'Большем теннисе'");
	puts("       Участник|     ATP    |   WTA   |    AO    |    GS   |   RG    |   Wd   |   US OP   |   ITF  | Сумма очков|");
	for (int i = 0; i < HEIGHT - 1; i++)
	{

		if (res[i][WIDTH] > res[i + 1][WIDTH]) {

			for (int j = 0; j < WIDTH2; j++) {
				float t = res[i][j];
				res[i][j] = res[i + 1][j];
				res[i + 1][j] = t;
				int tvr = 0;
				tvr = numbigrok[i];
				numbigrok[i] = numbigrok[i + 1];
				numbigrok[i + 1] = tvr;
			}
		}
	}

	for (int i = 0; i < HEIGHT; i++) {
		printf("%d) спортсмен %d |", i + 1, numbigrok[i]);
		for (int j = 0; j < WIDTH2; j++) {
			printf("  %8.2f", res[i][j]);
		}
		puts("\n");
	}
	puts("\n");
	for (int i = 0; i < HEIGHT; i++) {
		numbigrok[i] = i + 1;
	}
}

void  sort1(int** points, int maxpoint[WIDTH], float sum, float** res, int numbigrok[HEIGHT]) {
	tabl2(points, maxpoint, sum, res);
	puts("\t\t Таблица рейтинга в 'Большем теннисе'");
	puts("       Участник|     ATP    |   WTA   |    AO    |    GS   |   RG    |   Wd   |   US OP   |   ITF  | Сумма очков|");
	for (int z = 0; z < HEIGHT; z++) {
		for (int i = 0; i < HEIGHT - 1; i++)
		{
			if (res[i][WIDTH] < res[i + 1][WIDTH]) {

				for (int j = 0; j < WIDTH2; j++) {
					float t = res[i][j];
					res[i][j] = res[i + 1][j];
					res[i + 1][j] = t;
					int tvr = 0;
					tvr = numbigrok[i];
					numbigrok[i] = numbigrok[i + 1];
					numbigrok[i + 1] = tvr;
				}
			}
		}
	}
	for (int i = 0; i < HEIGHT; i++) {
		printf("%d) спортсмен %d |", i + 1, numbigrok[i]);
		for (int j = 0; j < WIDTH2; j++) {
			printf("  %8.2f", res[i][j]);
		}
		puts("\n");
	}
	for (int i = 0; i < HEIGHT; i++) {
		numbigrok[i] = i + 1;
	}



}
float sr_och(float** res) {

	float sred = 0.0;
	float ressred = 0.0;
	for (int i = 0; i < HEIGHT; i++) {
		sred += res[i][WIDTH];
	}
	ressred = sred / HEIGHT;

	return ressred;
}

float ob_och(float** res) {
	float sum1 = 0.0;
	for (int i = 0; i < HEIGHT; i++) {
		sum1 += res[i][WIDTH];
	}

	return sum1;
}

int zamena(int** points) {

	int x = 0, y = 0;
	int m;
	puts("Спортсмен");
	scanf("%i", &x);
	puts("Номер турнира :| ATP - 1| WTA - 2| AO - 3| GS - 4| RG - 5| Wd - 6| US OP - 7| ITF - 8|");
	scanf("%i", &y);
	printf("Очков у спортсмена %d:", x);
	scanf("%i", &m);
	points[x - 1][y - 1] = m;

}