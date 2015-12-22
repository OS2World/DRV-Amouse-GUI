.************************************************
.*
.*   Copyright 2002-2006 nb software
.*
.*   Help for AMouse
.************************************************

:userdoc.

:h1 res=10 id=aboutMain.AMouse - Configuraci¢n avanzada del rat¢n
:i1 id=aboutMain.AMouse - Configuraci¢n avanzada del rat¢n
:p.:artwork name='C:\work\c\amouse\Language\Help\amouse.bmp' runin align=left.
Este programa se puede utilizar para configurar la rueda de un
"rat¢n con rueda" (p.ej. Intelli-Mouse). Puede&colon.

:ul compact.
:li.controlar la funci¢n de la rueda
:li.fijar el valor del avance en el desplazamiento con la rueda
:li.definir la funci¢n de los botones 3...5 del rat¢n
:eul.

:h1 res=1900 id=wheel1.Rueda 1/2/3
:i1 id=wheel1.Rueda 1/2/3
:p.En esta p gina se configuran las acciones del rat¢n iniciadas al mover la rueda.
Hay una p gina por cada combinaci¢n soportada de rueda + tecla especial.
:p.Encontrar s una explicaci¢n m s detallada de cada control, si pulsas sobre
uno de los elementos de la siguiente lista&colon.

:ul compact.
:li.:link reftype=hd refid=no_func.Sin funci¢n:elink.
:li.:link reftype=hd refid=msgscroll.Mensajes de desplazamiento:elink.
:li.:link reftype=hd refid=msgline.Mensajes de teclado:elink.
:li.:link reftype=hd refid=msgpage.Desplazar una p gina por unidad de desplazamiento:elink.
:li.:link reftype=hd refid=msgvol.Establecer volumen de audio:elink.
:li.:link reftype=hd refid=keyboard.Actuar sobre ventana activa:elink.
:li.:link reftype=hd refid=pointer.Actuar sobre ventana bajo cursor del rat¢n:elink.
:li.:link reftype=hd refid=scrollitem.Velocidad de la rueda:elink.
:li.:link reftype=hd refid=cancel.Deshacer:elink.
:li.:link reftype=hd refid=standard.Por omisi¢n:elink.
:eul.
:note.
Esta p gina s¢lo ser  visible si se detecta una rueda en el rat¢n.

:h2 res=1901 id=no_func.Modo de operaci¢n - Sin Funci¢n
:p.Si se activa este bot¢n el sistema ignorar  las pulsaciones
sobre la rueda.

:h2 res=1902 id=msgscroll.Modo de operaci¢n - Mensajes de desplazamiento
:p.Si se activa este bot¢n se env¡a un mensaje de desplazamiento
(WM_VSCROLL/WM_HSCROLL) a las ventanas de texto. Esto simula el
movimiento de la barra de desplazamiento.

:h2 res=1903 id=msgline.Modo de operaci¢n - Mensajes de teclado
:p.Si se activa este bot¢n se env¡a un mensaje WM_CHAR a las
ventanas de texto. Simula la pulsaci¢n de los cursores, si la
caracter¡stica est  soportada por la ventana.

:h2 res=1904 id=msgpage.Modo de operaci¢n - Desplazar una p gina por unidad de desplazamiento
:p.Si se activa este bot¢n se env¡a un mensaje WM_CHAR a las
ventanas de texto. Simula la pulsaci¢n de ReP g y AvP g, si la
caracter¡stica est  soportada por la ventana.

:h2 res=1905 id=msgvol.Modo de operaci¢n - Establecer volumen de audio
:p.Si se activa este bot¢n, el movimiento de la rueda establece el volumen del sistema multimedia.

:h2 res=1906 id=keyboard.Actuar sobre ventana activa
:p.Si se activa est  opci¢n, se mover  la barra de desplazamiento
vertical de la ventana activa.
:p.Con algunos ratones la ventana que est‚ bajo el cursor del rat¢n podr¡a
activarse al pulsar la rueda.
:note.
En algunas ventanas, las subventanas pueden contener barras de desplazamiento
(p.ej. en Netscape Communicator). En este caso se mueve la ventana seleccionada
en £ltimo lugar.

:h2 res=1907 id=pointer.Actuar sobre ventana bajo cursor del rat¢n
:p.Si se activa est  opci¢n, se mover  la barra de desplazamiento
vertical de la ventana situada bajo el cursor del rat¢n.
:note.
No importa si esta ventana es la activa en este momento, o, incluso, si
est  parcialmente oculta por otras ventanas.

