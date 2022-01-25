
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
  int *A;           // pointer to array of int's
  int size;         // current max stack size
  int top;          // top of stack 
  float tooFullThresh;
  float tooEmptThresh;
  float enlargeThresh;
  float shrinkThresh;

public:
 /**
  * ArrayStack
  * 
  * Description:
  *      Constructor no params
  * 
  * Params:
  *     - None
  * 
  * Returns:
  *     - NULL
  */
  ArrayStack(){
    size = 10;
    A = new int[size];
    top = -1;
    tooFullThresh = 1;
    tooEmptThresh = .15;
    enlargeThresh = 2;
    shrinkThresh = .5;
  }

 /**
  * ArrayStack
  * 
  * Description:
  *      Constructor size param
  * 
  * Params:
  *     - int size
  * 
  * Returns:
  *     - NULL
  */
  ArrayStack(int s){
    size = s;
    A = new int[s];
    top = -1;
  }

   /**
  * ArrayStack
  * 
  * Description:
  *      Constructor 4 params for toofull tooEmpty enlarge and shrink
  * 
  * Params:
  *     - int size
  * 
  * Returns:
  *     - NULL
  */
  ArrayStack(float tooFull, float tooEmpty, float enlarge, float shrink){
    size = 10;
    A = new int[size];
    top = -1;
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
  * Public int: Peek
  * 
  * Description:
  *      Returns top value without altering the stack
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      [int] top value if any
  */
  int Peek(){
    if(!Empty()){
      return A[top];
    }
    
    return -99; // some sentinel value
                // not a good solution
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
  int Pop(){
    if(!Empty()){
      return A[top--];
    }

    return -99; // some sentinel value
                // not a good solution
  }

 /**
  * Public void: Print
  * 
  * Description:
  *      Prints stack to standard out
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      NULL
  */
  void Print(){
    for(int i=0;i<=top;i++){
      cout<<A[i]<<" ";
    }
    cout<<endl;
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
    if(Full()){
      containerGrow();
    }
    if(!Full()){
      if(findPercent() >= getTooFullThresh()){
      A[++top] = x;
      }
    }
  }

 /**
  * Public void: Resize
  * 
  * Description:
  *      Resizes the container for the stack by doubling
  *      its capacity
  * 
  * Params:
  *      NULL
  * 
  * Returns:
  *      NULL
  */
  void containerGrow(){
    int newSize = size*2;       // double size of original
    int *B = new int[newSize];  // allocate new memory

    for(int i=0;i<top;i++){    // copy values to new array
      B[i] = A[i];
    }

    delete [] A;                // delete old array

    size = newSize;             // save new size

    A = B;                      // reset array pointer

  }

  void containerShrink(){
    int newSize = size/2;
    if(newSize < 10){
      newSize = 10;
    }
    int *B = new int[newSize];

    for(int i=0; i < newSize; i++){
      B[i] = A[i];
    }

    delete [] A;

    size = newSize;

    A = B;
  }

  int findPercent () {
    float percent = (top / size);
  }

  void checkResize(){

  }

  /**
   *
   * Getters
   *  
   */
  float getTooFullThresh(){
    return tooFullThresh;
  }
  float getTooEmptThresh(){
    return tooEmptThresh;
  }
  float getEnlargeThresh(){
    return enlargeThresh;
  }
  float getShrinkThresh(){
    return shrinkThresh;
  }

  /**
   *
   * Setters
   *  
   */
  void setTooFullThresh(float x){
    tooFullThresh = x;
  }
  void setTooEmptThresh(float x){
    tooEmptThresh = x;
  }
  void setEnlargeThresh(float x){
    enlargeThresh = x;
  }
  void setShrinkThresh(float x){
    shrinkThresh = x;
  }

};



// MAIN DRIVER
// Simple Array Based Stack Usage:
int main(int argc, char **argv) {
  int x;
  float first, second, third, fourth;
  string filename;
    cout << "Enter 0 for default threshold, or enter 5 params\n";
    cout << "filename toofull tooempty enlarge shrink";
    ArrayStack stack;
    //cin >> first;
    // if(first = 0) {
    //   ArrayStack stack;
        
    // }
    // else{
    //   cin >> second >> third >> fourth;
    //   ArrayStack stack(first, second, third, fourth);
    // }

    ifstream fin;
    fin.open("nums_test.dat");
    while(!fin.eof()){
      fin >> x;
      if(x%2 == 0) {
        stack.push(x);
      }
    }
//   ArrayStack stack;
//   int r = 0;

//   for(int i=0;i<20;i++){
//     r = rand() % 100;
//     r = i+1;
//     if(!stack.Push(r)){
//       cout<<"Push failed"<<endl;
//     }
//   }

//   for(int i=0;i<7;i++){
//     stack.Pop();
//   }

//   stack.Print();
}