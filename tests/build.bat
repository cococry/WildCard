@ECHO OFF
SetLocal EnableDelayedExpansion

set files=
for /R %%f in (*.c) do (
    set files=!files! %%f
) 

set assemblyName=Tests
set vendorFiles= ../engine/vendor/Glad/src/glad.c ../engine/vendor/stb_image/stb_image.c ../engine/vendor/cglm/src/*.c ../engine/vendor/cglm/src/clipspace/*.c ../engine/vendor/cglm/src/swift/*.c 
set compilerFlags=-g -Wvarargs -Wall -Werror -o ../bin/%assemblyName%.exe
set includeDir= -Isrc -I../engine/vendor/Glad/include -I../engine/vendor/GLFW/include -I../engine/vendor/stb_image -I../engine/src -I../engine/src/wildcard -I../engine/vendor/cglm/include
set linkingFlags=-L../bin/ -lengine -lkernel32 -luser32 -lgdi32 -lwinspool -lcomdlg32 -ladvapi32 -lshell32 -lole32 -loleaut32 -luuid -lodbc32 -lopengl32 -L../engine/vendor/GLFW/lib/ -lglfw3 -lmsvcrtd.lib
set macros=-D_DEBUG -DWLDC_IMPORT -DGLFW_INCLUDE_NONE

echo Starting %assemblyName% build process...
clang %files%  %vendorFiles% %compilerFlags% %macros% %includeDir% %linkingFlags%