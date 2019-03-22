//#include "avlBinaryTree.h"
//#include "InernalBinaryAvlTreeNode.h"
//#include "BinaryTree.h"
#include <iostream>
//#include <time.h>
//#include "IndexedAvlBinaryTree.h"
#include "IndexedLinearList.h"
using namespace std;

//typedef AvlBinaryTree<string, InternalBinaryAvlTreeNode<string>>  IBT;
//
//void LoadBinaryTree(IBT	*bt) {
//
//
//	bt->insertRootNode("a");
//	IBT::BinaryTreeNode		btna(bt->getRootNode());
//	bt->insertLeftChild(btna, "b");
//	bt->insertRightChild(btna, "c");
//
//	IBT::BinaryTreeNode		&btnb = btna.getLeftChild();
//	IBT::BinaryTreeNode		&btnc = btna.getRightChild();
//	bt->insertLeftChild(btnb, "d");
//	bt->insertLeftChild(btnc, "e");
//	bt->insertRightChild(btnc, "f");
//	bt->draw(cout);
//	
//	IBT::BinaryTreeNode		&btnd = btnb.getLeftChild();
//	IBT::BinaryTreeNode		&btne = btnc.getLeftChild();
//	IBT::BinaryTreeNode		&btnf = btnc.getRightChild();
//	bt->insertLeftChild(btnd, "g");
//	bt->draw(cout);
//	bt->insertRightChild(btne, "h");
//	
//	bt->insertRightChild(btnf, "i");
//	bt->draw(cout);
//
//	IBT::BinaryTreeNode		&btnh = btnd.getRightChild();
//	bt->insertLeftChild(btnh, "k");
//	bt->draw(cout);
//	//bt->deleteNode(btnc.getLeftChild().getRightChild());
//	//bt->draw(cout);
//	//bt->deleteNode(btnc.getLeftChild());
//
//	//bt->deleteNode(btnc);
//
//	
//
//	bt->deleteNode(btnc.getRightChild());
//	bt->draw(cout);
//	cout << bt->size();
//	//bt->deleteNode(btnc.getLeftChild());
//	//cout << bt->size();
//	//bt->draw(cout);
//	auto i = btne.getRightChild();
//	bt->deleteNode(i);
//	bt->draw(cout);
//	cout << bt->size();
//	bt->deleteNode(btne);
//	bt->draw(cout);
//	cout << bt->size();
//
//	
//
//	bt->deleteNode(btnc.getRightChild());
//	bt->draw(cout);
//	cout << bt->size();
//
//
//
//	//bt->deleteNode(btne.getRightChild());
//	//cout << bt->size();
//
//
//}
//
//void testBinaryTree()
//{
//	IBT*	bt = new IBT;
//	srand(time(NULL));
//
//	LoadBinaryTree(bt);
//	bt->setNodeDisplayWidth(1);
//	bt->draw(cout);
//
//	delete bt;
//}
//
//void testRemove(int c) {
//
//
//
//}
//int maidn()
//{
//	int a;
//	//cin >> a;
//	testBinaryTree();
//
//
//	int dummy;
//	cin >> dummy;
//}
//



using namespace std;
void print_term(IndexedLinearList<int>&	ill) {
	for (int i = 0; i < ill.size(); i++)
		cout << ill.get(i) << "\t";
	cout << endl;
}

void random_insert(IndexedLinearList<int>&	ill) {
	int r;
	int data = rand() % 1000;
	r = rand() % (ill.size() + 1);
	cout << "insert index = " << r << "  data = " << data << endl;
	ill.insert(r, data);
	ill.drawTree();
	cout << endl;
	print_term(ill);
}
void random_remove(IndexedLinearList<int>&	ill) {
	int r;
	r = rand() % ill.size();
	cout << "remove index = " << r << "  data = " << ill.get(r) << endl;
	ill.remove(r);
	ill.drawTree();
	cout << endl;
	print_term(ill);
}
void random_tester(IndexedLinearList<int>&	ill) {
	int number_of_insert = 70;
	int number_of_remove = number_of_insert;

	for (int i = 0; i < number_of_insert; i++) {
		random_insert(ill);
	}
	//ill.drawTree();
	//cout << endl;
	//print_term(ill);
	for (int i = 0; i < number_of_remove; i++) {
		random_remove(ill);
	}

}
void testIndexedLinearList()
{
	IndexedLinearList<int>	ill;


	ill.insert(0, 10);
	ill.drawTree();
	print_term(ill);
	ill.insert(0, 50);
	ill.drawTree();
	print_term(ill);
	ill.insert(1, 70);
	ill.drawTree();
	print_term(ill);

	ill.insert(0, 25);
	ill.drawTree();
	print_term(ill);

	ill.insert(3, 94);
	ill.drawTree();
	print_term(ill);

	ill.insert(1, 88);
	ill.drawTree();
	print_term(ill);

	ill.insert(0, 75);
	ill.drawTree();
	print_term(ill);

	ill.insert(5, 32);
	ill.drawTree();
	print_term(ill);
	ill.insert(2, 92);
	ill.drawTree();
	print_term(ill);
	ill.remove(2);
	ill.drawTree();
	ill.remove(9);
	ill.drawTree();
	print_term(ill);
	ill.remove(3);
	ill.drawTree();
//	ill.remove(6);
//	ill.drawTree();
	ill.remove(4);
	ill.drawTree();
	ill.remove(1);
	ill.drawTree();
	//	ill.insert(1, 90034);
	ill.insert(0, 90045);
	ill.insert(0, 905);
	ill.insert(7, 90);

	ill.drawTree();
	ill.remove(2);
	ill.drawTree();
	ill.remove(9);
	ill.drawTree();
	ill.remove(3);
	ill.drawTree();
	ill.remove(6);
	ill.drawTree();
	ill.remove(0);
	ill.drawTree();
	ill.remove(1);
	ill.drawTree();
	ill.remove(1);
	ill.drawTree();
	cout << endl;

	for (int i = 0; i < ill.size(); i++)
		cout << ill.get(i) << "\t";
}

int main()
{
//	testIndexedLinearList();
	IndexedLinearList<int>	ill;
	for (int i = 0; i < 100; i++) {
		cout << i << endl << endl << endl;
		random_tester(ill);
	}
	int dummy;
	cin >> dummy;
}
