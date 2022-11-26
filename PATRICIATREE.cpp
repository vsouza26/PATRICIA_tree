#include "PATRICIATREE.hpp"
// retorna o bit da posição i no caracter C (1 byte 8 bits).
int PATRICIATREE::bit(int i, char c)
{
  int pos = i;
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
  for (int k = (posBit / 8); k < 30; k++)
  {
    for (int p = posBit % 8; p <= 8; p++)
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
      fsni.seekg(nodeAux->getOffset() * sizeof(FileNode));
      FileNode fn;
      fsni.read((char *)&fn, sizeof(FileNode));
      fsni.close();
      if (!strcmp(key, fn.getPIOriginal()))
      {
        return fn;
      }
      else
      {
        std::cout << "Não há palavra pesquisada!\n";
        return FileNode(NULL, NULL, -1, NULL);
      }
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

// ARGUMENTO TRADUCOES PRECISA ESTAR FORMATADO DA MANEIRA CORRETA
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
    std::cout << "palavra inserida no dicionario: " << palavraOriginal << "\n";
  }
  else
  {
    if (insertNodeRec(this->raiz, palavraOriginal, classeMorfologica, numTraducoes, traducoes, 0))
    {
      std::cout << "palavra inserida no dicionario: " << palavraOriginal << "\n";
    } // pequeno hack**
  }
};

INode *PATRICIATREE::insertNodeRec(Node *node, char *palavraOriginal, char *classeMorfologica, int numTraducoes, char *traducoes, int index)
{
  if (node)
  {
    switch (node->getTipo())
    {
    case ExtNode:
    {
      ENode *aux = (ENode *)node;
      std::ifstream fsin(this->nomeArquivo, std::ios::app | std::ios::binary);
      fsin.seekg(aux->getOffset() * sizeof(FileNode));
      FileNode fn;
      fsin.read((char *)&fn, sizeof(FileNode));
      fsin.close();
      unsigned int indexBit = diffBit(1, palavraOriginal, fn.getPIOriginal()); // referente a esse pedaço do codigo**
      if (indexBit == 241)
      {
        std::cout << "palavra ja existente: " << palavraOriginal << std::endl;
        return NULL;
      }
      // SE A INSERÇÃO NÃO É DE NÓS REPETIDOS
      std::ofstream fson(this->nomeArquivo, std::ios::out | std::ios::app | std::ios::binary);
      FileNode newWrite = FileNode(classeMorfologica, palavraOriginal, numTraducoes, traducoes);
      int offset = fson.tellp() / sizeof(FileNode);
      fson.write((char *)&newWrite, sizeof(FileNode));
      fson.close();
      ENode *newENode = new ENode(offset);
      if (bit(indexBit % 8, palavraOriginal[indexBit / 8]))
      {
        INode *newINode = new INode(indexBit, NULL, newENode);
        if (this->raiz == node)
        {
          newINode->setEsq(node);
          this->raiz = newINode;
        }
        return newINode;
      }
      else
      {
        INode *newINode = new INode(indexBit, newENode, NULL);
        if (this->raiz == node)
        {
          newINode->setDir(node);
          this->raiz = newINode;
        }
        return newINode;
      }
      break;
    }
    case IntNode:
    {
      INode *nodeaux = (INode *)node;
      if (bit(nodeaux->getIndex() % 8, palavraOriginal[nodeaux->getIndex() / 8]))
      {
        INode *nodex = insertNodeRec(nodeaux->getDir(), palavraOriginal, classeMorfologica, numTraducoes, traducoes, nodeaux->getIndex());
        if (!nodex)
          return NULL;
        if (nodex->getIndex() > nodeaux->getIndex())
        {
          // Checa qual filho está vago para inserir
          if (!nodex->getDir())
          {
            nodex->setDir(nodeaux->getEsq());
            nodeaux->setDir(nodex);
          }
          else
          {
            nodex->setEsq(nodeaux->getDir());
            nodeaux->setDir(nodex);
          }
        }
        else if (nodeaux == this->raiz)
        {
          if (!nodex->getDir())
          {
            nodex->setDir(nodeaux->getDir());
            nodeaux->setDir(nodex);
            this->raiz == nodex;
          }
          else
          {
            nodex->setEsq(nodeaux->getEsq());
            nodeaux->setEsq(nodex);
            this->raiz == nodex;
          }
        }
        else
        {
          return nodex;
        }
      }
      else
      {
        INode *nodex = insertNodeRec(nodeaux->getEsq(), palavraOriginal, classeMorfologica, numTraducoes, traducoes, nodeaux->getIndex());
        if (!nodex)
          return NULL;
        if (nodex->getIndex() > nodeaux->getIndex())
        {
          // Checa qual filho está vago para inserir
          if (!nodex->getDir())
          {
            nodex->setDir(nodeaux->getEsq());
            nodeaux->setEsq(nodex);
          }
          else
          {
            nodex->setEsq(nodeaux->getDir());
            nodeaux->setEsq(nodex);
          }
        }
        else if (nodeaux == this->raiz)
        {
          if (!nodex->getDir())
          {
            nodex->setDir(nodeaux);
            this->raiz = nodex;
            return NULL;
          }
          else
          {
            nodex->setEsq(nodeaux);
            this->raiz = nodex;
            return NULL;
          }
        }
        else
        {
          return nodex;
        }
      }
    }
    }
  }
}

