///////////////////////////////////////////////////////////////////////////////
//
// Author:           Alexander Ryan
// Email:            alexanderryan133@gmail.com
// Label:            P02
// Title:            Program 02 - Processing in Linear Time
// Course:           3013
// Semester:         Spring 2022
//
// Description:
//       Overview of a class implementing an array based stack
//
//
/////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include "mygetch.hpp"
#include "timer.hpp"
#include "termcolor.hpp"

#define RED termcolor::red

struct wordNode
{
  string word;
  wordNode *next;

  wordNode(string x)
  {
    word = x;
    next = nullptr;
  }
};

class wordList
{
  public:
	wordNode* tail;
	wordNode* head;
	int size;

	wordList()
	{
		head = tail = nullptr;
	}

	void push(string x)
	{
		wordNode* temp = new wordNode(x);
		if(head == nullptr) 
		{
			head = tail = temp;
		}
		else
		{
			tail->next = temp;
			tail = temp;
		}
		size++;
  }

  void print() 
  {
    wordNode* temp = head; 
    while(temp) 
	{
      cout << temp->word;

      if(temp->next) 
	  {
        cout << ", ";
      }
      temp = temp->next;
    }
      cout << endl;
  }
};

vector<string> FindWord(wordList list, string substring) 
{
    vector<string> matches; // to hold any matches
    size_t found;           // size_t is an integer position of
                            // found item. -1 if its not found.
    wordNode* temp = list.head;
    
    while (temp->next) // loop through array
		{ 
        found = temp->word.find(substring);    // check for substr match
        if (found == 0) 
				{         // if found >= 0 (its found then)
            matches.push_back(temp->word);     // add to matches
        }
			 temp = temp->next; // traverseres list
    }
    return matches;
}

int main() {
  string newWord; // Word to load into list
  wordList list; // word list

  char k; // current char
  string word = ""; // current substring
  vector<string> matches; // words that match
  int loc;

  ifstream fin; // infile variable
  fin.open("dictionary.txt"); // open dictionary file

  Timer T; // Timer variable 
  T.Start(); // Start timer

  while(fin >> newWord) //while you can still load things
  {
    list.push(newWord); // push this on list
  }

  T.End(); // end timer

  cout << "Loading complete\n\n";

  // Starts new timer
  Timer newTimer;

  while ((k = getch()) != 'Z') 
  {

    newTimer.Start(); // start new timer from 0

    // Tests for a backspace and if pressed deletes
    // last letter from "word".
    if ((int)k == 8) 
		{
      if (word.size() > 0) 
	  	{
        word = word.substr(0, word.size() - 1);
      }
    } 
		else 
		{
      // Make sure a letter was pressed and only letter
      if (!isalpha(k)) 
			{
        cout << "Letters only!" << endl;
        continue;
      }

      // We know its a letter, lets make sure its lowercase.
      // Any letter with ascii value < 97 is capital so we
      // lower it.
      if ((int)k < 97) 
			{
          k += 32;
      }
      word += k; // append char to word
    }

  	matches = FindWord(list, word);
		cout << "found words" << endl;
   	newTimer.End();

    if ((int)k != 32) // if k is not a space print it
		{ 
      //cout << T.NanoSeconds() << " nano" << endl;
      cout << "Keypressed: " << termcolor::blue << k << " = " << (int)k << termcolor::reset << std::endl;
      cout << "Current Substr: " << termcolor::red << word << termcolor::reset << endl;
      cout << "Words Found: ";
      cout << termcolor::green;
      // This prints out all found matches

			int loopSize;
			matches.size() > 10 ? loopSize = 10 : loopSize = matches.size();

      for (int i = 0; i < loopSize; i++) {
        // find the substring in the word
        cout << matches[i] << " ";
        }
            cout << termcolor::reset << endl
                 << endl;
        }
    }
    return 0;
}