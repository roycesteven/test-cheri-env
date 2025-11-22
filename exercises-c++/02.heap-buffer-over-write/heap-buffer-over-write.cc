// Copyright Microsoft and CHERIoT Contributors.
// SPDX-License-Identifier: MIT
#include <compartment.h>
#include <debug.hh>
#include <unwind.h>

using Debug = ConditionalDebug<true, "Heap Buffer Over Write Compartment">;

int __cheri_compartment("heap-buffer-over-write") vuln1()
{
    Debug::log("Testing Heap Buffer Over-write (C++)...");
    int* arr = nullptr;
    int ukuran =3;
    arr = new int[ukuran];
    if (!arr) {
        Debug::log("Allocation failed!");
        return 0;
    }
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    
    int index = 10;

    Debug::log("Attempting to write arr[{}] (out-of-bounds)...", index);
    if (index < 0 || index >= ukuran){
         Debug::log("Index: {} is out of bounds for array of size {}.", index, ukuran);
    }
    else{
        arr[index] = 999;
        Debug::log("Write completed (this should not be printed).");
        Debug::log("Value of written element: {}.", arr[index]);
    }
    delete[] arr;
        Debug::log( "This line may not be reached if the program crashes.");
    return 0;
}
