# Test de primalité
Test de primalité basé sur les algorithmes de Fermat et de Miller-Rabin et utilise l'algorithme de Square and multiply pour l'exponentiation modulaire.

## Installation
Le programme est distributé sous forme d'une archive .zip, pour executer à partir de cette archive il faut :
```bash
unzip LARBI_HAMITOUCHE.zip
cd LARBI_HAMITOUCHE/
make
```


## Usage

```bash
./prim -f [n] [k] # Tester si n est premier pour k fois en utilisant le test de Fermat.
./prim -m [n] [k] # Tester si n est premier pour k fois en utilisant le test de Miller-Rabin.
./prim -s [n] [exp] [m] # Calculer (n^exp modulo m) en utilisant Square and multiply.
./prim -g [n] # Générer un nombre aléatoire entre 0 et n-1

```
