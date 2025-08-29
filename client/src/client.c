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


	logger = iniciar_logger();
	config = iniciar_config("cliente.config");

	valor = config_get_string_value(config, "CLAVE");
	ip = config_get_string_value(config, "IP");
	puerto = config_get_string_value(config, "PUERTO");
	
	log_info(logger, "Hola! Soy un log\nCLAVE: %s\nIP: %s\nPUERTO: %s", valor, ip, puerto);
	conexion = crear_conexion(ip, puerto);
	leer_consola(logger);


	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/


	config_destroy(config);
	log_destroy(logger);
	// Enviamos al servidor el valor de CLAVE como mensaje

	// Armamos y enviamos el paquete
	paquete(conexion);

	//terminar_programa(conexion, logger, config);
	return 0;

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

void leer_consola(t_log* logger)
{
	char* leido;

		while ((leido = readline("> ")) != NULL){
		if(*leido == '\0'){
			free(leido);
			break;
		}
		log_info(logger, "Lei de consola: %s", leido);
		free(leido);
	}	
}

void paquete(int conexion)
{
    char* leido;
    t_paquete* paquete = crear_paquete();

    while ((leido = readline("> ")) != NULL) {
        if (*leido == '\0') {
            free(leido);
            break;
        }

        log_info(logger, "Lei de consola y agrego al paquete: %s", leido);
        agregar_a_paquete(paquete, leido, strlen(leido) + 1);

        free(leido);
    }

    enviar_paquete(paquete, conexion);
    eliminar_paquete(paquete);
}


void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config) 
	  con las funciones de las commons y del TP mencionadas en el enunciado */
}
