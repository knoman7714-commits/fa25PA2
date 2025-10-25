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
    MinHeap():size(0){}


    void push(int idx, int weightArr[]) {
     if (size >=64)return;
        data [size] = idx;
        upheap(size, weightArr);
        size++;
    }

    int pop(int weightArr[]) {
    if (size == 0) return-1;
        int ret = data[0];
        size--;
        if (size > 0) {
         data[0] = data[size];
            downheap(0, weightArr);
        }
        return ret; // placeholder
    }

    void upheap(int pos, int weightArr[]) {
        while (pos > 0) {
            int parent = (pos - 1) / 2;
            if (weightArr[data[pos]] < weightArr[data[parent]]) {
                int t = data[pos];
                data[pos] = data[parent];
                data[parent] = t;
                pos = parent;
            } else break;
        }
    }

    void downheap(int pos, int weightArr[]) {
        while (true) {
            int left = 2 * pos + 1, right =2* pos + 2;
            if (left>=size)break;
            int smallest = left;
            if (right < size && weightArr[data [right]] < weightArr [data[left]])
                smallest = right;

            if (weightArr[data [smallest]]<weightArr[data[pos]]) {
                int t = data[pos];
                data[pos] = data[smallest];
                data[smallest] = t;
                pos = smallest;

            } else break;
        }
    }
};

#endif