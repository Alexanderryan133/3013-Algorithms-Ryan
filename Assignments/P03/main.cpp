/**************************************************
 * Author:      Alexander Ryan
 * Email:       alexanderryan133@gmail.com
 * Title        P03 - Processing in Trie Tree Time
 * Semester:    Spring 2022
 * Date:        3/7/2022
 *************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include "mygetch.hpp"
#include "timer.hpp"
#include "termcolor.hpp"
#define CHAR_SIZE 26  
#define RED termcolor::red


bool isUpper(char letter) {
    int l = letter;
    return (l >= 65 && l <= 90);
}

bool isLower(char letter) {
    int l = letter;
    return (l >= 97 && l <= 122);
}

bool isLetter(char letter) {
    int l = letter;
    return isUpper(l) || isLower(l);
}

bool isAlphaOnly(string word) {
    for (int i = 0; i < word.length(); i++) {
        if (!isLetter(word[i])) {
            return false;
        }
    }
    return true;
}

void makeUpper(string &word) {
    for (int i = 0; i < word.length(); i++) {
        if (isLower(word[i])) {
            word[i] -= 32;
        }
    }
}

struct TrieNode {
  bool isLeaf;
  TrieNode *character[CHAR_SIZE];
  TrieNode() {
    this->isLeaf = false;

    for (int i = 0; i < CHAR_SIZE; i++) {
      this->character[i] = nullptr;
    }
  }
};

class Trie{
  TrieNode *root;
  void findAll(TrieNode *&, string);
  vector<string> results;

public:
  bool isEndOfWord;
  Trie* character[CHAR_SIZE];

  Trie(){
    root = new TrieNode;
    }
  void insert(string);
  vector<string> findAll(string);
};

void Trie::findAll(TrieNode *&curr,string key){

    if(curr->isLeaf){
        results.push_back(key);
    }

    for (int i = 0; i < 26; i++) {
        if(curr->character[i]){
            findAll(curr->character[i],key+char(i+65));
        }
    }
}

vector<string> Trie::findAll(string key){
    makeUpper(key);
    TrieNode* curr = root;
    bool isValidKey = false;
    results.clear();

    for (int i = 0; i < key.length(); i++) {
      // go to the next node

      if(!isLetter(key[i])) // If the char is not a letter, end loop
      {
        isValidKey = false;
        i = key.length();  // stop the loop
      }
      else if(curr->character[key[i] - 65] == nullptr) // If element is nullptr, end loop
      {
        isValidKey = false;
        i = key.length();
      }
      else
      {
        curr = curr->character[key[i] - 65];
        isValidKey = true;
      }
    }

    if(isValidKey) // Finds all partial matches if the path exists in the trie
    findAll(curr,key);
  
    return results;
}

void Trie::insert(string key) {
  makeUpper(key);
  //cout<<key<<endl;

  // start from the root node
  TrieNode *curr = root;
   for (int i = 0; i < key.length(); i++) {
    // create a new node if the path doesn't exist
    if (curr->character[key[i] - 65] == nullptr) {
      curr->character[key[i] - 65] = new TrieNode();
      }

      // go to the next node
      curr = curr->character[key[i] - 65];
    }

    // mark the current node as a leaf
    curr->isLeaf = true;
};

int main() {
  string newWord; // Word to load into list
  Trie *List = new Trie(); // Initialize Trie

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
    List->insert(newWord); // push this on list
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

  	matches = List->findAll(word);
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