:h2 res=1908 id=scrollitem.Velocidad de la rueda
:p.Con el :hp2.selector:ehp2. se fija el n£mero de l¡neas desplazadas
si la rueda se mueve un punto.

:h2 id=cancel.Deshacer
:p.Todos los par metros vuelven al valor que ten¡an antes del £ltimo cambio.

:h2 id=standard.Por omisi¢n
:p.Se establecen los valores por omisi¢n.

:h1 res=2100 id=wheel2.Rueda 4
:i1 id=wheel2.Wheel 4
:p.En esta p gina se configuran los valores iniciales del controlador, v lidos
en el inicio del PC.
:p.Las propiedades se establecen seleccionando el correspondiente bot¢n
en esta p gina.
:p.Encontrar s una explicaci¢n m s detallada de cada control, si pulsas sobre
alguno de los elementos de la siguiente lista&colon.
:ul compact.
:li.:link reftype=hd refid=scroll_vert.desplazamiento vertical:elink.
:li.:link reftype=hd refid=scroll_horz.desplazamiento horizontal:elink.
:li.:link reftype=hd refid=accel_delay.retardo en aceleraci¢n de la rueda:elink.
:li.:link reftype=hd refid=accel_value.velocidad de aceleraci¢n de la rueda:elink.
:li.:link reftype=hd refid=trackball.N£mero de ruedas:elink.
:li.:link reftype=hd refid=cancel.Deshacer:elink.
:li.:link reftype=hd refid=standard.Por omisi¢n:elink.
:eul.
:note.
Esta p gina s¢lo ser  visible si se detecta una rueda en el rat¢n.

:h2 res=2101 id=scroll_vert.Valores de inicio - desplazamiento vertical
:p.Si se activa esta opci¢n, mover la rueda de un rat¢n con s¢lo una
rueda realiza un desplazamiento vertical.

:h2 res=2102 id=scroll_horz.Valores de inicio - desplazamiento horizontal
:p.Si se activa esta opci¢n, mover la rueda de un rat¢n con s¢lo una
rueda realiza un desplazamiento horizontal.

:h2 res=2103 id=accel_delay.retardo en aceleraci¢n de la rueda (Tiempo de retardo)
:p.Si la rueda se desplaza m s r pido que el tiempo de retardo, el n£mero de l¡neas desplazadas se
incrementar  continuamente. El tiempo de retardo debe estar entre 100 y 2000 ms.

:h2 res=2104 id=accel_value.velocidad de aceleraci¢n de la rueda (Valor de aceleraci¢n)
:p.Este selector fija el n£mero utilizado para incrementar las unidades de desplazamiento,
si se mueve la rueda muy r pido.

:h2 res=2105 id=trackball.N£mero de ruedas
:p.Algunos ratones no son capaces de proporcionar al controlador su n£mero de ruedas o la existencia de un trackball.
En este caso es posible definir sus propiedades con este bot¢n.

:h1 res=2300 id=wheel3.Rueda 5
:i1 id=wheel3.Rueda 5
:p.La p gina :hp2.Rueda 5:ehp2. define excepciones del comportamiento de la rueda para algunas aplicaciones.
Si mueves la rueda del rat¢n se buscar , en la lista de esta p gina, una descripci¢n aceptable para la ventana / control.
Se buscar  la :hp2.Descripci¢n:ehp2. en la lista hasta que se encuentre una que coincida con la aplicaci¢n que este bajo el puntero del rat¢n.
Si no hay ninguna coincidencia, se toma la lista por omisi¢n de :hp2.AMouse:ehp2. (definida en :font facename=Courier size=14x14.AMouRes.rc:font facename=default.).
El texto descriptivo de la lista se utiliza para identificaci¢n por el usuario, por eso el nombre es arbitrario; incluso puede haber nombres duplicados.
:p.Las propiedades deben establecerse seleccionando el correspondiente bot¢n de esta p gina.
:p.Encontrar s una explicaci¢n m s detallada de cada control, si pulsas sobre
alguno de los elementos de la lista siguiente&colon.
:ul compact.
:li.:link reftype=hd refid=wheel_up.&uarrow.:elink.
:li.:link reftype=hd refid=wheel_down.&darrow.:elink.
:li.:link reftype=hd refid=wheel_delete.Suprimir:elink.
:li.:link reftype=hd refid=wheel_insert.Insertar:elink.
:li.:link reftype=hd refid=cancel.Cancelar:elink.
:eul.
:note.
Est  p gina s¢lo ser  visible si se ha detectado una rueda en el rat¢n.

