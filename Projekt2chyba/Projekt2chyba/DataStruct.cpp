#include "DataStruct.h"
#include <iostream>
#include <string>

void List::push_front(Node* node) {
	if (head == nullptr) head = node;
	else {
		node->next = head;
		head = node;
	}
	return;
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

void List::print() const {
	if (head == nullptr) std::cout << "PUSTO W CHUJ";
		else {
			Node* p = head;
			while (p != nullptr) {
				std::cout << "[" << p->id << ", " << p->state << ",  " << p->leftId << ", " << p->rightId << "]  ";
				p = p->next;
			}
		}
	
}

List::Node* List::findNodeById(Id id_) {
	Node* p = head;
	while (p != nullptr && p->id != id_) {
		p = p->next;
	}
	return p;
}

void plant(Tree::Node*& root, List nodeList, List::Node* outputNode) {
	if (root == nullptr) {
		root = new Tree::Node(outputNode);
		if (outputNode->leftId == NO_CHILD
			&& outputNode->rightId == NO_CHILD) {
			return;
		}
		else {
			plant(root->left, nodeList, nodeList.findNodeById(outputNode->leftId));
			plant(root->right, nodeList, nodeList.findNodeById(outputNode->rightId));
		}
	}
}

void Tree::print(Node* rt, int tab) const {
	if (rt != nullptr) {
		print(rt->left, tab + 1);
		std::cout << std::endl;
		for (int i = 0; i < tab; ++i) std::cout << "   ";
		std::cout << rt->state;
		std::cout << std::endl;
		print(rt->right, tab + 1);
	}
	if (root == nullptr) std::cout << "PUSTE";
}

void Tree::remove(Node*& rt) {
	if (rt != nullptr) {
		remove(rt->left);
		remove(rt->right);
		delete rt;
		rt = nullptr;
	}
}

bool calc(Tree::Node* n) {
	if (n->right == nullptr && n->left == nullptr) {
		return n->state;
	}
	else {
		bool result;
		switch (n->type) {
		case AND:
			result = calc(n->left) & calc(n->right);
			break;
		case OR:
			result = calc(n->left) | calc(n->right);
			break;
		case NEG:
			result = !calc(n->left);
			break;
		case NAND:
			result = !(calc(n->left) & calc(n->right));
			break;
		case NOR:
			result = !(calc(n->left) | calc(n->right));
			break;
		case XOR:
			result = calc(n->left) ^ calc(n->right);
			break;
		case XNOR:
			result = !(calc(n->left) ^ calc(n->right));
			break;
		}
		return result;
	}
}