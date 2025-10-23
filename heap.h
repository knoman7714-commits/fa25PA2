//
// Created by Manju Muralidharan on 10/19/25.
//

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

struct MinHeap {
    int data[64];
    int size;

    MinHeap() { size = 0; }

    void push(int idx, int weightArr[]) {
     if (size >64){}
        data [size++] = idx;
        upheap(size, weightArr);
    }

    int pop(int weightArr[]) {
    if (size == 0) return;
        int ret = data[0];
        size--;
        data[0] = data[size];
        downheap(0, weightArr);
        return ret; // placeholder
    }

    void upheap(int pos, int weightArr[]) {
        while (pos > 0) {
            int parent = (pos - 1) / 2;
            if (data[pos] < data[parent]) {
                int t = data[parent];
                data[pos] = data[parent];
                data[parent] = t;
                pos = parent;
            } else break;
        }
    }

    void downheap(int pos, int weightArr[]) {
        while (true) {
            int left = 2 * pos + 1;
            int right = 2 * pos;
            if (left >=size)break;
            int smallest = data[left];
            if (right < size && data[right] < smallest) {
                smallest = data[right];
            }
            if (weightArr[data [smallest]]>weightArr[data[pos]]) {
                int t = data[pos];
                data[pos] = data[smallest];
                data[smallest] = t;
                pos = smallest;
            }else {
                break;
            }
        }
    }
};

#endif