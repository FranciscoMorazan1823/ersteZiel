
template <typename type>

class DST : public DS<type> {
private:
    /*
        Como atributo privado local se manejar� el �rbol binario de
        b�squeda de tipo <type> como tal.

        Se declara un puntero a NodeT, un Nodo para �rboles binarios
        de b�squeda.
    */
    NodeT<type>* T;

    /*
        Funci�n que crea espacio en memoria para un NodeT<type>,
        es decir, un Nodo para un �rbol binario de b�squeda de tipo
        <type>.

        Se retorna la direcci�n del nuevo nodo creado, y esta
        direcci�n se retorna en forma "cruda" como void*.
    */
    void* createNode() override {
        //sizeof( NodeT<type> ) ya que se necesita espacio para
        //un Nodo para �rboles binarios de b�squeda para almacenar un
        //dato de tipo <type>
        return malloc(sizeof(NodeT<type>));
    }

    /*=== Funciones auxiliares para el manejo de �rboles binarios de b�squeda ===*/
    /*
        Funci�n auxiliar para calcular la altura de un �rbol binario de b�squeda
        de tipo <type>.

        Se recibe <tree> como el �rbol cuya altura se desea calcular.
    */
    int height(NodeT<type>* tree) {
        //Si el �rbol est� vac�o su altura es 0
        if (tree == NULL) return 0;

        //Si el �rbol no est� vac�o, se calcula la altura del sub-�rbol
        //izquierdo y la altura del sub-�rbol derecho, luego se determina
        //cu�l de estos resultados es el m�s grande y se retorna sum�ndole 1,
        //para incluir el nodo actual en el conteo
        return max(1 + height(tree->left), 1 + height(tree->right));
    }




    /*
        Funci�n auxiliar para insertar un nuevo nodo en un �rbol binario de
        b�squeda de tipo <type>.

        Se recibe <node> como el nuevo nodo a insertar en el �rbol, y se recibe
        <tree> como el �rbol donde se insertar� dicho nodo.

        Se asume que se recibe un �rbol no vac�o.
    */
    void insert_aux(NodeT<type>* tree, NodeT<type>* node) {
        //Si el dato del nuevo nodo es menor o igual al dato
        //del nodo actual, el nuevo nodo deber� insertarse en el
        //sub-�rbol izquierdo
        if (node->data <= tree->data)
            //Se verifica si el sub-�rbol izquierdo es una hoja
            if (tree->left == NULL) {
                //El nuevo nodo ser� el nuevo hijo izquierdo

                //El padre del nuevo nodo es el nodo actual
                node->parent = tree;
                //El hijo izquierdo del nodo actual es el nuevo nodo
                tree->left = node;
            }
            else
                //Si el sub-�rbol izquierdo no es una hoja, se procede
                //a insertar el nuevo nodo en dicho sector
                insert_aux(tree->left, node);

        //Si el dato del nuevo nodo es mayor al dato del nodo actual,
        //el nuevo nodo deber� insertarse en el sub-�rbol derecho
        else
            //Se verifica si el sub-�rbol derecho es una hoja
            if (tree->right == NULL) {
                //El nuevo nodo ser� el nuevo hijo derecho

                //El padre del nuevo nodo es el nodo actual
                node->parent = tree;
                //El hijo derecho del nodo actual es el nuevo nodo
                tree->right = node;
            }
            else
                //Si el sub-�rbol derecho no es una hoja, se procede
                //a insertar el nuevo nodo en dicho sector
                insert_aux(tree->right, node);
    }

    /*
        Funci�n auxiliar para la liberaci�n de memoria de un �rbol binario
        de b�squeda de tipo <type>.

        Se recibe <tree> como el �rbol cuyo espacio en memoria se liberar�.
    */
    void destroy_aux(NodeT<type>* tree) {
        //Si el �rbol est� vac�o no hay nada que liberar
        if (tree == NULL) return;

        //Se libera todo el espacio de memoria utilizado por el sub-�rbol
        //izquierdo
        destroy_aux(tree->left);

        //Se libera todo el espacio de memoria utilizado por el sub-�rbol
        //derecho
        destroy_aux(tree->right);

        //Se libera el espacio de memoeria utilizado por el nodo actual
        free(tree);
    }

    /*
        Funci�n auxiliar para la b�squeda de un dato de tipo <type> en un
        �rbol binario de b�squeda de tipo <type>.

        Se recibe <value> como el dato a buscar en el �rbol, y se recibe
        <tree> como �l �rbol donde se har� la b�squeda.

        Se retorna true si el dato se encuentra en el �rbol, y se retorna
        false en caso contrario.
    */
    bool search_aux(NodeT<type>* tree, type value) {
        //Si el �rbol est� vac�o no hay nada que buscar
        if (tree == NULL) return false;

        //Si el �rbol no est� vac�o, se verifica si el dato actual coincide
        //con el dato buscado.
        //De ser as� se retorna una respuesta de �xito.
        if (tree->data == value) return true;

        //De no haberse encontrado el dato en el nodo actual, se retorna el
        //resultado de buscarlo en el sub-�rbol izquierdo y/o el sub-�rbol
        //derecho
        return search_aux(tree->left, value) || search_aux(tree->right, value);
    }

