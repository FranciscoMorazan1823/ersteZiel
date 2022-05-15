
/*
    Implementaci�n de la interfaz DS, definida en "DS.h", para un
    grafo.

    Se define la implementaci�n como independiente del tipo de dato
    a almacenar mediante el uso de template.
*/
template <typename type>
/*
    En C++, la implementaci�n se maneja como una herencia,
    de modo que DSG hereda de DS.

    El indicador de visibilidad 'public' indica que DSG tendr�
    acceso a todos los m�todos de DS manteniendo la visibilidad
    original.

    Dado que DS es un template, debe indicarse el tipo de dato
    a utilizar mediante un "meta-par�metro". Sin embargo, el tipo
    de dato a�n no ha sido definido, ya que DSG tambi�n es un
    template, por lo que el "meta-par�metro" es el tipo de dato
    gen�rico local <type>.
*/


class DSG : public DS<type> {
private:
    /*
        Como atributo privado local se manejar� el grafo de datos de
        tipo <type> como tal.

        Se declara un puntero a NodeG, un Nodo para grafos.
    */



    NodeG<type>* G;

    /*
        Funci�n que crea espacio en memoria para un NodeG<type>,
        es decir, un Nodo para un grafo de tipo <type>.

        Se retorna la direcci�n del nuevo nodo creado, y esta
        direcci�n se retorna en forma "cruda" como void*.
    */
    void* createNode() override {
        //sizeof( NodeG<type> ) ya que se necesita espacio para
        //un Nodo para grafos para almacenar un dato de tipo <type>
        return malloc(sizeof(NodeG<type>));
    }

public:
    /*
        Funci�n que obtiene el Nodo inicial del grafo local
        de tipo <type>.

        La funci�n retorna la direcci�n de dicho Nodo.
    */
    Node<type>* getRoot() {
        return G;
    }

    /*
        Funci�n que retorna la categor�a del grafo local de
        tipo <type>.
    */
    category getCategory() override {
        //Al tratarse de una lista enlazada doble, se retorna
        //GRAPH.
        return GRAPH;
    }

    /*
        Funci�n para inicializar el grafo de tipo <type>.
    */
    void create() override {
        //Para inicializar un grafo basta con que el puntero
        //al inicio del grafo apunte a NULL
        G = NULL;
    }

    /*
        Funci�n que retorna la cantidad de nodos del grafo local
        de tipo <type>.
    */
    int extension() override {
        //Se inicializa un contador en 0
        int cont = 0;

        //Se copia el puntero al inicio del grafo para no
        //perder la referencia durante el proceso de recorrido
        NodeG<type>* Gcopy = G;

        //Se recorre el listado del grafo hasta el final
        while (Gcopy != NULL) {
            //Si entramos al while, hay un nodo no evaluado
            //Se actualiza el contador
            cont++;

            //Se avanza al siguiente nodo del grafo
            Gcopy = Gcopy->next;
        }

        /* Se puede a�adir ac� el conteo del n�mero de aristas */

        //Se retorna el resultado
        return cont;
    }

    /* La operaci�n de inserci�n sin datos adicionales no es aplicable
       a un grafo.                                                    */
    void insert(int id, type value, string name) override {
        cout << "N/A\n";
    }

    /*
        Funci�n para insertar un nodo con identificador <id> con un
        dato <value> de tipo <type> en un grafo de tipo <type>.

        El orden en el listado de nodos de un grafo no es relevante,
        por simplicidad se colocar�n nuevos nodos al inicio del listado.
    */
    void insert(type value, string name) override {
        //Se crea un nuevo nodo para el grafo que alojar� el nuevo valor <value>
        NodeG<type>* temp = new NodeG<type>(); //   (NodeG<type>*) createNode();
        
        //Se define el identificador del nuevo nodo como <id>
        //Se coloca <value> como el dato del nuevo nodo
        temp->data = value;
        temp->name = name;
        temp->deeper = new DST<int>();
        temp->deeper->create();
        //temp->deeper = NULL;
        cout << name << endl;
        //Todav�a no hay conexiones definidas para el nuevo nodo, se
        //inicializan en NULL
        temp->connections = NULL;
       cout << G << endl;
        //Se verifica si el grafo est� vac�o
        if (G == NULL) {
            cout << " el grafo al inicio si es null" << endl;
            //Si el grafo est� vac�o, el nuevo nodo se marca como
            //el nodo de entrada al grafo
            temp->entry = true;
            //No existe a�n nodo siguiente para el nuevo nodo
            temp->next = NULL;
        }
        else {

            //Si el grafo no est� vac�o, el nuevo nodo no ser�
            //el nodo de entrada al grafo
            temp->entry = false;
            //El nodo siguiente al nuevo nodo ser� el nodo que
            //actualmente est� al inicio del listado del grafo
            temp->next = G;
        }

        //El nuevo inicio del listado de nodos del grafo ser� el
        //nuevo nodo creado
        G = temp;
    }

