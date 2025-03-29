/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabrito- <mabrito-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 20:59:01 by msilva-c          #+#    #+#             */
/*   Updated: 2025/03/28 17:18:13 by mabrito-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// dar set para null de todas as vars do msh()
int	tokenizer(void)
{
	//char	**matrix;

	printf("%s\n", msh()->line);
	//mete espacos
	printf("%s\n", msh()->line);



	
	//matrix = split_spaces(msh()->line);
	//if (!matrix)
	//	return (0);
	//msh()->tokens = create_tokens(matrix);
	//if (!msh()->tokens)
	//	return (0);
	//free_matrix(matrix);
	//re_token(msh()->tokens);
	return (1);
}
