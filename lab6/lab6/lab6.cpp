#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

struct tree {
	int info;
	tree* left, * right;
} *root;

void add(tree*, int);
void view(tree*, int);
tree* del_info(tree*, int);
void clear(tree*);
tree* list(int);
void create(tree**, int, int, int*);


tree* list(int inf)
{
	tree* t = new tree;
	t->info = inf;
	t->left = t->right = nullptr;
	return t;
}

void add(tree* root, int key)
{
	tree* prev, * t;
	bool find = true;
	t = root;
	prev = t;
	while (t && find)
	{
		prev = t;
		if (key == t->info)
		{
			find = false;
			std::cout << "Dublucate Key" << std::endl;
		}
		else
		{
			if (key < t->info) t = t->left; else t = t->right;
		}
	}
	if (find)
	{
		t = list(key);
		if (key < prev->info) prev->left = t; else prev->right = t;
	}
}

void view(tree* p, int level)
{
	string str;
	if (p)
	{
		view(p->right, level + 1);
		for (int i = 0; i < level; i++) str += " ";
		cout << str + to_string(p->info) << endl;
		view(p->left, level + 1);
	}
}

pair<tree*, tree*> search(tree* root, int key)
{
	tree* search, * prev_search;
	search = root;
	prev_search = nullptr;
	while (search && search->info != key)
	{
		prev_search = search;
		if (search->info > key) search = search->left; else search = search->right;
	}
	if (!search)
	{
		cout << "Not found" << endl;
		return make_pair(nullptr, nullptr);
	}
	else return make_pair(search, prev_search);
}

tree* erase(tree* root, tree* del, tree* prev_del)
{
	tree* r, * prev_r;
	if (!del->right) r = del->left; else
		if (!del->left) r = del->right; else
		{
			prev_r = del;
			r = del->left;
			while (r->right)
			{
				prev_r = r;
				r = r->right;
			}
			if (prev_r == del) r->right = del->right; else
			{
				r->right = del->right;
				prev_r->right = r->left;
				r->left = prev_r;
			}
		}
	if (del == root) root = r; else
		if (del->info < prev_del->info) prev_del->left = r; else prev_del->right = r;
	delete del;
	return root;
}

void rec_r(tree* p, tree* prev_p)
{
	if (!p) return;
	rec_r(p->right, p);
	root = erase(root, p, prev_p);
}

void rec_l(tree* p, tree* prev_p)
{
	if (!p) return;
	rec_l(p->left, p);
	root = erase(root, p, prev_p);
}

void rec_root(tree* p, tree* prev_p, int data)
{
	if (!p) return;
	if (p->info == data)
	{
		root = erase(root, p, prev_p);
		return;
	}
	if (p->info > data) rec_root(p->left, p, data); else rec_root(p->right, p, data);
	root = erase(root, p, prev_p);
}

void individ(int key)
{
	tree* del, * prev_del;
	pair<tree*, tree*> tmp = search(root, key);
	del = tmp.first;
	prev_del = tmp.second;
	if (!del)
	{
		cout << "Not key!" << endl;
		return;
	}
	rec_r(del->right, del);
	rec_l(del->left, del);
	rec_root(root, nullptr, key);
}

tree* del_info(tree* root, int key)
{
	tree* del, * prev_del;
	pair<tree*, tree*> tmp = search(root, key);
	del = tmp.first;
	prev_del = tmp.second;
	if (!del)
	{
		cout << "Not Key! :(" << endl;
		return root;
	}
	cout << "Succesfull deleted" << endl;
	return erase(root, del, prev_del);
}

void create(tree** p, int n, int k, int* a)
{
	if (n == k)
	{
		*p = nullptr;
		return;
	}
	int m = (n + k) >> 1;
	*p = new tree;
	(*p)->info = a[m];
	create(&(*p)->left, n, m, a);
	create(&(*p)->right, m + 1, k, a);
}

void pre_order(tree* p)
{
	if (p) cout << p->info << " "; else return;
	if (p->left) pre_order(p->left);
	if (p->right) pre_order(p->right);
}

void in_order(tree* p)
{
	if (!p) return;
	if (p->left) in_order(p->left);
	if (p) cout << p->info << " "; else return;
	if (p->right) in_order(p->right);
}

void post_order(tree* p)
{
	if (!p) return;
	post_order(p->left);
	post_order(p->right);
	if (p) cout << p->info << " "; else return;
}

void clear(tree* t)
{
	if (t)
	{
		clear(t->left);
		clear(t->right);
		delete t;
	}
}

void get_array(tree* p, vector<int>& arr)
{
	if (!p) return;
	if (p->left) get_array(p->left, arr);
	if (p) arr.push_back(p->info); else return;
	if (p->right) get_array(p->right, arr);
}

int main()
{
	while (true)
	{
		std::cout << " 1 - create from array,\n 2 - Add,\n 3 - view,\n 4 - erase,\n 5 - individ,\n 6 - Pre-,in-,post-order;\n 7 - balance,\n 8 - clear,\n 9 - search,\n 0 - exit" << std::endl;
		int t;
		cin >> t;
		while (t < 0 && t>9)
		{
			cout << "Incorrect input!" << endl;
			std::cin >> t;
		}
		if (t == 1)
		{
			if (root)
			{
				cout << "you must clear your tree" << endl;
				continue;
			}
			cout << "input size of your array:";
			int k; cin >> k;
			int* a = new int[k];
			cout << "input your array:" << endl;
			for (int i = 0; i < k; i++) cin >> a[i];
			sort(a, a + k);
			create(&root, 0, k, a);
			cout << "tree has created and balanced" << endl;
			delete[]a;
		}
		if (t == 2)
		{
			std::cout << "input info:";
			int info; std::cin >> info;
			if (root == nullptr) root = list(info); else add(root, info);
		};
		if (t == 3)
		{
			if (!root) cout << "You have not tree! Add something!" << endl; else
			{
				cout << "-----------------View-------------" << endl;
				view(root, 0);
			}
		}
		if (t == 4)
		{
			int info;
			cout << "input del info: ";
			cin >> info;
			root = del_info(root, info);
		}
		if (t == 5)
		{
			int info;
			cout << "input del info: ";
			cin >> info;
			individ(info);
		}
		if (t == 6)
		{
			cout << "pre-order:" << endl;
			pre_order(root);
			cout << endl;
			cout << "in-order:" << endl;
			in_order(root);
			cout << endl;
			cout << "post-order:" << endl;
			post_order(root);
			cout << endl;
		}
		if (t == 7)
		{
			vector <int> arr;
			get_array(root, arr);
			clear(root);
			int* a = new int[arr.size() + 1];
			cout << endl;
			for (int i = 0; i < arr.size(); i++) a[i] = arr[i];
			create(&root, 0, arr.size(), a);
			delete[]a;
			arr.clear();
			cout << "Tree has balanced" << endl;
		}
		if (t == 8)
		{
			clear(root);
			cout << "tree has cleared" << endl;
		}
		if (t == 9)
		{
			cout << "input search info:";
			int key; cin >> key;
			pair<tree*, tree*> tmp = search(root, key);
			if (tmp.first)
			{
				cout << "Founded!" << endl;
			}
		}
		if (t == 0)
		{
			if (root != nullptr) std::cout << "You must clear your tree!" << std::endl; else {
				std::cout << "Bye!" << std::endl; break;
			}
		}
		system("pause");
		system("cls");
	}
}

