#include <bits/stdc++.h>

using namespace std;

#define dbg(x) cerr << "::: " << x << endl;
#define _ << ", " <<

typedef long long ll;
typedef pair<int, int> ii;

#define DUFF(cnt, N, FUNC, CHECK)\
	int cnt = N/8;\
    switch(N%8) {\
        do {    FUNC\
        case 7: FUNC\
        case 6: FUNC\
        case 5: FUNC\
        case 4: FUNC\
        case 3: FUNC\
        case 2: FUNC\
        case 1: FUNC\
        case 0: CHECK\
        } while(cnt--);\
    }

int main() {
	ios_base::sync_with_stdio(false);
	
	DUFF(cnt, 20, 
		printf("%d\n", cnt);,
		;
	);
	
	return 0;
}
