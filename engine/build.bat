@ECHO OFF
SetLocal EnableDelayedExpansion

set engineFiles=
for /R %%f in (*.c) do (
    set engineFiles=!engineFiles! %%f
)

set assemblyName=Engine
set includeDir= -Isrc -Isrc/wildcard -Ivendor/Glad/include -Ivendor/GLFW/include -Ivendor/stb_image
set compilerFlags=-g -shared -Wvarargs -Wall -Werror -o ../bin/%assemblyName%.dll
set linkingFlags=-lkernel32 -luser32 -lgdi32 -lwinspool -lcomdlg32 -ladvapi32 -lshell32 -lole32 -loleaut32 -luuid -lodbc32 -lopengl32 -Lvendor/GLFW/lib -lglfw3 -lmsvcrtd.lib
set macros=-D_DEBUG -DWLDC_EXPORT -D_CRT_SECURE_NO_WARNINGS -DGLFW_INCLUDE_NONE

echo Starting %assemblyName% build process...
clang %engineFiles% %compilerFlags% %macros% %includeDir% %linkingFlags% 