void PATRICIATREE::printTree(char c)
{
  // std::cout << "Endereço da raiz: " << this->raiz << "\n";
  if (c == 'c')
  {
    printTreeRecC(this->raiz);
  }
  else
    printTreeRecD(this->raiz);
}

void PATRICIATREE::printTreeRecC(Node *node)
{
  if (node)
  {
    switch (node->getTipo())
    {
    case (IntNode):
    {
      INode *nodeaux = (INode *)node;
      printTreeRecC(nodeaux->getDir());
      printTreeRecC(nodeaux->getEsq());
      break;
    }
    case (ExtNode):
    {
      ENode *nodeaux = (ENode *)node;
      std::ifstream fsm(nomeArquivo, std::ios::binary | std::ios::in);
      fsm.seekg(nodeaux->getOffset() * sizeof(FileNode));
      FileNode aux;
      fsm.read((char *)&aux, sizeof(FileNode));
      fsm.close();
      std::cout << aux.getPIOriginal() << "\n";
      /*                << "ENode offset: " << nodeaux->getOffset() << "\n"
                      << "ENode address: " << node << "\n\n"; */
      break;
    }
    default:
      break;
    }
  }
}

void PATRICIATREE::printTreeRecC(Node *node, char c)
{
  if (node)
  {
    switch (node->getTipo())
    {
    case (IntNode):
    {
      INode *nodeaux = (INode *)node;
      /*      std::cout << "INode index: " << nodeaux->getIndex() << " Endr: " << nodeaux << "\n"
                      << "Dir: " << nodeaux->getDir() << " Esq: " << nodeaux->getEsq() << "\n\n"; */
      printTreeRecC(nodeaux->getDir(), c);
      printTreeRecC(nodeaux->getEsq(), c);
      break;
    }
    case (ExtNode):
    {
      ENode *nodeaux = (ENode *)node;
      std::ifstream fsm(nomeArquivo, std::ios::binary | std::ios::in);
      fsm.seekg(nodeaux->getOffset() * sizeof(FileNode));
      FileNode aux;
      fsm.read((char *)&aux, sizeof(FileNode));
      fsm.close();
      if (c == aux.getClasseMorfologica())
      {
        std::cout << aux.getPIOriginal() << "\n";
      }
      break;
    }
    default:
      break;
    }
  }
}

void PATRICIATREE::printTreeRecD(Node *node)
{
  if (node)
  {
    switch (node->getTipo())
    {
    case (IntNode):
    {
      INode *nodeaux = (INode *)node;
      /*      std::cout << "INode index: " << nodeaux->getIndex() << " Endr: " << nodeaux << "\n"
                      << "Dir: " << nodeaux->getDir() << " Esq: " << nodeaux->getEsq() << "\n\n"; */
      printTreeRecD(nodeaux->getEsq());
      printTreeRecD(nodeaux->getDir());
      break;
    }
    case (ExtNode):
    {
      ENode *nodeaux = (ENode *)node;
      std::ifstream fsm(nomeArquivo, std::ios::binary | std::ios::in);
      fsm.seekg(nodeaux->getOffset() * sizeof(FileNode));
      FileNode aux;
      fsm.read((char *)&aux, sizeof(FileNode));
      fsm.close();
      std::cout << aux.getPIOriginal() << "\n";
      /*                << "ENode offset: " << nodeaux->getOffset() << "\n"
                      << "ENode address: " << node << "\n\n"; */
      break;
    }
    default:
      break;
    }
  }
}

