#ifndef DATA_STRUCTURES_PWYSOCKI2_
#define DATA_STRUCTURES_PWYSOCKI2_
#include <string>

typedef std::string Id;

enum Gate {AND,OR,NEG,NAND,NOR,XOR,XNOR};

struct List {
	struct Node {
		Id id;
		Id leftId;
		Id rightId;
		Gate type;
		bool state;
		Node* next;

		Node(Id id_,
			Id leftId_,
			Id rightId_,
			Gate type_,
			bool state_ = false) {
			
			next = nullptr;
			id = id_;
			leftId = leftId_;
			rightId = rightId_;
			type = type_;
			state = state_;
		}
	};

	Node* head;

	List(Node* head_ = nullptr) { head = head_;	}

	void push_front(Node* node);
	Node* findNodeById(Id id);
	void remove();
	void print() const;
};

struct Tree {
	struct Node {
		Node* left;
		Node* right;
		Gate type;
		bool state;

		Node(List::Node* nativeNode) {
			state = nativeNode->state;
			type = nativeNode->type;
			left = right = nullptr;
		}
	};

	Node* root;

	Tree(Node* root_ = nullptr) { root = root_; }
	void print(Node* rt, int tab = 0) const;
	void remove(Node*& rt);
};

const std::string NO_CHILD = "";

void plant(Tree::Node*& root, List nodeList, List::Node* outputNode);
bool calc(Tree::Node* n);

#endif