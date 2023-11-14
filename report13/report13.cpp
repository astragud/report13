#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 50
#define INF 100

typedef struct GraphType // 그래프 정의
{
	int n; // 정점의 개수
	int weight[MAX_VERTICES][MAX_VERTICES]; //인접행렬
} GraphType;

int A[MAX_VERTICES][MAX_VERTICES]; // 최단 거리를 저장하는 배열
int path[MAX_VERTICES][MAX_VERTICES]; // 최단 경로를 저장하기 위한 배열

// 그래프 정보를 출력하는 함수
void print_vertice(GraphType* g)
{
	printf("================================\n");
	for (int i = 0; i < g->n; i++)
	{
		for (int j = 0; j < g->n; j++)
		{
			if (A[i][j] == INF)
			{
				printf(" * ");
			}
			else
			{
				printf("%2d ", A[i][j]);
			}
		}
		printf("\n");
	}
	printf("================================\n");
}

//최단 경로 출력 함수
void print_path(int start, int end)
{
	if (start == end)
	{
		printf("%d ", start);
	}

	else if (path[start][end] == -1)
	{
		printf("%d ", start);
	}

	else
	{
		int via = path[start][end];
		print_path(start, via);
		printf("%d ", end);
	}
}

// Floyd-Warshall 알고리즘
void floyd(GraphType* g)
{
	int i, j, k;
	for (i = 0; i < g->n; i++)
	{
		for (j = 0; j < g->n; j++)
		{
			A[i][j] = g->weight[i][j];
			if (i != j && A[i][j] != INF)
			{
				path[i][j] = i; // i에서 j로 가는 최단 경로의 중간 정점은 i로 초기화
			}

			else
			{
				path[i][j] = -1; // 경로가 없는 경우 -1로 초기화
			}
		}
	}

	for (k = 0; k < g->n; k++)
	{
		for (i = 0; i < g->n; i++)
		{
			for (j = 0; j < g->n; j++)
			{
				if (A[i][k] + A[k][j] < A[i][j])
				{
					A[i][j] = A[i][k] + A[k][j]; // 최단 거리 업데이트
					path[i][j] = path[k][j]; // 최단 경로 업데이트
				}
			}
		}
	}
}

int main()
{
	GraphType g = { 10,
		{{ 0, 3, INF, INF, INF, 11, 12, INF, INF, INF },
		{ 3, 0, 5, 4, 1, 7, 8, INF, INF, INF },
		{ INF, 5, 0, 2, INF, INF, 6, 6, INF, INF },
		{ INF, 4, 2, 0, 13, INF, INF, 14, INF, 16 },
		{ INF, 1, INF, 13, 0, 9, INF, INF, 18, 17 },
		{ 11, 7, INF, INF, 9, 0, INF, INF, INF, INF },
		{ 12, 8, 6, INF, INF, INF, 0, 13, INF, INF },
		{ INF, INF, 5, 14, INF, INF, 13, 0, INF, 15 },
		{ INF, INF, INF, INF, 18, INF, INF, INF, 0, 10 },
		{ INF, INF, INF, 16, 17, INF, INF, 15, 10, 0 }}
	};

	floyd(&g);

	int start, end;
	printf("Floyd-Warshall Algorithm\n");
	
	for (int i = 0; i < 3; i++)
	{
		printf("start node: ");
		scanf_s("%d", &start);
		printf("end node: ");
		scanf_s("%d", &end);

		printf("shortest distance: %d\n", A[start - 1][end - 1]);
		printf("shortest path: ");
		print_path(start, end);
		printf("\n\n");
	}

	return 0;
}