#include <bits/stdc++.h>
#define lli long long int
#define mod 1000000007
#define pb push_back
#define INF 1e18
#define SIZE 100010

using namespace std;

vector<lli> adj[SIZE];
lli babyface[SIZE]; //to check which are to be included in babyfaces
bool visited[SIZE]; //for dfs only

//performing dfs to check if the graph creted in the rivalries
//is bipartite or not
//if yes we get the answer ,else its impossible

bool dfs(lli s, lli parent) {
	visited[s] = 1;
	lli i, v;
	babyface[s] = 1 - babyface[parent]; //assigning the nodes value fiffernt to its
										//parents if babyface[parent] = 0,babyface[s] = 1
										//if babyface[parent] = 1,babyface[s] = 0

	for (i = 0; i < adj[s].size(); i++) {
		v = adj[s][i];
		if (!visited[v]) {
			dfs(v, s);
		} else {
			if (babyface[v] == babyface[s]) //if two adjancent nodes have same value graph is not bipartite
				return 0;                                     //return false
		}
	}
	return 1;                                     //return true
}

int main() {

	lli n, i, j, k, u, v, r;
	string str, rival1, rival2;

	map<string, lli> m;                        //for assigning each name a index

	cin >> n;
	string names[n + 1];                       //for storing the name with index

	for (i = 1; i <= n; i++) {
		cin >> str;
		m[str] = i;
		names[i] = str;
	}

	cin >> r;

	for (i = 1; i <= r; i++) {
		cin >> rival1 >> rival2;
		u = m[rival1];
		v = m[rival2];                           //getting indeices of the names
		adj[u].pb(v);
		adj[v].pb(u);                                //adding edges to the graph
	}

	memset(babyface, 0, sizeof babyface);    //make all wrestlers as heels first
	memset(visited, 0, sizeof visited);        //for dfs all nodes are unvisited

	babyface[0] = 0;    //dummy parent for all roots in the connected components
						//for assigning the nodes

	bool possible = 1;
	//perform dfs for all the connected components and get a possible answer
	for (i = 1; i <= n; i++) {
		if (visited[i])
			continue;
		possible = dfs(i, 0);
		if (!possible)         //if not bipartite the partitioning is impossible
			break;
	}

	if (!possible) {
		cout << "Impossible " << endl;
		return 0;
	}

	//for storing the names of the two types
	vector<string> babyfaces, heels;

	for (i = 1; i <= n; i++) {
		if (babyface[i])
			babyfaces.pb(names[i]);
		else
			heels.pb(names[i]);
	}

	cout << "Yes\n";
	cout << "Babyfaces:";
	for (i = 0; i < babyfaces.size(); i++)
		cout << babyfaces[i] << " ";
	cout << endl;

	cout << "Heels:";
	for (i = 0; i < heels.size(); i++)
		cout << heels[i] << " ";
	cout << endl;

	return 0;
}
