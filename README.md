Autor: Daniel Ramírez Concepción

# System Monitor

Con la ayuda de Qt vamos a crear nuestro propio monitor del sistema. Nos permitirá examinar: procesos en ejecución, conexiones abiertas, temperatura de la CPU, hardware del sistema y todo lo que se nos ocurra.

## Requisitos

 1. [Clona este repositorio](https://github.com/DzThor/soa-system-monitor) en tu ordenador.
 2. Tener instalado Qt Creator 5.8.
 
## Compilar

 1. Una vez descargado el proyecto, debemos abrir desde dentro de Qt Creator el archivo **SystemMonitor.pro**, el cual encontraremos en el directorio del repositorio que hemos clonado previamente.
 2. Después usaremos el botón con forma de martillo, o usaremos el atajo de teclas *Ctrl + B*.
 3. Si no ha surgido ningún problema (que no debería), el programa estará listo para ser ejecutado.

## Ejecutar

1. Se requiere haber realizado los pasos para la compilación del proyecto.
2. Para ejecutar el programa usaremos el botón con el icono de Play o el atajo de teclas *Ctrl + R*.
3. Aparecerá el resultado del programa en una ventana nueva.

## Características del programa

El programa posee varias pestañas con sus peculiaridades.

## Sensores

Esta pestaña mostrará la información de los sensores instalados en el hardware detectado por el sistema operativo. Cada valor esta adjunto al sensor del que proviene. Esta información se actualiza de forma automática.

## Procesos

Se muestra la información de cada proceso del sistema, en este caso se muestra el PID, CmdLine, Owner y el número de threads. Esta información se actualiza de forma automática.

## Hardware

En esta pestaña se muestra la información del hardware del equipo, la cual no es necesario actualizar.

## Usuarios *(Opcional)*

Se muestran los usuarios activos en el equipo.

## Red *(Opcional)*

Podemos observar la cantidad de paquetes de tipo TCP, UDP, ICMP e IP, que gestiona el equipo.
