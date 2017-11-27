#include "Grafo.h"
#include "Vertice.h"
#include "Arista.h"
#include <queue>
#include <list>
#include <iostream>
Grafo::Grafo(){
	h = NULL;
}

Grafo::~Grafo(){
	this->Anular();
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

Vertice *Grafo::GetVertice(int id){
	Vertice *aux;
	aux = h;
	while(aux!=NULL){
		if(aux->id == id){
			return aux;
		}
		aux=aux->sig;
		
	}
	return NULL;
}

void Grafo::InsertaVertice(int id){
	Vertice *nuevo = new Vertice;
	nuevo->id=id;
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
void Grafo::InsertaAristaBi(Vertice *origen, Vertice *destino, int peso){
	InsertaArista(origen,destino,peso);
	InsertaArista(destino,origen,peso);
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
		std::cout << VertAux->id << " -> ";
		ArisAux = VertAux->ady;
		while(ArisAux != NULL){
			std::cout << ArisAux->ady->id << " -> " ;
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

void Grafo::Anular(){

	Vertice *aux;

	while(h!=NULL){
		aux=h;
		EliminarArista(h,h->sig);
		//std::cout<< aux->id << std::endl;
		h=h->sig;
		//std::cout<< h->id << std::endl;
		
		delete(aux);
	}
}


void Grafo::EliminarArista(Vertice *origen, Vertice *destino){

	bool flag=false;

	Arista *actual, *anterior;

	actual = origen->ady;

	if(actual==NULL){
		std::cout << "Vertices no na" << std::endl;
	}
	else if(actual->ady==destino){
std::cout << "Vertices no naasdf" << std::endl;
		origen->ady = actual->sig;
		delete(actual);
		EliminarArista(destino,origen);
	}
	else
	{
		while(actual->ady != NULL){
			if(actual->ady==destino){

				flag=true;
				anterior->sig=actual->sig;
				delete(actual);
				std::cout << "Se ha eliminado la arista" << std::endl;
				EliminarArista(destino,origen);
				break;
			}
			if(actual->sig != NULL){
				anterior=actual;
				actual=actual->sig;
			}else{
				break;
			}
		}
		if(!flag)
		{
			std::cout << "Vertices no conectados" << std::endl;
		}

	}

}

//TO-DO: devolver la lista de vertices a seguir DONE

std::stack<Vertice*> Grafo::CaminoCortoL2(Vertice *origen, Vertice *destino){

	Vertice *VerticeActual;
	Vertice *DestinoActual;

	Arista *aux;

	typedef std::pair<Vertice*, Vertice*> VerticeVertice;
	std::queue<Vertice*> cola;
	std::stack<VerticeVertice> pila;
	std::stack<Vertice*> recorrido;
	std::list<Vertice*> lista;
	std::list<Vertice*>::iterator i;

	bool band,band2,band3=false;

	cola.push(origen);

	while(!cola.empty()){
		band=false;
		VerticeActual=cola.front();
		cola.pop();
		for(i=lista.begin();i!=lista.end();i++){
			if(VerticeActual == *i){
				band=true;
			}
		}
		if(band==false){
			if(VerticeActual==destino){
				band3=true;
				DestinoActual=destino;
				while(!pila.empty()){
					//pila que sera la que se devuelva
					recorrido.push(DestinoActual);
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
				band2=false;
				for(i=lista.begin();i!=lista.end();i++){
					if(aux->ady == *i){
						band2=true;
					}
				}
				if(band2==false){
					cola.push(aux->ady);
					pila.push(VerticeVertice(VerticeActual, aux->ady));
				}
				aux=aux->sig;
			}

		}
	}

	if(band3==false){
		std::cout << "no hay na entre esos dos " << std::endl;
	}
	return recorrido;
}
