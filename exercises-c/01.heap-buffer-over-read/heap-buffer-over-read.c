// Copyright Microsoft and CHERIoT Contributors.
// SPDX-License-Identifier: MIT

#include <compartment.h>
#include <debug.h>
#include <stdio.h>
#include <unwind.h>
#include <stdlib.h>


#define DEBUG_CONTEXT "Heap Buffer Over Read Compartment"

/// Thread entry point.
__cheri_compartment("heap-buffer-over-read") int vuln1()
{
    int ukuran =3;
    int* arr = (int*)malloc(ukuran * sizeof(int));
    if (arr == NULL) {return 0;} // Always check for malloc failure
    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;
    for (int i =0; i<3;i++) {
        printf("%d",arr[i]); 
    }

    int index = 10;

    CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "Testing Buffer Over-read (C)...");

    CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "Accessing arr[{}]... ", index);

    if (index < 0 || index >= ukuran){
        CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "Index: {} is out of bounds for array of size {}.", index, ukuran);
    }
    else{
        int value = arr[index]; 
        CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "Value: {}", value);
    }
    free(arr);
    CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "Finished without crashing.");

    return 0;
}
