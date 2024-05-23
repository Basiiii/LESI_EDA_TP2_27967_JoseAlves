/**

    @file      Graph.c
    @brief     Ficheiro que cont�m a implementa��o das fun��es de gest�o de grafos.
    @details   ~
    @author    Jos� Ant�nio da Cunha Alves
    @date      12.05.2024
    @copyright � Jos� Ant�nio da Cunha Alves, 2024. All right reserved.

**/

#include "Global.h"
#include<malloc.h>
#include<string.h>

#pragma region Vertices
/**
    @brief  Fun��o que cria um nodo.
    @param  value - Valor a atribuir ao nodo.
    @retval       - Apontador para o nodo.
**/
Node* CreateNode(int value) {
    Node* aux = (Node*)malloc(sizeof(Node));
    if (aux == NULL) return NULL;
    aux->value = value;
    aux->next = NULL;
    aux->nextNode = NULL;
    aux->visited = false;
    return aux;
}

/**
    @brief  Fun��o que verifica se um nodo existe na mem�ria.
    @param  head  - Apontador para o in�cio da lista de nodos.
    @param  value - Valor do v�rtice a encontrar.
    @retval true - O nodo existe.
    @retval false - O nodo n�o existe.
**/
bool ExistNode(Node* head, int value) {
    if (head == NULL) return false;
    Node* aux = head;
    while (aux) {
        if (aux->value == value)return true;
        aux = aux->nextNode;
    }
    return false;
}

/**
    @brief Fun��o que liberta a mem�ria de um nodo.
    @param node - Apontador para o nodo a eliminar.
**/
void DestroyNode(Node* node) {
    free(node);
}

/**
    @brief  Fun��o que insere um nodo na lista de nodos.
    @param  head    - Apontador para o in�cio da lista de nodos.
    @param  newNode - Apontador para o nodo a adicionar � lista.
    @param  res     - Vari�vel de controlo de sucesso.
    @retval         - Apontador para a lista de nodos.
**/
Node* InsertNode(Node* head, Node* newNode, bool* res) {
    *res = false;

    //Caso ainda n�o existam v�rtices, insere no in�cio.
    if (head == NULL) {
        *res = 1;
        head = newNode;
        return head;
    }

    //Testa se j� existe um v�rtice com esse valor.
    if (ExistNode(head, newNode->value) == true) return head;
    else {
        //Procura posi��o onde inserir o novo v�rtice. Insere no fim.
        Node* aux = head;
        while (aux->nextNode != NULL) {
            aux = aux->nextNode;
        }
        //Estando na posi��o correta, insere.
        *res = true;
        if (aux == NULL)//Este � o primeiro valor e, por isso, ser� o novo head.
        {
            head = newNode;
        }
        else {
            aux->nextNode = newNode;
        }
        return head;
    }
}

/**
    @brief  Fun��o que elimina um nodo da lista de nodos.
    @param  head    - Apontador para o in�cio da lista de nodos.
    @param  codNode - Valor do nodo a eliminar.
    @param  res     - Vari�vel de controlo de sucesso.
    @retval         - Apontador para o in�cio da lista de nodos.
**/
Node* DeleteNode(Node* head, int codNode, bool* res) {
    *res = false;
    if (head == NULL) return NULL;

    //Encontra o v�rtice a eliminar.
    Node* prev = NULL;
    Node* aux = head;
    while (aux->value != codNode) {
        prev = aux;
        aux = aux->nextNode;
    }
    if (!aux)return head; //N�o existe o v�rtice a eliminar.
    
    //Caso o v�rtice a eliminar seja o primeiro.
    if (prev == NULL) {
        //Elimina as adjac�ncias do v�rtice a eliminar.
        aux->nextNode = DeleteAllAdj(aux->nextNode, res);
        if (*res == false)return head;
        head = aux->nextNode;
    }
    else {
        prev->nextNode = aux->nextNode;
    }
    DestroyNode(aux);
    *res = true;
    return head;
}

/**
    @brief  Fun��o que procura a posi��o de um nodo na lista de nodos.
    @param  head  - Apontador para o in�cio da lista de nodos.
    @param  value - Valor do nodo a procurar.
    @retval       - Retorna o nodo procurado, caso exista. Caso contr�rio, retorna NULL. 
**/
Node* WhereisNode(Node* head, int value){
    if (head == NULL) return NULL;
    Node* aux = head;
    while (aux) {
        if (aux->value == value) return aux; //Devolve o v�rtice que procuramos.
        aux = aux->nextNode;
    }
    return NULL;
}
#pragma endregion