:p.:hp7.Descripci¢n de los campos:ehp7.
:p.El comportamiento se muestra en la caja de abajo. La columna de la izquierda define la ventana / control,
al que afectar  el movimiento de la rueda. Los significados son&colon.
:ul compact.
:li.:hp2.Aplicaci¢n:ehp2.
.br
Nombre de la aplicaci¢n (p.ej. :font facename=Courier size=14x14.PROGRAMM.EXE:font facename=default.). 
Si este campo queda vac¡o el resultado de la comparaci¢n siempre ser  VERDADERO. Las clases del WPS siempre necesitan que este campo este vac¡o.
:li.:hp2.Clase:ehp2.
.br
Clase de ventana de la ventana / control. Aqu¡ se puede poner tanto el nombre de la clase (­sensible a may£sculas!)
como la id precedida de &osq.&numsign.&csq.. Si este campo queda vac¡o el resultado de la comparaci¢n siempre ser  VERDADERO.
:li.:hp2.Clase Padre:ehp2.
.br
Clase de ventana del padre de la ventana / control. Aqu¡ se puede poner tanto el nombre de la clase (­sensible a may£sculas!)
como la id precedida de &osq.&numsign.&csq.. Si este campo queda vac¡o el resultado de la comparaci¢n siempre ser  VERDADERO.
:li.:hp2.Opci¢n:ehp2.
.br
Aqu¡ se encontrar  una opci¢n (la descripci¢n se ver  all¡), si es necesaria para una &osq.vRelaci¢n&csq. o &osq.hRelaci¢n&csq. espec¡fica.
En todos los dem s casos este campo permanece vac¡o.
:eul.
:p.La columna de la derecha define la acci¢n iniciada por la rueda. Los significados son&colon.
:ul compact.
:li.:hp2.Modo:ehp2.
.br
Define el tipo de mensaje enviado a la ventana / control.
Se utilizar  :hp2.Desplazamiento:ehp2., si en la p gina
:link reftype=hd refid=wheel1.Rueda 1:elink. se ha seleccionado el
modo de operaci¢n :link reftype=hd refid=msgscroll.mensajes de desplazamiento:elink..
:hp2.Cursor:ehp2. funciona con
:link reftype=hd refid=msgline.mensajes de teclado:elink.,
:hp2.P gina:ehp2. en
:link reftype=hd refid=msgpage.Desplazar una p gina por unidad de desplazamiento:elink..
:hp2.Desplazamiento o Cursor:ehp2. reacciona, si el modo de operaci¢n seleccionado es tanto
:link reftype=hd refid=msgscroll.mensajes de desplazamiento:elink. como
:link reftype=hd refid=msgline.mensajes de teclado:elink..
:hp2.Todo:ehp2. reacciona en todas las propiedades.
:li.:hp2.vRelaci¢n resp. hRelaci¢n:ehp2.
.br
Define si el mensaje se env¡a directamente a la ventana / control, o si la siguente b£squeda ha de hacerse
en la jerarqu¡a de la ventana. Los significados son&colon.
:ul compact.
:li.:hp2.Ninguno:ehp2.&colon. El mensaje se enviar  directamente al control encontrado.
:li.:hp2.Padre:ehp2.&colon. Se busca un padre aceptable en la lista de descripciones.
:li.:hp2.Propietario:ehp2.&colon. Se busca un propietario aceptable en la lista de descripciones.
:li.:hp2.Siguiente:ehp2.&colon. La b£squeda se continuar  en el z-orden de los controles que est‚n
bajo el puntero del rat¢n.
:li.:hp2.Siguiente CB:ehp2.&colon. S¢lo se utiliza en cajas Combo. B sicamente realiza lo mismo que :hp2.Siguiente:ehp2.,
pero maneja el  rea invisible sobre el campo de entrada si la caja de listas no se est  mostrando.
:li.:hp2.Hermano[Opci¢n]:ehp2.&colon. Se buscar  una ventana hermana en la lista de descripciones con un nombre de clase
definido en el campo :hp2.opci¢n:ehp2..
:eul.
:li.:hp2.vOpci¢n / hOpci¢n:ehp2.
.br
Contiene una opci¢n dependiendo del tipo de mensaje establecido. Consulta all¡.
:li.:hp2.Arriba / Abajo bzw. Izq. / Dcha.:ehp2.
.br
Define el mensaje enviado a la ventana / control. Est n disponibles los siguientes mensajes&colon.
:ul compact.
:li.:hp2.WM_NULL:ehp2.&colon. No se enviar  ning£n mensaje. Normalmente, se utiliza
cuando se ha establecido el atributo :hp2.Ninguno:ehp2. en :hp2.vRelaci¢n:ehp2./:hp2.hRelaci¢n:ehp2..
:li.:hp2.WM_CONTROL:ehp2.&colon. Se env¡a un c¢digo de teclado directamente al controlador de teclado.
Son posibles las siguientes opciones&colon.
:ul compact.
:li.:hp2.p gina:ehp2.&colon. Se env¡an los c¢digos de teclado para las teclas Rep g-/Avp g.
:li.:hp2.cursor arriba/abajo:ehp2.&colon. Se env¡an los c¢digos de teclado para las teclas de cursor Arriba-/Abajo.
:li.:hp2.cursor izquierda/derecha:ehp2.&colon. Se env¡an los c¢digos de teclado para las teclas de cursor Izquierda-/Derecha.
:li.:hp2.mult cursor arriba/abajo:ehp2.&colon. Se env¡an los c¢digos de teclado para las teclas de cursor Arriba-/Abajo.
El n£mero de mensajes enviados se especifica en la propiedad :link reftype=hd refid=scrollitem.Velocidad de la rueda:elink..
:li.:hp2.mult cursor izquierda/derechat:ehp2.&colon. Se env¡an los c¢digos de teclado para las teclas de cursor Izquierda-/Derecha.
El n£mero de mensajes enviados se especifica en la propiedad :link reftype=hd refid=scrollitem.Velocidad de la rueda:elink..
:eul.
:li.:hp2.WM_VSCROLL:ehp2.&colon. Se env¡a un mensaje de desplazamiento vertical  a la barra de desplazamiento vertical.
:li.:hp2.WM_HSCROLL:ehp2.&colon. Se env¡a un mensaje de desplazamiento horizontal a la barra de desplazamiento horizontal.
:li.:hp2.N x WM_VSCROLL:ehp2.&colon. Como :hp2.WM_VSCROLL:ehp2., pero el n£mero de mensajes queda definido por
la propiedad :link reftype=hd refid=scrollitem.Velocidad de la rueda:elink..
:li.:hp2.N x WM_HSCROLL:ehp2.&colon. Como :hp2.WM_HSCROLL:ehp2., pero el n£mero de mensajes queda definido por
la propiedad :link reftype=hd refid=scrollitem.Velocidad de la rueda:elink..
:li.:hp2.WM_CHAR:ehp2.&colon. Se env¡a un mensaje de car cter. Son posibles las mismas opciones que para
:hp2.WM_CONTROL:ehp2..
:eul.
:eul.

