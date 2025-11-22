// Copyright Microsoft and CHERIoT Contributors.
// SPDX-License-Identifier: MIT
#include <compartment.h>
#include <cstdio>
#include <debug.hh>
#include <unwind.h>
#include <fail-simulator-on-error.h>

using Debug = ConditionalDebug<true, "OOB Pointer Arithmetic Compartment">;

static int is_valid_capability(const void *p)
{
    return __builtin_cheri_tag_get(p) != 0;
}


int __cheri_compartment("oob-pointer-arithmetic") vuln1()
{
    Debug::log("Testing Out-Of-Bounds Pointer Arithmetic (C++)...");
    int arr[4] = {100, 200, 300, 400};
    int arr_length = (int)(sizeof(arr)/ sizeof(arr[0]));
    Debug::log("Array base: {}", static_cast<int*>(arr));
    int jarak = 10;
    int* p = arr + jarak;
  
    Debug::log("Pointer moved to arr + {}: {}", jarak, static_cast<int*>(p));
    if(is_valid_capability(p)){
           int val = *p;
Debug::log("Read value: {}.", val);

    }
    // if(arr+arr_length <= p){
    // Debug::log("Offset {} is out of bounds for array of size {}.",
    //         jarak,
    //         arr_length );
    // }
    else{
             Debug::log("Offset {} is out of bounds for array of size {}.",
            jarak,
            arr_length );
    }
     Debug::log( "This line may not be reached if the program crashes.");
    return 0;
}