#pragma region Adjacencies
/**
    @brief  Fun��o que reserva lugar na mem�ria para uma nova adjac�ncia.
    @param  value  - Valor do v�rtice adjacente.
    @param  weight - Peso da aresta a criar.
    @retval        - Retorna um apontador para a adjac�ncia.
**/
AdjListNode* NewAdjacent(int value, int weight) {
    AdjListNode* adjacent = (AdjListNode*)malloc(sizeof(AdjListNode));
    if (adjacent == NULL) return NULL;
    adjacent->value = value;
    adjacent->next = NULL;
    adjacent->weight = weight;
    return adjacent;
}

/**
    @brief Fun��o que liberta a mem�ria de um nodo de adjac�ncia.
    @param node - Apontador para o nodo a eliminar.
**/
void AdjListNodeDestroy(AdjListNode* node) {
    free(node);
}

/**
    @brief  Fun��o que elimina uma adjac�ncia.
    @param  listAdj - Apontador para o in�cio da lista de adjac�ncias.
    @param  codAdj  - Valor do v�rtice a eliminar adjac�ncia.
    @param  res     - Vari�vel de controlo de sucesso.
    @retval         - Apontador para o in�cio da lista de adjac�ncias.
**/
AdjListNode* DeleteAdj(AdjListNode* listAdj, int codAdj, bool* res) {
    *res = false;
    if (listAdj == NULL) return NULL;
    //Procura a adjac�ncia a eliminar.
    AdjListNode* aux = listAdj;
    AdjListNode* prev = NULL;
    while (aux && aux->value != codAdj) {
        prev = aux;
        aux = aux->next;
    }
    if (!aux) return listAdj; //A adjac�ncia que queremos eliminar j� n�o existe.
    //A adjac�ncia a eliminar � o in�cio.
    if (prev == NULL) {
        listAdj = aux->next;
    }
    else {
        prev->next = aux->next;
    }
    AdjListNodeDestroy(aux);
    *res = true;
    return listAdj;
}

/**
    @brief  Fun��o que elimina todas as adjac�ncias de um v�rtice.
    @param  listAdj - Apontador para o in�cio da lista de adjac�ncias do v�rtice a eliminar.
    @param  res     - Vari�vel de controlo de sucesso.
    @retval         - Apontador para o in�cio da lista de adjac�ncias do v�rtice.
**/
AdjListNode* DeleteAllAdj(AdjListNode* listAdj, bool* res) {
    *res = false;
    if (listAdj == NULL)return NULL;
    //Percorre a lista e elimina as adjac�ncias.
    AdjListNode* aux = listAdj;
    while (aux) {
        if (aux){
            listAdj = aux->next;
            AdjListNodeDestroy(aux);
            aux = listAdj;
        }
    }
    listAdj = NULL;
    *res = true;
    return listAdj;
}

/**
    @brief  Fun��o que elimina a adjac�ncia de um nodo com todos os outros nodos.
    @param  node   - Apontador para o in�cio da lista de nodos.
    @param  codAdj - Valor do nodo a eliminar.
    @param  res    - Vari�vel de controlo de sucesso.
    @retval        - Apontador para o in�cio da lista de nodos.
**/
Node* DeleteAdjacenceAllNodes(Node* node, int codAdj, bool* res) {
    *res = false;
    if (node == NULL) return NULL;
    Node* aux = node;
    while (aux) {
        aux->next = DeleteAdj(aux->next, codAdj, res);
        aux = aux->nextNode;
    }
    *res = true;
    return node;
}

/**
    @brief  Fun��o que cria uma adjac�ncia.
    @param  listAdj - Apontador para o in�cio da lista de adjac�ncias.
    @param  idDest  - ID do v�rtice de destino.
    @param  weight  - Peso da aresta.
    @retval         - Apontador para o in�cio da lista de adjac�ncias.
**/
AdjListNode* InsertAdj(AdjListNode* listAdj, int idDest, int weight) {
    AdjListNode* newAdj;
    if ((newAdj = NewAdjacent(idDest, weight)) == NULL) return listAdj; //Imposs�vel criar a nova adjac�ncia.
    //Caso ainda n�o existam adjac�ncias na lista:
        if (listAdj == NULL) {
            listAdj = newAdj; //Insere no inicio.
        }
        else {//Insere a adjac�ncia no fim.
            AdjListNode* aux = listAdj;
            while (aux->next != NULL) {
                aux = aux->next;
            }
            aux->next = newAdj;
        }
        return listAdj;
}

#pragma endregion

#pragma region Graphs
/**
    @brief  Fun��o que insere um nodo num grafo.
    @param  graph - Apontador para o grafo.
    @param  node  - Apontador para o nodo a inserir no grafo.
    @param  res   - Vari�vel de controlo de sucesso.
    @retval       - Apontador para o grafo.
**/
GR* InsertNodeGraph(GR* graph, Node* node, int res) {
    res = 1;
    //Verifica��es:
    if (node == NULL) { //V�rtice Inv�lido
        res = 0;
        return graph;
    }
    if (graph == NULL) { //N�o existe grafo.
        res = -1;
        return NULL;
    }
    if (ExistNodeGraph(graph, node->value)) {
        res = -2;
        return graph;
    }
    graph->headGraph = InsertNode(graph->headGraph, node, &res);
    if (res == true)graph->numNodes++;
    return graph;
}

