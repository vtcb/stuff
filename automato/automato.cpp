#include <bits/stdc++.h>

using namespace std;

#define fr(a, b, c) for(int a = b; a < c; a++)

#define MAX_N 10011
#define MAX_S 101

typedef set< pair<int, int> > NDS;
typedef pair<int, char> Transition;

int alphabet_size;
vector<char> alphabet;
bool exists_in_alphabet[300];

int n, m;
vector< Transition > adj[MAX_N];

int initial_state;
int number_of_final_states;
set<int> final_states;

int q;
int mark[MAX_N][MAX_S];
int step;

bool run(const string& s) {

#define proc(a, b)\
	if(mark[a][b] != step) {\
		mark[a][b] = step;\
		next.insert( make_pair(a, b) );\
	}\

	step++;

	queue< NDS > q;
	
	NDS initial;
	initial.insert( make_pair(initial_state, 0) );
	
	q.push(initial);
	mark[initial_state][0] = step;
	
	while(!q.empty()) {
		NDS states = q.front(); q.pop();
		
		NDS next;
		
		for(NDS::iterator it = states.begin();
						  it != states.end();
						  it++) {
			pair<int, int> state = *it;
			if(state.second == s.size() && final_states.count(state.first)) {
				return true;
			}
			fr(i, 0, adj[state.first].size()) {
				Transition tr = adj[state.first][i];
				
				if(exists_in_alphabet[tr.second]) {
					if(state.second < s.size() && tr.second == s[state.second]) {
						proc(tr.first, state.second + 1);
					}
				} else { // Any element not in alphabet will be considered epsilon
					proc(tr.first, state.second);
				}
			}
		}
		
		if(!next.empty()) {
			q.push(next);
		}
	}
	
	return false;
	
#undef proc
}

int main() {
	ios_base::sync_with_stdio(false);
	
	cin >> alphabet_size;
	fr(i, 0, alphabet_size) {
		char element;
		cin >> element;
		alphabet.push_back(element);
		exists_in_alphabet[element] = true;
	}
	
	cin >> n >> m;
	
	fr(i, 0, m) {
		int u, v;
		char c;
		cin >> u >> v >> c;
		adj[u].push_back( make_pair(v, c) );
	}
	
	cin >> initial_state;
	
	cin >> number_of_final_states;
	
	fr(i, 0, number_of_final_states) {
		int st;
		cin >> st;
		final_states.insert(st);
	}
	
	cin >> q;
	
	fr(i, 0, q) {
		string s;
		cin >> s;
		
		cout << s << ": " << (run(s)?"OK":"NOPE") << endl;
	}

	return 0;
}

