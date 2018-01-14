#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

typedef long long LL;
const int INF = 0x3f3f3f3f;
const LL  LNF = 0x3f3f3f3f3f3f3f3fLL;


char s[1000];

int main() {
    scanf("%s", s);
    int ans = 0;
    int len = strlen(s);
    for(int i=0; i < len; ++i) {
        if( s[i] >= '0' && s[i] <= '9' ) {
            if((s[i] - '0')&1 ) ++ans;
        } else {
            if( s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'u' || s[i] == 'o' ) ++ans;
        }
    }

    printf("%d\n", ans);
    return 0;
}