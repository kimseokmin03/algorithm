#include <stdio.h>
#include <algorithm>
#include <cstring>

using namespace std;

int w[10000];
int p[10000];
int memo[10000][10000];

int knap(int i, int n, int capacity) {
	if(i==n){
        return 0;
    }
    if(memo[i][capacity] != -1){
        return memo[i][capacity];
    }

    int result;
    if(capacity<w[i]){
        result = knap(i+1,n,capacity);
    }else{
        result = max(knap(i+1,n,capacity), p[i] + knap(i+1,n,capacity-w[i]));
    }
    return memo[i][capacity]=result;
}

void check_item(int n, int capacity) {
	int current_capacity = capacity;

	for (int i = 0;i < n;i++) {
		int value_now = knap(i, n, current_capacity);
		int value_skip = knap(i + 1, n, current_capacity);
		if (value_now != value_skip) {
			printf("%d��° -> %d, %d\n", i + 1, p[i], w[i]);
			current_capacity -= w[i];
		}
	}
}

int main() {
	int n, m;
	memset(memo, -1, sizeof(memo));
	FILE* fp;
	fopen_s(&fp, "knapsack_input.txt", "r");
	fscanf_s(fp, "%d %d", &n, &m);
	for (int i = 0;i < n;i++) {
		fscanf_s(fp, "%d %d", &p[i], &w[i]);
	}
	printf("�ִ� ��ġ: %d\n", knap(0, n, m));
	printf("���õ� ������:\n");
	check_item(n, m);
	fclose(fp);
	return 0;
}