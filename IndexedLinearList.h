// Copyright (C) Kamaledin Ghiasi-Shirazi, Ferdowsi Univerity of Mashhad, 2016 (1395 Hijri Shamsi)
//
// Author: Kamaledin Ghiasi-Shirazi

#pragma once
#include <ostream>
#include "avlBinaryTree.h"
#include "IndexedAvlBinaryTree.h"
#include "avlBinaryIndexedTreeNode.h"

template <class T>
class IndexedLinearList{

public:
	typedef typename IndexedAvlBinaryTree<T, InternalBinaryAvlIndexedTreeNode<T>>::BinaryTreeNode BTN;
	IndexedLinearList(void){
		mIbt = new IndexedAvlBinaryTree < T, InternalBinaryAvlIndexedTreeNode<T> > ;
	}

	virtual ~IndexedLinearList(void) {
		delete mIbt;
	}

public:

	void insert(BTN &parent, const T& data) {
		if (!parent.hasLeftChild()) {
			mIbt->insertLeftChild(parent , data);
			return;
		}
		parent = parent.getLeftChild();
		while (parent.hasRightChild()) {
			parent = parent.getRightChild();
		}
		mIbt->insertRightChild(parent , data);
	}
	virtual void insert(int idx, const T& data) {
		if (mIbt->size() <= idx) {
			//throw "what are you doing :?";
			auto n = mIbt->getHeaderRootNode().getRightChild();//??????>>????>>??>>??>>??>>??>>??>>??>>??>>??>>??
			insert(n, data);
			return;
		}
		BTN btn = getNode(idx);
		insert(btn, data);
	}
	
	virtual T& get(int idx){
		BTN   node= getNode(idx);
		return node.getData();
	}
	
	bool isLeafNode(BTN& btn) {
		return !(btn.hasLeftChild()||btn.hasRightChild());
	}
	bool hasOneChild(BTN& btn) {
		return ((btn.hasLeftChild() || btn.hasRightChild()) && !hasTwoChild(btn));
	}
	bool hasTwoChild(BTN& btn) {
		return (btn.hasLeftChild() && btn.hasRightChild());
	}
	virtual void remove (int idx){
		BTN btn = getNode(idx);
		if (isLeafNode(btn)) {	//std::cout << idx<< "  leaf node is deleteing ..." << endl;
			mIbt->deleteNode(btn);
		
		}
		else if (hasOneChild(btn)) { //std::cout << idx << "   one childer node is deleteing ..." << endl;
			mIbt->deleteNode(btn);
			
		}
		else if (hasTwoChild(btn)) {	//std::cout << idx << "  2 childer node is deleteing ..." << endl ;
			mIbt->deleteNode2degree(btn);
		
		}
	}


	virtual int size() const {
		return mIbt->size();
	};

	virtual void drawTree()
	{
		mIbt->draw(cout);
	}

private:
	virtual BTN getNode(int idx){
		BTN* node = &(mIbt->getRootNode());
		while (node->hasLeftChild() || node->hasRightChild()) {
			int leftsize = mIbt->getLeftSize(*node);
			if (leftsize < idx) {
				idx = idx - leftsize - 1;//right
				node = &(node->getRightChild());
			}
			else if (leftsize == idx)
				return *node;//this
			else {
				node = &(node->getLeftChild());
			}//left
		}
		return *node;
	}

protected:
	IndexedAvlBinaryTree<T, InternalBinaryAvlIndexedTreeNode<T>>	*mIbt;
};

template <class T>
std::ostream& operator<<(std::ostream& os, const IndexedLinearList<T>& ll){

	for (int i=0; i < ll.size(); i++)
		os << ll.get(i) << "\t";

	return os;
}
