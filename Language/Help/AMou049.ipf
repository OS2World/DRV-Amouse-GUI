.************************************************
.*
.*   Copyright 2002-2006 nb software
.*
.*   Help for AMouse
.************************************************

:userdoc.

:h1 res=10 id=aboutMain.AMouse - Advanced Mouse Konfiguration
:i1 id=aboutMain.AMouse - Advanced Mouse Konfiguration
:p.:artwork name='C:\work\c\amouse\Language\Help\amouse.bmp' runin align=left.
Dieses Programm gestattet die Einstellung der Funktion des R„dchens einer
"R„dchen-Maus" (z. B. Intelli-Mouse). Es kann&colon.

:ul compact.
:li.die Arbeitsweise des R„dchens festlegen
:li.die Scroll-Increments pro Raststufe ausw„hlen
:li.die Funktionen der Buttons 3...5 der Maus festlegen
:eul.

:h1 res=1900 id=wheel1.R„dchen 1/2/3
:i1 id=wheel1.R„dchen 1
:p.šber die Seite :hp2.R„dchen 1:ehp2. des Notizbuchs
:hp2.AMouse - Merkmale:ehp2. k”nnen die
Aktionen ausgew„hlt werden, die durch das Vor- oder Zurckdrehen
des Mausr„dchens initiiert werden. Fr jede untersttzte Kombination
von R„dchen + Umschalttaste existiert eine solche Seite.
:p.Die Einstellungen k”nnen durch entprechende
Auswahl auf dieser Seite durchgefhrt werden.
:p.Eine genaue Erkl„rung fr jedes Feld wird angezeigt,
wenn der entsprechende Begriff aus der
untenstehenden Liste ausgew„hlt wird&colon.

:ul compact.
:li.:link reftype=hd refid=no_func.Ohne Funktion:elink.
:li.:link reftype=hd refid=msgscroll.Scroll Nachrichten:elink.
:li.:link reftype=hd refid=msgline.Tastatur Nachrichten:elink.
:li.:link reftype=hd refid=msgpage.Scrollen einer Seite pro Scrolleinheit:elink.
:li.:link reftype=hd refid=msgvol.Einstellen der Lautst„rke:elink.
:li.:link reftype=hd refid=keyboard.Wirkt auf aktives Fenster:elink.
:li.:link reftype=hd refid=pointer.Wirkt auf Fenster unter Mauszeiger:elink.
:li.:link reftype=hd refid=scrollitem.Rad-Geschwindigkeit:elink.
:li.:link reftype=hd refid=cancel.Widerrufen:elink.
:li.:link reftype=hd refid=standard.Standard:elink.
:eul.
:note text='Hinweis&colon.'.
Nur wenn ein R„dchen erkannt wurde, enth„lt das
Notizbuch auch die entsprechende Seite.

:h2 res=1901 id=no_func.Arbeitsweise - Ohne Funktion
:p.Wird dieser Radioknopf gew„hlt, so wird die Drehung
am R„dchen vom System ignoriert.

:h2 res=1902 id=msgscroll.Arbeitsweise - Scroll Nachrichten
:p.Wird dieser Knopf gew„hlt, wird an das jeweilige Fenster eine
Scroll-Nachricht (WM_VSCROLL/WM_HSCROLL) geschickt. Dies simuliert
ein Ziehen des Scroll-Balkens.

:h2 res=1903 id=msgline.Arbeitsweise - Tastatur Nachrichten
:p.Wird dieser Knopf gew„hlt, wird an das jeweilige Fenster der
Tastatur-Code einer Cursortaste geschickt (WM_CHAR). Dies simuliert das Drcken einer 
Pfeil-Taste, falls das Fenster dieses Feature untersttzt.

:h2 res=1904 id=msgpage.Arbeitsweise - Scrollen einer Seite pro Scrolleinheit
:p.Wird dieser Knopf gew„hlt, wird an das jeweilige Fenster der
Tastatur-Coder der Bl„ttertasten geschickt (WM_CHAR). Dies simuliert das Drcken
einer Bild-Taste, falls das Fenster dieses Feature untersttzt.

:h2 res=1905 id=msgvol.Arbeitsweise - Einstellen der Lautst„rke
:p.Wird dieser Knopf gew„hlt, wird bei Drehen des R„dchens die Lautst„rke des Multimedia-Systems
ver„ndert.

:h2 res=1906 id=keyboard.Wirkt auf aktives Fenster
:p.Wird dieser Radioknopf gew„hlt, so wird bei einer
Drehung am R„dchen die vertikale Bl„tterleiste des
Fensters bewegt, das gerade aktiv ist.
:p.Dabei kann bei manchen M„usen durch Niederdrcken des
R„dchens die Aktivierung auch auf das Fenster, das
sich gegenw„rtig unter dem Zeiger befindet, vorgenommen
werden.
:note text='Hinweis&colon.'.
Beachten Sie, daá mitunter in einem Hauptfenster mehrere
Unterfenster mit Bl„tterleisten vorkommen (z.B. im
Netscape Communicator). Es wird stets das Teilfenster bewegt,
das zuletzt selektiert wurde.

:h2 res=1907 id=pointer.Wirkt auf Fenster unter Mauszeiger
:p.Wird dieser Radioknopf gew„hlt, so wird bei einer
Drehung am R„dchen die vertikale Bl„tterleiste des
Fensters bewegt, ber dem sich der Mauszeiger gerade
befindet.
:note text='Hinweis&colon.'.
Dabei ist es belanglos ob dieses Fenster zu diesem
Zeitpunkt aktiv ist oder ob es sogar teilweise von
anderen Fenstern verdeckt ist.

