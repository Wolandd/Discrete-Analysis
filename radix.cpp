#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

void countingSortBits(std::vector <unsigned int>& A, int shift, unsigned int r) {
    unsigned int base = 1u << r; //1 digit | ..0000100000000 | 2^r num
    int mask = base - 1; // 000...011111111 | 2^r-1

    int n = A.size();
    int digit;
    std::vector <int> count(base, 0);
    std::vector <unsigned int> B(n);

    for (int i = 0; i < n; i++) {
        digit = (A[i] >> shift) & mask;
        count[digit]++;
    }

    for (int i = 1; i < base; i++) {
        count[i] += count[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        digit = (A[i] >> shift) & mask;
        B[count[digit] - 1] = A[i];
        count[digit]--;
    }
    A = B;
}

void radixSortBits(std::vector <unsigned int>& A) {
    unsigned int b = sizeof(unsigned int) * 8; // total bits
    unsigned int r = std::max(b, (unsigned int)log2(A.size())); // one digit size

    for (int shift = 0; shift < b; shift += r) {
        countingSortBits(A, shift, r);
    }
}

int main()
{
    
}

