#include <iostream>
//#include <windows.h>
#include "Grafo.h"

using namespace std;

int main()
{
    Grafo G;
    G.Inicializa();
    int opc;

    G.InsertaVertice("NodoA");
    G.InsertaVertice("PasilloB");
    G.InsertaVertice("NodoC");
    G.InsertaVertice("PasilloD");
    G.InsertaVertice("NodoG");
    G.InsertaVertice("PasilloJ");
    G.InsertaVertice("NodoN");
    G.InsertaVertice("PasilloE");
    G.InsertaVertice("NodoH");
    G.InsertaVertice("PasilloK");
    G.InsertaVertice("NodoO");
    G.InsertaVertice("PasilloL");
    G.InsertaVertice("NodoP");
    G.InsertaVertice("PasilloR");
    G.InsertaVertice("NodoS");
    G.InsertaVertice("PasilloT");
    G.InsertaVertice("NodoU");
    G.InsertaVertice("PasilloF");
    G.InsertaVertice("NodoI");
    G.InsertaVertice("PasilloM");
    G.InsertaVertice("NodoQ");
    G.InsertaVertice("PasilloAux1");
    G.InsertaVertice("PasilloAux2");

    G.InsertaArista(G.GetVertice("NodoA"), G.GetVertice("PasilloB"), 10);
    G.InsertaArista(G.GetVertice("PasilloB"), G.GetVertice("NodoA"), 10);

    G.InsertaArista(G.GetVertice("PasilloB"), G.GetVertice("NodoC"), 10);
    G.InsertaArista(G.GetVertice("NodoC"), G.GetVertice("PasilloB"), 10);

    G.InsertaArista(G.GetVertice("NodoC"), G.GetVertice("PasilloD"), 10);
    G.InsertaArista(G.GetVertice("PasilloD"), G.GetVertice("NodoC"), 10);

    G.InsertaArista(G.GetVertice("PasilloD"), G.GetVertice("NodoG"), 10);
    G.InsertaArista(G.GetVertice("NodoG"), G.GetVertice("PasilloD"), 10);

    G.InsertaArista(G.GetVertice("NodoG"), G.GetVertice("PasilloJ"), 10);
    G.InsertaArista(G.GetVertice("PasilloJ"), G.GetVertice("NodoG"), 10);

    G.InsertaArista(G.GetVertice("PasilloJ"), G.GetVertice("NodoN"), 30);
    G.InsertaArista(G.GetVertice("NodoN"), G.GetVertice("PasilloJ"), 30);

    G.InsertaArista(G.GetVertice("NodoC"), G.GetVertice("PasilloE"), 10);
    G.InsertaArista(G.GetVertice("PasilloE"), G.GetVertice("NodoC"), 10);

    G.InsertaArista(G.GetVertice("PasilloE"), G.GetVertice("NodoH"), 10);
    G.InsertaArista(G.GetVertice("NodoH"), G.GetVertice("PasilloE"), 10);

    G.InsertaArista(G.GetVertice("NodoH"), G.GetVertice("PasilloK"), 10);
    G.InsertaArista(G.GetVertice("PasilloK"), G.GetVertice("NodoH"), 10);

    G.InsertaArista(G.GetVertice("NodoO"), G.GetVertice("PasilloK"), 10);
    G.InsertaArista(G.GetVertice("PasilloK"), G.GetVertice("NodoO"), 10);

    G.InsertaArista(G.GetVertice("NodoH"), G.GetVertice("PasilloL"), 10);
    G.InsertaArista(G.GetVertice("PasilloL"), G.GetVertice("NodoH"), 10);

    G.InsertaArista(G.GetVertice("PasilloL"), G.GetVertice("NodoP"), 10);
    G.InsertaArista(G.GetVertice("NodoP"), G.GetVertice("PasilloL"), 10);

    G.InsertaArista(G.GetVertice("NodoP"), G.GetVertice("PasilloR"), 10);
    G.InsertaArista(G.GetVertice("PasilloR"), G.GetVertice("NodoP"), 10);

    G.InsertaArista(G.GetVertice("PasilloR"), G.GetVertice("NodoS"), 10);
    G.InsertaArista(G.GetVertice("NodoS"), G.GetVertice("PasilloR"), 10);

    G.InsertaArista(G.GetVertice("NodoS"), G.GetVertice("PasilloT"), 10);
    G.InsertaArista(G.GetVertice("PasilloT"), G.GetVertice("NodoS"), 10);

    G.InsertaArista(G.GetVertice("PasilloT"), G.GetVertice("NodoU"), 10);
    G.InsertaArista(G.GetVertice("NodoU"), G.GetVertice("PasilloT"), 10);

    G.InsertaArista(G.GetVertice("NodoC"), G.GetVertice("PasilloF"), 10);
    G.InsertaArista(G.GetVertice("PasilloF"), G.GetVertice("NodoC"), 10);

    G.InsertaArista(G.GetVertice("PasilloF"), G.GetVertice("NodoI"), 10);
    G.InsertaArista(G.GetVertice("NodoI"), G.GetVertice("PasilloF"), 10);

    G.InsertaArista(G.GetVertice("NodoI"), G.GetVertice("PasilloM"), 10);
    G.InsertaArista(G.GetVertice("PasilloM"), G.GetVertice("NodoI"), 10);

    G.InsertaArista(G.GetVertice("PasilloM"), G.GetVertice("NodoQ"), 10);
    G.InsertaArista(G.GetVertice("NodoQ"), G.GetVertice("PasilloM"), 10);

    G.InsertaArista(G.GetVertice("NodoG"), G.GetVertice("PasilloAux1"), 10);
    G.InsertaArista(G.GetVertice("PasilloAux1"), G.GetVertice("NodoO"), 10);
    G.InsertaArista(G.GetVertice("NodoO"), G.GetVertice("PasilloAux1"), 10);
    G.InsertaArista(G.GetVertice("PasilloAux1"), G.GetVertice("NodoG"), 10);

    G.InsertaArista(G.GetVertice("NodoN"), G.GetVertice("PasilloAux2"), 10);
    G.InsertaArista(G.GetVertice("PasilloAux2"), G.GetVertice("NodoU"), 10);
    G.InsertaArista(G.GetVertice("NodoU"), G.GetVertice("PasilloAux2"), 20);
    G.InsertaArista(G.GetVertice("PasilloAux2"), G.GetVertice("NodoN"), 20);

    do
    {
        cout<<"1. Ingresar Vertice"<<endl;
        cout<<"2. Ingresar arista"<<endl;
        cout<<"3. Lista de adyacencia"<<endl;
        cout<<"4. Tamaño"<<endl;
        /*cout<<"5. Eliminar vertice (no)"<<endl;
        cout<<"6. Eliminar arista (no)"<<endl;
        cout<<"7. Anular (no)"<<endl;*/
        cout<<"8. Recorrido en anchura"<<endl;
        cout<<"9. Recorrido en profundidad"<<endl;
        cout<<"10. Primero en anchura"<<endl;
        /*cout<<"11. Primero en profundidad"<<endl;
        cout<<"12. Primero el mejor"<<endl;*/
        cout<<"13. Salir"<<endl;
        cout<<endl<<"Elija una opcion: ";
        cin>>opc;
        switch(opc)
        {
        case 1:
        {
            string nombre;
            cout<<"Ingrese el nombre del vertice: ";
            cin.ignore();
            getline(cin, nombre, '\n');
            G.InsertaVertice(nombre);
            break;
        }
        case 2:
        {
            string origen, destino;
            int peso;
            if(G.Vacio())
            {
                cout<<"El grafo esta vacio"<<endl;
            }
            else
            {
                cout<<"Ingrese del nombre del vertice origen: ";
                cin.ignore();
                getline(cin, origen, '\n');
                cout<<"Ingrese el nombre del vertice destino: ";
                getline(cin, destino, '\n');
                cout<<"Ingrese el peso: ";
                cin>>peso;

                if(G.GetVertice(origen) == NULL || G.GetVertice(destino) == NULL)
                {
                    cout<<"Uno de los vertices no es valido"<<endl;
                }
                else
                {
                    G.InsertaArista(G.GetVertice(origen), G.GetVertice(destino), peso);
                }
            }
            break;
        }
        case 3:
        {
            if(G.Vacio())
            {
                cout<<"El grafo esta vacio"<<endl;
            }
            else
            {
                G.ListaAdyacencia();
            }
            break;
        }
        case 4:
        {
            if(G.Vacio())
            {
                cout<<"El grafo esta vacio"<<endl;
            }
            else
            {
                cout<<"Tamano: "<<G.Tamano()<<endl;
            }
            break;
        }
        /*case 5:
        {
            string nombre;
            system("cls");
            if(G.Vacio())
            {
                cout<<"El grafo esta vacio"<<endl;
            }
            else
            {
                cout<<"Ingrese el nombre del vertice a eliminar: ";
                cin.ignore();
                getline(cin, nombre, '\n');
                if(G.GetVertice(nombre) == NULL)
                {
                    cout<<"Vertice invalido"<<endl;
                }
                else
                {
                   G.EliminarVertice(G.GetVertice(nombre));
                }
            }
            cin.get();
            cin.get();
            break;
        }
        case 6:
        {
            string origen, destino;
            system("cls");
            if(G.Vacio())
            {
                cout<<"El grafo esta vacio"<<endl;
            }
            else
            {
                cout<<"Ingrese del nombre del vertice origen: ";
                cin.ignore();
                getline(cin, origen, '\n');
                cout<<"Ingrese el nombre del vertice destino: ";
                getline(cin, destino, '\n');
                if(G.GetVertice(origen) == NULL || G.GetVertice(destino) == NULL)
                {
                    cout<<"Vertices no validos"<<endl;
                }
                else
                {
                    G.EliminarArista(G.GetVertice(origen), G.GetVertice(destino));
                }
            }
            cin.get();
            cin.get();
            break;
        }
        case 7:
        {
            system("cls");
            if(G.Vacio())
            {
                cout<<"El grafo esta vacio"<<endl;
            }
            else
            {
               G.Anular();
            }
            cin.get();
            cin.get();
            break;
        }*/
        case 8:
        {
            string nombre;
            if(G.Vacio())
            {
                cout<<"El grafo esta vacio"<<endl;
            }
            else
            {
                cout<<"Ingrese el nombre del vertice inicial: ";
                cin.ignore();
                getline(cin, nombre, '\n');
                if(G.GetVertice(nombre) == NULL)
                {
                    cout<<"Ese vertice es invalido"<<endl;
                }
                else
                {
                    G.RecorridoAnchura(G.GetVertice(nombre));
                }
            }
            break;
        }
        case 9:
        {
            string nombre;
            if(G.Vacio())
            {
                cout<<"El grafo esta vacio"<<endl;
            }
            else
            {
                cout<<"Ingrese el nombre del vertice inicial: ";
                cin.ignore();
                getline(cin, nombre, '\n');
                if(G.GetVertice(nombre) == NULL)
                {
                    cout<<"Ese vertice es invalido"<<endl;
                }
                else
                {
                    G.RecorridoProfundidad(G.GetVertice(nombre));
                }
            }
            break;
        }
        case 10:
        {
            string origen, destino;
            if(G.Vacio())
            {
                cout<<"El grafo esta vacio"<<endl;
            }
            else
            {
                cout<<"Ingrese el nombre del vertice origen: ";
                cin.ignore();
                getline(cin, origen, '\n');
                cout<<"Ingrese el nombre del vertice destino: ";
                getline(cin, destino, '\n');
                if(G.GetVertice(origen) == NULL || G.GetVertice(destino) == NULL)
                {
                    cout<<"Vertices invalidos"<<endl;
                }
                else
                {
                    G.PrimeroAnchura(G.GetVertice(origen), G.GetVertice(destino));
                }
            }
            break;
        }
        /*case 11:
        {
            string origen, destino;
            system("cls");
            if(G.Vacio())
            {
                cout<<"El grafo esta vacio"<<endl;
            }
            else
            {
                cout<<"Ingrese el nombre del vertice origen: ";
                cin.ignore();
                getline(cin, origen, '\n');
                cout<<"Ingrese el nombre del vertice destino: ";
                getline(cin, destino, '\n');
                if(G.GetVertice(origen) == NULL || G.GetVertice(destino) == NULL)
                {
                    cout<<"Vertices invalidos"<<endl;
                }
                else
                {
                    G.PrimeroProfundidad(G.GetVertice(origen), G.GetVertice(destino));
                }
            }
            cin.get();
            cin.get();
            break;
        }
        case 12:
        {
            string origen, destino;
            system("cls");
            if(G.Vacio())
            {
                cout<<"El grafo esta vacio"<<endl;
            }
            else
            {
                cout<<"Ingrese el nombre del vertice origen: ";
                cin.ignore();
                getline(cin, origen, '\n');
                cout<<"Ingrese el nombre del vertice destino: ";
                getline(cin, destino, '\n');
                if(G.GetVertice(origen) == NULL || G.GetVertice(destino) == NULL)
                {
                    cout<<"Vertices invalidos"<<endl;
                }
                else
                {
                    G.PrimeroMejor(G.GetVertice(origen), G.GetVertice(destino));
                }
            }
            cin.get();
            cin.get();
            break;
        }*/
        case 13:
        {
            break;
        }
        default:
        {
            cout<<"Elija una opcion valida"<<endl;
        }
        }
    }
    while(opc != 13);
    return 0;
}
