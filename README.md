# ProyectoSO

CONECTAR LAS MÁQUINAS EN RED:
- Abrir el VirtualBox.
- En la sección de RED de la máquina virtual tanto del PUBLISHER como del BROKER, elegir red "RED INTERNA" donde dice "Conectado a".
- Hacer lo mismo para las máquinas virtuales que van a trabajar.
- Ejecutar la máquina virtual del BROKER.
- Dentro de la máquina virtual de BROKER, se debe abrir la configuración de red y se debe dar clic en "Edit Connections".
- Se debe añadir el tipo de conexión ETHERNET o CABLEADA.
- Dar clic en EDIT y ponerle un nombre a la red.
- En la sección "IPv4 Settings" se debe agregar el método manual.
- En la lista de direcciones, se añade una nueva dirección que va a tener la dirección (ADRESS) "192.168.1.1"
	y un NETMASK de 255.255.255.0 ("192.168.1.2" cuando se esté haciendo lo mismo en la máquina del PUBLISHER).
- Para guardar y finalizar se da clic en SAVE.
- Dentro de la máquina virtual del PUBLISHER, realizar los mismos pasos con la única diferencia que la dirección
(ADRESS) en la lista de direcciones debe ser 192.168.1.2

MAKEFILE:
- Ejecutar el comando "make".
*Esto permite crear la librería estática donde están implementadas las funcionaliades de la estructura que
se ha utilizado para este proyecto (tabla hash), además de crear los archivos ejecutables de publisher y broker.
- En la máquina virtual del BROKER se debe ejecutar el comando "make broker".
- En la máquina virtual del PUBLISHER se debe ejecutar el comando "make publisher".

EJECUCIÓN:
- En la terminal del BROKER se debe ejecutar el comando ./broker
- En la terminal del PUBLISHER se debe ejecutar el comando ./publisher
- Finalmente, desde la máquina virtual del publisher se ingresa el texto que será leído por el broker,
	este texto será almacenado en la tabla hash y enviado a un subscriber si este está suscrito al topico creado por el PUBLISHER.
*El archivo de configuración tiene como información el número de puerto y el tamaño de la tabla hash.
