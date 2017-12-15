#include <iostream>
//#include <windows->h>
#include "Grafo.h"
#include "Vertice.h"

using namespace std;

int main()
{
    Grafo *G = new Grafo();
    int opc;

    G->grafo_inserta_vertice(1); //NodoA
    G->grafo_inserta_vertice(2); //PasilloB
    G->grafo_inserta_vertice(3); //NodoC
    G->grafo_inserta_vertice(4); //PasilloD
    G->grafo_inserta_vertice(5); //NodoG
    G->grafo_inserta_vertice(6); //PasilloJ
    G->grafo_inserta_vertice(7); //NodoN
    G->grafo_inserta_vertice(8); //PasilloE
    G->grafo_inserta_vertice(9); //NodoH
    G->grafo_inserta_vertice(10); //PasilloK
    G->grafo_inserta_vertice(11); //NodoO
    G->grafo_inserta_vertice(12); //PasilloL
    G->grafo_inserta_vertice(13); //NodoP
    G->grafo_inserta_vertice(14); //PasilloR
    G->grafo_inserta_vertice(15); //NodoS
    G->grafo_inserta_vertice(16); //PasilloT
    G->grafo_inserta_vertice(17); //NodoU
    G->grafo_inserta_vertice(18); //PasilloF
    G->grafo_inserta_vertice(19); //NodoI
    G->grafo_inserta_vertice(20); //PasilloM
    G->grafo_inserta_vertice(21); //NodoQ
    G->grafo_inserta_vertice(22); //PasilloAux1
    G->grafo_inserta_vertice(23); //PasilloAux2

    G->grafo_inserta_arista_bi(G->grafo_get_vertice(1), G->grafo_get_vertice(2), 1);
    //G->grafo_inserta_arista_bi(G->grafo_get_vertice(2), G->grafo_get_vertice(1), 1);

    G->grafo_inserta_arista_bi(G->grafo_get_vertice(2), G->grafo_get_vertice(3), 1);
    //G->grafo_inserta_arista_bi(G->grafo_get_vertice(3), G->grafo_get_vertice(2), 1);

    G->grafo_inserta_arista_bi(G->grafo_get_vertice(3), G->grafo_get_vertice(4), 1);
    //G->grafo_inserta_arista_bi(G->grafo_get_vertice(4), G->grafo_get_vertice(3), 1);

    G->grafo_inserta_arista_bi(G->grafo_get_vertice(4), G->grafo_get_vertice(5), 1);
   // G->grafo_inserta_arista_bi(G->grafo_get_vertice(5), G->grafo_get_vertice(4), 1);

    G->grafo_inserta_arista_bi(G->grafo_get_vertice(5), G->grafo_get_vertice(6), 1);
   // G->grafo_inserta_arista_bi(G->grafo_get_vertice(6), G->grafo_get_vertice(5), 1);

    G->grafo_inserta_arista_bi(G->grafo_get_vertice(6), G->grafo_get_vertice(7), 3);
  //  G->grafo_inserta_arista_bi(G->grafo_get_vertice(7), G->grafo_get_vertice(6), 3);

    G->grafo_inserta_arista_bi(G->grafo_get_vertice(3), G->grafo_get_vertice(8), 1);
  //  G->grafo_inserta_arista_bi(G->grafo_get_vertice(8), G->grafo_get_vertice(3), 1);

    G->grafo_inserta_arista_bi(G->grafo_get_vertice(8), G->grafo_get_vertice(9), 1);
   // G->grafo_inserta_arista_bi(G->grafo_get_vertice(9), G->grafo_get_vertice(8), 1);

    G->grafo_inserta_arista_bi(G->grafo_get_vertice(9), G->grafo_get_vertice(10), 10);
  //  G->grafo_inserta_arista_bi(G->grafo_get_vertice(10), G->grafo_get_vertice(9), 10);

    G->grafo_inserta_arista_bi(G->grafo_get_vertice(11), G->grafo_get_vertice(10), 10);
 //   G->grafo_inserta_arista_bi(G->grafo_get_vertice(10), G->grafo_get_vertice(11), 10);

    G->grafo_inserta_arista_bi(G->grafo_get_vertice(9), G->grafo_get_vertice(12), 10);
 //   G->grafo_inserta_arista_bi(G->grafo_get_vertice(12), G->grafo_get_vertice(9), 10);

    G->grafo_inserta_arista_bi(G->grafo_get_vertice(12), G->grafo_get_vertice(13), 10);
  //  G->grafo_inserta_arista_bi(G->grafo_get_vertice(13), G->grafo_get_vertice(12), 10);

    G->grafo_inserta_arista_bi(G->grafo_get_vertice(13), G->grafo_get_vertice(14), 10);
  //  G->grafo_inserta_arista_bi(G->grafo_get_vertice(14), G->grafo_get_vertice(13), 10);

    G->grafo_inserta_arista_bi(G->grafo_get_vertice(14), G->grafo_get_vertice(15), 10);
   // G->grafo_inserta_arista_bi(G->grafo_get_vertice(15), G->grafo_get_vertice(14), 10);

    G->grafo_inserta_arista_bi(G->grafo_get_vertice(15), G->grafo_get_vertice(16), 10);
  //  G->grafo_inserta_arista_bi(G->grafo_get_vertice(16), G->grafo_get_vertice(15), 10);

    G->grafo_inserta_arista_bi(G->grafo_get_vertice(16), G->grafo_get_vertice(17), 10);
  //  G->grafo_inserta_arista_bi(G->grafo_get_vertice(17), G->grafo_get_vertice(16), 10);

    G->grafo_inserta_arista_bi(G->grafo_get_vertice(3), G->grafo_get_vertice(18), 10);
  //  G->grafo_inserta_arista_bi(G->grafo_get_vertice(18), G->grafo_get_vertice(3), 10);

    G->grafo_inserta_arista_bi(G->grafo_get_vertice(18), G->grafo_get_vertice(19), 10);
 //   G->grafo_inserta_arista_bi(G->grafo_get_vertice(19), G->grafo_get_vertice(18), 10);

    G->grafo_inserta_arista_bi(G->grafo_get_vertice(19), G->grafo_get_vertice(20), 10);
 //   G->grafo_inserta_arista_bi(G->grafo_get_vertice(20), G->grafo_get_vertice(19), 10);

    G->grafo_inserta_arista_bi(G->grafo_get_vertice(20), G->grafo_get_vertice(21), 10);
 //   G->grafo_inserta_arista_bi(G->grafo_get_vertice(21), G->grafo_get_vertice(20), 10);

    G->grafo_inserta_arista_bi(G->grafo_get_vertice(5), G->grafo_get_vertice(22), 10);
    G->grafo_inserta_arista_bi(G->grafo_get_vertice(22), G->grafo_get_vertice(11), 10);
  //  G->grafo_inserta_arista_bi(G->grafo_get_vertice(11), G->grafo_get_vertice(22), 10);
  //  G->grafo_inserta_arista_bi(G->grafo_get_vertice(22), G->grafo_get_vertice(5), 10);

    G->grafo_inserta_arista_bi(G->grafo_get_vertice(7), G->grafo_get_vertice(23), 10);
    G->grafo_inserta_arista_bi(G->grafo_get_vertice(23), G->grafo_get_vertice(17), 10);
  // G->grafo_inserta_arista_bi(G->grafo_get_vertice(17), G->grafo_get_vertice(23), 20);
   // G->grafo_inserta_arista_bi(G->grafo_get_vertice(23), G->grafo_get_vertice(7), 20);

    do
    {
        cout<<"1. Ingresar Vertice"<<endl;
        cout<<"2. Ingresar arista"<<endl;
        cout<<"3. Lista de adyacencia"<<endl;
        cout<<"4. Tamaño"<<endl;
        cout<<"5. grafo_camino_corto_l2"<<endl;
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
            G->grafo_inserta_vertice(nombre);
            break;
        }
        case 2:
        {
            int origen, destino;
            int peso;
            if(G->grafo_vacio())
            {
                cout<<"El grafo esta grafo_vacio"<<endl;
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

                if(G->grafo_get_vertice(origen) == NULL || G->grafo_get_vertice(destino) == NULL)
                {
                    cout<<"Uno de los vertices no es valido"<<endl;
                }
                else
                {
                    G->grafo_inserta_arista_bi(G->grafo_get_vertice(origen), G->grafo_get_vertice(destino), peso);
                }
            }
            break;
        }
        case 3:
        {
            if(G->grafo_vacio())
            {
                cout<<"El grafo esta grafo_vacio"<<endl;
            }
            else
            {
                G->grafo_lista_adyacencia();
            }
            break;
        }
        case 4:
        {
            if(G->grafo_vacio())
            {
                cout<<"El grafo esta grafo_vacio"<<endl;
            }
            else
            {
                cout<<"Tamano: "<<G->grafo_tamano()<<endl;
            }
            break;
        }
        case 5:
        {
            int origen, destino;
            if(G->grafo_vacio())
            {
                cout<<"El grafo esta grafo_vacio"<<endl;
            }
            else
            {
                cout<<"Ingrese el id nombre del vertice origen: ";
                cin.ignore();
                cin>>origen;
                cout<<"Ingrese id del nombre del vertice destino: ";
                cin>>destino;
                if(G->grafo_get_vertice(origen) == NULL || G->grafo_get_vertice(destino) == NULL)
                {
                    cout<<"Vertices invalidos"<<endl;
                }
                else
                {
                    Vertice *pv;
                    stack<Vertice*> algo=G->grafo_camino_corto_l2(G->grafo_get_vertice(origen), G->grafo_get_vertice(destino));
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
            if(G->grafo_vacio())
            {
                cout<<"El grafo esta grafo_vacio"<<endl;
            }
            else
            {
                cout<<"Ingrese id del nombre del vertice origen: ";
                cin.ignore();
                cin>>origen;
                cout<<"Ingrese id del nombre del vertice destino: ";
                cin>>destino;
                if(G->grafo_get_vertice(origen) == NULL || G->grafo_get_vertice(destino) == NULL)
                {
                    cout<<"Vertices no validos"<<endl;
                }
                else
                {
                    G->grafo_eliminar_arista(G->grafo_get_vertice(origen), G->grafo_get_vertice(destino));
                }
            }
            break;
        }
        case 7:
        {
            if(G->grafo_vacio())
            {
                cout<<"El grafo esta grafo_vacio"<<endl;
            }
            else
            {
               G->grafo_anular();
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
