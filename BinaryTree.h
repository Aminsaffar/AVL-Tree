// Copyright (C) Kamaledin Ghiasi-Shirazi, Ferdowsi Univerity of Mashhad, 2016 (1395 Hijri Shamsi)
//
// Author: Kamaledin Ghiasi-Shirazi
#pragma once
#include <string>
using namespace std;
template <class T, class IBTN>
class BinaryTree {
public:

	class BinaryTreeNode {
	public:
		virtual ~BinaryTreeNode(void) {}
		virtual T&	getData() { return mActualNode->getData(); }
		virtual void	setData(const T& data) { return mActualNode->setData(data); }
		virtual bool	hasLeftChild() const { return mActualNode->getLeftChild() != 0; }
		virtual BinaryTreeNode	getLeftChild()const { return BinaryTreeNode(mActualNode->getLeftChild()); }
		virtual bool	hasRightChild() const { return mActualNode->getRightChild() != 0; }
		virtual BinaryTreeNode	getRightChild() const { return BinaryTreeNode(mActualNode->getRightChild()); }
		template<typename S, typename R>
		friend class AvlBinaryTree;
		template<typename S, typename R>
		friend class IndexedAvlBinaryTree;
		template<class T>
		friend class InternalBinaryAvlTreeNode;


	private:
		template <class T, class R>
		friend class BinaryTree;
		BinaryTreeNode(IBTN* node) { mActualNode = node; }

		IBTN	*mActualNode;
	};


protected:
	/*
	ReverseInorderEnd
	----------------------|---------------------
	|											|
	ReversePostorderEnd					InorderEnd/ReversePreorderOEnd
	-------------------|-------------------
	|                                       |
	ActualTree						 PreorderEnd/PostorderEnd


	mRevInEnd
	----------------------|---------------------
	|											|
	mRevPostEnd									mInEnd=mRevPreEnd
	-------------------|-------------------
	|                                       |
	ActualTree							 mPreEnd=mPostEnd
	*/

	IBTN* 	mRevInEnd;
	IBTN* 	mRevPostEnd;
	IBTN* 	mInEnd;
	IBTN* 	mRevPreEnd;
	IBTN* 	mPreEnd;
	IBTN* 	mPostEnd;
	int		mNodeDisplayWidth;
	int		mSize;

public:
	BinaryTree(void) {
		mNodeDisplayWidth = 4;	// Don't change this value
		mSize = 0;

		mRevInEnd = new IBTN();
		mRevPostEnd = new IBTN();
		mInEnd = new IBTN();
		mRevPreEnd = mInEnd;
		mPreEnd = new IBTN();
		mPostEnd = mPreEnd;

		mRevInEnd->mLeftChild = mRevPostEnd;
		mRevPostEnd->mParent = mRevInEnd;

		mRevInEnd->mRightChild = mInEnd;
		mInEnd->mParent = mRevInEnd;

		mInEnd->mRightChild = mPreEnd;
		mPreEnd->mParent = mInEnd;


	}

	// caution: don't interpret virtual destrucor as an ordinary virtual function!
	virtual ~BinaryTree(void) {
		DeleteSubtree(mRevInEnd);
	}

	int	size() { return mSize; }
	void DeleteSubtree(IBTN* node) {
		if (node->mLeftChild)
			DeleteSubtree(node->mLeftChild);
		if (node->mRightChild)
			DeleteSubtree(node->mRightChild);
		delete node;
	}

	bool	isEmpty() {
		return mInEnd->mLeftChild == 0;
	}

	virtual void	insertRootNode(T data) {
		IBTN*	root;
		if (mInEnd->mLeftChild)
			throw ("Error: Root already exists.");
		root = new IBTN();
		root->mParent = mInEnd;
		*root->mData = data;
		root->mLeftChild = 0;
		root->mRightChild = 0;
		mInEnd->mLeftChild = root;
		mSize = 1;
	}

	virtual BinaryTreeNode	getRootNode() { return BinaryTreeNode(mInEnd->mLeftChild); }

	virtual BinaryTreeNode	getHeaderRootNode() { return BinaryTreeNode(mRevInEnd); }

	// error if a left child already exists.
	virtual void 	insertLeftChild(const BinaryTreeNode& parentNode, T data) {
		if (parentNode.mActualNode->mLeftChild)
			throw ("Error: left child already exists.");
		IBTN* newnode = new IBTN();
		newnode->setData(data);
		parentNode.mActualNode->mLeftChild = newnode;
		newnode->mParent = parentNode.mActualNode;
		mSize++;
	}


	// error if a right child already exists.
	virtual void insertRightChild(const BinaryTreeNode& parentNode, T data) {
		if (parentNode.mActualNode->mRightChild)
			throw ("Error: right child already exists.");
		IBTN* newnode = new IBTN();
		newnode->setData(data);
		parentNode.mActualNode->mRightChild = newnode;
		newnode->mParent = parentNode.mActualNode;
		mSize++;
	}


