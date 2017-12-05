#include "Scriptor.h"
#include <sstream>

Scriptor::Scriptor(std::string _i_fichero){ 
	crear(_i_fichero);
}

void Scriptor::crear(std::string _i_fichero){
	std::ifstream fichero(_i_fichero);
	int ikey;
	std::string value,key, line;

	if(fichero){
	    while (!fichero.eof()){
	    	getline(fichero, line);
            std::istringstream ss(line);

	        std::string name;
	        short var1;

	        ss >> name >> var1;

	        if (name == "#")
	        	continue;

	        if(name != "")
	        first[name] = var1;
	        
	        std::cout << name << var1 << std::endl << std::endl;
	    }
	}
	int i = 0;
	for (std::map<std::string , int>::iterator itr = first.begin(); itr != first.end(); ++itr){
    	std::cout<<itr->first<<"->"<<itr->second<<std::endl;//display the key/value pair
    	i++;
	}
	std::cout << i << "valores" << std::endl;
}


short Scriptor::Dame_valor_de(std::string _i_nombre){
	return first[_i_nombre];
}

Scriptor::~Scriptor(){}
