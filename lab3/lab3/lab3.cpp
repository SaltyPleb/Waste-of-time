#include <iostream>

using namespace std;

struct Stack {
	int info;
	Stack* next;
};

Stack* Add(Stack* begin, int num) {
	Stack* p = new Stack;
	p->info = num;
	p->next = begin;
	return p;
}

void View(Stack* begin) {
	Stack* p = begin;

	while (p != NULL) {
		cout << p->info << endl;
		p = p->next;
	}
}

void DeleteNegative(Stack** p) {
	Stack* temp;

	while ((*p)->info < 0) {
		temp = *p;
		*p = (*p)->next;
		delete temp;
		if (*p == NULL) return;
	}

	temp = *p;
	while (temp->next != NULL) {
		if (temp->next->info < 0)
		{
			Stack* toDel = temp->next;
			temp->next = temp->next->next;
			delete toDel;
		}
		else temp = temp->next;
	}
}

void SortInfo(Stack* p) {
	Stack* temp = NULL, * temp1;
	int r;

	if (p->next == NULL) return;

	do {
		for (temp1 = p; temp1->next != temp; temp1 = temp1->next)
			if (temp1->info > temp1->next->info) {
				r = temp1->info;
				temp1->info = temp1->next->info;
				temp1->next->info = r;
			}
		temp = temp1;
	} while (p->next != temp);
}

void Clear(Stack** p) {
	Stack* toDel;
	while (*p != NULL) {
		toDel = *p;
		*p = (*p)->next;
		delete toDel;
	}
}

int main() {
	Stack* begin = NULL;
	int key = -1, num = 0;
	const int MIN = -20, MAX = 20;

	while (1) {
		system("cls");
		cout << "1 - Create\n2 - Add\n3 - View\n4 - Remove negative\n0 - Exit" << endl;

		cin >> key;
		switch (key)
		{
		case 1:
			if (begin != NULL) Clear(&begin);
		case 2:
			system("cls");

			if (key != 1 && begin == NULL) {
				cout << "You need to create stack" << endl;
				system("pause");
				continue;
			}

			cout << "Enter quantity elements to add in stack... ";
			cin >> num;

			for (int i = 0; i < num; i++) {
				begin = Add(begin, rand() % (MAX - MIN) + MIN);
			}
			break;
		case 3:
			system("cls");

			if (begin == NULL) {
				cout << "Stack is empty" << endl;
				system("pause");
				continue;
			}

			SortInfo(begin);
			View(begin);

			system("pause");
			break;
		case 4:
			system("cls");

			if (begin == NULL) {
				cout << "Stack is empty" << endl;
				system("pause");
				continue;
			}

			DeleteNegative(&begin);
			cout << "Complete" << endl;

			system("pause");
			break;
		case 0:
			Clear(&begin);
			exit(0);
			break;
		default:
			continue;
			break;
		}
	}
}