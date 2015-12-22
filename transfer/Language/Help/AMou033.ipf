.************************************************
.*
.*   Copyright 2002-2006 nb software
.*
.*   Help for AMouse
.************************************************

:userdoc.

:h1 res=10 id=aboutMain.AMouse - Configuration avanc�e de la souris
:i1 id=aboutMain.AMouse - Configuration avanc�e de la souris
:p.:artwork name='C:\work\c\amouse\Language\Help\amouse.bmp' runin align=left.
Ce programme peut �tre utilis� pour la configuration du comportement de la
roulette des souris "Wheel mouse" (comme les "Intelli-Mouse"). 
Il permet &colon. 

:ul compact.
:li.le contr�le des op�rations de la roulette,
:li.le param�trage du nombre d'incr�ments de d�filement,
:li.la d�finition des fonctions des boutons 3 � 5 de la souris.
:eul.

:h1 res=1900 id=wheel1.Roulette (pages 1, 2 et 3)
:i1 id=wheel1.Roulette (pages 1, 2 et 3)
:p.Cette page sert � param�trer les actions de la souris initi�es par les 
mouvements de la roulette. 
Il y a une page pour chacune des combinaisons de touche et roulette 
support�es.
:p.Une explication plus d�taill�e de chaque action vous sera 
pr�sent�e en cliquant sur l'un des �l�ments de la liste 
ci-dessous &colon. 

:ul compact.
:li.:link reftype=hd refid=no_func.D�sactiv�e:elink.
:li.:link reftype=hd refid=keyboard.Action sur la fen�tre active:elink.
:li.:link reftype=hd refid=pointer.Action sur la fen�tre sous le pointeur de souris:elink.
:li.:link reftype=hd refid=msgscroll.Messages d�filement:elink.
:li.:link reftype=hd refid=msgline.Messages clavier:elink.
:li.:link reftype=hd refid=msgpage.D�filement de la page enti�re par unit�:elink.
:li.:link reftype=hd refid=msgvol.R�glage du volume audio:elink.
:li.:link reftype=hd refid=scrollitem.Vitesse de d�filement:elink.
:li.:link reftype=hd refid=cancel.D�faire:elink.
:li.:link reftype=hd refid=standard.Par d�faut:elink.
:eul.
:note.
ces pages ne sont visibles que si une souris avec roulette a �t� 
d�tect�e. 

:h2 res=1901 id=no_func.Mode de fonctionnement - D�sactiv�e
:p.Si l'option est activ�e, les mouvements de roulette seront 
ignor�s par le syst�me. 

:h2 res=1902 id=msgscroll.Mode de fonctionnement - Messages d�filement
:p.Si l'option est activ�e, un message de d�filement 
(WM_VSCROLL/WM_HSCROLL)  sera envoy� aux fen�tres de textes, 
simulant un d�placement de barre de d�filement. 

:h2 res=1903 id=msgline.Mode de fonctionnement - Messages clavier (curseurs)
:p.Si l'option est activ�e, un message WM_CHAR sera envoy� aux 
fen�tres de texte, simulant l'appui sur une touche de d�placement, 
dans la mesure o� les fen�tres supportent cette fonction. 

:h2 res=1904 id=msgpage.Mode de fonctionnement - D�filement de la page enti�re par unit�
:p.Si l'option est activ�e, un message WM_CHAR sera envoy� aux 
fen�tres de texte, simulant l'appui sur la touche Page Haut ou Page 
Bas, dans la mesure o� les fen�tres supportent cette fonction. 

:h2 res=1905 id=msgvol.Mode de fonctionnement - R�glage du volume audio
:p.Si l'option est activ�e, le fait d'actionner la roulette 
modifiera le volume sonore g�n�ral. 

:h2 res=1906 id=keyboard.Action sur la fen�tre active
:p.Si l'option est activ�e, la barre de d�filement verticale de la 
fen�tre active sera actionn�e. 
:p.Avec certaines souris, la fen�tre se trouvant sous le pointeur de 
souris peut �tre activ�e en cliquant sur la roulette. 
:note.pour certaines fen�tres, il se peut que les 'sous-fen�tres' 
contiennent aussi des barres de d�filement (des cadres dans Netscape 
Communicator, par exemple). Dans ce cas, la fen�tre qui a �t� 
s�lectionn�e en dernier est celle qui sera prise en compte. 

:h2 res=1907 id=pointer.Action sur la fen�tre sous le pointeur de souris
:p.Si l'option est activ�e, la barre de d�filement verticale de la 
fen�tre qui se trouve sous le pointeur de souris sera actionn�e. 
:note.la fen�tre n'a pas besoin d'�tre active ni compl�tement visible
� ce moment l�. 

:h2 res=1908 id=scrollitem.Vitesse de d�filement
:p.� l'aide du :hp2.bouton rotatif:ehp2., vous pouvez s�lectionner 
le nombre de lignes qui seront pass�es si la roulette est boug�e 
d'un cran. 

:h2 id=cancel.D�faire
:p.
:p.S�lectionnez D�faire pour restaurer les valeurs qu'avaient les 
param�tres avant les derni�res modifications. 


