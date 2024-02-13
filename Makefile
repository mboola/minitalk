#------------------------------------------------------------------------------
#
#	$ Makefile $
#
#	Makefile to create a client and a server that will comunicate between
#	them using signals.
#
#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
#	NAME OF THE EXECUTABLES
#------------------------------------------------------------------------------
NAME	=	minitalk
SERVER	=	server
CLIENT	=	client

#------------------------------------------------------------------------------
#	MAIN DIRECTORIES
#------------------------------------------------------------------------------
SRC			=	src
INCLUDE		=	include
OBJ_DIR		=	objects

#------------------------------------------------------------------------------
#	STATIC LIBRARIES
#------------------------------------------------------------------------------
LIBFT_DIR		=	ft_libft
LIBFT			=	${LIBFT_DIR}/libft.a

#------------------------------------------------------------------------------
#	COMPILATION FLAGS
#------------------------------------------------------------------------------
CC				=	cc
CFLAGS			=	-Wall #-Wextra -Werror
HEADERS			=	-I./${INCLUDE}
OPTIMIZATION	=	#-O3
DEBUG			=	#-g

#------------------------------------------------------------------------------
#	LINKING LIBRARIES
#------------------------------------------------------------------------------
LIBFT_LINK		=	-L./${LIBFT_DIR} -lft

#------------------------------------------------------------------------------
#	FILES
#------------------------------------------------------------------------------
MINITALK_HEADER	=	${INCLUDE}/minitalk.h

SERVER_DIR	=	server
CLIENT_DIR	=	client
SERVER_SRC	=	server.c
CLIENT_SRC	=	client.c

#------------------------------------------------------------------------------
#	RULE TO GET THE .O COMPILED
#------------------------------------------------------------------------------
SERVER_FILES	=	${patsubst %.c,${OBJ_DIR}/%.o,${notdir ${SERVER_SRC}}}
CLIENT_FILES	=	${patsubst %.c,${OBJ_DIR}/%.o,${notdir ${CLIENT_SRC}}}

${OBJ_DIR}/%.o: ${SRC}/*/%.c Makefile
	$(CC) ${CFLAGS} ${HEADERS} ${OPTIMIZATION} -c $< -o $@ ${DEBUG}

#------------------------------------------------------------------------------
#	MAIN RULES TO COMPILE AND CREATE THE EXECUTABLE AND TO CLEAN IT
#------------------------------------------------------------------------------
all: ${OBJ_DIR} ${LIBFT} ${NAME}

${NAME}: ${SERVER} ${CLIENT}
	@echo "Compilating minitalk."

${SERVER}: ${SERVER_FILES}
	${CC} ${SERVER_FILES} ${LIBFT_LINK} -o $@ ${DEBUG}

${CLIENT}: ${CLIENT_FILES}
	${CC} ${CLIENT_FILES} ${LIBFT_LINK} -o $@ ${DEBUG}

${LIBFT}:
	@echo "Compilating libft."
	@make -C ${LIBFT_DIR}

clean:
	@make clean -C ${LIBFT_DIR}
	@rm -f ${OBJ_FILES}

fclean: clean
	@if [ -d ${OBJ_DIR} ]; \
	then \
        rm -rf ${OBJ_DIR}; \
    fi
	@make fclean -C ${LIBFT_DIR}
	@rm -f ${SERVER}
	@rm -f ${CLIENT}

re: fclean all

#------------------------------------------------------------------------------
#	RULES TO CREATE THE DIRECTORIES
#------------------------------------------------------------------------------
${OBJ_DIR}:
	@echo "Creating objects file directory."
	@mkdir -p $@

.PHONY: all clean fclean re

