#include "main.hpp"
int main()
{
  FHandler *fh = new FHandler();
  char c;
  while (std::cin >> c)
  {
    switch (c)
    {
    case 'i':
      fh->insereTraducao();
      break;
    case 'a':
      fh->listaClasse();
      break;
    case 'c':
      fh->consultaClasse();
      break;
    case 'l':
      fh->listaPalavrasOrigem();
      break;
    case 't':
      fh->listaTraducoes();
      break;
    case 'r':
      fh->removePalavra();
      break;
    case 'p':
      fh->imprimeArvore();
      break;
    case 'e':
      std::cout << "\n";
      return 0;
      break;
    default:
      break;
    }
  }
}