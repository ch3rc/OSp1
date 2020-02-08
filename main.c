#include "flags.h"

int main(int argc, char *argv[])
{

	initOptions();

	setOptions(argc, argv);

	print();
	return 0;

}	
