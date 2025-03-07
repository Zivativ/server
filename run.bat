@echo off


xmake build
copy netlib.dll build\windows\x64\release\netlib.dll 
xmake run