all:
		gcc geradorNumeros.c -o gerador
		./gerador 1000 100000 1.txt && sleep 1 && ./gerador 10000 100000 2.txt && sleep 1 && ./gerador 100000 100000 3.txt && sleep 1 && ./gerador 100000 10000 4.txt && sleep 1 && ./gerador 1000000 50000 5.txt && sleep 1 && ./gerador 1000000 500000 6.txt


		gcc sort.c -o sort
		clear
		./sort 1.txt && ./sort 2.txt && ./sort 3.txt && ./sort 4.txt && ./sort 5.txt && ./sort 6.txt

clean:
	rm gerador sort *.txt