:h2 res=1908 id=scrollitem.Rad-Geschwindigkeit
:p.Mit dem :hp2.Schiebeknopfsymbol:ehp2. kann eingestellt
werden um wieviele Zeilen ein Fenster herauf- bzw.
heruntergebl„ttert werden soll, wenn das R„dchen um
eine Raste weiterbewegt wird.

:h2 id=cancel.Widerrufen
:p.Die Einstellungen aller Parameter werden auf die Werte vor
der letzten nderung zurckgesetzt.

:h2 id=standard.Standard
:p.Die Default-Einstellungen werden gesetzt.

:h1 res=2100 id=wheel2.R„dchen 4
:i1 id=wheel2.R„dchen 4
:p.šber die Seite :hp2.R„dchen 4:ehp2. des Notizbuchs
:hp2.AMouse - Merkmale:ehp2. k”nnen die
Startwerte des Treibers eingestellt werden, die beim
Neustart des Rechners gelten sollen
:p.Die Einstellungen k”nnen durch entprechende
Auswahl auf dieser Seite durchgefhrt werden.
:p.Eine genaue Erkl„rung fr jedes Feld wird angezeigt,
wenn der entsprechende Begriff aus der
untenstehenden Liste ausgew„hlt wird&colon.
:ul compact.
:li.:link reftype=hd refid=scroll_vert.vertikales Scrollen:elink.
:li.:link reftype=hd refid=scroll_horz.horizontales Scrollen:elink.
:li.:link reftype=hd refid=accel_delay.Verz”gerung der Scroll-Beschleunigung:elink.
:li.:link reftype=hd refid=accel_value.Geschwindigkeit der Scroll-Beschleunigung:elink.
:li.:link reftype=hd refid=trackball.Anzahl der R„dchen:elink.
:li.:link reftype=hd refid=cancel.Widerrufen:elink.
:li.:link reftype=hd refid=standard.Standard:elink.
:eul.
:note text='Hinweis&colon.'.
Nur wenn ein R„dchen erkannt wurde, enth„lt das
Notizbuch auch die entsprechende Seite.

:h2 res=2101 id=scroll_vert.Vertikales Scrollen
:p.Nach dem Systemstart wird beim Drehen des R„dchens vertikal gescrollt.

:h2 res=2102 id=scroll_horz.Horizontales Scrollen
:p.Nach dem Systemstart wird beim Drehen des R„dchens horizontal gescrollt.

:h2 res=2103 id=accel_delay.Verz”gerung der Scroll-Beschleunigung (Verz”gerungszeit)
:p.Wird das R„dchen ber die Verz”gerungszeit hinaus schnell gedreht, wird die Zahl der Zeilen, um die 
gescrollt kontinuierlich erh”ht. Die Verz”gerungszeit l„át sich im Bereich von 100 bis 2000 ms einstellen.

:h2 res=2104 id=accel_value.Geschwindigkeit der Scroll-Beschleunigung (Beschleunigungswert)
:p.Dieser Schieberegler legt fest, um wieviele Scrolleinheiten beim schnellen Drehen des R„dchens erh”ht wird.

:h2 res=2105 id=trackball.Anzahl der R„dchen
:p.Bei manchen M„usen l„át sich die Anzahl der R„dchen oder das Vorhandensein eines Trackballs nicht detektieren.
In diesem Fall kann mit diesem Knopf eingestellt werden, ob die Maus 2 R„dchen bzw. einen Trackball besitzt.

:h1 res=2300 id=wheel3.R„dchen 5
:i1 id=wheel3.R„dchen 5
:p.Die Seite :hp2.R„dchen 5:ehp2. definiert Ausnahmen im Verhalten des R„dchens fr bestimmte Applikationen.
Wird an der Maus das R„dchen gedreht, wird in der Liste auf dieser Seite nach einer passenden Beschreibung fr 
ein Fenster /  Control gesucht. Hierbei wird die Liste :hp2.Beschreibung:ehp2. von oben nach unten abgearbeitet, 
bis eine šbereinstimmung mit der Anwendung unter dem Mauszeiger festgestellt wird. 
Findet keine šbereinstimmung statt, wird die Default-Liste von :hp2.AMouse:ehp2. 
(definiert in :font facename=Courier size=14x14.AMouRes.rc:font facename=default.) abgearbeitet. Der Beschreibungstext in der Liste dient zur Identifikation 
durch den Anwender, der Name ist daher willkrlich; er wird auch nicht auf Duplikate untersucht.
:p.Die Einstellungen k”nnen durch entprechende
Auswahl auf dieser Seite durchgefhrt werden.
:p.Eine genaue Erkl„rung fr jedes Feld wird angezeigt,
wenn der entsprechende Begriff aus der
untenstehenden Liste ausgew„hlt wird&colon.
:ul compact.
:li.:link reftype=hd refid=wheel_up.&uarrow.:elink.
:li.:link reftype=hd refid=wheel_down.&darrow.:elink.
:li.:link reftype=hd refid=wheel_delete.L”schen:elink.
:li.:link reftype=hd refid=wheel_insert.Einfgen:elink.
:li.:link reftype=hd refid=cancel.Widerrufen:elink.
:eul.
:note text='Hinweis&colon.'.
Nur wenn ein R„dchen erkannt wurde, enth„lt das
Notizbuch auch die entsprechende Seite.