    /*
        Funci�n auxiliar para el conteo de ocurrencias de un dato de tipo
        <type> en un �rbol binario de b�squeda de tipo <type>.

        Se recibe <value> como el dato cuyas ocurrencias se desean contar,
        y se recibe <tree> como el �rbol donde se har� el proceso.

        Se retorna el resultado del conteo
    */
    int count_aux(NodeT<type>* tree, type value) {
        //Si el �rbol est� vac�o, no hay nada que contar
        if (tree == NULL) return 0;

        //Si el �rbol no est� vac�o, se cuentan las ocurrencias de <value> en
        //el sub-�rbol izquierda, a esto se le suma el total de ocurrencias de
        //<value> en el sub-�rbol derecho, y finalmente a esto se le suma 1 s�lo
        //si el dato del nodo actual tambi�n es una ocurrencia de <value>.
        return ((tree->data == value) ? 1 : 0) + count_aux(tree->left, value) + count_aux(tree->right, value);
    }

    /*
        Funci�n auxiliar para mostrar el contenido de un �rbol binario de b�squeda
        de tipo <type>.

        Se recibe <tree> como el �rbol cuyo contenido se desea mostrar.

        Se muestra el contenido en una sola l�nea colocando la informaci�n de cada
        nodo con el formato siguiente:

                        [ <dato> HIJO_IZQUIERDO HIJO_DERECHO ]

        Donde HIJO_IZQUIERDO e HIJO_DERECHO siguen a su vez el mismo formato.

        Toda hijo nulo se mostrar� directamente como NULL.
    */
    void show_aux(NodeT<type>* tree) {
        //Si el �rbol est� vac�o, se muestra �nicamente NULL
        if (tree == NULL) { cout << " NULL "; return; }

        //Si el �rbol no est� vac�o se abre el contenido
        //y se coloca el dato del nodo actual
        cout << "[ " << tree->data << " ";

        //Se muestra el contenido del sub-�rbol izquierdo
        show_aux(tree->left);
        //Se muestra el contenido del sub-�rbol derecho
        show_aux(tree->right);

        //Se cierra el contenido del �rbol
        cout << "]";
    }

    /*
        Funci�n auxiliar para el mostrado verbose del contenido de un �rbol binario
        de b�squeda de tipo <type>.

        Se recibe <tree> como el �rbol cuyo contenido se desea mostrar.

        Se recibe <level> como el nivel del �rbol cuyo contenido se desea mostrar.

        Se muestra el contenido de cada nodo con el formato siguiente:

                        Padre: <dato>.
                        Hijo izquierdo:
                            HIJO_IZQUIERDO
                        Hijo derecho:
                            HIJO_DERECHO

        Donde HIJO_IZQUIERDO e HIJO_DERECHO siguen a su vez el mismo formato.

        Toda hijo nulo se mostrar� con el mensaje "Hijo nulo.".

        Adicionalmente, el formato anterior ser� precedido por una cantidad de tabulaciones
        igual al nivel del �rbol que se est� mostrando. Esto se hace mediante el uso de la
        clase string de la siguiente forma:

                                string(<numero>,<caracter>)

        Lo cual provee una cadena de caracteres formada por <caracter> repetido <numero> veces.
    */
    void show_aux_verbose(NodeT<type>* tree, int level) {
        //Si el �rbol est� vac�o solo se muestra el mensaje "Hijo nulo."
        if (tree == NULL) {
            //Se tabula una cantidad <level> de veces
            cout << string(level, '\t') << "Hijo nulo.\n";
            return;
        }

        //Si el �rbol no est� vac�o, se muestra primero el contenido del
        //nodo actual.
        //Se tabula una cantidad <level> de veces
        cout << string(level, '\t') << "Padre: " << tree->data << ".\n";

        //Se introduce la secci�n para el contenido del sub-�rbol izquierdo
        //tabulando una cantidad <level> de veces
        cout << string(level, '\t') << "Hijo izquierdo:\n";
        //Se muestra el contenido del sub-�rbol izquierdo aumentando el nivel en 1
        show_aux_verbose(tree->left, level + 1);

        //Se introduce la secci�n para el contenido del sub-�rbol derecho
        //tabulando una cantidad <level> de veces
        cout << string(level, '\t') << "Hijo derecho:\n";
        //Se muestra el contenido del sub-�rbol derecho aumentando el nivel en 1
        show_aux_verbose(tree->right, level + 1);
    }

public:
    /*
        Funci�n que obtiene el Nodo inicial del �rbol binario de
        b�squeda local de tipo <type>.

        La funci�n retorna la direcci�n de dicho Nodo.
    */
    Node<type>* getRoot() {
        return T;
    }

    /*
        Funci�n que retorna la categor�a del �rbol binario de
        b�squeda local de tipo <type>.
    */
    category getCategory() override {
        //Al tratarse de un �rbol binario de b�squeda, se retorna
        //BINARY_SEARCH_TREE.
        return BINARY_SEARCH_TREE;
    }

