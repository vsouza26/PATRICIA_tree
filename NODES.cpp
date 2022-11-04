#include "NODES.hpp"

INode::INode(int offset, Node *esq, Node *dir)
{
    INode::setIndex(offset);
    INode::setDir(dir);
    INode::setEsq(esq);
};

void INode::setIndex(int index)
{
    this->index = index;
}

int INode::getIndex()
{
    return this->index;
}

void INode::setDir(Node *dir)
{
    this->dir = dir;
}

Node *INode::getDir()
{
    return this->dir;
}

void INode::setEsq(Node *esq)
{
    this->esq = esq;
}

Node *INode::getEsq()
{
    return this->esq;
}

FileNode::FileNode(int numTraducoes, char classeMorfologica, char *piOriginal, char *piDestino)
{
    FileNode::setNumTraducoes(numTraducoes);
    FileNode::setClasseMorfologica(classeMorfologia);
    FileNode::setPIDestino(piDestino);
    FileNode::setPIOriginal(piDestino);
}

int FileNode::getNumTraducoes()
{
    return this->numTraducoes;
}

unsigned int FileNode::getOffset(){
    return this->offset;
}

char FileNode::getClasseMorfologia()
{
    return this->classeMorfologia;
}

char *FileNode::getPIDestino()
{
    return this->piDestino;
}

char *FileNode::getPIOriginal()
{
    return this->piOriginal;
}

void FileNode::setNumTraducoes(int numTraducoes)
{
    if (numTraducoes < 11)
    {
        std::cerr << "Não pode haver mais traduções\n";
    }
    else
    {
        numTraducoes += 1;
    }
}

void FileNode::setPIDestino(char *piDestino)
{
    int numIndex = this->getNumTraducoes();
    if (numIndex <= 9)
    {
        int indexTraducao = 0;
        for (int i = 50 * numIndex; i < 50 * (numIndex +  1); i++)
        {
            this->piDestino[i] = piDestino[indexTraducao];
            indexTraducao++;
        }
        this->setNumTraducoes(numIndex + 1);
    } else {
        std::cerr << "Não é permitido inserir mais traduções";
    }
}

void FileNode::setPIOriginal(char *piOrigin)
{
    for(int i = 0; i < 30; i++){
        this->piOriginal[i] = piOrigin[i];
    }
}

void FileNode::setOffset(unsigned int offset){
    this->offset = offset;
}

void FileNode::setClasseMorfologica(char c){
    this->classeMorfologia = c;
}