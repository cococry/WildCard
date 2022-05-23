@ECHO OFF
SetLocal EnableDelayedExpansion

set engineFiles=
for /R %%f in (*.c) do (
    set engineFiles=!engineFiles! %%f
)

set assemblyName=Engine
set vendorFiles= vendor/Glad/src/*.c vendor/stb_image/*.c
set includeDir= -Isrc -Ivendor/Glad/include -Ivendor/GLFW/include/GLFW -Ivendor/stb_image
set compilerFlags=-g -shared -Wvarargs -Wall -Werror -o ../bin/%assemblyName%.dll
set linkingFlags=-luser32 -lgdi32 -lopengl32 -Lvendor/GLFW/lib/glfw3
set macros=-D_DEBUG -DWLDC_EXPORT -D_CRT_SECURE_NO_WARNINGS

echo Starting %assemblyName% build process...
clang %engineFiles% %compilerFlags% %macros% %includeDir% %linkingFlags%