/**
 * @date    2017/12/23
 * @author  lemon clown
 * @contest 907
 * @tag     水题
 */

#include <cstdio>
#include <algorithm>
using namespace std;


int main() {
    int a, b, c, d;
    scanf("%d%d%d%d", &a, &b, &c, &d);
    if( d > 2*c ) printf("-1\n");
    else {
        int x = max(c, d);
        int y = max(b, d*2+1);
        int z = max(a, d*2+1);
        y = max(x+1, y);
        z = max(y+1, z);

        if( x <= 2*d && x <= 2*c && y <= 2*b && z <= 2*a ) printf("%d\n%d\n%d\n", z, y, x);
        else printf("-1\n");
    }
    return 0;
}