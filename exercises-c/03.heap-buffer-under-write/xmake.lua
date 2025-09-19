-- Copyright Microsoft and CHERIoT Contributors.
-- SPDX-License-Identifier: MIT

set_project("CHERIoT Hello World")
sdkdir = "../../cheriot-rtos/sdk"
includes(sdkdir)
set_toolchains("cheriot-clang")

option("board")
    set_default("sail")

option("sdk")
    set_default("/cheriot-tools/")

option("debug_run")
    set_default("false")
    set_showmenu(true)
    set_description("Run simulator in debug mode (-i)")

compartment("heap-buffer-under-write")
    -- memcpy
    add_deps("freestanding", "debug", "unwind_error_handler")
    add_files("heap-buffer-under-write.c")

-- Firmware image for the example.
firmware("heap-buffer-under-write-vulnerability")
    add_deps("stdio")
    add_deps("heap-buffer-under-write")
    on_load(function(target)
        target:values_set("board", "$(board)")
        target:values_set("threads", {
            {
                compartment = "heap-buffer-under-write",
                priority = 1,
                entry_point = "vuln1",
                stack_size = 0x400,
                trusted_stack_frames = 1
            }
        }, {expand = false})
    end)

on_run(function (target)
    local targetfile = target:targetfile()
    local simulator = "/cheriot-tools/bin/mpact_cheriot"
    local rundir = "./runs/run_" .. os.date("%Y%m%d_%H%M%S")

    -- check debug option
    local args = {"--output_dir=" .. rundir}
    if get_config("debug_run") == true then
        table.insert(args, "-i")
        print("Running in debug mode...")
    else
        print("Running in normal mode...")
    end
    table.insert(args, targetfile)
    os.mkdir(rundir)
    os.execv(simulator, args)
end)
