#ifndef VERTICE_H
#define VERTICE_H

class Arista;
class Vertice
{
	public:

	  Vertice *sig;
	  Arista *ady;
	  std::string nombre;
	  int id;

	  Vertice();
	  virtual ~Vertice();
};



#endif