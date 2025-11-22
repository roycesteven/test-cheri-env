// Copyright Microsoft and CHERIoT Contributors.
// SPDX-License-Identifier: MIT
#include <compartment.h>
#include <debug.hh>
#include <unwind.h>
#include <fail-simulator-on-error.h>

using Debug = ConditionalDebug<true, "Heap Buffer Under Write Compartment">;

int __cheri_compartment("heap-buffer-under-write") vuln1()
{
    Debug::log("Testing Heap Buffer Under-write (C++)...");

    int* arr = new int[3];
    const int arr_length = (int)(sizeof(arr)/ sizeof(arr[0]));
    if (!arr)
    {
        Debug::log("Allocation failed!");
        return 0;
    }
    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;
    Debug::log("Attempting under-write arr[-1] = 999 ...");
    int index = -1;
    if (index < 0 || index >= arr_length){
        Debug::log("Index: {} is out of bounds.", index);
    }
    else{
        arr[index] = 999;
        Debug::log("Under-write completed (this should not be printed).");
        Debug::log("Inserted element: {}.", arr[index]);
    }
    delete[] arr;
            Debug::log( "This line may not be reached if the program crashes.");
    return 0;
}
