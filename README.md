# Proyecto Final en C con Cairo

Este proyecto está escrito en C y utiliza la librería **Cairo** para gráficos. A continuación se detallan los pasos para compilarlo en **Windows**.

## ✅ Requisitos
- [MinGW-w64](https://www.mingw-w64.org/downloads/)
- [Cairo para Windows (MSYS2)](https://www.msys2.org/) o [GTK Runtime](https://github.com/tschoonj/GTK-for-Windows-Runtime-Environment-Installer/releases)

Es recomendable usar MSYS2 para instalar Mingw-w64 y Cairo.
Para hacerlo abre una ventana de terminal de MSYS2.
1.  Sincroniza e instala paquetes, actualiza la base de datos de paquetes(descarga la lista mas reciente), actualiza todos los paquetes instalados a sus últimas versiones.
```
pacman -Syu
```

2. Actualiza los paquetes del sistema a la version mas reciente.
```
pacman -Su
```

3. Instala MingW-w64
```
pacman -S mingw-w64-x86_64-gcc
```

4. Instala Cairo
```
pacman -S mingw-w64-x86_64-cairo
```

## ✅ Pasos para compilar
1. Abre la terminal **CMD** en la carpeta del proyecto.
2. Ejecuta el script `compile.bat` (incluido en este repositorio).

## ✅ Comando manual
Si prefieres compilar manualmente:
1. Abre la terminal **MSYSM2 MingW-w64**.
2. Ve a la carpeta de tu proyecto.
```
cd /c/ruta/a/tu/proyecto
```
3. Compila con gcc
```
gcc *.c -o programa.exe -lcairo
```
4. Ejecuta el programa
```
./programa.exe