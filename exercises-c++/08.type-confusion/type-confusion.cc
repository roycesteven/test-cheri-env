// Copyright Microsoft and CHERIoT Contributors.
// SPDX-License-Identifier: MIT
#include <compartment.h>
#include <debug.hh>
#include <unwind.h>
#include <fail-simulator-on-error.h>

using Debug = ConditionalDebug<true, "Type Confusion Compartment">;

const char Hello[] = "Hello World!";

static int is_valid_capability(const void *p)
{
    return __builtin_cheri_tag_get(p) != 0;
}

union long_ptr {
    long l;
    const char* ptr;
} lp = { .ptr = Hello };

void inc_long_ptr(long_ptr* lpp) {
    lpp->l++;
}

int __cheri_compartment("type-confusion") vuln1()
{
    Debug::log("Testing Type confusion (C++)...");
    Debug::log("Before inc_long_ptr: lp.ptr = {}", lp.ptr);
    inc_long_ptr(&lp);
    if (is_valid_capability(lp.ptr)){
         Debug::log("After inc_long_ptr: lp.ptr = {}", lp.ptr);
    }
    else{
        Debug::log("Pointer is no longer valid after inc_long_ptr.");
    }
      Debug::log( "This line may not be reached if the program crashes.");
   
    return 0;
}
