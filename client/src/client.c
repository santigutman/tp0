#include "client.h"
#include <commons/config.h>
#include <commons/log.h>

t_log* iniciar_logger(void);
t_config* iniciar_config(char* path);


int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */

	logger = iniciar_logger();

	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"

	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config("client/cliente.config");

	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'
	valor = config_get_string_value(config, "CLAVE");
	ip = config_get_string_value(config, "IP");
	puerto = config_get_string_value(config, "PUERTO");


	// Loggeamos el valor de config
	log_info(logger, "Hola! Soy un log\nCLAVE: %s\nIP: %s\nPUERTO: %s", valor, ip, puerto);


	/* ---------------- LEER DE CONSOLA ---------------- */

	//leer_consola(logger);
	config_destroy(config);
	log_destroy(logger);
	return 0;
	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	// Enviamos al servidor el valor de CLAVE como mensaje

	// Armamos y enviamos el paquete
	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger = log_create("tp0.log", "TP0", 1, LOG_LEVEL_INFO);

	return nuevo_logger;
}

t_config* iniciar_config(char* path)
{
	t_config* nuevo_config = config_create(path);

	return nuevo_config;
}

t_paquete* leer_consola(t_log* logger)
{
	t_paquete* paquete = crear_paquete()
	char* leido;

	while ((leido = readline("> ")) != NULL){
		if(*leido == '\0'){
			free(leido);
			break;
		}
		log_info(logger, "Lei de consola: %s", leido);
		agregar_a_paquete(paquete, leido, 10)
		free(leido);
	}	
}

void paquete(int conexion)
{
	// Leemos y esta vez agregamos las lineas al paquete
	t_paquete* paqueteAEnviar = leer_consola()
	enviar_paquete(paqueteAEnviar, conexion)
	eliminar_paquete(paquete)
	
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */
}