:p.:hp7.Ejemplos:ehp7.
:p.Debido a un error en versiones antiguas de Mozilla (versi¢n 1.3 y anteriores) el desplazamiento horizontal con mensajes normales de WM_SCROLL
no funciona. Una manera de solucionar esto podr¡a ser introducir las dos siguientes opciones.
:p.:artwork name='C:\work\c\amouse\Language\Help\Mozilla_Line_034.bmp' align=left.
:p.Esta entrada act£a, si en la p gina :link reftype=hd refid=wheel1.Rueda 1:elink. se ha seleccionado el
modo de operaci¢n :hp2.mensajes de desplazamiento:ehp2. o :hp2.mensajes de teclado:ehp2..
En este caso los mensajes de tecla de cursor horizontal y vertical se env¡an al padre.
(&odq.mult cursor&cdq.). Mozilla es identificado, si tanto :hp2.Clase:ehp2. como
:hp2.Clase padre:ehp2. son del tipo :hp2.MozillaWindowClass:ehp2..
:p.:artwork name='C:\work\c\amouse\Language\Help\Mozilla_Page_034.bmp' align=left.
:p.Para desplazamientos de una p gina (:hp2.Modo = P gina:ehp2.) se env¡a un mensaje de car cter Rep g/Avp g en caso de desplazamiento vertical.
:p.:artwork name='C:\work\c\amouse\Language\Help\Command_Line_034.bmp' align=left.
:p.Si mueves la rueda sobre una ventana de indicador de mandatos, el comportamiento por omisi¢n es desplazar los contenidos de la ventana (si 
hay barras de desplazamiento presentes).
Las propiedades mostradas arriba hacen que en su lugar que se desplace el historial de comandos.

:h2 res=2313 id=wheel_up.&uarrow. (Mover entrada hacia arriba)
:p.Mueve la entrada seleccionada en la lista de entradas una posici¢n hacia arriba.

:h2 res=2314 id=wheel_down.&darrow. (Mover entrada hacia abajo)
:p.Mueve la entrada seleccionada en la lista de entradas una posici¢n hacia abajo.

:h2 res=2316 id=wheel_delete.Suprimir
:p.Suprime la entrada seleccionada en la lista para este bot¢n.

