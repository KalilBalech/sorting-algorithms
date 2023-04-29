#include <mysortfunctions.h>
#include <cmath>
#include <queue>

void myradixsort(std::vector<int> &v, SortStats &stats) {
    // you need to set the counting of recursive recursive_calls
    stats.recursive_calls = 0;
    // you need to set the depth = the maximum height of the tree of recursion calls. 
    stats.depth_recursion_stack = 0;
    // the tester already knows the size of v and the algorithm name, it already measures time
    // you may set custom1 field if you want to measure anything else.
    stats.custom1 = 0;
    
    if(v.empty()) return;

    int factor, i, j, k;
    int n = v.size();
    int base = 10;
    int bigger = n;
    std::vector<std::queue<int>> digits(10);

    int d = log10(bigger) + 1;

    for (i=0, factor=1; i<d; factor *= base, i++) {
        for (j=0; j<n; j++) digits[(v[j]/factor)%base].push(v[j]);
        for (j=0, k=0; j<base; j++)
            while (!digits[j].empty()) {
                v[k++] = digits[j].front();
                digits[j].pop();
            }
    }
}