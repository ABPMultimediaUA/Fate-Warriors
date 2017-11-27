#include <iostream>
//#include <windows->h>
#include "Grafo.h"
#include "Vertice.h"

using namespace std;

int main()
{
    Grafo *G = new Grafo();
    int opc;

    G->InsertaVertice(1); //NodoA
    G->InsertaVertice(2); //PasilloB
    G->InsertaVertice(3); //NodoC
    G->InsertaVertice(4); //PasilloD
    G->InsertaVertice(5); //NodoG
    G->InsertaVertice(6); //PasilloJ
    G->InsertaVertice(7); //NodoN
    G->InsertaVertice(8); //PasilloE
    G->InsertaVertice(9); //NodoH
    G->InsertaVertice(10); //PasilloK
    G->InsertaVertice(11); //NodoO
    G->InsertaVertice(12); //PasilloL
    G->InsertaVertice(13); //NodoP
    G->InsertaVertice(14); //PasilloR
    G->InsertaVertice(15); //NodoS
    G->InsertaVertice(16); //PasilloT
    G->InsertaVertice(17); //NodoU
    G->InsertaVertice(18); //PasilloF
    G->InsertaVertice(19); //NodoI
    G->InsertaVertice(20); //PasilloM
    G->InsertaVertice(21); //NodoQ
    G->InsertaVertice(22); //PasilloAux1
    G->InsertaVertice(23); //PasilloAux2

    G->InsertaAristaBi(G->GetVertice(1), G->GetVertice(2), 1);
    //G->InsertaAristaBi(G->GetVertice(2), G->GetVertice(1), 1);

    G->InsertaAristaBi(G->GetVertice(2), G->GetVertice(3), 1);
    //G->InsertaAristaBi(G->GetVertice(3), G->GetVertice(2), 1);

    G->InsertaAristaBi(G->GetVertice(3), G->GetVertice(4), 1);
    //G->InsertaAristaBi(G->GetVertice(4), G->GetVertice(3), 1);

    G->InsertaAristaBi(G->GetVertice(4), G->GetVertice(5), 1);
   // G->InsertaAristaBi(G->GetVertice(5), G->GetVertice(4), 1);

    G->InsertaAristaBi(G->GetVertice(5), G->GetVertice(6), 1);
   // G->InsertaAristaBi(G->GetVertice(6), G->GetVertice(5), 1);

    G->InsertaAristaBi(G->GetVertice(6), G->GetVertice(7), 3);
  //  G->InsertaAristaBi(G->GetVertice(7), G->GetVertice(6), 3);

    G->InsertaAristaBi(G->GetVertice(3), G->GetVertice(8), 1);
  //  G->InsertaAristaBi(G->GetVertice(8), G->GetVertice(3), 1);

    G->InsertaAristaBi(G->GetVertice(8), G->GetVertice(9), 1);
   // G->InsertaAristaBi(G->GetVertice(9), G->GetVertice(8), 1);

    G->InsertaAristaBi(G->GetVertice(9), G->GetVertice(10), 10);
  //  G->InsertaAristaBi(G->GetVertice(10), G->GetVertice(9), 10);

    G->InsertaAristaBi(G->GetVertice(11), G->GetVertice(10), 10);
 //   G->InsertaAristaBi(G->GetVertice(10), G->GetVertice(11), 10);

    G->InsertaAristaBi(G->GetVertice(9), G->GetVertice(12), 10);
 //   G->InsertaAristaBi(G->GetVertice(12), G->GetVertice(9), 10);

    G->InsertaAristaBi(G->GetVertice(12), G->GetVertice(13), 10);
  //  G->InsertaAristaBi(G->GetVertice(13), G->GetVertice(12), 10);

    G->InsertaAristaBi(G->GetVertice(13), G->GetVertice(14), 10);
  //  G->InsertaAristaBi(G->GetVertice(14), G->GetVertice(13), 10);

    G->InsertaAristaBi(G->GetVertice(14), G->GetVertice(15), 10);
   // G->InsertaAristaBi(G->GetVertice(15), G->GetVertice(14), 10);

    G->InsertaAristaBi(G->GetVertice(15), G->GetVertice(16), 10);
  //  G->InsertaAristaBi(G->GetVertice(16), G->GetVertice(15), 10);

    G->InsertaAristaBi(G->GetVertice(16), G->GetVertice(17), 10);
  //  G->InsertaAristaBi(G->GetVertice(17), G->GetVertice(16), 10);

    G->InsertaAristaBi(G->GetVertice(3), G->GetVertice(18), 10);
  //  G->InsertaAristaBi(G->GetVertice(18), G->GetVertice(3), 10);

    G->InsertaAristaBi(G->GetVertice(18), G->GetVertice(19), 10);
 //   G->InsertaAristaBi(G->GetVertice(19), G->GetVertice(18), 10);

    G->InsertaAristaBi(G->GetVertice(19), G->GetVertice(20), 10);
 //   G->InsertaAristaBi(G->GetVertice(20), G->GetVertice(19), 10);

    G->InsertaAristaBi(G->GetVertice(20), G->GetVertice(21), 10);
 //   G->InsertaAristaBi(G->GetVertice(21), G->GetVertice(20), 10);

    G->InsertaAristaBi(G->GetVertice(5), G->GetVertice(22), 10);
    G->InsertaAristaBi(G->GetVertice(22), G->GetVertice(11), 10);
  //  G->InsertaAristaBi(G->GetVertice(11), G->GetVertice(22), 10);
  //  G->InsertaAristaBi(G->GetVertice(22), G->GetVertice(5), 10);

    G->InsertaAristaBi(G->GetVertice(7), G->GetVertice(23), 10);
    G->InsertaAristaBi(G->GetVertice(23), G->GetVertice(17), 10);
  // G->InsertaAristaBi(G->GetVertice(17), G->GetVertice(23), 20);
   // G->InsertaAristaBi(G->GetVertice(23), G->GetVertice(7), 20);

    do
    {
        cout<<"1. Ingresar Vertice"<<endl;
        cout<<"2. Ingresar arista"<<endl;
        cout<<"3. Lista de adyacencia"<<endl;
        cout<<"4. Tamaño"<<endl;
        cout<<"5. CaminoCortoL2"<<endl;
        cout<<"6. Salir"<<endl;
        cout<<endl<<"Elija una opcion: ";
        cin>>opc;
        switch(opc)
        {
        case 1:
        {
            int nombre;
            cout<<"Ingrese la id nombre del vertice: ";
            cin.ignore();
            cin>>nombre;
            G->InsertaVertice(nombre);
            break;
        }
        case 2:
        {
            int origen, destino;
            int peso;
            if(G->Vacio())
            {
                cout<<"El grafo esta vacio"<<endl;
            }
            else
            {
                cout<<"Ingrese id del nombre del vertice origen: ";
                cin.ignore();
                cin>>origen;
                cout<<"Ingrese id del nombre del vertice destino: ";
                cin>>destino;
                cout<<"Ingrese el peso: ";
                cin>>peso;

                if(G->GetVertice(origen) == NULL || G->GetVertice(destino) == NULL)
                {
                    cout<<"Uno de los vertices no es valido"<<endl;
                }
                else
                {
                    G->InsertaAristaBi(G->GetVertice(origen), G->GetVertice(destino), peso);
                }
            }
            break;
        }
        case 3:
        {
            if(G->Vacio())
            {
                cout<<"El grafo esta vacio"<<endl;
            }
            else
            {
                G->ListaAdyacencia();
            }
            break;
        }
        case 4:
        {
            if(G->Vacio())
            {
                cout<<"El grafo esta vacio"<<endl;
            }
            else
            {
                cout<<"Tamano: "<<G->Tamano()<<endl;
            }
            break;
        }
        case 5:
        {
            int origen, destino;
            if(G->Vacio())
            {
                cout<<"El grafo esta vacio"<<endl;
            }
            else
            {
                cout<<"Ingrese el id nombre del vertice origen: ";
                cin.ignore();
                cin>>origen;
                cout<<"Ingrese id del nombre del vertice destino: ";
                cin>>destino;
                if(G->GetVertice(origen) == NULL || G->GetVertice(destino) == NULL)
                {
                    cout<<"Vertices invalidos"<<endl;
                }
                else
                {
                    Vertice *pv;
                    stack<Vertice*> algo=G->CaminoCortoL2(G->GetVertice(origen), G->GetVertice(destino));
                    while(!algo.empty()){
                        pv=algo.top();
                        cout << pv->id <<" -> ";
                        algo.pop();
                    }
                    cout<<endl;

                }
            }
            break;
        }
        case 6:
        {
            int origen, destino;
            if(G->Vacio())
            {
                cout<<"El grafo esta vacio"<<endl;
            }
            else
            {
                cout<<"Ingrese id del nombre del vertice origen: ";
                cin.ignore();
                cin>>origen;
                cout<<"Ingrese id del nombre del vertice destino: ";
                cin>>destino;
                if(G->GetVertice(origen) == NULL || G->GetVertice(destino) == NULL)
                {
                    cout<<"Vertices no validos"<<endl;
                }
                else
                {
                    G->EliminarArista(G->GetVertice(origen), G->GetVertice(destino));
                }
            }
            break;
        }
        case 7:
        {
            if(G->Vacio())
            {
                cout<<"El grafo esta vacio"<<endl;
            }
            else
            {
               G->Anular();
            }
            break;
        }   
        case 9:
        {

            break;
        }
        default:
        {
            cout<<"Elija una opcion valida"<<endl;
        }
        }
    }
    while(opc != 9);
    delete G;
    return 0;
}
