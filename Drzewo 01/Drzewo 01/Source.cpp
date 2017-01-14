#include <iostream>

using namespace std;

template <typename T>
class BDrzewo {

	class Node {
	public:
		T key;
		Node* parent;
		Node* left;
		Node* right;
		Node(T v);
		T getVal() const { return key; }
	};

private:
	Node* root;

public:
	BDrzewo();
	void add(T v);

	void rek_print(Node*& p, int tab) {
		rek_print(p->left, tab + 1);
		for (int i = 0; i < tab; i++) cout << "\t";
		cout << " " << p->key << " ";
		rek_print(p->right, tab + 1);
	}

	void print() {
		rek_print(root, 0);
	}
};

int main() {
	BDrzewo<int> drzewko;
	drzewko.add(10);
	drzewko.add(20);
	drzewko.print();
}

template<typename T>
BDrzewo<T>::BDrzewo() {
	root = nullptr;
}

template <typename T>
void BDrzewo<T>::add(T v) {
	Node* InsertNode = new Node(v);
	Node* y = nullptr;
	Node* x = root;

	while (x != nullptr)
	{
		y = x;

		if (InsertNode->key < x->key)
		{
			x = x->left;
		}
		else
		{
			x = x->right;
		}
	}

	InsertNode->parent = y;

	if (y == nullptr)
	{
		root = InsertNode;
	}
	else
	{
		if (InsertNode->key < y->key)
		{
			y->left = InsertNode;
		}
		else
		{
			y->right = InsertNode;
		}
	}
}

template <typename T>
BDrzewo<T>::Node::Node(T v) {
	key = v;
	left = right = parent = nullptr;
}