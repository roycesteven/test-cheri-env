// Copyright Microsoft and CHERIoT Contributors.
// SPDX-License-Identifier: MIT

#include <compartment.h>
#include <debug.h>
#include <unwind.h>

#define DEBUG_CONTEXT "OOB Pointer Arithmetic Compartment"

__cheri_compartment("oob-pointer-arithmetic") int vuln1(void)
{
    CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "Testing Out-Of-Bounds Pointer Arithmetic (C)...");
    int arr[4] = {100, 200, 300, 400};
    CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "Array base: {}", (uintptr_t)arr);
    const int arr_length = (int)(sizeof(arr)/ sizeof(arr[0]));
    const int jarak = 10;

    /* Make a pointer well past the end via arithmetic */
    int *p = arr + jarak; // pointer now points far beyond arr
    CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "Pointer moved to arr + {}: {}", jarak, (uintptr_t)p);
    
    CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "Dereferencing OOB pointer ...");
    if (jarak < 0 || jarak >=arr_length){
            CHERIOT_DEBUG_LOG(
            DEBUG_CONTEXT,
            "Offset {} is out of bounds for array of size {}.",
            jarak,
            arr_length);
    }
    else{
    int val = *p; // out-of-bounds read (or write) via pointer arithmetic
    CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "Read value: {}.", val);
    }
    CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "This line may not be reached if the program crashes.");

    return 0;
}
