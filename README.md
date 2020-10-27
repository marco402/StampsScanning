
# Project StampsScanning(// Written by Marc Prieur (marco40_github@sfr.fr))
*****************************************************************************************
     # **For use StampsScanning.exe, download and unzip "delivery for windows.zip"             
     # **Pour utiliser StampsScanning.exe, télécharger et decompresser "delivery for windows.zip"
*****************************************************************************************

** En Français plus loin... 

# --------------------------------Version 1.0.1-------------------------------------
- Load file example at the first load.
- Add cleanMatrix with debug window if DEBUGCLEAN.
- Form stamp add average perforation.
# --------------------------------Version 1.0-------------------------------------

# General principle:
- This software separates stamps scanned together.
- At the end of the treatment, each stamp is displayed in an independent window for recording.
- If the .ini file(see Memorization parameters) has not been created yet,
an example stamp will be loaded at first launch.

# Installing the compiled version:
There is no installation program, just unzip "delivery for windows.zip".

# Write to disk by the code stampsScanning:
- No key in registry.
- Only the file .ini() is created in the same place as the .exe at the first output of the application.
- Other entries are the stamps upon validation by the user. 
# Details:
## Main window:
At launch, this window is displayed, consisting of:
- A toolbar,
- one area for the image
- A status bar.
The toolbar consists of:
- A button to open a file of scanned stamps.
- A start button.
- A 90° step rotation button.
- A drop-down list of 1 to 10 pixels for the border around the stamp(5 by default recommended value).
- A drop-down list to choose the year for the stamps. 
- A button that closes all open stamp windows.
- A button to cancel current treatments.
- A button to access this help.
- A list of English or French language choices.
- A detection threshold selection bar if displayed (see Storing parameters)
The status bar displays:
- The file loaded.
- A scroll bar.
- Different messages.

## Stamp window
Same composition as main window.
The toolbar consists of:
- A text box to enter its reference(only mandatory).
- A text box to enter its name.
- A text box to enter its year.
- A button to save the stamp.
- A 90° step rotation knob.
- A list indicating the dentition for each side of the stamp.
- A button to change the backup folder.
- A button that calibrates the perforation calculation.
The status bar displays:
- The backup folder.
- The saved file with its dimensions.
- The file is in jpg compression by default of QT.

# Saving stamps:
The stamps are saved in the folder stored in the file in the . ini and may be changed by the button in the stamp window.
If several stamps are displayed and the file has been changed, after saving a first stamp, restart the treatment to update the path on the others.
The file name consists of the reference followed by the name and year separated by a _.
The file is in jpeg format.
If the save went well, the stamp name turns green.

# Use:
Scan of stamps:
 It is advisable to scan the stamps in bitmap 200 ppm 32bits.
 It is necessary to place stamps on such a black background and homogeneous as possible(personally I return the cover of the scanner).
 The stamps don’t need to be properly aligned,
it is especially necessary to respect a gap of 3/4 mm minimum.

# Perforation Calibration:
It proved necessary to calibrate the perforation (linked to the scanner?), to do this
choose a good condition whole number of teeth for 2cm.
The calibration command will ask you to enter this number of teeth.
This information can quickly be erroneous depending on the quality of the dentition.
This information is saved in the . ini file and can be used if 2cm is not desired.

# Memorization parameters:
A stampsScanning.ini file allows you to save different parameters:
Under the key ParamIde:
The last selected border width.
The last path used
The last used path of the scan file input folder.
The last used path of the stamps file output folder.
The last language selected.
Under the key ParamProcess :
Modified from main window :
The ratio for perforation (equal to 2cm/2.54 at departure)
modified by the calibration button.
Le seuil de détection si calibrationThreshold=true(threshold).
The number of millimetres for the vertical scan which must be less than the smallest patch, the smaller this value the longer the processing will be (sweepStamp_mm).

# For debug:
Editable directly in the .ini file(close the application before load .ini).
The displayDebugContour key to true displays the contour of the detected stamps on the loaded image. 

The calibrationThreshold to true key displays the detection threshold selection bar.
When the bar is moved, the new value is displayed in the status bar, when the mouse is released, a window is displayed in black and white depending on the threshold.
Obliteration around the edges of the patch can disturb the contour. 
___________________________________________________________________________________________

# --------------------------------Version 1.0.1-------------------------------------
- Chargement d'un fichier exemple au premier lancement.
- Affichage de la moyenne des 4 dentitions.
# --------------------------------Version 1.0-------------------------------------

# Description:

# Principe général:
- Ce logiciel permet de séparer des timbres scannés ensembles.
- A l'issu du traitement, chaque timbre est affiché dans une fenêtre indépendante pour enregistrement.
- Si le fichier .ini(voir Mémorisation des paramètres) n'a pas encore été crée, un timbre exemple sera chargé au premier lancement.

# Installation de la version compilée:
Il n'y a pas de programme d'installation, il suffit de dézipper "delivery for windows.zip".

# Ecriture sur le disque par le code stampsScanning.
- Aucune clé dans la base de registre.
- Seul le fichier .ini(voir Mémorisation des paramètres) est crée au même endroit que le .exe à la première sortie de l'application.
- Les autres écritures sont les timbres sur validation de l'utilisateur.

