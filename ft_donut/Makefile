# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gicomlan <gicomlan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/08 13:59:24 by gicomlan          #+#    #+#              #
#    Updated: 2025/05/08 14:22:59 by gicomlan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_donut

CC = cc
CFLAGS = -Wall -Wextra -Werror -I includes
LDFLAGS = -lm

SRC = main.c \
      sources/ft_donut_utils.c \
      sources/ft_donut_init.c \
      sources/ft_donut_math.c \
      sources/ft_donut_render.c

# Dossiers pour les fichiers objets et dépendances
OBJ_DIR = obj
DEP_DIR = deps

# Création des chemins pour les fichiers .o et .d
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
DEP = $(addprefix $(DEP_DIR)/, $(SRC:.c=.d))

# Obtention des sous-répertoires nécessaires
OBJ_DIRS = $(OBJ_DIR) $(sort $(dir $(OBJ)))
DEP_DIRS = $(DEP_DIR) $(sort $(dir $(DEP)))

all: $(NAME)

# Création des répertoires nécessaires
$(OBJ_DIRS) $(DEP_DIRS):
	@mkdir -p $@

# Inclusion des fichiers de dépendances
-include $(DEP)

# Règle de compilation des fichiers objets avec génération de dépendances
$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR) $(DEP_DIR) $(dir $(OBJ)) $(dir $(DEP))
	$(CC) $(CFLAGS) -MMD -MP -MF $(DEP_DIR)/$*.d -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)
	@echo "Compilation terminée : $(NAME) est prêt !"

clean:
	@echo "Suppression des fichiers objets et de dépendances..."
	@rm -rf $(OBJ_DIR)
	@rm -rf $(DEP_DIR)
	@echo "Nettoyage terminé"

fclean: clean
	@echo "Suppression de l'exécutable $(NAME)..."
	@rm -f $(NAME)
	@echo "Suppression terminée"

re: fclean all

.PHONY: all clean fclean re
