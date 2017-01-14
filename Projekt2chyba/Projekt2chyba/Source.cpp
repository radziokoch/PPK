#include <iostream>
#include <vector>
#include <string>
using namespace std;
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

enum Gate {AND,OR,NEG,NAND,NOR,XOR,XNOR};
typedef string Id;

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
		if (head == nullptr) cout << "PUSTO W CHUJ";
		else {
			Node* p = head;
			while (p != nullptr) {
				cout << p->id << "(" << p->key << ")  ";
				p = p->next;
			}
		}
	}

};

void List::push_front(List::Node* node) {
	if (head == nullptr) head = node;
	else {
		node->next = head;
		head = node;
	}
	return;
}

List::Node* List::findNodeById(Id ide) {
	Node* p = head;
	while (p != nullptr && p->id != ide) {
		p = p->next;
	}
	return p;
}

void List::remove() {
	if (head == nullptr) { }
	else if (head->next == nullptr) 
		delete head;
	else {
		Node* p = head->next;
		while (p != nullptr) {
			delete head;
			head = p;
			p = p->next;
		}
		delete head;
	}
	head = nullptr;
	return;
}
	

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

void Tree::plant(Node*& root, List nativeNodeList, List::Node* outRoot) {
	root = new Node(outRoot);
	if (outRoot->left != "" && outRoot->right != "") {
		plant(root->left, nativeNodeList, nativeNodeList.findNodeById(outRoot->left));
		plant(root->right, nativeNodeList, nativeNodeList.findNodeById(outRoot->right));
	}
	else return;

}

bool Tree::Node::r_calc(Node* node) {
	if (node->left != nullptr && node->right != nullptr) {
		bool result;
		switch (type) {
		case AND:
			result = r_calc(node->left) & r_calc(node->right);
			break;
		case OR:
			result = r_calc(node->left) | r_calc(node->right);
			break;
		case NEG:
			result = !r_calc(node->left);
			break;
		case NAND:
			result = !(r_calc(node->left) & r_calc(node->right));
			break;
		case NOR:
			result = !(r_calc(node->left) | r_calc(node->right));
			break;
		case XOR:
			result = r_calc(node->left) ^ r_calc(node->right);
			break;
		case XNOR:
			result = !(r_calc(node->left) ^ r_calc(node->right));
			break;
		}
		return result;
	}
	else 
		return node->key;
}

int main() {
	List lista;
	
	lista.push_front(new List::Node("G", NAND, "E", "F"));
	lista.push_front(new List::Node("E", OR, "A", "B"));
	lista.push_front(new List::Node("F", NOR, "B", "C"));
	lista.push_front(new List::Node("A", OR, "", "",true));
	lista.push_front(new List::Node("B", OR, "", "",true));
	lista.push_front(new List::Node("C", OR, "", ""));
	
	lista.print();

	Tree tree;

	tree.plant(tree.root, lista, lista.findNodeById("G"));
	


	cout << endl;

	
	tree.root->calc();
	cout << endl << "XXX " << tree.root->key;
	cout << endl;
	tree.print(tree.root);
	cout << endl << endl;
	lista.print();
	int d;
	cin >> d;
}