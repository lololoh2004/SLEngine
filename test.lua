local success, ffi = pcall(require, "ffi")

if success then
    print("FFI Aviable! Working on " .. ffi.os)
    
    ffi.cdef[[
        void Sleep(int ms);
    ]]
else
    print("FFI Not Aviable")
end

PrintHello()

--return 42