:h2 res=2315 id=wheel_insert.Insertar
:p.Inserta una nueva entrada en la lista para este bot¢n.

:h1 res=2700 id=insertappl.Insertar Aplicaci¢n
:i1 id=insertappl.Insertar Aplicaci¢n
:p.Este di logo se utiliza para insertar una nueva definici¢n del comportamiento de la rueda para una aplicaci¢n seleccionada.
El significado de los controles corresponde con la descripci¢n en 
:link reftype=hd refid=wheel3.Rueda 5:elink.. La :hp2.Descripci¢n:ehp2. su puede utilizar para insertar
cualquier texto definido por el usuario que identifique las entradas en la lista de
:link reftype=hd refid=wheel3.Rueda 5:elink..

:h1 res=1500 id=keys1.Teclas 1
:i1 id=keys.Teclas 1
:p.En esta p gina se definen las acciones para los botones 3, 4 y 5 del rat¢n.
:p.Las propiedades se establecen seleccionando la respectiva elecci¢n en esta p gina.
:p.Encontrar s una explicaci¢n m s detallada de cada control, si pulsas sobre
alguno de los elementos de la siguiente lista&colon.
:ul compact.
:li.:link reftype=hd refid=button3.Bot¢n 3:elink.
:li.:link reftype=hd refid=button4.Bot¢n 4:elink.
:li.:link reftype=hd refid=button5.Bot¢n 5:elink.
:li.:link reftype=hd refid=button6.Bot¢n 6:elink.
:li.:link reftype=hd refid=button7.Bot¢n 7:elink.
:li.:link reftype=hd refid=button8.Bot¢n 8:elink.
:li.:link reftype=hd refid=button9.Bot¢n 9:elink.
:li.:link reftype=hd refid=button10.Bot¢n 10:elink.
:li.:link reftype=hd refid=cbutton3.Ctrl+Bot¢n 3:elink.
:li.:link reftype=hd refid=cbutton4.Ctrl+Bot¢n 4:elink.
:li.:link reftype=hd refid=cbutton5.Ctrl+Bot¢n 5:elink.
:li.:link reftype=hd refid=cbutton6.Ctrl+Bot¢n 6:elink.
:li.:link reftype=hd refid=cbutton7.Ctrl+Bot¢n 7:elink.
:li.:link reftype=hd refid=cbutton8.Ctrl+Bot¢n 8:elink.
:li.:link reftype=hd refid=cbutton9.Ctrl+Bot¢n 9:elink.
:li.:link reftype=hd refid=cbutton10.Ctrl+Bot¢n 10:elink.
:li.:link reftype=hd refid=abutton3.Alt+Bot¢n 3:elink.
:li.:link reftype=hd refid=abutton4.Alt+Bot¢n 4:elink.
:li.:link reftype=hd refid=abutton5.Alt+Bot¢n 5:elink.
:li.:link reftype=hd refid=abutton6.Alt+Bot¢n 6:elink.
:li.:link reftype=hd refid=abutton7.Alt+Bot¢n 7:elink.
:li.:link reftype=hd refid=abutton8.Alt+Bot¢n 8:elink.
:li.:link reftype=hd refid=abutton9.Alt+Bot¢n 9:elink.
:li.:link reftype=hd refid=abutton10.Alt+Bot¢n 10:elink.
:li.:link reftype=hd refid=keycombset3.Set 3:elink.
:li.:link reftype=hd refid=keycombset4.Set 4:elink.
:li.:link reftype=hd refid=keycombset5.Set 5:elink.
:li.:link reftype=hd refid=keycombset6.Set 6:elink.
:li.:link reftype=hd refid=keycombset7.Set 7:elink.
:li.:link reftype=hd refid=keycombset8.Set 8:elink.
:li.:link reftype=hd refid=keycombset9.Set 9:elink.
:li.:link reftype=hd refid=keycombset10.Set 10:elink.
:li.:link reftype=hd refid=keycomb.Key combination:elink.
:li.:link reftype=hd refid=cancel.Cancelar:elink.
:li.:link reftype=hd refid=standard.Por omisi¢n:elink.
:eul.
:note.
Esta p gina s¢lo ser  visible si se detecta una rueda en el rat¢n.

:p.:hp2.Funciones de los botones:ehp2.
:p.Est n disponibles las siguiente funciones&colon.

