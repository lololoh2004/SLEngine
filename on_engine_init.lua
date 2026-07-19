---------------------------------------------
-- You can leave small on-init things here --
---------------------------------------------

--utils.system_launch("notepad.exe", "")
console.pro_print('bold', 'success', 'hello in green', 123, true)
--
--options = {
--    first_ = "i think its first" ,
--    second_ = 1,
--    i_think_third = "1",
--}
--console.pick("hello its pick", options)


local bp_files = utils.dir_to_tab("./bp_mods")
--for i = 1, #files do
--    print("File [" .. i .. "]: " .. files[i])
--end

engine.add_hook("on_render_ui", "bp_choice", function()
    sgui.begin_window("BP TO RUN..")
    for i = 1, #bp_files do
        local bp_name = bp_files[i]
        if sgui.add_button(bp_name) then
            console.msg("[LUA] INFO : You launch " .. bp_name .. "\n   Upon successful startup, the engine GUI will close..\n\n")
            local success, error_msg = pcall(dofile, "./bp_mods/" .. bp_name .. "/lua/on_init.lua")
            if not success then
                console.msg("[LUA] ERROR : NO_INIT_FILE_IN_BP : " .. bp_name .. ":\n   " .. tostring(error_msg) .. "\n")
            else
                --console.msg("[LUA] INFO : Success !  : " .. bp_name .. " loaded correctly\n   Engine GUI will close" .. "\n")
                engine.del_hook("on_render_ui", "bp_choice")
            end
        end
    end
    sgui.end_window()
end)

--engine.del_hook("on_render_ui", "bp_choice")


