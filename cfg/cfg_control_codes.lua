-- TERM_CONTROL_CFG
-- do not delete first comment

-- TUTRIAL how to add new names to buttons on keyboard:
-- Add to table below your key like: "<system>" + "_" + "<keycode>" = "<action_name>"
--                          example: win / lin  +  _  +  72         = "up"
--                          will be: win_72 = "up"
-- "<action_name>" is name which will returned from term::get_key()
--
-- Example logic from c++:
-- 1. term::get_key() will freeze console (wt.exe or kitty)
-- 2. When you press up arrow on keyboard console will unfreeze
-- 3. In that moment term::get_key() will return "up" in std::string

id = {
    -- WIN32
    win_72 = "up",
    win_80 = "down",
    win_13 = "enter",

    -- else (linux or smth)
    lin_65 = "up",
    lin_66 = "down",
    lin_10 = "enter",
}
return id