:h2 id=standard.Par d�faut
:p.Les param�tres par d�faut seront restaur�s. 


:h1 res=2100 id=wheel2.Roulette (page 4)
:i1 id=wheel2.Roulette (page 4)
:p.Cette page est utilis�e pour d�finir les valeurs de d�marrage du 
pilote, valides � l'amor�age de l'ordinateur. 
:p.Les param�trages seront effectu�s en s�lectionnant les boutons 
correspondant sur cette page. 
:p.Une explication plus d�taill�e de chaque action vous sera 
pr�sent�e en cliquant sur l'un des �l�ments de la liste 
ci-dessous &colon. 
:ul compact.
:li.:link reftype=hd refid=scroll_vert.D�filement vertical:elink.
:li.:link reftype=hd refid=scroll_horz.D�filement horizontal:elink.
:li.:link reftype=hd refid=accel_delay.D�lai d'acc�l�ration du d�filement:elink.
:li.:link reftype=hd refid=accel_value.V�locit� de l'acc�l�ration du d�filement:elink.
:li.:link reftype=hd refid=trackball.Nombre de roulettes:elink.
:li.:link reftype=hd refid=cancel.D�faire:elink.
:li.:link reftype=hd refid=standard.Par d�faut:elink.
:eul.
:note.
cette page n'est visible que si une souris avec roulette a �t� 
d�tect�e. 

:h2 res=2101 id=scroll_vert.Valeurs au d�marrage - D�filement vertical
:p.Si l'option est activ�e, actionner la roulette d'une souris avec 
une seule roulette r�sultera en un d�filement vertical. 

:h2 res=2102 id=scroll_horz.Valeurs au d�marrage - D�filement horizontal
:p.Si l'option est activ�e, actionner la roulette d'une souris avec 
une seule roulette r�sultera en un d�filement horizontal. 

:h2 res=2103 id=accel_delay.D�lai d'acc�l�ration du d�filement (D�lai d'activation)
:p.Si la roulette est actionn�e rapidement et plus longtemps que le 
d�lai, le nombre de lignes utilis�es pour le d�filement seront 
contin�ment accrues. 
Le d�lai peut aller de 100 � 2000 ms. 

:h2 res=2104 id=accel_value.V�locit� de l'acc�l�ration du d�filement (Valeur de l'acc�l�ration)
:p.Cette glissi�re fixe le nombre utilis� pour l'accroissement des 
unit�s de d�filement, si la roulette est rapidement actionn�e. 

:h2 res=2105 id=trackball.Nombre de roulettes
:p.Certaines souris sont incapables de retourner leur nombre de 
roulettes ou l'existence d'une boule de commande (trackball) au 
pilote de souris. 
Dans ce cas il est possible de d�finir cette propri�t� par 
l'interm�diaire de cette option. 

:h1 res=2300 id=wheel3.Roulette (page 5)
:i1 id=wheel3.Roulette (page 5)
:p.Cette page est utilis�e pour d�finir les exceptions au 
comportement de la roulette pour certaines applications. 
Si vous actionnez la roulette de la souris, dans la liste de cette 
page, une description d'un contr�le ou d'une fen�tre sera 
recherch�e. 
Ici, la :hp2.Description:ehp2. sera parcourue jusqu'� ce qu'une 
correspondance avec l'application sous le pointeur de souris soit 
trouv�e. 
.br
S'il n'y a pas de correspondance, la liste par d�faut 
d':hp2.AMouse:ehp2.  (d�finie dans 
:font facename=Courier size=14x14.AMouRes.rc:font facename=default.) 
sera prise en compte. 
Le texte descriptif de la liste est juste employ� pour pour une 
identification plus ais�e par l'utilisateur, le nom est donc 
arbitraire; il se peut qu'il y ait des doublons. 
:p.Le param�trage peut �tre fait par s�lection des boutons 
respectifs de cette page. 
:p.Une explication plus d�taill�e de chaque contr�le sera affich�e 
si vous cliquez sur l'un des �l�ments de la liste ci-dessous &colon. 
:ul compact.
:li.:link reftype=hd refid=wheel_up.&uarrow.:elink.
:li.:link reftype=hd refid=wheel_down.&darrow.:elink.
:li.:link reftype=hd refid=wheel_delete.Suppression:elink.
:li.:link reftype=hd refid=wheel_insert.Insertion:elink.
:li.:link reftype=hd refid=cancel.D�faire:elink.
:eul.
:note.
Cette page est visible uniquement si une roulette a �t� d�tect�e 
pour la souris. 

