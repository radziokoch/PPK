#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <regex>
#include <vector>
#include "DataStruct.h"

using namespace std;

bool parseInputsFile2(const string& fname, List<List<Bundle> >& stateList);
bool parseInputsFile(const string& fname, List<Bundle>& stateList);
bool parseCircuitFile(const string& fname, List<CNode>& gates, List<CNode>& outputs);
bool checkStructure(List<CNode>& nodeList, List<List<Bundle> >& inStatesList, List<CNode>& reqOutputs);
bool buildOutput(const string& fname, List<CNode>& nodeList, List<List<Bundle> >& inStatesList, List<CNode>& reqOutputs);

int main(int argc, char** argv) {
	
	string inputsFilename;
	string circuitFilename;
	string outputFilename;

	List<CNode> nodeList;
	List<List<Bundle> > inStatesList;
	List<CNode> reqOutputs;
	
	if (parseInputsFile2("input.txt", inStatesList)) {
		if (parseCircuitFile("cir.u", nodeList, reqOutputs)) {
			//if (checkStructure(nodeList, inStatesList, reqOutputs)) {
				buildOutput("out.txt", nodeList, inStatesList, reqOutputs);
			//}
		}
	}

	/*nodeList.remove();
	reqOutputs.remove();
	List<List<Bundle> >::Node* p = inStatesList.head;
	while (p != nullptr) {
		p->key.remove();
		p = p->next;
	}
	inStatesList.remove();

	/*if (handleArgs(int argc, string* argvs)) {
		if (parseCircuitFile(circuitFilename)) {
			if (parseInputsFile(inputsFilename)) {

			}
		}
	}*/

	/*
	List<Bundle> l;
	List<CNode> gates;
	List<CNode> outputs;
	ifstream fin;
	parseCircuitFile("inp.txt", gates, outputs);
	
	List<CNode>::Node* p = gates.head;
	while (p != nullptr) {
		cout << "(" << p->key.id << ", " << p->key.leftId << ", " << p->key.rightId << ")\n";
		p = p->next;
	}
	
	gates.remove();
	outputs.remove();
	l.remove();
	*/

	

	int d;
	cin >> d;
}

bool parseInputsFile2(const string& fname, List<List<Bundle> >& stateList) {
	ifstream fin;
	fin.open(fname);
	if (fin.is_open()) {
		stringstream s;
		string line;

		while (fin.good()) {
			List<Bundle> list;
			getline(fin, line);
			s.clear();
			s.str(line);
			while (getline(s, line, ' ')) {
				Bundle bundle;
				bundle.id = line;
				list.push_front(bundle);
			}
			stateList.push_front(list);
		}

		List<List<Bundle> >::Node* pp = stateList.head;
		while (pp != nullptr) {
			List<Bundle>::Node* p = pp->key.head;
			while (p != nullptr) {
				string tmp = p->key.id;
				p->key.id = tmp.substr(0, tmp.find(':'));
				if (tmp.substr(tmp.find(':') + 1, tmp.size() - tmp.find(':') - 1) == "0") p->key.state = false;
				else p->key.state = true;
				p = p->next;
			}
			pp = pp->next;
		}
	}
	else {
		cout << "Blad pliku: " << fname;
		return false;
	}
}

bool parseInputsFile(const string& fname, List<Bundle>& stateList) {
	ifstream fin;
	fin.open(fname);
	if (fin.is_open()) {

		stringstream s;
		string line;
		//List<Bundle> stateList;

		while (fin.good()) {
			getline(fin, line);
			s.clear();
			s.str(line);
			while (getline(s, line, ' ')) {
				Bundle bundle;
				bundle.id = line;
				stateList.push_front(bundle);
			}
		}

		List<Bundle>::Node* p = stateList.head;
		while (p != nullptr) {
			string tmp = p->key.id;
			p->key.id = tmp.substr(0, tmp.find(':'));
			if (tmp.substr(tmp.find(':') + 1, tmp.size() - tmp.find(':') - 1) == "0") p->key.state = false;
			else p->key.state = true;
			p = p->next;
		}

		p = stateList.head;
		while (p != nullptr) {
			cout << "(" << p->key.id << ", " << p->key.state << ")\n";
			p = p->next;
		}
	}
	else {
		cout << "Blad pliku: " << fname;
		return false;
	}
}

