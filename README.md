# Network Traffic Anomaly Detection

Este proyecto implementa un sistema de detección de anomalías en tráfico de red utilizando el método de Gauss-Seidel y análisis estadístico.

## Requisitos Previos

### Instalar MinGW-w64 (compilador C++)
1. Descarga MinGW-w64 desde: https://github.com/niXman/mingw-builds-binaries/releases
2. Selecciona la versión x86_64 (ej: "x86_64-13.2.0-release-posix-seh-ucrt-rt_v11-rev1.7z")
3. Extrae el contenido en `C:\mingw64`
4. Agrega `C:\mingw64\bin` a las variables de entorno del sistema:
   - Abre "Editar las variables de entorno del sistema"
   - Click en "Variables de entorno"
   - En "Variables del sistema", selecciona "Path" y click en "Editar"
   - Click en "Nuevo" y agrega `C:\mingw64\bin`
   - Click en "Aceptar" en todas las ventanas

### Verificar la instalación
1. Cierra y vuelve a abrir el Símbolo del sistema (cmd)
2. Ejecuta el siguiente comando para verificar la instalación:
```bash
g++ --version
```

## Compilar y Ejecutar el Proyecto

1. Abre el Símbolo del sistema (cmd) y navega hasta el directorio del proyecto:
```bash
cd ruta\a\tu\proyecto
```

2. Compila el proyecto:
```bash
g++ -std=c++17 main.cpp NetworkTrafficAnalyzer.cpp -o network_analyzer
```

3. Ejecuta el programa:
```bash
network_analyzer.exe
```

## Nota Importante sobre el Método de Gauss-Seidel

El método de Gauss-Seidel requiere que la matriz del sistema sea diagonalmente dominante. Una matriz es diagonalmente dominante si, para cada fila, el valor absoluto del elemento diagonal es mayor que la suma de los valores absolutos de los demás elementos de esa fila.

Por ejemplo, en el sistema de ecuaciones:
```
x1 + 2x2 + x3 = 1500
2x1 + 3x2 + 4x3 = 3000
3x1 + x2 + 5x3 = 2800
```

Para que sea diagonalmente dominante, necesitamos reorganizar las ecuaciones para que:
- |1| > |2| + |1| (no cumple)
- |3| > |2| + |4| (no cumple)
- |5| > |3| + |1| (cumple)

Para solucionar esto, puedes:
1. Reordenar las ecuaciones para que la matriz sea diagonalmente dominante
2. O modificar el código para usar otro método iterativo como Jacobi o SOR

## Estructura del Proyecto

- `NetworkTrafficAnalyzer.h`: Declaración de la clase principal
- `NetworkTrafficAnalyzer.cpp`: Implementación de los métodos
- `main.cpp`: Programa principal con ejemplos de uso

## Solución de Problemas

### Error: 'g++' no es reconocido como un comando
- Verifica que MinGW-w64 esté instalado correctamente
- Asegúrate de que la ruta `C:\mingw64\bin` esté en las variables de entorno
- Reinicia el Símbolo del sistema

### Error: Matrix is not diagonally dominant
- Reordena las ecuaciones del sistema para que la matriz sea diagonalmente dominante
- O modifica el código para usar otro método iterativo

### Error durante la compilación
- Verifica que estás usando C++17 o superior
- Asegúrate de que todos los archivos fuente estén en el directorio correcto
- Verifica que no haya errores de sintaxis en el código

## Notas Adicionales

- El programa utiliza el método de Gauss-Seidel para resolver sistemas de ecuaciones lineales
- La detección de anomalías se basa en un umbral del 10% de desviación
- Los ejemplos incluidos demuestran tanto tráfico normal como anómalo