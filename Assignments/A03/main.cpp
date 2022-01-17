/**
 *  Author:     Alexander Ryan 
 *  Email:      Alexanderryan133@gmail.com
 *  Label:      A03
 *  Title:      Commenting Code
 *  Course:     3013
 *  Semester:   Spring 2022
*/
#include <iostream>

using namespace std;

int A[100];             //Creates array A of size 100

/**
 *  Node
 * 
 *  Description:
 *  creates a node for a linked list
 * 
 *  Public Methods:
 *      -Default Constructor creates a node with the x value -1
 *      -Overloaded Constructor creates a node with the parameter for the x value
*/
struct Node {
    int x;              //Number stored in the node
    Node *next;         //A pointer to the next node in the list
    Node() {            //Default Constructor
        x = -1;         //Setting the x value equal to -1
        next = NULL;    //Settting the address of the next value to NULL
    }                   //since this would be the last node in the list
    Node(int n) {       //Overloaded Constructor
        x = n;          //Setting x equal to the parameter n
        next = NULL;    //Settting the address of the next value to NULL
    }                   //since this would be the last node in the list       
};

/**
 *  List
 * 
 *  Description:
 *  uses the Node struct from above to create a linked list
 * 
 *  Public Methods:
 *      -Default Constructor sets size to 0 and initailizes head & tail to NULL
 *      -Push(int val); pushes the value val onto the linked list
 *      -Insert(int val)
 *      -PrintTail(); prints the last value in the list
 *      -Print(); prints every value in the list
 *      -Pop(); NOT IMPLEMENTED DO NOT USE
*/
class List {
private:
    Node *Head;
    Node *Tail;
    int Size;

public:
    List() {                            //Default Constructor
        Head = Tail = NULL;             //Initialize head and tail to NULL
        Size = 0;                       //Initialize Size to 0
    }

    void Push(int val) {                //Pushes val onto the end of the list
        // allocate new memory and init node
        Node *Temp = new Node(val);

        if (!Head && !Tail) {
            Head = Tail = Temp;
        } else {
            Tail->next = Temp;
            Tail = Temp;
        }
        Size++;
    }

    void Insert(int val) {
        // allocate new memory and init node
        Node *Temp = new Node(val);

        // figure out where it goes in the list

        Temp->next = Head;
        Head = Temp;
        if (!Tail) {
            Tail = Head;
        }
        Size++;
    }

    void PrintTail() {
        cout << Tail->x << endl;
    }

    string Print() {
        Node *Temp = Head;
        string list;

        while (Temp != NULL) {
            list += to_string(Temp->x) + "->";
            Temp = Temp->next;
        }

        return list;
    }

    // not implemented
    int Pop() {
        Size--;
        return 0; //
    }

    List operator+(const List &Rhs) {
        // Create a new list that will contain both when done
        List NewList;

        // Get a reference to beginning of local list
        Node *Temp = Head;

        // Loop through local list and Push values onto new list
        while (Temp != NULL) {
            NewList.Push(Temp->x);
            Temp = Temp->next;
        }

        // Get a reference to head of Rhs
        Temp = Rhs.Head;

        // Same as above, loop and push
        while (Temp != NULL) {
            NewList.Push(Temp->x);
            Temp = Temp->next;
        }

        // Return new concatenated version of lists
        return NewList;
    }

    // Implementation of [] operator.  This function returns an
    // int value as if the list were an array.
    int operator[](int index) {
        Node *Temp = Head;

        if (index >= Size) {
            cout << "Index out of bounds, exiting";
            exit(0);
        } else {

            for (int i = 0; i < index; i++) {
                Temp = Temp->next;
            }
            return Temp->x;
        }
    }

    friend ostream &operator<<(ostream &os, List L) {
        os << L.Print();
        return os;
    }
};

int main(int argc, char **argv) {
    List L1;
    List L2;

    for (int i = 0; i < 25; i++) {
        L1.Push(i);
    }

    for (int i = 50; i < 100; i++) {
        L2.Push(i);
    }

    //cout << L1 << endl;
    L1.PrintTail();
    L2.PrintTail();

    List L3 = L1 + L2;
    cout << L3 << endl;

    cout << L3[5] << endl;
    return 0;
}