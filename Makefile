# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dcaetano <dcaetano@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/09 13:31:50 by dcaetano          #+#    #+#              #
#    Updated: 2026/01/12 11:40:53 by dcaetano         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# === COMMANDS =============================================================== #

CPP          = c++
MK           = mkdir
RM           = rm
AR_RCS       = ar rcs

# === DIRECTORIES ============================================================ #

INCS_D       = includes
SRCS_D       = srcs
OBJS_D       = objs
MAND_D       = mandatory
BNUS_D       = bonus

# === EXTENSIONS ============================================================= #

CPP_EXT      = .cpp
HPP_EXT      = .hpp
OBJ_EXT      = .o

# === FILES ================================================================== #

CLSS         = Computor
CPPS         = $(CLSS)
HDRS         = $(CLSS) ft_$(NAME)
CLSS_B       = Computor
CPPS_B       = $(CLSS_B)
HDRS_B       = $(CLSS_B) ft_$(NAME)

ifeq ($(MAKECMDGOALS),bonus)
    INCS     = $(addprefix $(BNUS_D)/$(INCS_D)/, \
                           $(addsuffix $(HPP_EXT), \
                                       $(HDRS_B)))
    SRCS     = $(addprefix $(BNUS_D)/$(SRCS_D)/, \
                           $(addsuffix $(CPP_EXT), \
                                       $(CPPS_B)))
    OBJS     = $(patsubst $(BNUS_D)/$(SRCS_D)/%$(CPP_EXT), \
                          $(OBJS_D)/$(BNUS_D)/$(SRCS_D)/%$(OBJ_EXT), \
                          $(SRCS))
    MAIN_CPP = bonus$(CPP_EXT)
else
    INCS     = $(addprefix $(MAND_D)/$(INCS_D)/, \
                           $(addsuffix $(HPP_EXT), \
                                       $(HDRS)))
    SRCS     = $(addprefix $(MAND_D)/$(SRCS_D)/, \
                           $(addsuffix $(CPP_EXT), \
                                       $(CPPS)))
    OBJS     = $(patsubst $(MAND_D)/$(SRCS_D)/%$(CPP_EXT), \
                          $(OBJS_D)/$(MAND_D)/$(SRCS_D)/%$(OBJ_EXT), \
                          $(SRCS))
    MAIN_CPP = main$(CPP_EXT)
endif

MAIN_OBJ     = $(patsubst %$(CPP_EXT), \
                          $(OBJS_D)/%$(OBJ_EXT), \
                          $(MAIN_CPP))

# === FLAGS ================================================================== #

CPP_FLAGS    = -Wall -Wextra -Werror -std=c++2a -pedantic -g -Ofast
MK_FLAGS     = -p
RM_FLAGS     = -rfv

# === PROJECT ================================================================ #

NAME         = computor
LIB          = $(NAME).a

# === RULES ================================================================== #

all: $(NAME)

bonus: $(NAME)

$(OBJS_D)/%$(OBJ_EXT): %$(CPP_EXT) $(INCS)
	@$(MK) $(MK_FLAGS) $(dir $@)
	$(CPP) $(CPP_FLAGS) -c $< -o $@

$(OBJS_D)/$(MAND_D)/$(SRCS_D)/%$(OBJ_EXT): $(MAND_D)/$(SRCS_D)/%$(CPP_EXT) $(INCS)
	@$(MK) $(MK_FLAGS) $(dir $@)
	$(CPP) $(CPP_FLAGS) -c $< -o $@

$(OBJS_D)/$(BNUS_D)/$(SRCS_D)/%$(OBJ_EXT): $(BNUS_D)/$(SRCS_D)/%$(CPP_EXT) $(INCS)
	@$(MK) $(MK_FLAGS) $(dir $@)
	$(CPP) $(CPP_FLAGS) -c $< -o $@

$(LIB): $(OBJS)
	@$(AR_RCS) $(LIB) $(OBJS)

$(NAME): $(LIB) $(MAIN_OBJ)
	$(CPP) $(CPP_FLAGS) $(MAIN_OBJ) $(LIB) -o $(NAME)

clean:
	@$(RM) $(RM_FLAGS) $(OBJS_D)

fclean: clean
	@$(RM) $(RM_FLAGS) $(NAME) $(LIB)

re: fclean all

.PHONY: all bonus clean fclean re