:p.:hp7.Description des champs:ehp7.
:p.Le comportement est affich� dans la bo�te du bas. 
La colonne de gauche d�finit la fen�tre ou le contr�le qui r�agira 
au tour de roulette.
Voici la signification des diff�rents �l�ments &colon. 
:ul compact.
:li.:hp2.Application:ehp2.
.br
Nom de l'application (par ex. :font facename=Courier size=14x14.PROGRAMM.EXE:font facename=default.). 
Si ce champ est laiss� vide, le r�sultat de comparaison sera 
toujours VRAI. 
Ce champ doit �tre vide pour les classes du WPS. 
:li.:hp2.Classe:ehp2.
.br
Classe de fen�tre de la fen�tre ou du contr�le. 
Ici doit �tre entr� soit le nom de la classe (respecter la casse !) 
soit l'identificateur pr�c�d� d'un &osq.&numsign.&csq.&per. 
Si ce champ est laiss� vide, le r�sultat de comparaison sera 
toujours VRAI. 
:li.:hp2.Classe parente:ehp2.
.br
Classe de fen�tre parente de la fen�tre ou du contr�le. 
Ici doit �tre entr� soit le nom de la classe (respecter la casse !) soit 
l'identificateur pr�c�d� d'un &osq.&numsign.&csq.&per. 
Si ce champ est laiss� vide, le r�sultat de comparaison sera toujours VRAI. 
:li.:hp2.Option:ehp2.
.br
Une option sera trouv�e ici si n�cessaire pour une &osq.RelationV&csq. ou 
&osq.RelationH&csq. sp�cifique. 
Dans tous les autres cas, ce champ restera vide. 
:eul.
:p.La colonne de droite d�finit l'action initi�e par la roulette. 
Voici la signification des diff�rents �l�ments &colon. 
:ul compact.
:li.:hp2.Mode:ehp2.
.br
D�finit le type de message � envoyer � la fen�tre ou au contr�le. 
.br
:hp2.D�filement:ehp2. sera utilis� si sur la page 
:link reftype=hd refid=wheel1.Roulette 1:elink. le mode op�ratoire 
:link reftype=hd refid=msgscroll.Messages d�filement:elink. a �t� 
s�lectionn�. 
.br
:hp2.Curseur:ehp2. r�agit sur les 
:link reftype=hd refid=msgline.Messages clavier:elink.&per. 
.br
:hp2.Page:ehp2.r�agit sur :link reftype=hd refid=msgpage.D�filement 
d'une page enti�re par unit� de d�filement:elink.&per. 
.br
:hp2.D�filement ou Curseur:ehp2. r�agit, si le mode op�ratoire 
s�lectionn� est soit :link reftype=hd refid=msgscroll.Messages 
d�filement:elink. ou soit :link reftype=hd refid=msgline.Messages 
clavier:elink.&per. 
L':hp2.ensemble:ehp2. r�agit sur tous les param�tres. 
:li.:hp2.RelationV (respectivement RelationH):ehp2. 
.br
D�finit si le message doit �tre envoy� directement � la fen�tre ou 
au contr�le, ou si une recherche plus approfondie doit �tre faite 
dans la hi�rarchie de la fen�tre. 
Voici la signification des diff�rents �l�ments &colon. 
:ul compact.
:li.:hp2.Aucun:ehp2. &colon. le message sera envoy� directement au 
contr�le trouv�. 
:li.:hp2.Parent:ehp2. &colon. un parent correspondant sera recherch� 
dans la liste de description. 
:li.:hp2.Propri�taire:ehp2. &colon. un propri�taire correspondant 
sera recherch� dans la liste de description. 
:li.:hp2.Suivant:ehp2. &colon. la recherche se poursuivra selon 
l'"ordre-z" des autres contr�les qui se trouveraient aussi sous le 
pointeur de souris. 
:li.:hp2.CB suivante:ehp2.&colon. uniquement utilis� pour les listes 
combo. Il agit � la base comme :hp2.Suivant:ehp2., mais traite la 
zone invisible sous le champ d'entr�e si la bo�te de liste ne 
s'affiche pas. 
:li.:hp2.Soeur[Option]:ehp2.&colon. une fen�tre soeur sera 
recherch�e dans la liste de description avec le nom de classe d�fini 
par le champ d'entr�e d' :hp2.option:ehp2.&per. 
:eul.
:li.:hp2.OptionV / OptionH:ehp2.
.br
Contient une option d�pendant du type de message param�tr�. 
Voir plus bas. 
:li.:hp2.Haut / Bas, Gauche / Droit:ehp2.
.br
D�finit le message envoy� � la fen�tre ou au contr�le. 
Ci-apr�s sont pr�sent�s les diff�rents messages disponibles &colon. 
:ul compact.
:li.:hp2.WM_NULL:ehp2.&colon. aucun message sera envoy�. Utilis� 
normalement lorsque pour :hp2.RelationV:ehp2./:hp2.RelationH:ehp2. 
l'attribut :hp2.Aucun:ehp2. est utilis�&per. 
:li.:hp2.WM_CONTROL:ehp2.&colon. un code clavier est envoy� 
directement au pilote de clavier. 
Les options suivantes sont possibles &colon. 
:ul compact.
:li.:hp2.page:ehp2. &colon. sont envoy�s les codes clavier 
PgHaut/PgBas. 
:li.:hp2.curseur haut/bas:ehp2. &colon. sont envoy�s les codes 
clavier Haut/Bas. 
:li.:hp2.curseur gauche/droit:ehp2. &colon. sont envoy�s les codes 
clavier Gauche/Droite. 
:li.:hp2.multi curseur haut/bas:ehp2. &colon. sont envoy�s les codes 
clavier Haut/Bas. 
Le nombre de messages envoy� est d�fini par les param�tres de la 
page :link reftype=hd refid=scrollitem.Vitesse de d�filement:elink.&per. 
:li.:hp2.multi curseur gauche/droit:ehp2. &colon. sont envoy�s les 
codes clavier Gauche/Droite. 
Le nombre de messages envoy� est d�fini par les param�tres dans 
:link reftype=hd refid=scrollitem.Vitesse de d�filement:elink.&per. 
:eul.
:li.:hp2.WM_VSCROLL:ehp2. &colon. un message de d�filement 
vertical est envoy� � la barre de d�filement verticale. 
:li.:hp2.WM_HSCROLL:ehp2. &colon. un message de d�filement 
horizontal est envoy� � la barre de d�filement horizontal. 
:li.:hp2.N x WM_VSCROLL:ehp2. &colon. comme :hp2.WM_VSCROLL:ehp2., 
mais le nombre de messages est d�fini par les param�tres de la page 
:link reftype=hd refid=scrollitem.Vitesse de d�filement:elink.&per. 
:li.:hp2.N x WM_HSCROLL:ehp2. &colon. comme :hp2.WM_HSCROLL:ehp2., 
mais le nombre de messages est d�fini par les param�tres de la page 
:link reftype=hd refid=scrollitem.Vitesse de d�filement:elink.&per. 
:li.:hp2.WM_CHAR:ehp2. &colon. un message caract�re est envoy�. Les 
m�mes options que pour :hp2.WM_CONTROL:ehp2. sont possibles. 
:eul.
:eul.

