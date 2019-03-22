//problems deletion order is log n now ;(**/
//todo private some methods
#pragma once
#include "BinaryTree.h"
#include "InernalBinaryAvlTreeNode.h"
using namespace std;

template <class T ,class IBTN>
class AvlBinaryTree : public BinaryTree<T, IBTN>
{
	//typedef  InternalBinaryAvlTreeNode<T>  IBTN;
public:
	AvlBinaryTree(){}
	virtual void insertLeftChild(const BinaryTreeNode& parentNode, T data) {
		BinaryTree::insertLeftChild(parentNode, data);
		balanceAll(parentNode.mActualNode);
	}
	virtual void insertRightChild(const BinaryTreeNode& parentNode, T data) {
		BinaryTree::insertRightChild(parentNode, data);
		balanceAll(parentNode.mActualNode);
	}
	
	void balanceAll(IBTN* p) {
		if (p == mInEnd) {
			return;
		}
		balance(p);
		balanceAll(p->getParent());
	}

	void updateheight(IBTN* p) {
		int hl = height(p->mLeftChild);
		int hr = height(p->mRightChild);
		p->height = (hl>hr ? hl : hr) + 1;
	};
	int height(IBTN *node) {
		if (node)
			return node->height;
		return 0;
	};
	int balanceFactor(IBTN* p) {	
		 return height(p->mLeftChild) - height(p->mRightChild);
	};
	virtual IBTN* rr_rotation(IBTN *parent) {
		//cout << "rr";// << "p" << parent;
		IBTN *temp;
		temp = parent->mRightChild;
		parent->mRightChild = temp->mLeftChild;
		//?1010
		if(temp->mLeftChild)
		temp->mLeftChild->mParent = parent;
		
		temp->mLeftChild = parent;


		if (parent->mParent->getRightChild())
			if (parent->mParent->mRightChild == parent)
				parent->mParent->mRightChild = temp;

		if (parent->mParent->getLeftChild())
			if (parent->mParent->mLeftChild == parent)
				parent->mParent->mLeftChild = temp;
		temp->mParent = parent->mParent;//?nead

	   //?1010
		if (parent)
			parent->mParent = temp;
		updateheight(parent);
		updateheight(temp);
		return temp;
	};
	virtual IBTN* ll_rotation(IBTN *parent) {
		//cout << "ll";// << "p" << parent->getData();
		IBTN *temp;
		temp = parent->mLeftChild;
		parent->mLeftChild = temp->mRightChild;
		//?1010
		if (temp->mRightChild)
			temp->mRightChild->mParent = parent;

		temp->mRightChild = parent;


		if (parent->mParent->getRightChild())
			if (parent->mParent->mRightChild == parent)
				parent->mParent->mRightChild = temp;

		if (parent->mParent->getLeftChild())
			if (parent->mParent->mLeftChild == parent)
				parent->mParent->mLeftChild = temp;


		temp->mParent = parent->mParent;//?nead
		//?1010
		if (parent)
			parent->mParent = temp;


		updateheight(parent);
		updateheight(temp);
		return temp;
	};
	IBTN* lr_rotation(IBTN *parent) {
		//cout << "lr";
		IBTN *temp;
		temp = parent->mLeftChild;
		parent->mLeftChild = rr_rotation(temp);
		return ll_rotation(parent);
	};
	IBTN* rl_rotation(IBTN *parent) {
		//cout << "rl";
		IBTN *temp;
		temp = parent->mRightChild;
		parent->mRightChild = ll_rotation(temp);
		return rr_rotation(parent);
	};
	IBTN* balance(IBTN *temp) {
		//cout << "balance" << "p" <<temp <<endl;
		updateheight(temp);
		int bal_factor = balanceFactor(temp);
		if (bal_factor > 1)
		{
			if (balanceFactor(temp->mLeftChild) > 0)
				temp = ll_rotation(temp);
			else
				temp = lr_rotation(temp);
		}
		else if (bal_factor < -1)
		{
			if (balanceFactor(temp->mRightChild) > 0)
				temp = rl_rotation(temp);
			else
				temp = rr_rotation(temp);
		}
		return temp;
	};
	bool find(T key) {
		IBTN *tmp = root;
		while (root != 0) {
			if (key == tmp->key) {
				return true;
			}
			else if (key < tmp->key) {
				tmp = tmp->left;
			}
			else {
				tmp = tmp->right;
			}
		}
		return false;
	};
	//IBTN* insert(IBTN *p, const T data) {
	//	if (!p) {
	//		mSize++;
	//		return new IBTN(data);
	//	}if (data < p->getData())
	//		p->mLeftChild = insert(p->mLeftChild, data);
	//	else
	//		p->mRightChild = insert(p->mRightChild, data);
	//	return balance(p);
	//};
	
	void display(IBTN *ptr, int level) {
		int i;
		if (ptr != NULL)

		{
			display(ptr->mRightChild, level + 1);

			printf("\n");

			if (ptr == getRootNode())

				cout << "Root -> ";

			for (i = 0; i < level && ptr != root; i++)
				cout << "        ";
			cout << *ptr;
			display(ptr->mLeftChild, level + 1);

		}
	};

	virtual void deleteNode(const BinaryTreeNode& node) {
		IBTN* parentNode;
		parentNode = node.mActualNode->getParent();
		BinaryTree::deleteNode(node);
		balanceAll(parentNode);

	}
private:
};
