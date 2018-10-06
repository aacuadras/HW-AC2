#include "autocompleter.h"


///TODO
//Work on rotations
//Aaron: left_rotation, left_right_rotation
//Jonathan: right_rotation, right_left rotation

//Constructor
Autocompleter::Autocompleter()
{
	//Root points to nothing when the Autocompleter is declared
	root = nullptr;
	
}

//Insert function


//Size function
int Autocompleter::size()
{
	//Returns the value returned by size_recurse starting from root
	return size_recurse(root);
}

//Recursive size function
int Autocompleter::size_recurse(Node * root)
{
	//If the root pointer points to null, it doesn't add 1 to the sum
	if (root == nullptr)
	{
		return 0;
	}
	else
	{
		return (1 + size_recurse(root->left) + size_recurse(root->right));
	}
}

//Completions function
void Autocompleter::completions(string x, vector<string> &T)
{
	vector<Entry> J;
	completions_recurse(x, this->root, J);
	T.resize(3);

	T[0] = J[0].s;
	T[1] = J[1].s;
	T[2] = J[2].s;

	if (T[2] == "")
	{
		T.pop_back();
	}
	if (T[1] == "")
	{
		T.pop_back();
	}
	if (T[0] == "")
	{
		T.pop_back();
	}

}

//Recursive completions function
void Autocompleter::completions_recurse(string x, Node* root, vector<Entry> &C)
{
	Entry obj;
	obj.freq = 0;
	obj.s = "";
	if (C.empty() == true)
	{
		C.push_back(obj);
		C.push_back(obj);
		C.push_back(obj);
	}

	if (root == nullptr)
	{
		return;
	}

	if (root->e.s.substr(0, x.length()) == x)
	{
		if (root->e.freq > C[0].freq && C[1].s != root->e.s && C[2].s != root->e.s)
		{
			C.insert(C.begin(), root->e);
			C.resize(3);
		}
		if (root->e.freq > C[1].freq && C[0].s != root->e.s && C[2].s != root->e.s)
		{
			C.insert(C.begin() + 1, root->e);
			C.resize(3);
		}
		if (root->e.freq > C[2].freq && C[0].s != root->e.s && C[1].s != root->e.s)
		{
			C.insert(C.begin() + 2, root->e);
			C.resize(3);
		}

		completions_recurse(x, root->left, C);
		completions_recurse(x, root->right, C);
	}

	else if (root->e.s.substr(0, x.length()) > x)
	{
		completions_recurse(x, root->left, C);
	}
	else
	{
		completions_recurse(x, root->right, C);
	}
}

//Insert function
void Autocompleter::insert(string x, int freq)
{
	Entry obj;
	obj.s = x;
	obj.freq = freq;
	//cout << x << endl;
	insert_recurse(obj, this->root);

}

//Recursive insert function
void Autocompleter::insert_recurse(Entry e, Node *&root)
{
	if (root == nullptr)
	{
		root = new Node(e);
	}
	else if (e.s == root->e.s && e.freq == root->e.freq)
	{
		return;
	}
	else
	{
		//if (root->e.s.substr(0, e.s.length()) > e.s)
		if (root->e.s.compare(e.s) > 0)
		{
			insert_recurse(e, root->left);
		}
		else
		{
			insert_recurse(e, root->right);
		}
	}

	//Will rebalance from the bottom to the top every time something is inserted
	rebalance(root);
	root->height = MAX(root->left, root->right) + 1;
}

void Autocompleter::rebalance(Node *&root)
{
	int balfactor = height(root->left) - height(root->right);

	//If it's greater than 1, right rotate (left case)
	if (balfactor > 1)
		//if(height(root->left) > (height(root->right) + 1))
	{
		//If the height of the left subtree is greater than the height of the right subtree
		//then left_left case (right rotate)
		if (height(root->left->left) > height(root->left->right))
		{
			right_rotate(root);
		}
		//If the height of the right subtree is greater than the height of the left subtree
		//then left_right case (left_right rotate)
		else
		{
			left_rotate(root->left);
			right_rotate(root);
		}
	}
	//If it's less than 1, left rotate (right case)
	else if (balfactor < -1)
		//else if(height(root->left) > (height(root->right) + 1))
	{
		//If the height of the right subtree is greateer than the height of the left subtree
		//then right_right case (left rotate)
		if (height(root->right->left) < height(root->right->right))
		{
			left_rotate(root);
		}
		//If the height of the left subtree is greater than the height of the right subtree
		//then right_left case (right_left rotate)
		else
		{
			right_rotate(root->right);
			left_rotate(root);
		}
	}
}


void Autocompleter::right_rotate(Node *&root)
{
	if (root->right == nullptr && root->left == nullptr)
	{
		return;
	}

	Node *x = root;
	root = root->left;
	x->left = nullptr;
	x->left = root->right;
	root->right = x;

}


//"Completed left rotation"
void Autocompleter::left_rotate(Node * &root)
{
	if (root->right == nullptr && root->left == nullptr)
	{
		return;
	}
	Node *x = root;
	root = root->right;
	x->right = nullptr;
	x->right = root->left;
	root->left = x;

}

//Height update helper function
int Autocompleter::MAX(Node * x, Node *y)
{
	if (root == nullptr)
		return -1;

	else
	{
		if (height(x) > height(y))
		{
			return height(x);
		}
		else
		{
			return height(y);
		}
	}
}
