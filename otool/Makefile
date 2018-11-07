# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/17 07:19:36 by ysan-seb          #+#    #+#              #
#    Updated: 2018/11/07 18:09:30 by ysan-seb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_otool

SRC_PATH = src/

LIB_MACHO_PATH = ../lib_macho/

LIB_PATH = lib/

SRCS =	$(SRC_PATH)main.c \
		$(SRC_PATH)otool.c \
		$(SRC_PATH)handle_fat32.c \
		$(SRC_PATH)handle_32.c \
		$(SRC_PATH)handle_64.c \
		$(SRC_PATH)handle_archive.c \
		$(SRC_PATH)parse_segment_32.c \
		$(SRC_PATH)parse_segment_64.c \
		$(SRC_PATH)output_32.c \
		$(SRC_PATH)output_64.c \
		$(LIB_MACHO_PATH)checkoff.c \
		$(LIB_MACHO_PATH)swap_bits_16.c \
		$(LIB_MACHO_PATH)swap_bits_32.c \
		$(LIB_MACHO_PATH)swap_bits_64.c \
		$(LIB_MACHO_PATH)swap_or_16.c \
		$(LIB_MACHO_PATH)swap_or_32.c \
		$(LIB_MACHO_PATH)swap_or_64.c \
		$(LIB_MACHO_PATH)get_mach_header_32.c \
		$(LIB_MACHO_PATH)get_mach_header_64.c \
		$(LIB_MACHO_PATH)get_load_command.c \
		$(LIB_MACHO_PATH)get_segment_command_32.c \
		$(LIB_MACHO_PATH)get_segment_command_64.c \
		$(LIB_MACHO_PATH)get_section_32.c \
		$(LIB_MACHO_PATH)get_section_64.c \
		$(LIB_MACHO_PATH)get_fat_header.c \
		$(LIB_MACHO_PATH)get_fat_arch_32.c \

OBJS = $(SRCS:.c=.o)

CC = gcc

FLAGS = -Wall -Werror -Wextra

HEADER = -I./inc

LIBFT = ./libft/libft.a

RM = rm -rf

all	: $(NAME)

$(NAME):$(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(HEADER)

%.o: %.c inc/otool.h
	gcc $(FLAGS) -o $@ -c  $< $(HEADER)

clean	:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re	:	fclean
	make

.PHONY: all lib clean fclean re
