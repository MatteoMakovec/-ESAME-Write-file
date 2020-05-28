#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <errno.h>



int main(int argc, char *argv[]) {

	char * file_name;
	char * text_to_write;
	int text_to_write_len;


	if (argc == 1) {
		printf("specificare come parametro il nome del file da creare e su cui scrivere\n");
		exit(EXIT_FAILURE);
	}

	file_name = argv[1];
	printf("scrivo nel file %s\n", file_name);

	int fd = open(file_name,
				  O_CREAT | O_TRUNC | O_WRONLY,
				  S_IRUSR | S_IWUSR // l'utente proprietario del file avrà i permessi di lettura e scrittura sul nuovo file
				 );
	if (fd == -1) { // errore!
		perror("open()");
		exit(EXIT_FAILURE);
	}

	text_to_write = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. At ultrices mi tempus imperdiet nulla malesuada pellentesque elit. Non enim praesent elementum facilisis leo vel fringilla est ullamcorper. Non quam lacus suspendisse faucibus interdum. Metus vulputate eu scelerisque felis imperdiet. At ultrices mi tempus imperdiet nulla malesuada pellentesque. At tempor commodo ullamcorper a lacus vestibulum. Consequat semper viverra nam libero justo laoreet sit amet. Facilisis magna etiam tempor orci eu. Convallis tellus id interdum velit laoreet id donec ultrices. Interdum velit euismod in pellentesque massa placerat duis ultricies. Senectus et netus et malesuada fames. Pharetra vel turpis nunc eget lorem dolor. Nisi porta lorem mollis aliquam ut porttitor leo a. Euismod elementum nisi quis eleifend quam adipiscing vitae proin.";

	text_to_write_len = strlen(text_to_write); // NON consideriamo lo '\0' finale

	printf("scrivo %d bytes\n", text_to_write_len);

	int res = write(fd, text_to_write, text_to_write_len);
	// write restituisce il numero di bytes che ha scritto
	// in caso di errore, restuisce -1

	if (res == -1) {
		perror("write()");
		exit(EXIT_FAILURE);
	}

	// close file

	if (close(fd) == -1) {
		perror("close");
		exit(EXIT_FAILURE);
	}

	printf("bye!\n");

	exit(EXIT_SUCCESS);
}
