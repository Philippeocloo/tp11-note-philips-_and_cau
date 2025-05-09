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

# Troubleshooting

Si ça ne compile pas, il est possible qu'il vous manque des dépendances:

- Linux (Ubuntu)
```bash
    sudo apt install libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev libwayland-dev libxkbcommon-dev
```