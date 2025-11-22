// Copyright Microsoft and CHERIoT Contributors.
// SPDX-License-Identifier: MIT

#include "stddef.h"
#include <compartment.h>
#include <debug.h>
#include <stdio.h>
#include <unwind.h>
#include <stdlib.h>


#define DEBUG_CONTEXT "Use After Free Compartment"

/// Thread entry point.
__cheri_compartment("use-after-free") int vuln1()
{
    CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "Testing Use-After-Free (C)...");
    int* ptr = (int*)malloc(sizeof(int));
    if (ptr == NULL) {return 0;}
    *ptr = 123;
    CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "ptr points to memory with value: {}", *ptr);
    printf("%d\n", *ptr);
    printf("%p\n", ptr);
    free(ptr);
    ptr = NULL;
    CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "Memory has been freed.");
    CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "Attempting to dereference dangling pointer... ");
    if(ptr !=NULL){
        *ptr = 456;
        CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "Value is now: {}", *ptr);
    }
    else{
        CHERIOT_DEBUG_LOG(
        DEBUG_CONTEXT,
        "Use-after-free prevented: pointer is NULL after free.");
    }


    




    return 0;
}
