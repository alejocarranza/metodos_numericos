set title 'Modelo de Rendimiento'
set xlabel 'Numero de Usuarios'
set ylabel 'Tiempo de Respuesta (ms)'
set grid
set key left top
plot 'datos_grafico.txt' using 1:2 title 'Datos Reales' with points pointtype 7 pointsize 1.5,\
     'datos_grafico.txt' using 1:3 title 'Modelo Ajustado' with lines linewidth 2
pause -1
