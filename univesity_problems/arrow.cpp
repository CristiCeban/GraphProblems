//https://www.pbinfo.ro/?pagina=probleme&id=1049

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

int n, m, test, pozstartx, pozstarty,nFav,pctMax,nr,x,y,tk,c,l,nr1,val;
int Max = 0;
int **matrice;
int **matriceVis;
int **ciclu;
int moveX[5] = { 0,0,-1,0,1 };
int moveY[5] = { 0,1,0,-1,0 };
FILE *fin, *fout;

int isSafe(int x, int y) 
{
	if (x > 0 && x <= n && y > 0 && y <= m)
		return 1;
	return 0;
}
void citire()
{
	fin = fopen("arrows.in", "r");
	fout = fopen("arrows.out", "w");
	fscanf(fin, "%d %d %d", &test, &n, &m);
	matrice = (int**)malloc(sizeof(int*)*n+1);
	for (int i = 1; i<=n; i++)
	{
		matrice[i] = (int*)malloc(sizeof(int)*m+1);
	}
	for (int i = 1; i<=n; i++)
	{
		for (int j = 1; j<=m; j++)
		{
			fscanf(fin, "%d", &matrice[i][j]);
		}
	}
	fscanf(fin, "%d %d", &pozstartx, &pozstarty);
	matriceVis = (int**)malloc(sizeof(int*)*n+2);
	for (int i = 0; i<=n+1; i++)
	{
		matriceVis[i] = (int*)malloc(sizeof(int)*m+2);
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			matriceVis[i][j] = 0;
		}
	}
	for(int i=0;i<m+1;i++)
	{
		matriceVis[0][i] = matriceVis[n + 1][i] = -1;
	}
	for(int i=0;i<n+1;i++)
	{
		matriceVis[i][0] = matriceVis[i][m+1] = -1;
	}
	ciclu = (int**)malloc(sizeof(int*)*n+1);
	for(int i=1;i<=n;i++)
	{
		ciclu[i] = (int*)malloc(sizeof(int)*m+1);
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			ciclu[i][j] = 0;
		}
	}
}
void rezolvare()
{
	int nrmax =n*m*1000;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if (matriceVis[i][j] == 0)
			{
				nr = nrmax; x = i; y = j;
				while (isSafe(x, y) && matriceVis[x][y] == 0)
				{
					nr++;
					matriceVis[x][y] = nr;
					int dir = matrice[x][y];
					x += moveX[dir];
					y += moveY[dir];
				}
				if (isSafe(x, y))
				{
					if (matriceVis[x][y] > nrmax)
					{
						nr -= nrmax;
						tk += nr;
						int l = x;
						c = y;
						nr1 = matriceVis[x][y] - nrmax;
						int val = (nr - nr1 + 1) * 1000;
						if (val > Max)
							Max = val;
						do
						{
							matriceVis[x][y] = val;
							ciclu[x][y] = 1;
							int dir = matrice[x][y];
							x += moveX[dir];
							y += moveY[dir];
						} while (!(l == x&&c == y));
						if (!(x == i&&y == j))
						{
							val = matriceVis[l][c];
							nr = nr1 - 1;
							l = i;
							c = j;
							if (nr * 1000 + val > Max)
								Max = nr * 1000 + val;
							while (!(l == x&&c == y))
							{
								matriceVis[l][c] = nr * 1000 + val;
								ciclu[l][c] = 1;
								nr--;
								int dir = matrice[l][c];
								l += moveX[dir];
								c += moveY[dir];
							}
						}
					}
					else
						if (ciclu[x][y] == 1) {
							tk =tk + nr - nrmax;
							val = matriceVis[x][y];
							nr -= nrmax;
							l = i;
							c = j;
							if (nr * 1000 + val > Max)
								Max = nr * 1000 + val;
							while (!(l == x&&c == y))
							{
								matriceVis[l][c] = nr * 1000 + val;
								ciclu[l][c] = 1;
								nr--;
								int dir = matrice[l][c];
								l += moveX[dir];
								c += moveY[dir];
							}
						}
						else
						{
							val = matriceVis[x][y];
							nr -= nrmax;
							l = i;
							c = j;
							if (nr + val > Max)
								Max = nr + val;
							while (!(l == x&&c == y))
							{
								matriceVis[l][c] = nr + val;
								nr--;
								int dir = matrice[l][c];
								l += moveX[dir];
								c += moveY[dir];
							}
						}
				}
				else
				{
					l = i;
					c = j;
					nr -= nrmax;
					while(isSafe(l,c))
					{
						matriceVis[l][c] = nr--;
						int dir = matrice[l][c];
						l += moveX[dir];
						c += moveY[dir];
					}
					if (matriceVis[i][j] > Max)
						Max = matriceVis[i][j];
				}
			}
		}
	}
}
int main()
{
	citire();
	rezolvare();
	if(test==1)
	{
		fprintf(fout, "%d", matriceVis[pozstartx][pozstarty]);
	}
	else if(test==2)
	{
		fprintf(fout, "%d", tk);
	}
	else
	{
		fprintf(fout, "%d", Max);
	}
	fclose(fin);
	fclose(fout);
	return 0;
	
}