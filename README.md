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

## O que foi feito
- Transformação da imagem colorida para tons de cinza
- Filtro gaussiano
- Filtro de Sobel
- Binarização
- Transformada de hough
- Segmentacao da pupila
- Diagnóstico da catarata

## O que não foi feito
- Todas as funcionalidades básicas foram atendidas

## Extras 
- Desenho da iris (Para ativar, rode: ./catarata -i Catarata.ppm -f ppm -o diagnostico.txt -t )

## O que seria feito diferentemente		
- Outra linguagem que não c.
- A organização dos códigos seriam outra. Algumas funções seriam refatoradas, outras criadas (como uma função para checar os args do main).