bool parseCircuitFile(const string& fname, List<CNode>& gates, List<CNode>& outputs) {
	ifstream fin;
	fin.open(fname);
	if (fin.is_open()) {
		stringstream s;
		string line;
		
		// Odczyt pierwszej linijki z wejsciami
		getline(fin, line);
		s.str(line);
		string expr;
		getline(s, expr, ' ');
		if (expr == "IN:") {
			while (getline(s, expr, ' ')) {
				CNode cnode(expr, INPUT);
				if (findNodeById(expr,gates) == nullptr) gates.push_front(cnode);
			}
		}
		else {
			cout << "Pierwsza linijka pliku " << fname << " musi zawierac liste wejsc ukladu";
			return false;
		}

		// Odczyt drugiej linijki z wyjsciami
		getline(fin, line);
		s.clear();
		s.str(line);
		getline(s, expr, ' ');
		if (expr == "OUT:") {
			while (getline(s, expr, ' ')) {
				CNode cnode(expr, OUTPUT);
				if (findNodeById(expr, outputs) == nullptr) outputs.push_front(cnode);
			}
		}
		else {
			cout << "Druga linijka pliku " << fname << " musi zawierac liste wyjsc, ktorych stan ma byc odczytany";
			return false;
		}

		// Odczyt bramek, poczawszy od trzeciej linijki pliku
		while (fin.good()) {
			getline(fin, line);
			s.clear();
			s.str(line);
			getline(s, expr, ' ');
			Gate type;
			if (expr == "AND") type = AND;
			else if (expr == "OR") type = OR;
			else if (expr == "NEG") type = NEG;
			else if (expr == "NAND") type = NAND;
			else if (expr == "NOR") type = NOR;
			else if (expr == "XOR") type = XOR;
			else if (expr == "XNOR") type = XNOR;
			else {
				cout << "Nieznane wyrazenie: " << expr;
				return false;
			}
			string in1, in2, out;
			getline(s, in1, ' ');
			getline(s, in2, ' ');
			getline(s, out, ' ');
			CNode cnode(out, type, in1, in2);
			if (findNodeById(out, gates) == nullptr) gates.push_front(cnode);
		}

		return true;
	}
	else {
		cout << "Blad pliku: " << fname;
		return false;
	}
}

bool checkStructure(List<CNode>& nodeList, List<List<Bundle> >& inStatesList, List<CNode>& reqOutputs) {
	
	// Sprawdzenie czy kazdy z wezlow ukladu ma kompletne polaczenia
	List<CNode> requiredNodesList;
	List<CNode>::Node* p = nodeList.head;
	while (p != nullptr) {
		CNode leftTmp(p->key.leftId);
		CNode rightTmp(p->key.rightId);
		if (findNodeById(p->key.leftId, requiredNodesList) == nullptr) requiredNodesList.push_front(leftTmp);
		if (findNodeById(p->key.rightId, requiredNodesList) == nullptr) requiredNodesList.push_front(rightTmp);
		p = p->next;
	}
	if (!inclusion(requiredNodesList, nodeList)) {
		cout << "Blad strukturalny ukladu";
		return false;
	}
	
	// Wykrycie niedozwolonych sprzezen bramek
	p = nodeList.head;
	while (p != nullptr) {
		if (p->key.id == p->key.leftId || p->key.id == p->key.rightId) {
			cout << "Sprzezenie bramki niedozwolone";
			return false;
		}
		p = p->next;
	}

	// Sprawdzenie czy szukane wyjscia ukladu istnieja
	p = reqOutputs.head;
	while (p != nullptr) {
		if (findNodeById(p->key.id, nodeList) == nullptr) {
			cout << "Pozadane wyjscie ukladu nie istnieje";
			return false;
		}
		p = p->next;
	}

	p = nodeList.head;
	while (p != nullptr) {
		if (p->key.type == INPUT) {
			List<List<Bundle> >::Node* pp = inStatesList.head;
			while (pp != nullptr) {
				if (findNodeById(p->key.id, pp->key) == nullptr) {
					cout << "Brakujace stany wejsc ukladu";
					return false;
				}
				pp = pp->next;
			}
		}
		p = p->next;
	}

	return true;
}

bool buildOutput(const string& fname, List<CNode>& nodeList, List<List<Bundle> >& inStatesList, List<CNode>& reqOutputs) {
	ofstream fout(fname);
	if (fout.is_open()) {

		List<List<Bundle> >::Node* p = inStatesList.head;
		while (p != nullptr) {
			fout << "IN: ";
			List<CNode>::Node* ptr = nodeList.head;
			while (ptr != nullptr) {
				if (ptr->key.type == INPUT) ptr->key.state = findNodeById(ptr->key.id,p->key)->key.state;
				fout << ptr->key.id << ":" << ptr->key.state << " ";
				ptr = ptr->next;
			}

			List<CNode>::Node* r = reqOutputs.head;
			fout << "   OUT: ";
			while (r != nullptr) {
				fout << r->key.id << ":";
				string outId = r->key.id;
				Tree tree;
				plant(tree.root, nodeList, findNodeById(outId, nodeList));
				fout << calc(tree.root) << " ";
				tree.remove(tree.root);
				r = r->next;
			}
			fout << endl;
			p = p->next;
		}
		return true;
	}
	else {
		cout << "Blad pliku: " << fname;
		return false;
	}
}