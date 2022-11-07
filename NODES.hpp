#include <iostream>
#include <string.h>
class Node
{
};

class INode : public Node
{
private:
    Node *esq, *dir;
    int index;

public:
    INode(int offset, Node *esq, Node *dir);
    int getIndex();
    Node *getEsq();
    Node *getDir();
    void setEsq(Node *esq);
    void setDir(Node *dir);
    void setIndex(int valor);
};

class FileNode : public Node
{
private:
    int numTraducoes; // Número de traduções disponíveis para a palavra
    char classeMorfologica[1];
    char piOriginal[30];     // Palavra em Idioma de origem
    char piDestino[50 * 10]; // Palavra em Idioma Destino (Podem Existir até 10 traduções da mesma palavra)

public:
    FileNode(char* classeMorfologica, char *piOriginal, int numTraducoes, char * piDestino);
    FileNode();
    int getNumTraducoes();
    char getClasseMorfologica();
    char *getPIOriginal();
    char *getPIDestino();
    void setClasseMorfologica(char *c);
    void setNumTraducoes(int numTraducoes);
    void setPIOriginal(char *piOriginal);
    void setPIDestino(char *piDestino);
};

class ENode : public Node
{
private:
    unsigned int offsetFile;
public:
    ENode(int offsetFile);
    unsigned int getOffset();
    void setOffset(unsigned int offset);};
