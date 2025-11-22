// Copyright Microsoft and CHERIoT Contributors.
// SPDX-License-Identifier: MIT
#include <compartment.h>
#include <debug.hh>
#include <assert.h>
#include <stddef.h>
#include <unwind.h>
#include <fail-simulator-on-error.h>

using Debug = ConditionalDebug<true, "Stack Buffer Over Write Compartment">;

void write_buf(char* buf, size_t ix)
{
    buf[ix] = 'b';
}

int __cheri_compartment("stack-buffer-over-write") vuln1()
{
    Debug::log("Testing Stack Buffer Over Write (C++)...");
    char upper[0x10];
    char lower[0x10];
    Debug::log(
        "upper = {}, lower = {}, diff = {}",
        static_cast<void*>(upper),
        static_cast<void*>(lower),
        static_cast<long>(reinterpret_cast<uintptr_t>(upper) - reinterpret_cast<uintptr_t>(lower))
    );
    assert((uintptr_t)upper == (uintptr_t)&lower[sizeof(lower)]);
    upper[0] = 'a';
    Debug::log("upper[0] = {}", upper[0]);

    size_t index = sizeof(lower);
    if(index >= sizeof(lower) ){
        Debug::log("Index: {} is out of bounds for array of size {}.", index, sizeof(lower));
    }
    else{
        write_buf(lower, sizeof(lower));
        Debug::log("lower[0] = {}", lower[0]);
    }
    Debug::log( "This line may not be reached if the program crashes.");
    return 0;
}
