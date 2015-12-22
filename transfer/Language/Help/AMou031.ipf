.************************************************
.*
.*   Copyright 2002-2006 nb software
.*
.*   Help for AMouse                                                                             
.************************************************

:userdoc.

:h1 res=10 id=aboutMain.AMouse - Uitgebreide muis configuratie
:i1 id=aboutMain.AMouse - Uitgebreide muis configuratie
:p.:artwork name='C:\work\c\amouse\Language\Help\amouse.bmp' runin align=left.
Dit programma kan gebruikt worden voor de configuratie van het wiel of een
"wielmuis" (b.v. Intelli-Mouse). Het kan&colon.

:ul compact.
:li.de werking van het wiel beheren
:li.het aantal bladervergrotingen van het wiel instellen
:li.de functie van de muisknoppen 3...5 bepalen
:eul.

:h1 res=1900 id=wheel1.Wiel 1/2/3
:i1 id=wheel1.Wiel 1/2/3
:p.Deze pagina wordt gebruikt om de acties van de muis, die voortkomen 
uit het draaien van het wiel, in te stellen. Er is voor elke ondersteunde
combinatie van wiel + shift toets een pagina.
:p.Een uitgebreidere verklaring van elke mogelijkheid zal getoond worden, als u
op ‚‚n van de onderwerpen uit de onderstaande lijst klikt&colon.

:ul compact.
:li.:link reftype=hd refid=no_func.Geen functie:elink.
:li.:link reftype=hd refid=msgscroll.Boodschappen bladeren:elink.
:li.:link reftype=hd refid=msgline.Toetsenbord boodschappen:elink.
:li.:link reftype=hd refid=msgpage.Blader de gehele pagina per bladereenheid:elink.
:li.:link reftype=hd refid=msgvol.Instellen audio volume:elink.
:li.:link reftype=hd refid=keyboard.Werkt op actieve venster:elink.
:li.:link reftype=hd refid=pointer.Werkt op venster onder de muisaanwijzer:elink.
:li.:link reftype=hd refid=scrollitem.Wielsnelheid:elink.
:li.:link reftype=hd refid=cancel.Ongedaan maken:elink.
:li.:link reftype=hd refid=standard.Standaard:elink.
:eul.
:note.
Deze pagina is alleen zichtbaar als er een wiel gevonden is op de muis.

:h2 res=1901 id=no_func.Werkingsmodus - Geen functie
:p.Als deze keuze geselecteerd is zal een draaiing van het wiel genegeerd
worden door het systeem.

:h2 res=1902 id=msgscroll.Werkingsmodus - Boodschappen bladeren
:p.Als deze knop geselecteerd is, zal er een bladerboodschap (WM_VSCROLL/WM_HSCROLL) 
naar de tekst vensters gestuurd worden. Dit simuleert het bewegen van de bladerbalk.

:h2 res=1903 id=msgline.Werkingsmodus - Toetsenbord boodschappen
:p.Als deze knop geselecteerd is, zal er een WM_CHAR boodschap naar de tekstvensters
gestuurd worden. Dit simuleert het indrukken van een cursortoets, als deze mogelijkheid
ondersteund wordt door het venster.

:h2 res=1904 id=msgpage.Werkingsmodus -  Blader de gehele pagina per bladereenheid
:p.Als deze knop geselecteerd is, zal er een WM_CHAR boodschap naar de tekstvensters
gestuurd worden. Dit simuleert het indrukken van een pagina naar boven of beneden toets,
als deze mogelijkheid ondersteund wordt door het venster.

:h2 res=1905 id=msgvol.Werkingsmodus - Instellen audio volume
:p.Als deze knop geselecteerd is, zal het draaien van het wiel het volume van het multimedia systeem instellen.

:h2 res=1906 id=keyboard.Werkt op het actieve venster
:p.Als deze keuze geselecteerd wordt, zal de verticale bladerbalk van het
actieve venster verplaatst worden.
:p.Bij sommige muizen zal het venster onder de muisaanwijzer geactiveerd worden
door het indrukken van het wiel.
:note.
Op sommige vensters kan het zijn dat subvensters ook bladerbalken bevatten (b.v. in
Netscape Communicator). In dit geval zal het laatst geselecteerde venster verplaatst worden.

:h2 res=1907 id=pointer.Werkt op venster onder muisaanwijzer
:p.Als deze keuze geselecteerd is, zal de verticale bladerbalk van het venster
onder de muisaanwijzer verplaatst worden.
:note.
Het maakt niet uit of dit venster op dit moment actief is, of zelfs als het gedeeltelijk
verborgen is achter andere vensters.

