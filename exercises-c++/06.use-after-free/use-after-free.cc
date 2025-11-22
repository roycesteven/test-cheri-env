// Copyright Microsoft and CHERIoT Contributors.
// SPDX-License-Identifier: MIT
#include <compartment.h>
#include <debug.hh>
#include <unwind.h>
#include <fail-simulator-on-error.h>

using Debug = ConditionalDebug<true, "Use After Free Compartment">;

static int is_valid_capability(const void *p)
{
    return __builtin_cheri_tag_get(p) != 0;
}

int __cheri_compartment("use-after-free") vuln1()
{
    Debug::log("Testing Use-After-Free (C++)...");
    int* ptr = new int;
    if (!ptr)
    {
        Debug::log("Allocation failed!");
        return 0;
    }
    *ptr = 123;
    Debug::log("ptr capability: {}", ptr);
    Debug::log("ptr points to memory with value: {}", *ptr);
    delete ptr;
    Debug::log("Memory has been freed.");
    if(is_valid_capability(ptr)){
        *ptr = 456;
        Debug::log("ptr points to memory with value: {}", *ptr);
        Debug::log("Value is now: {} (this should not be printed)", *ptr);
    }
    else{
        Debug::log("Memory had been freed.");
    }
        Debug::log( "This line may not be reached if the program crashes.");
   
    return 0;
}
