# Projet Arcade - EPITECH

Ce dépôt contient le rendu du projet **Arcade** conforme au sujet officiel fourni par EPITECH.

## Objectif du projet

Créer un moteur de jeu capable de :
- Charger dynamiquement des bibliothèques de jeux (`.so`)
- Charger dynamiquement des bibliothèques graphiques (`.so`)
- Gérer un menu de sélection de jeu/librairie
- Proposer au moins **2 jeux** et **3 bibliothèques graphiques**
- Respecter les règles de compilation avec un seul Makefile à la racine

## Contenu

- `lib/` : contient toutes les bibliothèques dynamiques (.so)
- `Games/` : contient les jeux (ex. Snake, Démineur)
- `Display/` : contient les bibliothèques graphiques (SFML, SDL2, ncurses)
- `Core/` : contient le cœur du moteur
- `arcade` : binaire principal compilé
- `assets/` : fichiers nécessaires pour le rendu graphique (fontes, textures)
- `README.md` : ce fichier
- `rapport.pdf` : sujet officiel

## Lancement

```bash
make re
./arcade lib/arcade_sfml.so
```

## Jeux inclus

- Snake : jouable au clavier (flèches), vitesse réglée, score affiché
- Démineur : difficulté sélectionnable, navigation clavier (flèches + espace + F)

## Bibliothèques graphiques incluses

- SFML
- SDL2
- Ncurses

## Fonctionnalités clés

- Système de menu interactif pour lancer les jeux/librairies
- Changement de lib graphique et jeu à la volée
- Score dynamique
- Utilisation correcte des objets `DisplayObject`
- Chargement dynamique validé via `nm -D` et `dlopen/dlsym`

## Dépendances

- SFML
- SDL2
- ncurses
- C++17
- Linux compatible

## Auteur

- [Ton prénom / nom ici]
