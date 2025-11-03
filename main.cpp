//
// Created by Manju Muralidharan on 10/19/25.
//
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "heap.h"
using namespace std;

// Global arrays for node information
const int MAX_NODES = 64;
int weightArr[MAX_NODES];
int leftArr[MAX_NODES];
int rightArr[MAX_NODES];
char charArr[MAX_NODES];

// Function prototypes
void buildFrequencyTable(int freq[], const string& filename);
int createLeafNodes(int freq[]);
int buildEncodingTree(int nextFree);
void generateCodes(int root, string codes[]);
void encodeMessage(const string& filename, string codes[]);

int main() {
    int freq[26] = {0};

    // Step 1: Read file and count letter frequencies
    buildFrequencyTable(freq, "input.txt");

    // Step 2: Create leaf nodes for each character with nonzero frequency
    int nextFree = createLeafNodes(freq);

    // Step 3: Build encoding tree using your heap
    int root = buildEncodingTree(nextFree);

    // Step 4: Generate binary codes using an STL stack
    string codes[26];
    generateCodes(root, codes);

    // Step 5: Encode the message and print output
    encodeMessage("input.txt", codes);

    return 0;
}

/*------------------------------------------------------
    Function Definitions (Students will complete logic)
  ------------------------------------------------------*/

// count letter of frequencies from file
void buildFrequencyTable(int freq[], const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    char ch;
    while (file.get(ch)) {
        // Convert uppercase to lowercase
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';

        // Count only lowercase letters
        if (ch >= 'a' && ch <= 'z')
            freq[ch - 'a']++;
    }
    file.close();

    cout << "Frequency table built successfully.\n";
}
// make leaf nodes for characters to show up
int createLeafNodes(int freq[]) {
    int nextFree = 0;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) {
            charArr[nextFree] = 'a' + i;
            weightArr[nextFree] = freq[i];
            leftArr[nextFree] = -1;
            rightArr[nextFree] = -1;
            nextFree++;
        }
    }
    cout << "Created " << nextFree << " leaf nodes.\n";
    return nextFree;
}

// creates encoding tree with min heap
int buildEncodingTree(int nextFree) {
    if (nextFree == 0 )return -1;
    if (nextFree == 1)return 0;
  MinHeap h;

    for (int i = 0; i < nextFree; ++i) {
        h.push(i,weightArr);
    }
    int cur = nextFree;
    while (h.size > 1) {
        int a =h.pop(weightArr);
        int b = h.pop(weightArr);
        if (cur >=MAX_NODES) {
            cerr << "Node " << cur << " exceeds MAX_NODES\n";
            exit(1);
        }
        weightArr[cur] = weightArr[a] + weightArr[b];
        leftArr[cur] = a;
        rightArr[cur] = b;
        charArr[cur] = '#';
        h.push(cur,weightArr);
        cur++;
    }
    return h.pop(weightArr);
}

//creates binary code repeatedly using a stack
//each leaf char gets a binary string
void generateCodes(int root, string codes[]) {
    for (int i = 0; i < 26; ++i) codes[i].clear();
    if (root < 0) return;
    struct Frame {int node; string path;};
    stack<Frame> st;
    st.push({root,""});
    while (!st.empty()) {
        Frame f = st.top();st.pop();
        int n = f.node;
        bool isLeaf = (leftArr[n] ==-1 && rightArr[n]==-1);
        if (isLeaf) {
            char ch = charArr[n];
            if (ch >= 'a' && ch <= 'z') {
                codes [ ch - 'a'] = f.path.empty()? "0" : f.path;
            }
        } else {
            if (rightArr[n] != -1) st.push ({rightArr[n],f.path +"1"});
            if (leftArr [n] != -1) st.push ({leftArr[n],f.path +"0"});
        }
    }
}

// Step 5: Print table and encoded message
void encodeMessage(const string& filename, string codes[]) {
    cout << "\nCharacter : Code\n";
    for (int i = 0; i < 26; ++i) {
        if (!codes[i].empty())
            cout << char('a' + i) << " : " << codes[i] << "\n";
    }

    cout << "\nEncoded message:\n";

    ifstream file(filename);
    char ch;
    while (file.get(ch)) {
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';
        if (ch >= 'a' && ch <= 'z')
            cout << codes[ch - 'a'];
    }
    cout << "\n";
    file.close();
}