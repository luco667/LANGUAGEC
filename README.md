# Programmation en C avec MinGW / GCC (Windows)

Guide complet pour installer **MinGW** avec GCC et configurer le **PATH**.

---

## Téléchargement

Télécharger MinGW depuis SourceForge :  
https://sourceforge.net/projects/mingw/

Fichier :
mingw-get-setup.exe

---

## Installation

### 1. Lancer l’installateur
- Ouvrir `w64devkit-x64-2.6.0.7z.exe`
- Cliquer sur **Install**

---

### 2. Configuration
- Laisser les options par défaut (ou modifier si nécessaire)
- Attendre la fin du téléchargement

---

### 3. Sélection des paquets

Dans le **MinGW Installation Manager** :

Installer au minimum :
- mingw32-base
- mingw32-gcc-g++
- mingw32-gcc-objc
- msys-base

Clic droit → **Mark for Installation**

---

### 4. Appliquer l’installation

- Cliquer sur la croix (X)
- Choisir **Review Changes**
- Cliquer sur **Apply**
- Attendre le téléchargement
- Cliquer sur **Close**

---

## Configuration du PATH

### 1. Ouvrir les variables d’environnement

- Clic droit sur **Ce PC**
- **Propriétés**
- **Paramètres système avancés**
- **Variables d’environnement**

---

### 2. Modifier `Path`

Dans **Variables système** :

- Sélectionner `Path`
- Cliquer sur **Modifier**
- Cliquer sur **Nouveau** (ou Edit Text selon version)

Ajouter :

C:\MinGW\bin  
C:\MinGW\msys\1.0\bin

---

### 3. Valider

- Cliquer sur **OK** partout
- Ne pas cliquer sur Cancel
- Redémarrer le PC (recommandé)

---

## Vérification

Ouvrir un terminal (cmd) :

gcc --version

---

## Résultat

- GCC installé
- MinGW fonctionnel
- Compilation possible depuis n’importe quel dossier

---

## Programmation

Créer `main.c` :

#include <stdio.h>

int main() {
    printf("Hello World\n");
    return 0;
}

Compiler :

gcc main.c -o main.exe

Exécuter :

main.exe

---

## ⚠️ Notes

- Si `gcc` n’est pas reconnu → PATH mal configuré
- Vérifier que `C:\MinGW\bin` est bien ajouté
- Redémarrer le terminal après modification
