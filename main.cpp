// Jazveer Kaler
//  10/22/2023
//  Studentlist
//  Description: This program will display a menu of options to the user. The user will be able to add a student, delete it, and print out all students. This is accomplished through a linked list.
//

#include <cctype>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <vector>
#include "node.h"
#include "student.h"

using namespace std;

// function prototypes
void add(Node* &head, Node* current, Node* prev, Node* inputNode);
void print(Node* next);
void del(Node* &head,Node* prev, Node* current, int deleteID);
void avg(Node* head, float sumGPA, int totalNodes);

int main() {
  bool running = true;
  char command[15];
  Node* head = NULL;

    cout << "WELCOME TO LINKED LIST PART 2!" << endl;
    cout << "(Student List but different)" << endl;

  // while loop that runs the program
    // From my student list code
  while (running == true) {

    // takes in commands
    cout << "Type in a command: ADD, PRINT, DELETE, AVERAGE, or QUIT" << endl;
    cin.get(command, 16);
    cin.ignore(16, '\n');

    // ADD
    if (strcmp(command, "ADD") == 0) {
        Student* inputStudent = new Student();
         //Takes in information
         cout << "First Name: " << endl;
         char input[20];
         cin.get(input, 20);
         cin.ignore(80, '\n');
         strcpy(inputStudent->getFirstName(), input);
         
         cout << "Last Name: " << endl;
         cin.get(input, 20);
         cin.ignore(80, '\n');
         strcpy(inputStudent->getLastName(), input);
         
         cout << "Student ID: " << endl;
         int int1;
         cin >> int1;
         cin.ignore(80, '\n');
         inputStudent->setID(int1);
         
         cout << "Student GPA: " << endl;
         float float1;
         cin >> float1;
         cin.ignore(80, '\n');
         inputStudent->setGPA(float1);

         Node* inputNode = new Node(inputStudent);
         
         add(head, head, head, inputNode);
    }

    // PRINT
    else if (strcmp(command, "PRINT") == 0) {
        cout << "Printing all students: " << endl;
        print(head);
    }

    // DELETE
    else if (strcmp(command, "DELETE") == 0) {
        int ID = 0;
        cout << "Delete ID: " << endl;
        cin >> ID;
        cin.ignore(11, '\n');
        
        del(head, head, head, ID);
    }
      
    // AVERAGE
    else if (strcmp(command, "AVERAGE") == 0) {
        float sumGPA = 0;
        int totalNodes;
        avg(head, sumGPA, totalNodes);
    }

    // QUIT
    else if (strcmp(command, "QUIT") == 0) {
      cout << "Program ended." << endl;
      running = false;
    }
  }
  return 0;
}

// Every single function has an if statement to see if the list is completely empty

// Not working half the time?
//anytime more than one student
void add(Node* &head, Node* current, Node* prev, Node* inputNode) {
  if (head == NULL) {
    head = inputNode;
  }

  else {
    if (inputNode->getStudent()->getID() < head->getStudent()->getID()) {
      Node* tempNode = head;
      head = inputNode;
      head->setNext(tempNode); // Keeps crashing, need to fix
    }
    else if (inputNode->getStudent()->getID() < current->getStudent()->getID()) {
      prev->setNext(inputNode);
      inputNode->setNext(current);
    }
      //Adds to the end of list
    else if (current->getNext() == NULL) {
      current->setNext(inputNode);
    }
      //recursion
    else {
      add(head, current->getNext(), current, inputNode);
    }
    //return;
  }
  //return;
}

//Credit to Levi for helping me
void del(Node* &head, Node* prev, Node* current, int deleteID) {
    // Case 1
      if (head == NULL) {
        cout << "List is empty!" << endl;
      }
    
      // Can't find student with the delete ID
      else if (current == NULL)
        cout << "This student does not exist in the Linked List!" << endl;
    
      // Inputted ID matches with a node
      else if (current->getStudent()->getID() == deleteID) {

        if (current == head) {
          Node* tempNode = head->getNext();
          head->~Node();
          head = tempNode;
        }
          
        else if (current != head && current->getNext() != NULL) {
          prev->setNext(current->getNext());
          current->~Node();
        }
          
        else if (current != head && current->getNext() == NULL) {
          prev->setNext(NULL);
          current->~Node();
        }
          
          cout << "Student has been deleted!" << endl;
          
      }
      // Iteration
      else {
        del(head, current->getNext(), current, deleteID);
      }
}

void avg(Node* head, float sumGPA, int totalNodes) {
  // Case 1
    if (head == NULL && totalNodes == 0) {
    cout << "No students" << endl;
  }
    
    
  else if (head != NULL) {
    sumGPA += head->getStudent()->getGPA();
    totalNodes++;
    avg(head->getNext(), sumGPA, totalNodes);
  }
  // Average GPA:
  else {
    cout << "Average GPA: ";
    cout << fixed << setprecision(2) << sumGPA / (totalNodes - 1) << endl;
  }
}

// print
void print(Node* next) {
    // Empty list
  if (next == NULL) {
    cout << "List is empty!" << endl;
  }
    
    // 0 students
    else if (next != NULL && next->getNext() == NULL) {
      next->getStudent()->print();
    }
    
    //more than one student
  if (next != NULL) {
    next->getStudent()->print();
    print(next->getNext());
  }
}
