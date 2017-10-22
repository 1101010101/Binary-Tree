#include<iostream>
using namespace std;

typedef int nodeEntry;
const int SUCCESS = 0;

struct Bnode		//二叉树节点结构
{
	nodeEntry data;	//数据成员
	Bnode *left;	//左子树
	Bnode *right;	//右子树
};

class BinTree
{
	Bnode *root;
	void recursivePreorder(Bnode *x);
	void recursiveInorder(Bnode *x);
	void recursivePostorder(Bnode *x);
	int searchDelete(Bnode *subRoot, const nodeEntry target);
	int removeRoot(Bnode *subRoot);
	Bnode *searchNode(Bnode *subRoot, const nodeEntry target)const;
	int searchInsert(Bnode * &subRoot, const nodeEntry newData);
public:
	BinTree();
	~BinTree();
	void preorder();
	void inorder();
	void postorder();
	bool empty()const;
	void clear();
	int height()const;
	int size()const;
	int insert(const nodeEntry x);
	int remove(const nodeEntry x);
	int search(const nodeEntry x)const;
protected:
	int count;
};

BinTree::BinTree()
{
	count = 0;
	root = NULL;
}

BinTree::~BinTree()
{
	delete root;
}

void BinTree::preorder()			//本函数对二叉树进行前序遍历，使用辅助函数recursivePreorder
{
	recursivePreorder(root);
}

void BinTree::recursivePreorder(Bnode *subRoot)	//subRoot要么为空，要么指向一棵子二叉树
{
	if (subRoot != NULL)
	{
		cout << subRoot->data << " ";
		recursivePreorder(subRoot->left);
		recursivePreorder(subRoot->right);
	}
}

void BinTree::inorder()				//本函数对二叉树进行中序遍历，使用辅助函数recursiveInorder
{
	recursiveInorder(root);
}

void BinTree::recursiveInorder(Bnode *subRoot)//subRoot要么为空，要么指向一棵子二叉树
{
	if (subRoot != NULL)
	{
		recursiveInorder(subRoot->left);
		cout << subRoot->data << " ";
		recursiveInorder(subRoot->right);
	}
}

void BinTree::postorder()			//本函数对二叉树进行后序遍历，使用辅助函数recursivePostorder
{
	recursivePostorder(root);
}

void BinTree::recursivePostorder(Bnode *subRoot)//subRoot要么为空，要么指向一棵子二叉树
{
	if (subRoot != NULL)
	{
		recursivePostorder(subRoot->left);
		recursivePostorder(subRoot->right);
		cout << subRoot->data << " ";
	}
} 

int BinTree::search(const nodeEntry target)const 		//在BinTree里查找记录target
{
	Bnode *found = searchNode(root,target);				//调用递归查找函数
	if (found == NULL)
		return OVERFLOW;
	else
		return SUCCESS;
}

Bnode *BinTree::searchNode(Bnode *subRoot, const nodeEntry target)const//递归查找函数，在跟节点为subRoot的查找树里查找target
{
	if (subRoot == NULL || subRoot->data == target)
		return subRoot;
	else if (subRoot->data < target)
		return searchNode(subRoot->right, target);
	else
		return searchNode(subRoot->left, target);
}

/*如果有必要，也可以将递归查找改为循环查找
Bnode *BinTree::searchNode(Bnode *subRoot, const nodeEntry target)const
{
	while (subRoot != NULL&&subRoot->data != target)
		if (subRoot->data < target)
			subRoot = subRoot->right;
		else
			subRoot = subRoot->left;
	return subRoot;
}*/

int BinTree::insert(const nodeEntry newData)//在BinTree里插入记录newData
{
	return searchInsert(root, newData);
}

int BinTree::searchInsert(Bnode * &subRoot, const nodeEntry newData)//递归插入函数
{
	if (subRoot == NULL)
	{
		subRoot = new Bnode;
		if (subRoot == NULL)
		{
			cout << "不能分配新空间，插入失败" << endl;
			return OVERFLOW;
		}
		subRoot->data = newData;
		subRoot->left = NULL;
		subRoot->right = NULL;
	}
	else if (newData < subRoot->data)
		return searchInsert(subRoot->left, newData);
	else if (newData > subRoot->data)
		return searchInsert(subRoot->right, newData);
	else return OVERFLOW;
}

int BinTree::remove(const nodeEntry target) //在BinTree里删除记录target
{
	return searchDelete(root, target);//调用递归查找删除函数
}

int BinTree::searchDelete(Bnode *subRoot, const nodeEntry target)//递归查找函数
{
	if (subRoot == NULL || subRoot->data == target)
		return removeRoot(subRoot);
	else if (target < subRoot->data)
		return searchDelete(subRoot->left, target);
	else 
		return searchDelete(subRoot->right, target);
}

int BinTree::removeRoot(Bnode *subRoot)//辅助函数，在BinTree里删除记录subRoot
{
	if (subRoot == NULL)
		return OVERFLOW;
	Bnode * to_delete = subRoot;
	if (subRoot->right == NULL)			//右子树为空，往左面查找
		subRoot = subRoot->left;
	else if(subRoot->left == NULL)		//左子树为空，往右面查找
		subRoot = subRoot->right;
	else								//两棵子树皆不为空
	{
		to_delete = subRoot->left;		//往左寻找节点subRoot的前驱节点
		Bnode *parent = subRoot;		//parent记录节点to_delete的父节点
		while (to_delete->right != NULL)
		{
			parent = to_delete;			//to_delete不是前驱节点
			to_delete = to_delete->right;
		}
		subRoot->data = to_delete->data;//从节点to_delete移动到根节点
		if (parent == subRoot)
			subRoot->left = to_delete->left;
		else
			parent->right = to_delete->left;
	}
	delete to_delete;
	return SUCCESS;
}

bool BinTree::empty()const	//判断二叉树是否为空
{
	return root == NULL;
}
