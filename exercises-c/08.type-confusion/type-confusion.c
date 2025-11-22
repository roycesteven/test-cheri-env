#include <compartment.h>
#include <debug.h>
#include <unwind.h>

#define DEBUG_CONTEXT "Type Confusion Compartment"

const char hello[] = "Hello World!";

static int is_valid_capability(const void *p)
{
    return __builtin_cheri_tag_get(p) != 0;
}

union long_ptr {
    long l;
    const char *ptr;
} lp = { .ptr = hello };

void inc_long_ptr(union long_ptr *lpp) {
    lpp->l++;
}

__cheri_compartment("type-confusion") int vuln1()
{
    CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "Testing Type confusion (C)...");

    CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "Before inc_long_ptr: lp.ptr = {}", (char*)lp.ptr);

    inc_long_ptr(&lp);
    if(!is_valid_capability(lp.ptr)){
 CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "Pointer is no longer valid after inc_long_ptr.");
    }
    else if (is_valid_capability(lp.ptr)){
        CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "After inc_long_ptr: lp.ptr = {}", (char*)lp.ptr);
    }
       CHERIOT_DEBUG_LOG(DEBUG_CONTEXT, "This line may not be reached if the program crashes.");

    return 0;
}
