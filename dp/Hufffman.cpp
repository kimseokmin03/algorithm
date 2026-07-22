#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

class node {
public:
	float freq;
	char alphabet;
	node* lchild, * rchild;
};

struct compare_node{
	bool operator()(const node* a, const node* b){
		return a->freq > b->freq;
	}
};

void print_hcode(node* tnode, string hcode) {
	if (tnode->lchild == NULL && tnode->rchild == NULL) {
		printf("%c --> %s\n", tnode->alphabet, hcode.c_str());
	}
	if (tnode->lchild != NULL) {
		string ncode = hcode + "0";
		print_hcode(tnode->lchild, ncode);
	}
	if (tnode->rchild != NULL) {
		string ncode = hcode + "1";
		print_hcode(tnode->rchild, ncode);
	}
}

void huffman(int n, float* freq) {
	priority_queue<node*, vector<node*>, compare_node> pq;

	for (int i = 0; i < n; i++) {
		node* tnode = (node*)malloc(sizeof(node));

		tnode->freq = freq[i];
		tnode->alphabet = 'A' + i;
		tnode->lchild = tnode->rchild = NULL;
		pq.push(tnode);
	}
	node* nnode;
	float cost = 0;

	while (pq.size() > 1) {
		node* tnode1 = pq.top(); pq.pop();
		node* tnode2 = pq.top(); pq.pop();
		nnode = (node*)malloc(sizeof(node));
		nnode->freq = tnode1->freq + tnode2->freq;
		nnode->alphabet = '0';
		cost += nnode->freq;
		nnode->lchild = tnode1;
		nnode->rchild = tnode2;
		pq.push(nnode);
	}
	printf("cost: %f\n", cost);
	nnode = pq.top();

	string hcode;
	print_hcode(nnode, hcode);
}

int main() {
	int n=0;
	float freq[100000];
	FILE* txt;
	int error = fopen_s(&txt, "huffman_sample.txt", "r");
	fscanf(txt, "%d", &n);

	for (int i = 0;i < n;i++) {
		fscanf(txt, "%f", &freq[i]);
	}
	huffman(n, freq);
	fclose(txt);
	return 0;
}	