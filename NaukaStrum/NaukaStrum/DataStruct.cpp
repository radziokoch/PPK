#include "DataStruct.h"

List<CNode>::Node* findNodeById(Id id, List<CNode> list) {
	List<CNode>::Node* p = list.head;
	while (p != nullptr && p->key.id != id) {
		p = p->next;
	}
	return p;
}

List<Bundle>::Node* findNodeById(Id id, List<Bundle> list) {
	List<Bundle>::Node* p = list.head;
	while (p != nullptr && p->key.id != id) {
		p = p->next;
	}
	return p;
}

bool inclusion(const List<CNode>& A, const List<CNode>& B) {
	List<CNode>::Node* p = A.head;
	while (p != nullptr) {
		if (findNodeById(p->key.id, B) == nullptr) return false;
		p = p->next;
	}
	return true;
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

void plant(Tree::Node*& root, List<CNode> nodeList, List<CNode>::Node* outputNode) {
	if (root == nullptr) {
		root = new Tree::Node(outputNode);
		if (outputNode->key.leftId == NO_CHILD
			&& outputNode->key.rightId == NO_CHILD) {
			return;
		}
		else {
			plant(root->left, nodeList, findNodeById(outputNode->key.leftId, nodeList));
			plant(root->right, nodeList, findNodeById(outputNode->key.rightId, nodeList));
		}
	}
}