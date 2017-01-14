#include <iostream>
#include <Windows.h>

using namespace std;

namespace pw {
	struct Node {
		int key;
		Node* left;
		Node* right;

		Node(int v) { key = v; left = right = nullptr; }
	};

	void insert(Node*& r, int v) {

		if (r == nullptr) r = new Node(v);
		else {
			if (r->key > v) {
				if (r->left == nullptr) {
					r->left = new Node(v); return;
				}
				else insert(r->left, v);
			}
			else {
				if (r->right == nullptr) {
					r->right = new Node(v);;
					return;
				}
				else insert(r->right, v);
			}
		}
	}

	void print(Node*& r, int tab = 0) {
		if (r != nullptr) {
			print(r->right, tab + 1);
			cout << endl;
			for (int i = 0; i < tab; ++i) cout << "\t";
			cout << r->key;
			cout << endl;
			print(r->left, tab + 1);
		}
	}

	Node*& minNode(Node* r) {
		while (r->left != nullptr) r = r->left;
		return r;
	}

	Node*& maxNode(Node* r) {
		while (r->right != nullptr) r = r->right;
		return r;
	}

	bool remove(Node*& r, int v) {
		if (r->key > v) remove(r->left, v);
		else if (r->key < v) remove(r->right, v);
		else {
			if (r->left == nullptr && r->right == nullptr) {
				delete r;
				r = nullptr;
			}
			else if (r->left != nullptr && r->right != nullptr) {
				int min = minNode(r->right)->key;
				r->key = min;
				remove(r->right, min);
			}
			else {
				Node* tmp = r;
				Node* child = (r->left != nullptr) ? r->left : r->right;
				r = child;
				delete tmp;
			}
			return true;
		}
		return false;
	}

	Node* search(Node* r, int v) {
		while (r != nullptr && r->key != v) {
			if (v < r->key) r = r->left;
			else if (v > r->key) r = r->right;
		}
		return r;
	}
}


int main() {
	pw::Node* root = nullptr;
	int n;
	
	while (cin >> n && n!=-1) {
		system("cls");
		pw::insert(root, n);
		pw::print(root);
		cout << endl << endl << "MIN = " << pw::minNode(root)->key;
		cout << endl << endl << "MAX = " << pw::maxNode(root)->key; 
		cout << endl;
	}

	
	while (cin >> n && n != -1) {
		system("cls");
		pw::remove(root, n);
		pw::print(root);
	}
	
	cout << endl << (pw::search(root, 200) != nullptr);

	//pw::print(root);

	Sleep(6000);
	int d;
	cin >> d;
}