/*
ADA. 2025-26
Práctica 1.
*/

#include <unistd.h>
#include <iostream>
#include <math.h>

using namespace std;

//--------------------------------------------------------------
// Bubble sort basic algorithm

void bubbleSort(int * v, size_t size){

    for (size_t i = 1; i < size; i++)
        for (size_t j = 0; j < size - i; j++)
            if (v[j]>v[j+1]){ /*swap*/
                int aux = v[j]; 
                v[j] = v[j+1]; 
                v[j+1] = aux;
            }
}  
//--------------------------------------------------------------                


int main(void){

    srand(0);

    cout << "# BubbleSort CPU times in milliseconds:"
        << endl
        << "# Size \t CPU time (ms.)"
        << endl
        << "# ----------------------------"
        << endl;

    for (int exp = 10; exp <= 16; exp++){
        size_t size = size_t( pow(2,exp) );
        int* v = new int [size];
        if (!v){
            cerr << "Error, not enough memory!" << endl;
            exit (EXIT_FAILURE);  
        }

        cout << size << "\t\t" << std::flush;

        for (size_t j = 0; j < size; j++) 
            v[j] = rand(); 

        auto start = clock();
        bubbleSort(v,size);
        auto end = clock();


        cout << 1000.0 * (end-start) / CLOCKS_PER_SEC  << endl;

        for (size_t i = 1; i < size; i++)
            if (v[i] < v[i-1]){ 
                cerr << "Panic, array not sorted! " << i << endl; 
                exit(EXIT_FAILURE);            
            }

        delete[] v; 
    }
}