    /*
        Funci�n para extraer un dato de tipo <type> del nodo con
        identificador <id> del grafo local de tipo <type>.

        Se asume pre-validaci�n de un identificador v�lido.
    */
    type extract(int id) override {
        //Se copia el puntero al inicio del grafo para no
        //perder la referencia durante el proceso de recorrido
        NodeG<type>* Gcopy = G;

        //Se recorre el listado de nodos del grafo hasta el final
        while (Gcopy != NULL) {
            //Si el nodo actual corresponde con el solicitado,
            //ya no seguimos recorriendo el listado
            if (Gcopy->id == id) break;

            //Se avanza al siguiente nodo del grafo
            Gcopy = Gcopy->next;
        }

        //Se retorna el dato del nodo del grafo solicitado
        return Gcopy->data;
    }

    /*
        Funci�n para liberar todo el espacio en memoria
        utilizado por un grafo de tipo <type>.
    */
    void destroy() override {
        //Variables auxiliares para el proceso
        NodeG<type>* temp;
        NodeSL<NodeG<type>*>* L;
        NodeSL<NodeG<type>*>* tempL;

        //Se recorre el listado de nodos del grafo hasta el final
        while (G != NULL) {
            //Se copia la referencia al nodo actual en la
            //variable auxiliar temp para "rescatarlo"
            temp = G;

            //Se almacena el listado de conexiones del nodo "rescatado"
            //en la variable auxiliar L
            L = temp->connections;

            //Se recorre el listado de conexiones hasta el final
            while (L != NULL) {
                //Se copia la referencia a la conexi�n actual en la
                //variable auxiliar tempL para "rescatarla"
                tempL = L;

                //Avanzamos a la siguiente conexi�n del listado
                //Ac� es donde perder�amos la referencia a la conexi�n
                //actual si no la hubi�ramos "rescatado"
                L = L->next;

                //A trav�s de la variable auxiliar tempL, liberamos
                //la conexi�n previamente "rescatada"
                free(tempL);
            }

            //Avanzamos al siguiente nodo del grafo
            //Ac� es donde perder�amos la referencia al nodo
            //actual si no lo hubi�ramos "rescatado"
            G = G->next;

            //A trav�s de la variable auxiliar temp, liberamos
            //el nodo previamente "rescatado"
            free(temp);
        }
        //Al final del proceso, G habr� quedado apuntando a NULL,
        //lo cual est� bien ya que se interpreta como un grafo
        //vac�o, y eso es coherente con la operaci�n realizada.
    }

    /*
        Funci�n que determina si un valor <value> de tipo <type>
        se encuentra o no dentro de un grafo de tipo <type>.

        Se retorna true si se encuentra, false en caso
        contrario.
    */
    bool search(type value) override {
        //Respuesta por defecto: "No se encuentra"
        bool ans = false;

        //Se copia el puntero al inicio del grafo para no perder
        //la referencia durante el proceso de recorrido
        NodeG<type>* Gcopy = G;

        //Se recorre el listado de nodos del grafo hasta final
        while (Gcopy != NULL) {
            //Verificamos si el dato almacenado en el nodo
            //actual es igual al que buscamos
            if (Gcopy->data == value) {
                //Se ha encontrado el dato, se setea una
                //respuesta positiva
                ans = true;
                //Se termina el proceso de recorrido porque
                //ya no es necesario seguir buscando
                break;
            }
            //Se avanza al siguiente nodo del grafo
            Gcopy = Gcopy->next;
        }
        //Se retorna el resultado
        return ans;
    }

