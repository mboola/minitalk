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
SERVER_BONUS	=	server_bonus
CLIENT_BONUS	=	client_bonus

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
CFLAGS			=	-Wall -Wextra -Werror
HEADERS			=	-I./${INCLUDE}
OPTIMIZATION	=	-O3
DEBUG			=	#-g
MMD				=	-MMD -MD

#------------------------------------------------------------------------------
#	LINKING LIBRARIES
#------------------------------------------------------------------------------
LIBFT_LINK		=	-L./${LIBFT_DIR} -lft

#------------------------------------------------------------------------------
#	FILES
#------------------------------------------------------------------------------
MINITALK_HEADER	=	${INCLUDE}/minitalk.h

SERVER_SRC	=	server.c
CLIENT_SRC	=	client.c
SERVER_SRC_BONUS	=	server_bonus.c
CLIENT_SRC_BONUS	=	client_bonus.c

#------------------------------------------------------------------------------
#	RULE TO GET THE .O COMPILED
#------------------------------------------------------------------------------
SERVER_FILES	=	${patsubst %.c,${OBJ_DIR}/%.o,${notdir ${SERVER_SRC}}}
CLIENT_FILES	=	${patsubst %.c,${OBJ_DIR}/%.o,${notdir ${CLIENT_SRC}}}
SERVER_FILES_BONUS	=	${patsubst %.c,${OBJ_DIR}/%.o,${notdir ${SERVER_SRC_BONUS}}}
CLIENT_FILES_BONUS	=	${patsubst %.c,${OBJ_DIR}/%.o,${notdir ${CLIENT_SRC_BONUS}}}

OBJ_FILES	=	${SERVER_FILES} ${CLIENT_FILES} ${SERVER_FILES_BONUS} ${CLIENT_FILES_BONUS}

${OBJ_DIR}/%.o: ${SRC}/*/%.c ${MINITALK_HEADER} Makefile
	$(CC) ${CFLAGS} ${HEADERS} ${OPTIMIZATION} -c $< -o $@ ${DEBUG}

#------------------------------------------------------------------------------
#	MAIN RULES TO COMPILE AND CREATE THE EXECUTABLE AND TO CLEAN IT
#------------------------------------------------------------------------------
all: make_libs ${OBJ_DIR} ${NAME}

make_libs:
	@make -C ${LIBFT_DIR}

${NAME}: ${SERVER} ${CLIENT}
	@echo "Compilating minitalk."

bonus: make_libs ${OBJ_DIR} ${SERVER_BONUS} ${CLIENT_BONUS}

${SERVER}: ${SERVER_FILES} ${LIBFT} 
	${CC} ${SERVER_FILES} ${LIBFT_LINK} -o $@ ${DEBUG}

${CLIENT}: ${CLIENT_FILES} ${LIBFT}
	${CC} ${CLIENT_FILES} ${LIBFT_LINK} -o $@ ${DEBUG}

${SERVER_BONUS}: ${SERVER_FILES_BONUS} ${LIBFT} 
	${CC} ${SERVER_FILES_BONUS} ${LIBFT_LINK} -o $@ ${DEBUG}

${CLIENT_BONUS}: ${CLIENT_FILES_BONUS} ${LIBFT} 
	${CC} ${CLIENT_FILES_BONUS} ${LIBFT_LINK} -o $@ ${DEBUG}

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
	@rm -f ${SERVER_BONUS}
	@rm -f ${CLIENT_BONUS}

re: fclean all

#------------------------------------------------------------------------------
#	RULES TO CREATE THE DIRECTORIES
#------------------------------------------------------------------------------
${OBJ_DIR}:
	@echo "Creating objects file directory."
	@mkdir -p $@

.PHONY: all clean fclean re bonus
