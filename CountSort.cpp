#include <iostream>
#include <vector> 
//Counting Sort for not negative

std::vector <int> countingSort(const std::vector <int>& A, int k) {
    std::vector <int> P(k+1, 0);
    int n = A.size();
    for (int i = 0; i < n; i++) {
        P[A[i]]++;
    }

    std::vector <int> Ps(k + 1, 0);
    Ps[0] = P[0];
    for (int i = 1; i < k + 1; i++) {
        Ps[i] = Ps[i - 1] + P[i];
    }

    std::vector <int> B(n);
    for (int i = n - 1; i >= 0; i--) {
        B[Ps[A[i]] - 1] = A[i]; 
        Ps[A[i]]--;
    }
    return B;
}

int main()
{
    std::vector <int> A = { 324, 52, 235, 546, 52, 7865,321, 8756, 58, 321 };
    int k = 8756;

    std::vector <int> B = countingSort(A, k);

    for (int i = 0; i < B.size(); i++) {
        std::cout << B[i] << ' ';
    }
}

