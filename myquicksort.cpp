#include <mysortfunctions.h>
#include <sortauxfuncs.h>
#include <vector>

using namespace std;

int medianOf3Partition(int min, int max, vector<int> &v, SortStats &stats){
    stats.recursive_calls += 1;
    stats.custom1 += 1;
    if(stats.custom1 > stats.depth_recursion_stack) stats.depth_recursion_stack = stats.custom1;
    int pivot, pivotIndex;
    int mean = (min+max)/2;
    vector<int> set = {v[min], v[max], v[mean]};
    sort(set.begin(), set.end());

    if(set[1] == v[min]){
        pivot = v[min];
        pivotIndex = min;
    }
    else if(set[1] == v[max]){
        pivot = v[max];
        pivotIndex = max;
    }
    else{
        pivot = v[mean];
        pivotIndex = mean;
    }

    int aux = v[min];
    v[min] = pivot;
    v[pivotIndex] = aux;

    int l = min + 1;
    int r = max;
    while(true){
        while(l < max && v[l] < pivot) l++;
        while(r > min && v[r] >= pivot) r--;
        if (l >= r) break;
        int aux = v[l];
        v[l] = v[r];
        v[r] = aux;
    }
    v[min] = v[r];
    v[r] = pivot;
    stats.custom1 -= 1;
    return r;
}

// you only need to mantain the headers. You can create aux funcs, objects, or create a generic quicksort that can work with different functions to select the pivot.
void myquicksort_2recursion_medianOf3_intern(int min, int max, vector<int> &v, SortStats &stats){
    stats.recursive_calls += 1;
    stats.custom1 += 1;
    if(stats.custom1 > stats.depth_recursion_stack) stats.depth_recursion_stack = stats.custom1;
    if(min < max){
        int p = medianOf3Partition(min, max, v, stats);
        myquicksort_2recursion_medianOf3_intern(min, p-1, v, stats);
        myquicksort_2recursion_medianOf3_intern(p+1, max, v, stats);
    }
    stats.custom1 -= 1;
}
/// the most comon quicksort, with 2 recursive calls
void myquicksort_2recursion_medianOf3(std::vector<int> &v, SortStats &stats) {

    // you need to set the counting of recursive recursive_calls
    stats.recursive_calls = 0;
    // you need to set the depth = the maximum height of the tree of recursion calls. 
    stats.depth_recursion_stack = 0;
    // the tester already knows the size of v and the algorithm name, it already measures time
    // you may set custom1 field if you want to measure anything else.
    stats.custom1 = 0;

    myquicksort_2recursion_medianOf3_intern(0, v.size()-1, v, stats);
}// function myquicksort_2recursion_medianOf3


void myquicksort_1recursion_medianOf3_intern(int min, int max, vector<int> &v, SortStats &stats){
    stats.recursive_calls += 1;
    stats.custom1 += 1;
    if(stats.custom1 > stats.depth_recursion_stack) stats.depth_recursion_stack = stats.custom1;
    while (min < max) {
        int p = medianOf3Partition(min, max, v, stats);
        if (p-min < max-p) {
            myquicksort_1recursion_medianOf3_intern(min, p-1, v, stats);
            min = p+1;
        }
        else {
            myquicksort_1recursion_medianOf3_intern(p+1, max, v, stats);
            max = p-1;
        }
    }
    stats.custom1 -= 1;
}

/// quicksort with one recursive call
void myquicksort_1recursion_medianOf3(std::vector<int> &v, SortStats &stats) {

    // you need to set the counting of recursive recursive_calls
    stats.recursive_calls = 0;
    // you need to set the depth = the maximum height of the tree of recursion calls. 
    stats.depth_recursion_stack = 0;
    // the tester already knows the size of v and the algorithm name, it already measures time
    // you may set custom1 field if you want to measure anything else.
    stats.custom1 = 0;

    myquicksort_1recursion_medianOf3_intern(0, v.size()-1, v, stats);
} // function myquicksort_1recursion_medianOf3

int fixedPartition(int min, int max, vector<int> &v, SortStats &stats){ // 0 1
    stats.recursive_calls += 1;
    stats.custom1 += 1;
    if(stats.custom1 > stats.depth_recursion_stack) stats.depth_recursion_stack = stats.custom1;
    int pivot = v[min]; //0
    int l = min + 1; // 1
    int r = max; // 1
    while(true){
        while(l < max && v[l] < pivot) l++;
        while(r > min && v[r] >= pivot) r--;
        if (l >= r) break;
        int aux = v[l];
        v[l] = v[r];
        v[r] = aux;
    }
    v[min] = v[r];
    v[r] = pivot;
    stats.custom1 -= 1;
    return r;
}

void myquicksort_fixedPivot_intern(int min, int max, vector<int> &v, SortStats &stats){ // 0 1
    stats.recursive_calls += 1;
    stats.custom1 += 1;
    if(stats.custom1 > stats.depth_recursion_stack) stats.depth_recursion_stack = stats.custom1;
    if(min < max){
        int p = fixedPartition(min, max, v, stats);
        myquicksort_fixedPivot_intern(min, p-1, v, stats);
        myquicksort_fixedPivot_intern(p+1, max, v, stats);
    }
    stats.custom1 -= 1;
}
/// quicksort with fixed pivot 
/// be sure to compare with equivalent implementation 
/// e.g., if you do 1 recursive call, compare with the 1recursion version
void myquicksort_fixedPivot(std::vector<int> &v, SortStats &stats) {
    

    // you need to set the counting of recursive recursive_calls
    stats.recursive_calls = 0;
    // you need to set the depth = the maximum height of the tree of recursion calls. 
    stats.depth_recursion_stack = 0;
    // the tester already knows the size of v and the algorithm name, it already measures time
    // you may set custom1 field if you want to measure anything else.
    // stats.custom1 stores the current height of the three of recursion calls.
    stats.custom1 = 0;

    myquicksort_fixedPivot_intern(0, v.size()-1, v, stats);
} // myquicksort_fixedPivot


