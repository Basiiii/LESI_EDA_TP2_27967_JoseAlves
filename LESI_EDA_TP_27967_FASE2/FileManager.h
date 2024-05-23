#pragma once

#define FILE_SEPARATOR ';'

typedef struct NodeFile {
    int value;
}NodeFile;

typedef struct AdjListNodeFile {
    int value;
    int weight;
}AdjListNodeFile;

typedef struct GrFile {
    int v; //N�mero de v�rtices no grafo.
}GrFile;

/**
    @brief  Fun��o que importa dados de um ficheiro de texto e os coloca num grafo.
    @param  fileName - Nome do ficheiro a importar
    @param  res      - Vari�vel de controlo de sucesso.
    @retval          - Apontador para o grafo.
**/
GR* ImportData(char fileName[], bool* res);

bool SaveGraph(char fileName[], GR* graph);

bool OpenGraph(char* fileName[], GR* graph);