:p.:hp7.Beschreibung der Felder:ehp7.
:p.Das Verhalten wird im unteren Kasten angezeigt. Die linke Spalte definiert das 
Fenster / Control, auf das das R„dchen reagieren soll. Dabei bedeuten&colon.
:ul compact.
:li.:hp2.Application:ehp2.
.br
Name der Anwendung (z. B. :font facename=Courier size=14x14.PROGRAMM.EXE:font facename=default.). Ist das Feld leer, ist das 
Vergleichsergebnis immer TRUE. WPS-Klassen ben”tigen hier ein leeres Feld.
:li.:hp2.Class:ehp2.
.br
Window Class des Fensters / Controls. Hier steht entweder ein Klassenname 
(Groá-/Kleinschreibung beachten!) oder eine ID mit vorangestelltem &osq.&numsign.&csq.. Ist 
das Feld leer, ist das Vergleichsergebnis immer TRUE.
:li.:hp2.Parent Class:ehp2.
.br
Parent Window Class des Fensters / Controls. Hier steht entweder ein Klassenname 
(Groá-/Kleinschreibung beachten!) oder eine ID mit vorangestelltem &osq.&numsign.&csq.. Ist 
das Feld leer, ist das Vergleichsergebnis immer TRUE.
:li.:hp2.Option:ehp2.
.br
Falls fr bestimmte &osq.vRelation&csq. oder &osq.hRelation&csq. ben”tigt, steht hier eine Option (Beschreibung 
siehe dort). In allen anderen F„llen bleibt das Feld leer.
:eul.
:p.Die rechte Spalte definiert das Verhalten, welche Aktion das R„dchen ausl”sen soll. Dabei bedeuten&colon.
:ul compact.
:li.:hp2.Mode:ehp2.
.br
Definiert den Typ von Nachricht, der an das Fenster / Control geschickt werden soll. 
:hp2.Scroll:ehp2. wird verwendet, wenn auf der Seite 
:link reftype=hd refid=wheel1.R„dchen 1:elink. als Arbeitsweise
:link reftype=hd refid=msgscroll.Scroll Nachrichten:elink.
eingestellt wurde. :hp2.Cursor:ehp2. reagiert auf 
:link reftype=hd refid=msgline.Tastatur Nachrichten:elink.,
:hp2.Page:ehp2. auf 
:link reftype=hd refid=msgpage.Scrollen einer Seite pro Scrolleinheit:elink..
:hp2.Scroll or Cursor:ehp2. wirkt, wenn als Arbeitsweise entweder
:link reftype=hd refid=msgscroll.Scroll Nachrichten:elink. oder
:link reftype=hd refid=msgline.Tastatur Nachrichten:elink. eingestellt wurde.
:hp2.All:ehp2. reagiert auf alle Einstellungen.
:li.:hp2.vRelation bzw. hRelation:ehp2.
.br
Definiert, ob die Message direkt an das Fenster / Control geschickt werden soll oder ob in der 
Window-Hierarchie weitergesucht werden soll. Hierbei bedeuten&colon.
:ul compact.
:li.:hp2.None:ehp2.&colon. Message wird direkt an das gefundene Control geschickt.
:li.:hp2.Parent:ehp2.&colon. In der Beschreibungsliste wird nach einem passenden Parent gesucht.
:li.:hp2.Owner:ehp2.&colon. In der Beschreibungsliste wird nach einem passenden Owner gesucht.
:li.:hp2.Next:ehp2.&colon. In der Beschreibungsliste wird in z-Order nach hinten weitergesucht 
nach Controls, die ebenfalls unter dem Zeiger liegen.
:li.:hp2.CB Next:ehp2.&colon. Wird nur fr Comboboxen verwendet. Es bewirkt im wesentlichen 
dasselbe wie :hp2.Next:ehp2., behandelt aber die unsichtbare Fl„che unter dem Eingabefeld bei
zugeklappter Liste korrekt.
:li.:hp2.Sibling[Option]:ehp2.&colon. In der Beschreibungsliste wird nach einem Sibling-Window gesucht, 
das den Klassennamen besitzt, der unter :hp2.Option:ehp2. steht.
:eul.
:li.:hp2.vOption / hOption:ehp2.
.br
Enth„lt eine Option, die vom jeweiligen Messagetyp abh„ngig ist. Siehe dort.
:li.:hp2.Up / Down bzw. Left / Right:ehp2.
.br
Definiert die Message, die an das Fenster / control geschickt wird. Hierbei sind verfgbar&colon.
:ul compact.
:li.:hp2.WM_NULL:ehp2.&colon. Es wird keine Message gesandt. Wird normalerweise verwendet, 
wenn unter :hp2.vRelation:ehp2./:hp2.hRelation:ehp2. das Attribut :hp2.None:ehp2. verwendet wird.
:li.:hp2.WM_CONTROL:ehp2.&colon. Es wird ein Tastencode direkt an den Tastaturtreiber gesandt. 
Hierbei sind folgende Optionen m”glich&colon.
:ul compact.
:li.:hp2.page:ehp2.&colon. Der Tastencode fr die Tasten PgUp bzw. PgDown wird geschickt.
:li.:hp2.cursor up/down:ehp2.&colon. Der Tastencode fr die Auf/Ab-Cursortasten wird geschickt.
:li.:hp2.cursor left/right:ehp2.&colon. Der Tastencode fr die Links/Rechts-Cursortasten wird geschickt.
:li.:hp2.mult cursor up/down:ehp2.&colon. Der Tastencode fr die Auf/Ab-Cursortasten wird geschickt. 
Die Anzahl wird durch die Einstellung unter :link reftype=hd refid=scrollitem.Rad-Geschwindigkeit:elink. festgelegt.
:li.:hp2.mult cursor left/right:ehp2.&colon. Der Tastencode fr die Links/Rechts-Cursortasten wird geschickt.
Die Anzahl wird durch die Einstellung unter :link reftype=hd refid=scrollitem.Rad-Geschwindigkeit:elink. festgelegt.
:eul.
:li.:hp2.WM_VSCROLL:ehp2.&colon. Es wird eine vertikale Scroll-Message an den vertikalen Scrollbar geschickt.
:li.:hp2.WM_HSCROLL:ehp2.&colon. Es wird eine horizontale Scroll-Message an den horizontalen Scrollbar geschickt.
:li.:hp2.N x WM_VSCROLL:ehp2.&colon. Wie :hp2.WM_VSCROLL:ehp2., die Anzahl wird durch die Einstellung 
unter :link reftype=hd refid=scrollitem.Rad-Geschwindigkeit:elink. festgelegt.
:li.:hp2.N x WM_HSCROLL:ehp2.&colon. Wie :hp2.WM_HSCROLL:ehp2., die Anzahl wird durch die Einstellung 
unter :link reftype=hd refid=scrollitem.Rad-Geschwindigkeit:elink. festgelegt.
:li.:hp2.WM_CHAR:ehp2.&colon. Es wird eine Character-Message geschickt. Es sind dieselben Optionen wie
unter :hp2.WM_CONTROL:ehp2. m”glich.
:eul.
:eul.

