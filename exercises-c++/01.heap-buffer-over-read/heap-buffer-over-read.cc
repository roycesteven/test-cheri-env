// Copyright Microsoft and CHERIoT Contributors.
// SPDX-License-Identifier: MIT


#include <compartment.h>
#include <debug.hh>
#include <unwind.h>
#include <fail-simulator-on-error.h>

/// Expose debugging features unconditionally for this compartment.
using Debug = ConditionalDebug<true, "Heap Buffer Over Read Compartment">;


/// Thread entry point.
int __cheri_compartment("heap-buffer-over-read") vuln1()
{
    Debug::log("Running Buffer Over-read (C++)...");
    int ukuran = 3;
    int* arr = new int[ukuran];
    if (arr == nullptr)
    {
        Debug::log("Allocation failed!");
        return -1;
    }
    Debug::log("Array created, assigning values...");
    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;
    
    Debug::log("Accessing arr[10] (out-of-bounds)...");
    int index =10;

    if(index < 0 || index >=ukuran ){
    Debug::log("Index: {} is out of bounds for array of size {}.", index, ukuran);
    }else{
    int value = arr[index];
Debug::log("Value: {}", value);
    }


    delete[] arr;
    Debug::log("Completed without crashing.");
    return 0;
}
