//https://www.pbinfo.ro/?pagina=probleme&id=1572

#include<iostream>
#include <fstream>
#include <list> 
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#define NIL -1 
using namespace std;

ifstream fin;
ofstream fout;
vector<int> vect;
string str;
vector<set<int>> myset;
int count1 = 0;
int iter = 0;
class edge
{
public:
	int u;
	int v;
	edge(int u, int v);
};
edge::edge(int u, int v)
{
	this->u = u;
	this->v = v;
}
class Graph
{
	int V;
	int E;
	list<int> *adj;
	void APUtil(int v, bool visited[], int disc[], int low[],
		int parent[], bool ap[]);
	void bridgeUtil(int v, bool visited[], int disc[], int low[],
		int parent[]);
	void BCCUtil(int u, int disc[], int low[],
		list<edge>* st, int parent[]);
public:
	Graph(int V);
	void addEdge(int v, int w);
	void AP();
	void bridge();
	void BCC();
};

Graph::Graph(int V)
{
	this->V = V;
	this->E = 0;
	adj = new list<int>[V];
}
void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w);
	adj[w].push_back(v);
	E++;
}
void Graph::APUtil(int u, bool visited[], int disc[],
	int low[], int parent[], bool ap[])
{
	static int time = 0;

	int children = 0;

	visited[u] = true;

	disc[u] = low[u] = ++time;


	list<int>::iterator i;
	for (i = adj[u].begin(); i != adj[u].end(); ++i)
	{
		int v = *i;


		if (!visited[v])
		{
			children++;
			parent[v] = u;
			APUtil(v, visited, disc, low, parent, ap);

			low[u] = min(low[u], low[v]);


			if (parent[u] == NIL && children > 1)
				ap[u] = true;

			if (parent[u] != NIL && low[v] >= disc[u])
				ap[u] = true;
		}


		else if (v != parent[u])
			low[u] = min(low[u], disc[v]);
	}
}
void Graph::AP()
{
	int *disc = new int[V];
	bool *visited = new bool[this->V];
	int *low = new int[V];
	int *parent = new int[V];
	bool *ap = new bool[V];


	for (int i = 0; i < V; i++)
	{
		parent[i] = NIL;
		visited[i] = false;
		ap[i] = false;
	}

	for (int i = 0; i < V; i++)
		if (visited[i] == false)
			APUtil(i, visited, disc, low, parent, ap);

	vector<int> vect;
	for (int i = 0; i < V; i++)
		if (ap[i] == true)
			vect.push_back(i + 1);
	fout << vect.size() << endl;
	for (int i = 0; i<vect.size(); i++)
	{
		fout << vect[i] << " ";
	}
}
void Graph::bridgeUtil(int u, bool visited[], int disc[],
	int low[], int parent[])
{
	static int time = 0;

	visited[u] = true;
	disc[u] = low[u] = ++time;

	list<int>::iterator i;
	for (i = adj[u].begin(); i != adj[u].end(); ++i)
	{
		int v = *i;

		if (!visited[v])
		{
			parent[v] = u;
			bridgeUtil(v, visited, disc, low, parent);
			low[u] = min(low[u], low[v]);
			if (low[v] > disc[u]) {
				vect.push_back(u + 1);
				vect.push_back(v + 1);
			}
		}
		else if (v != parent[u])
			low[u] = min(low[u], disc[v]);
	}
}
void Graph::bridge()
{
	bool *visited = new bool[V];
	int *disc = new int[V];
	int *low = new int[V];
	int *parent = new int[V];
	for (int i = 0; i < V; i++)
	{
		parent[i] = NIL;
		visited[i] = false;
	}
	for (int i = 0; i < V; i++)
		if (visited[i] == false)
			bridgeUtil(i, visited, disc, low, parent);
}
void Graph::BCCUtil(int u, int disc[], int low[], list<edge>* st,
	int parent[])
{
	static int time = 0;
	disc[u] = low[u] = ++time;
	int children = 0;
	list<int>::iterator i;
	for (i = adj[u].begin(); i != adj[u].end(); ++i) {
		int v = *i;

		if (disc[v] == -1) {
			children++;
			parent[v] = u;
			st->push_back(edge(u, v));
			BCCUtil(v, disc, low, st, parent);
			low[u] = min(low[u], low[v]);
			if ((disc[u] == 1 && children > 1) || (disc[u] > 1 && low[v] >= disc[u])) {
				while (st->back().u != u || st->back().v != v) {
					myset[iter].insert(st->back().u+1);
					myset[iter].insert(st->back().v + 1);
					st->pop_back();
				}
				myset[iter].insert(st->back().u + 1);
				myset[iter].insert(st->back().v + 1);
				iter++;
				st->pop_back();
				count1++;
			}
		}
		else if (v != parent[u]) {
			low[u] = min(low[u], disc[v]);
			if (disc[v] < disc[u]) {
				st->push_back(edge(u, v));
			}
		}
	}
}
void Graph::BCC()
{
	int* disc = new int[V];
	int* low = new int[V];
	int* parent = new int[V];
	list<edge>* st = new list<edge>[E];

	for (int i = 0; i < V; i++) {
		disc[i] = NIL;
		low[i] = NIL;
		parent[i] = NIL;
	}

	for (int i = 0; i < V; i++) {
		if (disc[i] == NIL)
			BCCUtil(i, disc, low, st, parent);

		int j = 0;
		while (st->size() > 0) {
			j = 1;
			myset[iter].insert(st->back().u + 1);
			myset[iter].insert(st->back().v + 1);
			st->pop_back();
		}
		if (j == 1) {
			count1++;
			iter++;
		}
	}
}
void printSol()
{
	for (int i = 0; i < count1; i++) {
		fout << myset[i].size() << " ";
		for (set<int>::iterator iter = myset[i].begin(); iter != myset[i].end(); iter++)
		{
			fout << *iter << " ";
		}
		fout << endl;
	}
}
int main()
{
	int test = 0;
	int n, m, u, v;
	fin.open("componentebiconexe.in");
	fout.open("componentebiconexe.out");
	fin >> test >> n >> m;
	Graph g(n);
	myset.resize(n);
	for (int i = 0; i<m; i++)
	{
		fin >> u >> v;
		u--; v--;
		g.addEdge(u, v);
	}
	if (test == 1)
	{
		g.BCC();
		fout << count1 << endl;
		printSol();
	}
	if (test == 2) {
		g.AP();
	}
	if (test == 3)
	{
		g.bridge();
		fout << vect.size() / 2 << endl;
		for (int i = 0; i<vect.size(); i = i + 2)
		{
			fout << vect[i] << " " << vect[i + 1] << endl;
		}
	}
	fin.close();
	fout.close();
	return 0;
}