:p.:hp7.Beispiele:ehp7.
:p.ltere Versionen von Mozilla (Version 1.3 und vorher) haben einen Fehler, wenn ber die normalen
WM_HSCROLL-Nachrichten horizontal gescrollt wird. Um dies zu beheben, wird dies mit den folgenden zwei 
Eintr„gen behoben.
:p.:artwork name='C:\work\c\amouse\Language\Help\Mozilla_Line_049.bmp' align=left.
:p.Dieser Eintrag reagiert, wenn auf der Seite :link reftype=hd refid=wheel1.R„dchen 1:elink. als 
Arbeitsweise :hp2.Scroll Nachrichten:ehp2. oder :hp2.Tastatur Nachrichten:ehp2. eingestellt ist.
In diesem Fall werden horizontal und vertikal an den Parent Character-Messages geschickt
(&odq.mult cursor&cdq.). Mozilla wird identifiziert, wenn sowohl :hp2.Class:ehp2. als auch 
:hp2.Parent Class:ehp2. vom Typ :hp2.MozillaWindowClass:ehp2. sind.
:p.:artwork name='C:\work\c\amouse\Language\Help\Mozilla_Page_049.bmp' align=left.
:p.Fr seitenweises Scrollen (:hp2.Mode = Page:ehp2.) wird vertikal eine PgUp/PgDown Character-Message
geschickt.
:p.:artwork name='C:\work\c\amouse\Language\Help\Command_Line_049.bmp' align=left.
:p.Das Standardverhalten beim Drehen des R„dchens ber einem Kommandofenster ist, daá der Fensterinhalt
gescrollt wird (falls Scrollbalken vorhanden sind). Die gezeigten Einstellungen bewirken, daá stattdessen die
Kommando-Historie durchgescrollt wird.

:h2 res=2313 id=wheel_up.&uarrow. (Eintrag nach oben bewegen)
:p.Bewegt den in der linken Liste selektierten Eintrag um eine Position nach oben.

:h2 res=2314 id=wheel_down.&darrow. (Eintrag nach unten bewegen)
:p.Bewegt den in der linken Liste selektierten Eintrag um einen Position nach unten.

:h2 res=2316 id=wheel_delete.L”schen
:p.L”scht den in der linken Liste selektierten Eintrag.

:h2 res=2315 id=wheel_insert.Einfgen
:p.Fgt einen neuen Eintrag in der linken Liste am Ende ein.

:h1 res=2700 id=insertappl.Anwendung einfgen
:i1 id=insertappl.Anwendung einfgen
:p.Dieser Dialog dient zur Eingabe einer neuen Beschreibung fr das Verhalten des Mausr„dchens.
Die Bedeutung der Felder entspricht der Beschreibung unter 
:link reftype=hd refid=wheel3.R„dchen 5:elink. Unter Beschreibung kann ein beliebiger Text 
eingegeben werden, der zur Identifikation der Eingaben in der Listbox unter
:link reftype=hd refid=wheel3.R„dchen 5:elink. dient.

