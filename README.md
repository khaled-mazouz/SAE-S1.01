# SAE
Ce projet universitaire consiste à développer un programme capable d’interpréter dix commandes permettant de gérer des participants, des concours, leurs scores et l’évolution de leur classement.

Commandes disponibles :

"EXIT" : met fin à l’exécution du programme.

"INSCRIRE" : suivie du nom et du prénom d’un participant, permet de l’inscrire.

"PARTICIPANTS" : affiche la liste des participants ayant obtenu un score non nul à au moins un concours, ainsi que le nombre de concours concernés pour chacun d’eux.

"CREER" : suivie du nom d’un concours, permet de créer ce concours.

"CONCOURS" : affiche la liste des concours créés, ainsi que le nombre de participants ayant obtenu un score non nul à chacun d’eux.

"GAIN" : suivie de l’identifiant d’un participant, de l’identifiant d’un concours et d’un nombre de points, permet d’ajouter ces points au score existant du participant pour le concours concerné.

"SCORE" : suivie de l’identifiant d’un participant, affiche les concours auxquels il a participé ainsi que les scores correspondants.

"CLASSEMENT" : suivie de l’identifiant d’un concours, affiche le classement des participants pour ce concours, avec leur nom, leur prénom et leur score.

"COMPARAISON" : suivie des identifiants de deux concours, permet de comparer les scores des participants en calculant le rapport entre le score obtenu au second concours et celui obtenu au premier. La comparaison prend en compte les participants ayant obtenu un score non nul à au moins l’un des deux concours. Le cas où le score du premier concours est nul doit être géré afin d’éviter une division par zéro.

"BILAN ": suivie de l’identifiant d’un concours, affiche son classement et indique, pour chaque participant, le nombre de places gagnées ou perdues depuis la dernière exécution de cette commande pour ce même concours.
