#include <iostream>
#include <queue>
#include <stack>

using namespace std;

class Tree
{
private:
	struct Node
	{
		int data;
		Node* left;
		Node* right;
		Node(int _data) { data = _data; left = nullptr; right = nullptr; }
	};

	Node* root;

	void Create();
	void CreateBST();
	void Delete(Node* ptr);
	Node* InPre(Node* ptr);
	Node* InPost(Node* ptr);

public:
	Tree();
	~Tree();

	Node* GetRoot() { return root; }

	void PreOrder(Node* ptr);
	void InOrder(Node* ptr);
	void PostOrder(Node* ptr);
	void LevelOrder(Node* ptr);
	int Count(Node* ptr);
	int Height(Node* ptr);
	int CountLeaves(Node* ptr);
	Node* Search(Node* ptr, int key);
	//void Insert(Node* ptr, int val);
	Node* Insert(Node* ptr, int val);
	Node* Delete(Node* ptr, int val);
};

int main()
{
	Tree T;

	T.InOrder(T.GetRoot());
	cout << endl;

	T.Insert(T.GetRoot(), 0);

	T.InOrder(T.GetRoot());
	cout << endl;

	T.Delete(T.GetRoot(), 0);

	T.InOrder(T.GetRoot());
	cout << endl;

	cout << "Node Count: " << T.Count(T.GetRoot()) << endl;
	cout << "Number of leaves: " << T.CountLeaves(T.GetRoot()) << endl;
	cout << "Max Tree Height: " << T.Height(T.GetRoot()) << endl;
	cout << "Search found: " << T.Search(T.GetRoot(), 5)->data << endl;

	return 0;
}

void Tree::Create()
{
	queue <Node*> q;
	Node* t;
	Node* p;

	int _data;
	cout << "Enter data for root: ";
	cin >> _data;
	root = new Node(_data);

	q.push(root);

	while (!q.empty())
	{
		p = q.front();
		q.pop();

		cout << "Enter data for left branch of " << p->data << ": ";
		cin >> _data;

		if (_data != -1)
		{
			t = new Node(_data);
			p->left = t;
			q.push(t);
		}

		cout << "Enter data for right branch " << p->data << ": ";
		cin >> _data;

		if (_data != -1)
		{
			t = new Node(_data);
			p->right = t;
			q.push(t);
		}
	}
}

void Tree::CreateBST()
{
	cout << "Enter data for binary search tree terminated by -1: ";
	int num;
	cin >> num;

	root = new Node(num);
	
	cin >> num;
	while (num != -1)
	{
		Node* ptr = root;
		Node* t = nullptr;

		while (ptr != nullptr)
		{
			t = ptr;
			if (ptr->data > num)
				ptr = ptr->left;
			else
				ptr = ptr->right;
		}

		ptr = new Node(num);
		if (ptr->data > t->data)
			t->right = ptr;
		else
			t->left = ptr;

		cin >> num;
	}
}

void Tree::Delete(Node* ptr)
{
	if (ptr->left != nullptr)
		Delete(ptr->left);

	if (ptr->right != nullptr)
		Delete(ptr->right);

	delete ptr;
}

Tree::Tree()
{
	CreateBST();
}

Tree::~Tree()
{
	Delete(root);
}

/*
void Tree::PreOrder(Node* ptr)
{
	if (ptr != nullptr)
	{
		cout << ptr->data << " ";
		PreOrder(ptr->left);
		PreOrder(ptr->right);
	}
}
*/

void Tree::PreOrder(Node* ptr)
{
	stack<Node*> s;

	while (ptr != nullptr || !s.empty())
	{
		if (ptr != nullptr)
		{
			cout << ptr->data << " ";
			s.push(ptr);
			ptr = ptr->left;
		}
		else
		{
			ptr = s.top();
			s.pop();
			ptr = ptr->right;
		}
	}
}

/*
void Tree::InOrder(Node* ptr)
{
	if (ptr != nullptr)
	{
		InOrder(ptr->left);
		cout << ptr->data << " ";
		InOrder(ptr->right);
	}
}
*/

void Tree::InOrder(Node* ptr)
{
	stack<Node*> s;

	while (ptr != nullptr || !s.empty())
	{
		if (ptr != nullptr)
		{
			s.push(ptr);
			ptr = ptr->left;
		}
		else
		{
			ptr = s.top();
			s.pop();
			cout << ptr->data << " ";
			ptr = ptr->right;
		}
	}
}

