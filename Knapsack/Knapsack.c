# include <stdlib.h>
# include <stdio.h>
# include "Knapsack.h"

extern unsigned num;
extern OBJ object[];
extern float knapsack;

int main() {
	for ( unsigned i = 0; i < num; i ++ )
		object[i].performance = object[i].value / object[i].weight;
	sortObject(object, num);
	
	float wei, val;
	for(unsigned i=0; i<num; i++) {
		if(object[i].weight > knapsack) {
			wei = object[i].weight - knapsack;
			val = object[i].performance * wei;
			knapsack = 0;
			printf("%sを%.1fkg\n", object[i].name, wei);
		}
		else if(object[i].weight < knapsack) {
			knapsack -= object[i].weight;
			printf("%sを%.1fkg\n", object[i].name, object[i].weight);
		}
		if(knapsack == 0) break;
	}
	return 0;
}

void sortObject(OBJ obj[], unsigned n) {
	OBJ tmp;
	for(int i=0; i<num; i++) {
		for(int j=num; j>i; j--) {
			if(obj[j].performance > obj[j-1].performance) {
				tmp = obj[j];
				obj[j] = obj[j-1];
				obj[j-1] = tmp;
			}
		}
	}
}
