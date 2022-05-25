@ECHO OFF


echo Starting build process...

pushd engine
call build.bat
popd
if %ERRORLEVEL% neq 0 (echo: Error:%ERRORLEVEL% && exit)

pushd tests
call build.bat
popd
if %ERRORLEVEL% neq 0 (echo: Error:%ERRORLEVEL% && exit)

echo Built repository successfully.