#include <iostream>

class Node
{
};

class INode : public Node
{
private:
    Node *esq, *dir;
    int index;
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
    unsigned int offset;
    int numTraducoes; // Número de traduções disponíveis para a palavra
    char classeMorfologia;
    char piOriginal[30];     // Palavra em Idioma de origem
    char piDestino[50 * 10]; // Palavra em Idioma Destino (Podem Existir até 10 traduções da mesma palavra)
    FileNode(int numTraducoes, char classeMorfologia, char *piOriginal, char *piDestino);
    unsigned int getOffset();
    int getNumTraducoes();
    char getClasseMorfologia();
    char *getPIOriginal();
    char *getPIDestino();
    void setOffset(unsigned int offset);
    void setClasseMorfologica(char c);
    void setNumTraducoes(int numTraducoes);
    void setPIOriginal(char *piOriginal);
    void setPIDestino(char *piDestino);
};

class ENode : public Node
{
private:
    unsigned int offset;
    FileNode fileNode;
    ENode(int numTraducoes, char classeMorfologia, char *piOriginal, char *piDestino);
    unsigned int getOffset();
    void setOffset(unsigned int offset);
};