/**
    @brief  Fun��o que elimina um nodo de um grafo.
    @param  graph   - Apontador para o grafo.
    @param  codNode - C�digo do nodo a eliminar.
    @param  res     - Vari�vel de controlo de sucesso.
    @retval         - Apontador para o grafo.
**/
GR* DeleteNodeGraph(GR* graph, int codNode, bool* res) {
    *res = false;
    if (graph == NULL)return NULL;

    graph->headGraph = DeleteNode(graph->headGraph, codNode, res);
    graph->headGraph = DeleteAdjacenceAllNodes(graph->headGraph, codNode, res);
    if (*res == true) graph->numNodes--;
    return graph;
}

/**
    @brief  Fun��o que elimina uma adjac�ncia de um grafo.
    @param  graph   - Apontador para o grafo.
    @param  origin  - ID do v�rtice de origem.
    @param  destiny - ID do v�rtice de destino
    @param  res     - Vari�vel de controlo de sucesso.
    @retval         - Apontador para o grafo.
**/
GR* DeleteAdjGraph(GR* graph, int origin, int destiny, bool* res) {
    *res = false;
    if (graph == NULL)return NULL;
    //Verificar se os v�rtices de origem e destino existem no grafo.
    Node* originNode = WhereIsNodeGraph(graph,origin);
    if (originNode == NULL)return graph;
    Node* destinyNode = WhereIsNodeGraph(graph, destiny);
    if (destinyNode == NULL)return graph;

    originNode->next = DeleteAdj(originNode->next, destiny, res);
    return graph;
}

/**
    @brief  Fun��o que procura um nodo num grafo.
    @param  graph  - Apontador para o grafo.
    @param  idNode - ID do nodo a procurar.
    @retval        - Retorna o nodo procurado, caso exista. Caso contr�rio, retorna NULL.
**/
Node* WhereIsNodeGraph(GR* graph, int idNode){
    if (graph == NULL)return NULL;
    return(WhereisNode(graph->headGraph, idNode));
}

/**
    @brief  Fun��o que insere uma adjac�ncia num grafo.
    @param  graph     - Apontador para o grafo.
    @param  idOrigin  - ID do v�rtice de origem.
    @param  idDestiny - ID do v�rtice de destino.
    @param  weight    - Peso da aresta.
    @param  res       - Vari�avel de controlo de sucesso.
    @retval           - Apontador para o grafo.
**/
GR* InsertAdjaGraph(GR* graph, int idOrigin, int idDestiny, int weight, bool* res) {
    *res = false;
    if (graph == NULL)return NULL;
    Node* originNode = WhereIsNodeGraph(graph, idOrigin);
    if (originNode == NULL)return graph;
    Node* destinyNode = WhereIsNodeGraph(graph, idDestiny);
    
    //Se n�o existir o v�rtice de destino, cria-o e insere-o no grafo.
    if (destinyNode == NULL) {
        destinyNode=CreateNode(idDestiny);
        graph=InsertNodeGraph(graph, destinyNode, res);
    }

    originNode->next = InsertAdj(originNode->next, idDestiny, weight);
    return graph;
}

/**
    @brief  Fun��o que aloca mem�ria para e inicia um grafo.
    @param  v - N�mero de v�rtices a incluir num grafo.
    @retval   - Apontador para o grafo.
**/
GR* CreateGraph(int v) {
    GR* aux = (GR*)malloc(sizeof(GR));;
    if (aux != NULL) {
        aux->headGraph = NULL;
        aux->numNodes = v;
    }
    return aux;
}

/**
    @brief  Fun��o que verifica se um nodo existe num grafo.
    @param  graph  - Apontador para o grafo.
    @param  idNode - ID do nodo a procurar.
    @retval  true  - Caso o nodo exista.
    @retval  false  - Caso o nodo n�o exista.
**/
bool ExistNodeGraph(GR* graph, int idNode) {
    if (graph == NULL)return false;
    return(ExistNode(graph->headGraph, idNode));
}

#pragma endregion
/**
    @brief Fun��o que mostra um grafo.
    @param graph - Apontador para o grafo a mostrar.
**/
void ShowGraph(GR* graph) {
    Node* current = graph->headGraph;
    while (current != NULL){

        printf("\nVertice %d->\n", current->value); //Mostra o v�rtice
        AdjListNode* adjacent = current->next;
        while (adjacent!=NULL)
        {
            printf("\t\t adjacent: %d \t  weight: %d\n", adjacent->value, adjacent->weight);
            adjacent = adjacent->next;
        }
        current = current->nextNode;
    }
}