:h1 res=1500 id=keys1.Tasten 1
:i1 id=keys1.Tasten 1
:p.šber die Seite :hp2.Tasten 1:ehp2. des Notizbuchs
:hp2.AMouse - Merkmale:ehp2. k”nnen die Aktionen
fr das Drcken der Tasten 3, 4 und 5 der Maus 
eingestellt werden.
:p.Die Einstellungen k”nnen durch entprechende
Auswahl auf dieser Seite durchgefhrt werden.
:p.Eine genaue Erkl„rung fr jedes Feld wird angezeigt,
wenn der entsprechende Begriff aus der
untenstehenden Liste ausgew„hlt wird&colon.
:ul compact.
:li.:link reftype=hd refid=button3.Taste 3:elink.
:li.:link reftype=hd refid=button4.Taste 4:elink.
:li.:link reftype=hd refid=button5.Taste 5:elink.
:li.:link reftype=hd refid=button6.Taste 6:elink.
:li.:link reftype=hd refid=button7.Taste 7:elink.
:li.:link reftype=hd refid=button8.Taste 8:elink.
:li.:link reftype=hd refid=button9.Taste 9:elink.
:li.:link reftype=hd refid=button10.Taste 10:elink.
:li.:link reftype=hd refid=cbutton3.Ctrl+Taste 3:elink.
:li.:link reftype=hd refid=cbutton4.Ctrl+Taste 4:elink.
:li.:link reftype=hd refid=cbutton5.Ctrl+Taste 5:elink.
:li.:link reftype=hd refid=cbutton6.Ctrl+Taste 6:elink.
:li.:link reftype=hd refid=cbutton7.Ctrl+Taste 7:elink.
:li.:link reftype=hd refid=cbutton8.Ctrl+Taste 8:elink.
:li.:link reftype=hd refid=cbutton9.Ctrl+Taste 9:elink.
:li.:link reftype=hd refid=cbutton10.Ctrl+Taste 10:elink.
:li.:link reftype=hd refid=abutton3.Alt+Taste 3:elink.
:li.:link reftype=hd refid=abutton4.Alt+Taste 4:elink.
:li.:link reftype=hd refid=abutton5.Alt+Taste 5:elink.
:li.:link reftype=hd refid=abutton6.Alt+Taste 6:elink.
:li.:link reftype=hd refid=abutton7.Alt+Taste 7:elink.
:li.:link reftype=hd refid=abutton8.Alt+Taste 8:elink.
:li.:link reftype=hd refid=abutton9.Alt+Taste 9:elink.
:li.:link reftype=hd refid=abutton10.Alt+Taste 10:elink.
:li.:link reftype=hd refid=keycombset3.Setzen 3:elink.
:li.:link reftype=hd refid=keycombset4.Setzen 4:elink.
:li.:link reftype=hd refid=keycombset5.Setzen 5:elink.
:li.:link reftype=hd refid=keycombset6.Setzen 6:elink.
:li.:link reftype=hd refid=keycombset7.Setzen 7:elink.
:li.:link reftype=hd refid=keycombset8.Setzen 8:elink.
:li.:link reftype=hd refid=keycombset9.Setzen 9:elink.
:li.:link reftype=hd refid=keycombset10.Setzen 10:elink.
:li.:link reftype=hd refid=keycomb.Tastenkombination:elink.
:li.:link reftype=hd refid=cancel.Widerrufen:elink.
:li.:link reftype=hd refid=standard.Standard:elink.
:eul.
:note text='Hinweis&colon.'.
Nur wenn ein R„dchen erkannt wurde, enth„lt das
Notizbuch auch die entsprechende Seite.

:p.:hp2.Tastenfunktionen:ehp2.
:p.Folgende Funktionen sind vorhanden&colon.

:ul.
:li.:hp5.Ausschneiden:ehp5.
.br
Es wird die Clipboard-Funktion "Ausschneiden" geschickt (Shift-Entf)
:li.:hp5.Kopieren:ehp5.
.br
Es wird die Clipboard-Funktion "Kopieren" geschickt (Ctrl-Einfg)
:li.:hp5.Einfgen:ehp5.
.br
Es wird die Clipboard-Funktion "Einfgen" geschickt (Shift-Einfg)
:li.:hp5.Mitteltaste:ehp5.
.br
Die Reaktion entspricht der Standard-Taste 3 einer Maus. Die Umschalt-Tasten der 
Tastatur werden bercksichtigt und korrekt behandelt.
:li.:hp5.Alle Fenster verkleinern/verdecken:ehp5.
.br
Alle Fenster werden verkleinert oder verdeckt, entsprechend den M”glichkeiten
des Fensters.
:li.:hp5.Alle Fenster wiederherstellen:ehp5.
.br
Alle Fenster werden auf die Gr”áe vor einem Verkleinern oder Vergr”áern eingestellt.
:li.:hp5.Fensterliste:ehp5.
.br
Die Fensterliste wird angezeigt.
:li.:hp5.Anwendung schlieáen:ehp5.
.br
Die Anwendung wird beendet.
:li.:hp5.Doppelklick:ehp5.
.br
Es wird eine Doppelklick-Nachricht an die Anwendung geschickt.
:li.:hp5.Fenster vergr”áern:ehp5.
.br
Das Fenster wird auf maximale Gr”áe vergr”áert.
:li.:hp5.Fenster verkleinern/verdecken:ehp5.
.br
Das Fenster wird verkleinert oder verdeckt, entsprechend den M”glichkeiten
des Fensters.
:li.:hp5.Fenster wiederherstellen:ehp5.
.br
Das Fenster wird auf seine Gr”áe vor einem Verkleinern oder Vergr”áern eingestellt.
:li.:hp5.Scroll Richtung umschalten:ehp5.
.br
Die Scroll-Richtung wird zwischen vertikal und horizontal hin- und hergeschaltet
:li.:hp5.Fenster nach hinten schieben:ehp5.
.br
Das Fenster unter dem Mauszeiger wird hinter alle anderen Fenster auf dem
Desktop verschoben.
:li.:hp5.Tastenkombination:ehp5.
.br
Es wird der Tastencode der im Auswahlfeld gezeigten Tastenkombination an die Anwendung geschickt.
:li.:hp5.Keine Aktion:ehp5.
.br
Ein Druck des Knopfes hat keine Wirkung.
:eul.

:h2 res=1501 id=button3.Taste 3
:p.Mit diesem Auswahlfeld kann eingestellt werden, welche
Aktion durch Drcken der Taste 3 durchgefhrt werden soll.

