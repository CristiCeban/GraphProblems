//https://www.pbinfo.ro/?pagina=probleme&id=2282

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
int findParent(int i, int parent[])
{
	if (parent[parent[i]] != parent[i])
		parent[i] = findParent(parent[i], parent);
	return parent[i];
}
int nr = 5;
void unionNodes(int a, int b, int parent[], int size[])
{
	int parent_a = findParent(a, parent), parent_b = findParent(b, parent);
	if (parent_a == parent_b)
		return;
	if (size[parent_a] >= size[parent_b])
	{
		size[parent_a] += size[parent_b];
		parent[parent_b] = parent_a;
	}
	else
	{
		size[parent_b] += size[parent_a];
		parent[parent_a] = parent_b;
	}
	return;
}

int main()
{
	int N, M, a, b;
	scanf("%d%d", &N, &M);
	int componenteConexe = N;
	int *parent = (int*)malloc(sizeof(int)*N + 1);
	int *size = (int *)malloc(sizeof(int)*N + 1);
	int **MatrixEdge = (int**)malloc(sizeof(int*)*M + 1);
	int *sol = (int*)malloc(sizeof(int)*M);
	for (int i = 0; i <= M; i++)
	{
		MatrixEdge[i] = (int*)malloc(sizeof(int) * 2);
	}
	for (int i = 1; i <= N; i++)
	{
		parent[i] = i;
		size[i] = 1;
	}

	for (int i =1; i <=M; i++)
	{
		scanf(" %d %d", &a, &b);
		MatrixEdge[i][0] = a;
		MatrixEdge[i][1] = b;
	}
	int *vecsol = (int*)malloc(sizeof(int)*M+1);
	int iter = 1;
	for (int k = M; k >=1; k--) {
		if (findParent(MatrixEdge[k][0], parent)!=findParent(MatrixEdge[k][1],parent))
			componenteConexe--;
		vecsol[iter] = componenteConexe;
		iter++;
		unionNodes(MatrixEdge[k][0], MatrixEdge[k][1], parent, size);
	}
	vecsol[0] = N;
	for(int i=M-1;i>=0;i--)
	{
		printf("%d\n", vecsol[i]);
	}
	return 0;
}