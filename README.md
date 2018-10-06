# Make-forwarder
Creates dsiware forwarders to nds roms in the sd card to be launched via the nds-bootstrap

# Linux/Mac support
To compile the program for those platforms, download the source and run the command ```g++ *.cpp -o make_forwarder```

# Usage
## Pc part
Make sure to have the [template.nds](https://github.com/edo9300/Rungame-template) file in the same folder as the executable.
Drag your rom on the exe, and it will create a "title" folder.
Copy the created folder in the root of your sd card.
## Dsi part
When you first start the app, you'll have to set up the paths to the game and the bootstrap. If you are already using [TWiLight Menu++](https://github.com/RocketRobz/TWiLightMenu), then the bootstrap will be in the "_nds" folder, otherwise download it from [ahezard's repo](https://github.com/ahezard/nds-bootstrap/releases). This setup is required only at the first launch, if you want to redo the setup, you can do it by keeping a pressed during the boot of the app.

## Missing features
Having the possibilty to change the per-game settings of the bootsrtap from the app itself. The only way for now is to manually edit the "bootsrtap.ini" file in the "data" folder of the app.

# Credits
Tuxality: He has made the tool to create a valid tmd for the dsiware [maketmd](https://github.com/Tuxality/maketmd), which i directly included in my program.
Ahezard: He has made the python script (that i ported to cpp) to fix the header of the dsiwares.
