#include <mysortfunctions.h>
#include <sortauxfuncs.h>
#include <vector>
#include <algorithm>

void merge(int initial, int mean, int final, std::vector<int> &v, std::vector<int> &aux, SortStats &stats) {
    stats.recursive_calls += 1;
    stats.custom1 += 1;
    if(stats.custom1 > stats.depth_recursion_stack) stats.depth_recursion_stack = stats.custom1;
    int i1 = initial;
    int i2 = initial;
    int i3 = mean+1;
    while (i2 <= mean && i3 <= final){
        if (v[i2] < v[i3]) aux[i1++] = v[i2++];
        else aux[i1++] = v[i3++];
    }
    while (i2 <= mean) aux[i1++] = v[i2++];
    while (i3 <= final) aux[i1++] = v[i3++];
    for (int j=initial; j<= final ; j++) v[j] = aux[j];
    stats.custom1 -= 1;
}
void merge_iterative(int initial, int mean, int final, std::vector<int> &v, std::vector<int> &aux, SortStats &stats) {
    int i1 = initial;
    int i2 = initial;
    int i3 = mean+1;
    while (i2 <= mean && i3 <= final){
        if (v[i2] < v[i3]) aux[i1++] = v[i2++];
        else aux[i1++] = v[i3++];
    }
    while (i2 <= mean) aux[i1++] = v[i2++];
    while (i3 <= final) aux[i1++] = v[i3++];
    for (int j=initial; j<= final ; j++) v[j] = aux[j];
}

void mergeSort_recursive_intern(int initial, int final, std::vector<int> &v, std::vector<int> &aux, SortStats &stats) {
    stats.recursive_calls += 1;
    stats.custom1 += 1;
    if(stats.custom1 > stats.depth_recursion_stack) stats.depth_recursion_stack = stats.custom1;
    if (initial < final) {
        int mean = (initial+final)/2;
        mergeSort_recursive_intern(initial, mean, v, aux, stats);
        mergeSort_recursive_intern(mean+1, final, v, aux, stats);
        merge(initial, mean, final, v, aux, stats);
    }
    stats.custom1 -= 1;
}

void mymergesort_recursive(std::vector<int> &v, SortStats& stats) {

    std::vector<int> aux(v.size());
    // you need to set the counting of recursive recursive_calls
    stats.recursive_calls = 0;
    // you need to set the depth = the maximum height of the tree of recursion calls. 
    stats.depth_recursion_stack = 0;
    // the tester already knows the size of v and the algorithm name, it already measures time
    // you may set custom1 field if you want to measure anything else.
    stats.custom1 = 0;
    mergeSort_recursive_intern(0, v.size() - 1, v, aux, stats);
}

void mergeSort_iterativa_intern(int initial, int final, std::vector<int> &v, std::vector<int> &aux, SortStats &stats) {
    int blockSize = 1;
    while (blockSize < final) {
        int begginingFirstBlock = initial;
        while (begginingFirstBlock+blockSize <= final) {
            int finalSecondBlock = final < begginingFirstBlock-1+2*blockSize ? final : begginingFirstBlock-1+2*blockSize;
            int finalFirstBlock = begginingFirstBlock+blockSize-1;
            merge_iterative(begginingFirstBlock, finalFirstBlock, finalSecondBlock, v, aux, stats);
            begginingFirstBlock += 2*blockSize;
        }
        blockSize *= 2; // tamanho dos blocos é duplicado
    }
}

void mymergesort_iterative(std::vector<int> &v, SortStats &stats) {
    
    std::vector<int> aux(v.size());
    // you need to set the counting of recursive recursive_calls
    stats.recursive_calls = 0;
    // you need to set the depth = the maximum height of the tree of recursion calls. 
    stats.depth_recursion_stack = 0;
    // the tester already knows the size of v and the algorithm name, it already measures time
    // you may set custom1 field if you want to measure anything else.
    stats.custom1 = 0;

    mergeSort_iterativa_intern(0, v.size()-1, v, aux, stats);
}