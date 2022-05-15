/*
    Implementaci�n de la interfaz DS, definida en "DS.h", para una
    lista enlazada simple.

    Se define la implementaci�n como independiente del tipo de dato
    a almacenar mediante el uso de template.
*/
template <typename type>
/*
    En C++, la implementaci�n se maneja como una herencia,
    de modo que DSSL hereda de DS.

    El indicador de visibilidad 'public' indica que DSSL tendr�
    acceso a todos los m�todos de DS manteniendo la visibilidad
    original.

    Dado que DS es un template, debe indicarse el tipo de dato
    a utilizar mediante un "meta-par�metro". Sin embargo, el tipo
    de dato a�n no ha sido definido, ya que DSSL tambi�n es un
    template, por lo que el "meta-par�metro" es el tipo de dato
    gen�rico local <type>.
*/
class DSSL : public DS<type> {
private:
    /*
        Como atributo privado local se manejar� la lista enlazada
        simple de datos tipo <type> como tal.

        Se declara un puntero a NodeSL, un Nodo para listas enlazadas
        simples.
    */
    NodeSL<type>* L;

    /*
        Funci�n que crea espacio en memoria para un NodeSL<type>,
        es decir, un Nodo para una lista enlazada simple de tipo
        <type>.

        Se retorna la direcci�n del nuevo nodo creado, y esta
        direcci�n se retorna en forma "cruda" como void*.
    */
    void* createNode() override {
        //sizeof( NodeSL<type> ) ya que se necesita espacio para
        //un Nodo para listas enlazadas simples para almacenar un
        //dato de tipo <type>
        return malloc(sizeof(NodeSL<type>));
    }

public:
    /*
        Funci�n que obtiene el Nodo inicial de la lista enlazada simple
        local de tipo <type>.

        La funci�n retorna la direcci�n de dicho Nodo.
    */
    Node<type>* getRoot() {
        return L;
    }

    /*
        Funci�n que retorna la categor�a de la lista enlazada
        simple local de tipo <type>.
    */
    category getCategory() override {
        //Al tratarse de una lista enlazada simple, se retorna
        //SINGLE_LINKED_LIST.
        return SINGLE_LINKED_LIST;
    }

    /*
        Funci�n para inicializar la lista enlazada simple de
        tipo <type>.
    */
    void create() override {
        //Para inicializar una lista enlazada simple basta con
        //que el puntero al inicio de la lista apunte a NULL
        L = NULL;
    }

    /*
        Funci�n que retorna la longitud de la lista enlazada
        simple local de tipo <type>.
    */
    int extension() override {
        //Se inicializa un contador en 0
        int cont = 0;

        //Se copia el puntero al inicio de la lista enlazada
        //simple para no perder la referencia durante el
        //proceso de recorrido
        NodeSL<type>* Lcopy = L;

        //Se recorre la lista hasta el final
        while (Lcopy != NULL) {
            //Si entramos al while, hay un nodo no evaluado
            //Se actualiza el contador
            cont++;

            //Se avanza al siguiente nodo de la lista
            Lcopy = Lcopy->next;
        }

        //Se retorna el resultado
        return cont;
    }

    /*
        Funci�n para insertar un valor <value> de tipo <type>
        en la lista enlazada simple local de tipo <type>.

        Se asume inserci�n al inicio de la lista.
    */
    void insert(type value, string name) override {
        //Se crea un nuevo nodo para la lista enlazada simple
        //que alojar� el nuevo valor <value>
        NodeSL<type>* temp = (NodeSL<type>*) createNode();
        //Se coloca el valor <value> en el nuevo nodo
        temp->data = value;

        //Se verifica si la lista se encuentra actualmente vac�a
        if (L == NULL)
            //Si la lista est� vac�a, el nodo siguiente al nuevo
            //nodo no existe a�n, por lo que se define como NULL
            temp->next = NULL;
        else
            //Si la lista no est� vac�a, el nodo siguiente al nuevo
            //nodo es el nodo que actualmente est� al inicio de la
            //lista
            temp->next = L;

        //Se define el inicio de la lista como el nuevo nodo
        L = temp;
    }

