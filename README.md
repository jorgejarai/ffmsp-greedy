# `ffmsp-greedy`

Proyecto para resolver el problema FFMSP utilizando heurísticas *greedy*.

## Instrucciones para compilar

Este programa requiere CMake para ser compilado.

Para compilar el programa, ejecute los siguientes comandos:

```console
$ mkdir build
$ cd build
$ cmake ..
$ make
```

## Ejecución

```console
$ ./build/greedy -i <ruta_instancia> -th <umbral>
$ ./build/greedy_rnd -i <ruta_instancia> -th <umbral> -a <coef_determinismo>
```

Los archivos del dataset no están incluidos en este repositorio.
