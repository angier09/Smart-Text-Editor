#pragma warning(disable : 4996)
#include<iostream>
#include<cctype>
#include<string>
#include<cstring>
#include<fstream>
#include<windows.h>
#include<cstdio>
#include<queue>

using namespace std;

void SetCursorPosition(int x, int y)
{
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { x,y };
	SetConsoleCursorPosition(output, pos);
}

class Node1
{
public:
	char ch;
	string str;
	int count;
	Node1* next;
	Node1* left;
	Node1* right;

	Node1()
	{
		ch = ' ';
		count = 0;
		next = NULL;
		left = NULL;
		right = NULL;
	}
};

class List
{
private:
	Node1* head;

public:
	List()
	{
		head = NULL;
	}

	Node1* get_head()
	{
		return head;
	}

	Node1* check_char(char ch)
	{
		if (head == NULL)
		{
			return NULL;
		}
		else
		{
			Node1* temp = head;
			Node1* return_value = NULL;
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

		Node1* check = check_char(ch);

		if (check == NULL)
		{
			if (head == NULL)
			{
				Node1* newnode = new Node1;
				newnode->ch = ch;
				newnode->count = 1;
				head = newnode;
			}
			else if (head->next == NULL)
			{
				Node1* newnode = new Node1;
				newnode->ch = ch;
				newnode->count = 1;
				head->next = newnode;
			}
			else
			{
				Node1* temp = head;
				while (temp->next != NULL)
				{
					temp = temp->next;
				}

				Node1* newnode = new Node1;
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
			Node1* temp = head;
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
		Node1* current = head;
		Node1* forward = head->next;
		Node1* prev = NULL;
		Node1* temp;
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

	void insert_node(Node1* node)
	{
		if (head == NULL)
		{
			head = node;
		}
		else
		{
			Node1* temp = head;

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

		Node1* current = head;
		Node1* forward = current->next;
		Node1* temp = head;

		while (head->next != NULL)
		{
			current = head;
			forward = current->next;
			Node1* newnode = new Node1;
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
		Node1* temp = head;

		while (temp != NULL)
		{
			cout << temp->ch << ": " << temp->str << endl;
			temp = temp->next;
		}
		cout << endl;
	}
	void create_code(Node1* temp, string st)
	{
		traverse(temp, st);
	}

	void traverse(Node1* temp, string st)
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
			Node1* newnode = new Node1;
			newnode->str = st;
			newnode->ch = temp->ch;
			insert_node(newnode);
			traverse(temp->left, st + '0');
			traverse(temp->right, st + '1');
		}

	}

	void encoded_string(string st, string& st1)
	{
		Node1* temp = head;
		for (int i = 0; i < st.size(); i++)
		{
			temp = head;
			if ((st[i] >= 'a' && st[i] <= 'z') || (st[i] >= 'A' && st[i] <= 'Z'))
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

string userEncodedFile = "\0"; //gobal variable it will have file name
void encoded(string st, string file_name) // pssing file name and ofstream object
{
	List l;
	List codes;
	string st1 = " ";
	int length = 0;
	char c = ' ';

	for (int i = 0; i < st.size(); i++)
	{
		l.insert(st[i]);
	}
	l.insert_tree();

	codes.create_code(l.get_head(), st1);

	codes.encoded_string(st, st1);

	//writing to file
	ofstream output;
	Node1* temp = codes.get_head();

	output.open("encoded" + file_name, ios::app);

	output << st1 << "-";

	while (temp != NULL)
	{
		output << temp->ch << temp->str;
		temp = temp->next;
	}
	output << '.';
}

void encodeFile(string file_name) //before exit encode file, passing file name
{
	string s;

	ifstream readfile;

	readfile.open(file_name, ios::in);

	if (!readfile.is_open())
	{
		cout << "File cannot open!" << endl;
		return;
	}

	while (!readfile.eof())
	{
		getline(readfile, s);
		if (!readfile.eof())
		{
			encoded(s, file_name); //encode each word of file
		}
	}
	readfile.close();
}


class Node
{
public:
	char letter;		//it will store charcter:in word 'trie',letter ='t', letter ='r',letter = 'i',letter = 'e' 
	bool isWord;		//flag will be true only when a word is completed 'trie' at 'e' isWord is true 
	Node* childern[26];	//each node will have 26 childern's, lowercase alphates only
	bool suggested;		//if word displayed in word suggestion don't display
	bool selected;		//to check word selected or not
public:

	Node() //constructor
	{
		letter = '\0';
		isWord = false;
		suggested = false;
		selected = false;
		for (int i = 0; i < 26; i++)
		{
			childern[i] = nullptr;
		}
	}

	Node(char ch) 	//parametrized constructor
	{
		letter = ch;
		isWord = false;
		suggested = false;
		selected = false;
		for (int i = 0; i < 26; i++)
		{
			childern[i] = nullptr;
		}
	}
};

//queue used for word suggestions
queue<char> words;
queue<char>temp;
char queTop = ' ';
int queSize = 0;
const int suggestionSize = 30;
//array of 10 used because at a time 10 suggested words will be displayed
string arrStr[suggestionSize] = {};
string suggestedWord = " ";
int arrStrCount = 0;

class TriTree
{
private:
	Node* rootNode;

public:

	TriTree()
	{
		rootNode = new Node; //keep root node an empty character
	}

	void insertWord(string inputWord)
	{
		char ch = '\0';
		int index = 0;
		Node* current = rootNode;
		for (int i = 0; i < inputWord.length(); i++)
		{
			ch = inputWord[i];
			if (isupper(ch) == true) //check for upper case letters
			{
				ch = ch + 32;		 //make lower case
			}

			index = ch - 'a';		//to find index of array where our next letter will be pointing
			if (current->childern[index] == nullptr)
			{
				current->childern[index] = new Node(ch);
			}
			current = current->childern[index];
		}
		current->isWord = true;
	}

	bool checkWordinTree(string inputWord)  //checking that word exits in tree or not
	{
		char ch = '\0';
		int index = 0;
		Node* current = rootNode;
		for (int i = 0; i < inputWord.length(); i++)
		{
			ch = inputWord[i];
			if (isupper(ch) == true) //check for upper case letters
			{
				ch = ch + 32;		 //make lower case
			}

			index = ch - 'a';		//to find index of array where our next letter will be pointing
			if (current->childern[index] == nullptr)
			{
				cout << "Word Does Not Exist" << endl;
				return false;
			}
			else
			{
				cout << current->childern[index]->letter;
				current = current->childern[index];
			}
		}
		cout << endl;
		return true;
	}

	bool loadDictionary(TriTree& trieObj) //loading whole dictionary in tree
	{
		ifstream inputWords;
		inputWords.open("Sorted Dictionary.txt", ios::in);
		//inputWords.open("DIC.txt", ios::in);
		if (inputWords.is_open() != true) //if file does not open
		{
			cout << "Dictionary File cannot open" << endl;
			return false;
		}
		while (inputWords.eof() != true) //if not end of file input in tree
		{
			string str;
			inputWords >> str;
			if (inputWords.eof() != true)  //not storing end of file character in tree
			{
				trieObj.insertWord(str);
			}
		}
		inputWords.close(); //close file at the end
	}


	Node* startFrmLetter(string inputLetter) //moving pointer to the location of letter given by user
	{
		arrStrCount = 0;
		char ch = ' ';
		int index = 0;
		Node* current = rootNode;
		queSize = inputLetter.length();
		for (int i = 0; i < inputLetter.length(); i++) //loop ends on length 
		{
			ch = inputLetter[i];
			if (isupper(ch) == true) //check for upper case letters
			{
				ch = ch + 32;		 //make lower case
			}

			index = ch - 'a';		//to find index of array where our next letter will be pointing
			words.push(ch);			//given user words push in que,used later
			queTop = ch;

			if (current->childern[index] == nullptr) //if null do nothing
			{
			}
			if (current->childern[index] != nullptr) //if not null go to the child and search again 
			{
				//cout << current->childern[index]->letter;
				current = current->childern[index];
			}
		}
		return current; //retun current...from this location the words will be searched
	}
	void checkingSuggestions(Node* current)
	{
		Node* currentPtr = current;
		for (int index = 0; index < 26; index++)
		{
			currentPtr = current;
			if (currentPtr->childern[index] != NULL)
			{
				currentPtr = currentPtr->childern[index];
				//can & cannot are two where, one is completed on n and other on t 
				//so if we in que if we have to chech that 'n' is enqueued
				//thats why this variable is used
				queTop = currentPtr->letter;
				words.push(currentPtr->letter);
				checkingSuggestions(currentPtr);
				if (currentPtr->isWord == true && currentPtr->suggested == false)
				{
					if (queTop != currentPtr->letter)
					{
						words.push(currentPtr->letter);
					}
					currentPtr->suggested = true;
					suggestedWordArr();
				}
			}
		}
	}

	void suggestedWordArr()
	{
		suggestedWord = "\0";	//every time new word will be suggested so making it null
		char ch = ' ';
		int i = 0;
		while (words.empty() != true)
		{
			if (i < queSize)    //count of words enter by user, push in temp queu bcz we need for next sugg
			{
				ch = words.front();
				suggestedWord = ch + suggestedWord;
				temp.push(ch);
				words.pop();
				//cout << ch;
			}
			else
			{
				ch = words.front();
				suggestedWord = ch + suggestedWord;
				words.pop();
				//cout << ch;
			}
			i = i + 1;
		}
		//word is stored in reverse so making it orignal word
		reverse(suggestedWord.begin(), (suggestedWord.end()));
		if (arrStrCount < suggestionSize)
		{
			arrStr[arrStrCount] = suggestedWord;       //arrStrCount is the count of suggested words in array
			arrStrCount = arrStrCount + 1;
		}
		while (temp.empty() != true)
		{
			ch = temp.front();
			temp.pop();
			queTop = ch;
			words.push(ch);
		}
	}

	void callSugg(string letter)
	{
		//initiallizing 
		while (words.empty() != true)
		{
			words.pop();
		}
		//for (int i = 0; i < suggestionSize; i++)
		//{
		//	arrStr[i] = "\0";
		//}
		Node* current = startFrmLetter(letter);
		checkingSuggestions(current);
	}

	void showSuggestedWords(int index, string& suggestSTR)
	{
		if (arrStr[index] != "\0" && index < suggestionSize)
		{
			suggestSTR = arrStr[index];
			cout << arrStr[index] << endl;
		}
	}
};

using namespace std;

void clearScreen()
{
	for (int i = 23; i < 28; i++)
	{
		for (int j = 0; j < 65; j++)
		{
			cout << " ";
		}
	}
	cout << endl;
}

void writeSuggestioninFile(string fileName, string suggestedWord)
{
	ofstream writeFile;
	writeFile.open(fileName, ios::app);
	if (writeFile.is_open() != true)
	{
		cout << fileName << " cannot open" << endl;
	}
	writeFile << suggestedWord << endl;
}

using namespace std;

string suggestion = "\0";
int cursorLocation = 0; //to print suggested word at typed place we will use this variable
int writingInFile(ofstream& writeUserFile, string fileName, int& stringLength, string suggestedWord)
{
	bool flagFile = false;
	//cin.clear();
	int len = fileName.length();		//file name input by user ...take its length
	char* file = new char[len + 1];		//allocate character array 
	for (int i = 0; i < len + 1; i++)	//store file name in character array
	{
		file[i] = fileName[i];
	}
	//cursorLocation = 0;
	char discard;
	char ch = '_';
	if (suggestedWord != "\0")
	{
		cout << " " << suggestedWord << " ";
		writeSuggestioninFile(fileName, suggestedWord);
		flagFile = true;
	}
	else
	{
		cout << " ";
	}
	FILE* filePtr{};            //file pointer pointer to the file where we want to save our text
	filePtr = fopen(file, "a"); //fopen takes character pointer as input and "a" shows it is in append mode
	while (ch != '=')
	{
		if (ch == '\n' && ch != '=')
		{
			cin >> ch;
			if (isupper(ch) == true) //check for upper case letters
			{
				ch = ch + 32;		 //make lower case
			}
		}
		else if (ch != '=' && ch != '3' && ch != '4')
		{
			cin >> ch;
			if (ch != '\n' && ch != '=' && ch != '3' && ch != '4')
			{
				cursorLocation = cursorLocation + 1;
				suggestion = suggestion + ch;
			}
			if (isupper(ch) == true) //check for upper case letters
			{
				ch = ch + 32;		 //make lower case
			}
		}
		if (ch == '=')			//if user press '=' then suggestions will be shown
		{
			putc('\n', filePtr);
			writeUserFile.close();
			return 1;
		}
		else if (ch == '3')		//if user press '3' then save file & end
		{
			putc('\n', filePtr);
			writeUserFile.close();
			return 0;
		}
		else if (ch == '4')		//if user press '4' then end
		{
			return 0;
		}
		++stringLength;
		stringLength = (stringLength + suggestedWord.length());
		suggestedWord = "\0";
		if (flagFile != true)
		{
			putc(ch, filePtr);
		}
	}

}

using namespace std;
int main()
{
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "                                                       TEXT EDITOR                                                      " << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "		MENU:	1: New File		2:Load Saved File	3: Save File & Exit		4: Exit " << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "Entre Choice = ";
	int choice = 0;
	cin >> choice;
	cin.ignore();
	ofstream writeUserFile;
	string fileName;
	int stringLength = 0;
	int sentenceLength = 0;
	int col = 0;
	int row = 0;
	switch (choice)
	{
	case 1:  //creating new file
	{
		do
		{
			cout << "Enter New File Name (fileName.txt): ";
			getline(cin, fileName);
			writeUserFile.open(fileName, ios::out);
			userEncodedFile = fileName;
		} while (writeUserFile.fail());
		cout << "File created Succesfully...Start Typing" << endl;
		break;
	}
	case 2: //loading prevoiusly saved data
	{
		cout << "Enter File Name (fileName.txt): ";
		getline(cin, fileName);
		ifstream readUserFile;
		readUserFile.open(fileName, ios::app);

		if (readUserFile.is_open() != true)	//if file does not open
		{
			cout << "User File cannot open" << endl;
			return 0;
		}
		cout << "File Opened...Continue Typing" << endl;
		userEncodedFile = fileName;
		while (readUserFile.eof() != true) //if not end of file input in tree
		{
			string str;
			getline(readUserFile, str);
			if (readUserFile.eof() != true)  //not storing end of file character in tree
			{
				cout << str << " ";
				sentenceLength = str.length();
				stringLength = (sentenceLength + (stringLength + 1));
			}

		}
		cout << " ";
		stringLength = stringLength + 1;
		readUserFile.close();
		break;
	}
	case 3: //save file and end program
	{
		cout << "Enter File Name (fileName.txt): ";
		getline(cin, fileName);
		userEncodedFile = fileName;
		encodeFile(userEncodedFile);
		writeUserFile.close();
		return 0;
		break;
	}
	case 4: //simply exit programme
	{
		cout << endl << "EXIT" << endl;
		return 0;
		break;
	}
	default:
		break;
	}

	bool flag = false;
	string temp = "\0";
	col = stringLength - 1;
	TriTree treeObj;
	treeObj.loadDictionary(treeObj);
	flag = writingInFile(writeUserFile, fileName, stringLength, temp);
	if (flag == 0)
	{
		encodeFile(userEncodedFile);
		SetCursorPosition(22, 28);  // x col, y row 
		cout << "-----------------------EXITED--------------------" << endl;
		return 0;
	}

	int wordCount = 0;
	int x = 9;
	int y = 18;
	//cout << "Length of my string = " << stringLength << endl;
	SetCursorPosition(0, 20); //0 col and 20 row
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "		          PRESS:	  '/': New Suggestion		 ';': Select Suggested Word" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	char discard;
	char letter[100]{};
	char symbol = ' ';
	string str = " ";

	string suggestSTR = "\0";
	int suggestedWord = 0;
	while (symbol != 4)
	{
		treeObj.callSugg(suggestion); //this function will create suggestion of words input by user

		suggestSTR = "\0";
		//treeObj.callSugg(suggestion); //this function will create suggestion of words input by user
		SetCursorPosition(0, 23); //0 col and 23 row
		clearScreen();
		SetCursorPosition(0, 23); //0 col and 23 row
		cout << "Suggested Word: ";
		if (suggestedWord < suggestionSize)
		{
			treeObj.showSuggestedWords(suggestedWord, suggestSTR);
		}
		cout << "Enter Choice : ";

		cin >> symbol;
		switch (symbol)
		{
		case ';':
		{
			suggestion = "\0";
			SetCursorPosition((stringLength - cursorLocation), 8); //x col and 8 row
			//writingInFile(writeUserFile, fileName, stringLength, suggestSTR);
			flag = writingInFile(writeUserFile, fileName, stringLength, suggestSTR);
			if (flag == 0)
			{
				SetCursorPosition(22, 28);  // x col, y row 
				cout << "-----------------------EXITED--------------------" << endl;
				encodeFile(userEncodedFile); //before exit encode file, pssing file name
				return 0;
			}
			suggestedWord = 0;
			break;
		}
		case '/':
		{
			suggestedWord = suggestedWord + 1;
			break;
		}
		case '4':
		{
			writeUserFile.close();
			SetCursorPosition(22, 28);  // x col, y row 
			encodeFile(userEncodedFile);
			return 0;
		}
		default:
			break;
		}
	}

	SetCursorPosition(22, 28);  // x col, y row 
	return 0;
}