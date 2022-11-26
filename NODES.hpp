#pragma once
#include <iostream>
#include <string.h>
enum Type
{
    IntNode,
    ExtNode,
};
class Node
{
    Type tipo;
public:
    void setTipo(Type tipo);
    Type getTipo();
};

class INode : public Node
{
private:
    Node *esq, *dir;
    unsigned int index;
public:
    INode(unsigned int offset, Node *esq, Node *dir);
    unsigned int getIndex();
    Node *getEsq();
    Node *getDir();
    void setEsq(Node *esq);
    void setDir(Node *dir);
    void setIndex(int valor);
};

class FileNode
{
private:
    int numTraducoes; // Número de traduções disponíveis para a palavra
    char classeMorfologica[1];
    char piOriginal[30];     // Palavra em Idioma de origem
    char piDestino[50 * 10]; // Palavra em Idioma Destino (Podem Existir até 10 traduções da mesma palavra)
public:
    FileNode(char *classeMorfologica, char *piOriginal, int numTraducoes, char *piDestino);
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
    ENode(unsigned int offsetFile);
    unsigned int getOffset();
    void setOffset(unsigned int offset);
};
