#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "HedeHodoShell.h"
using namespace std;
struct node
{
	vector<node*> children;
	string fileName;
	bool isFolder;
	vector<string> doc;
	node *parent;
}*root,*current;

// Create a new subdirectory under the working directory
void makeDir( string dirName )
{
	for(int i=0; i<current->children.size(); i++)
	{
		// Create a new subdirectory under the working directory
		if(current->children[i]->fileName == dirName)
		{
			cout << "ERROR: " << dirName << " already exists." << endl;
			return;
		}
	}
	node *newNode = new node;
	newNode->fileName = dirName;
	newNode->isFolder = true;
	newNode->parent = current;
	current->children.push_back(newNode);
	cout << "Directory " << dirName << " is created." << endl;
}

// Create a new empty subdocument under the working directory
void makeDoc( string docName )
{
	for(int i=0; i<current->children.size(); i++)
	{
		// If there is a subdirectory or subdocument with the same name
		if(current->children[i]->fileName == docName)
		{
			cout << "ERROR: " << docName << " already exists." << endl;
			return;
		}
	}
	node *newNode = new node;
	newNode->fileName = docName;
	newNode->isFolder = false;
	newNode->parent = current;
	current->children.push_back(newNode);
	cout << "Document " << docName << " is created." << endl;
}

// Append a line lineContent to the document named as docName
void appendLine( string docName, string lineContent)
{
	node *tmp;
	for(int i=0; i<current->children.size(); i++)
	{
		if(current->children[i]->fileName == docName)
		{
			tmp = current->children[i];
			break;
		}
	}
	tmp->doc.push_back(lineContent);
	cout << "APPEND: Document " << docName << " has " << tmp->doc.size() << " lines." << endl;
}

// Remove the subdocument from the working directory
void remove( string docName )
{
	node *tmp;
	for(int i=0; i<current->children.size(); i++)
	{
		if(current->children[i]->fileName == docName && current->children[i]->isFolder == false)
		{
			tmp = current->children[i];
			current->children.erase (current->children.begin()+i,current->children.begin()+i+1);
			cout << "REMOVE: Document " << docName << " is removed." << endl;
			delete tmp;
			return;
		}
	}
	// If such subdocument does not exist
	cout << "ERROR: " << docName << " does not exist." << endl;
}

// Recursively remove the subdirectory from the working directory
void removeRecursive(node *rootDir)
{
	if(rootDir == NULL)
	{
		return;
	}
	for(int i=0; i<rootDir->children.size(); i++)
	{
		removeRecursive(rootDir->children[i]);
	}
	delete rootDir;
}

void removeR( string dirName )
{
	for(int i=0; i<current->children.size(); i++)
	{
		if(current->children[i]->fileName == dirName && current->children[i]->isFolder == true)
		{
			removeRecursive(current->children[i]);
			current->children.erase (current->children.begin()+i,current->children.begin()+i+1);
			cout << "RECURSIVE REMOVE: Directory " << dirName << " is removed." << endl;
			return;
		}
	}
	// If such subdirectory does not exist
	cout << "ERROR: " << dirName << " does not exist." << endl;
}

// Print the path from the root directory to the working directory.
void printWorkingDirRecursive(node *cur)
{
	if(cur == root)
	{
		cout << "/";
		return;
	}
	printWorkingDirRecursive(cur->parent);
	cout << cur->fileName << "/";
}

void printWorkingDir()
{
	printWorkingDirRecursive(current);
	cout << endl;
}

// Change the working directory
void changeWorkingDir( string dirName )
{
	// If dirName is "..", then our new working directory will be the parent directory of the current working directory
	if( dirName == ".." )
	{
		current = current->parent;
		cout << "CHANGE: " << current->fileName << " is the new working directory." << endl;
		return;
	}
	else
	{
		for(int i=0; i<current->children.size(); i++)
		{
			if(current->children[i]->fileName == dirName && current->children[i]->isFolder == true)
			{
				current = current->children[i];
				cout << "CHANGE: " << current->fileName << " is the new working directory." << endl;
				return;
			}
		}
	}
	// If the current working directory does not have a subdirectory named as dirName
	cout << "ERROR: " << dirName << " does not exist." << endl;
}

// Print the names of all subdirectories and subdocuments of the working directory
void list()
{
	for(int i=0; i<current->children.size(); i++)
	{
		// Print 0 if the child is a directory
		if(current->children[i]->isFolder == true)
			cout << "Directory 0 ";
		else
		{
			int characterSize=0;
			// number of characters in the document
			for(int j=0; j<current->children[i]->doc.size(); j++)
			{
				characterSize += current->children[i]->doc[j].length();
			}
			cout << "Document " << characterSize << " ";
		}
		cout << current->children[i]->fileName << endl;;
	}
}

