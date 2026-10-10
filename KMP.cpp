#include <iostream>
#include <string>
#include <vector>

void prefixFunction(std::vector <int>& sp, const std::string& pat) {
    sp[0] = 0;
    int m = pat.size();
    int j = 0;
    for (int i = 1; i < m; i++) {
        while (j > 0 && pat[i] != pat[j]) {
            j = sp[j - 1];
        }
        if (pat[i] == pat[j]) {
            j++;
        }
        sp[i] = j;
    }
}

std::vector <int> KMP(const std::string& text, const std::string& pat) {
    if (pat.empty()) {
        return { 0 };
    }
    int n = text.size();
    int m = pat.size();
    std::vector <int> sp(m);
    prefixFunction(sp, pat);
    int j = 0;
    std::vector <int> entry;
    for (int i = 0; i < n; i++) {
        while (j > 0 && text[i] != pat[j]) {
            j = sp[j - 1];
        }
        if (text[i] == pat[j]) {
            j++;
        }
        if (j == m) {
            entry.push_back(i - j + 1);
            j = sp[j - 1];
        }
    }
    return entry;
}

int main()
{
    
}

