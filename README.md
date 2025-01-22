1. Structure du jeu :
	•	Plateau de jeu : Un plateau est représenté par une matrice (tableau 2D) où chaque case peut contenir un pion numéroté ou être vide. La case vide sera désignée par une valeur spéciale (par exemple, 0).
	•	Pions numérotés : Les pions sont placés sur le plateau, chaque pion ayant un numéro unique (par exemple, de 1 à N).
	•	Score : Le score du joueur dépend des cases adjacentes à la case vide. Le score est calculé en fonction de la proximité des pions autour de cette case.

2. Initialisation :
	•	Un plateau de jeu est créé et rempli de pions numérotés.
	•	Une case aléatoire est laissée vide.

3. Règles du jeu :
	•	Placement des pions : Le joueur place les pions sur le plateau, en s’assurant qu’une case reste vide à la fin du placement.
	•	Calcul du score : Le score d’un joueur est basé sur la somme des numéros des pions adjacents à la case vide. Les cases adjacentes peuvent être à gauche, droite, en haut ou en bas de la case vide (selon la taille du plateau).
