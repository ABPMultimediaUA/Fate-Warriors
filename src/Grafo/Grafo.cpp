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