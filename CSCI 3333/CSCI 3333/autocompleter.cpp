#include "autocompleter.h"

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
	if (this->root == nullptr)
	{
		return 0;
	}
	else
	{
		return (1 + size_recurse(this->root->left) + size_recurse(this->root->right));
	}
}

//Completions function
void Autocompleter::completions(string x, vector<string> &T)
{
	//Clearing the vector so it can be filled again
	T.clear();
	//Declaring new vector to store entries and send it to completions_recurse
	vector<Entry> D;
	//New entry with an empty string and 0 as frequency and storing it three times in the vector
	//making it a size 3 vector
	Entry emptyEntry;
	emptyEntry.s = "";
	emptyEntry.freq = 0;
	D.push_back(emptyEntry);
	D.push_back(emptyEntry);
	D.push_back(emptyEntry);

	completions_recurse(x, root, D);
}

//Recursive completions function
void Autocompleter::completions_recurse(string x, Node* root, vector<Entry> &C)
{
	//If root equals null, do nothing
	if (root == nullptr)
	{
		return;
	}
	else if (root->e.s > x)
	{
		//If the entry at root has greater frequency than the 1st element of the vector
		//and the string (s) starts with the substring (x), the entry is inserted as the first element,
		//the previous first element becomes the second and the previous second element becomes the last
		if (root->e.freq >= C[0].freq && (root->e.s.rfind(x, 0) == 0))
		{
			Entry hold, hold1;
			hold = C[0];
			C[0] = root->e;
			hold1 = C[1];
			C[1] = hold;
			C[2] = hold1;
		}
		//If the entry at root has greater frequency than the 2nd element of the vector
		//and the string (s) starts with the substring (x), the entry is inserted as the second element
		//and the previous second element becomes the third element
		else if (root->e.freq >= C[1].freq && (root->e.s.rfind(x, 0) == 0))
		{
			Entry hold;
			hold = C[1];
			C[1] = root->e;
			C[2] = hold;
		}
		//If the entry at root has greater frequency than the 3rd element of the vector
		//and the string (s) starts with the substring (x), the entry is inserted as the third element
		else if (root->e.freq >= C[2].freq && (root->e.s.rfind(x, 0) == 0))
		{
			C[2] = root->e;
		}
		//Check for more strings until it reaches nullptr
		completions_recurse(x, root->left, C);
		completions_recurse(x, root->right, C);
	}
	else
	{
		//If the the string of the entry is not greater than x, then it will check only to the right
		completions_recurse(x, root->right, C);
	}
}

void Autocompleter::insert(string x, int freq)
{
	Entry obj;
	obj.s = x;
	obj.freq = freq;

	insert_recurse(obj, this->root);

}

void Autocompleter::insert_recurse(Entry e, Node *&root)
{
	if (root == nullptr)
	{
		Node *baby = new Node(e);
		root = baby;
	}

	if (e.s == root->e.s && e.freq == root->e.freq)
	{
		return;
	}
	else
	{
		if(root->e.s.substr(0, e.s.length()) > e.s)
		{
			insert_recurse(e, root->left);
		}
		else
		{
			insert_recurse(e, root->right);
		}
	}

	rebalance(root);
}

void Autocompleter::rebalance(Node *root)
{
	int heightdiff = height(root->left) - height(root->right);

	if(heightdiff > 1)
	{
		if (height(root->left) > 0)
		{

		}
	}
	else if (heightdiff < -1)
	{

	}
}

void Autocompleter::right_right_rotate(Node* &root)
{
	Node *a, *b, *bl;

	a = root;
	b = root->right;
	bl = b->left;

	root = b;
	a->right = bl;
	b->left = a;

}
void Autocompleter::left_left_rotate(Node* &root)
{
	Node *a, *b, *br;		//these pointers will point to 

	a = root;
	b = root->left;
	br = b->right;

	root = b;
	a->left = br;
	b->right = a;
}
void Autocompleter::right_left_rotate(Node *&root)
{
	//write some code here to make it a right right rotate



	right_right_rotate(root);
}
void Autocompleter::left_right_rotate(Node *&root)
{
	//write some code here to make it a left left rotate



	left_left_rotate(root);
}