:h2 res=1908 id=scrollitem.Wielsnelheid
:p. Met de :hp2.draaiknop:ehp2. kan het aantal regels geselecteerd worden die gebladerd
worden als het wiel ‚‚n tandje verplaatst wordt.

:h2 id=cancel.Ongedaan maken
:p.De instellingen van alle parameters worden teruggezet naar de waarden die ze hadden voor de laatste wijziging.

:h2 id=standard.Standaard
:p.De standaard instellingen worden gekozen.

:h1 res=2100 id=wheel2.Wiel 4
:i1 id=wheel2.Wiel 4
:p.Deze pagina wordt gebruikt om de opstartwaarden van het stuurprogramma in te stellen,
die geldig zijn op het moment van opstarten van de PC.
:p.De instellingen kunnen gedaan worden met de betreffende knop op deze
instellingen pagina.
:p.Een meer gedetailleerde verklaring van elke mogelijkheid zal getoond worden
als u op ‚‚n van de onderstaande onderwerpen klikt.
:ul compact.
:li.:link reftype=hd refid=scroll_vert.verticaal bladeren:elink.
:li.:link reftype=hd refid=scroll_horz.horizontaal bladeren:elink.
:li.:link reftype=hd refid=accel_delay.vertraging van de bladeracceleratie:elink.
:li.:link reftype=hd refid=accel_value.snelheid van bladeracceleratie:elink.
:li.:link reftype=hd refid=trackball.Aantal wielen:elink.
:li.:link reftype=hd refid=cancel.Ongedaan maken:elink.
:li.:link reftype=hd refid=standard.Standaard:elink.
:eul.
:note.
Deze pagina is alleen zichtbaar, als er een wiel gevonden is op de muis.

:h2 res=2101 id=scroll_vert.Opstartwaarden - verticaal bladeren
:p.Als deze knop geselecteerd is, zal het draaien van het wiel op een muis met enkel wiel
resulteren in verticaal bladeren.

:h2 res=2102 id=scroll_horz.Opstartwaarden - horizontaal bladeren
:p.Als deze knop geselecteerd is, zal het draaien van het wiel op een muis met enkel wiel
resulteren in horizontaal bladeren.

:h2 res=2103 id=accel_delay.Vertraging van bladeracceleratie (Vertragingstijd)
:p.Als het wiel snel gedraaid wordt langer dan de vertragingstijd, zal het aantal regels gebruikt
voor het bladeren continue verhoogd worden. De vertragingstijd kan aangepast worden tussen 100 en 2000 ms.

:h2 res=2104 id=accel_value.Snelheid van bladeracceleratie (Acceleratiewaarde)
:p.Deze schuifbalk stelt het aantal te gebruiken bladereenheden in die gebruikt worden voor de toename, als het
wiel snel gedraaid wordt.

:h2 res=2105 id=trackball.Aantal wielen
:p.Sommige muizen zijn niet in staat om het aantal wielen of de aanwezigheid van een trackball kenbaar
te maken aan het muis stuurprogramma. In dit geval is het mogelijk om deze eigenschap met deze knop in te stellen.

:h1 res=2300 id=wheel3.Wiel 5
:i1 id=wheel3.Wiel 5
:p.De :hp2.Wiel 5:ehp2. pagina bepaald de uitzonderingen van gedrag voor sommige applicaties.
Als u de muis in de lijst op deze pagina draait zal een geschikte omschrijving van een venster/bediening gezocht worden.
Hier zal de lijst met :hp2.omschrijvingen:ehp2. naar beneden doorzocht worden totdat er een overeenkomst met de applicatie onder de muisaanwijzer gevonden is.
Als er geen overeenkomst gevonden is, zal de standaard lijst van :hp2.AMouse:ehp2. (gedefinieerd in :font facename=Courier size=14x14.AMouRes.rc:font facename=default.)
genomen worden. De omschrijving in de lijst dient ter identificatie voor de gebruiker, waardoor de naam arbitrair is; er kunnen zelfs dubbele namen voorkomen.
:p.De instellingen kunnen gedaan worden met de beschikbare knoppen op deze instellingenpagina.
:p.Een uitgebreidere toelichting voor elke bedieningsmogelijkheid zal getoond worden, als u op ‚‚n van
de onderwerpen in de onderstaande lijst klikt&colon.
:ul compact.
:li.:link reftype=hd refid=wheel_up.&uarrow.:elink.
:li.:link reftype=hd refid=wheel_down.&darrow.:elink.
:li.:link reftype=hd refid=wheel_delete.Verwijderen:elink.
:li.:link reftype=hd refid=wheel_insert.Invoegen:elink.
:li.:link reftype=hd refid=cancel.Annuleren:elink.
:eul.
:note.
Deze pagina is alleen zichtbaar, als er een wiel gevonden is op de muis.

