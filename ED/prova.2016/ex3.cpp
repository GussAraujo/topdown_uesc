int ehvazia(){}

int main(int argc, char const *argv[])
{
  char op;
  double valor;

  while (cin >> op) {
    switch (op) {
    case 'BIPUSH':
      cin >> valor;
      empilhar(&p, valor);
      break;
    case 'IADD':
      double a = desempilhar(&p);
      double b = desempilhar(&p);
      empilhar(&p, (a + b));
      break;
    case 'ISUB':
      double a = desempilhar(&p);
      double b = desempilhar(&p);
      empilhar(&p, (a - b));
      break;
    default:
      break;
    }
  }
  

  return 0;
}