    /*
        Funci�n para insertar un valor <value> de tipo <type>
        en la posici�n indicada por <pos> de la lista enlazada simple
        local de tipo <type>.

        Se asume pre-validaci�n de una posici�n v�lida.
    */
    void insert(int pos, type value, string name) override {
        //Se crea un nuevo nodo para la lista enlazada simple
        //que alojar� el nuevo valor <value>
        NodeSL<type>* temp = (NodeSL<type>*) createNode();
        //Se coloca el valor <value> en el nuevo nodo
        temp->data = value;

        //Se copia el puntero al inicio de la lista enlazada
        //simple para no perder la referencia durante el
        //proceso de recorrido
        NodeSL<type>* Lcopy = L;

        //Se avanza en la lista hasta la posici�n anterior a la
        //posici�n en la que se desea insertar el nuevo nodo
        //Nos referiremos a esta posici�n como "anterior"
        for (int i = 0; i < pos - 1; i++) Lcopy = Lcopy->next;

        //El nodo siguiente al nuevo nodo ser� el que actualmente
        //es el nodo siguiente del "nodo anterior"
        temp->next = Lcopy->next;
        //El nuevo nodo siguiente del "nodo anterior" es el nuevo
        //nodo
        Lcopy->next = temp;
    }
    //Versi�n alterna de la funci�n anterior
    /*
    void insert(int pos, type value){
        NodeSL<type>* temp = ( NodeSL<type>* ) createNode();
        temp->data = value;

        NodeSL<type>* Lcopy = L;

        int cont = 0;
        while(Lcopy != NULL){
            if(cont == pos-1) break;

            Lcopy = Lcopy->next;
            cont++;
        }

        temp->next = Lcopy->next;
        Lcopy->next = temp;

    }
    */

    /*
        Funci�n para extraer un dato de tipo <type> de la
        posici�n indicada por <pos> en la lista enlazada simple
        local de tipo <type>.

        Se asume pre-validaci�n de una posici�n v�lida.
    */
    type extract(int pos) override {
        //Se copia el puntero al inicio de la lista enlazada
        //simple para no perder la referencia durante el
        //proceso de recorrido
        NodeSL<type>* Lcopy = L;

        //Se avanza en la lista hasta la posici�n indicada por
        //el par�metro <pos>
        for (int i = 0; i < pos; i++) Lcopy = Lcopy->next;

        //Se retorna el dato almacenado en el nodo ubicado en
        //la posici�n solicitada
        return Lcopy->data;
    }

    /*
        Funci�n para liberar todo el espacio en memoria
        utilizado por una lista enlazada simple de tipo
        <type>.
    */
    void destroy() override {
        //Variable auxiliar para el proceso
        NodeSL<type>* temp;

        //Se recorre la lista hasta el final
        while (L != NULL) {
            //Se copia la referencia al nodo actual en la
            //variable auxiliar para "rescatarlo"
            temp = L;

            //Avanzamos al siguiente nodo de la lista
            //Ac� es donde perder�amos la referencia al nodo
            //actual si no lo hubi�ramos "rescatado"
            L = L->next;

            //A trav�s de la variable auxiliar, liberamos
            //el nodo previamente "rescatado"
            free(temp);
        }
        //Al final del proceso, L habr� quedado apuntando a NULL,
        //lo cual est� bien ya que se interpreta como una lista
        //vac�a, y eso es coherente con la operaci�n realizada.
    }

    /*
        Funci�n que determina si un valor <value> de tipo <type>
        se encuentra o no dentro de una lista enlazada simple
        de tipo <type>.

        Se retorna true si se encuentra, false en caso
        contrario.
    */
    bool search(type value) override {
        //Respuesta por defecto: "No se encuentra"
        bool ans = false;

        //Se copia el puntero al inicio de la lista enlazada
        //simple para no perder la referencia durante el
        //proceso de recorrido
        NodeSL<type>* Lcopy = L;

        //Se recorre la lista hasta el final
        while (Lcopy != NULL) {
            //Verificamos si el dato almacenado en el nodo
            //actual es igual al que buscamos
            if (Lcopy->data == value) {
                //Se ha encontrado el dato, se setea una
                //respuesta positiva
                ans = true;
                //Se termina el proceso de recorrido porque
                //ya no es necesario seguir buscando
                break;
            }
            //Se avanza al siguiente nodo de la lista
            Lcopy = Lcopy->next;
        }
        //Se retorna el resultado
        return ans;
    }

    /*
        Funci�n que determina la cantidad de ocurrencias de un valor
        <value> de tipo <type> en una lista enlazada simple de tipo
        <type>.
    */
    int count(type value) override {
        //Se inicializa un contador en 0
        int cont = 0;

        //Se copia el puntero al inicio de la lista enlazada
        //simple para no perder la referencia durante el
        //proceso de recorrido
        NodeSL<type>* Lcopy = L;

        //Se recorre la lista hasta el final
        while (Lcopy != NULL) {
            //Verificamos si el dato almacenado en el nodo
            //actual es igual al que buscamos, en cuyo caso
            //aumentamos el contador
            if (Lcopy->data == value) cont++;

            //Se avanza al siguiente nodo de la lista
            Lcopy = Lcopy->next;
        }
        //Se retorna el resultado
        return cont;
    }