void PATRICIATREE::printTreeRecD(Node *node, char c)
{
  if (node)
  {
    switch (node->getTipo())
    {
    case (IntNode):
    {
      INode *nodeaux = (INode *)node;
      /*      std::cout << "INode index: " << nodeaux->getIndex() << " Endr: " << nodeaux << "\n"
                      << "Dir: " << nodeaux->getDir() << " Esq: " << nodeaux->getEsq() << "\n\n"; */
      printTreeRecD(nodeaux->getEsq(), c);
      printTreeRecD(nodeaux->getDir(), c);
      break;
    }
    case (ExtNode):
    {
      ENode *nodeaux = (ENode *)node;
      std::ifstream fsm(nomeArquivo, std::ios::binary | std::ios::in);
      fsm.seekg(nodeaux->getOffset() * sizeof(FileNode));
      FileNode aux;
      fsm.read((char *)&aux, sizeof(FileNode));
      fsm.close();
      if (c == aux.getClasseMorfologica())
      {
        std::cout << "classe morfologica: " << c << " ";
        std::cout << aux.getPIOriginal() << "\n";
      }
      /*                << "ENode offset: " << nodeaux->getOffset() << "\n"
                      << "ENode address: " << node << "\n\n"; */
      break;
    }
    default:
      break;
    }
  }
}
void PATRICIATREE::removeNode(char *palavraOriginal)
{
  removeNodeRec(this->raiz, palavraOriginal);
}

Node *PATRICIATREE::removeNodeRec(Node *node, char *palavraOriginal)
{
  if (node)
  {
    switch (node->getTipo())
    {
    case IntNode:
    {
      INode *nodeAux = (INode *)node;
      if (bit(nodeAux->getIndex() % 8, palavraOriginal[nodeAux->getIndex() / 8]))
      {
        Node *rtrnPointer = removeNodeRec(nodeAux->getDir(), palavraOriginal);
        if (!rtrnPointer)
        {
          ENode *node1 = (ENode *)nodeAux->getEsq();
          if (nodeAux == this->raiz)
          {
            this->raiz = node1;
          }
          delete nodeAux;
          std::cout << "palavra removida:" << palavraOriginal << "\n";
          return node1;
        }
        else
        {
          nodeAux->setDir(rtrnPointer);
          return nodeAux;
        }
      }
      else
      {
        Node *rtrnPointer = removeNodeRec(nodeAux->getEsq(), palavraOriginal);
        if (!rtrnPointer)
        {
          ENode *node1 = (ENode *)nodeAux->getDir();
          if (nodeAux == this->raiz)
          {
            this->raiz = node1;
          }
          delete nodeAux;
          std::cout << "palavra removida:" << palavraOriginal << "\n";
          return node1;
        }
        else
        {
          nodeAux->setEsq(rtrnPointer);
          return nodeAux;
        }
      }
      break;
    }
    case ExtNode:
    {
      ENode *nodeAux = (ENode *)node;
      std::ifstream fsni(this->nomeArquivo);
      fsni.seekg(nodeAux->getOffset() * sizeof(FileNode));
      FileNode fn;
      fsni.read((char *)&fn, sizeof(FileNode));
      fsni.close();
      if (!strcmp(palavraOriginal, fn.getPIOriginal()))
      {
        return NULL;
      }
      else
      {
        std::cout << "palavra inexistente no dicionario: " << palavraOriginal << "\n";
        return node;
      }
      break;
    }
    default:
      std::cout << "palavra inexistente no dicionario: " << palavraOriginal << "\n";
      return node;
      break;
    }
  }
}

