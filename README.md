# IFT611 Task Manager
### Alexandre Roussel (ROUA2814)
### Alexandre Beauquel (BEAA3410)
### Sébastien O’Neel (ONES2901)    
## Installation:
#### Linux:
Dans home:

`wget https://usherbrooke-my.sharepoint.com/:u:/r/personal/ones2901_usherbrooke_ca/Documents/QT.zip?csf=1&web=1&e=vketbt`

`sudo mv QT.zip /opt/.`

`cd /opt`

`sudo unzip QT.zip`

#### Windows
Installer WSL:

Dans `powershell`:

`wsl --install`

Installer Ubuntu:

Microsoft store -> Ubuntu -> Install

`wsl --install -d Ubuntu`

une fois Ubuntu d'installer répéter les mêmes étapes que sous-Linux

## Execution:
`git clone https://github.com/abeauquel/ift611.git`

`cd ift611`

`cmake .`

`make`

`./ift611`