:h2 res=1502 id=button4.Taste 4
:p.Mit diesem Auswahlfeld kann eingestellt werden, welche
Aktion durch Drcken der Taste 4 durchgefhrt werden soll.

:h2 res=1503 id=button5.Taste 5
:p.Mit diesem Auswahlfeld kann eingestellt werden, welche
Aktion durch Drcken der Taste 5 durchgefhrt werden soll.
                
:h2 res=1504 id=button6.Taste 6
:p.Mit diesem Auswahlfeld kann eingestellt werden, welche
Aktion durch Drcken der Taste 6 durchgefhrt werden soll.
                
:h2 res=1505 id=button7.Taste 7
:p.Mit diesem Auswahlfeld kann eingestellt werden, welche
Aktion durch Drcken der Taste 7 durchgefhrt werden soll.
                
:h2 res=1506 id=button8.Taste 8
:p.Mit diesem Auswahlfeld kann eingestellt werden, welche
Aktion durch Drcken der Taste 8 durchgefhrt werden soll.
                
:h2 res=1507 id=button9.Taste 9
:p.Mit diesem Auswahlfeld kann eingestellt werden, welche
Aktion durch Drcken der Taste 9 durchgefhrt werden soll.
                
:h2 res=1508 id=button10.Taste 10
:p.Mit diesem Auswahlfeld kann eingestellt werden, welche
Aktion durch Drcken der Taste 10 durchgefhrt werden soll.
                
:h2 res=1511 id=cbutton3.Strg+Taste 3
:p.Mit diesem Auswahlfeld kann eingestellt werden, welche
Aktion durch Drcken der Taste 3 zusammen mit der Strg-Taste auf der Tastatur
durchgefhrt werden soll.

:h2 res=1512 id=cbutton4.Strg+Taste 4
:p.Mit diesem Auswahlfeld kann eingestellt werden, welche
Aktion durch Drcken der Taste 4  zusammen mit der Strg-Taste auf der Tastatur
durchgefhrt werden soll.

:h2 res=1513 id=cbutton5.Strg+Taste 5
:p.Mit diesem Auswahlfeld kann eingestellt werden, welche
Aktion durch Drcken der Taste 5 zusammen mit der Strg-Taste auf der Tastatur
durchgefhrt werden soll.

:h2 res=1514 id=cbutton6.Strg+Taste 6
:p.Mit diesem Auswahlfeld kann eingestellt werden, welche
Aktion durch Drcken der Taste 6 zusammen mit der Strg-Taste auf der Tastatur
durchgefhrt werden soll.

:h2 res=1515 id=cbutton7.Strg+Taste 7
:p.Mit diesem Auswahlfeld kann eingestellt werden, welche
Aktion durch Drcken der Taste 7 zusammen mit der Strg-Taste auf der Tastatur
durchgefhrt werden soll.

:h2 res=1516 id=cbutton8.Strg+Taste 8
:p.Mit diesem Auswahlfeld kann eingestellt werden, welche
Aktion durch Drcken der Taste 8 zusammen mit der Strg-Taste auf der Tastatur
durchgefhrt werden soll.

:h2 res=1517 id=cbutton9.Strg+Taste 9
:p.Mit diesem Auswahlfeld kann eingestellt werden, welche
Aktion durch Drcken der Taste 9 zusammen mit der Strg-Taste auf der Tastatur
durchgefhrt werden soll.

:h2 res=1518 id=cbutton10.Strg+Taste 10
:p.Mit diesem Auswahlfeld kann eingestellt werden, welche
Aktion durch Drcken der Taste 10 zusammen mit der Strg-Taste auf der Tastatur
durchgefhrt werden soll.

:h2 res=1521 id=abutton3.Alt+Taste 3
:p.Mit diesem Auswahlfeld kann eingestellt werden, welche
Aktion durch Drcken der Taste 3 zusammen mit der Alt-Taste auf der Tastatur
durchgefhrt werden soll.

:h2 res=1522 id=abutton4.Alt+Taste 4
:p.Mit diesem Auswahlfeld kann eingestellt werden, welche
Aktion durch Drcken der Taste 4 zusammen mit der Alt-Taste auf der Tastatur
durchgefhrt werden soll.

:h2 res=1523 id=abutton5.Alt+Taste 5
:p.Mit diesem Auswahlfeld kann eingestellt werden, welche
Aktion durch Drcken der Taste 5 zusammen mit der Alt-Taste auf der Tastatur
durchgefhrt werden soll.

:h2 res=1524 id=abutton6.Alt+Taste 6
:p.Mit diesem Auswahlfeld kann eingestellt werden, welche
Aktion durch Drcken der Taste 6 zusammen mit der Alt-Taste auf der Tastatur
durchgefhrt werden soll.

:h2 res=1525 id=abutton7.Alt+Taste 7
:p.Mit diesem Auswahlfeld kann eingestellt werden, welche
Aktion durch Drcken der Taste 7 zusammen mit der Alt-Taste auf der Tastatur
durchgefhrt werden soll.

:h2 res=1526 id=abutton8.Alt+Taste 8
:p.Mit diesem Auswahlfeld kann eingestellt werden, welche
Aktion durch Drcken der Taste 8 zusammen mit der Alt-Taste auf der Tastatur
durchgefhrt werden soll.

:h2 res=1527 id=abutton9.Alt+Taste 9
:p.Mit diesem Auswahlfeld kann eingestellt werden, welche
Aktion durch Drcken der Taste 9 zusammen mit der Alt-Taste auf der Tastatur
durchgefhrt werden soll.