:p.:hp7.Exemples:ehp7.
:p.� cause un bug dans les anciennes versions de Mozilla (version 
1.3 et ant�rieures), le d�filement horizontal en utilisant la 
m�thode usuelle des messages WM_SCROLL ne fonctionne pas. 
Une solution de remplacement vous est propos�e dans les deux �crans 
suivants. 
:p.:artwork name='C:\work\c\amouse\Language\Help\Mozilla_Line_033.bmp' align=left.
:p.Cette entr�e fonctionne si sur la page 
:link reftype=hd refid=wheel1.Roulette 1:elink. le mode op�ratoire 
:hp2.Messages d�filement:ehp2. ou :hp2.Messages clavier:ehp2. a �t� 
s�lectionn�. 
Dans ce cas, les messages de curseurs horizontaux et verticaux sont 
envoy�s au parent (&odq.multi curseur&cdq.). 
Mozilla est identifi� si :hp2.Classe:ehp2. ainsi que :hp2.Classe 
parente:ehp2. sont de type :hp2.MozillaWindowClass:ehp2.&per. 

:p.:artwork name='C:\work\c\amouse\Language\Help\Mozilla_Page_033.bmp' align=left.
:p.Pour un d�filement page par page (:hp2.Mode = Page:ehp2.), un 
message caract�re PgHaut/PgBas est envoy� dans le cas d'un 
d�filement vertical. 
:p.:artwork name='C:\work\c\amouse\Language\Help\Command_Line_033.bmp' align=left.
:p.Si vous actionnez la roulette sur une fen�tre de ligne de 
commande, le comportement par d�faut est de faire d�filer le contenu 
de la fen�tre (si les barres de d�filement sont pr�sentes). 
Les param�tres affich�s ici provoquent le d�filement de l'historique 
des commandes � la place. 

