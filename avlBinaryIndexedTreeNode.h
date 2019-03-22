#pragma once
//todo : InternalBinaryAvlTreeNode<T>
//#include "InernalBinaryAvlTreeNode.h"
//template <class T, class IBTN>
//class IndexedBinaryTree;
//
//
//template <class T>
//class InternalBinaryAvlIndexedTreeNode : InternalBinaryAvlTreeNode<T> {
//private:
//	int	mLeftSize;
//
//public:
//	InternalBinaryAvlIndexedTreeNode() {
//		mLeftSize = 0;
//
//	}
//
//
//	template<typename S, typename R>
//	friend class BinaryTree;
//
//	template<typename S, typename R>
//	friend class IndexedBinaryTree;
//
//		virtual std::string toString();
//		//virtual std::string toString();
//	
//		template<typename S, typename R>
//		friend class BinaryTree;
//	
//		template<typename S, typename R>
//		friend class IndexedAvlBinaryTree;
//	
//		template<typename S, typename R>
//		friend class AvlBinaryTree;
//};


template <class T>
class InternalBinaryAvlIndexedTreeNode 
{
public:
	InternalBinaryAvlIndexedTreeNode(void)
	{
		mLeftSize = 0;
		height = 1;
		mLeftChild = 0;
		mRightChild = 0;
		mData = new T();
	}
	InternalBinaryAvlIndexedTreeNode(T data)
	{
		height = 1;
		mLeftChild = 0;
		mRightChild = 0;
		mData = new T();
		setData(data);
	}
	virtual ~InternalBinaryAvlIndexedTreeNode(void)
	{
		delete mData;
	}

	virtual T&	getData()
	{
		return *mData;
	}

	virtual void setData(const T& data)
	{
		*mData = data;
	}

	virtual InternalBinaryAvlIndexedTreeNode<T>*	getLeftChild()
	{
		return mLeftChild;
	}

	virtual InternalBinaryAvlIndexedTreeNode<T>*	getRightChild()
	{
		return mRightChild;
	}
	virtual InternalBinaryAvlIndexedTreeNode<T>*	getParent()
	{
		return mParent;
	}

	virtual void setLeftChild(InternalBinaryAvlIndexedTreeNode<T>* lc)
	{
		mLeftChild = lc;
	}

	virtual	void setRightChild(InternalBinaryAvlIndexedTreeNode<T>* rc)
	{
		mRightChild = rc;
	}
	virtual	void setParent(InternalBinaryAvlIndexedTreeNode<T>* parent)
	{
		mParent = parent;
	}

	virtual void setHeight(int _height) {
		height = _height;
	}
	virtual int setHeight() {
		return height;
	}
	//friend std::ostream& operator<<(std::ostream& out, LinkedList& list);
	friend std::ostream& operator<<(std::ostream& out, InternalBinaryAvlIndexedTreeNode& d) {
		//out << d.toString(); //assuming you define print for  
		out << (int)d.getData();

		return out;
	}
	virtual std::string toString();
	//virtual std::string toString();

	template<typename S, typename R>
	friend class BinaryTree;

	template<typename S, typename R>
	friend class IndexedAvlBinaryTree;

	template<typename S, typename R>
	friend class AvlBinaryTree;
protected:

	//InternalBinaryAvlTreeNode<T>*	mParent;    // this dont have this and only have subtree :(
	int	mLeftSize;
	InternalBinaryAvlIndexedTreeNode<T>*	mLeftChild;
	InternalBinaryAvlIndexedTreeNode<T>*	mRightChild;
	InternalBinaryAvlIndexedTreeNode<T>*	mParent;
	int height;

private:
	T* mData;
};

std::string InternalBinaryAvlIndexedTreeNode<int>::toString()
{
	char buff[32];
	std::string s;
	itoa(*mData, buff, 10);
	s = buff;
	return s;
}