:p.:hp7.Beschrijving van de velden:ehp7.
:p.Het gedrag wordt getoond in het onderste kader. De linkerkolom definieert het venster/besturing
dat zal reageren op het draaien van het wiel. De betekenissen zijn als volgt&colon.
:ul compact.
:li.:hp2.Programma:ehp2.
.br
Naam van het programma (b.v. :font facename=Courier size=14x14.PROGRAMMA.EXE:font facename=default.).
Als dit veld leeg gelaten wordt, zal de vergelijking altijd TRUE zijn. Voor WPS classes dient dit veld altijd leeg te zijn.
:li.:hp2.Class:ehp2.
.br
Venster class van het venster/besturing. Hier wordt ofwel de class naam (hoofdlettergevoelig!) ofwel het id
voorafgegaan door een &osq.&numsign.&csq. ingevoerd. Als dit veld leeg gelaten wordt, zal de vergelijking altijd TRUE zijn. 
:li.:hp2.Hogere class:ehp2.
.br
Hogere class van het venster/besturing. Hier wordt ofwel de class naam (hoofdlettergevoelig!) ofwel het id
voorafgegaan door een &osq.&numsign.&csq. ingevoerd. Als dit veld leeg gelaten wordt, zal de vergelijking altijd TRUE zijn. 
:li.:hp2.Optie:ehp2.
.br
Indien nodig voor een specifieke &osq.vRelatie&csq. of &osq.hRelatie&csq., zal hier een optie te vinden zijn (zie de omschrijving).
In alle andere gevallen zal dit veld leeg blijven.
:eul.
:p.De rechter kolom definieert de actie die gestart wordt door het wiel. De betekenissen zijn&colon.
:ul compact.
:li.:hp2.Modus:ehp2.
.br
Bepaalt de soort boodschap dat naar het venster/besturing gestuurd wordt.
:hp2.Bladeren:ehp2. zal gebruikt worden op een pagina
:link reftype=hd refid=wheel1.Wiel 1:elink. de werkingsmodus
:link reftype=hd refid=msgscroll.Boodschappen bladeren:elink. is geselecteerd.
:hp2.Aanwijzer:ehp2. reageert op
:link reftype=hd refid=msgline.Toetsenbord boodschappen:elink.,
:hp2.Pagina:ehp2. op
:link reftype=hd refid=msgpage.Blader gehele pagina per bladereenheid:elink..
:hp2.Bladeren of Aanwijzer:ehp2. reageert, als de geselecteerde werkingsmodus is ‚‚n van
:link reftype=hd refid=msgscroll.Boodschappen bladeren:elink. or
:link reftype=hd refid=msgline.Toetsenbord boodschappen:elink..
:hp2.Alle:ehp2. reageert op alle instellingen.
:li.:hp2.vRelatie resp. hRelatie:ehp2.
.br
Bepaalt of de boodschap direct naar het venster/besturing gestuurd moet worden of dat er verder gezocht
moet worden in de vensterhi‰rarchie. De betekenissen zijn&colon.
:ul compact.
:li.:hp2.Geen:ehp2.&colon. De boodschap wordt direct naar de gevonden besturing gestuurd.
:li.:hp2.Ouder:ehp2.&colon. Er wordt naar een geschikte ouder gezocht in de lijst met omschrijvingen.
:li.:hp2.Eigenaar:ehp2.&colon. Er wordt naar een geschikte eigenaar gezocht in de lijst met omschrijvingen.
:li.:hp2.Volgende:ehp2.&colon. Het zoeken zal doorgaan in de z-order van besturingen die ook onder de
muisaanwijzer liggen.
:li.:hp2.CB Volgende:ehp2.&colon. Wordt alleen gebruikt bij gecombineerde selectielijsten. Het doet in principe hetzelfde als :hp2.Volgende:ehp2.,
maar gaat over de onzichtbare ruimte onder het invoerveld als deze selectielijst niet getoond wordt.
:li.:hp2.Verwant[optie]:ehp2.&colon. Er zal naar een verwant venster gezocht worden in de lijst met omschrijvingen op basis
van de class naam zoals die opgegeven is in het :hp2.optie:ehp2. invoerveld.
:eul.
:li.:hp2.vOptie / hOptie:ehp2.
.br
Bevat een optie, afhankelijk van het ingestelde boodschaptype. Zie aldaar.
:li.:hp2.Omhoog / Omlaag bzw. Links / Rechts:ehp2.
.br
Bepaalt welke boodschap naar het venster/besturing gestuurd wordt. Hier zijn de volgende boodschappen beschikbaar&colon.
:ul compact.
:li.:hp2.WM_NULL:ehp2.&colon. Er zal geen boodschap gestuurd worden. Gewoon gebruik, als op
:hp2.vRelatie:ehp2./:hp2.hRelatie:ehp2. het attribuut :hp2.Geen:ehp2. gebruikt wordt.
:li.:hp2.WM_CONTROL:ehp2.&colon. Een toetsenbordcode wordt direct naar het toetsenbord stuurprogramma gestuurd.
De volgende opties zijn mogelijk&colon.
:ul compact.
:li.:hp2.pagina:ehp2.&colon. De toetsenbordcode voor de PgUp/PgDn toets wordt gestuurd.
:li.:hp2.cursor omhoog/omlaag:ehp2.&colon. De toetsenbordcode voor de Omhoog/Omlaag cursor toets wordt gestuurd.
:li.:hp2.cursor links/rechts:ehp2.&colon. De toetsenbordcode voor de Links/Rechts cursor toets wordt gestuurd.
:li.:hp2.meerdere cursor omhoog/omlaag:ehp2.&colon. De toetsenbordcode voor de Omhoog/Omlaag cursor toets wordt gestuurd.
Het aantal boodschappen dat gestuurd wordt is gedefinieerd door :link reftype=hd refid=scrollitem.Wielsnelheid:elink..
:li.:hp2.meerdere cursor links/rechts:ehp2.&colon. De toetsenbordcode voor de Links/Rechts cursor toets wordt gestuurd.
Het aantal boodschappen dat gestuurd wordt is gedefinieerd door :link reftype=hd refid=scrollitem.Wielsnelheid:elink..
:eul.
:li.:hp2.WM_VSCROLL:ehp2.&colon. Een verticale bladerboodschap wordt naar de verticale bladerbalk gestuurd.
:li.:hp2.WM_HSCROLL:ehp2.&colon. Een horizontale bladerboodschap wordt naar de horizontale bladerbalk gestuurd.
:li.:hp2.N x WM_VSCROLL:ehp2.&colon. Als :hp2.WM_VSCROLL:ehp2., maar het aantal boodschappen is gedefinieerd door
:link reftype=hd refid=scrollitem.Wielsnelheid:elink..
:li.:hp2.N x WM_HSCROLL:ehp2.&colon. Als :hp2.WM_HSCROLL:ehp2., maar het aantal boodschappen is gedefinieerd door
:link reftype=hd refid=scrollitem.Wielsnelheid:elink..
:li.:hp2.WM_CHAR:ehp2.&colon. Een karakterboodschap wordt gestuurd. Dezelfde opties als voor
:hp2.WM_CONTROL:ehp2. zijn mogelijk.
:eul.
:eul.