/*
void Tree::PostOrder(Node* ptr)
{
	if (ptr != nullptr)
	{
		PostOrder(ptr->left);
		PostOrder(ptr->right);
		cout << ptr->data << endl;
	}
}
*/

void Tree::PostOrder(Node* ptr)
{
	stack<Node*> s;
	s.push(ptr);

	while (!s.empty())
	{
		Node* t = s.top();

		if (t == nullptr)
		{
			s.pop();
			cout << s.top()->data << " ";
			s.pop();
			continue;
		}

		s.push(nullptr);

		if (t->right != nullptr)
			s.push(t->right);
		if (t->left != nullptr)
			s.push(t->left);
	}
}

void Tree::LevelOrder(Node* ptr)
{
	queue<Node*> q;
	Node* t;

	cout << ptr->data << " ";
	q.push(ptr->left);
	q.push(ptr->right);

	while (!q.empty())
	{
		t = q.front();
		q.pop();

		cout << t->data << " ";

		if (t->left != nullptr)
			q.push(t->left);
		if (t->right != nullptr)
			q.push(t->right);
	}
}

int Tree::Count(Node* ptr)
{
	if (ptr != nullptr)
		return Count(ptr->left) + Count(ptr->right) + 1;
	return 0;
}

int Tree::Height(Node* ptr)
{
	int x = 0;
	int y = 0;

	if (ptr == nullptr)
		return 0;
	else
	{
		x = Height(ptr->left);
		y = Height(ptr->right);
	}

	if (x > y)
		return x + 1;
	else
		return y + 1;
}

int Tree::CountLeaves(Node* ptr)
{
	if (ptr == nullptr)
		return 0;
	else if (ptr->left == nullptr && ptr->right == nullptr)
		return 1;
	else
		return CountLeaves(ptr->left) + CountLeaves(ptr->right);
}

Tree::Node* Tree::Search(Node* ptr, int key)
{
	while (ptr != nullptr)
	{
		if (ptr->data == key)
			return ptr;
		else if (ptr->data > key)
			ptr = ptr->left;
		else
			ptr = ptr->right;
	}

	return nullptr;
}

/*
void Tree::Insert(Node* ptr, int val)
{
	Node* t = nullptr;

	while (ptr != nullptr)
	{
		t = ptr;

		if (ptr->data == val)
			return;
		else if (ptr->data > val)
			ptr = ptr->left;
		else
			ptr = ptr->right;
	}

	ptr = new Node(val);
	if (ptr->data < t->data)
		t->left = ptr;
	else
		t->right = ptr;
}
*/

Tree::Node* Tree::Insert(Node* ptr, int val)
{
	if (ptr == nullptr)
	{
		Node* t = new Node(val);
		return t;
	}
	else if (val < ptr->data)
		ptr->left = Insert(ptr->left, val);
	else
		ptr->right = Insert(ptr->right, val);

	return ptr;
}

Tree::Node* Tree::Delete(Node* ptr, int val)
{
	if (ptr == nullptr)
		return nullptr;

	if (ptr->left == nullptr && ptr->right == nullptr)
	{
		if (ptr == root)
			root = nullptr;
		delete ptr;
		return nullptr;
	}

	if (ptr->data > val)
		ptr->left = Delete(ptr->left, val);
	else if (ptr->data < val)
		ptr->right = Delete(ptr->right, val);
	else
	{
		if (Height(ptr->left) > Height(ptr->right))
		{
			Node* t = InPre(ptr->left);
			ptr->data = t->data;
			ptr->left = Delete(ptr->left, t->data);
		}
		else
		{
			Node* t = InPost(ptr->right);
			ptr->data = t->data;
			ptr->right = Delete(ptr->right, t->data);
		}
	}

	return ptr;
}

Tree::Node* Tree::InPre(Node* ptr)
{
	Node* t = nullptr;

	while (ptr != nullptr)
	{
		t = ptr;
		ptr = ptr->right;
	}

	return t;
}

Tree::Node* Tree::InPost(Node* ptr)
{
	Node* t = nullptr;

	while (ptr != nullptr)
	{
		t = ptr;
		ptr = ptr->left;
	}

	return t;
}