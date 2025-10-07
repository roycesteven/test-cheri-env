// Diagnostics for double-free behavior
// SPDX-License-Identifier: MIT

#include <compartment.h>
#include <debug.hh>
#include <unwind.h>
#include <fail-simulator-on-error.h>

using Debug = ConditionalDebug<true, "Double Compartment">;


__cheri_compartment("double-free") int vuln1(void)
{
    Debug::log("Testing Double Free...");

    int *ptr = (int*)malloc(sizeof(int));
    if (!ptr) { Debug::log( "malloc returned NULL"); return 0; }
    *ptr = 42;

    int rc1 = free(ptr);
    Debug::log( "free 1 rc = {}", rc1);

    int rc2 = free(ptr);
    if (rc2 == -EINVAL){
        Debug::log( "Second free rejected: EINVAL (double free detected).");
    }

    return 0;
}