:p.:hp7.Voorbeelden:ehp7.
:p.Als gevolg van een fout in oudere Mozilla versies (versie 1.3 en ouder) werkt horizontaal bladeren via de gewone WM_SCROLL boodschappen
niet. Een noodoplossing hiervoor kan wellicht verkregen worden door de volgende twee ingangen.
:p.:artwork name='C:\work\c\amouse\Language\Help\Mozilla_Line_001.bmp' align=left.
:p.Deze ingang werkt, indien op pagina :link reftype=hd refid=wheel1.Wiel 1:elink. als de werkingsmodus
:hp2.Bladeren boodschappen:ehp2. of :hp2.Toetsenbord bladeren:ehp2. geselecteerd is.
In dit geval worden horizontale en verticale cursor toets boodschappen naar de ouder gestuurd.
(&odq.meerdere cursor&cdq.). Mozilla wordt herkend, zowel als :hp2.class:ehp2. als 
:hp2.Ouder class:ehp2. van het type :hp2.MozillaWindowClass:ehp2. zijn.
:p.:artwork name='C:\work\c\amouse\Language\Help\Mozilla_Page_001.bmp' align=left.
:p.Voor pagina's bladeren (:hp2.Modus = Pagina:ehp2.) wordt er een PgUp/PgDn boodschap gestuurd bij verticaal bladeren.
:p.:artwork name='C:\work\c\amouse\Language\Help\Command_Line_001.bmp' align=left.
:p.Als u het wiel draait boven een opdrachtregel venster, is het standaard gedrag om door de vensterinhoud te bladeren (als er
bladerbalken aanwezig zijn).
De getoonde instellingen veroorzaken echter het bladeren door de opdrachtengeschiedenis.

:h2 res=2313 id=wheel_up.&uarrow. (Verplaats ingang hoger)
:p.Verplaatst de geselecteerde ingang in de programmalijst ‚‚n positie hoger.

