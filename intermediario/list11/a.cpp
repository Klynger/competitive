#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

#define N 1000010

char needle[N];
int patternPrefix[N];

void computePrefixes(const int SIZE) {
	int index = 0;
	for(int i = 1; i < SIZE;) {
		if (needle[i] == needle[index]) {
			patternPrefix[i] = ++index;
			i++;
		} else {
			if(index != 0)
				index = patternPrefix[index-1];
			else {
				patternPrefix[i] = 0;
				i++;
			}
		}
	}

}

void kmp(const int SIZE) {
	computePrefixes(SIZE);

	int i = 0, j = 0;
	char aux;
	bool flag = true;
	bool flag2 = true;
	scanf("\n");
	while(true) {
		if(flag){
			scanf("%c", &aux);
			flag2 = true;
		}
		
		if (aux == '\n')
			break;
		
		if(aux == needle[j]) {
			flag = true;
			j++;
		} else {
			if(j != 0) {
				flag = false;
				j = patternPrefix[j-1];
			} else {
				flag = true;
			}
		}

		if(j == SIZE) {
			printf("%lld\n", ((ll)i-(ll)SIZE+1));	
			if(j > 0)
				j = aux == needle[patternPrefix[j-1]] ? 
			patternPrefix[j-1]+1 : patternPrefix[j-1];
		}
		if(flag2)
			i++;
		flag2 = false;
	}// while
}

int main () {
	int size;
	bool flagFirst = true;
	while(scanf("%d", &size) != EOF) {
		scanf("\n");
		for(int i = 0; i < size; i++) {
			scanf("%c", &needle[i]);
		}
		if(!flagFirst)
			printf("\n");

		kmp(size);
		flagFirst = false;
	}
	

	return 0;
}