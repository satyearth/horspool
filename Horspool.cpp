#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

unordered_map<char, int> preprocess_pattern(const string& pattern) {
    int m = pattern.length();
    unordered_map<char, int> bad_char_shift;

    for (int i = 0; i < m - 1; ++i) {
        bad_char_shift[pattern[i]] = m - 1 - i;
    }

    return bad_char_shift;
}

int search_pattern_dna(const string& text, const string& pattern) {
    int n = text.length();
    int m = pattern.length();
    unordered_map<char, int> bad_char_shift = preprocess_pattern(pattern);
    int i = m - 1;

    while (i < n) {
        int k = 0;
        while (k < m && pattern[m - 1 - k] == text[i - k]) {
            ++k;
        }

        if (k == m) {
            return i - m + 1;  // Pattern found at position i - m + 1
        }

        // Shift based on the bad character in the text
        char bad_char = text[i];
        if (bad_char_shift.find(bad_char) != bad_char_shift.end()) {
            i += bad_char_shift[bad_char];
        } else {
            i += m;  // Shift the pattern completely to the right
        }
    }

    return -1;  // Pattern not found in the text
}

int main() {
    // string dna_sequence = "ATCGATCGTACGATCG";
    // string pattern_to_find = "TACG";
    string dna_sequence , pattern_to_find ;
    cout<< "Enter the DNA sequence: ";
    cin>>dna_sequence;
    cout<< "Enter the pattern to find: ";
    cin>>pattern_to_find;

    int result = search_pattern_dna(dna_sequence, pattern_to_find);
    if (result != -1) {
        cout << "Pattern found at position " << result << endl;
    } else {
        cout << "Pattern not found in the DNA sequence" << endl;
    }

    return 0;
}
