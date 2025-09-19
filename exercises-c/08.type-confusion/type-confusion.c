#include <compartment.h>
#include <debug.h>
#include <unwind.h>

#define DEBUG_CONTEXT "Type Confusion Compartment"

const char hello[] = "Hello World!";

union long_ptr {
    long l;
    const char *ptr;
} lp = { .ptr = hello };

void inc_long_ptr(union long_ptr *lpp) {
    lpp->l++;
}

__cheri_compartment("type-confusion") int vuln1(void)
{
    CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "Testing Type confusion (C)...");

    CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "Before inc_long_ptr: lp.ptr = {}", (char*)lp.ptr);
    inc_long_ptr(&lp);
    CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "After inc_long_ptr: lp.ptr = {}", (char*)lp.ptr);

    return 0;
}
