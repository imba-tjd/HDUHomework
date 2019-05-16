objects = md5.o main.o

main : $(objects)
	gcc $(objects) -o main.exe

.PHONY : clean run ln
clean :
	-rm -f *.o *.exe
run :
	./main.exe
	md5sum plain.txt
ln :
	# -cmd /c 'mklink plain.txt ../DES/桃花源记.txt'
	-ln -s ../DES/桃花源记.txt plain.txt
