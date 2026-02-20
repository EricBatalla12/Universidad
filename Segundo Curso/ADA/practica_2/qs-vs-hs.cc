/*

ADA. 2025-26
Practice 2: "Empirical analysis by means of program-steps account of two sorting algorithms: Middle-Quicksort and Heapsort."
*/
#include <unistd.h>
#include <iostream>
#include <math.h>

using namespace std;

//--------------------------------------------------------------
// Middle-Quicksort:
// The algorithm selects the middle element of the array as the "pivot".
// In a process called "partitioning", it rearranges the elements so that
// all elements smaller than the pivot are placed to its left, and
// all elements greater than the pivot are placed to its right.
// The process is then repeated recursively on the two resulting
// subarrays (left and right of the pivot).
//--------------------------------------------------------------

double middle_QuickSort(int *v, long left, long right) {
    long i, j;
    int pivot;
    int steps = 0;
    if (left < right) {
        i = left; j = right;
        pivot = v[(i + j) / 2];
        // pivot based partitioning:
        do {
            steps++;
            while (v[i] < pivot) {steps++; i++;}
            while (v[j] > pivot) {steps++; j--;}
            steps++;
            if (i <= j) {
                swap(v[i], v[j]);
                i++; j--;
            }
        } while (i <= j);
        // Repeat for each non-empty subarray:
        if (left < j) steps = steps + middle_QuickSort(v, left, j);
        if (i < right) steps = steps + middle_QuickSort(v, i, right);
    }
    return steps;
}

//--------------------------------------------------------------
// Heapsort:
// The algorithm works by repeatedly selecting the largest remaining element
// and placing it at the end of the vector in its correct position.
//
// To efficiently select the largest element, it builds a max-heap.
//
// The sink procedure is used for heap construction (or reconstruction).
//--------------------------------------------------------------

double sink(int *v, size_t n, size_t i)
// Sink an element (indexed by i) in a tree to maintain the heap property.
// n is the size of the heap.
{   
    double steps = 0;
    size_t largest;
    size_t l, r; // indices of left and right childs

    do {
        steps++;
        largest = i;  // Initialize largest as root
        l = 2 * i + 1;  // left = 2*i + 1
        r = 2 * i + 2;  // right = 2*i + 2

        // If the left child exists and is larger than the root
        if (l < n && v[l] > v[largest])
            largest = l;

        // If the right child exists and is larger than the largest so far
        if (r < n && v[r] > v[largest])
            largest = r;

        // If the largest is still the root, the process is done
        if (largest == i) break;

        // Otherwise, swap the new largest with the current node i and repeat the process with the children
        swap(v[i], v[largest]);
        i = largest;
    } while (true);
    return steps;
}

//--------------------------------------------------------------
// Heapsort algorithm (ascending sorting)
double heapSort(int *v, size_t n)
{
    double steps = 0;
    // Build a max-heap with the input array ("heapify"):
    // Starting from the last non-leaf node (right to left), sink each element to construct the heap.
    for (size_t i = n / 2 - 1; true; i--) {
        steps++;
        steps = sink(v, n, i) + steps;
        if (i == 0) break; // As size_t is an unsigned type
    }

    // At this point, we have a max-heap. Now, sort the array:
    // Repeatedly swap the root (largest element) with the last element and rebuild the heap.
    for (size_t i = n - 1; i > 0; i--) {
        steps++;
        // Move the root (largest element) to the end by swapping it with the last element.
        swap(v[0], v[i]);
        // Rebuild the heap by sinking the new root element.
        // Note that the heap size is reduced by one in each iteration (so the element moved to the end stays there)
        steps = steps + sink(v, i, 0);
        // The process ends when the heap has only one element, which is the smallest and remains at the beginning of the array.
    }
    return steps;
}

int main()
{
cout << "# QUICKSORT VERSUS HEAPSORT." << endl;
cout << "# Average processing Msteps (millions of program steps)" << endl;
cout << "# Number of samples (arrays of integer): 30" << endl;
cout << "# \tRANDOM ARRAYS\t\tSORTED ARRAYS \tREVERSE SORTED ARRAYS" << endl;
cout << "# \t------------------- ------------------- ---------------------" << endl;
cout << " Size   QuickSort  HeapSort QuickSort HeapSort  QuickSort  HeapSort" << endl;
cout << "#============================================================================" << endl;

     

    for (int exp = 15; exp <= 20; exp++){
        size_t size = size_t( pow(2,exp) );
        int* vquick = new int [size];
        int* vheap = new int [size];

        if (!vquick || !vheap){
            cerr << "Error, not enough memory!" << endl;
            exit (EXIT_FAILURE);  
        }

        cout << size << "\t" << std::flush;

   //Declaración steps reiniciadas por cada exponente añadido
        double steps_rand_quick = 0;
        double steps_rand_heap = 0;

        double steps_sorted_quick = 0;
        double steps_sorted_heap = 0;

        double steps_reverse_quick = 0;
        double steps_reverse_heap = 0;

        //Para hacer las 30 muestras y su media solo de los random, ya que los otros dos casos son los mismos vectores
        for (int k = 0; k < 30; k++){
         for (size_t j = 0; j < size; j++){
            vquick[j] = rand(); 
            vheap[j] = vquick[j];
         }
        //Cálculo de los steps
        steps_rand_quick = middle_QuickSort(vquick,0,size - 1) + steps_rand_quick;
        steps_rand_heap = heapSort(vheap,size) + steps_rand_heap;

        }

         for (size_t j = 0; j < size; j++){
            vquick[j] = j; 
            vheap[j] = j;
         }

        steps_sorted_quick = middle_QuickSort(vquick,0,size - 1) + steps_sorted_quick;
        steps_sorted_heap = heapSort(vheap,size) + steps_sorted_heap;

          for (size_t j = 0; j < size; j++){
            vquick[j] = size - j; 
            vheap[j] = size - j;
         }

        steps_reverse_quick = middle_QuickSort(vquick,0,size - 1) + steps_reverse_quick;
        steps_reverse_heap = heapSort(vheap,size) + steps_reverse_heap;

        steps_rand_quick = steps_rand_quick / 30; //Media de steps para ordenar un vector random con quicksort
        steps_rand_heap = steps_rand_heap / 30; //Media de steps para ordenar un vector random con quicksort

        //Imprimir por pantalla los millones de pasos
        cout << steps_rand_quick/1000000 << "  ";
        cout << steps_rand_heap/1000000  << "  ";

        cout << steps_sorted_quick/1000000 << "   ";
        cout << steps_sorted_heap/1000000  << "   ";

        cout << steps_reverse_quick/1000000 << "   ";
        cout << steps_reverse_heap/1000000  <<endl;

        delete[] vquick;
        delete[] vheap;
    }

    
}
