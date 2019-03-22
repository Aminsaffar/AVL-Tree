// Copyright (C) Kamaledin Ghiasi-Shirazi, Ferdowsi Univerity of Mashhad, 2016 (1395 Hijri Shamsi)
//
// Author: Kamaledin Ghiasi-Shirazi

#pragma once
#include <string>
#include "avlBinaryIndexedTreeNode.h"

using namespace std;
template <class T, class IBTN>
class IndexedAvlBinaryTree : public AvlBinaryTree<T, IBTN>
{
public:
	IndexedAvlBinaryTree()
	{
		//add index to dummy node !!
	}

	virtual void	insertRootNode(T data)
	{
		BinaryTree::insertRootNode(data);
	}

	// error if a left child already exists.
	virtual void insertLeftChild(const BinaryTreeNode& parentNode, T data)
	{
		//AvlBinaryTree::insertLeftChild(parentNode, data);
		BinaryTree::insertLeftChild(parentNode, data);
		Updatemleftsize(getActualNode(parentNode)->mLeftChild, 1);
		balanceAll(parentNode.mActualNode);
	}

	// error if a right child already exists.
	virtual void insertRightChild(const BinaryTreeNode& parentNode, T data)
	{
		//AvlBinaryTree::insertRightChild(parentNode, data);
		BinaryTree::insertRightChild(parentNode, data);
		Updatemleftsize(getActualNode(parentNode)->mRightChild, 1);
		balanceAll(parentNode.mActualNode);
	}

	// Only leaf nodes and nodes with degree 1 can be deleted. 
	// If a degree-1 node is deleted, it is replaced by its subtree.
	virtual void deleteNode(const BinaryTreeNode& node)
	{
		Updatemleftsize(getActualNode(node), -1);
		AvlBinaryTree::deleteNode(node);
	}
	virtual void deleteNode2degree(const BinaryTreeNode& node)
	{
		BinaryTreeNode& delnode = node.getLeftChild();
		while (delnode.hasRightChild()) {
			delnode = delnode.getRightChild();
		}
		*(getActualNode(node)->mData) = *(getActualNode(delnode)->mData);

		//Updatemleftsize(getActualNode(delnode), -1);
		//BinaryTree::deleteNode(delnode);
		deleteNode(delnode);

	}

	virtual int getLeftSize(const BinaryTreeNode& node)
	{
		return getActualNode(node)->mLeftSize;
	}
	//int calcLeftSize(IBTN* node) {
	//	int s = 0;
	//	IBTN* tmp = node->mLeftChild;
	//	if (tmp) {
	//		s += tmp->mLeftSize + 1;
	//		if (tmp->mRightChild)
	//			while (tmp = tmp->mRightChild) {
	//				s += tmp->mLeftSize + 1;
	//			}
	//	}
	//	return s;
	//}
	virtual IBTN* rr_rotation(IBTN *parent) {
		IBTN* tmp = AvlBinaryTree::rr_rotation(parent);
		tmp->mLeftSize +=  tmp->mLeftChild->mLeftSize + 1;
		return tmp;
	}

	
	virtual IBTN* ll_rotation(IBTN *parent) {
		IBTN* tmp = AvlBinaryTree::ll_rotation(parent);
		parent->mLeftSize = parent->mLeftSize - tmp->mLeftSize -1;
		return tmp;
	}
private:
	bool isLeftChildOfParent(IBTN* node) {
		return  (node->mParent->mLeftChild == node);
	}

	void Updatemleftsize(IBTN* node, int n) {
		if (!node)
			return;
		while (node != mInEnd) {
			if (isLeftChildOfParent(node)) {
				node->mParent->mLeftSize += n;
			}
			node = node->mParent;
		}
	}

};