	// Only leaf nodes and nodes with degree 1 can be deleted. 
	// If a degree-1 node is deleted, it is replaced by its subtree.
	virtual void 	deleteNode(const BinaryTreeNode& node) {
		//std::cout << node.mActualNode->toString();
		if (node.mActualNode->mRightChild) {
			if (node.mActualNode->mLeftChild) {
				throw "Error: the degree is 2";//comment this to allow delete 
											   //BinaryTreeNode* itnode = &node.getLeftChild();
											   //while (itnode->hasRightChild()) {
											   //	itnode = &itnode->getRightChild();
											   //}
											   //node.mActualNode->mData = itnode->mActualNode->mData;
											   //deleteNode(*itnode);
											   //return;
			}
			//here only have right child D
			if (node.mActualNode->mParent->mLeftChild == node.mActualNode) {
				node.mActualNode->mParent->mLeftChild = node.mActualNode->mRightChild;
				node.mActualNode->mRightChild->mParent = node.mActualNode->mParent;
			}
			else if (node.mActualNode->mParent->mRightChild == node.mActualNode) {
				node.mActualNode->mParent->mRightChild = node.mActualNode->mRightChild;
				node.mActualNode->mRightChild->mParent = node.mActualNode->mParent;
			}
		}
		else if (node.mActualNode->mLeftChild) {
			//only have left child
			if (node.mActualNode->mParent->mRightChild == node.mActualNode) {
				node.mActualNode->mParent->mRightChild = node.mActualNode->mLeftChild;
				node.mActualNode->mLeftChild->mParent = node.mActualNode->mParent;
			}
			else if (node.mActualNode->mParent->mLeftChild == node.mActualNode) {
				node.mActualNode->mParent->mLeftChild = node.mActualNode->mLeftChild;
				node.mActualNode->mLeftChild->mParent = node.mActualNode->mParent; // debugr :)
			}
		}
		else {
			if (node.mActualNode->mParent->mRightChild == node.mActualNode)
				node.mActualNode->mParent->mRightChild = 0;

			else
				node.mActualNode->mParent->mLeftChild = 0;

		}
		delete node.mActualNode;
		mSize--;
	}

	void setNodeDisplayWidth(int width) {
		mNodeDisplayWidth = width;
	}

	// This function is solely written to work on small binary trees.
	// The code has many other known limitations.
	void draw(std::ostream& out) {
		if (mSize == 0)
			return;

		int maxDepth = 9;
		int depth = depthCalc(getRootNode().mActualNode);


		if (depth > maxDepth) {
			out << "Can't draw, the height of the tree is greater than " << (maxDepth + 1) / 2 << "\n";
			return;
		}

		depth = depth * 2 - 1;

		char **map = new char *[depth];
		for (int i = 0; i < depth; i++) {
			map[i] = new char[160];
			for (int j = 0; j < 160; j++)
				map[i][j] = 0;
		}

		recursiveDraw(getRootNode().mActualNode, map, 80, 0);

		for (int i = 0; i < depth; i++)
		{
			for (int j = 0; j < 160; j++)
				out << map[i][j];
			out << endl;
		}

		for (int i = 0; i < depth; i++)
			delete[] map[i];
		delete[] map;
	}


	int depthCalc(IBTN* root) {
		int res = 1;
		if (root->mRightChild) {
			int rightDepth = depthCalc(root->mRightChild) + 1;
			res = rightDepth;
		}
		if (root->mLeftChild) {
			int leftDepth = depthCalc(root->mLeftChild) + 1;
			res = (res > leftDepth) ? res : leftDepth;
		}
		return res;
	}

	void recursiveDraw(IBTN* root, char** lines, int x, int y) {
		int des = 1;
		for (int i = 0; i < y / 2 + 2; i++)
			des *= 2;
		des = 160 / des;
		//root:
		string s = root->toString();
		//s += "";
		//s += root->mParent->toString();
		int m = s.length() < mNodeDisplayWidth ? s.length() : mNodeDisplayWidth;
		for (int i = 0; i < m; i++)
			lines[y][x + i - mNodeDisplayWidth / 2] = s[i];
		//left child:
		if (root->mLeftChild) {
			for (int i = 0; i < des; i++)
				lines[y + 1][x - i] = '-';
			lines[y + 1][x] = '|';
			recursiveDraw(root->mLeftChild, lines, x - des, y + 2);
		}
		//right child:
		if (root->mRightChild) {
			for (int i = 0; i < des; i++)
				lines[y + 1][x + i] = '-';
			lines[y + 1][x] = '|';
			recursiveDraw(root->mRightChild, lines, x + des, y + 2);
		}
	}


	virtual string toString() {
		string str;
		if (mSize == 0)
			return str;
		int maxDepth = 20;
		int depth = depthCalc(getActualNode(getRootNode()));

		if (depth > maxDepth) {
			return str;
		}

		depth = depth * 2 - 1;

		char **map = new char *[depth];
		for (int i = 0; i < depth; i++) {
			map[i] = new char[160];
			for (int j = 0; j < 160; j++)
				map[i][j] = ' ';
		}

		recursiveDraw(getActualNode(getRootNode()), map, 80, 0);

		for (int i = 0; i < depth; i++)
			for (int j = 0; j < 160; j++)
				str += map[i][j];

		for (int i = 0; i < depth; i++)
			delete[] map[i];
		delete[] map;
		return str;
	}

protected:
	virtual IBTN*	getActualNode(const BinaryTreeNode& node) { return node.mActualNode; }
};

