#include<bits/stdc++.h>

// This is a solution for the problem https://codeforces.com/contest/1133/problem/D

using namespace std;

int main() {
    int n;
    scanf("%d", &n);

    vector<int> a(n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    long double b;
    int zeros = 0;
    long long ans = 0;
    map<long double, long long> divs;
    for (int i = 0; i < n; i++) {
        scanf("%Lg", &b);

        if (a[i] == 0) {
            if (b == 0) zeros++;
            continue;
        }
        divs[b/a[i]]++;
        ans = max(ans, divs[b/a[i]]);
    }

    printf("%lld\n", ans + zeros);

    return 0;
}