:h2 res=1528 id=abutton10.Alt+Taste 10
:p.Mit diesem Auswahlfeld kann eingestellt werden, welche
Aktion durch Drcken der Taste 10 zusammen mit der Alt-Taste auf der Tastatur
durchgefhrt werden soll.

:h2 res=1529 id=keycombset3.Tastenkombination 3 setzen
:p.Mit diesem Knopf wird die im Eingabefeld :link reftype=hd refid=keycomb.Tastenkombination:elink. eingegebene
Tastenkombination bernommen, wenn im :link reftype=hd refid=button3.Auswahlfeld:elink. :hp1.Tastenkombination:ehp1.
eingestellt wurde.

:h2 res=1530 id=keycombset4.Tastenkombination 4 setzen
:p.Mit diesem Knopf wird die im Eingabefeld :link reftype=hd refid=keycomb.Tastenkombination:elink. eingegebene
Tastenkombination bernommen, wenn im :link reftype=hd refid=button4.Auswahlfeld:elink. :hp1.Tastenkombination:ehp1.
eingestellt wurde.

:h2 res=1531 id=keycombset5.Tastenkombination 5 setzen
:p.Mit diesem Knopf wird die im Eingabefeld :link reftype=hd refid=keycomb.Tastenkombination:elink. eingegebene
Tastenkombination bernommen, wenn im :link reftype=hd refid=button5.Auswahlfeld:elink. :hp1.Tastenkombination:ehp1.
eingestellt wurde.

:h2 res=1532 id=keycombset6.Tastenkombination 6 setzen
:p.Mit diesem Knopf wird die im Eingabefeld :link reftype=hd refid=keycomb.Tastenkombination:elink. eingegebene
Tastenkombination bernommen, wenn im :link reftype=hd refid=button6.Auswahlfeld:elink. :hp1.Tastenkombination:ehp1.
eingestellt wurde.

:h2 res=1533 id=keycombset7.Tastenkombination 7 setzen
:p.Mit diesem Knopf wird die im Eingabefeld :link reftype=hd refid=keycomb.Tastenkombination:elink. eingegebene
Tastenkombination bernommen, wenn im :link reftype=hd refid=button7.Auswahlfeld:elink. :hp1.Tastenkombination:ehp1.
eingestellt wurde.

:h2 res=1534 id=keycombset8.Tastenkombination 8 setzen
:p.Mit diesem Knopf wird die im Eingabefeld :link reftype=hd refid=keycomb.Tastenkombination:elink. eingegebene
Tastenkombination bernommen, wenn im :link reftype=hd refid=button8.Auswahlfeld:elink. :hp1.Tastenkombination:ehp1.
eingestellt wurde.

:h2 res=1535 id=keycombset9.Tastenkombination 9 setzen
:p.Mit diesem Knopf wird die im Eingabefeld :link reftype=hd refid=keycomb.Tastenkombination:elink. eingegebene
Tastenkombination bernommen, wenn im :link reftype=hd refid=button9.Auswahlfeld:elink. :hp1.Tastenkombination:ehp1.
eingestellt wurde.

:h2 res=1536 id=keycombset10.Tastenkombination 10 setzen
:p.Mit diesem Knopf wird die im Eingabefeld :link reftype=hd refid=keycomb.Tastenkombination:elink. eingegebene
Tastenkombination bernommen, wenn im :link reftype=hd refid=button10.Auswahlfeld:elink. :hp1.Tastenkombination:ehp1.
eingestellt wurde.

:h2 res=1537 id=keycomb.Tastenkombination festlegen
:p.Dieses Eingabefeld erlaubt es, ein Tastenkrzel zu definieren, das einer beliebigen Maustaste zugeordnet
werden kann.
:p.Nachdem ein Tastenkrzel definiert und einer Maustaste zugeordnet wurde, wird diese Tastenkombination immer
an die Anwendung geschickt, wenn die entsprechende Maustaste gedrckt wird.
:p.Um ein Tastenkrzel zu definieren, muss in das Eingabefeld geklickt werden. Anschliessend einfach die 
Tastenkombination drcken, die einer Maustaste zugeordnet werden soll (z. B. :hp2.Alt-F4:ehp2.).
Das Eingabefeld zeigt dann diese Tastenkombination an. Durch drcken eines der Kn”pfe :hp2.Setzen:ehp2. wird diese 
Tastenkombination dann dem entsprechenden Mausknopf zugeordnet.

:h1 res=1700 id=keys2.Tasten 2
:i1 id=keys2.Tasten 2
:p.šber die Seite :hp2.Tasten 2:ehp2. des Notizbuchs
:hp2.AMouse - Merkmale:ehp2. kann das Verhalten verschiedener
Controls bei Mausaktionen ver„ndert werden.
:p.Die Einstellungen k”nnen durch entprechende
Auswahl auf dieser Seite durchgefhrt werden.
:p.Eine genaue Erkl„rung fr jedes Feld wird angezeigt,
wenn der entsprechende Begriff aus der
untenstehenden Liste ausgew„hlt wird&colon.
:ul compact.
:li.:link reftype=hd refid=dblclick_entry.Doppelklick auf Eingabefelder:elink.
:li.:link reftype=hd refid=click_combo.Klick auf Comboboxen:elink.
:li.:link reftype=hd refid=smartcruise.SmartCruise:elink.
:li.:link reftype=hd refid=cancel.Widerrufen:elink.
:li.:link reftype=hd refid=standard.Standard:elink.
:eul.

