#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mstracke <mstracke@student.42berlin.d      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/13 13:00:58 by mstracke          #+#    #+#              #
#    Updated: 2025/09/08 14:47:29 by mstracke         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
#here are the declarations
CUR_DIR = $(shell pwd)
NAME = cppftlib.a
CXX = c++
CXXFLAGS = -Wall -Werror -Wextra -std=c++98 -Iinclude -Isrcs 
DEPFLAGS = -MMD -MP

#to create a program for testing reasons
#PROGRAM = test
#HEADERS = libft.h ft_printf/ft_printf.h get_next_line/get_next_line.h

SRCS = cppftlib_open.cpp \
       	cppftlib_convert_s2i.cpp \
	cppftlib_convert_s2f.cpp \
	cppftlib_convert_f2s.cpp

#variable substitution		
OBJS = $(SRCS:%.cpp=objs/%.o)

#create header dependencies for each o-file
DEPS := $(OBJS:.o=.d)

# here the rules start

#This target depends on $(NAME), making it the default target to build everything.
all: $(NAME)

#use of ar -rc or ar -rcs?
# compiles each source into an object file (c-flag); the The -I./ flag ensures that the compiler looks for header files in the current directory when compiling the source files specified in $(SRCS) (The -I. is included so that gcc will look in the current directory (.) for the include file .h ). -r  updates archive (replace or add files) or (c) create if it doesn't exist. -s could be useful for including an index
#ranlib creates and index which improves the efficiency of certain operations, such as quickly looking up symbols within the library.The index is stored in the archive itself.
$(NAME): $(OBJS) 
	ar -rcs $(NAME) $(OBJS) 
	ranlib $(NAME)
	@echo -- cppftlib compiled, lib created / updated

$(OBJS): objs/%.o : srcs/%.cpp
	@mkdir -p objs
	$(CXX) $(CXXFLAGS) $(DEPFLAGS) -c $< -o $@ && printf "Compiling: $(notdir $<)"

#to consider dependency-files
-include $(DEPS)

#clean: This target removes the object files ($(OFILES)).
#use rm -rf or rm -f? 
#r: This option allows rm to remove directories and their contents recursively, not necessary?
#f: "force" -->prevents the command from prompting for confirmation
clean: 
#	rm -f $(OBJS) $(OBJS_PRINTF) $(OBJS_GNL)
	@rm -rf objs 
	@echo -- Deleting all .o-files
	
# fclean: this target depends on clean. Once all object files are deleted, this rule will delete the created executable / the compiled binary ('$(NAME)') 
fclean: clean
	rm -f $(NAME)
#	@rm -f $(PROGRAM)


#This target depends on fclean and all, effectively cleaning and rebuilding the project.
re: fclean all

#This line specifies that the listed targets (all, clean, fclean, re) are phony targets, meaning they don't represent actual files, and should always be considered out-of-date, triggering their recipes to be executed.
.PHONY: all clean fclean re
