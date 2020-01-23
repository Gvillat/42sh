/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 10:41:55 by arsciand          #+#    #+#             */
/*   Updated: 2020/01/23 12:11:50 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "sh42.h"
# include "enum.h"
# include <termios.h>

/*
**	Some build data
*/

typedef struct	s_build
{
	u_int8_t	release;
	u_int8_t	version;
	u_int16_t	patch;
	u_int32_t	date;
}				t_build;

/*
** Lexer_parser_analyzer
*/

typedef struct s_lexer 	t_lexer;
typedef struct s_parser	t_parser;
typedef struct s_analyzer t_analyzer;
typedef struct s_core t_core;

typedef t_analyzer	*(*t_analyze)(t_analyzer*, t_core*);
typedef t_analyze t_anal[NB_ANALYZER_STATE][NB_PARSER_STATE];
typedef t_lst *(*t_lexing)(t_lexer*, t_lst *);

typedef struct s_read t_read;

/*
**	t_db is formated to support environnement variables ; {key} and {value}
**	t_db is formated to support environnement variables ; {key}, {value} and {type}
*/

typedef struct		s_db
{
	char		*key;
	char		*value;
	u_int8_t	type;
	u_int32_t	hit;		// Only for hash_map
}				t_db;

/*
**	t_process is formated to contain background processes
*/


typedef struct	s_process_var
{
	char		*name;
	pid_t		pid;
	u_int16_t	bck_order;	// Background place order (0 = last)
	u_int16_t	bck_id;		// Background id
}				t_process_var;

/*
**	t_hash and his db for hash table implementation
*/

typedef struct	s_hash
{
	t_lst		**map;
	u_int32_t	value;
	u_int32_t	size;			// Size located
	u_int32_t	lenght;			// Numbers of keys
}				t_hash;

/*
**			COMMAND_LINE
*/

typedef struct s_expan
{
	char 			*(*machine)(char* ,t_core*);
	e_pstate 	id;
	int 			len;
	char			*data;
}		t_expan;

typedef struct s_lex_exp
{
	t_lst 			*(*func)(t_lexer *, e_pstate, int, t_lst *);
	e_pstate 	id;
	int 			len;
}		t_lex_exp;

/*
**			COMMAND_LINE
*/

typedef struct			s_read
{
	char				prompt[10];
	int					prompt_len;
	int					x_index;
	int					x;
	int					y;
	int					width;
	int					ws_col;
	int					ws_li;
	int					ac;

	int					flag;
	int					sub_prompt;
	int					status;

	char				*tcaps[CAPS_NBR];
	char				*buffer;
	char				*tmp_buff;
	char				**cmd;

	t_core				*shell;
	t_lst				*heredoc;
	t_lst				*history;
	t_lst				*history_index;
}						t_read;

/*
** 			LEXER_PARSER_ANALYZER
*/

typedef struct	s_redir
{
	e_pstate			type;
	char				*heredoc;
	char				*op[2];
	int					io_num[2];
	int					dup_fd;
}				t_redir;

typedef struct			s_process
{
	e_pstate			type;
	t_lst				*assign_list;
	t_lst				*redir_list;
	char				**av;
	char				*bin;
	pid_t				pid;
}						t_process;

typedef struct			s_job
{
	char			*command;
	t_lst			*process_list;
	// struct termios	  *term_modes;
	// pid_t			   pgid;
	// t_filedesc		  fd;
	// int		 status; // 1 = running | 0 = stopped par exemple
	e_pstate		type;
}			t_job;

typedef struct			s_analyzer
{
	t_anal				analyze;
	e_astate			state;
	t_lst				*lexer;
	t_job			   job;
	t_process		   process;
	t_redir			 redir;
	t_db				db;
	t_lst			   *job_list;
	t_lst			   *process_list;
	t_lst			   *redir_list;
}			t_analyzer;

typedef struct			s_graph
{
	e_pstate	  *good_type;
}					   t_graph;

typedef struct		s_parser
{
	t_graph			graph[NB_PARSER_STATE];
	e_pstate		state;
}					t_parser;

typedef struct			s_token
{
	e_pstate id;
	char			*data;
	size_t		  len;
}			  t_token;

typedef struct 		 	s_lexer
{
	char			*buff;
	e_lstate		status;
	size_t			ntok;
	size_t			buf_pos;
	t_lexing		lex[NB_LEXER_STATE];
	t_token 		token;
}				t_lexer;

/*
**	t_core
*/

typedef struct	s_core
{
	/* structs */
	t_read				term;
	t_build				build;
	t_hash				hash;			// Gonna call it on the stack for now
	t_db				db;
	t_lst				*running_process;

	/* init shell */
	struct termios		old_t;			// Pour eviter la globale
	struct termios		new_t;

	/* lists */
	t_lst				*env;
	t_lst				*pos_vars;
	t_lst				*lexer; //TO REMOVE
	t_lst				*job_list;

	/* variables */
	int32_t				status;				//	last exit status value (echo $?)
	int32_t				heredoc;			//	counting number of heredocs
	u_int8_t			opt;				//	Option
}				t_core;

#endif