void PATRICIATREE::listTranslation(char *k)
{
  FileNode nd = searchTree(k);
  if (nd.getNumTraducoes() != -1)
  {
    std::cout << "traducoes da palavra: " << nd.getPIOriginal() << "\n";
    for (int i = 0; i < nd.getNumTraducoes(); i++)
    {
      for (int j = 0; j < 50; j++)
      {
        if (nd.getPIDestino()[i * 50 + j] == '\0')
        {
          std::cout << "\n";
          break;
        }
        else
        {
          std::cout << nd.getPIDestino()[i * 50 + j];
        }
      }
    }
  }
}

void PATRICIATREE::printTreeClasse(char c, char c2)
{
  if (c == 'c')
  {
    printTreeRecC(this->raiz, c2);
  }
  else
  {
    printTreeRecD(this->raiz, c2);
  }
}

void PATRICIATREE::listClass(char *k)
{
  FileNode nd = searchTree(k);
  if (nd.getNumTraducoes() != -1)
  {
    std::cout << "classe da palavra: " << k << ": ";
    switch (nd.getClasseMorfologica())
    {
    case ('a'):
      std::cout << "adjetivo\n";
      break;
    case ('s'):
      std::cout << "substantivo\n";
      break;
    case ('v'):
      std::cout << "verbo\n";
      break;
    default:
      break;
    }
  }
}

void PATRICIATREE::printTree()
{
  std::queue<char *> *fila = new std::queue<char *>;
  printTreeRec(this->raiz, fila);
  while (char *f = fila->front())
  {
    fila->pop();
    std::cout << f << " ";
    int k = 0;
    while (f[k] != '\0')
    {
    //  std::cout << f[k] << " ";
      for (int i = 1; i <= 8; i++)
      {
        int t = (int)f[k];
        t -= 96;
        char d = (char)t;
        std::cout << bit(i,d);
      }
      k++;
      std::cout << " ";
    }
    delete f;
    std::cout << "00000000";
    std::cout << "\n";
  }
}

void PATRICIATREE::printTreeRec(Node *node, std::queue<char *> *fila)
{
  if (!node)
    return;
  switch (node->getTipo())
  {
  case IntNode:
  {
    INode *inode = (INode *)node;
    std::cout << "bit: " << inode->getIndex() << " fesq: ";
    Node *nodeesq = inode->getEsq();
    Node *nodedir = inode->getDir();
    if (nodeesq->getTipo() == IntNode)
    {
      INode *inodeesq = (INode *)nodeesq;
      std::cout << inodeesq->getIndex() << " ";
    }
    else
    {
      ENode *enodeesq = (ENode *)nodeesq;
      std::ifstream fs(this->nomeArquivo, std::ios::binary | std::ios::in);
      fs.seekg(enodeesq->getOffset() * sizeof(FileNode));
      FileNode nd;
      fs.read((char *)&nd, sizeof(FileNode));
      fs.close();
      std::cout << nd.getPIOriginal() << " ";
    }
    std::cout << "fdir: ";

    if (nodedir->getTipo() == IntNode)
    {
      INode *inodedir = (INode *)nodedir;
      std::cout << inodedir->getIndex() << "\n";
    }
    else
    {
      ENode *enodedir = (ENode *)nodedir;
      std::ifstream fs(this->nomeArquivo, std::ios::binary | std::ios::in);
      fs.seekg(enodedir->getOffset() * sizeof(FileNode));
      FileNode nd;
      fs.read((char *)&nd, sizeof(FileNode));
      fs.close();
      std::cout << nd.getPIOriginal() << "\n";
    }
    printTreeRec(inode->getEsq(), fila);
    printTreeRec(inode->getDir(), fila);
    break;
  }
  case ExtNode:
  {
    ENode *enode = (ENode *)node;
    std::ifstream fs(this->nomeArquivo, std::ios::binary | std::ios::in);
    fs.seekg(enode->getOffset() * sizeof(FileNode));
    FileNode nd;
    fs.read((char *)&nd, sizeof(FileNode));
    fs.close();
    std::cout << nd.getPIOriginal() << "\n";
    char *elem = new char[30];
    for (int i = 0; i < 30; i++)
    {
      elem[i] = nd.getPIOriginal()[i];
    }
    fila->push(elem);
    break;
  }
  }
}