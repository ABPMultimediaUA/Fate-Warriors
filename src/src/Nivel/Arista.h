#ifndef ARISTA_H
#define ARISTA_H

class Vertice;
class Arista
{
	public:
	  inline Arista * get_sig(){
	  	  return _sig;
	  }
	  inline Vertice * get_ady(){
	  	  return _ady;
	  }
	  inline float get_peso(){
		  return _peso;
	  }
	  inline int get_id(){
		  return _id;
	  }
	  inline void set_sig(Arista* _i_sig){
		  _sig=_i_sig;
	  }
	  inline void set_ady(Vertice* _i_ady){
		  _ady=_i_ady;
	  }
	  inline void set_peso(float _i_peso){
		  _peso=_i_peso;
	  }
	  inline void set_id(int _i_id){
		  _id=_i_id;
	  }
	  Arista();
	  ~Arista();

	private:
	  Arista *_sig;
	  Vertice *_ady;
	  float _peso;
	  int _id;
};



#endif