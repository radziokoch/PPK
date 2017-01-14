#include<iostream>
#include<string>

using namespace std;

class Node {
public:
	enum GateType { NEG, AND, NAND, OR, NOR, XOR, XNOR };
private:
	GateType gateType;
	bool val;
	bool vKnown;
	Node* in1;
	Node* in2;
public:

	Node(bool v) {
		this->val = v;
		vKnown = true;
	}

	Node(GateType gt, Node* i1, Node* i2) {
		vKnown = false;
		gateType = gt;
		this->in1 = i1;
		this->in2 = i2;
	}

	bool getVal() {
		if (vKnown) return val;
		else {
			bool out;
			bool i1 = in1->getVal();
			bool i2 = in2->getVal();

			switch (gateType) {
				case NEG:
					out = !i1; break;
				case AND:
					out = i1 & i2; break;
				case NAND:
					out = (!(i1&i2)); break;
				case OR:
					out = i1 | i2; break;
				case NOR:
					out = !(i1 | i2); break;
				case XOR:
					out = i1 ^ i2; break;
				case XNOR:
					out = !(i1 ^ i2); break;
			}

			vKnown = true;
			val = out;
			return out;
		}
	}

	bool valKnown() const { return vKnown; }
};

int main() {
	Node N1(1), N6(1);
	Node N5(Node::NAND, &N1, &N6);
	Node N2(Node::XOR, &N1, &N5);
	Node N4(Node::NOR, &N5, &N6);
	Node N3(Node::NAND, &N2, &N4);

	

	cout << N3.getVal();
	
	int d;
	cin >> d;
}