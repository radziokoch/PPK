/*#include "DataStructures.h"

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
	if (head == nullptr) {}
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


// ###################################### DRZEWO ####################################

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
*/