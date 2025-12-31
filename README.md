# Projet étudiant — Implémentation du jeu Ricochet Robots

Projet réalisé à Centrale Nantes dans le cadre du module SMP  
Date de rendu : 14 mai 2025.

## Contexte

Ce dépôt correspond à un TP réalisé en groupe dans le cadre de la formation d’ingénieur à Centrale Nantes.  
Le projet consiste en l’implémentation du jeu *Ricochet Robots* en plateau 3D, incluant la simulation des déplacements des robots, la gestion des cibles et la génération aléatoire du plateau.

Les règles du jeu imposent des déplacements contraints jusqu’à un obstacle, avec pour objectif de minimiser le nombre de mouvements afin d’atteindre les cibles dans l’ordre défini.

## Fonctionnalités principales

- Simulation des déplacements des robots selon les règles du jeu
- Gestion des cibles à atteindre
- Génération aléatoire du plateau
- Évaluation des solutions en fonction du nombre de déplacements


# Compilation

1. Créer un dossier build à la racine du projet et y accéder:
```bash
    mkdir build && cd build
```

2. Générer les fichiers de compilation
```bash
    cmake ..
```

3. Compiler
```bash
    make -j
```

4. Profiter
```bash
    ./gui
```

5. Tester
```bash
    make unit_tests && ./unit_tests
```

# Troubleshooting

Si ça ne compile pas, il est possible qu'il vous manque des dépendances:

- Linux (Ubuntu)
```bash
    sudo apt install libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev libwayland-dev libxkbcommon-dev
```
