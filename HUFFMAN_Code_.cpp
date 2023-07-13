#include<iostream>
#include<string>
#include<fstream>
using namespace std;


class Node {
public:
	char ch;
	string str;
	int count;
	Node* next;
	Node* left;
	Node* right;

	Node()
	{
		ch = ' ';
		count = 0;
		next = NULL;
		left = NULL;
		right = NULL;
	}
};

class List {
private:
	Node* head;

public:
	List()
	{
		head = NULL;
	}

	Node* get_head()
	{
		return head;
	}

	Node* check_char(char ch)
	{
		if (head == NULL)
		{
			return NULL;
		}
		else
		{
			Node* temp = head;
			Node* return_value = NULL;
			while (temp != NULL)
			{
				if (temp->ch == ch)
				{
					return_value = temp;
					break;
				}
				else
				{
					temp = temp->next;
				}
			}
			return return_value;
		}
	}

	void insert(char ch)
	{
		if (ch == ' ')
		{
			return;
		}

		Node* check = check_char(ch);

		if (check == NULL)
		{
			if (head == NULL)
			{
				Node* newnode = new Node;
				newnode->ch = ch;
				newnode->count = 1;
				head = newnode;
			}
			else if (head->next == NULL)
			{
				Node* newnode = new Node;
				newnode->ch = ch;
				newnode->count = 1;
				head->next = newnode;
			}
			else
			{
				Node* temp = head;
				while (temp->next != NULL)
				{
					temp = temp->next;
				}

				Node* newnode = new Node;
				newnode->ch = ch;
				newnode->count = 1;
				temp->next = newnode;
			}
		}
		else
		{
			check->count++;
		}
	}

	void display()
	{
		if (head == NULL)
			return;
		else
		{
			Node* temp = head;
			while (temp != NULL)
			{
				cout << temp->ch << temp->count << endl;
				temp = temp->next;
			}
		}
		cout << endl;
	}

	void sort()
	{
		Node* current = head;
		Node* forward = head->next;
		Node* prev = NULL;
		Node* temp;
		bool flag = false;
		if (current == NULL || forward == NULL)
		{
			return;
		}

		do
		{
			current = head;
			flag = false;
			forward = head->next;
			prev = NULL;
			while (forward != NULL)
			{
				if (prev == NULL)
				{
					if (current->count > forward->count)
					{
						current->next = forward->next;
						forward->next = current;
						head = forward;
						flag = true;

						temp = forward;
						forward = current;
						current = temp;

						prev = current;
						current = current->next;
						forward = forward->next;
					}
					else
					{
						prev = current;
						current = current->next;
						forward = forward->next;
					}
				}
				else
				{
					if (current->count > forward->count)
					{
						prev->next = forward;
						current->next = forward->next;
						forward->next = current;

						flag = true;
						temp = forward;
						forward = current;
						current = temp;

						prev = current;
						current = current->next;
						forward = forward->next;
					}
					else
					{
						prev = current;
						current = current->next;
						forward = forward->next;
					}
				}
			}
		} while (flag == true);
	}

	void insert_node(Node* node)
	{
		if (head == NULL)
		{
			head = node;
		}
		else
		{
			Node* temp = head;

			while (temp->next != NULL)
			{
				temp = temp->next;
			}
			temp->next = node;
		}
	}

	void insert_tree()
	{
		if (head == NULL)
		{
			return;
		}

		Node* current = head;
		Node* forward = current->next;
		Node* temp = head;

		while (head->next != NULL)
		{
			current = head;
			forward = current->next;
			Node* newnode = new Node;
			newnode->ch = '-';
			newnode->count = current->count + forward->count;
			newnode->left = current;
			newnode->right = forward;

			if (forward->next != NULL)
			{
				head = forward->next;
			}
			else
			{
				head = newnode;
				head->next = NULL;
				break;
			}
			current->next = NULL;
			forward->next = NULL;

			insert_node(newnode);
			if (head->next != NULL)
			{
				sort();
			}
		}
	}

	void display_codes()
	{
		Node* temp = head;

		while (temp != NULL)
		{
			cout << temp->ch << ": " << temp->str << endl;
			temp = temp->next;
		}
		cout << endl;
	}
	void create_code(Node* temp, string st)
	{
		traverse(temp, st);
	}

	void traverse(Node* temp, string st)
	{
		if (temp == NULL)
		{
			return;
		}

		if (temp->ch == '-')
		{
			traverse(temp->left, st + '0');
			traverse(temp->right, st + '1');
		}

		if (temp->ch != '-')
		{
			Node* newnode = new Node;
			newnode->str = st;
			newnode->ch = temp->ch;
			insert_node(newnode);
			traverse(temp->left, st + '0');
			traverse(temp->right, st + '1');
		}

	}

	void encoded_string(string st, string& st1)
	{
		Node* temp = head;
		for (int i = 0; i < st.size(); i++)
		{
			temp = head;
			if (st[i] >= 'a' && st[i] <= 'z')
			{
				while (temp->ch != st[i])
				{
					if (st[i] == ' ')
					{
						break;
					}
					temp = temp->next;
				}
				st1 = st1 + temp->str;
			}
			else if (st[i] == ' ')
			{
				st1 = st1 + ' ';
			}
		}
	}
};


int main()
{
	List l;
	List codes;
	string st;
	string st1;
	int length;
	char c;


	cout << "Enter string: ";
	getline(cin, st);

	for (int i = 0; i < st.size(); i++)
	{
		l.insert(st[i]);
	}
	cout << "Unsorted data: " << endl;
	l.display();

	l.sort();

	cout << "Sorted data: " << endl;
	l.display();

	l.insert_tree();

	cout << "data after tree insertion: " << endl;
	l.display();

	cout << endl;
	codes.create_code(l.get_head(), st1);

	/*codes.display_codes();*/

	codes.encoded_string(st, st1);

	//writing to file

	/*ofstream output;
	Node* temp = codes.get_head();

	output.open("out.txt",ios::app);

	output << st1 << "-";

	while (temp != NULL)
	{
		output << temp->ch << temp->str;
		temp = temp->next;
	}
	output << '.';*/

	//reading from file
	List* newlist = new List;
	string s;
	string s1;
	st1 = "";
	ifstream input;
	input.open("out.txt");

	while (input.get(c))
	{
		if (c == '-')
		{
			break;
		}
		else
		{
			st1 = st1 + c;
		}
	}

	while (input.get(c))
	{
		if (c == '.')
		{
			break;
		}
		else if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		{
			Node* newnode = new Node;
			newnode->ch = c;
			while (input.get(c))
			{
				if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
				{
					input.putback(c);
					break;
				}
				else if (c == '.')
				{

				}
				else
				{
					newnode->str = newnode->str + c;
				}
			}
			newlist->insert_node(newnode);
		}
	}

	Node* temp1 = newlist->get_head();
	bool flag = false;
	for (int i = 0; i < st1.size(); i++)
	{
		if (st1[i] == ' ')
		{
			s = s + ' ';
		}
		else
		{
			s1 = s1 + st1[i];
			while (temp1 != NULL)
			{
				if (temp1 == NULL)
				{

					break;
				}
				if (temp1->str == s1)
				{
					s = s + temp1->ch;
					s1 = "";
					break;
				}
				temp1 = temp1->next;
			}
			temp1 = newlist->get_head();
		}
	}

	cout << s << endl;
}
