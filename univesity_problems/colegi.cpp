//https://www.pbinfo.ro/?pagina=probleme&id=2268

#include <iostream>
#include <map>
#include <string>
using namespace std;

int main()
{
	map<string, int> m;
	map<string, int>::iterator it;
	int n;
	string s;
	cin >> n;
	for(int i=0;i<n;i++)
	{
		cin >> s;
		it = m.find(s);
		if (it!=m.end())
		{
			m[s] +=1;
		}
		else
		{
			m.insert(pair<string, int>(s, 1));
		}
		
	}
	int max = 0;
	string nume;
	for (it = m.begin(); it != m.end(); it++)
		if (max < it->second) {
			max = it->second;
			nume = it->first;
		}
	cout << nume<<' '<<max;
}