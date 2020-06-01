//https://infonline.pbinfo.ro/?pagina=probleme&id=2041

#define _CRT_SECURE_NO_WARNINGS

#include <queue>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
struct cell
{
	int x, y;
	int dis;
	cell() {}
	cell(int x, int y, int dis) : x(x), y(y), dis(dis) {}
};

//Functie pentru a vedea daca nu iesim din hotarele tablei de sah.
bool isInside(int x, int y, int N, int M)
{
	if (x >= 0 && x < N && y >= 0 && y < M)
		return true;
	return false;
}

int Target(int **knightPos, int targetPos[],
	int N, int M, int K, int test)
{
	//Ideea consta ca pornim din castel,si vizitam toate spozitiile tablei de sah,
	//iar daca una din pozitii(stari) e un cavaler ,distanta pana la el o introducem
	//in vectorul vecRes,care apoi il sortam si in functie de ceea ce ne trebuie
	//afisam sau distanta minima dintre cavaleri
	//sau distanta maxima a tuturor cavalerilor.
	vector<int> vecRes;
	//Pozitiile unde se poate misca calul.
	int dx[] = { -2, -1, 1, 2, -2, -1, 1, 2 };
	int dy[] = { -1, -2, -2, -1, 1, 2, 2, 1 };

	// Coada pentru a stoca starile calului in tabla de sah.
	queue<cell> q;

	// Prima stare a Coadei e insusi castelul,si distanta e 0.
	q.push(cell(targetPos[0], targetPos[1], 0));

	cell t;
	int x, y;
	bool **visit = new bool*[N];
	for (int i = 0; i<N; i++)
	{
		visit[i] = new bool[M];
	}


	// Toate celulele le facem nevizitate
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			visit[i][j] = false;

	// vizitam prima stare,insusi casteluk
	visit[targetPos[0]][targetPos[1]] = true;

	// Ciclam atat timp cat avem elemente in stiva
	while (!q.empty())
	{
		t = q.front();
		q.pop();

		// Daca celula curenta e egala cu celula cautata(a unui dintre cai),
		// Returnam distanta ei.
		for (int i = 0; i < K; i++) {
			if (t.x == knightPos[i][0] && t.y == knightPos[i][1]) {
				vecRes.push_back(t.dis);
			}
		}

		// Trecem prin toate miscarile posibile
		for (int i = 0; i < 8; i++)
		{
			x = t.x + dx[i];
			y = t.y + dy[i];

			// Daca celula urmatoare nu e vizitata,si e in hotarele tablei de sah,
			// Introducem starea curenta in stiva.
			if (isInside(x, y, N, M) && !visit[x][y]) {
				visit[x][y] = true;
				q.push(cell(x, y, t.dis + 1));
			}
		}
	}
	sort(vecRes.begin(), vecRes.end());//sortam vectorul distantelor cailor pana la castel
	if (test == 1)
	{
		return vecRes[0];
	}
	else
	{
		return vecRes[K - 1];
	}
}

int main()
{
	ifstream fin;
	ofstream fout;
	int test, N, M, K, u, v;
	int targetPos[2] = { 0,0 };
	int **knightPos; //Coordonatele tuturor cavalerilor
	fin.open("camelot.in");
	fout.open("camelot.out");
	fin >> test >> N >> M >> K >> targetPos[0] >> targetPos[1]; //Citim datele.
	targetPos[0]--; targetPos[1]--; // Facem transformarea pentru indexarea in C.
	knightPos = new int*[K]; //alocam dinamic matricea cavalerilor,
							 //sunt k cavaleri,fiecare cu cate 2 coordonate,X si Y.
	for (int i = 0; i<K; i++)
	{
		knightPos[i] = new int[2];
	}
	for (int i = 0; i<K; i++) //Le citim.
	{
		fin >> u >> v;
		u--; v--;
		knightPos[i][0] = u;
		knightPos[i][1] = v;

	}
	fout << Target(knightPos, targetPos, N, M, K, test);
	fin.close();
	fout.close();
	return 0;
}