    /*
        Funci�n que invierte el contenido de una lista enlazada
        simple de tipo <type>.
    */
    void reverse() override {
        //Se prepara un puntero a Nodo de lista enlazada simple para
        //datos de tipo <type> que servir� para apuntar al inicio de
        //una nueva lista que contendr� los datos de la lista actual
        //en orden invertido
        NodeSL<type>* new_one = NULL;

        //Se copia el puntero al inicio de la lista enlazada
        //simple para no perder la referencia durante el
        //proceso de recorrido
        NodeSL<type>* Lcopy = L;

        //Se prepara un puntero a nodo de lista enlazada simple
        //de tipo <type> adicional que servir� como variable auxiliar
        NodeSL<type>* temp;

        //Se recorre la lista hasta el final
        while (Lcopy != NULL) {
            /*Se crea un nodo para la nueva lista, manteniendo que
              sea para una lista enlazada simple para datos de tipo
              <type>.
              Dado que createNode() retorna un puntero "crudo", es
              necesario hacer el casting correspondiente para darle
              formato al bloque de memoria otorgado.               */
            temp = (NodeSL<type>*) createNode();

            //Se coloca en el nuevo nodo el dato ubicado en el nodo
            //actual del recorrido de la lista local
            temp->data = Lcopy->data;

            //Se procede a insertar el nuevo nodo al inicio de la
            //nueva lista
            //Se verifica primero si la nueva lista se encuentra vac�a
            if (new_one == NULL)
                //Si la nueva lista se encuentra vac�a, el nodo siguiente
                //al nuevo nodo creado a�n no existe, por lo que se define
                //como NULL
                temp->next = NULL;
            else
                //Si la nueva lista no est� vac�a, entonces el nodo siguiente
                //al nuevo nodo creado es el nodo que actualmente se encuentra
                //al inicio de la nueva lista
                temp->next = new_one;

            //El nuevo inicio de la nueva lista es ahora el nuevo nodo creado
            new_one = temp;

            //Se avanza al siguiente nodo de la lista local
            Lcopy = Lcopy->next;
        }

        //La lista local en su estado actual ya no ser� utilizada, por lo que
        //se invoca a la funci�n destroy() para liberar todo el espacio de
        //memoria que le corresponde
        destroy();

        //La nueva lista local ser� ahora la nueva lista creada, que contiene
        //los datos de la lista original en el orden inverso
        L = new_one;
    }

    /*
        Funci�n que muestra el contenido de una lista enlazada simple de
        tipo <type>.

        <verbose> indica el nivel de detalle a mostrar:
            - Si es false, solo se muestra la lista como tal.

            - Si es true, se detalla posici�n por posici�n el contenido de
              la lista.
    */
    void show(bool verbose) override {
        //Se verifica si la lista est� vac�a,
        //en cuyo caso no hay nada que mostrar y se
        //terminar�a el proceso de mostrado
        if (L == NULL) {
            cout << "La lista est� vac�a.\n";
            return;
        }

        //Se copia el puntero al inicio de la lista enlazada
        //simple para no perder la referencia durante el
        //proceso de recorrido
        NodeSL<type>* Lcopy = L;

        if (verbose) {
            //Variable auxiliar para mostrar el contenido de la lista
            int index = 1;

            //Se recorre la lista hasta el final
            while (Lcopy != NULL) {
                //Se especifica expl�citamente el valor de cada elemento
                //almacenado en la lista, uno por l�nea, indicando la posici�n
                //haciendo uso de la variable auxiliar
                cout << "Element #" << index << " is: " << Lcopy->data << "\n";
                //Se le suma 1 a la variable auxiliar
                index++;

                //Se avanza al siguiente nodo de la lista
                Lcopy = Lcopy->next;
            }
        }
        else {
            //Se muestra el contenido de la lista como una secuencia de datos
            //conectados entre s� en una sola l�nea, representando las
            //conexiones con '->'.

            //Se recorre la lista hasta el final
            while (Lcopy != NULL) {
                //Se coloca el dato actual seguido de '->'
                cout << Lcopy->data << " -> ";

                //Se avanza al siguiente nodo de la lista
                Lcopy = Lcopy->next;
            }
            //El �ltimo dato conecta con NULL, indicando el final de la lista
            cout << "NULL\n";
        }
    }
};
