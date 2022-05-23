@ECHO OFF
SetLocal EnableDelayedExpansion

set files=
for /R %%f in (*.c) do (
    set files=!files! %%f
) 

set assemblyName=Tests
set vendorFiles= vendor/Glad/src/*.c vendor/stb_image/*.c
set compilerFlags=-g -o ../bin/%assemblyName%.exe
set includeDir= -Isrc -Ivendor/Glad/include -Ivendor/GLFW/include/GLFW -Ivendor/stb_image -I../engine/src
set linkingFlags=-L../bin/ -lengine.lib -luser32 -lgdi32 -lopengl32 -Lvendor/GLFW/lib/glfw3
set macros=-D_DEBUG -DWLDC_IMPORT

echo Starting %Tests% build process...
clang %files% %compilerFlags% %macros% %includeDir% %linkingFlags%