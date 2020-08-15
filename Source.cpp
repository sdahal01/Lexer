#include <string>
#include <fstream>
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;
bool check_if_keyword(char* string);
bool check_if_delimiter(char c);
bool check_if_identifier(char* string);
bool check_if_int(char* string);
bool check_if_real_num(char* string);
bool check_if_operator(char c);
char* subString(char* string, int left, int right);
void parse(char* string);
void readFile(string filename);

int main() {
	readFile("input.txt");
	system("pause");
	return 0;
}

// Checking if the its keyword
bool check_if_keyword(char* string)
{
	if (!strcmp(string, "int") || !strcmp(string, "float")
		|| !strcmp(string, "bool") || !strcmp(string, "if")
		|| !strcmp(string, "else") || !strcmp(string, "then")
		|| !strcmp(string, "endif") || !strcmp(string, "while") || !strcmp(string, "whileend")
		|| !strcmp(string, "do") || !strcmp(string, "doend") || !strcmp(string, "for")
		|| !strcmp(string, "forend") || !strcmp(string, "input") || !strcmp(string, "output")
		|| !strcmp(string, "and") || !strcmp(string, "or") || !strcmp(string, "function"))
		return true;
	else
		return false;
}

// Checking if the its an identifier

// Checking if the its a delimiter
bool check_if_delimiter(char c)
{
	if (c == ' ' || c == '+' || c == '-' || c == '*' ||
		c == '/' || c == ',' || c == ';' || c == '>' ||
		c == '<' || c == '=' || c == '(' || c == ')' ||
		c == '[' || c == ']' || c == '{' || c == '}' ||
		c == '\'' || c == ':' || c == '!' || c == '.')
		return true;
	else
		return false;
}
bool check_if_identifier(char* string)
{
	if (string[0] == '0' || string[0] == '1' || string[0] == '2' ||
		string[0] == '3' || string[0] == '4' || string[0] == '5' ||
		string[0] == '6' || string[0] == '7' || string[0] == '8' ||
		string[0] == '9' || check_if_delimiter(string[0]) == true)
		return false;
	else
		return true;
}

// Checking if the its an int
bool check_if_int(char* string)
{
	int length = strlen(string);
	if (length == 0)
		return false;
	for (int i = 0; i < length; i++)
	{
		if (string[i] != '0' && string[i] != '1' && string[i] != '2'
			&& string[i] != '3' && string[i] != '4' && string[i] != '5'
			&& string[i] != '6' && string[i] != '7' && string[i] != '8'
			&& string[i] != '9' || (string[i] == '-' && i > 0))
			return false;
	}
	return true;
}
// Checking if the its a real number
bool check_if_real_num(char* string)
{
	int length = strlen(string);
	bool isDecimal = false;
	if (length == 0)
		return false;
	for (int i = 0; i < length; i++)
	{
		if (string[i] != '0' && string[i] != '1' && string[i] != '2'
			&& string[i] != '3' && string[i] != '4' && string[i] != '5'
			&& string[i] != '6' && string[i] != '7' && string[i] != '8'
			&& string[i] != '9' && string[i] != '.' || (string[i] == '-' && i > 0))
			return false;
		if (string[i] == '.')
			isDecimal = true;
	}
	return isDecimal;
}
// Checking if the its an operator
bool check_if_operator(char c)
{
	if (c == '+' || c == '-' || c == '*' ||
		c == '/' || c == '>' || c == '<' ||
		c == '=' || c == '%')
		return true;
	else
		return false;
}


// Extracting the substring
char* subString(char* string, int left, int right)
{
	char* subStr = (char*)malloc(sizeof(char) * (right - left + 2));

	for (int i = left; i <= right; i++)
		subStr[i - left] = string[i];
	subStr[right - left + 1] = '\0';
	return subStr;
}
void parse(char* string)
{
	ofstream ofile;
	ofile.open("output.txt");
	int left = 0, right = 0;
	int len = strlen(string);
	ofile << "TOKENS \t\t\t\t\t\t\t Lexemes\n";
	ofile << "____________________________________________________________________\n";

	while (right <= len && left <= right) {
		if (check_if_delimiter(string[right]) == false)
			right++;

		
		if (check_if_delimiter(string[right]) == true && left == right) {
			if (check_if_operator(string[right]) == true)
				ofile << "OPERATOR \t\t\t\t\t" << string[right] << "\n";
			else
				if(string[right] != ' ')
					ofile << "SPERATOR \t\t\t\t\t" << string[right] << "\n";
				
		right++;
		left = right;
		} else if (check_if_delimiter(string[right]) == true && left != right
			|| (right == len && left != right)) {
			char* subStr = subString(string, left, right - 1);

			if (check_if_keyword(subStr) == true)
				ofile << "KEYWORD \t\t\t\t\t" << subStr << "\n";

			else if (check_if_int(subStr) == true)
				ofile << "INTEGER \t\t\t\t\t" << subStr << "\n";

			else if (check_if_real_num(subStr) == true)
				ofile << "REAL NUMBER \t\t\t\t\t" << subStr << "\n";

			else if (check_if_identifier(subStr) == true
				&& check_if_delimiter(string[right - 1]) == false)
				ofile << "IDENTIFIER \t\t\t\t\t" << subStr << "\n";

			else if (check_if_identifier(subStr) == false
				&& check_if_delimiter(string[right - 1]) == false)
				ofile  << "NOT VALID \t\t\t\t\t" << subStr << "\n";
			left = right;
		}
		
	}
	cout << "Output file has been created." << endl;
	return;
	
}

void readFile(string filename)
{
	vector<char> list;
	fstream file(filename);
	if (file.is_open())
	{
		cout << "File opened.." << filename << endl;
		string line;
		char t;
		while (getline(file, line))
		{
			line += ' ';
			for (int i = 0; i < line.length(); i++)
			{
				t = line[i];
				list.push_back(t);
			}
		}
		
	}

	char array[200];
	for (int i = 0; i < list.size() && i < 100 ; i++)
	{
		array[i] = list[i];
	}
	parse(array);
	
	file.close();
		
}