:ul.
:li.:hp5.Cortar:ehp5.
.br
Se realizar  la funci¢n de "Cortar" al portapapeles (Mays-Supr)
:li.:hp5.Copiar:ehp5.
.br
Se realizar  la funci¢n de "Copiar" al portapapeles  (Ctrl-Ins)
:li.:hp5.Pegar:ehp5.
.br
Se realizar  la funci¢n de "Pegar" del portapapeles (Mays-Ins)
:li.:hp5.Bot¢n central:ehp5.
.br
EL bot¢n seleccionado se comportar  como el tercer bot¢n de un rat¢n. El estado
de las teclas de may£sculas del teclado se preserva y maneja correctamente.
:li.:hp5.Minimizar/Ocultar todas las ventanas:ehp5.
.br
Se minimizar n u ocultar n todas las ventanas, dependiendo de su comportamiento.
:li.:hp5.Restaurar todas las ventanas:ehp5.
.br
Se restaurar n todas las ventanas a su tama¤o anterior a la funci¢n minimizar/ocultar/maximizar.
:li.:hp5.Lista de ventanas:ehp5.
.br
Se muestra la Lista de ventanas
:li.:hp5.Cerrar aplicaci¢n:ehp5. 
.br
Se cerrar  la aplicaci¢n.
:li.:hp5.Doble click:ehp5.
.br
Se env¡a a la aplicaci¢n un mensaje de doble click.
:li.:hp5.Maximizar ventana:ehp5.
.br
Se maximizar  la ventana.
:li.:hp5.Minimizar/Ocultar ventana:ehp5.
.br
Se minimizar  u ocultar  la ventana, dependiendo de su comportamiento.
:li.:hp5.Restaurar ventana:ehp5.
.br
Se restaurar  la ventana a su tama¤o anterior a la funci¢n minimizar/ocultar/maximizar.
:li.:hp5.Alternar direcci¢n de desplazamiento:ehp5.
.br
La direcci¢n del desplazamiento se alternar  entre vertical y horizontal.
:li.:hp5.Colocar ventana al fondo:ehp5.
.br
La ventana sobre la que est‚ el cursor se desplazar  detr s de todas las otras
ventanas del escritorio.
:li.:hp5.Key combination:ehp5.
.br
The key code of the key combination shown in the entry field will be sent to the application.
:li.:hp5.Ninguna acci¢n:ehp5.
.br
Pulsar el bot¢n no origina ninguna acci¢n.
:eul.

:h2 res=1501 id=button3.Bot¢n 3
:p.Esta combinaci¢n de controles se utiliza para seleccionar la acci¢n a realizar
cuando se pulsa el bot¢n 3 del rat¢n.

:h2 res=1502 id=button4.Bot¢n 4
:p.Esta combinaci¢n de controles se utiliza para seleccionar la acci¢n a realizar
cuando se pulsa el bot¢n 4 del rat¢n.

:h2 res=1503 id=button5.Bot¢n 5
:p.Esta combinaci¢n de controles se utiliza para seleccionar la acci¢n a realizar
cuando se pulsa el bot¢n 5 del rat¢n.

:h2 res=1504 id=button6.Bot¢n 6
:p.Esta combinaci¢n de controles se utiliza para seleccionar la acci¢n a realizar
cuando se pulsa el bot¢n 6 del rat¢n.

:h2 res=1505 id=button7.Bot¢n 7
:p.Esta combinaci¢n de controles se utiliza para seleccionar la acci¢n a realizar
cuando se pulsa el bot¢n 7 del rat¢n.

:h2 res=1506 id=button8.Bot¢n 8
:p.Esta combinaci¢n de controles se utiliza para seleccionar la acci¢n a realizar
cuando se pulsa el bot¢n 8 del rat¢n.

:h2 res=1507 id=button9.Bot¢n 9
:p.Esta combinaci¢n de controles se utiliza para seleccionar la acci¢n a realizar
cuando se pulsa el bot¢n 9 del rat¢n.

:h2 res=1508 id=button10.Bot¢n 10
:p.Esta combinaci¢n de controles se utiliza para seleccionar la acci¢n a realizar
cuando se pulsa el bot¢n 10 del rat¢n.

:h2 res=1511 id=cbutton3.Ctrl+Bot¢n 3
:p.Esta combinaci¢n de controles se utiliza para seleccionar la acci¢n a realizar
cuando se pulsa el bot¢n 3 del rat¢n junto a la tecla Ctrl.

:h2 res=1512 id=cbutton4.Ctrl+Bot¢n 4
:p.Esta combinaci¢n de controles se utiliza para seleccionar la acci¢n a realizar
cuando se pulsa el bot¢n 4 del rat¢n junto a la tecla Ctrl.

