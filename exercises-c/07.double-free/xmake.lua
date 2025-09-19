-- Copyright Microsoft and CHERIoT Contributors.
-- SPDX-License-Identifier: MIT

set_project("CHERIoT Hello World")
sdkdir = "../../cheriot-rtos/sdk"
includes(sdkdir)
set_toolchains("cheriot-clang")

option("board")
    set_default("sail")

compartment("double-free")
    -- memcpy
    add_deps("freestanding", "debug", "unwind_error_handler")
    add_files("double-free.c")

-- Firmware image for the example.
firmware("double-free-vulnerability")
    add_deps("stdio")
    add_deps("double-free")
    on_load(function(target)
        target:values_set("board", "$(board)")
        target:values_set("threads", {
            {
                compartment = "double-free",
                priority = 1,
                entry_point = "vuln1",
                stack_size = 0x400,
                trusted_stack_frames = 1
            }
        }, {expand = false})
    end)
