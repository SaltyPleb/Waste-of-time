#include <iostream>
//using namespace std;

struct queue
{
	int info;
	queue* next, * prev;

} *begin, * end, * t;


void create(queue**, queue**, int);
void add(int, queue**, queue**, int);
void individ(queue**, queue**);
void view(int, queue*);
void clear(queue**);

void create(queue** b, queue** e, int data)
{
	t = new queue;
	t->info = data;
	t->next = t->prev = nullptr;
	*b = *e = t;
}

void individ(queue** b, queue** e)
{
	while (true)
	{
		t = *b;
		bool found = false;
		while (t != nullptr)
		{
			if (t->info < 0)
			{
				found = true;
				break;
			}
			t = t->next;
		}
		if (!found) break;
		if (t->prev == nullptr)
		{
			(t->next)->prev = nullptr;
			*b = t->next;
			delete t;
			continue;
		}
		if (t->next == nullptr)
		{
			(t->prev)->next = nullptr;
			*e = t->prev;
			delete t;
			continue;
		}
		(t->prev)->next = t->next;
		(t->next)->prev = t->prev;
		delete t;
	}
}

void add(int type, queue** b, queue** e, int data)
{
	t = new queue;
	t->info = data;
	if (!type)
	{
		t->prev = nullptr;
		t->next = *b;
		(*b)->prev = t;
		*b = t;
	}
	else
	{
		t->next = nullptr;
		t->prev = *e;
		(*e)->next = t;
		*e = t;
	}
}
void view(int type, queue* t)
{
	while (t != nullptr)
	{
		std::cout << t->info << std::endl;
		if (type) t = t->prev; else t = t->next;
	}
}

void clear(queue** p)
{
	while (*p != nullptr)
	{
		t = *p;
		*p = (*p)->next;
		delete t;
	}
}

int main()
{
	int i, in, n, kod, kod1;
	char Str[2][10] = { "Begin ", "End " };
	while (true)
	{
		std::cout << "\n\tCreat - 1\n\tAdd - 2\n\tView - 3\n\tDel - 4\n\tindivid - 5\n\tEXIT - 0  :  ";
		std::cin >> kod;
		switch (kod)
		{
		case 1:
			if (begin != NULL)
			{
				std::cout << "Clear Memory!" << std::endl;
				break;
			}
			std::cout << "Begin Info = ";
			std::cin >> in;
			create(&begin, &end, in);
			std::cout << "Creat Begin = " << begin->info << std::endl;
			break;
		case 2:
			std::cout << "Info = ";
			std::cin >> in;
			std::cout << "Add Begin -0, Add End -1 :  ";
			std::cin >> kod1;
			add(kod1, &begin, &end, in);
			if (kod1 == 0)
				t = begin;
			else t = end;
			std::cout << "Add to " << Str[kod1] << "  " << t->info << std::endl;
			break;
		case 3:
			if (!begin)
			{
				std::cout << "queue Pyst!" << std::endl;
				break;
			}
			std::cout << "View Begin-0,View End-1:";
			std::cin >> kod1;
			if (kod1 == 0)
			{
				t = begin;
				std::cout << "--Begin --" << std::endl;
			}
			else
			{
				t = end;
				std::cout << "---End --" << std::endl;
			}
			view(kod1, t);
			break;
		case 4:
			clear(&begin);
			std::cout << "Memory Free!" << std::endl;
			break;
		case 5:
			individ(&begin, &end);
			std::cout << "Individ has done!" << std::endl;
			break;
		case 0:
			if (begin != NULL) clear(&begin);
			return 0;
		}
		system("pause");
		system("cls");
	}
}