#include <regex>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <list>
#include "DataStruct.h"
/*
struct Node {
	int id;
	bool key;
	Node* left;
	Node* right;

	Node(int i = 0, bool k = false) { id = i; key = k; left = right = nullptr; }
	bool calc(Node* n) {
		if (n->left != nullptr && n->right != nullptr) {
			return (calc(n->right) ^ calc(n->left));
		}
		else
			return n->key;
	}
};

Node* find(Node* r, int id) {
	if (r != nullptr) {
		if (r->id == id) return r;
		else {
			Node* l = find(r->left, id);
			Node* ri = find(r->right, id);
			if (l == nullptr && ri == nullptr) return nullptr;
			else if (l != nullptr) return l;
			else if (ri != nullptr) return ri;
		}
	}
	return nullptr;
}

void insert(Node* root, int id, int newId, bool k = false) {
	Node* dest = find(root, id);
	Node* newNode = new Node(newId, k);
	if (dest->left == nullptr && dest->right == nullptr) dest->left = newNode;
	else if (dest->left == nullptr && dest->right != nullptr) dest->left = newNode;
	else if (dest->left != nullptr && dest->right == nullptr) dest->right = newNode;
	else cout << "BLAD KURWA";
	return;
}



int main() {
	Node* r = new Node(12);
	insert(r, 12, 10);
	insert(r,12,11);
	insert(r, 10,7);
	insert(r, 10,8);
	insert(r, 11, 8);
	insert(r, 11,9);
	insert(r, 7, 1, true);
	insert(r, 7, 2, true);
	insert(r, 8,3, false);
	insert(r, 8,4,false);
	insert(r, 9,5,false);
	insert(r, 9, 6, false);

	cout << r->calc(r);

	

	int d;
	cin >> d;
}

*/


using namespace std;

int main() {
	
	ifstream fin("uklad.u");
	List nodeList;
	string line;
	stringstream s;
	string label[4];
	getline(fin, line);
	s.str(line);
	s >> label[0] >> label[1] >> label[2] >> label[3];
	nodeList.push_front(new List::Node(label[1], "","", OR));
	nodeList.push_front(new List::Node(label[2], "", "", OR));
	nodeList.push_front(new List::Node(label[3], "", "", OR,1));
	s.clear();

	getline(fin, line);
	s.str(line);
	string out;
	s >> out;
	s >> out;
	s.clear();
	
	while (fin.good()) {
		getline(fin, line);
		s.str(line);
		for (int i = 0; i < 4; ++i) s >> label[i];
		Gate t;
		if (label[0] == "AND") t = AND;
		else if (label[0] == "OR") t = OR;
		else if (label[0] == "NEG") t = NEG;
		else if (label[0] == "NAND") t = NAND;
		else if (label[0] == "NOR") t = NOR;
		else if (label[0] == "XOR") t = XOR;
		else if (label[0] == "XNOR") t = XNOR;
		nodeList.push_front(new List::Node(label[3], label[1], label[2], t));
		s.clear();
	}

	nodeList.print();

	Tree tree;
	plant(tree.root, nodeList, nodeList.findNodeById(out));
	cout << endl << out << " = " << calc(tree.root);
	//tree.remove(tree.root);
	//cout << out;

	cout << endl << endl;

	

	int d;
	cin >> d;
}