:h2 res=2313 id=wheel_up.&uarrow. (D�placement de l'entr�e vers le haut) 
:p.D�place l'entr�e s�lectionn�e dans la liste d'applications une 
position plus haut.

:h2 res=2314 id=wheel_down.&darrow. (D�placement de l'entr�e vers le bas) 
:p.D�place l'entr�e s�lectionn�e dans la liste d'applications une 
position plus bas. 

:h2 res=2316 id=wheel_delete.Suppression 
:p.Suppression de l'entr�e s�lectionn�e dans la liste � gauche de ce 
bouton. 

:h2 res=2315 id=wheel_insert.Insertion 
:p.Insertion d'une nouvelle entr�e � la liste � gauche de ce bouton. 

:h1 res=2700 id=insertappl.Insertion d'application 
:i1 id=insertappl.Insertion d'application 
:p.Cette bo�te de dialogue est utilis�e pour ins�rer une nouvelle 
d�finition de comportement de la roulette pour une application 
s�lectionn�e. 
La signification des contr�les suivent les description � la page 
:link reftype=hd refid=wheel3.Roulette 5:elink.&per. 
:hp2.Description:ehp2. pourra �tre utilis� pour l'insertion de tout 
texte d�fini par l'utilisateur identifiant les entr�es de la bo�te 
de liste de la page :link reftype=hd refid=wheel3.Roulette 
5:elink.&per. 

:h1 res=1500 id=keys1.Boutons (page 1)
:i1 id=keys1.Boutons (page 1)
:p.Cette page est utilis�e pour d�finir les actions � affecter aux 
boutons 3, 4 et 5 de la souris.  
:p.Les param�trages seront effectu�s en s�lectionnant les boutons 
correspondant sur cette page. 
:p.Une explication plus d�taill�e de chaque action vous sera 
pr�sent�e en cliquant sur l'un des �l�ments de la liste 
ci-dessous &colon. 
:ul compact.
:li.:link reftype=hd refid=button3.Bouton 3:elink.
:li.:link reftype=hd refid=button4.Bouton 4:elink.
:li.:link reftype=hd refid=button5.Bouton 5:elink.
:li.:link reftype=hd refid=button6.Bouton 6:elink.
:li.:link reftype=hd refid=button7.Bouton 7:elink.
:li.:link reftype=hd refid=button8.Bouton 8:elink.
:li.:link reftype=hd refid=button9.Bouton 9:elink.
:li.:link reftype=hd refid=button10.Bouton 10:elink.
:li.:link reftype=hd refid=cbutton3.Ctrl+Bouton 3:elink.
:li.:link reftype=hd refid=cbutton4.Ctrl+Bouton 4:elink.
:li.:link reftype=hd refid=cbutton5.Ctrl+Bouton 5:elink.
:li.:link reftype=hd refid=cbutton6.Ctrl+Bouton 6:elink.
:li.:link reftype=hd refid=cbutton7.Ctrl+Bouton 7:elink.
:li.:link reftype=hd refid=cbutton8.Ctrl+Bouton 8:elink.
:li.:link reftype=hd refid=cbutton9.Ctrl+Bouton 9:elink.
:li.:link reftype=hd refid=cbutton10.Ctrl+Bouton 10:elink.
:li.:link reftype=hd refid=abutton3.Alt+Bouton 3:elink.
:li.:link reftype=hd refid=abutton4.Alt+Bouton 4:elink.
:li.:link reftype=hd refid=abutton5.Alt+Bouton 5:elink.
:li.:link reftype=hd refid=abutton6.Alt+Bouton 6:elink.
:li.:link reftype=hd refid=abutton7.Alt+Bouton 7:elink.
:li.:link reftype=hd refid=abutton8.Alt+Bouton 8:elink.
:li.:link reftype=hd refid=abutton9.Alt+Bouton 9:elink.
:li.:link reftype=hd refid=abutton10.Alt+Bouton 10:elink.
:li.:link reftype=hd refid=keycombset3.Set 3:elink.
:li.:link reftype=hd refid=keycombset4.Set 4:elink.
:li.:link reftype=hd refid=keycombset5.Set 5:elink.
:li.:link reftype=hd refid=keycombset6.Set 6:elink.
:li.:link reftype=hd refid=keycombset7.Set 7:elink.
:li.:link reftype=hd refid=keycombset8.Set 8:elink.
:li.:link reftype=hd refid=keycombset9.Set 9:elink.
:li.:link reftype=hd refid=keycombset10.Set 10:elink.
:li.:link reftype=hd refid=keycomb.Key combination:elink.
:li.:link reftype=hd refid=cancel.D�faire:elink.
:li.:link reftype=hd refid=standard.Par d�faut:elink.
:eul.
:note.
cette page n'est visible que si une souris avec roulette a �t� 
d�tect�e. 

:p.:hp2.Fonctions des boutons:ehp2.
:p.Sont disponibles les fonctions suivantes &colon. 

:ul.
:li.:hp5.Couper:ehp5.
.br
Affectation de la fonction "Couper" vers le presse-papier 
(Maj-Suppr). 
:li.:hp5.Copier:ehp5.
.br
Affectation de la fonction "Copier" vers le presse-papier 
(Ctrl-Inser). 
:li.:hp5.Coller:ehp5.
.br
Affectation de la fonction "Coller" vers le presse-papier 
(Maj-Inser). 
:li.:hp5.Bouton du milieu:ehp5.
.br
Le bouton s�lectionn� agit comme un bouton 3 standard de souris. 
L'�tat de la touche 'maj' du clavier est pr�serv� et g�r� 
correctement. 
:li.:hp5.R�duire/Cacher toutes les fen�tres:ehp5.
.br
Toutes les fen�tres seront r�duites ou cach�es en fonction du 
comportement de la fen�tre. 
:li.:hp5.Restauration de toutes les fen�tres:ehp5.
.br
Toutes les fen�tres seront restaur�es � la taille qu'elles avaient 
avant la fonction de R�duction/Masquage/Agrandissement. 
:li.:hp5.Liste des fen�tres:ehp5.
.br
La liste des fen�tres sera affich�e. 
:li.:hp5.Fermeture de l'application:ehp5.
.br
L'application sera ferm�e. 
:li.:hp5.Double clic:ehp5.
.br
Un message double-clic sera envoy� � l'applicaton. 
:li.:hp5.Agrandissement de la fen�tre.:ehp5.
.br
La fen�tre sera agrandie. 
:li.:hp5.R�duire/Cacher la fen�tre:ehp5.
.br
La fen�tre sera r�duite ou cach�e, en fonction de son comportement. 
:li.:hp5.Restauration de la fen�tre:ehp5.
.br
La fen�tre sera restaur�e � la taille qu'elle avait avant la 
fonction de R�duction/Masquage/Agrandissement. 
:li.:hp5.Changer la direction de d�filement:ehp5.
.br
La direction de d�filement basculera de vertical � horizontal. 
:li.:hp5.Placer la fen�tre � l'arri�re-plan:ehp5.
.br
La fen�tre sous le pointeur de la souris sera plac�e sous toutes les 
autres fen�tres du bureau. 
:li.:hp5.Key combination:ehp5.
.br
The key code of the key combination shown in the entry field will be sent to the application.
:li.:hp5.Aucune action:ehp5.
.br
L'appui sur le bouton n'aura aucune action. 
:eul.

:h2 res=1501 id=button3.Bouton 3
:p.Cette bo�te de contr�les est utilis�e pour s�lectionner l'action 
� effectuer � l'appui sur le bouton 3. 

:h2 res=1502 id=button4.Bouton 4
:p.Cette bo�te de contr�les est utilis�e pour s�lectionner 
l'action � effectuer � l'appui sur le bouton 4.

:h2 res=1503 id=button5.Bouton 5
:p.Cette bo�te de contr�les est utilis�e pour s�lectionner 
l'action � effectuer � l'appui sur le bouton 5.

:h2 res=1504 id=button6.Bouton 6
:p.Cette bo�te de contr�les est utilis�e pour s�lectionner 
l'action � effectuer � l'appui sur le bouton 6.

:h2 res=1505 id=button7.Bouton 7
:p.Cette bo�te de contr�les est utilis�e pour s�lectionner 
l'action � effectuer � l'appui sur le bouton 7.

:h2 res=1506 id=button8.Bouton 8
:p.Cette bo�te de contr�les est utilis�e pour s�lectionner 
l'action � effectuer � l'appui sur le bouton 8.

:h2 res=1507 id=button9.Bouton 9
:p.Cette bo�te de contr�les est utilis�e pour s�lectionner 
l'action � effectuer � l'appui sur le bouton 9.

:h2 res=1508 id=button10.Bouton 10
:p.Cette bo�te de contr�les est utilis�e pour s�lectionner 
l'action � effectuer � l'appui sur le bouton 10.

:h2 res=1511 id=cbutton3.Ctrl+Bouton 3
:p.Cette bo�te de contr�les est utilis�e pour s�lectionner 
l'action � effectuer � l'appui sur le bouton 3 en combinaison avec 
la touche Ctrl du clavier. 

:h2 res=1512 id=cbutton4.Ctrl+Bouton 4
:p.Cette bo�te de contr�les est utilis�e pour s�lectionner l'action 
� effectuer � l'appui sur le bouton 4 en combinaison avec la 
touche Ctrl du clavier. 

:h2 res=1513 id=cbutton5.Ctrl+Bouton 5
:p.Cette bo�te de contr�les est utilis�e pour s�lectionner l'action 
� effectuer � l'appui sur le bouton 5 en combinaison avec la 
touche Ctrl du clavier. 

:h2 res=1514 id=cbutton6.Ctrl+Bouton 6
:p.Cette bo�te de contr�les est utilis�e pour s�lectionner l'action 
� effectuer � l'appui sur le bouton 6 en combinaison avec la 
touche Ctrl du clavier. 

:h2 res=1515 id=cbutton7.Ctrl+Bouton 7
:p.Cette bo�te de contr�les est utilis�e pour s�lectionner l'action 
� effectuer � l'appui sur le bouton 7 en combinaison avec la 
touche Ctrl du clavier. 

:h2 res=1516 id=cbutton8.Ctrl+Bouton 8
:p.Cette bo�te de contr�les est utilis�e pour s�lectionner l'action 
� effectuer � l'appui sur le bouton 8 en combinaison avec la 
touche Ctrl du clavier. 

:h2 res=1517 id=cbutton9.Ctrl+Bouton 9
:p.Cette bo�te de contr�les est utilis�e pour s�lectionner l'action 
� effectuer � l'appui sur le bouton 9 en combinaison avec la 
touche Ctrl du clavier. 

:h2 res=1518 id=cbutton10.Ctrl+Bouton 10
:p.Cette bo�te de contr�les est utilis�e pour s�lectionner l'action 
� effectuer � l'appui sur le bouton 10 en combinaison avec la 
touche Ctrl du clavier. 

:h2 res=1521 id=abutton3.Alt+Bouton 3
:p.Cette bo�te de contr�les est utilis�e pour s�lectionner l'action 
� effectuer � l'appui sur le bouton 3 en combinaison avec la 
touche Alt du clavier. 

:h2 res=1522 id=abutton4.Alt+Bouton 4
:p.Cette bo�te de contr�les est utilis�e pour s�lectionner l'action 
� effectuer � l'appui sur le bouton 4 en combinaison avec la 
touche Ctrl du clavier. 

:h2 res=1523 id=abutton5.Alt+Bouton 5
:p.Cette bo�te de contr�les est utilis�e pour s�lectionner l'action 
� effectuer � l'appui sur le bouton 5 en combinaison avec la 
touche Alt du clavier. 

:h2 res=1524 id=abutton6.Alt+Bouton 6
:p.Cette bo�te de contr�les est utilis�e pour s�lectionner l'action 
� effectuer � l'appui sur le bouton 6 en combinaison avec la 
touche Alt du clavier. 

:h2 res=1525 id=abutton7.Alt+Bouton 7
:p.Cette bo�te de contr�les est utilis�e pour s�lectionner l'action 
� effectuer � l'appui sur le bouton 7 en combinaison avec la 
touche Alt du clavier. 

:h2 res=1526 id=abutton8.Alt+Bouton 8
:p.Cette bo�te de contr�les est utilis�e pour s�lectionner l'action 
� effectuer � l'appui sur le bouton 8 en combinaison avec la 
touche Alt du clavier. 

:h2 res=1527 id=abutton9.Alt+Bouton 9
:p.Cette bo�te de contr�les est utilis�e pour s�lectionner l'action 
� effectuer � l'appui sur le bouton 9 en combinaison avec la 
touche Alt du clavier. 

:h2 res=1528 id=abutton10.Alt+Bouton 10
:p.Cette bo�te de contr�les est utilis�e pour s�lectionner l'action 
� effectuer � l'appui sur le bouton 10 en combinaison avec la 
touche Alt du clavier. 

:h2 res=1529 id=keycombset3.Set key combination 3
:p.This button is used to assign the :link reftype=hd refid=keycomb.key combination:elink. in the entry field to 
the mouse button, if the :link reftype=hd refid=button3.combo box:elink. has been set to :hp1.Key combination:ehp1..

:h2 res=1530 id=keycombset4.Set key combination 4
:p.This button is used to assign the :link reftype=hd refid=keycomb.key combination:elink. in the entry field to 
the mouse button, if the :link reftype=hd refid=button4.combo box:elink. has been set to :hp1.Key combination:ehp1..

:h2 res=1531 id=keycombset5.Set key combination 5
:p.This button is used to assign the :link reftype=hd refid=keycomb.key combination:elink. in the entry field to 
the mouse button, if the :link reftype=hd refid=button5.combo box:elink. has been set to :hp1.Key combination:ehp1..

:h2 res=1532 id=keycombset6.Set key combination 6
:p.This button is used to assign the :link reftype=hd refid=keycomb.key combination:elink. in the entry field to 
the mouse button, if the :link reftype=hd refid=button6.combo box:elink. has been set to :hp1.Key combination:ehp1..

:h2 res=1533 id=keycombset7.Set key combination 7
:p.This button is used to assign the :link reftype=hd refid=keycomb.key combination:elink. in the entry field to 
the mouse button, if the :link reftype=hd refid=button7.combo box:elink. has been set to :hp1.Key combination:ehp1..

:h2 res=1534 id=keycombset8.Set key combination 8
:p.This button is used to assign the :link reftype=hd refid=keycomb.key combination:elink. in the entry field to 
the mouse button, if the :link reftype=hd refid=button8.combo box:elink. has been set to :hp1.Key combination:ehp1..

:h2 res=1535 id=keycombset9.Set key combination 9
:p.This button is used to assign the :link reftype=hd refid=keycomb.key combination:elink. in the entry field to 
the mouse button, if the :link reftype=hd refid=button9.combo box:elink. has been set to :hp1.Key combination:ehp1..

:h2 res=1536 id=keycombset10.Set key combination 10
:p.This button is used to assign the :link reftype=hd refid=keycomb.key combination:elink. in the entry field to 
the mouse button, if the :link reftype=hd refid=button10.combo box:elink. has been set to :hp1.Key combination:ehp1..

:h2 res=1537 id=keycomb.Define key combination
:p.This entry field allows to define key combinations, that may be assigned to an arbitrary mouse button.
:p.After a key combination has been defined and assigned to a mouse button, this key combination will be sent to 
the applicaton, if the responding mouse button has been pressed.
:p.To define a key combination, the entry field must be clicked. Afterwards, the key combination has to be pressed (e.g. :hp2.Alt-F4:ehp2.).
The entry field then shows this key combination. By pressing one of the :hp2.Set:ehp2.-buttons, this key combination is
assiged to the corresponding mouse button.

:h1 res=1700 id=keys2.Boutons (page 2)
:i1 id=keys2.Boutons (page 2)
:p.Cette page est utilis�e pour d�finir le comportement des 
diff�rents contr�les sur les actions de la souris.
:p.Le param�trage s'effectue en cochant les options.
:p.Une explication plus d�taill�e de chaque contr�le vous sera 
pr�sent�e en cliquant sur l'un des �l�ments de la liste ci-dessous &colon. 
:ul compact.
:li.:link reftype=hd refid=dblclick_entry.Double-clic sur champ d'entr�e:elink.
:li.:link reftype=hd refid=click_combo.Clic sur bo�te de s�lection:elink.
:li.:link reftype=hd refid=smartcruise.SmartCruise:elink.
:li.:link reftype=hd refid=cancel.D�faire:elink.
:li.:link reftype=hd refid=standard.Par d�faut:elink.
:eul.

:h2 res=1701 id=dblclick_entry.Double-clic sur champ d'entr�e
:p.Si l'option est s�lectionn�e, un double-clic sur un champ 
d'entr�e r�sultera en une s�lection d'un mot complet. 

:h2 res=1702 id=click_combo.Clic sur bo�te de s�lection
:p.Si l'option est s�lectionn�e, un clic sur un champ d'entr�e 
faisant partie d'une bo�te de s�lection r�sulte en un d�roulement de 
la partie bo�te de s�lection. 

:h2 res=1703 id=smartcruise.SmartCruise
:p.Active la fonction SmartCruise des souris Logitech MX500, MX700 et MX1000. 
Si l'option est s�lectionn�e, les param�tres des boutons 7, 8, 9 et 10 sont
ignor�s. Avec cette fonction, les boutons 7 et 8 permettent le d�filement
vertical et les boutons 9 et 10 (si pr�sent) le d�filement horizontal. 

:h1 res=1100 id=devinfo.Informations (page 1)
:i1 id=devinfo.Informations (page 1)
:p.Cette page affiche le type et le num�ro de version du logiciel sur le PC 
relatif � ce produit. 
:p.Par ailleurs, vous aurez des informations � propos du type de la souris 
d�tect�e par votre syst�me. 
:note.pour un grand nombre de souris, il est impossible de d�tecter 
correctement le nombre de boutons. De plus, le Gestionnaire de Pr�sentation
(Presentation Manager ) supporte seulement 3 boutons au maximum. C'est la
raison pour laquelle il est possible que le nombre de boutons affich� soit 
incorrect dans le cas o� la souris en aurait plus de trois. 

:h1 res=1300 id=wldevinfo.Informations (page 2)
:i1 id=wldevinfo.Informations (page 2)
:p.Cette page affiche des informations sp�cifiques aux souris sans 
fil, supportant les requ�tes vers ces donn�es. 
:p.Le :hp5.num�ro de p�riph�rique:ehp5. n'est int�ressant que pour 
les souris USB et affiche le num�ro d'index du p�riph�rique. 
:p.Le :hp5.num�ro de canal:ehp5. donne le canal actuellement utilis� 
par la souris, si le support de canaux multiples est disponible. 
:p.L':hp5.�tat des batteries:ehp5. affiche l'�tat de charge en cours 
des batteries. 
:p.Une explication plus d�taill�e du contr�le vous sera pr�sent�e en
cliquant sur l'un des �l�ments de la liste ci-dessous &colon. 
:ul compact.
:li.:link reftype=hd refid=battery_warning.Avertissement sur l'�tat des batteries:elink.
:eul.

:h2 res=1304 id=battery_warning.Avertissement sur l'�tat des batteries
:p.Si l'option est activ�e, une bo�te de messsage appara�tra si la batterie
de votre souris est presque vide. 

:h1 res=2500 id=timing.R�glages
:i1 id=timing.R�glages
:p.Cette page sert au r�glage de la r�activit� ainsi que l'acc�l�ration
de la souris. 
:p.:hp5.L'acc�l�ration:ehp5.&colon. Pour chaque �v�nements de 
souris, le nombre d'unit�s de mouvement physique est compar� aux 
seuils de premier et second niveau. Si le nombre est sup�rieur au 
second niveau, le multiplicateur de second niveau sera utilis�; si 
le nombre est sup�rieur au premier niveau mais inf�rieur au second, 
le multiplicateur de premier niveau sera utilis�. Si le nombre est 
inf�rieur au premier niveau, aucun multiplicateur n'est utilis�. Ces 
calculs sont r�alis�s s�par�ments pour les axes X et Y. 
Les valeurs sont calcul�es comme suit &colon. 

:table cols='20 20' rules=both frame=box.
:row.
:c.Seuil de 1er niveau
:c.Valeur d�finie
:row.
:c.Seuil de 2nd niveau
:c.Valeur d�finie * 7
:row.
:c.Multiplicateur de 1er niveau
:c.Valeur d�finie
:row.
:c.Multiplicateur de 2nd niveau
:c.Valeur d�finie * 7
:row.
:c.Multiplicateur de 1er niveau
:c.Valeur d�finie
:row.
:c.Multiplicateur de 2nd niveau
:c.Valeur d�finie * 2
:etable.

:ul compact.
:li.:link reftype=hd refid=pollrate.R�activit� de la souris:elink.
:li.:link reftype=hd refid=mouaccel_value.Valeur de l'acc�l�ration:elink.
:li.:link reftype=hd refid=mouaccel_threshold.D�lai d'activation de l'acc�l�ration:elink.
:li.:link reftype=hd refid=cancel.D�faire:elink.
:li.:link reftype=hd refid=standard.Standard:elink.
:eul.

:h2 res=2501 id=pollrate.R�activit� de la souris
:p.Cette glissi�re permet de d�finir la r�activit� de la souris. 

:h2 res=2502 id=mouaccel_value.Valeur de l'acc�l�ration
:p.Cette glissi�re permet de d�finir la valeur de l'acc�l�ration. 

:h2 res=2503 id=mouaccel_threshold.D�lai d'activation de l'acc�l�ration
:p.Cette glissi�re permet de d�finir le seuil � partir duquel il y 
aura acc�l�ration. 

:euserdoc.