    /*
        Funci�n que determina la cantidad de ocurrencias de un valor
        <value> de tipo <type> en un grafo de tipo <type>.
    */
    int count(type value) override {
        //Se inicializa un contador en 0
        int cont = 0;

        //Se copia el puntero al inicio del grafo para no perder
        //la referencia durante el proceso de recorrido
        NodeG<type>* Gcopy = G;

        //Se recorre el listado de nodos del grafo hasta final
        while (Gcopy != NULL) {
            //Verificamos si el dato almacenado en el nodo
            //actual es igual al que buscamos, en cuyo caso
            //aumentamos el contador
            if (Gcopy->data == value) cont++;

            //Se avanza al siguiente nodo del grafo
            Gcopy = Gcopy->next;
        }

        //Se retorna el resultado
        return cont;
    }

    /* La operaci�n de inversi�n de contenido no es aplicable a un grafo. */
    void reverse() override {
        cout << "N/A\n";
    }

    /*
        Funci�n que muestra el contenido de un grafo de tipo <type>.

        <verbose> indica el nivel de detalle a mostrar:
            - Si es false, solo se muestra el grafo como tal.

            - Si es true, se detalla posici�n por posici�n, y conexi�n por
              por conexi�n, el contenido del grafo.
    */
    void show(bool verbose) override {
        //Se verifica si el grafo est� vac�o,
        //en cuyo caso no hay nada que mostrar y se
        //terminar�a el proceso de mostrado
        if (G == NULL) {
            cout << "El grafo est� vac�o.\n";
            return;
        }

        //Se copia el puntero al inicio del grafo para no perder
        //la referencia durante el proceso de recorrido
        NodeG<type>* Gcopy = G;
        //Variable auxiliar para el proceso
        NodeSL<NodeG<type>*>* L;

        if (verbose)
            //Se recorre el listado de nodos del grafo hasta final
            while (Gcopy != NULL) {
                /*
                    Se muestra el contenido de cada nodo con el formato siguiente:

                                    Nodo #: <id>
                                    Datos: <dato>
                                    Conexiones:
                                        Conexi�n #1 corresponde al Nodo #<id>
                                        Conexi�n #2 corresponde al Nodo #<id>
                                                        ...
                */

                //Se muestran id y dato del nodo actual
                cout << "Nodo #" << Gcopy->id << ":\n\tDatos: " << Gcopy->data << "\n\tConexiones:\n";

                //Se extrae el listado de conexiones del nodo actual en la
                //variable auxiliar L
                L = Gcopy->connections;

                //Variable auxiliar para generar un correlativo en el proceso
                int index = 1;

                //Se recorre el listado de conexiones hasta el final
                while (L != NULL) {
                    //Se informan los detalles de la conexi�n actual
                    cout << "\tConexi�n #" << index << " corresponde al Nodo #" << L->data->id << "\n";
                    //Se aumenta el correlativo
                    index++;

                    //Se avanza a la siguiente conexi�n
                    L = L->next;
                }

                //Se avanza al siguiente nodo del grafo
                Gcopy = Gcopy->next;
            }
        else {
            //Se recorre el listado de nodos del grafo hasta final
            while (Gcopy != NULL) {
                /*
                    Se muestra el contenido en una sola l�nea colocando la informaci�n de cada
                    nodo con el formato siguiente:

                                ( <id> , <dato> , [ <id1>-><id2>->...->NULL ] ) ->
                */

                //Se abre el nodo actual y se coloca su identificador y su dato, y se abre
                //su listado de conexiones
                cout << "( " << Gcopy->id << " , " << Gcopy->data << " , [ ";

                //Se extrae el listado de conexiones del nodo actual y se almacena
                //en la variable auxiliar L
                L = Gcopy->connections;

                //Se recorre el listado de conexiones hasta el final
                while (L != NULL) {
                    //Se muestra el identificador del nodo de la conexi�n actual
                    cout << L->data->id << "->";

                    //Se avanza a la siguiente conexi�n
                    L = L->next;
                }
                //Se coloca NULL como la �ltima conexi�n, se cierra el listado de conexiones,
                //y se cierra el nodo actual del grafo
                cout << "NULL ] )" << " -> ";

                //Se avanza al siguiente nodo del grafo
                Gcopy = Gcopy->next;
            }

            //Se coloca NULL como el �ltimo nodo del listado de nodos del grafo
            cout << "NULL\n";
        }
    }
};