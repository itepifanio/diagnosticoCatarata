# Diagnostico de Catarata
Projeto final da disciplina de ITP

![alt text](https://github.com/itepifanio/diagnosticoCatarata/blob/master/docs/assets/images/imagem1.png)
<img src="https://github.com/itepifanio/diagnosticoCatarata/blob/master/docs/assets/images/cat.png" width="471px">
## Autores:
* [Ítalo Epifânio de Lima e Silva](https://github.com/itepifanio)
* [Joel de Farias Mendonça Júnior](https://github.com/Joelfmjr)
### Como compilar o projeto
* Para rodar:

	make && ./catarata -i Catarata.ppm -f ppm -o diagnostico.txt
	
* Para apagar progresso:

	make clean

## Informações sobre o projeto

 O projeto, escrito em C, analisa 4 imagens em formato ppm (duas
 com catarata e duas sem catarata). São realizados várias etapas 
 de processamento de imagem para chegar a um diagnóstico. Filtro
 gaussiano, filtro de sobel, binarização, transformada de hough 
 foram algumas das técnicas utilizadas.

