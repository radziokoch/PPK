#pragma once
#include <iostream>
namespace pwysocki {
	template<typename T>
	class List {

	private:
		template<typename T>
		class Node {
		private:
			T val;
			Node* prev;
			Node* next;
		public:
			Node() {
				prev = nullptr;
				next = nullptr;
			}
			Node(T v) {
				val = v;
				prev = nullptr;
				next = nullptr;
			}
			
		};

		Node* head;
		Node* tail;
		int count;

	public:

		List() {
			head = nullptr;
			tail = nullptr;
			count = 0;
		}

		void push_back(const T& v) {
			Node* tmp = new Node(v);
			if (this->is_empty()) {
				head = tail = tmp;
			}
			else {
				tail->next = tmp;
				tmp->prev = tail;
				tail = tmp;
			}
			++count;
		}

		void print() const {
			Node* ptr = head;
			while (ptr != nullptr) {
				std::cout << ptr->val << " ";
				ptr = ptr->next;
			}
		}

		bool is_empty() const {
			return (count == 0);
		}
	};
}