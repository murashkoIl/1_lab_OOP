//#include "pch.h"
#include <iostream>
#include <string>
using namespace std;

class Word {

public:

	Word() {}

	Word(string s) {
		str = s;
	}

	string getStr() {
		return str;
	}

	void setStr(string input_str) {
		str = input_str;
	}

	// метод перевода char'ов в string


	string toString(char* input_data)
	{
		cout << " test " << endl;
		string str = string(input_data);
		return str;
	}


private:
	string str = "";
};

class EngTrans : public Word {

public:

	EngTrans(string str) : Word(str) {
		engStr = str;
	}

private:
	string engStr;

};

class RusTrans : public Word {
public:

	RusTrans(string str) : Word(str) {
		rusStr = str;
	}

private:
	string rusStr;

};

class Dictionary_item
{
private:

	Dictionary_item* rightChild;
	Dictionary_item* leftChild;

	Word* rusTrans;
	Word* engTrans;

public:
	Dictionary_item() {

		rusTrans = 0;
		engTrans = 0;
		rightChild = NULL;
		leftChild = NULL;
	}

	Dictionary_item(EngTrans* engWord, RusTrans* rusWord) {

		rusTrans = rusWord;
		engTrans = engWord;
		rightChild = NULL;
		leftChild = NULL;

	}

	void setRightChild(Dictionary_item* item) {
		rightChild = item;
	}

	void setLeftChild(Dictionary_item* item) {
		leftChild = item;
	}

	void setEngTrans(EngTrans* engTrans) {
		this->engTrans->getStr() = engTrans->getStr();
		// this->engTrans->setStr(engTrans->getStr());
	}

	Dictionary_item* getRightChild() {
		return rightChild;
	}

	Dictionary_item* getLeftChild() {
		return leftChild;
	}

	Word* getEngTrans() {

		return engTrans;
	}

	Word* getRusTrans() {

		return rusTrans;
	}



};

class Dictionary : public Word {

public:

	Dictionary_item root;

	void addItem(EngTrans engWord, RusTrans rusWord) { // при добавлении нового узла затирается предыдущий

		Dictionary_item newItem(&engWord, &rusWord);
		Dictionary_item* currentNode, * parent;

		if (root.getRusTrans() == 0) {
			root = newItem;
			return;
		}

		currentNode = &root;
		parent = &root;

		//bool isLeft = false;

		while (true) {
			if (currentNode->getRightChild() != NULL && currentNode->getRightChild()->getEngTrans()->getStr() > engWord.getStr()) {
				//isLeft = false;
				parent = currentNode;
				currentNode = currentNode->getRightChild();
			}
			else if (currentNode->getLeftChild() != NULL && currentNode->getLeftChild()->getEngTrans()->getStr() < engWord.getStr()) {
				//isLeft = true;
				parent = currentNode;
				currentNode = currentNode->getLeftChild();
			}
			else if (currentNode->getEngTrans()->getStr() > engWord.getStr()) {

				parent->setRightChild(&newItem);
				break;
			}
			else {
				parent->setLeftChild(&newItem);
				break;
			}

		}
	}
};

void main() {

	setlocale(LC_ALL, "RU");

	RusTrans rusTrans(" _слово_ ");
	cout << rusTrans.getStr() << endl;
	EngTrans engTrans(" _word_ ");
	cout << engTrans.getStr() << endl;

	Dictionary dict;
	dict.addItem(engTrans, rusTrans);

	RusTrans rusTrans1("строка");
	EngTrans engTrans1("string");

	dict.addItem(engTrans1, rusTrans1);




	cout << endl;
}