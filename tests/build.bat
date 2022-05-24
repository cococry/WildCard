@ECHO OFF
SetLocal EnableDelayedExpansion

set files=
for /R %%f in (*.c) do (
    set files=!files! %%f
) 

set assemblyName=Tests
set vendorFiles= vendor/Glad/src/*.c vendor/stb_image/*.c
set compilerFlags=-g -o ../bin/%assemblyName%.exe
set includeDir= -Isrc -I../engine/vendor/Glad/include -I../engine/vendor/GLFW/include -I../engine/vendor/stb_image -I../engine/src
set linkingFlags=-L../bin/ -lengine.lib -lkernel32 -luser32 -lgdi32 -lwinspool -lcomdlg32 -ladvapi32 -lshell32 -lole32 -loleaut32 -luuid -lodbc32 -lopengl32 -L../engine/vendor/GLFW/lib/ -lglfw3 -lmsvcrtd.lib
set macros=-D_DEBUG -DWLDC_IMPORT -DGLFW_INCLUDE_NONE

echo Starting %Tests% build process...
clang %files% %compilerFlags% %macros% %includeDir% %linkingFlags%