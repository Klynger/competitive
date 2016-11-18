#include<bits/stdc++.h>

using namespace std;

#define N 50003
#define INF 10000

int arr[N];
int tree[N*4];


void printTree(int n) {
  for(int i = 1; i < n*3; i++)
    printf("%d ", tree[i]);
  printf("\n");
}

void create(int node, int l, int r) {
  if(l == r) {
      tree[node] = arr[l];
  
  } else {
    create(node*2, l, (l+r)/2);
    create(node*2+1, (l+r)/2+1, r);
    tree[node] = max(tree[node*2], tree[node*2+1]);
  }

}

int query(int node, int l, int r, int ql, int qr) {
  if(r < ql || qr < l) {
    printf("Aqui\n");
    return -INF;
  
  } else if(l <= ql && qr <= r) {
    return tree[node];
  
  } 

  return max(query(node*2, l, (l+r)/2, ql, qr), query(node*2+1, (l+r)/2+1, r, ql, qr));
}

void update(int node, int l, int r, int index, int value) {
  
  if(l == r && l == index) {
    arr[l] = value;
    tree[node] = value;
  } else if (l <= index && index <= r) {
    update(node*2, l, (l+r)/2, index, value);
    update(node*2+1, (l+r)/2+1, r, index, value);
    
    tree[node] = max(tree[node*2], tree[node*2+1]);
  }
  
}

int main() {
  int n;
  scanf("%d", &n);
  for(int x = 0; x < n; x++)  
    scanf("%d", &arr[x]);
  
  create(1, 0, n-1);
  printTree(n);
  int m;
  scanf("%d", &m);
  
  int op, x, y;
  for(int q = 0; q < m; q++) {
    scanf("%d %d %d", &op, &x, &y);
    if(op)
      printf("%d\n", query(1, 0, n-1, x-1, y-1));
    else {
      update(1, 0, n-1, x-1, y);
      printTree(n);
    }
  }
  
  return 0;
}



















