// Copyright Microsoft and CHERIoT Contributors.
// SPDX-License-Identifier: MIT

#include <compartment.h>
#include <debug.h>
#include <unwind.h>
#include <stdlib.h>

#define DEBUG_CONTEXT "Heap Buffer Under Write Compartment"

__cheri_compartment("heap-buffer-under-write") int vuln1(void)
{
    CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "Testing Heap Buffer Under-write (C)...");
    int ukuran =3;
    int *arr = (int *)malloc(ukuran * sizeof(int));
    if (arr == NULL) { return 0; }
    arr[0] = 10; arr[1] = 20; arr[2] = 30;
    int index =-1;
    CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "Attempting under-write arr[{}] = 999 ...", index);

    if (index < 0 || index >= ukuran){
        CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "Index: {} is out of bounds.", index);
    }
    else{
        arr[index] = 999;
        CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "Value: {}", arr[index]);
    }
    free(arr);
    CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "Freed array (if we reached here).");
    return 0;
}
