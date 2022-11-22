#include "main.hpp"
int main()
{
  PATRICIATREE ptree = PATRICIATREE("saida.dat");
  char palavraOriginal[30] = {'a', 'b', 'a', 'a', 'a'};
  char traducoes[500] = {'s', 'l', 'e', 'e', 'p'};
  char key1[30] = {'a', 'a', 'a', 'a', 'a'};
  char c[1] = {'c'};
  ptree.insertNode(palavraOriginal, c, 1, traducoes);
  ptree.insertNode(key1, c, 1, traducoes);
  ptree.insertNode(key1, c, 1, traducoes);
  ptree.printTree();
}