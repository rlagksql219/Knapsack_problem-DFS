#include<stdio.h>

int W = 9;
int n = 5;
int p[6] = { 0,20,30,35,12,3 };
int w[6] = { 0,2,5,7,3,1 };
int maxprofit = 0; //최대 이익
int include[6];
int bestset[6];


void knapsack(int i, int profit, int weight);
int promising(int i, int profit, int weight, int maxprofit);


int main(void) {

	knapsack(0, 0, 0);
	printf("<최대이익 : %d>\n", maxprofit);
}


//knapsack problem을 풀기위해 상태공간트리를 구축하는 함수
void knapsack(int i, int profit, int weight) {

	if (weight <= W && profit > maxprofit) { //지금까지의 best case
		maxprofit = profit;
		printf("maxprofit : %d\n", maxprofit);

		//item의 포함여부 출력
		for (int k = 0; k <= 6; k++) {
			bestset[k] = include[k];
			if (k != 0 && bestset[k] == 0) {
				printf("[item%d]:No ", k);
			}
			else if (k != 0 && bestset[k] == 1) {
				printf("[item%d]:Yes ", k);
			}

		}
		printf("\n\n");
	}

	if (promising(i, profit, weight, maxprofit)) {
		include[i + 1] = 1; //w[i+1]포함
		knapsack(i + 1, profit + p[i + 1], weight + w[i + 1]);
		include[i + 1] = 0; //w[i+1]포함하지 않음
		knapsack(i + 1, profit, weight);
	}
}


//노드가 유망한지 확인하는 함수
int promising(int i, int profit, int weight, int maxprofit) {
	int j, k;
	int totweight;
	float bound;

	if (weight >= W)
		return 0;

	else {
		j = i + 1;
		bound = profit; //초기화
		totweight = weight;

		while (j <= n && totweight + w[j] <= W) {
			totweight = totweight + w[j];
			bound = bound + p[j];
			j++;
		}
		k = j;
		if (k <= n) { //bound계산
			bound = bound + (W - totweight) * (p[k] / w[k]);
		}
		return (bound > maxprofit);
	}
}