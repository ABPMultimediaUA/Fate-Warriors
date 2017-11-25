#include "Grafo.h"

void Grafo::Inicializa(){
	h = NULL;
}

bool Grafo::Vacio(){
	if(h==NULL){
		return true;
	}
	else{
		return false;
	}
}

int Grafo::Tamano(){
	int cont=0;
	Vertice *aux;
	aux = h;
	while(aux!=NULL){
		cont++;
		aux=aux->sig;
	}
	return cont;
}

Vertice *Grafo::GetVertice(std::string nombre){
	Vertice *aux;
	aux = h;
	while(aux!=NULL){
		if(aux->nombre == nombre){
			return aux;
		}
		aux=aux->sig;
		
	}
	return NULL;
}

void Grafo::InsertaVertice(std::string nombre){
	Vertice *nuevo = new Vertice;
	nuevo->nombre=nombre;
	nuevo->sig=NULL;
	nuevo->ady=NULL;

	if(Vacio()){
		h=nuevo;
	}
	else{
		Vertice *aux;
		aux=h;
		while(aux->sig!=NULL){
			aux = aux->sig;
		}
		aux->sig=nuevo;
	}

}

void Grafo::InsertaArista(Vertice *origen, Vertice *destino, int peso){
	Arista *nueva = new Arista;

	nueva->peso=peso;
	nueva->sig=NULL;
	nueva->ady=NULL;

	Arista *aux;

	aux=origen->ady;

	if(aux==NULL){
		origen->ady=nueva;
		nueva->ady=destino;
	}
	else{
		while(aux->sig!=NULL){
			aux= aux->sig;
		}
		aux->sig=nueva;
		nueva->ady=destino;
	}

}

void Grafo::ListaAdyacencia(){
	Vertice *VertAux;
	Arista *ArisAux;

	VertAux = h;

	while(VertAux != NULL){
		std::cout << VertAux->nombre << " -> ";
		ArisAux = VertAux->ady;
		while(ArisAux != NULL){
			std::cout << ArisAux->ady->nombre << " -> " ;
			ArisAux = ArisAux->sig;
		}
		VertAux = VertAux->sig;
		std::cout<<std::endl;
	}
}
/*void Grafo::RecorridoAnchura(Vertice *origen){
	
	int band, band2;

	Vertice *actual;

	std::queue<Vertice*> cola;
	std::list<Vertice*> lista;
	std::list<Vertice*>::iterator i;

	cola.push(origen);
	while(!cola.empty()){
		
		band=0;
		actual=cola.front();
		cola.pop();

		for(i=lista.begin();i!=lista.end();i++){
			if(*i==actual){
				band=1;
				break;

			}
		}
		if(band==0){
			std::cout << actual->nombre << ", ";
			lista.push_back(actual);

			Arista *aux;
			aux = actual->ady;
			while(aux!=NULL){
				band2=0;
				
				for(i=lista.begin();i!=lista.end();i++){
					
					if(aux->ady == *i){
						
						band2=1;
					}
				}
				if(band2==0){
					
					cola.push(aux->ady);
				}
				aux=aux->sig;
			}
		}
	}
	std::cout << std::endl;
}

void Grafo::RecorridoProfundidad(Vertice *origen){

	Vertice *actual;
	std::stack<Vertice*> pila;
	std::list<Vertice*> lista;
	std::list<Vertice*>::iterator i;
	pila.push(origen);
	int band=0,band2=0;

	while(!pila.empty()){
		band=0;
		actual=pila.top();
		pila.pop();
		for(i=lista.begin(); i!=lista.end();i++){
			if(*i==actual){
				band=1;
			}
		}
		if(band==0){
			std::cout << actual->nombre<<", ";
			lista.push_back(actual);

			Arista *aux;
			aux=actual->ady;

			while(aux!=NULL){
				band2=0;
				for(i=lista.begin();i!=lista.end();i++){
					if(*i==aux->ady){
						band2=1;
					}
				}
				if(band2==0){
					pila.push(aux->ady);
				}
				aux=aux->sig;
			}
		}
	}
	std::cout << std::endl;

}*/



//TO-DO: devolver la lista de vertices a seguir

void Grafo::CaminoCortoL2(Vertice *origen, Vertice *destino){

	Vertice *VerticeActual;
	Vertice *DestinoActual;

	Arista *aux;

	typedef std::pair<Vertice*, Vertice*> VerticeVertice;
	std::queue<Vertice*> cola;
	std::stack<VerticeVertice> pila;
	std::list<Vertice*> lista;
	std::list<Vertice*>::iterator i;

	int band,band2,band3=0;

	cola.push(origen);

	while(!cola.empty()){
		band=0;
		VerticeActual=cola.front();
		cola.pop();
		for(i=lista.begin();i!=lista.end();i++){
			if(VerticeActual == *i){
				band=1;
			}
		}
		if(band==0){
			if(VerticeActual==destino){
				band3=1;
				DestinoActual=destino;
				while(!pila.empty()){
					std::cout << DestinoActual->nombre << " <- ";
					while(!pila.empty() && pila.top().second!=DestinoActual){
						pila.pop();
					}
					if(!pila.empty()){
						DestinoActual=pila.top().first;
					}
				}
			}
			lista.push_back(VerticeActual);

			aux=VerticeActual->ady;

			while(aux!=NULL){
				band2=0;
				for(i=lista.begin();i!=lista.end();i++){
					if(aux->ady == *i){
						band2=1;
					}
				}
				if(band2==0){
					cola.push(aux->ady);
					pila.push(VerticeVertice(VerticeActual, aux->ady));
				}
				aux=aux->sig;
			}

		}
	}

	if(band3==0){
		std::cout << "no hay na entre esos dos " << std::endl;
	}
}
