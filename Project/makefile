#functional compile cmd
#g++ -o project main.cpp file_management.cpp

SRC = ./src/
HDR = ./hdr/
RSC = ./rsc/

me:
	g++ -o project $(SRC)main.cpp $(SRC)file_management.cpp $(SRC)U_type_functions.cpp $(SRC)D_type_functions.cpp

.PHONY = clean
clean:
	rm -rf project