:h2 res=1513 id=cbutton5.Ctrl+Bot¢n 5
:p.Esta combinaci¢n de controles se utiliza para seleccionar la acci¢n a realizar
cuando se pulsa el bot¢n 5 del rat¢n junto a la tecla Ctrl.

:h2 res=1514 id=cbutton6.Ctrl+Bot¢n 6
:p.Esta combinaci¢n de controles se utiliza para seleccionar la acci¢n a realizar
cuando se pulsa el bot¢n 6 del rat¢n junto a la tecla Ctrl.

:h2 res=1515 id=cbutton7.Ctrl+Bot¢n 7
:p.Esta combinaci¢n de controles se utiliza para seleccionar la acci¢n a realizar
cuando se pulsa el bot¢n 7 del rat¢n junto a la tecla Ctrl.

:h2 res=1516 id=cbutton8.Ctrl+Bot¢n 8
:p.Esta combinaci¢n de controles se utiliza para seleccionar la acci¢n a realizar
cuando se pulsa el bot¢n 8 del rat¢n junto a la tecla Ctrl.

:h2 res=1517 id=cbutton9.Ctrl+Bot¢n 9
:p.Esta combinaci¢n de controles se utiliza para seleccionar la acci¢n a realizar
cuando se pulsa el bot¢n 9 del rat¢n junto a la tecla Ctrl.

:h2 res=1518 id=cbutton10.Ctrl+Bot¢n 10
:p.Esta combinaci¢n de controles se utiliza para seleccionar la acci¢n a realizar
cuando se pulsa el bot¢n 10 del rat¢n junto a la tecla Ctrl.

:h2 res=1521 id=abutton3.Alt+Bot¢n 3
:p.Esta combinaci¢n de controles se utiliza para seleccionar la acci¢n a realizar
cuando se pulsa el bot¢n 3 del rat¢n junto a la tecla Alt.

:h2 res=1522 id=abutton4.Alt+Bot¢n 4
:p.Esta combinaci¢n de controles se utiliza para seleccionar la acci¢n a realizar
cuando se pulsa el bot¢n 4 del rat¢n junto a la tecla Alt.

:h2 res=1523 id=abutton5.Alt+Bot¢n 5
:p.Esta combinaci¢n de controles se utiliza para seleccionar la acci¢n a realizar
cuando se pulsa el bot¢n 5 del rat¢n junto a la tecla Alt.

:h2 res=1524 id=abutton6.Alt+Bot¢n 6
:p.Esta combinaci¢n de controles se utiliza para seleccionar la acci¢n a realizar
cuando se pulsa el bot¢n 6 del rat¢n junto a la tecla Alt.

:h2 res=1525 id=abutton7.Alt+Bot¢n 7
:p.Esta combinaci¢n de controles se utiliza para seleccionar la acci¢n a realizar
cuando se pulsa el bot¢n 7 del rat¢n junto a la tecla Alt.

:h2 res=1526 id=abutton8.Alt+Bot¢n 8
:p.Esta combinaci¢n de controles se utiliza para seleccionar la acci¢n a realizar
cuando se pulsa el bot¢n 8 del rat¢n junto a la tecla Alt.

:h2 res=1527 id=abutton9.Alt+Bot¢n 9
:p.Esta combinaci¢n de controles se utiliza para seleccionar la acci¢n a realizar
cuando se pulsa el bot¢n 9 del rat¢n junto a la tecla Alt.

:h2 res=1528 id=abutton10.Alt+Bot¢n 10
:p.Esta combinaci¢n de controles se utiliza para seleccionar la acci¢n a realizar
cuando se pulsa el bot¢n 10 del rat¢n junto a la tecla Alt.

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

:h1 res=1700 id=keys2.Teclas 2
:i1 id=keys2.Keys 2
:p.En esta p gina se define el comportamiento de varios controles a acciones del rat¢n.
:p.Las propiedades se deben establecer seleccionando la correspondiente elecci¢n en esta p gina.
:p.Encontrar s una explicaci¢n m s detallada de cada control pulsando
sobre los elementos de la siguiente lista&colon.
:ul compact.
:li.:link reftype=hd refid=dblclick_entry.Doble click sobre campos de entrada:elink.
:li.:link reftype=hd refid=click_combo.Click sobre cajas combo:elink.
:li.:link reftype=hd refid=smartcruise.SmartCruise:elink.
:li.:link reftype=hd refid=cancel.Deshacer:elink.
:li.:link reftype=hd refid=standard.Est ndar:elink.
:eul.

:h2 res=1701 id=dblclick_entry.Doble click sobre campos de entrada
:p.Si seleccionas este bot¢n, al realizar una doble pulsaci¢n con el rat¢n sobre un campo
de entrada, se seleccionar  una palabra completa.

