#include <iostream>
//#include <windows->h>
#include "Grafo.h"
#include "Vertice.h"
#include "Arista.h"
using namespace std;

int main()
{

    int opc;
  
    //crear grafo padre e hijos
    //crear nodos de los hijo y aristas
    //meterlos en el padre
    
    Grafo *G = new Grafo();
    

    Grafo *G1 = new Grafo();

    G1->grafo_inserta_vertice(1,0,0,nullptr);
    G1->grafo_inserta_vertice(2,0,0,nullptr);
    G1->grafo_inserta_arista_bi(G1->grafo_get_vertice(1), G1->grafo_get_vertice(2), 1,0);

    Grafo *G2 = new Grafo();

    G2->grafo_inserta_vertice(1,0,0,nullptr);
    G2->grafo_inserta_vertice(2,0,0,nullptr);
    G2->grafo_inserta_arista_bi(G2->grafo_get_vertice(1), G2->grafo_get_vertice(2), 1,0);

    Grafo *G3 = new Grafo();

    G3->grafo_inserta_vertice(1,0,0,nullptr);
    G3->grafo_inserta_vertice(2,0,0,nullptr);
    G3->grafo_inserta_arista_bi(G3->grafo_get_vertice(1), G3->grafo_get_vertice(2), 1,0);

    G->grafo_inserta_vertice(1,0,0,G1);
    G->grafo_inserta_vertice(2,0,0,G2);
    G->grafo_inserta_vertice(3,0,0,G3);

    G->grafo_inserta_arista_bi(G->grafo_get_vertice(1), G->grafo_get_vertice(2), 1,3);
    G->grafo_inserta_arista_bi(G->grafo_get_vertice(2), G->grafo_get_vertice(3), 1,4);











    /*for(int i=1;i<=5;i++){
        G1->grafo_inserta_vertice(i,0,0,nullptr);
    }

    int peso=1;*/

    /*//se rellenan las aristas horizontalmente
    int ancho=3,largo=3;
    for(int i=0;i<ancho;i++){
        for(int j=0;j<largo;j++){
            if(j!=0){
                G1->grafo_inserta_arista_bi(G1->grafo_get_vertice(i),G1->grafo_get_vertice(j),peso);
            }
        }
    }*/

    /*G1->grafo_inserta_arista_bi(G1->grafo_get_vertice(1), G1->grafo_get_vertice(2), 1);
    G1->grafo_inserta_arista_bi(G1->grafo_get_vertice(1), G1->grafo_get_vertice(5), 1);
    G1->grafo_inserta_arista_bi(G1->grafo_get_vertice(1), G1->grafo_get_vertice(4), 1);
    G1->grafo_inserta_arista_bi(G1->grafo_get_vertice(2), G1->grafo_get_vertice(4), 1);
    G1->grafo_inserta_arista_bi(G1->grafo_get_vertice(2), G1->grafo_get_vertice(5), 1);
    G1->grafo_inserta_arista_bi(G1->grafo_get_vertice(2), G1->grafo_get_vertice(6), 1);
    G1->grafo_inserta_arista_bi(G1->grafo_get_vertice(2), G1->grafo_get_vertice(3), 1);
    G1->grafo_inserta_arista_bi(G1->grafo_get_vertice(3), G1->grafo_get_vertice(5), 1);
    G1->grafo_inserta_arista_bi(G1->grafo_get_vertice(3), G1->grafo_get_vertice(6), 1);
    G1->grafo_inserta_arista_bi(G1->grafo_get_vertice(4), G1->grafo_get_vertice(5), 1);
    G1->grafo_inserta_arista_bi(G1->grafo_get_vertice(4), G1->grafo_get_vertice(8), 1);
    G1->grafo_inserta_arista_bi(G1->grafo_get_vertice(4), G1->grafo_get_vertice(7), 1);
    G1->grafo_inserta_arista_bi(G1->grafo_get_vertice(5), G1->grafo_get_vertice(6), 1);
    G1->grafo_inserta_arista_bi(G1->grafo_get_vertice(5), G1->grafo_get_vertice(7), 1);
    G1->grafo_inserta_arista_bi(G1->grafo_get_vertice(5), G1->grafo_get_vertice(8), 1);
    G1->grafo_inserta_arista_bi(G1->grafo_get_vertice(5), G1->grafo_get_vertice(9), 1);
    G1->grafo_inserta_arista_bi(G1->grafo_get_vertice(6), G1->grafo_get_vertice(8), 1);
    G1->grafo_inserta_arista_bi(G1->grafo_get_vertice(6), G1->grafo_get_vertice(9), 1);
    G1->grafo_inserta_arista_bi(G1->grafo_get_vertice(7), G1->grafo_get_vertice(8), 1);
    G1->grafo_inserta_arista_bi(G1->grafo_get_vertice(8), G1->grafo_get_vertice(9), 1);*/

   /* Grafo *G2 = new Grafo();
    
   for(int i=1;i<5;i++){
        G2->grafo_inserta_vertice(i,0,0,nullptr);
    }*/


    /*G2->grafo_inserta_arista_bi(G2->grafo_get_vertice(1), G2->grafo_get_vertice(2), 1);
    G2->grafo_inserta_arista_bi(G2->grafo_get_vertice(1), G2->grafo_get_vertice(4), 1);
    G2->grafo_inserta_arista_bi(G2->grafo_get_vertice(1), G2->grafo_get_vertice(3), 1);
    G2->grafo_inserta_arista_bi(G2->grafo_get_vertice(2), G2->grafo_get_vertice(3), 1);
    G2->grafo_inserta_arista_bi(G2->grafo_get_vertice(2), G2->grafo_get_vertice(4), 1);
    G2->grafo_inserta_arista_bi(G2->grafo_get_vertice(3), G2->grafo_get_vertice(4), 1);*/

    //Grafo *G3 = new Grafo();

    //G3->grafo_inserta_vertice(1,0,0,nullptr);

    //grafoLOD2
    /*Grafo *G = new Grafo();
    

     G->grafo_inserta_vertice(1,30,15,G1);
     G->grafo_inserta_vertice(2,30,15,G2);
     G->grafo_inserta_vertice(3,30,15,G3);


    G->grafo_inserta_arista_bi(G->grafo_get_vertice(1), G->grafo_get_vertice(2), 1, 4);
    G->grafo_inserta_arista_bi(G->grafo_get_vertice(2), G->grafo_get_vertice(3), 1, 5);
    
    cout << G->grafo_get_arista(4)->_peso << endl;

    cout << G->grafo_tamano() << endl;
    //cout << G->grafo_get_vertice(1)->get_lod1()->grafo_tamano() << endl;
    cout << G1->grafo_tamano() << endl;
    //cout << G->grafo_get_vertice(2)->get_lod1()->grafo_tamano() << endl;
    cout << G2->grafo_tamano() << endl;
    cout << "x:" << G->grafo_get_vertice(1)->get_coord_x() << ",y:" << G->grafo_get_vertice(1)->get_coord_y() << endl;

    G->grafo_get_arista(4)->_peso=5;
    
    std::cout << G->grafo_get_arista(4)->_peso << std::endl;*/

    /*int origen, destino;
           
                cout<<"Ingrese el id nombre del vertice origen: ";
                cin>>origen;
                cout<<"Ingrese id del nombre del vertice destino: ";
                cin>>destino;
                if(G->grafo_get_vertice(1)->get_lod1()->grafo_get_vertice(origen) == NULL || G->grafo_get_vertice(1)->get_lod1()->grafo_get_vertice(destino) == NULL)
                {
                    cout<<"Vertices invalidos"<<endl;
                }
                else
                {
                    Vertice *pv;
                    stack<Vertice*> algo=G->grafo_get_vertice(1)->get_lod1()->grafo_camino_corto_l2(G->grafo_get_vertice(1)->get_lod1()->grafo_get_vertice(origen), G->grafo_get_vertice(1)->get_lod1()->grafo_get_vertice(destino));
                    while(!algo.empty()){
                        pv=algo.top();
                        cout << pv->_id <<" -> ";
                        algo.pop();
                    }
                    cout<<endl;

                }

    do
    {
        cout<<"1. Ingresar Vertice"<<endl;
        cout<<"2. Ingresar arista"<<endl;
        cout<<"3. Lista de adyacencia"<<endl;
        cout<<"4. Tama�o"<<endl;
        cout<<"5. grafo_camino_corto_l2"<<endl;
        cout<<"6. Salir"<<endl;
        cout<<endl<<"Elija una opcion: ";
        cin>>opc;
        switch(opc)
        {
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
                        cout << pv->_id <<" -> ";
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
    while(opc != 9);*/
    delete G;
    //delete G2;
    //delete G3;
    return 0;
}