:h2 res=2314 id=wheel_down.&darrow. (Verplaats ingang lager)
:p.Verplaatst de geselecteerde ingang in de programmalijst ‚‚n positie lager.

:h2 res=2316 id=wheel_delete.Verwijderen
:p.Verwijdert de in de programmalijst geselecteerde ingang links van deze knop.

:h2 res=2315 id=wheel_insert.Invoegen
:p.Voegt een nieuwe ingang aan de programmalijst toe, links van deze knop.

:h1 res=2700 id=insertappl.Invoegen programma
:i1 id=insertappl.Invoegen programma
:p.Deze dialoog is bedoeld voor het invoeren van een nieuwe definitie van wielgedrag voor
een geselecteerd programma. De betekenis van de knoppen komt overeen met de beschrijving in
:link reftype=hd refid=wheel3.wiel 5:elink. :hp2.Omschrijving:ehp2. kan gebruikt worden voor het invoeren van
elke gebruikerseigen tekst die de ingangen in de selectielijst van :link reftype=hd refid=wheel3.wiel 5:elink..
identificeert.

:h1 res=1500 id=keys1.Toetsen 1
:i1 id=keys1.Toetsen 1
:p.Deze pagina wordt gebruikt voor het bepalen van de acties voor de knoppen 3, 4 en 5 van de muis.
:p.De instellingen kunnen gedaan worden door selectie van de betreffende keuze op deze instellingenpagina.
:p.Er zal een uitgebreidere verklaring van elke besturing gegeven worden, als u op ‚‚n van de
onderwerpen in onderstaande lijst klikt&colon.
:ul compact.
:li.:link reftype=hd refid=button3.Knop 3:elink.
:li.:link reftype=hd refid=button4.Knop 4:elink.
:li.:link reftype=hd refid=button5.Knop 5:elink.
:li.:link reftype=hd refid=button6.Knop 6:elink.
:li.:link reftype=hd refid=button7.Knop 7:elink.
:li.:link reftype=hd refid=button8.Knop 8:elink.
:li.:link reftype=hd refid=button9.Knop 9:elink.
:li.:link reftype=hd refid=button10.Knop 10:elink.
:li.:link reftype=hd refid=cbutton3.Ctrl+Knop 3:elink.
:li.:link reftype=hd refid=cbutton4.Ctrl+Knop 4:elink.
:li.:link reftype=hd refid=cbutton5.Ctrl+Knop 5:elink.
:li.:link reftype=hd refid=cbutton6.Ctrl+Knop 6:elink.
:li.:link reftype=hd refid=cbutton7.Ctrl+Knop 7:elink.
:li.:link reftype=hd refid=cbutton8.Ctrl+Knop 8:elink.
:li.:link reftype=hd refid=cbutton9.Ctrl+Knop 9:elink.
:li.:link reftype=hd refid=cbutton10.Ctrl+Knop 10:elink.
:li.:link reftype=hd refid=abutton3.Alt+Knop 3:elink.
:li.:link reftype=hd refid=abutton4.Alt+Knop 4:elink.
:li.:link reftype=hd refid=abutton5.Alt+Knop 5:elink.
:li.:link reftype=hd refid=abutton6.Alt+Knop 6:elink.
:li.:link reftype=hd refid=abutton7.Alt+Knop 7:elink.
:li.:link reftype=hd refid=abutton8.Alt+Knop 8:elink.
:li.:link reftype=hd refid=abutton9.Alt+Knop 9:elink.
:li.:link reftype=hd refid=abutton10.Alt+Knop 10:elink.
:li.:link reftype=hd refid=keycombset3.Set 3:elink.
:li.:link reftype=hd refid=keycombset4.Set 4:elink.
:li.:link reftype=hd refid=keycombset5.Set 5:elink.
:li.:link reftype=hd refid=keycombset6.Set 6:elink.
:li.:link reftype=hd refid=keycombset7.Set 7:elink.
:li.:link reftype=hd refid=keycombset8.Set 8:elink.
:li.:link reftype=hd refid=keycombset9.Set 9:elink.
:li.:link reftype=hd refid=keycombset10.Set 10:elink.
:li.:link reftype=hd refid=keycomb.Key combination:elink.
:li.:link reftype=hd refid=cancel.Annuleren:elink.
:li.:link reftype=hd refid=standard.Standaard:elink.
:eul.
:note.
Deze pagina is alleen zichtbaar als er een wiel op de muis gevonden is.

:p.:hp2.Knop functies:ehp2.
:p.De volgende functies zijn beschikbaar&colon.

