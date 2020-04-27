# Tests de primalité de Fermat et de Miller-Rabin

Implémentations de tests de primalité de nature probabiliste utilisant le Petit Théorème de Fermat et l'exponentiation modulaire. 

### Algorithmes utilisés 
 - **Square and multiply** *exponentiation modulaire*
  - **Algorithme de Fermat** *basé sur le Petit Théorème de Fermat*
  - **Algorithme de Miller-Rabin** *exploite quelques propriété suplémentaire au Petit Théorème de Fermat*

## Getting Started

Ces instructions vont vous permettre d'avoir une copie du répertoire du projet en local.

### Prérequis
Pour pouvoir installer ce tester de primalité, il faut avoir un compilataur du langage C (le **Makefile** fournis est basé sur *gcc*) installé ainsi que la librairie GMP.
Installation de GCC:
```
sudo apt install gcc
```
Installation de GMP:
* Récupérer l'archive de [GMP](https://gmplib.org/#DOWNLOAD) 
* Extraire le contenu de l'archive
* Générer un Makefile et compiler la bibliothèque
```
./configure
make
```

* Tester que tous s'est bien passé
```
make check
```

* Installation de la bibliothèque
```
sudo make install 
```

### Installation
Le programme est distributé sous forme d'une archive .zip, pour executer à partir de cette archive il faut :

Extraire le contenu de l'archive

```
unzip DEBIANE_LARBI_HAMITOUCHE
```
Se rendre dans répertoire extrait

```
cd DEBIANE_LARBI_HAMITOUCHE/
```

Compiler le projet

```
make
```
Pour utiliser le test de primalité, il suffit au choix :

* Ajouter l'exécutable obtenu dans le dossier des exécutable 

```
sudo mv prim /bin
```
* Ajouter le répertoire courant au path

```
PATH=$PATH!:~/path_to_current_directory
```
## Usage
```bash
./prim -f [n] [k] # Tester si n est premier pour k fois en utilisant le test de Fermat.
./prim -m [n] [k] # Tester si n est premier pour k fois en utilisant le test de Miller-Rabin.
./prim -s [n] [exp] [m] # Calculer (n^exp modulo m) en utilisant Square and multiply.
./prim -g [n] # Générer un nombre aléatoire entre 0 et n-1

```

## Construit avec

* [GNU MP](https://gmplib.org/) - The GNU  Multiple Precision Arithmetic Library
* [C Langage](https://www.gnu.org/software/gnu-c-manual/gnu-c-manual.html) - Langage de programmation utilisé

## Autheurs

* **Akli HAMITOUCHE** - [GitHub Link](https://github.com/m4ssi)

* **Mahdi LARBI** - [Github Link](https://github.com/medish)

* **Mohamed Ramdane DEBIANE** - [Github Link](https://github.com/Khalimouh)

