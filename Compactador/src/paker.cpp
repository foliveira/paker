#include <iostream>
#include "pk.h"
#include "unpk.h"

using namespace std;

int main(int argc, char *argv[]) 
{
	if(argc > 1)
	{
		if(!strcmp(argv[1], "-h"))
		{
			cout << "Paker - Compressão de ficheiros" << endl;
			cout << endl << "Para empacotar use:" << endl;
			cout << endl << argv[0] << " rle|lzss|mix repetition_bits|[position_bits coincidence_bits] <filename>" << endl;
			cout << endl << "ou para desempacotar:" << endl;
			cout << endl << argv[0] << " -u <filename>" << endl;
			cout << endl << "Para comprimir escolher um dos seguintes modos:" << endl;
			cout << endl << "\trle - Utilizar a te'cnica RLE sobre o ficheiro, ";
			cout << "e' necessa'rio fornecer o valore de repetition_bits (valores 4 por defeito)." << endl;
			cout << endl << "\tlzss - Utilizar a te'cnica LZSS sobre o ficheiro, ";
			cout << "e' necessa'rio fornecer os valores de position_bits e coincidence_bits (valores 10 e 4 por defeito)." << endl;
			cout << endl << "\tmix - Utilizar a te'cnica LZSS em conjunto com RLE sobre o ficheiro, ";
			cout << "e' necessa'rio fornecer os valores de repetition_bits, position_bits e coincidence_bits (valores 4, 10 e 4 por defeito)." << endl;
			cout << endl << endl << "ISEL 2008 - Fa'bio Oliveira [30979] e Renato Verissi'mo [30796]" << endl;

			return 0;
		}
		else if(!strcmp(argv[1], "-u"))
		{
			if (argc < 3) 
			{ 
				cout << "Use " << argv[0] << " -h para obter ajuda" << endl; 
				return 1; 
			}

			UnPk upk(argv[argc - 1]);
			int error = upk.init();
			
			if(error) 
				return error;
		    
			upk.go();
		}
		else 
		{
			if (argc < 4) 
			{ 
				cout << "Use " << argv[0] << " -h para obter ajuda" << endl; 
				return 1;
			}

			FileName iname = argv[argc - 1];
			FileName oname = iname.getBaseName();

			oname.addExtension(pk_ext);

			Pk pk(iname, oname);
			int error = pk.init();
			
			if(error) 
				return error;

			pk.go(argc - 2, argv + 1, iname.getExtension());
		}
	}
	else
	{
		cout << "Use " << argv[0] << " -h para obter ajuda" << endl; 	
		return 1;
	}
}