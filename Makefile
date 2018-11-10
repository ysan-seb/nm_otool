# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysan-seb <ysan-seb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/17 07:19:36 by ysan-seb          #+#    #+#              #
#    Updated: 2018/11/10 16:37:25 by ysan-seb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NM_NAME = ft_nm

OTOOL_NAME = ft_otool

NM_SRC_PATH = ./nm/src/

OTOOL_SRC_PATH = ./otool/src/

LIB_MACHO_PATH = ./lib_macho/

NM_SRCS =		$(NM_SRC_PATH)main.c \
				$(NM_SRC_PATH)parse_opt.c \
				$(NM_SRC_PATH)nm.c \
				$(NM_SRC_PATH)handle_fat32.c \
				$(NM_SRC_PATH)handle_32.c \
				$(NM_SRC_PATH)handle_64.c \
				$(NM_SRC_PATH)handle_archive.c \
				$(NM_SRC_PATH)parse_section_32.c \
				$(NM_SRC_PATH)parse_section_64.c \
				$(NM_SRC_PATH)sort_32.c \
				$(NM_SRC_PATH)sort_ascii_32.c \
				$(NM_SRC_PATH)reverse_sort_ascii_32.c \
				$(NM_SRC_PATH)digit_sort_32.c \
				$(NM_SRC_PATH)reverse_digit_sort_32.c \
				$(NM_SRC_PATH)sort_64.c \
				$(NM_SRC_PATH)sort_ascii_64.c \
				$(NM_SRC_PATH)reverse_sort_ascii_64.c \
				$(NM_SRC_PATH)digit_sort_64.c \
				$(NM_SRC_PATH)reverse_digit_sort_64.c \
				$(NM_SRC_PATH)output_32.c \
				$(NM_SRC_PATH)output_64.c \
				$(NM_SRC_PATH)checkptr.c \
				$(LIB_MACHO_PATH)checkoff.c \
				$(LIB_MACHO_PATH)swap_bits_16.c \
				$(LIB_MACHO_PATH)swap_bits_32.c \
				$(LIB_MACHO_PATH)swap_bits_64.c \
				$(LIB_MACHO_PATH)swap_or_16.c \
				$(LIB_MACHO_PATH)swap_or_32.c \
				$(LIB_MACHO_PATH)swap_or_64.c \
				$(LIB_MACHO_PATH)get_mach_header_32.c \
				$(LIB_MACHO_PATH)get_mach_header_64.c \
				$(LIB_MACHO_PATH)get_symtab_command.c \
				$(LIB_MACHO_PATH)get_load_command.c \
				$(LIB_MACHO_PATH)get_segment_command_32.c \
				$(LIB_MACHO_PATH)get_segment_command_64.c \
				$(LIB_MACHO_PATH)get_section_32.c \
				$(LIB_MACHO_PATH)get_section_64.c \
				$(LIB_MACHO_PATH)get_fat_header.c \
				$(LIB_MACHO_PATH)get_fat_arch_32.c \

OTOOL_SRCS =	$(OTOOL_SRC_PATH)main.c \
				$(OTOOL_SRC_PATH)parse_opt.c \
				$(OTOOL_SRC_PATH)otool.c \
				$(OTOOL_SRC_PATH)handle_fat32.c \
				$(OTOOL_SRC_PATH)handle_32.c \
				$(OTOOL_SRC_PATH)handle_64.c \
				$(OTOOL_SRC_PATH)handle_archive.c \
				$(OTOOL_SRC_PATH)parse_segment_32.c \
				$(OTOOL_SRC_PATH)parse_segment_64.c \
				$(OTOOL_SRC_PATH)output_32.c \
				$(OTOOL_SRC_PATH)output_64.c \
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

NM_OBJS = $(NM_SRCS:.c=.o)

OTOOL_OBJS = $(OTOOL_SRCS:.c=.o)

CC = gcc

FLAGS = -Wall -Werror -Wextra -g

HEADER = -I./inc

LIBFT = ./libft/libft.a

RM = rm -rf

all	: lib $(NM_NAME) $(OTOOL_NAME)

lib	:
	@make -C libft/

$(NM_NAME):$(NM_OBJS)
	$(CC) $(FLAGS) -o $(NM_NAME) $(NM_OBJS) $(HEADER) $(LIBFT)

$(OTOOL_NAME):$(OTOOL_OBJS)
	$(CC) $(FLAGS) -o $(OTOOL_NAME) $(OTOOL_OBJS) $(HEADER) $(LIBFT)

%.o: %.c ./inc/lib_macho.h ./inc/libft.h ./inc/libftprintf.h ./inc/nm.h ./inc/otool.h
	gcc $(FLAGS) -o $@ -c  $< $(HEADER)

clean	:
	@make -C libft/ clean
	$(RM) $(NM_OBJS)
	$(RM) $(OTOOL_OBJS)

fclean: clean
	@make -C libft/ fclean
	$(RM) $(NM_NAME)
	$(RM) $(OTOOL_NAME)

re	:	fclean
	make

.PHONY: all lib clean fclean re
