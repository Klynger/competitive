#include<bits/stdc++.h>

// https://codeforces.com/contest/1133/problem/C

using namespace std;

int main() {
    int n;
    scanf("%d", &n);
    int arr[n];

    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    sort(arr, arr+n);

    int maxSum = 1;
    int local = 1;
    int j = 1;
    int i = 0;
    while (i < n - 1 && j < n) {
        if (arr[j] - arr[i] <= 5) {
            local++;
            j++;
        } else {
            i++;
            local--;
        }
        maxSum = max(maxSum, local);
    }
    printf("%d\n", maxSum);

    return 0;
}