//Print the first n lines of the document
void head( int n, string docName )
{
	for(int i=0; i<current->children.size(); i++)
	{
		if(current->children[i]->fileName == docName && current->children[i]->isFolder == false)
		{
			// If the document contains less than n lines, then print the whole document.
			if(current->children[i]->doc.size()<n)
			{
				for(int j=0; j<current->children[i]->doc.size(); j++)
				{
					cout << current->children[i]->doc[j] << endl;
				}
			}
			else
			{
				for(int j=0; j<n; j++)
				{
					cout << current->children[i]->doc[j] << endl;
				}
			}
			return;
		}
	}
	// If such document does not exist
	cout << "ERROR: Document " << docName << " does not exist." << endl;
}

// Print the last n lines of the document
void tail( int n, string docName )
{
	for(int i=0; i<current->children.size(); i++)
	{
		if(current->children[i]->fileName == docName && current->children[i]->isFolder == false)
		{
			if(current->children[i]->doc.size()<n)
			{
				for(int j=0; j<current->children[i]->doc.size(); j++)
				{
					cout << current->children[i]->doc[j] << endl;
				}
			}
			else
			{
				for(int j=current->children[i]->doc.size()-n; j<current->children[i]->doc.size(); j++)
				{
					cout << current->children[i]->doc[j] << endl;
				}
			}
			return;
		}
	}
	// If such document does not exist
	cout << "ERROR: Document " << docName << " does not exist." << endl;
}

// Print the total number of lines in the document
void lineCount( string docName )
{
	for(int i=0; i<current->children.size(); i++)
	{
		if(current->children[i]->fileName == docName && current->children[i]->isFolder == false)
		{
			cout << "LINECOUNT: Document " << docName << " has " << current->children[i]->doc.size() << " lines." << endl;
			return;
		}
	}
	// If such document does not exist
	cout << "ERROR: Document " << docName << " does not exist." << endl;
}

// Print unique word count in the document
void uniqueWordCountCalculation(vector<string>& ar, vector<string> s)
{
	bool exist = false;
	string word;
	for(int i =0; i<s.size(); i++)
	{
		istringstream iss(s[i]);
		while(iss >> word)
		{
			for(int j=0; j<ar.size(); j++)
			{
				if(ar[j] == word)
					exist = true;
			}
			if(!exist)
			{
				ar.push_back(word);
			}
			exist = false;
		}
	}
}

void uniqueWordCount( string docName )
{
	vector<string>word;
	for(int i=0; i<current->children.size(); i++)
	{
		if(current->children[i]->fileName == docName && current->children[i]->isFolder == false)
		{
			uniqueWordCountCalculation(word,current->children[i]->doc);
			
			cout << "WORDCOUNT: Document " << docName << " has " << word.size() << " unique words." << endl;
			return;
		}
	}
	// If such document does not exist
	cout << "ERROR: Document " << docName << " does not exist." << endl;
}

// Destructor
HedeHodoShell::~HedeHodoShell()
{
	removeRecursive(root);
} 
void HedeHodoShell::executeCommand( string command )
{
	if(root == NULL)
	{
		node *newNode = new node;
		newNode->fileName = "root";
		newNode->isFolder = true;
		newNode->parent = NULL;
		current = root = newNode;
	}
	int index = command.find(" ");
	int index2,index3;
	string s;
	string s2,s3;
	
	// determine which function is called
	if( command == "list")
	{
		list();
	}
	else if( command == "printWorkingDir")
	{
		printWorkingDir();
	}
	else
	{
		index2 = command.find(" ",index+1);
		if(index2 != -1)
		{
			s = command.substr(0,index2);
			if( s == "remove -r" )
			{
				index2 = command.find(" ",index+1);
				s2 = command.substr(index2+1);
				removeR(s2);
			}
			else
			{
				s = command.substr(0,index);
				if( s == "head" )
				{
					int n;
					index2 = command.find(" ",index+1);
					s2 = command.substr(index+1,index2-index-1); // n
					s3 = command.substr(index2+1);
					istringstream(s2) >> n;
					head(n,s3);
				}
				else if( s == "tail" )
				{
					int n;
					index2 = command.find(" ",index+1);
					s2 = command.substr(index+1,index2-index-1); // n
					s3 = command.substr(index2+1);
					istringstream(s2) >> n;
					tail(n,s3);
				}
				else
				{
					index2 = command.find("'");
					s2 = command.substr(index+1,index2-index-2); //.txt part
					index3 = command.find("'",index2+1);
					s3 = command.substr(index2+1,index3-index2-1); // line content
					appendLine(s2,s3);
				}
			}
		}
		else 
		{
			s = command.substr(0,index);
			if( s == "makeDir" )
			{
				string dirName = command.substr(index+1);
				makeDir(dirName);
			}
			else if( s == "makeDoc" )
			{
				string docName = command.substr(index+1);
				makeDoc(docName);
			}
			else if( s == "remove" )
			{
				string docName = command.substr(index+1);
				remove(docName);
			}
			else if( s == "lineCount" )
			{
				string docName = command.substr(index+1);
				lineCount(docName);
			}	
			else if( s == "changeWorkingDir" )
			{
				string dirName = command.substr(index+1);
				changeWorkingDir(dirName);
			}
			else if( s == "uniqueWordCount" )
			{
				string docName = command.substr(index+1);
				uniqueWordCount(docName);
			}
		}
	}
}
