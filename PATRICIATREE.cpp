#include "PATRICIATREE.hpp"
// retorna o bit da posição i no caracter C (1 byte 8 bits).
int PATRICIATREE::bit(int i, char c)
{
  if (i == 0)
    return 0;
  int k = (int)c;
  for (int j = 1; j <= 8 - i; i++)
    k = k / 2;
  return k % 2;
}
// I precisa ser um inteiro positivo diferente de 0.
int PATRICIATREE::diffBit(int i, char *key1, char *key2)
{
  int posBit = i;
  for (int k = i - 1; k < 30; k++)
  {
    for (int p = 1; p <= 8; p++)
    {
      if (bit(p, key1[k]) == bit(p, key2[k]))
      {
        posBit++;
      }
      else
      {
        return posBit;
      }
    }
  }
  return posBit;
}

PATRICIATREE::PATRICIATREE(std::string nomeArquivo)
{
  this->nomeArquivo = nomeArquivo;
  this->nBitsChave = 30;
  this->raiz = NULL;
}

int PATRICIATREE::writeToFile(char *palavraOriginal, char *classeMorfologica, int numTraducoes, char *traducoes)
{
  std::ofstream fd(this->nomeArquivo, std::ios::binary | std::ios::app); // File Descriptor que abre o arquivo em binário e em modo de adiciona ao final
  FileNode fn = FileNode(classeMorfologica, palavraOriginal, numTraducoes, traducoes);
  int pointer = fd.tellp();
  fd.write((char *)&fn, sizeof(FileNode));
  fd.close();
  return pointer;
}

FileNode PATRICIATREE::readFromFile(int offset)
{
  std::ifstream fd(this->nomeArquivo, std::ios::binary | std::ios::in); // File descriptor que lê o arquivo nomeArquivo no offset e retorna o FileNode
  fd.seekg(offset);
  FileNode fn; // FileNode a ser populado
  fd.read((char *)&fn, sizeof(FileNode));
  fd.close();
  return fn;
}
// key Deve ser um array de tamanho 30.
FileNode PATRICIATREE::searchTreeRec(Node *Node, char *key)
{
  if (Node)
  {
    switch (Node->getTipo())
    {
    case IntNode:
    {
      INode *nodeAux = (INode *)Node;
      if (bit(nodeAux->getIndex() % 8, key[nodeAux->getIndex() / 8]))
        return searchTreeRec(nodeAux->getDir(), key);
      else
        return searchTreeRec(nodeAux->getEsq(), key);
      break;
    }
    case ExtNode:
    {
      ENode *nodeAux = (ENode *)Node;
      std::ifstream fsni(this->nomeArquivo);
      fsni.seekg(nodeAux->getOffset());
      FileNode fn;
      fsni.read((char *)&fn, sizeof(FileNode));
      fsni.close();
      return fn;
      break;
    }
    default:
      return FileNode(NULL, NULL, -1, NULL);
      break;
    }
  }
  else
  {
    return FileNode(NULL, NULL, -1, NULL);
  }
}
// Key é um char array de tamanho 30
FileNode PATRICIATREE::searchTree(char *key)
{
  return this->searchTreeRec(this->raiz, key);
}

// ARGUEMENTO TRADUCOES PRECISA ESTAR FORMATADO DA MANEIRA CORRETA
void PATRICIATREE::insertNode(char *palavraOriginal, char *classeMorfologica, int numTraducoes, char *traducoes)
{
  if (!this->raiz)
  {
    FileNode fn = FileNode(classeMorfologica, palavraOriginal, numTraducoes, traducoes);
    std::ofstream fsnode(this->nomeArquivo, std::ios::binary);
    unsigned int offset = fsnode.tellp();
    fsnode.write((char *)&fn, sizeof(FileNode));
    fsnode.close();
    ENode *en = new ENode(offset);
    this->raiz = en;
  }
  else
  {
    insertNodeRec(this->raiz, palavraOriginal, classeMorfologica, numTraducoes, traducoes, 0); //pequeno hack**
  }
};

void PATRICIATREE::insertNodeRec(Node *node, char *palavraOriginal, char *classeMorfologica, int numTraducoes, char *traducoes, int index)
{
  if (node)
  {
    switch (node->getTipo())
    {
    case ExtNode:
    {
      ENode *aux = (ENode *)node;
      std::ifstream fsin(this->nomeArquivo, std::ios::app | std::ios::binary);
      fsin.seekg(aux->getOffset());
      FileNode fn;
      fsin.read((char *)&fn, sizeof(FileNode));
      fsin.close();
      unsigned int indexBit = diffBit(index + 1, palavraOriginal, fn.getPIOriginal()); //referente a esse pedaço do codigo**
      if (indexBit == 241)
      {
        std::cout << "palavra ja existente: " << palavraOriginal << std::endl;
        return;
      }
      // SE A INSERÇÃO NÃO É DE NÓS REPETIDOS
      std::ofstream fson(this->nomeArquivo, std::ios::out | std::ios::app | std::ios::binary);
      FileNode newWrite = FileNode(classeMorfologica, palavraOriginal, numTraducoes, traducoes);
      int offset = fson.tellp();
      fson.write((char *)&newWrite, sizeof(FileNode));
      fson.close();
      ENode *newENode = new ENode(offset);
      if (bit(indexBit % 8, palavraOriginal[indexBit / 8]))
      {

        INode *newINode = new INode(indexBit, node, newENode);
        if (node == this->raiz)
        {
          this->raiz = newINode;
        }
        node = newINode;
      }
      else
      {
        INode *newINode = new INode(indexBit, newENode, node);
        if (node == this->raiz)
        {
          this->raiz = newINode;
        }
        node = newINode;
      }
      break;
    }
    case IntNode:
    {
      INode *nodeaux = (INode *)node;
      if (bit(nodeaux->getIndex() % 8, palavraOriginal[nodeaux->getIndex() / 8]))
      {
        insertNodeRec(nodeaux->getDir(), palavraOriginal, classeMorfologica, numTraducoes, traducoes, nodeaux->getIndex());
      }
      else
      {
        insertNodeRec(nodeaux->getEsq(), palavraOriginal, classeMorfologica, numTraducoes, traducoes, nodeaux->getIndex());
      }
      break;
    }
    }
  }
}

void PATRICIATREE::printTree()
{
  std::cout << "Endereço da raiz: " << this->raiz << "\n";
  printTreeRec(this->raiz);
}

void PATRICIATREE::printTreeRec(Node *node)
{
  if (node)
  {
    switch (node->getTipo())
    {
    case (IntNode):
    {
      INode *nodeaux = (INode *)node;
      std::cout << "INode index: " << nodeaux->getIndex() << "\n"
                << "Dir: " << nodeaux->getDir() << " Esq: " << nodeaux->getEsq() << "\n\n";
      printTreeRec(nodeaux->getDir());
      printTreeRec(nodeaux->getEsq());
      break;
    }
    case (ExtNode):
    {
      ENode *nodeaux = (ENode *)node;
      std::cout << "ENode offset: " << nodeaux->getOffset() << "\n"
                << "ENode address: " << node << "\n\n";
      break;
    }
    default:
      break;
    }
  }
}