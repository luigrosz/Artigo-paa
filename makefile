all:
		gcc geradorNumeros.c -o gerador
		./gerador 1000 100000 1.txt && sleep 1 && ./gerador 10000 100000 2.txt && sleep 1 && ./gerador 100000 100000 3.txt && sleep 1 && ./gerador 100000 10000 4.txt && sleep 1 && ./gerador 1000000 50000 5.txt && sleep 1 && ./gerador 100000 500000 6.txt

clean:
	rm gerador *.txt
