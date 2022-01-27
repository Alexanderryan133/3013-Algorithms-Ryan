
///////////////////////////////////////////////////////////////////////////////
//
// Author:           Alexander Ryan
// Email:            alexanderryan133@gmail.com
// Label:            P01
// Title:            Program 01 - Resizing the Stack
// Course:           3013
// Semester:         Spring 2022
//
// Description:
//       Overview of a class implementing an array based stack
//
//
/////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/**
 * ArrayStack
 * 
 * Description:
 *      Array based stack
 * 
 * Public Methods:
 *      - See class below
 * 
 * Usage: 
 *      - See main program
 *      
 */
class ArrayStack{
private:
  int *A;                 // pointer to array of int's
  int size, top;          // current size of the stack and the top of the stack    
  double tooFullThresh;   // Threshold where the stack is too full
  double tooEmptThresh;   // Threshold where the stack is too empty  
  double enlargeThresh;   // The ratio that the stack grows by
  double shrinkThresh;    // The ratio that the stack shrinks by

public:
  int resize, counter, maxSize;  
 /**
  * ArrayStack
  * 
  * Description:
  *      Default constructor no params
  * 
  * Params:
  *     - None
  * 
  * Returns:
  *     - NULL
  */
  ArrayStack(){
    size = 10;
    resize = 0;
    A = new int[size];
    top = -1;
    maxSize = 0;
    tooFullThresh = 1;
    tooEmptThresh = .15;
    enlargeThresh = 2;
    shrinkThresh = .5;
  }

   /**
  * ArrayStack
  * 
  * Description:
  *      Constructor 4 params for toofull tooEmpty enlarge and shrink
  * 
  * Params:
  *     - double tooFull - The percent at which the stack will grow
  *     - double tooEmpty - The percent (In decimal form) that the stack will shrink
  *     - double enlarge - The ratio that the stack will grow by
  *     - double shrink - The ration that the stack will shrink by
  * 
  * Returns:
  *     - NULL
  */
  ArrayStack(double tooFull, double tooEmpty, double enlarge, double shrink){
    size = 10;
    resize = 0;
    A = new int[size];
    top = -1;
    maxSize = 0;
    tooFullThresh = tooFull;
    tooEmptThresh = tooEmpty;
    enlargeThresh = enlarge;
    shrinkThresh = shrink;
  }

 /**
  * Public bool: Empty
  * 
  * Description:
  *      Stack empty?
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      [bool] true = empty
  */
  bool Empty(){
    return (top <= -1);
  }
  
 /**
  * Public bool: Full
  * 
  * Description:
  *      Stack full?
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      [bool] true = full
  */
  bool Full(){
    return (top >= size-1);
  }

 /**
  * Public int: Pop
  * 
  * Description:
  *      Returns top value and removes it from stack
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      [int] top value if any
  */
  void pop(){
    if(findPercent() < getShrinkThresh()){
      containerShrink();
    }
    if(!Empty()){
      top--;
      }else{
      cout<<"Empty!!"<<endl;
      }
  }

 /**
  * Public bool: Push
  * 
  * Description:
  *      Adds an item to top of stack
  * 
  * Params:
  *      [int] : item to be added
  * 
  * Returns:
  *      [bool] ; success = true
  */
  void push(int x){
    if(findPercent() >= getTooFullThresh()){
      containerGrow();
    }
    
    A[++top] = x;
  }

 /**
  * Public void: containerGrow
  * 
  * Description:
  *      Resizes the container for the stack by enlargeThresh
  *      
  * Params:
  *      NULL
  * 
  * Returns:
  *      NULL
  */
  void containerGrow(){
    int newSize = size*enlargeThresh;       // double size of original
    int *B = new int[newSize];  // allocate new memory

    for(int i=0;i<top;i++){    // copy values to new array
      B[i] = A[i];
    }

    delete [] A;                // delete old array

    size = newSize;             // save new size
    if(size > maxSize) {
      maxSize = size;
    }
    A = B;                      // reset array pointer
    resize++;
  }

 /**
  * Public void: containerShrink
  * 
  * Description:
  *      Resizes the container for the stack by the shrinkThresh
  *      its capacity
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      NULL
  */

  void containerShrink(){

    if(size <= 10){                 //Maintains the stack is always size 10
      return;
    }
    int newSize = (double)size*(double)shrinkThresh;   //determine the new size

    int *B = new int[newSize];

    for(int i=0; i < newSize; i++){
      B[i] = A[i];
    }

    delete [] A;

    size = newSize;

    A = B;
    resize++;
  }

  double findPercent () {     //Returns a decimal value based percent of 
                              //how much of the stack is used
    double percent = ((double) top+1)  / (double) size;
    return percent;
  }

  void showStats() {  //Prints all important information to the console.
    cout << "###############################################\n";
    cout << "Program 1 - Resizing the Stack\n";
    cout << "CMPS 3013\n";
    cout << "Alexander Ryan\n\n";

    cout << "Config Params: \n";
    cout << "   Full Threshold: " << tooFullThresh << endl;
    cout << "   Shrink Threshold: " << tooEmptThresh << endl;
    cout << "   Grow Ratio: " << enlargeThresh << endl;
    cout << "   Shrink Ratio: " << shrinkThresh << endl;

    cout << "\nProcessed " << counter << " commands.\n\n";

    cout << "Max Stack Size: " << maxSize << endl;
    cout << "End Stack Size: " << size << endl;
    cout << "Stack Resized: " << resize << " times \n\n";

    cout << "###############################################\n";
  }

  /**
   *
   * Getters
   *  
   */
  double getTooFullThresh(){
    return tooFullThresh;
  }
  double getTooEmptThresh(){
    return tooEmptThresh;
  }
  double getEnlargeThresh(){
    return enlargeThresh;
  }
  double getShrinkThresh(){
    return shrinkThresh;
  }

  /**
   *
   * Setters
   *  
   */
  void setTooFullThresh(double x){
    tooFullThresh = x;
  }
  void setTooEmptThresh(double x){
    tooEmptThresh = x;
  }
  void setEnlargeThresh(double x){
    enlargeThresh = x;
  }
  void setShrinkThresh(double x){
    shrinkThresh = x;
  }

};



// MAIN DRIVER
// Simple Array Based Stack Usage:
int main(int argc, char **argv) {
  int x;
  //float first, second, third, fourth;
  string filename;
  ArrayStack *stack;
    // cout << "Enter 0 for default threshold, or enter 5 params\n";
    // cout << "filename toofull tooempty enlarge shrink" << endl;
    //stack->setEnlargeThresh(stof(argv[2]));
  if(argc == 1) {
      cout<<"argc == 1"<<endl;
      stack = new ArrayStack();
      filename = "nums_test.dat";
    }else{
      cout <<"overloaded" << endl;
      filename = argv[1];
      stack = new ArrayStack(stof(argv[2]), stof(argv[3]), stof(argv[4]), stof(argv[5]));
    }

    ifstream fin;
    fin.open(filename);
    while(!fin.eof()){
      fin >> x;
      if(x%2 == 0) {
        stack->push(x);
      }else{
        stack->pop();
      }
      stack->counter++;
    }

    stack->showStats();
}