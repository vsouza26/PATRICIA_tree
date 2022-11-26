#include "FILEHANDLER.hpp"

void FHandler::listaTraducoes()
{
  char k[30];
  for (int i = 0; i < 30; i++)
  {
    k[i] = '\0';
  }
  std::cin.ignore();
  std::cin.getline(k, 30);
  this->arvore->listTranslation(k);
}

void FHandler::insereTraducao()
{
  std::cin.ignore();
  char traducoes[500];
  char buffer[50];
  char t[30];
  char c[2];
  char classe[1];
  for (int i = 0; i < 30; i++)
  {
    t[i] = '\0';
  }
  std::cin.getline(t, 30);
  std::cin >> c;
  classe[0] = c[0];
  int num;
  std::cin >> num;
  std::cin.ignore(); // HACK PARA FAZER CIN FUNCIONAR COM O GETLINE
  for (int j = 0; j < 500; j++)
  {
    traducoes[j] = '\0';
  }

  for (int r = 0; r < num; r++)
  {
    for (int b = 0; b < 50; b++)
    {
      buffer[b] = '\0';
    }
    std::cin.getline(buffer, 50);
    for (int s = 0; s < 50; s++)
    {
      traducoes[r * 50 + s] = buffer[s];
    }
  }
  for (int s = 0; s < 500; s++)
  {
    //   std::cout << t << " pos: " << s << " :" << traducoes[s] << "\n";
  }
  this->arvore->insertNode(t, classe, num, traducoes);
}

void FHandler::listaPalavrasOrigem()
{
  char c;
  std::cin >> c;
  this->arvore->printTree(c);
}

FHandler::FHandler()
{
  this->arvore = new PATRICIATREE("saida.dat");
}

void FHandler::consultaClasse()
{
  char k[30];
  for (int i = 0; i < 30; i++)
  {
    k[i] = '\0';
  }
  std::cin.ignore();
  std::cin.getline(k, 30);
  this->arvore->listClass(k);
}

void FHandler::removePalavra()
{
  char k[30];
  for (int i = 0; i < 30; i++)
  {
    k[i] = '\0';
  }
  std::cin.ignore();
  std::cin.getline(k, 30);
  this->arvore->removeNode(k);
}

void FHandler::imprimeArvore()
{
  this->arvore->printTree();
}

void FHandler::listaClasse(){
  char classe, ordem;
  std::cin >> classe >> ordem;
  this->arvore->printTreeClasse(ordem,classe);
}