:ul.
:li.:hp5.Knippen:ehp5.
.br
De klembord functie "Knippen" zal uitgevoerd worden (Shift-Del)
:li.:hp5.Kopi‰ren:ehp5.
.br
De klembord functie "Kopi‰ren" zal uitgevoerd worden (Ctrl-Ins)
:li.:hp5.Plakken:ehp5.                                
.br
De klembord functie "Plakken" zal uitgevoerd worden (Shift-Ins)
:li.:hp5.Centreren knop:ehp5.
.br
De geselecteerde knop zal zich gedragen als de standaard knop 3 van een muis. De status
van de shift toetsen op het toetsenbord wordt bewaard en correct verwerkt.
:li.:hp5.Verkleinen/Alle vensters verbergen:ehp5.
.br
Alle vensters worden verkleind of verborgen, afhankelijk van het venstergedrag.
:li.:hp5.Alle vensters herstellen:ehp5.
.br
Alle vensters zullen hersteld worden naar de grootte die ze hadden voor de verkleinen/verbergen/maximaliseren functie.
:li.:hp5.Vensterlijst:ehp5.
.br
De vensterlijst zal getoond worden.
:li.:hp5.Programma sluiten:ehp5. 
.br
Het programma zal gesloten worden.
:li.:hp5.Dubbel klikken:ehp5.
.br
Er zal een dubbele klik boodschap naar het programma gestuurd worden.
:li.:hp5.Maximaliseren venster:ehp5.
.br
Het venster zal gemaximaliseerd worden.
:li.:hp5.Verkleinen/Verbergen venster:ehp5.
.br
Het venster zal verkleind of verborgen worden, afhankelijk van het venstergedrag.
:li.:hp5.Herstellen venster:ehp5.
.br
Het venster zal hersteld worden naar de grootte die het had voor de verkleinen/verbergen/maximaliseer functie.
:li.:hp5.Schakelen bladerrichting:ehp5.
.br
De bladerrichting zal schakelen tussen verticaal en horizontaal.
:li.:hp5.Verplaats venster naar achtergrond:ehp5.
.br
Het venster onder de muisaanwijzer zal achter alle andere vensters op de werkplek verplaatst worden.
:li.:hp5.Key combination:ehp5.
.br
The key code of the key combination shown in the entry field will be sent to the application.
:li.:hp5.Geen actie:ehp5.
.br
Het indrukken van de knop zal geen actie veroorzaken.
:eul.

:h2 res=1501 id=button3.Knop 3
:p.De selectielijst besturing wordt gebruikt om de actie te selecteren die plaats vindt
bij het indrukken van muisknop 3.

:h2 res=1502 id=button4.Knop 4
:p.De selectielijst besturing wordt gebruikt om de actie te selecteren die plaats vindt
bij het indrukken van muisknop 4.

:h2 res=1503 id=button5.Knop 5
:p.De selectielijst besturing wordt gebruikt om de actie te selecteren die plaats vindt
bij het indrukken van muisknop 5.

:h2 res=1504 id=button6.Knop 6
:p.De selectielijst besturing wordt gebruikt om de actie te selecteren die plaats vindt
bij het indrukken van muisknop 6.

:h2 res=1505 id=button7.Knop 7
:p.De selectielijst besturing wordt gebruikt om de actie te selecteren die plaats vindt
bij het indrukken van muisknop 7.

:h2 res=1506 id=button8.Knop 8
:p.De selectielijst besturing wordt gebruikt om de actie te selecteren die plaats vindt
bij het indrukken van muisknop 8.

:h2 res=1507 id=button9.Knop 9
:p.De selectielijst besturing wordt gebruikt om de actie te selecteren die plaats vindt
bij het indrukken van muisknop 9.

:h2 res=1508 id=button10.Knop 10
:p.De selectielijst besturing wordt gebruikt om de actie te selecteren die plaats vindt
bij het indrukken van muisknop 10.

:h2 res=1511 id=cbutton3.Ctrl+Knop 3
:p.De selectielijst besturing wordt gebruikt om de actie te selecteren die plaats vindt
bij het indrukken van muisknop 3 tezamen met de Ctrl-toets op het toetsenbord.

:h2 res=1512 id=cbutton4.Ctrl+Knop 4
:p.De selectielijst besturing wordt gebruikt om de actie te selecteren die plaats vindt
bij het indrukken van muisknop 4 tezamen met de Ctrl-toets op het toetsenbord.

:h2 res=1513 id=cbutton5.Ctrl+Knop 5
:p.De selectielijst besturing wordt gebruikt om de actie te selecteren die plaats vindt
bij het indrukken van muisknop 5 tezamen met de Ctrl-toets op het toetsenbord.

