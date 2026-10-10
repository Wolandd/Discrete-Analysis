#include <iostream>
#include <vector>

void insertionSort(std::vector <double>& a) {
    int n = a.size();
    for (int i = 1; i < n; i++) {
        int j = i;
        double x = a[i];
        while (j - 1 >= 0 && x < a[j-1]) {
            a[j] = a[j-1];
            j--;
        }
        a[j] = x;
    }
}

void bucketSort(std::vector <double>& a) {
    int n = a.size();
    if (n <= 1) {
        return;
    }
    std::vector < std::vector <double> > k(n);
    for (int i = 0; i < n; i++) {
        k[int(a[i] * n)].push_back(a[i]);
    }

    for (int i = 0; i < n; i++) {
        insertionSort(k[i]);
    }
    int idx = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k[i].size(); j++) {
            a[idx] = k[i][j];
            idx++;
        }
    }
}

int main()
{
    // bucketsss :)
}
