#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define size 100

void ham(int (*arr)[size], int a)
{
	int i = 1, k = 0, j, m = 0;
	int leng = a - i - 1;
	int c = a - 1;

	if (a % 2 == 0)
		c++;

	for (k = 0; k < c / 2; k++)
	{
		leng = a - i;
		for (j = k; j < leng + k; j++)
			arr[k][j] = ++m;

		for (j = k; j < leng + k; j++)
			arr[j][a - k - 1] = ++m;

		for (j = k; j < leng + k; j++)
			arr[a - k - 1][a - 1 - j] = ++m;

		for (j = k; j < leng + k; j++)
			arr[a - 1 - j][k] = ++m;
		i += 2;
	}
	if (a % 2 != 0)
		arr[k][k] = ++m;
}

int main()
{
	int a = 0, i = 0, j = 0;
	int arr[size][size] = {0};

	printf("number under %d: ", size);
	scanf("%d", &a);

	ham(arr, a);

	for (i = 0; i < a; i++)
	{
		for (j = 0; j < a; j++)
		{
			printf("\t%d", arr[i][j]);
		}
		printf("\n");
	}

	return 0;
}