# Détails:
## Fenêtre principale:
Au lancement, cette fenêtre est affichée,elle est constituée de:
- Une barre d'outils,
- Une zone pour l'image
- Une barre d'état.
La barre d'outils est constituée de:
- Un bouton pour ouvrir un fichier de timbres scannés.
- Un bouton de démarrage.
- Un bouton de rotation par pas de 90°.
- Une liste déroulante de 1 à 10 pixels pour la bordure qui entoure le timbre(5 par défaut valeur conseillée).
- Un bouton qui permet de fermer toutes les fenêtres timbre ouvertes.
- Un bouton pour annuler les traitements en cours.
- Un bouton pour accéder à cet aide.
- Une liste de choix du langage Anglais ou Français.
- Une barre de sélection du seuil de détection si affichée (voir Mémorisation des paramètres).
La barre d'état permet d'afficher:
- Le fichier chargé.
- Une barre de défilement.
- Différents messages.
## Fenêtre timbre
Même composition que la fenêtre principale.
La barre d'outils est constituée de:
- Une zone de texte pour saisir sa référence(seule obligatoire).
- Une zone de texte pour saisir son nom.
- Une zone de texte pour saisir l'année du timbre.
- Un bouton pour sauvegarder le timbre.
- Un bouton de rotation par pas de 90°.
- Une liste qui indique la dentition pour chaque coté du timbre.
- Un bouton qui permet de changer le dossier de sauvegarde.
- Un bouton qui permet d'étalonner le calcul de la dentition.
La barre d'état permet d'afficher:
- Le chemin de sauvegarde.
- Le fichier enregistré avec ses dimensions.
- Le fichier est en jpeg compression par défaut de QT.

# Sauvegarde des timbres :
Les timbres sont sauvegardés dans le dossier mémorisé dans le fichier indiqué dans le .ini et peut-être changé par le bouton de la fenêtre timbre.
Si plusieurs timbres sont affichés et que le dossier à été changé, après avoir sauvé un premier timbre, relancer le traitement pour mettre le chemin a jour sur les autres.
Le nom de fichier est constitué de la référence suivit du nom et de l'année séparés pas un _.
Le fichier est au format jpeg.
Si la sauvegarde s'est bien passée,le nom du timbre devient vert.

# Utilisation:
Scannage des timbres:
Il est conseillé de scanner les timbres en bitmap 200 ppm 24bits.
Il est nécessaire de poser les timbres sur un fond aussi noir et homogène que possible(personnellement je retourne le couvercle du scanner).
Les timbres n'ont pas besoin d'être bien alignés.
Il est surtout nécessaire de respecter un écartement de 3/4 mm minimum.

# Calibration de la dentition
Il s'est avéré nécessaire d'étalonner la dentition(lié au scanner?), pour cela choisissez un timbre en bon état avec un nombre entier de dents pour 2cm.
La commande d'étalonnage vous demandera de saisir ce nombre de dents.
Cette information peut rapidement être erronée suivant la qualité de la dentition.
Cette information est enregistrée dans le fichier .ini et peux être utilisée si on ne souhaite pas 2cm.

# Mémorisation des paramètres:
Un fichier stampsScanning.ini permet d'enregistrer différents paramètres:
Sous la clé ParamIde:
La dernière largeur de bordure sélectionnée(border).
Le dernier chemin utilisé du dossier en entrée des fichiers scan(currentPathLoad).
Le dernier chemin utilisé du dossier en sortie pour les timbres(currentPathSave).
Le dernier langage sélectionné(currentLanguage).
Sous la clé ParamProcess :
Modifiables à partir de la fenêtre principale :
Le rapport pour la dentition(égal à 2cm/2.54 au départ)éventuellement modifié par le bouton d'étalonnage(ratioPerforation).
Le seuil de détection si calibrationThreshold=true(threshold).
Le nombre de millimètre pour le balayage vertical qui doit être inférieur au plus petit timbre, plus cette valeur est petite plus le traitement sera long(sweepStamp_mm).

# Pour du debug :
Modifiable directement dans le fichier .ini(fermer l'application avant de charger le .ini).
La clé displayDebugContour à true affiche le contour des timbres détectés sur l'image de départ.
La clé calibrationThreshold à true affiche la barre de sélection du seuil de détection.
Sur déplacement de la barre, la nouvelle valeur est affichée dans la barre d'état, sur relâchement de la souris, une fenêtre s'affiche en noir et blanc fonction du seuil.
Une oblitération sur le pourtour du timbre peut perturber le contour. 

__________________________________________________________________________
# Development environnement

- Windows.
   - Program developed in C++ and QT.
   - Ide QT créator or visual studio.

# Installation

- Installation of QT.

- if visual studio:
        - installation of visual studio version 15.9.14  or more recent.
        - installation of qt-vsaddin-msvc2017-2.3.2.vsix or more recent function of visual studio version.
		Warning
			regenerate everything on change of compilation constant.
		Warning
			languages are at exe level.
# delivery
        
- create a directory delivery
- copy StampsScanning.exe in delivery
- open a console:
        - cd ....\delivery>
        - C:\Qt\5.13.0\msvc2017_64\bin\windeployqt.exe StampsScanning.exe
- return to windows
		- transfert directories help and languages to delivery.
		- to help keep only *.qch and */qhc
		- to languages keep only *.qm and *.png

___________________________________________________________________________________________