:h2 res=1702 id=click_combo.Click sobre cajas combo
:p.Si este bot¢n est  seleccionado, cuando pulses con el rat¢n sobre el campo de entrada de una
caja combo, se abrir  la lista desplegable de dicha caja.

:h2 res=1703 id=smartcruise.SmartCruise
:p.Esto habilita la funci¢n SmartCruise de los ratones Logitech MX500, MX700 and MX1000. Si est  casilla
esta activada, se ignoran las propiedades para los botones 7, 8, 9 y 10. Con esta funci¢n, los botones 7 y 8
desplazan verticalmente, los botones 9 y 10 (si los hay) desplazan horizontalmente.

:h1 res=1100 id=devinfo.Informaci¢n del dispositivo
:i1 id=devinfo.Informaci¢n del dispositivo
:p.Est  p gina muestra el tipo y n£mero de versi¢n del software del PC relativo
a este producto.
:p.Adem s se informa del tipo de rat¢n detectado por el sistema.
:note.
Para muchos ratones es imposible detectar el n£mero de botones correctamente. Adem s,
el Presentation Manager s¢lo soporta 3 botones como m ximo. Esta es la raz¢n por la
que posiblemente el n£mero de botones mostrado pueda ser incorrecto, si el rat¢n
tiene m s de 3.

:h1 res=1300 id=wldevinfo.Informaci¢n del dispositivo 2
:i1 id=wldevinfo.Informaci¢n del dispositivo 2
:p.Esta p gina muestra informaci¢n espec¡fica para ratones sin cable, si soportan mostrar estos datos.
:p.El :hp5.N£mero de dispositivo:ehp5., s¢lo interesa para ratones USB y muestra el ¡ndice del dispositivo.
:p.El :hp5.N£mero de canal:ehp5. muestra el canal usado con el rat¢n, que soporte multiples canales.
:p.El :hp5.Estabo de la bater¡a:ehp5. muestra el estado actual de carga de la bater¡a.
:p.Pulse sobre cada uno de los elementos de la lista de abajo, para obtener una 
explicaci¢n m s detallada&colon.
:ul compact.
:li.:link reftype=hd refid=battery_warning.Aviso de bater¡a:elink.
:eul.

:h2 res=1304 id=battery_warning.Aviso de bater¡a
:p.Si activa esta casilla se mostrar  una ventana emergente si  la bater¡a de su rat¢n est  casi vac¡a.

:h1 res=2500 id=timing.Tiempos
:i1 id=timing.Tiempos
:p.En este di logo se establecen diversos tiempos del rat¢n: tanto el ratio interno de sondeo
como los valores de aceleraci¢n.
 
:p.:hp5.Descripci¢n de la aceleraci¢n:ehp5.&colon. Para cada evento del rat¢n,
la cuenta de unidades f¡sicas movidas se compara contra los umbrales de primer
y segundo nivel. Si la cuenta es superior al umbral del segundo nivel se utilizar 
el multiplicador del segundo nivel; si la cuenta es superior al primer nivel pero
inferior al segundo se utilizar  el multiplicador del primer nivel. Si la cuenta es
inferior al umbral del primer nivel no se utilizar  multiplicador. Estos c lculos se
hacen para los ejes X e Y independientemente.
Los valores se calculan de la siguiente manera&colon.

:table cols='20 20' rules=both frame=box.
:row.
:c.umbral del primer nivel
:c.valor del selector
:row.
:c.umbral del segundo nivel
:c.valor del selector * 7
:row.
:c.multiplicador del primer nivel
:c.valor del selector
:row.
:c.multiplicador del segundo nivel
:c.valor del selector * 2
:etable.

:ul compact.
:li.:link reftype=hd refid=pollrate.Ratio de sondeo del rat¢n:elink.
:li.:link reftype=hd refid=mouaccel_value.Valor de aceleraci¢n:elink.
:li.:link reftype=hd refid=mouaccel_threshold.Umbral de aceleraci¢n:elink.
:li.:link reftype=hd refid=cancel.Cancelar:elink.
:li.:link reftype=hd refid=standard.Por omisi¢n:elink.
:eul.

:h2 res=2501 id=pollrate.Ratio de sondeo del rat¢n
:p.El selector define el ratio interno de sondeo del rat¢n.

:h2 res=2502 id=mouaccel_value.Valor de aceleraci¢n
:p.El selector define el valor de aceleraci¢n.

:h2 res=2503 id=mouaccel_threshold.Umbral de aceleraci¢n
:p.El selector define el umbral de aceleraci¢n.

:euserdoc.
