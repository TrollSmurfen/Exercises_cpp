#include<iostream>
using namespace std;

int main () {

int var = 22; // Initialisation
int* ptr; // Declaration of a pointer
ptr = &var;

int value = *ptr; //Derefering

cout << "Value of var: " << var << endl;
cout << "Adress stored in ptr: " << ptr << endl;
cout << "Value pointed to by ptr: " << *ptr << endl;

    return 0;

}
