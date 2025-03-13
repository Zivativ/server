set_project("server")

set_xmakever("2.6.0")

set_languages("c99")

target("server")
    set_kind("binary")  
    add_files("src/*.c")
    add_files("src/**/*.c") 
    add_includedirs("src") 

    if is_os("windows") then
        add_linkdirs("lib/windows") 
        add_links("netlib") 
    else
        add_linkdirs("lib/linux") 
        add_links("libnetlib.a") 
    end