:h2 res=1514 id=cbutton6.Ctrl+Knop 6
:p.De selectielijst besturing wordt gebruikt om de actie te selecteren die plaats vindt
bij het indrukken van muisknop 6 tezamen met de Ctrl-toets op het toetsenbord.

:h2 res=1515 id=cbutton7.Ctrl+Knop 7
:p.De selectielijst besturing wordt gebruikt om de actie te selecteren die plaats vindt
bij het indrukken van muisknop 7 tezamen met de Ctrl-toets op het toetsenbord.

:h2 res=1516 id=cbutton8.Ctrl+Knop 8
:p.De selectielijst besturing wordt gebruikt om de actie te selecteren die plaats vindt
bij het indrukken van muisknop 8 tezamen met de Ctrl-toets op het toetsenbord.

:h2 res=1517 id=cbutton9.Ctrl+Knop 9
:p.De selectielijst besturing wordt gebruikt om de actie te selecteren die plaats vindt
bij het indrukken van muisknop 9 tezamen met de Ctrl-toets op het toetsenbord.

:h2 res=1518 id=cbutton10.Ctrl+Knop 10
:p.De selectielijst besturing wordt gebruikt om de actie te selecteren die plaats vindt
bij het indrukken van muisknop 10 tezamen met de Ctrl-toets op het toetsenbord.

:h2 res=1521 id=abutton3.Alt+Knop 3
:p.De selectielijst besturing wordt gebruikt om de actie te selecteren die plaats vindt
bij het indrukken van muisknop 3 tezamen met de Alt-toets op het toetsenbord.

:h2 res=1522 id=abutton4.Alt+Knop 4
:p.De selectielijst besturing wordt gebruikt om de actie te selecteren die plaats vindt
bij het indrukken van muisknop 4 tezamen met de Alt-toets op het toetsenbord.

:h2 res=1523 id=abutton5.Alt+Knop 5
:p.De selectielijst besturing wordt gebruikt om de actie te selecteren die plaats vindt
bij het indrukken van muisknop 5 tezamen met de Alt-toets op het toetsenbord.

:h2 res=1524 id=abutton6.Alt+Knop 6
:p.De selectielijst besturing wordt gebruikt om de actie te selecteren die plaats vindt
bij het indrukken van muisknop 6 tezamen met de Alt-toets op het toetsenbord.

:h2 res=1525 id=abutton7.Alt+Knop 7
:p.De selectielijst besturing wordt gebruikt om de actie te selecteren die plaats vindt
bij het indrukken van muisknop 7 tezamen met de Alt-toets op het toetsenbord.

:h2 res=1526 id=abutton8.Alt+Knop 8
:p.De selectielijst besturing wordt gebruikt om de actie te selecteren die plaats vindt
bij het indrukken van muisknop 8 tezamen met de Alt-toets op het toetsenbord.

:h2 res=1527 id=abutton9.Alt+Knop 9
:p.De selectielijst besturing wordt gebruikt om de actie te selecteren die plaats vindt
bij het indrukken van muisknop 9 tezamen met de Alt-toets op het toetsenbord.

:h2 res=1528 id=abutton10.Alt+Knop 10
:p.De selectielijst besturing wordt gebruikt om de actie te selecteren die plaats vindt
bij het indrukken van muisknop 10 tezamen met de Alt-toets op het toetsenbord.

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

:h1 res=1700 id=keys2.Toetsen 2
:i1 id=keys2.Toetsen 2
:p.Deze pagina wordt gebruikt voor het bepalen van de acties voor de verschillende besturingen van de muis.
:p.De instellingen kunnen gedaan worden door selectie van de betreffende keuze op deze instellingenpagina.
:p.Er zal een uitgebreidere verklaring van elke besturing gegeven worden, als u op ‚‚n van de
onderwerpen in onderstaande lijst klikt&colon.
:ul compact.
:li.:link reftype=hd refid=dblclick_entry.Dubbel klikken op invoervelden:elink.
:li.:link reftype=hd refid=click_combo.Klikken op gecombineerde selectielijsten:elink.
:li.:link reftype=hd refid=smartcruise.SmartCruise:elink.
:li.:link reftype=hd refid=cancel.Beginwaarde:elink.
:li.:link reftype=hd refid=standard.Standaard:elink.
:eul.

:h2 res=1701 id=dblclick_entry.Dubbel klikken op invoervelden
:p.Als deze knop geselecteerd is, zal een dubbel klik in een invoerveld resulteren in de selectie van een volledig woord.

:h2 res=1702 id=click_combo.Klikken op gecombineerde selectielijsten
:p.Als deze knop geselecteerd is, zal een klik op het invoerveld deel van een gecombineerde selectielijst resulteren in het 
naar beneden klappen van het selectielijst deel.

