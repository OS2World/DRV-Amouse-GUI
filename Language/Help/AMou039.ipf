.************************************************
.*
.*   Copyright 2002-2006 nb software
.*
.*   Help for AMouse
.************************************************

:userdoc.

:h1 res=10 id=aboutMain.AMouse - Configurazione avanzata mouse
:i1 id=aboutMain.AMouse - Configurazione avanzata mouse
:p.:artwork name='C:\work\c\amouse\Language\Help\amouse.bmp' runin align=left.
Questo programma permette di configurare la rotella nei mouse che ne
dispongono (ad es. l'Intelli-Mouse). E' possibile&colon.

:ul compact.
:li.controllare il funzionamento della rotella;
:li.impostare l'ampiezza della funzione di scorrimento della rotella;
:li.definire funzioni specifiche per i tasti aggiuntivi (terzo, quarto, quinto...) del mouse.
:eul.

:h1 res=1900 id=wheel1.Rotella, 1/2/3
:i1 id=wheel1.Rotella, 1/2/3
:p.Queste pagine permettono di variare la modalit… di funzionamento della rotella del mouse.
E' presente una pagina per ciascuna delle combinazioni rotella + tasto controllo supportate.
:p.Si scelga un argomento dalla lista seguente per una spiegazione pi— dettagliata
sulle singole voci&colon.

:ul compact.
:li.:link reftype=hd refid=no_func.Nessuna funzione:elink.
:li.:link reftype=hd refid=msgscroll.Messaggi di scorrimento:elink.
:li.:link reftype=hd refid=msgline.Messaggi tastiera:elink.
:li.:link reftype=hd refid=msgpage.Scorrimento di una pagina per unit… di scrolling:elink.
:li.:link reftype=hd refid=msgvol.Regolazione volume audio:elink.
:li.:link reftype=hd refid=keyboard.Agisci sulla finestra attiva:elink.
:li.:link reftype=hd refid=pointer.Agisci sulla finestra sotto il puntatore del mouse:elink.
:li.:link reftype=hd refid=scrollitem.Velocit… rotella:elink.
:li.:link reftype=hd refid=cancel.Regredire:elink.
:li.:link reftype=hd refid=standard.Valore assunto:elink.
:eul.
:note text='Nota&colon.'.
Queste pagine vengono visualizzate solo se il sistema rileva la presenza di un mouse con rotella.

:h2 res=1901 id=no_func.Modalit… funzionamento - Nessuna funzione
:p.Selezionando questa impostazione il sistema ignora l'eventuale rotazione
della rotella.

:h2 res=1902 id=msgscroll.Modalit… funzionamento - Messaggi di scorrimento
:p.Selezionando questa impostazione viene inviato alla finestra un messaggio di scorrimento (WM_VSCROLL/WM_HSCROLL).
Il risultato Š lo stesso che si otterrebbe agendo direttamente sulla barra di scorrimento della finestra.

:h2 res=1903 id=msgline.Modalit… funzionamento - Messaggi tastiera
:p.Selezionando questa impostazione viene inviato alla finestra un messaggio WM_CHAR. Il risultato Š lo stesso che si
otterrebbe premendo uno dei tasti cursore della tastiera (se la finestra accetta questo tipo di immissione).

:h2 res=1904 id=msgpage.Modalit… funzionamento - Scorrimento di una pagina per unit… di scrolling
:p.Selezionando questa impostazione viene inviato alla finestra un messaggio WM_CHAR. Il risultato Š lo stesso che si
otterrebbe premendo il tasto PagSu o PagGi— della tastiera (se la finestra accetta questo tipo di immissione).

:h2 res=1905 id=msgvol.Modalit… funzionamento - Regolazione volume audio
:p. Selezionando questa impostazione, ruotando la rotella del mouse si varia il volume del sistema multimedia.

:h2 res=1906 id=keyboard.Agisci sulla finestra attiva
:p.Se questa impostazione Š selezionata, lo scorrimento della rotella agisce sulla
finestra attiva.
:p.Con alcuni mouse, la finestra sotto al puntatore pu• venire attivata premendo
sulla rotella.
:note text='Nota&colon.'.
Š possibile avere barre di scorrimento anche nelle sottofinestre (per es. con Netscape Communicator).
In tal caso l'azione di scorrimento va sulla finestra che Š stata selezionata per ultima.

:h2 res=1907 id=pointer.Agisci sulla finestra sotto il puntatore del mouse
:p.Se questa impostazione Š selezionata, lo scorrimento della rotella agisce sulla finestra sotto
al puntatore del mouse.
:note text='Nota bene&colon.'.
Non ha importanza se la finestra Š attiva o no e neanche se Š parzialmente coperta
da altre finestre.

:h2 res=1908 id=scrollitem.Velocit… rotella
:p.Questo :hp2.valore:ehp2. imposta il numero di linee di scorrimento per ogni scatto
della rotella del mouse.

:h2 id=cancel.Regredire
:p.Tutte le impostazioni sono riportate ai valori precedenti l'ultima modifica.

:h2 id=standard.Valore assunto
:p.Per tutte le impostazioni vengono caricati i valori definiti all'installazione del programma.

:h1 res=2100 id=wheel2.Rotella, 4
:i1 id=wheel2.Rotella, 4
:p.Da questa pagina Š possibile definire le  impostazioni iniziali del driver
all'avvio del sistema.
:p.Per modificare le impostazioni agire sui comandi in questa
pagina.
:p.Per una spiegazione pi— dettagliata relativa alle singole voci scegliere
un argomento dalla lista seguente&colon.
:ul compact.
:li.:link reftype=hd refid=scroll_vert.Scorrimento verticale:elink.
:li.:link reftype=hd refid=scroll_horz.Scorrimento orizzontale:elink.
:li.:link reftype=hd refid=accel_delay.Ritardo accelerazione scorrimento:elink.
:li.:link reftype=hd refid=accel_value.Velocit… accelerazione scorrimento:elink.
:li.:link reftype=hd refid=trackball.Numero rotelle:elink.
:li.:link reftype=hd refid=cancel.Regredire:elink.
:li.:link reftype=hd refid=standard.Valore assunto:elink.
:eul.
:note text='Nota&colon.'.
Questa pagina viene visualizzata solo se il sistema rileva la presenza di un mouse con rotella.

:h2 res=2101 id=scroll_vert.Valore all'avvio - scorrimento verticale
:p.Selezionando questa impostazione, agendo sulla rotella di un mouse con rotella singola viene inviato un
messaggio di scorrimento verticale.

:h2 res=2102 id=scroll_horz.Valore all'avvio - scorrimento orizzontale
:p.Selezionando questa impostazione, agendo sulla rotella di un mouse con rotella singola viene inviato un
messaggio di scorrimento orizzontale.

:h2 res=2103 id=accel_delay.Ritardo accelerazione scorrimento
:p.Se la rotella viene fatta scorrere rapidamente per un tempo superiore al ritardo qui impostato, il numero di linee
per unit… di scorrimento aumenta progressivamente. Il ritardo Š impostabile in un intervallo compreso tra 100 e 2000 ms.

:h2 res=2104 id=accel_value.Velocit… accelerazione scorrimento (valore accelerazione)
:p.Questo comando controlla di quanto aumenta il numero delle unit… di scorrimento quando la rotella viene ruotata rapidamente.

:h2 res=2105 id=trackball.Numero rotelle
:p.Alcuni tipi di mouse non comunicano al driver quante rotelle sono presenti, o se vi Š una trackball.
Tramite questo bottone si possono impostare comunque i valori corretti.

:h1 res=2300 id=wheel3.Rotella, 5
:i1 id=wheel3.Rotella, 5
:p.Questa pagina permette, se lo si desidera, di definire eccezioni al normale comportamento della rotella per certe applicazioni.
Quando si agisce sulla rotella, il driver del mouse esamina l'elenco in questa pagina alla ricerca di una descrizione finestra/controllo adatta.
L'elenco :hp2.Descrizione:ehp2. viene letto dall'alto verso il basso finch‚ non viene individuata la voce corrispondente all'applicazione in quel momento sotto il puntatore del mouse.
Se nessuna delle voci nell'elenco soddisfa la ricerca, il driver passa ad esaminare la lista standard di :hp2.AMouse:ehp2.
(definita nel file :font facename=Courier size=14x14.AMouRes.rc:font facename=default.).
I nomi delle voci nella lista sono definiti dall'utente ed hanno valore puramente descrittivo. Si possono scegliere a piacimento e si pu• anche usare pi— volte uno stesso nome.
:p.Per modificare le impostazioni, agire sui rispettivi tasti nella pagina.
:p.Per spiegazioni dettagliate sui vari comandi, fare riferimento alle voci nell'elenco qui sotto&colon.
:ul compact.
:li.:link reftype=hd refid=wheel_up.&uarrow.:elink.
:li.:link reftype=hd refid=wheel_down.&darrow.:elink.
:li.:link reftype=hd refid=wheel_delete.Cancella:elink.
:li.:link reftype=hd refid=wheel_insert.Aggiungi:elink.
:li.:link reftype=hd refid=cancel.Regredire:elink.
:eul.
:note text='Nota&colon.'.
Questa pagina viene visualizzata solo se il sistema rileva la presenza di un mouse con rotella.

:p.:hp7.Descrizione dei campi:ehp7.
:p.Nel box sotto l'elenco sono riportati i valori impostati per una data applicazione. Nella colonna di sinistra vi Š il
nome della finestra/controllo che reagisce alla rotazione della rotella. I vari campi sono&colon.
:ul compact.
:li.:hp2.Applicazione:ehp2.
.br
Nome dell'applicazione (per es. :font facename=Courier size=14x14.PROGRAMMA.EXE:font facename=default.).
Se il campo Š vuoto, il risultato del confronto Š sempre TRUE. Per le classi WPS questo campo deve essere vuoto.
:li.:hp2.Classe:ehp2.
.br
Classe finestra della finestra/controllo. Va inserito o il nome della classe (attenzione a maiuscole e minuscole) o la sua
ID preceduta da &osq.&numsign.&csq.. Se il campo Š vuoto, il risultato del confronto Š sempre TRUE.
:li.:hp2.Classe genitore:ehp2.
.br
Classe della finestra "genitore" della finestra/controllo. Va inserito o il nome della classe (attenzione a maiuscole
e minuscole) o la sua ID preceduta da &osq.&numsign.&csq.. Se il campo Š vuoto, il risultato del confronto Š sempre TRUE.
:li.:hp2.Opzione:ehp2.
.br
Va inserita la eventuale opzione per una &osq.RelazioneV&csq. o &osq.RelazioneH&csq. specifica (per ulteriori spiegazioni
si veda la voce relativa). Negli altri casi il campo deve rimanere vuoto.
:eul.
:p.Nella colonna di destra si vede qual'Š l'azione determinata dalla rotazione della rotella. I vari campi sono&colon.
:ul compact.
:li.:hp2.Mode:ehp2.
.br
Definisce il tipo di messaggio che, inviato alla finestra/controllo, attiva l'eccezione.
L'impostazione :hp2.Scroll:ehp2. risponde nel caso di un comando
:link reftype=hd refid=msgscroll.Messaggi di scorrimento:elink. (come impostato dalle pagine
:link reftype=hd refid=wheel1.Rotella:elink. precedenti).
:hp2.Cursor:ehp2. reagisce ad un comando
:link reftype=hd refid=msgline.Messaggi tastiera:elink.,
:hp2.Page:ehp2. ad un comando
:link reftype=hd refid=msgpage.Scorrimento di una pagina per unit… di scrolling:elink..
:hp2.Scroll o Cursor:ehp2. reagiscono sia se il comando intercettato Š
:link reftype=hd refid=msgscroll.Messaggi scorrimento:elink. sia se Š
:link reftype=hd refid=msgline.Messaggi tastiera:elink..
:hp2.All:ehp2. reagisce per tutte le impostazioni.
:li.:hp2.RelazioneV e RelazioneH:ehp2.
.br
Definisce se il messaggio deve essere inviato direttamente alla finestra/controllo o se dev'essere fatta una
ricerca ulteriore nella gerarchia della finestra. I campi sono&colon.
:ul compact.
:li.:hp2.None:ehp2.&colon. il messaggio viene inviato direttamente al controllo individuato.
:li.:hp2.Parent:ehp2.&colon. viene ricercato un "genitore" appropriato nell'elenco descrizioni.
:li.:hp2.Owner:ehp2.&colon. viene ricercato un "proprietario" appropriato nell'elenco descrizioni.
:li.:hp2.Avanti:ehp2.&colon. la ricerca continua sull'asse z per altri controlli che si dovessero trovare sotto
il puntatore del mouse.
:li.:hp2.CB Next:ehp2.&colon. usato solo per i Combobox. Sostanzialmente come il comando :hp2.Next:ehp2.,
ma controlla l'area non visibile sotto il campo immissione se il box elenco non Š visualizzato.
:li.:hp2.Sibling[Option]:ehp2.&colon. nell'elenco descrizioni viene ricercata una finestra "sorella" con nome classe
pari a quello definito nel campo :hp2.Opzione:ehp2..
:eul.
:li.:hp2.OpzioneV / OpzioneH:ehp2.
.br
Specifica un'opzione, dipendente dal tipo di messaggio impostato. Si veda sotto.
:li.:hp2.Su/giu e Sinistra/destra:ehp2.
.br
Definisce il tipo di messaggio da inviare alla finestra/controllo. Sono disponibili i seguenti tipi di messaggio&colon.
:ul compact.
:li.:hp2.WM_NULL:ehp2.&colon. Non viene inviato nessun messaggio. Generalmente da usare se in
:hp2.vRelation:ehp2./:hp2.hRelation:ehp2. si Š specificato :hp2.None:ehp2..
:li.:hp2.WM_CONTROL:ehp2.&colon. Viene inviato un codice tastiera direttamente al driver della tastiera.
Sono possibili le seguenti opzioni&colon.
:ul compact.
:li.:hp2.page:ehp2.&colon. invia i codici tastiera per i tasti PagSu-/PagGi—.
:li.:hp2.cursor up/down:ehp2.&colon. invia i codici tastiera per i tasti cursore Su/Gi—.
:li.:hp2.cursor left/right:ehp2.&colon. invia i codici tastiera per i tasti cursore Destra/Sinistra.
:li.:hp2.mult cursor up/down:ehp2.&colon. invia i codici tastiera per i tasti cursore Su/Gi—.
Il numero di messaggi inviati dipende dall'impostazione :link reftype=hd refid=scrollitem.Velocit… rotella:elink..
:li.:hp2.mult cursor left/right:ehp2.&colon. invia i codici tastiera per i tasti cursore Destra/Sinistra.
Il numero di messaggi inviati dipende dall'impostazione :link reftype=hd refid=scrollitem.Velocit… rotella:elink..
:eul.
:li.:hp2.WM_VSCROLL:ehp2.&colon. invia un messaggio di scorrimento verticale alla barra di scorrimento verticale.
:li.:hp2.WM_HSCROLL:ehp2.&colon. invia un messaggio di scorrimento orizzontale alla barra di scorrimento orizzontale.
:li.:hp2.N x WM_VSCROLL:ehp2.&colon. come :hp2.WM_VSCROLL:ehp2., ma il numero di messaggi inviati dipende
dall'impostazione :link reftype=hd refid=scrollitem.Velocit… rotella:elink..
:li.:hp2.N x WM_HSCROLL:ehp2.&colon. come :hp2.WM_HSCROLL:ehp2., ma il numero di messaggi inviati dipende
dall'impostazione :link reftype=hd refid=scrollitem.Velocit… rotella:elink..
:li.:hp2.WM_CHAR:ehp2.&colon. invia un messaggio carattere. Sono disponibili le stesse opzioni previste per
:hp2.WM_CONTROL:ehp2..
:eul.
:eul.

:p.:hp7.Esempi:ehp7.
:p.A causa di un baco nelle versioni pi— vecchie di Mozilla (versione 1.3 e precedenti) lo scorrimento orizzontale
attraverso i normali messaggi WM_SCROLL non funziona. Le due immissioni seguenti permettono di aggirare efficacemente il problema.
:p.:artwork name='C:\work\c\amouse\Language\Help\Mozilla_Line_039.bmp' align=left.
:p.Questa immissione funziona se nella :link reftype=hd refid=wheel1.prima pagina Rotella:elink. si Š impostato
:hp2.Messaggi scorrimento:ehp2. o :hp2.Messaggi tastiera:ehp2. come modo di funzionamento.
Ruotando la rotella, alla finestra "genitore" saranno inviati messaggi con i codici tastiera cursore verticale e orizzontale
(&odq.mult cursor&cdq.). La finestra Mozilla Š identificata quando sia :hp2.Classe:ehp2. che :hp2.Classe genitore:ehp2. appartengono al tipo :hp2.MozillaWindowClass:ehp2..
:p.:artwork name='C:\work\c\amouse\Language\Help\Mozilla_Page_039.bmp' align=left.
:p.Per poter scorrere di una pagina alla volta (:hp2.Mode = Page:ehp2.) viene invece inviato un carattere
PagSu/PagGi— (solo per lo scorrimento verticale).
:p.:artwork name='C:\work\c\amouse\Language\Help\Command_Line_039.bmp' align=left.
:p.Ruotando la rotella su una finestra comandi, il normale comportamento prevede che l'azione sia diretta sulle
barre di scorrimento eventualmente presenti. Le impostazioni mostrate qui permettono invece di usare la rotella
per scorrere la storia dei comandi.

:h2 res=2313 id=wheel_up.&uarrow. (Muovi in su)
:p.Sposta in su di una posizione la voce selezionata nell'elenco descrizioni.

:h2 res=2314 id=wheel_down.&darrow. (Muovi in gi—)
:p.Sposta in gi— di una posizione la voce selezionata nell'elenco descrizioni.

:h2 res=2316 id=wheel_delete.Cancella
:p.Cancella la voce selezionata nell'elenco alla sinistra di questo tasto.

:h2 res=2315 id=wheel_insert.Aggiungi
:p.Inserisce una nuova voce nell'elenco alla sinistra di questo tasto.

:h1 res=2700 id=insertappl.Nuova applicazione
:i1 id=insertappl.Nuova applicazione
:p.Questa finestra permette di inserire una nuova definizione per il comportamento della rotella rispetto ad una
data applicazione. I controlli in questa finestra corrispondono a quelli descritti nella pagina
:link reftype=hd refid=wheel3.Rotella, 5:elink.. Il campo :hp2.Descrizione:ehp2. permette di inserire un
testo, a scelta dell'utente, per identificare le varie voci nell'elenco di
:link reftype=hd refid=wheel3.pagina 5:elink..

:h1 res=1500 id=keys1.Tasti, 1
:i1 id=keys.Tasti, 1
:p.Questa pagina permette di definire funzioni specifiche per i tasti del mouse.
:p.Agire sulle voci relative per modificare le singole impostazioni.
:p.Per una spiegazione pi— dettagliata relativa alle singole voci, selezionare
un argomento dalla lista seguente&colon.
:ul compact.
:li.:link reftype=hd refid=button3.Tasto 3:elink.
:li.:link reftype=hd refid=button4.Tasto 4:elink.
:li.:link reftype=hd refid=button5.Tasto 5:elink.
:li.:link reftype=hd refid=button6.Tasto 6:elink.
:li.:link reftype=hd refid=button7.Tasto 7:elink.
:li.:link reftype=hd refid=button8.Tasto 8:elink.
:li.:link reftype=hd refid=button9.Tasto 9:elink.
:li.:link reftype=hd refid=button10.Tasto 10:elink.
:li.:link reftype=hd refid=cbutton3.Ctrl+tasto 3:elink.
:li.:link reftype=hd refid=cbutton4.Ctrl+tasto 4:elink.
:li.:link reftype=hd refid=cbutton5.Ctrl+tasto 5:elink.
:li.:link reftype=hd refid=cbutton6.Ctrl+tasto 6:elink.
:li.:link reftype=hd refid=cbutton7.Ctrl+tasto 7:elink.
:li.:link reftype=hd refid=cbutton8.Ctrl+tasto 8:elink.
:li.:link reftype=hd refid=cbutton9.Ctrl+tasto 9:elink.
:li.:link reftype=hd refid=cbutton10.Ctrl+tasto 10:elink.
:li.:link reftype=hd refid=abutton3.Alt+tasto 3:elink.
:li.:link reftype=hd refid=abutton4.Alt+tasto 4:elink.
:li.:link reftype=hd refid=abutton5.Alt+tasto 5:elink.
:li.:link reftype=hd refid=abutton6.Alt+tasto 6:elink.
:li.:link reftype=hd refid=abutton7.Alt+tasto 7:elink.
:li.:link reftype=hd refid=abutton8.Alt+tasto 8:elink.
:li.:link reftype=hd refid=abutton9.Alt+tasto 9:elink.
:li.:link reftype=hd refid=abutton10.Alt+tasto 10:elink.
:li.:link reftype=hd refid=keycombset3.Imposta combinazione tasti 3:elink.
:li.:link reftype=hd refid=keycombset4.Imposta combinazione tasti 4:elink.
:li.:link reftype=hd refid=keycombset5.Imposta combinazione tasti 5:elink.
:li.:link reftype=hd refid=keycombset6.Imposta combinazione tasti 6:elink.
:li.:link reftype=hd refid=keycombset7.Imposta combinazione tasti 7:elink.
:li.:link reftype=hd refid=keycombset8.Imposta combinazione tasti 8:elink.
:li.:link reftype=hd refid=keycombset9.Imposta combinazione tasti 9:elink.
:li.:link reftype=hd refid=keycombset10.Imposta combinazione tasti 10:elink.
:li.:link reftype=hd refid=keycomb.Combinazione tasti:elink.
:li.:link reftype=hd refid=cancel.Regredire:elink.
:li.:link reftype=hd refid=standard.Valore assunto:elink.
:eul.
:note text='Nota&colon.'.
Questa pagina viene visualizzata solo se il sistema rileva la presenza di un mouse con rotella.

:p.:hp2.Funzioni tasti:ehp2.
:p.Sono disponibili le seguenti funzioni&colon.

:ul.
:li.:hp5.Taglia:ehp5.
.br
Esegue la funzione Appunti "Taglia" (Maiusc-Canc).
:li.:hp5.Copia:ehp5.
.br
Esegue la funzione Appunti "Copia" (Ctrl-Ins).
:li.:hp5.Incolla:ehp5.
.br
Esegue la funzione Appunti "Incolla" (Maiusc-Ins).
:li.:hp5.Tasto centrale mouse:ehp5.
.br
Il tasto selezionato si comporta come un normale tasto 3 del mouse. Lo stato dei tasti
controllo della tastiera Š preservato e gestito di conseguenza.
:li.:hp5.Riduci/nascondi tutte le finestre:ehp5.
.br
Tutte le finestre vengono ridotte al minimo o nascoste, a seconda dell'impostazione della finestra.
:li.:hp5.Ripristina tutte le finestre:ehp5.
.br
Tutte le finestre sono ripristinate alla dimensione precedente i comandi Riduci/Nascondi/Ingrandisci.
:li.:hp5.Elenco finestre:ehp5.
.br
Viene visualizzato l'elenco finestre.
:li.:hp5.Chiudi applicazione:ehp5.
.br
L'applicazione viene chiusa.
:li.:hp5.Doppio clic:ehp5.
.br
Viene inviato all'applicazione un messaggio di doppio clic.
:li.:hp5.Ingrandisci al massimo finestra:ehp5.
.br
La finestra Š ingrandita al massimo.
:li.:hp5.Riduci/nascondi finestra:ehp5.
.br
La finestra viene ridotta al minimo o nascosta, a seconda dell'impostazione prevista.
:li.:hp5.Ripristina finestra:ehp5.
.br
La finestra Š ripristinata alla dimensione precedente i comandi Riduci/Nascondi/Ingrandisci.
:li.:hp5.Cambia direzione scorrimento:ehp5.
.br
Passa dallo scorrimento verticale a quello orizzontale.
:li.:hp5.Spingi finestra sotto le altre:ehp5.
.br
La finestra sotto al puntatore del mouse viene spinta dietro alle altre finestre aperte
sulla Scrivania.
:li.:hp5.Combinazione tasti:ehp5.
.br
I codici della combinazione di tasti mostrata nel campo immissione verranno inviati all'applicazione.
:li.:hp5.Nessuna funzione:ehp5.
.br
La pressione sul tasto non attiva nessuna azione.
:eul.

:h2 res=1501 id=button3.Tasto 3
:p.Selezionare dal menu a tendina la funzione che si desidera assegnare
al tasto 3 del mouse.

:h2 res=1502 id=button4.Tasto 4
:p.Selezionare dal menu a tendina la funzione che si desidera assegnare
al tasto 4 del mouse.

:h2 res=1503 id=button5.Tasto 5
:p.Selezionare dal menu a tendina la funzione che si desidera assegnare
al tasto 5 del mouse.

:h2 res=1504 id=button6.Tasto 6
:p.Selezionare dal menu a tendina la funzione che si desidera assegnare
al tasto 6 del mouse.

:h2 res=1505 id=button7.Tasto 7
:p.Selezionare dal menu a tendina la funzione che si desidera assegnare
al tasto 7 del mouse.

:h2 res=1506 id=button8.Tasto 8
:p.Selezionare dal menu a tendina la funzione che si desidera assegnare
al tasto 8 del mouse.

:h2 res=1507 id=button9.Tasto 9
:p.Selezionare dal menu a tendina la funzione che si desidera assegnare
al tasto 9 del mouse.

:h2 res=1508 id=button10.Tasto 10
:p.Selezionare dal menu a tendina la funzione che si desidera assegnare
al tasto 10 del mouse.

:h2 res=1511 id=cbutton3.Ctrl+tasto 3
:p.Selezionare dal menu a tendina la funzione che si desidera assegnare
al tasto 3 del mouse in combinazione con il tasto Ctrl della tastiera.

:h2 res=1512 id=cbutton4.Ctrl+tasto 4
:p.Selezionare dal menu a tendina la funzione che si desidera assegnare
al tasto 4 del mouse in combinazione con il tasto Ctrl della tastiera.

:h2 res=1513 id=cbutton5.Ctrl+tasto 5
:p.Selezionare dal menu a tendina la funzione che si desidera assegnare
al tasto 5 del mouse in combinazione con il tasto Ctrl della tastiera.

:h2 res=1514 id=cbutton6.Ctrl+tasto 6
:p.Selezionare dal menu a tendina la funzione che si desidera assegnare
al tasto 6 del mouse in combinazione con il tasto Ctrl della tastiera.

:h2 res=1515 id=cbutton7.Ctrl+tasto 7
:p.Selezionare dal menu a tendina la funzione che si desidera assegnare
al tasto 7 del mouse in combinazione con il tasto Ctrl della tastiera.

:h2 res=1516 id=cbutton8.Ctrl+tasto 8
:p.Selezionare dal menu a tendina la funzione che si desidera assegnare
al tasto 8 del mouse in combinazione con il tasto Ctrl della tastiera.

:h2 res=1517 id=cbutton9.Ctrl+tasto 9
:p.Selezionare dal menu a tendina la funzione che si desidera assegnare
al tasto 9 del mouse in combinazione con il tasto Ctrl della tastiera.

:h2 res=1518 id=cbutton10.Ctrl+tasto 10
:p.Selezionare dal menu a tendina la funzione che si desidera assegnare
al tasto 10 del mouse in combinazione con il tasto Ctrl della tastiera.

:h2 res=1521 id=abutton3.Alt+tasto 3
:p.Selezionare dal menu a tendina la funzione che si desidera assegnare
al tasto 3 del mouse in combinazione con il tasto Alt della tastiera.

:h2 res=1522 id=abutton4.Alt+tasto 4
:p.Selezionare dal menu a tendina la funzione che si desidera assegnare
al tasto 4 del mouse in combinazione con il tasto Alt della tastiera.

:h2 res=1523 id=abutton5.Alt+tasto 5
:p.Selezionare dal menu a tendina la funzione che si desidera assegnare
al tasto 5 del mouse in combinazione con il tasto Alt della tastiera.

:h2 res=1524 id=abutton6.Alt+tasto 6
:p.Selezionare dal menu a tendina la funzione che si desidera assegnare
al tasto 6 del mouse in combinazione con il tasto Alt della tastiera.

:h2 res=1525 id=abutton7.Alt+tasto 7
:p.Selezionare dal menu a tendina la funzione che si desidera assegnare
al tasto 7 del mouse in combinazione con il tasto Alt della tastiera.

:h2 res=1526 id=abutton8.Alt+tasto 8
:p.Selezionare dal menu a tendina la funzione che si desidera assegnare
al tasto 8 del mouse in combinazione con il tasto Alt della tastiera.

:h2 res=1527 id=abutton9.Alt+tasto 9
:p.Selezionare dal menu a tendina la funzione che si desidera assegnare
al tasto 9 del mouse in combinazione con il tasto Alt della tastiera.

:h2 res=1528 id=abutton10.Alt+tasto 10
:p.Selezionare dal menu a tendina la funzione che si desidera assegnare
al tasto 10 del mouse in combinazione con il tasto Alt della tastiera.

:h2 res=1529 id=keycombset3.Imposta combinazione tasti 3
:p.Questo bottone assegna al tasto del mouse la :link reftype=hd refid=keycomb.combinazione tasti:elink. presente
nel campo immissione, se il :link reftype=hd refid=button3.selettore:elink. Š stato impostato su :hp1.Combinazione tasti:ehp1..

:h2 res=1530 id=keycombset4.Imposta combinazione tasti 4
:p.Questo bottone assegna al tasto del mouse la :link reftype=hd refid=keycomb.combinazione tasti:elink. presente
nel campo immissione, se il :link reftype=hd refid=button4.selettore:elink. Š stato impostato su :hp1.Combinazione tasti:ehp1..

:h2 res=1531 id=keycombset5.Imposta combinazione tasti 5
:p.Questo bottone assegna al tasto del mouse la :link reftype=hd refid=keycomb.combinazione tasti:elink. presente
nel campo immissione, se il :link reftype=hd refid=button5.selettore:elink. Š stato impostato su :hp1.Combinazione tasti:ehp1..

:h2 res=1532 id=keycombset6.Imposta combinazione tasti 6
:p.Questo bottone assegna al tasto del mouse la :link reftype=hd refid=keycomb.combinazione tasti:elink. presente
nel campo immissione, se il :link reftype=hd refid=button6.selettore:elink. Š stato impostato su :hp1.Combinazione tasti:ehp1..

:h2 res=1533 id=keycombset7.Imposta combinazione tasti 7
:p.Questo bottone assegna al tasto del mouse la :link reftype=hd refid=keycomb.combinazione tasti:elink. presente
nel campo immissione, se il :link reftype=hd refid=button7.selettore:elink. Š stato impostato su :hp1.Combinazione tasti:ehp1..

:h2 res=1534 id=keycombset8.Imposta combinazione tasti 8
:p.Questo bottone assegna al tasto del mouse la :link reftype=hd refid=keycomb.combinazione tasti:elink. presente
nel campo immissione, se il :link reftype=hd refid=button8.selettore:elink. Š stato impostato su :hp1.Combinazione tasti:ehp1..

:h2 res=1535 id=keycombset9.Imposta combinazione tasti 9
:p.Questo bottone assegna al tasto del mouse la :link reftype=hd refid=keycomb.combinazione tasti:elink. presente
nel campo immissione, se il :link reftype=hd refid=button9.selettore:elink. Š stato impostato su :hp1.Combinazione tasti:ehp1..

:h2 res=1536 id=keycombset10.Imposta combinazione tasti 10
:p.Questo bottone assegna al tasto del mouse la :link reftype=hd refid=keycomb.combinazione tasti:elink. presente
nel campo immissione, se il :link reftype=hd refid=button10.selettore:elink. Š stato impostato su :hp1.Combinazione tasti:ehp1..

:h2 res=1537 id=keycomb.Definizione delle combinazioni di tasti
:p.Il campo permette di definire combinazioni di tasti della tastiera da assegnare ai tasti del mouse.
:p.Una volta definita ed assegnata, la combinazione di tasti prescelta viene inviata
all'applicazione ogni volta che si preme il corrispondente bottone del mouse.
:p.Per definire una combinazione di tasti, cliccare nel campo immissione; quindi, premere la combinazione di tasti desiderata
(per es.&colon. :hp2.Alt+F4:ehp2.), che viene visualizzata nel campo immissione. Premendo uno dei
bottoni :hp2.Imposta:ehp2., si assegna la combinazione ad un dato tasto del mouse.

:h1 res=1700 id=keys2.Tasti, 2
:i1 id=keys2.Tasti, 2
:p.Questa pagina permette di definire il comportamento dei diversi controlli sulle azioni del mouse.
:p.Le impostazioni si modificano agendo sui relativi comandi presenti nella pagina.
:p.Per una spiegazione pi— dettagliata, scegliere un argomento
dalla lista seguente&colon.
:ul compact.
:li.:link reftype=hd refid=dblclick_entry.Doppio clic su un campo immissione:elink.
:li.:link reftype=hd refid=click_combo.Clic su un Combo Box:elink.
:li.:link reftype=hd refid=smartcruise.SmartCruise:elink.
:li.:link reftype=hd refid=cancel.Regredire:elink.
:li.:link reftype=hd refid=standard.Valore assunto:elink.
:eul.

:h2 res=1701 id=dblclick_entry.Doppio clic su un campo immissione
:p.Selezionando questo bottone, cliccando due volte in un campo immissione si seleziona la parola su cui si Š cliccato.

:h2 res=1702 id=click_combo.Clic su un Combo Box
:p.Selezionando questo bottone, cliccando all'interno del campo immissione di un Combo Box si apre la lista
relativa.

:h2 res=1703 id=smartcruise.SmartCruise
:p.Attivando questa opzione si abilita la funzionalit… SmartCruise, presente sui mouse Logitech
modello MX500, MX700 e MX1000. Se l'opzione Š attiva, le impostazioni relative ai tasti 7, 8, 9
e 10 vengono ignorate e si possono usare i tasti 7 e 8 per scorrere in verticale e quelli 9 e
10 (se presenti) per scorrere in verticale.

:h1 res=1100 id=devinfo.Informazioni dispositivo
:i1 id=devinfo.Informazioni dispositivo
:p.Questa pagina mostra tipo e versione del software installato sul PC relativo a
questo prodotto.
:p.Sono inoltre fornite informazioni relative al tipo di mouse rilevato nel sistema.
:note text='Nota bene&colon.'.
In molti casi Š impossibile determinare correttamente il numero di tasti sul mouse e comunque
il Presentation Manager supporta tre tasti al massimo. Per questo motivo pu• capitare che,
se sono presenti pi— di tre tasti, non ne venga rilevato correttamente
il numero.

:h1 res=1300 id=wldevinfo.Informazioni dispositivo, 2
:i1 id=wldevinfo.Informazioni dispositivo, 2
:p.Se il dispositivo rilevato ne supporta l'acquisizione, questa pagina mostra informazioni specifiche per i mouse senza filo.
:p.:hp5.Numero dispositivo:ehp5. riguarda solo i mouse USB ed indica il numero indice del dispositivo.
:p.:hp5.Numero canale:ehp5. mostra il canale utilizzato, nel caso di mouse che supportino canali multipli.
:p.:hp5.Stato batteria:ehp5. mostra lo stato di carica corrente della batteria del dispositivo.
:p.Per una spiegazione pi— dettagliata, scegliere un argomento
dalla lista seguente&colon.
:ul compact.
:li.:link reftype=hd refid=battery_warning.Avviso batteria:elink.
:eul.

:h2 res=1304 id=battery_warning.Avviso batteria
:p.Se questa impostazione Š selezionata, quando la batteria del mouse Š prossima ad esaurirsi viene visualizzata una finestra di avviso.

:h1 res=2500 id=timing.Temporizzazione
:i1 id=timing.Temporizzazione
:p.Da questa finestra si possono controllare le temporizzazioni relative alla frequenza di controllo
del mouse ed ai valori di accelerazione.

:p.:hp5.Accelerazione:ehp5.&colon. Per ogni movimento del mouse, l'ampiezza effettiva dello
spostamento viene confrontata con i valori soglia di primo e secondo livello. Se il mouse viene
spostato per un numero di unit… superiore alla soglia di secondo livello, il sistema applica il moltiplicatore
previsto per il secondo livello. Se il numero di unit… Š superiore al primo livello ed inferiore al secondo
viene applicato il moltiplicatore previsto per il primo livello. Se il mouse viene spostato per un numero
di unit… inferiore alla soglia di primo livello non viene utilizzato alcun moltiplicatore. I calcoli
sono effettuati separatamente per l'asse X e per quello Y. I valori sono calcolati come segue&colon.

:table cols='30 30' rules=both frame=box.
:row.
:c.soglia primo livello
:c.valore cursore
:row.
:c.soglia secondo livello
:c.valore cursore per 7
:row.
:c.moltiplicatore primo livello
:c.valore cursore
:row.
:c.moltiplicatore secondo livello
:c.valore cursore per 2
:etable.

:ul compact.
:li.:link reftype=hd refid=pollrate.Frequenza di controllo del mouse:elink.
:li.:link reftype=hd refid=mouaccel_value.Valore accelerazione:elink.
:li.:link reftype=hd refid=mouaccel_threshold.Soglia accelerazione:elink.
:li.:link reftype=hd refid=cancel.Regredire:elink.
:li.:link reftype=hd refid=standard.Valore assunto:elink.
:eul.

:h2 res=2501 id=pollrate.Frequenza di controllo del mouse
:p.Questo cursore controlla la frequenza interna di "polling" del mouse.

:h2 res=2502 id=mouaccel_value.Valore accelerazione
:p.Questo cursore regola il valore di accelerazione.

:h2 res=2503 id=mouaccel_threshold.Soglia accelerazione
:p.Questo cursore regola la soglia di accelerazione.

:euserdoc.
