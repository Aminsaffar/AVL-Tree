#pragma once
#include <String>
using namespace std;
template <class T>
class InternalBinaryAvlTreeNode
{
public:
	InternalBinaryAvlTreeNode(void)
	{
		height = 1;
		mLeftChild = 0;
		mRightChild = 0;
		mData = new T();
	}
	InternalBinaryAvlTreeNode(T data)
	{
		height = 1;
		mLeftChild = 0;
		mRightChild = 0;
		mData = new T();
		setData(data);
	}
	virtual ~InternalBinaryAvlTreeNode(void)
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

	virtual InternalBinaryAvlTreeNode<T>*	getLeftChild()
	{
		return mLeftChild;
	}

	virtual InternalBinaryAvlTreeNode<T>*	getRightChild()
	{
		return mRightChild;
	}
	virtual InternalBinaryAvlTreeNode<T>*	getParent()
	{
		return mParent;
	}

	virtual void setLeftChild(InternalBinaryAvlTreeNode<T>* lc)
	{
		mLeftChild = lc;
	}

	virtual	void setRightChild(InternalBinaryAvlTreeNode<T>* rc)
	{
		mRightChild = rc;
	}
	virtual	void setParent(InternalBinaryAvlTreeNode<T>* parent)
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
	friend std::ostream& operator<<(std::ostream& out, InternalBinaryAvlTreeNode& d) {
		//out << d.toString(); //assuming you define print for  
		out << (int)d.getData();

		return out;
	}

	//virtual std::string toString();

	template<typename S, typename R>
	friend class BinaryTree;

	template<typename S, typename R>
	friend class IndexedAvlBinaryTree;

	template<typename S, typename R>
	friend class AvlBinaryTree;
	template<typename T>
	friend class InternalBinaryAvlIndexedTreeNode;
protected:

	//InternalBinaryAvlTreeNode<T>*	mParent;    // this dont have this and only have subtree :(
	InternalBinaryAvlTreeNode<T>*	mLeftChild;
	InternalBinaryAvlTreeNode<T>*	mRightChild;
	InternalBinaryAvlTreeNode<T>*	mParent;
	int height;

private:
	T* mData;
};


