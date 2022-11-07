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

FileNode::FileNode(char* classeMorfologica, char *piOriginal, int numTraducoes, char *piDestino)
{
    this->setNumTraducoes(numTraducoes);
    this->setPIDestino(piDestino);
    this->setClasseMorfologica(classeMorfologica);
    this->setPIOriginal(piOriginal);
}

FileNode::FileNode(){}

int FileNode::getNumTraducoes()
{
    return this->numTraducoes;
}

char FileNode::getClasseMorfologica()
{
    return this->classeMorfologica[0];
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
        this->numTraducoes = numTraducoes;
    }
    else
    {
        std::cerr << "Não pode haver mais traduções\n";
    }
}

void FileNode::setPIDestino(char *piDestino)
{
    strcpy(this->piDestino, piDestino);
    //   int numIndex = this->getNumTraducoes();
    //   bool endEntry = false;
    //   if (numIndex <= 9)
    //   {
    //       for (int i = 50 * numIndex; i < 50 * (numIndex + 1); i++)
    //       {
    //           if (piDestin[i%50] != '\0' && !endEntry)
    //           {                                          // acha o fim da string a ser inserida e zera os outros caracteres
    //               this->piDestino[i] = piDestin[i % 50]; // i%50 sempre começará no 0 para n valores de i
    //               std::cout << "Inserindo " << piDestin[i%50] << " na pos: " << i%50 << "\n";
    //           }
    //           else
    //           {
    //               this->piDestino[i] = '\0';
    //               std::cout << "Zerando as posições " << i << " pos. relativa:  " << i%50 << "\n";
    //               endEntry = true;
    //           }
    //       }
    //       this->setNumTraducoes(numIndex + 1);
    //}
    // else
    //{
    //    std::cerr << "Não é permitido inserir mais traduções";
    //}
}

void FileNode::setPIOriginal(char *piOrigin)
{
    bool endEntry = false;
    for (int i = 0; i < 30; i++)
    {
        if (piOrigin[i] != '\0' && !endEntry) // acha o fim da string a ser inserida e zera os outros caracteres
            this->piOriginal[i] = piOrigin[i];
        else
        {
            this->piOriginal[i] = '\0';
            endEntry = true;
        }
    }
}

void FileNode::setClasseMorfologica(char *c)
{
    strcpy(this->classeMorfologica,c);
}

ENode::ENode(int offsetFile)
{
    this->offsetFile = offsetFile;
}
