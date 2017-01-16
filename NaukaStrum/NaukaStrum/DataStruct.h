#ifndef DATA_STRUCT_H_PWYS_
#define DATA_STRUCT_H_PWYS_
#include <string>
enum Gate {
	AND,OR,NEG,NAND,NOR,XOR,XNOR,INPUT,OUTPUT
};

struct Bundle {
	std::string id;
	bool state;
};

typedef std::string Id;

struct CNode {
	Id id;
	Id leftId;
	Id rightId;
	Gate type;
	bool state;
	CNode(Id id_ = "", Gate type_ = INPUT) { id = id_; leftId = rightId = ""; type = type_; state = false; }
	CNode(Id id_, Gate type_, Id leftId_, Id rightId_) { id = id_; type = type_; leftId = leftId_; rightId = rightId_; state = false; }
};

template<typename T>
struct List {
	struct Node {
		T key;
		Node* next;
		Node(T key_) { next = nullptr; key = key_; }
	};

	Node* head;
	//int count;

	List() { head = nullptr; }

	void push_front(T k) {
		Node* node = new Node(k);
		if (head == nullptr) head = node;
		else {
			node->next = head;
			head = node;
		}
		return;
	}
	void remove() {
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

};

List<CNode>::Node* findNodeById(Id id, List<CNode> list);

List<Bundle>::Node* findNodeById(Id id, List<Bundle> list);

bool inclusion(const List<CNode>& A, const List<CNode>& B);


struct Tree {
	struct Node {
		Node* left;
		Node* right;
		Gate type;
		bool state;

		Node(List<CNode>::Node* nativeNode) {
			state = nativeNode->key.state;
			type = nativeNode->key.type;
			left = right = nullptr;
		}
	};

	Node* root;

	Tree(Node* root_ = nullptr) { root = root_; }
	//void print(Node* rt, int tab = 0) const;
	void remove(Node*& rt);
};

const std::string NO_CHILD = "";

void plant(Tree::Node*& root, List<CNode> nodeList, List<CNode>::Node* outputNode);
bool calc(Tree::Node* n);


#endif // !DATA_STRUCT_H_PWYS_