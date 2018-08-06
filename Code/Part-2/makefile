
execute:
	bison -d Sample.y
	flex scan.l
	gcc lex.yy.c Sample.tab.c -ll -lm -o ac_circuit_solver
	touch execute

clean:
	rm -rf execute ac_circuit_solver top.svg results.txt