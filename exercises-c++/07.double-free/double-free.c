// Diagnostics for double-free behavior
// SPDX-License-Identifier: MIT

#include <errno.h>
#include <compartment.h>
#include <debug.h>
#include <unwind.h>
#include <stdlib.h>

#define DEBUG_CONTEXT "Double Free Compartment"

__cheri_compartment("double-free") int vuln1(void)
{
    CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "Testing Double Free...");

    int *ptr = (int*)malloc(sizeof(int));
    if (!ptr) { CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "malloc returned NULL"); return 0; }
    *ptr = 42;

    int rc1 = free(ptr);
    CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "free 1 rc = {}", rc1);

    int rc2 = free(ptr);
    if (rc2 == -EINVAL){
        CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "Second free rejected: EINVAL (double free detected).");
    }

    return 0;
}