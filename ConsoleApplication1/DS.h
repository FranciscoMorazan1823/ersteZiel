/*
    Interfaz que define los m�todos a utilizar para la
    manipulaci�n y administraci�n de estructuras de datos
    din�micas.

    Se define la interfaz como independiente del tipo de
    dato a almacenar mediante el uso de template.
*/
template <typename type>
class DS {
private:
    /*
        Funci�n que crea espacio en memoria para un
        Nodo de una estructura de datos din�mica de tipo
        <type>.
    */
    virtual void* createNode() = 0;

public:
    /*
        Funci�n que obtiene el Nodo inicial o de entrada
        de la estructura de datos din�mica local de tipo
        <type>.

        La funci�n retorna la direcci�n de dicho Nodo.
    */
    virtual Node<type>* getRoot() = 0;

    /*
        Funci�n que retorna la categor�a de la estructura
        de datos din�mica local de tipo <type>.

        Esta categor�a puede ser:
            - SINGLE_LINKED_LIST para las listas enlazadas
              simples.
            - DOUBLE_LINKED_LIST para las listas enlazadas
              simples.
            - BINARY_SEARCH_TREE para los �rboles de b�squeda
              binarios.
            - GRAPH para los grafos.

        La funci�n hace uso de la enumeraci�n category
        definida en "dynamicDS.h".
    */
    virtual category getCategory() = 0;

    /*
        Funci�n para inicializar una estructura de datos
        din�mica de tipo <type>.
    */
    virtual void create() = 0;

    /*
        Funci�n que retorna la extensi�n de la estructura
        de datos din�mica local de tipo <type>.

        Se define como extensi�n la cantidad de informaci�n
        almacenada por la estructura de datos din�mica:
            - Si la estructura es un �rbol, su extensi�n es
              su altura.
            - Si la estructura es un grafo, su extensi�n es
              su cantidad de nodos.
            - En cualquier otro caso, la extensi�n ser� la
              longitud de la estructura.
    */
    virtual int extension() = 0;

    /*
        Funci�n para insertar un valor <value> de tipo <type>
        en la estructura de datos din�mica local de tipo <type>.
    */
    virtual void insert(type value, string name) = 0;

    /*
        Funci�n para insertar un valor <value> de tipo <type>
        en la posici�n indicada por <pos> de la estructura de datos
        din�mica local de tipo <type>.
    */
    virtual void insert(int pos, type value, string name) = 0;

    /*
        Funci�n para extraer un dato de tipo <type> de la
        posici�n indicada por <pos> en la estructura de datos
        din�mica local de tipo <type>.
    */
    virtual type extract(int pos) = 0;

    /*
        Funci�n para liberar todo el espacio en memoria
        utilizado por una estructura de datos din�mica de
        tipo <type>.
    */
    virtual void destroy() = 0;

    /*
        Funci�n que determina si un valor <value> de tipo <type>
        se encuentra o no dentro de una estructura de datos din�mica
        de tipo <type>.

        Se retorna true si se encuentra, false en caso
        contrario.
    */
    virtual bool search(type value) = 0;

    /*
        Funci�n que determina la cantidad de ocurrencias de un valor
        <value> de tipo <type> en una estructura de datos din�mica
        de tipo <type>.
    */
    virtual int count(type value) = 0;

    /*
        Funci�n que invierte el contenido de una estructura de datos
        din�mica de tipo <type>, si la operaci�n es posible de realizar.

        Si la operaci�n no es posible, se informa.
    */
    virtual void reverse() = 0;

    /*
        Funci�n que muestra el contenido de una estructura de datos
        din�mica de tipo <type>.

        <verbose> indica el nivel de detalle a mostrar:
            - Si es false, solo se muestra la estructura de datos como tal.

            - Si es true, se detalla posici�n por posici�n el contenido de
              la estructura de datos.
    */
    virtual void show(bool verbose) = 0;
};

