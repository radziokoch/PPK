/*#ifndef DATA_STRUCTURES_PWYSOCKI_
#define DATA_STRUCTURES_PWYSOCKI_
#include <string>
#include <iostream>

enum Gate { AND, OR, NEG, NAND, NOR, XOR, XNOR };
typedef std::string Id;

struct List {
	struct Node {
		Node* next;
		Id id;
		Gate type;
		bool key;
		Id left;
		Id right;

		Node(Id nId, Gate nType, Id nLeft, Id nRight, bool nKey = false) { id = nId; left = nLeft; right = nRight; key = nKey; type = nType; next = nullptr; }
	};

	Node* head;


	List(Node* node = nullptr) { head = node; }
	void push_front(Node* node);
	Node* findNodeById(Id id);
	void remove();

	void print() const {
		if (head == nullptr) std::cout << "PUSTO W CHUJ";
		else {
			Node* p = head;
			while (p != nullptr) {
				std::cout << p->id << "(" << p->key << ")  ";
				p = p->next;
			}
		}
	}

};


/*
	#########################################  DRZEWO ###########################################

struct Tree {
	struct Node {
		Node* left;
		Node* right;
		List::Node* nativeNode;
		bool key;
		Gate type;

		Node(List::Node* nNode) { nativeNode = nNode;  key = nNode->key; type = nativeNode->type; left = right = nullptr; }

		bool r_calc(Node* node);
		void calc() { key = r_calc(this); }
	};

	Node* root;

	Tree(Node* node = nullptr) { root = node; }
	void plant(Node*&, List, List::Node*);


	void print(Node*& root, int tab = 0) {
		if (root != nullptr) {
			print(root->left, tab + 1);
			cout << endl;
			for (int i = 0; i < tab; ++i) cout << "    ";
			cout << root->nativeNode->id << " " << root->nativeNode->key;
			cout << endl;
			print(root->right, tab + 1);
		}
	}
};

#endif 
*/