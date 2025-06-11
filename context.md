# 📊 Detección de Anomalías en Tráfico de Red mediante Ajuste Estadístico y Métodos Iterativos

## 👨‍💻 Carrera: Ingeniería Informática  
## 👨‍🔬 Autor: Alejo Carranza  
## 🧪 Área: Análisis de Datos, Redes, Métodos Numéricos  

---

## 🧠 Introducción

El tráfico de red es un recurso crítico en cualquier entorno informático, desde redes empresariales hasta servicios en la nube. La detección temprana de **anomalías en el comportamiento del tráfico** permite identificar amenazas de seguridad, errores de configuración o fallas de rendimiento. Tradicionalmente, esto se aborda con sistemas complejos de machine learning, pero en este proyecto se propone una alternativa más matemática y transparente: **modelar el tráfico con ajuste estadístico y resolver sistemas de ecuaciones mediante el método de Gauss-Seidel**.

---

## 🎯 Objetivo General

Desarrollar un sistema capaz de **detectar comportamientos anómalos en tráfico de red** utilizando técnicas de ajuste estadístico y resolución iterativa de sistemas lineales mediante el **método de Gauss-Seidel**.

---

## 🎯 Objetivos Específicos

- Recolectar datos reales o simulados de tráfico de red.
- Modelar el comportamiento esperado del tráfico mediante regresiones o sistemas lineales.
- Resolver dichos modelos usando el método iterativo de Gauss-Seidel.
- Detectar desviaciones significativas entre el modelo y los valores reales para identificar anomalías.
- Evaluar la eficacia del sistema con datos sintéticos y casos reales.

---

## 🧩 Justificación

En contextos como ciberseguridad, optimización de redes o monitoreo de servicios, es fundamental contar con herramientas **precisas, interpretables y eficientes** para anticipar fallas o detectar ataques. Este enfoque combina la **solidez de las matemáticas aplicadas** con la posibilidad de interpretabilidad que muchas veces se pierde en los modelos de inteligencia artificial.

Además, se propone aplicar conceptos vistos en materias como:
- Métodos Numéricos (Gauss-Seidel)
- Estadística
- Redes de Computadoras
- Estructuras de Datos y Análisis Algorítmico

---

## 📚 Marco Teórico

### 🔹 Tráfico de Red
- Variables: número de paquetes, tamaño promedio, origen/destino, frecuencia.
- Herramientas de captura: Wireshark, TCPDump, datasets públicos como CIC-IDS2017.

### 🔹 Anomalías comunes
- Ataques DDoS (bruscos aumentos de tráfico)
- Escaneo de puertos
- Caídas o picos inusuales
- Cambios en patrones de paquetes

### 🔹 Ajuste estadístico
- Regresión lineal para modelar tráfico esperado
- Matrices de correlación entre variables

### 🔹 Método de Gauss-Seidel
- Método iterativo para resolver sistemas lineales
- Requiere una matriz cercana a diagonalmente dominante
- Aplicable en tiempo real para ajustar modelos constantemente

---

## 🧪 Metodología

1. **Recolección de Datos**
   - Captura de tráfico real (Wireshark) o uso de datasets simulados
   - Preprocesamiento con Pandas: limpieza, selección de variables

2. **Modelado Matemático**
   - Suposición: el tráfico puede modelarse con un sistema lineal aproximado
   - Ejemplo: 
     \[
     x_1 + 2x_2 + x_3 = 1500 \\
     2x_1 + 3x_2 + 4x_3 = 3000 \\
     3x_1 + x_2 + 5x_3 = 2800
     \]
   - Interpretación: variables como tiempo, cantidad y tamaño de paquetes se ajustan para predecir el tráfico

3. **Aplicación de Gauss-Seidel**
   - Implementación en Python con control de iteraciones y errores
   - Comparación contra soluciones exactas

4. **Evaluación de Anomalías**
   - Se define una tolerancia aceptable (e.g. ±10%)
   - Cuando el tráfico real excede el valor esperado según el modelo → se marca como **anomalía**

5. **Visualización**
   - Gráficas de tráfico normal vs. anómalo
   - Alertas en consola o dashboard simple

---

## 🛠️ Herramientas y Tecnologías

- **Python** (NumPy, Pandas, Matplotlib, Scikit-learn)
- **Wireshark** o datasets públicos
- **Jupyter Notebook** o VS Code
- Posible integración con bases de datos (SQLite, MongoDB)

---

## 📈 Cronograma Tentativo

| Semana | Actividad |
|--------|-----------|
| 1      | Revisión teórica y definición de variables de red |
| 2      | Búsqueda o captura de datos de tráfico |
| 3      | Análisis estadístico inicial y limpieza de datos |
| 4      | Construcción del modelo y armado del sistema de ecuaciones |
| 5      | Implementación del método de Gauss-Seidel |
| 6      | Detección de anomalías y validación |
| 7      | Redacción del informe y presentación de resultados |

---

## ✅ Resultados Esperados

- Sistema funcional que pueda detectar anomalías simples en datos de tráfico.
- Validación contra ejemplos conocidos.
- Un informe final con gráficos, explicaciones matemáticas y evaluación del modelo.

---

## 📌 Posibles Extensiones

- Aplicar otras técnicas iterativas (Jacobi, SOR).
- Añadir aprendizaje automático para comparar métodos.
- Aplicación en redes reales en tiempo real con dashboards interactivos.

---

## 🧠 Conclusión

Este proyecto busca demostrar cómo herramientas matemáticas como el método de Gauss-Seidel pueden ser útiles en un entorno informático real, aplicando técnicas claras, eficientes y fácilmente interpretables para detectar anomalías en redes de comunicación.