:h2 res=1701 id=dblclick_entry.Doppelklick auf Eingabefelder
:p.Wenn dieser Auswahlknopf ausgew„hlt wurde, wird beim Doppelklick auf ein Eingabefeld
ein komplettes Wort selektiert.

:h2 res=1702 id=click_combo.Klick auf Comboboxen
:p.Wenn dieser Auswahlknopf ausgew„hlt wurde, wird beim Klick auf das Eingabefeld einer
Combobox die Liste aufgerollt.

:h2 res=1703 id=smartcruise.SmartCruise
:p.Wenn dieser Auswahlknopf ausgew„hlt wurde, wird bei Logitech-M„usen vom Typ 
MX500, MX700 und MX1000 das SmartCruise Feature aktiviert. Die Einstellungen fr die Kn”pfe
7, 8, 9 und 10 werden in diesem Fall dann ignoriert.
Mit diesem Feature wirken die Kn”pfe 7 und 8 wie ein vertikales Rad, die Kn”pfe 9 und 10 (falls 
vorhanden) wie ein horizontales Rad.

:h1 res=1100 id=devinfo.Ger„teinformation
:i1 id=devinfo.Ger„teinformation
:p.Diese Dialogseite zeigt die Versionsst„nde der :hp1.AMouse:ehp1.-Software an.
:p.Zudem wird angezeigt, welcher Typ von Maus vom System
erkannt wurde. Dabei werden Anschluá,
Anzahl der Mauskn”pfe und das Vorhandensein eines R„dchens
gemeldet.
:note text='Hinweis&colon.'.
Bei vielen M„usen l„át sich die Zahl der vorhandenen Kn”pfe nicht korrekt ermitteln.
Auáerdem untersttzt der Presentation Manager nur maximal 3 Kn”pfe. Aus diesem Grund
wird die Anzahl m”glicherweise falsch angezeigt, wenn die Maus mehr als 3 besitzt.

:h1 res=1300 id=wldevinfo.Ger„teinformation 2
:i1 id=wldevinfo.Ger„teinfo 2
:p.Diese Dialogseite zeigt spezifische Informationen zu drahtlosen M„usen, falls diese die Abfrage dieser 
Daten untersttzen. 
:p.Die :hp5.Ger„tenummer:ehp5. ist interessant fr USB-Ger„te und zeigt den Ger„teindex.
:p.Die :hp5.Kanalnummer:ehp5. zeigt den verwendeten Kanal bei Ger„ten, die ber mehrere Kan„le verfgen.
:p.Der :hp5.Batteriezustand:ehp5. zeigt den aktuellen Ladezustand der Batterie in der Maus.
:p.Eine genaue Erkl„rung fr jedes Feld wird angezeigt,
wenn der entsprechende Begriff aus der
untenstehenden Liste ausgew„hlt wird&colon.
:ul compact.
:li.:link reftype=hd refid=battery_warning.Batteriewarnung:elink.
:eul.

:h2 res=1304 id=battery_warning.Batteriewarnung
:p.Wenn dieser Auswahlknopf gew„hlt wird, erscheint ein Warnhinweis, wenn die Batterie der Maus
fast leer ist.

:h1 res=2500 id=timing.Zeitangaben
:i1 id=timing.Zeitangaben
:p.Diese Dialogseite dient zur Einstellung einiger Zeitangaben der Maus: der internen Abfragerate sowie
der Beschleunigungswerte.
:p.:hp5.Funktion der Beschleunigung:ehp5.&colon. Fr jeden Maus-Event wird die Zahl der physikalischen Einheiten, die die
Maus bewegt wurde, verglichen gegen 2 Schwellwerte. Wenn die Zahl gr”áer ist als der zweite Schwellwert,
wird die Zahl der Einheiten multipliziert mit einem "2nd level Multiplikator". Ist die Zahl zwischen dem ersten und
zweiten Schwellwert, wird die Zahl der Einheiten multipliziert mit einem "1st level Multiplikator". In jedem anderen
Fall wird kein Multiplikator bentzt. Dies wird jeweils unabh„ngig fr die X- und Y-Achse durchgefhrt.
Die Werte berechnen sich wie folgt&colon.
:table cols='20 20' rules=both frame=box.
:row.
:c.1. Schwellwert
:c.Wert des Schiebereglers
:row.
:c.2. Schwellwert
:c.Wert des Schiebereglers * 7
:row.
:c.1st level Multiplikator
:c.Wert des Schiebereglers
:row.
:c.2nd level Multiplikator
:c.Wert des Schiebereglers * 2
:etable.

:ul compact.
:li.:link reftype=hd refid=pollrate.Maus Abfragerate:elink.
:li.:link reftype=hd refid=mouaccel_value.Beschleunigungswert:elink.
:li.:link reftype=hd refid=mouaccel_threshold.Beschleunigungsschwelle:elink.
:li.:link reftype=hd refid=cancel.Widerrufen:elink.
:li.:link reftype=hd refid=standard.Standard:elink.
:eul.

:h2 res=2501 id=pollrate.Maus Abfragerate
:p.Dieser Schieberegler legt die mausinterne Abfragerate fest. 

:h2 res=2502 id=mouaccel_value.Beschleunigungswert
:p.Dieser Schieberegler definiert den Multiplikator fr die Mausbeschleunigung.

:h2 res=2503 id=mouaccel_threshold.Beschleunigungsschwelle
:p.Dieser Schieberegler definiert den Schwellwert fr die Mausbeschleunigung

:euserdoc.