    void assignTree(NodeT<type>* tree) {
        T = tree;
    }

    /*
        Funci�n para inicializar el �rbol binario de b�squeda
        de tipo <type>.
    */
    void create() override {
        //Para inicializar un �rbol binario de b�squeda basta con
        //que el puntero al inicio del �rbol apunte a NULL
        T = NULL;
    }

    /*
        Funci�n que retorna la altura del �rbol binario de b�squeda
        local de tipo <type>.
    */
    int extension() override {
        //Se env�a el �rbol binario de b�squeda local a la funci�n
        //auxiliar para el c�lculo de altura y se retorna dicho
        //resultado
        return height(T);
    }

    /*
        Funci�n para insertar un valor <value> de tipo <type>
        en el �rbol binario de b�squeda local de tipo <type>.
    */
    void insert(type value, string name) override {
        //Se crea un nuevo nodo para el �rbol binario de b�squeda
        //local que alojar� el nuevo valor <value>
        NodeT<type>* temp = new NodeT<type>();
            //(NodeT<type>*) createNode();
        //Se coloca el valor <value> en el nuevo nodo
        cout << name << endl;

        temp->data = value;
        temp->name = name;
        temp->left = NULL;
        temp->right = NULL;


        //Se verifica si el �rbol se encuentra actualmente vac�o
        if (T == NULL) {
            cout << "es nuloss" << endl;
            cout << name << endl;

            //Si el �rbol est� vac�o, el padre para el nuevo
            //nodo no existe a�n, por lo que se define como NULL
            temp->parent = NULL;
            //Se define el nuevo nodo como la ra�z del �rbol
            T = temp;

        }
        else {

            cout << "no era nulo" << endl;
            //Si el �rbol no est� vac�o, se env�a el �rbol binario
            //de b�squeda local y el nuevo nodo creado a la funci�n
            //auxiliar para inserci�n de nodos en un �rbol
            insert_aux(T, temp);
        }
    }

    /* La operaci�n de inserci�n por posici�n no es aplicable a un �rbol
       binario de b�squeda.                                             */
    void insert(int pos, type value, string name) override {
        cout << "N/A\n";
    }

    /* La operaci�n de extracci�n por posici�n no es aplicable a un �rbol
       binario de b�squeda.                                              */
    type extract(int pos) override {
        cout << "N/A\nSe retorna valor nulo.\n";
        return (type)0;
    }

    /*
        Funci�n para liberar todo el espacio en memoria
        utilizado por un �rbol binario de b�squeda de tipo
        <type>.
    */
    void destroy() override {
        //Se env�a el �rbol binario de b�squeda local a la funci�n
        //auxiliar para liberaci�n de memoria
        destroy_aux(T);
        //Se define el �rbol como vac�o
        T = NULL;
    }

    /*
        Funci�n que determina si un valor <value> de tipo <type>
        se encuentra o no dentro de un �rbol binario de b�squeda
        de tipo <type>.

        Se retorna true si se encuentra, false en caso
        contrario.
    */
    bool search(type value) override {
        //Se env�a el �rbol binario de b�squeda local y el dato a
        //buscar a la funci�n auxiliar para b�squeda de un dato
        return search_aux(T, value);
    }

    /*
        Funci�n que determina la cantidad de ocurrencias de un valor
        <value> de tipo <type> en un �rbol binario de b�squeda de tipo
        <type>.
    */
    int count(type value) override {
        //Se env�a el �rbol binario de b�squeda local y el dato cuyas
        //ocurrencias se contar�n a la funci�n auxiliar para conteo de
        //ocurrencias
        return count_aux(T, value);
    }

    /* La operaci�n de inversi�n de contenido no es aplicable a un �rbol
       binario de b�squeda.                                              */
    void reverse() override {
        cout << "N/A\n";
    }

    /*
        Funci�n que muestra el contenido de un �rbol binario de b�squeda de
        tipo <type>.

        <verbose> indica el nivel de detalle a mostrar:
            - Si es false, solo se muestra el �rbol como tal.

            - Si es true, se detalla posici�n por posici�n y nivel por nivel
              el contenido del �rbol.

        Se implementa recorrido en Pre-Order.
    */
    void show(bool verbose) override {
        //Se verifica si el �rbol est� vac�o,
        //en cuyo caso no hay nada que mostrar y se
        //terminar�a el proceso de mostrado
        if (T == NULL) {
            cout << "El �rbol est� vac�o.\n";
            return;
        }

        if (verbose)
            //Se env�a el �rbol binario de b�squeda local a la funci�n
            //auxiliar para mostrado verbose
            //Se env�a un 0 para indicar que el proceso comienza en la ra�z
            //del �rbol, es decir, en el nivel 0 del �rbol
            show_aux_verbose(T, 0);
        else {
            //Se env�a el �rbol binario de b�squeda local a la funci�n
            //auxiliar para mostrado no verbose
            show_aux(T);
            cout << "\n";
        }
    }
};
