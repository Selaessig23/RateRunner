# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mstracke <mstracke@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/09 13:50:36 by mstracke          #+#    #+#              #
#    Updated: 2025/11/09 15:26:12 by mstracke         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = RateRunner 
CXX = c++
CXXFLAGS =  -Wall -Werror -Wextra -std=c++98 -Isrc -Iinclude
# -MMD: Generate a .d file listing only your project headers (the ones you #include with quotes or via your -I paths), excluding system headers.
# -MP: Appends dummy rules for every dependency in the .d file. Prevents “No rule to make target …” errors if a header (or .tpp) gets deleted. 
DEPFLAGS =	-MMD -MP
# CXXFLAGS += -Wshadow 
# CXXFLAGS += -Wconversion -Wunreachable-code
# CXXFLAGS += -Wno-shadow
# CXXFLAGS += -pedantic
# -O0: Disables optimization to make debugging easier..
# CXXFLAGS += -g3 -O0

#libraries
#add pathes of lib to cflags to find headers easily
CPPFTLIB = cppftlib.a
CPPFTLIB_PATH = cppftlib
CPPFTLIB_LIBRARY = cppftlib/cppftlib.a
CPPFTLIB_CREATE = cppftlib.a
CXXFLAGS += -Icppftlib

#file to test the program
ARGS = "bitcoin_example_file.csv" "example_file_to_analyze.txt"

#sources
SRCS =	main.cpp \
		BitcoinExchange.cpp \
		utils.cpp

#variable substitution
OBJS = $(SRCS:%.cpp=obj/%.o)

# DEPS :=  deps.mk
# shouldn't I also integrate easyfind.tpp?
DEPS :=	$(OBJS:.o=.d)

#This target depends on $(NAME), making it the default target to build everything.
all:$(NAME)

$(NAME): $(CPPFTLIB_LIBRARY) $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(CPPFTLIB_LIBRARY)
		@echo "-- prog created, try it by using ./RateRunner <path_of_database> <path_of_infile_to_analyze>"

obj/%.o: src/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(DEPFLAGS) -c $< -o $@

#The -C option is used to change the directory to the specified path before executing make. In this context, it ensures that make operates in the subfolder, not the current directory.
#!important to note: if the program can't find any of the dependencies it will do all: always running libft-make (=updating correctly)
$(CPPFTLIB_LIBRARY): $(CPPFTLIB_CREATE)
	@$(MAKE) -C cppftlib

$(CPPFTLIB_CREATE):
#	@echo CREATE OR UPDATE LIBFT

# Include generated dependency files
-include $(DEPS)

clean:
	@rm -rf obj
	@make -C $(CPPFTLIB_PATH) clean
	@echo -- Deleting all .o and dependency-files

# fclean: this target depends on clean. Once all object files are deleted, this rule will delete the created executable / the compiled binary ('$(NAME)')
fclean: clean
	@rm -f $(NAME)
	@make -C $(CPPFTLIB_PATH) fclean
	@echo -- Deleting executables

#This target depends on fclean and all, effectively cleaning and rebuilding the project.
re: fclean all

run: all
	@echo
	@PATH=".$${PATH:+:$${PATH}}" && $(NAME) $(ARGS)

valrun: all
	@echo
	@PATH=".$${PATH:+:$${PATH}}" && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes $(NAME) $(ARGS)


#This line specifies that the listed targets (all, clean, fclean, re) are phony targets, meaning they don't represent actual files, and should always be considered out-of-date, triggering their recipes to be executed.
.PHONY: all clean fclean re force_deps
