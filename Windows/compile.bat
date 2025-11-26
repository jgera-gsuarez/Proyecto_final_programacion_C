@echo off
REM =============================================
REM Compilar todos los archivos .c en el directorio actual
REM Usando MSYS2 (MinGW 64-bit) con Cairo instalado
REM =============================================

echo Compilando proyecto con GCC (MSYS2)...
gcc *.c -o programa.exe -lcairo

if %ERRORLEVEL% neq 0 (
    echo Error en la compilacion.
) else (
    echo Compilacion completada correctamente.
    echo Ejecuta el programa con: ./programa.exe
)
pause
