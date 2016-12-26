# This is the Makefile to use for Homework Assignment #9
# To use, at the prompt, type:
#
#       make Calc               # This will make executable calc
# or
#       make Driver             # This will make executable driver
# or
#       make clean              # This will safely remove old stuff

DIR=$(HOME)/../public/hw9

all:	Driver Calc

Calc:	Calc.o Decin.o Main.o Namein.o
	g++ -Wall -pedantic -o Calc -g Calc.o Decin.o Main.o Namein.o
	touch Calc.datafile

Calc.o:	Calc.c Calc.h Decin.h Tree.h List.h Stack.h SymTab.h Tree.c
	g++ -Wall -pedantic -g -c Calc.c

Driver:	Driver.o 
	g++ -Wall -pedantic -o Driver Driver.o 
	touch Driver.datafile

Driver.o:	Driver.c Driver.h Tree.h Tree.c SymTab.h
	g++ -Wall -pedantic -g -c Driver.c

Decin.o:	Decin.c Decin.h
	g++ -Wall -pedantic -g -c Decin.c

Main.o:	Main.c Calc.h Tree.h List.h Stack.h SymTab.h
	g++ -Wall -pedantic -g -c Main.c

Namein.o:	Namein.h Namein.c
	g++ -Wall -pedantic -g -c Namein.c

valgrind_Calc: Calc
	valgrind --leak-check=full --read-var-info=yes \
	    --show-reachable=yes ./Calc $(DEBUG)

valgrind_Driver: Driver
	valgrind --leak-check=full --read-var-info=yes \
	    --show-reachable=yes ./Driver $(DEBUG)

clean:
	rm -f *.o Calc Driver
	make fresh

new:
	make clean
	make

backup:	Makefile *.[ch]
	cp Makefile *.[ch] backup

directories:
	mkdir $(HOME)/hw9
	mkdir $(HOME)/hw9/backup

fresh:
	rm -f Calc.datafile Driver.datafile
	touch Calc.datafile Driver.datafile

install:
	cp $(DIR)/Makefile $(DIR)/Main.c \
	$(DIR)/Decin.c $(DIR)/Stack.c $(DIR)/Calc.c \
	$(DIR)/Namein.c $(DIR)/Tree.c.empty $(DIR)/List.c \
	$(DIR)/Decin.h $(DIR)/Stack.h $(DIR)/Calc.h \
	$(DIR)/Namein.h $(DIR)/List.h $(DIR)/SymTab.h \
	$(DIR)/Tree.h $(DIR)/.hw9.vcproj $(DIR)/.hw9.sln \
	$(DIR)/.cproject $(DIR)/.project \
	$(DIR)/*commands $(HOME)/hw9

public:
	make new
	chmod 700 $(DIR)
	cp -p .cproject .project .hw9.vcproj .hw9.sln Makefile \
	Calc alphabet* Driver *.h *.c* *commands $(DIR)
	rm -f $(DIR)/Tree.c
	rm -f $(DIR)/Driver.[ch]
	#
	strip $(DIR)/Calc $(DIR)/Driver
	#
	chmod 600 $(DIR)/*
	chmod 711 $(DIR)/Calc $(DIR)/Driver
	chmod 644 $(DIR)/Calc.h $(DIR)/Calc.c \
		$(DIR)/Decin.h $(DIR)/Decin.c \
		$(DIR)/List.h $(DIR)/List.c \
		$(DIR)/Namein.h $(DIR)/Namein.c \
		$(DIR)/Stack.h $(DIR)/Stack.c \
		$(DIR)/Main.c \
		$(DIR)/SymTab.h \
		$(DIR)/Tree.h \
		$(DIR)/Makefile \
		$(DIR)/alphabet \
		$(DIR)/alphabet.rev \
		$(DIR)/Tree.c.empty $(DIR)/*commands \
		$(DIR)/.cproject $(DIR)/.project \
		$(DIR)/.hw9.vcproj $(DIR)/.hw9.sln
	#
	#rm -rf $(HOME)/../cs12xzz/hw9/*

	# move html files to public_html directory
	rm -r $(HOME)/public_html/hw9/
	mkdir $(HOME)/public_html/hw9
	cp *html $(HOME)/public_html/hw9
	chmod 744 $(HOME)/public_html/hw9/*html
	chmod 755 $(HOME)/public_html/hw9/


	# When assignment is ready to be viewed be students
	chmod 755 $(DIR)
	# scp -p Makefile *.[ch] $(DIR)/Calc $(DIR)/Driver cs12xzz@ieng6-201:~/hw9