:h2 res=1703 id=smartcruise.SmartCruise
:p.Dit activeert de SmartCruise mogelijkheid van Logitech MX500, MX700 en MX1000 muizen. Als dit
vinkje geactiveerd is, worden de instellingen voor knoppen 7, 8, 9 en 10 genegeerd. Met deze
mogelijkheid bladeren de knoppen 7 en 8 verticaal en 9 en 10 (indien aanwezig) horizontaal.

:h1 res=1100 id=devinfo.Apparaat informatie
:i1 id=devinfo.Apparaat informatie
:p.Deze pagina toont de soort en het versienummer van de programmatuur op de PC dat
gerelateerd is aan dit produkt.
:p.Verder wordt u ge‹nformeerd over het type muis dat gevonden is op uw systeem.
:note.
Voor veel muizen is het onmogelijk om het aantal knoppen correct te achterhalen. Aanvullend
ondersteunt de Presentation Manager maximaal maar drie knoppen. Dit is mogelijk de reden
waarom het aantal knoppen dat getoond wordt niet correct is, als de muis meer dan drie
heeft.

:h1 res=1300 id=wldevinfo.Apparaat informatie 2
:i1 id=wldevinfo.Apparaat informatie 2
:p.Deze pagina toont specifieke informatie voor draadloze muizen, als zij de raadpleging van deze gegevens ondersteunen.
:p.Het :hp5.Apparaat nummer:ehp5. is alleen interessant voor USB muizen en toont de apparaat index.
:p.Het :hp5.Kanaal nummer:ehp5. toont het gebruikte kanaal van muizen, die meerdere kanalen ondersteunen.
:p.De :hp5.Batterij status:ehp5. toont de huidige batterijlading.
:p.Er zal een uitgebreidere verklaring van elke besturing gegeven worden als u op ‚‚n
van de onderwerpen in de onderstaande lijst klikt&colon.
:ul compact.
:li.:link reftype=hd refid=battery_warning.Batterij waarschuwing:elink.
:eul.

:h2 res=1304 id=battery_warning.Batterij waarschuwing
:p.Als dit vinkje geselecteerd is, zal er een boodschap getoond worden als de batterij van uw muis bijna leeg is.

:h1 res=2500 id=timing.Timings
:i1 id=timing.Timings
:p.Deze dialoogpagina wordt gebruikt om een aantal timings van de muis in te stellen: de interne opvraagsnelheid
als ook de acceleratiewaarden.
 
:p.:hp5.Beschrijving van de acceleratie:ehp5.&colon. Voor elke muisgebeurtenis, wordt het aantal
fysiek verplaatste eenheden geteld en vergeleken met de eerste en tweede niveau grenswaarden. Als de
waarde groter is dan de tweede grenswaarde, zal de tweede niveau vermenigvuldiging gebruikt worden; als
de waarde groter is dan de eerste grenswaarde maar kleiner dan de tweede grenswaarde, zal de eerste niveau
vermenigvuldiging gebruikt worden. Als de waarde minder is dan de eerste grenswaarde, zal er geen vermenigvuldiging
gebruikt worden. Deze berekeningen worden apart gedaan voor de X- en Y-as.
De waarden worden als volgt berekend&colon.

:table cols='20 20' rules=both frame=box.
:row.
:c.Eerste grenswaarde
:c.schuifbalkwaarde
:row.
:c.Tweede grenswaarde
:c.schuifbalkwaarde * 7
:row.
:c.Eerste niveau vermenigvuldiging
:c.schuifbalkwaarde
:row.
:c.Tweede niveau vermenigvuldiging
:c.schuifbalkwaarde * 2
:etable.

:ul compact.
:li.:link reftype=hd refid=pollrate.Muis opvraagsnelheid:elink.
:li.:link reftype=hd refid=mouaccel_value.Acceleratiewaarde:elink.
:li.:link reftype=hd refid=mouaccel_threshold.Acceleratiegrenswaarde:elink.
:li.:link reftype=hd refid=cancel.Annuleren:elink.
:li.:link reftype=hd refid=standard.Standaard:elink.
:eul.

:h2 res=2501 id=pollrate.Muis opvraagsnelheid
:p.De schuifbalk bepaalt de interne opvraagsnelheid van de muis.

:h2 res=2502 id=mouaccel_value.Acceleratiewaarde
:p.De schuifbalk bepaalt de acceleratiewaarde.

:h2 res=2503 id=mouaccel_threshold.Acceleratiegrenswaarde
:p.De schuifbalk bepaalt de acceleratiegrenswaarde.

:euserdoc.
