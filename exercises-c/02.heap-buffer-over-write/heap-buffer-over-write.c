// Copyright Microsoft and CHERiOT Contributors.
// SPDX-License-Identifier: MIT

#include <compartment.h>
#include <debug.h>
#include <unwind.h>
#include <stdlib.h>

#define DEBUG_CONTEXT "Heap Buffer Over Write Compartment"

__cheri_compartment("heap-buffer-over-write") int vuln1(void)
{
    int ukuran =3;
    int* arr = (int*)malloc(ukuran * sizeof(int));
    if (arr == NULL) { return 0; }

    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;

    CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "Testing Buffer Over-write (C)...");
    int index = 3;

    CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "Attempting to write arr[{}]...", index);



    if (index < 0 || index >= ukuran){
        CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "Index: {} is out of bounds for array of size {}.", index, ukuran);
    }
    else{
        arr[index] = 999;
        CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "Value: {}", arr[index]);
    }

    free(arr);
    CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "This line may not be reached if the program crashes.");

    return 0;
}
