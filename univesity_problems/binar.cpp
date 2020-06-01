//http://varena.ro/problema/binar

#include <iostream>
#include <fstream>

using namespace std;
/*Ideea consta in expandarea nodurilor arborelui,
 *si se face controlul daca este vreo pereche care se potriveste sau nu.
 *Daca s-a gasit o pereche atunci match=true,
 *si se face mai departe expandarea pana cand nu gasim o alta pereche,
 *in acest caz flag=true,s-au gasit 2 perechi,si se iese din stiva de executie,
 *sau,se face expandarea pana cand nu se gasesc valori,
 *Nodurile nu se expandeaza mai departe daca suma celor 2 noduri e mai mare decat n.
 *Arborele e simulat prin stiva implicita ce se formeaza prin recursivitate.
 */

bool flag;  //Variabila arata daca s-au gasit 2 potriviri in arbore.
			//In acest caz se iese din stiva de executie creata in "tree" recursiv,
			//si match =false,ca sunt 2 sau mai multe potriviri.
bool found; //Variabila ce arata daca s-a gasit numarul cautat prin functia find.
bool match; //Variabila ce arata daca s-a gasit vreo potrivire,Daca numarul este in arbore.
int p; //Factorul de multiplicare
long long int n; //Numerele ce trebuie validate,prima se face toate operatiile cu
				 // un numar,se scrie rezultatul in fisier,apoi se trece la urmatorul.
				 // 
	//Functia ce cauta daca este vreun nod egal cu k,numarul ce rezulta din
	//n-v,unde n e numarul din Input,iar v e un nod expandat.
void find(long long int v, long long int k)  
{
	if (v == k)
		found = true;
	else
		if ((v > k) || (found))  //Daca s-a expandat mai mult,sau found se reintoarce.
			return;
		else
		{
			find(v*p + 1, k); //Altfel cauta in partea dreapta a arborelui
			if (found)  
				return;
			find(v*p, k);  //Stanga
		}
}
void tree(long long int v)
{
	if ((v >= n) || (flag))  //Conditia de intoarcere din stiva
		return;
	tree(p*v);  //Expandarea in dreapta
	if (flag)     //Conditia de intoarcere
		return;
	tree(p*v + 1); //Expandarea in stanga
	if (flag)
		return;
	if (n - v<v) //In cazul in care e o posibila potrivire
	{
		found = false; //se reseteaza variatibla found
		find(1, n - v); //se face cautarea a celui de al 2 nod cu proprietatea
							//ca nod1+nod2=n;nodul 2 are forma n-nod1.
		if (!found)         //Daca nu s-a gasit asa nod se reintoarce in stiva.
			return;
		if (match)			//In caz contrar,daca era deja gasit o potrivire,
		{
			match = false;
			flag = true;	//Flag devine 1,si e conditia de iesire din toata stiva a arborelui.
		}
		else				//Daca nu s-a mai gasit pana acum o potrivire,Match devine 1,deci e o potrivire.
		{
			match = true;
		}
	}
}
int main()
{
	ifstream fin;
	ofstream fout;
	fin.open("binar.in");
	fout.open("binar.out");
	fin >> p;
	for (int i = 0; i<4; i++)  //Pentru fiecare numar se calculeaza rezultatul,
		                       //apoi se trece la urmatorul.
	{
		fin >> n;
		match = false;		   //Se  reseteaza match si flag pentru noul n.
		flag = false;
		tree(1);			   //Se incepe cautarea,radacina intotdeauna fiind 1.
		if (match)
			fout << 1 << " ";
		else
			fout << 0 << " ";
	}

	fin.close();
	fout.close();
	return 0;
}