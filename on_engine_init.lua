--utils.system_launch("notepad.exe", "")
console.pro_print('bold', 'success', 'hello in green', 123, true)
--
--options = {
--    first_ = "i think its first" ,
--    second_ = 1,
--    i_think_third = "1",
--}
--console.pick("hello its pick", options)

-- You can leave small on-init things here

engine.add_hook("on_render_ui", "my_menu", function()
    sgui.begin_window("BP TO RUN..")
        if sgui.add_button("Run test click") then
            console.msg("CLICK!\n")
        end
    sgui.end_window()
end)


local files = utils.dir_to_tab(".")

for i = 1, #files do
    print("File [" .. i .. "]: " .. files[i])
end