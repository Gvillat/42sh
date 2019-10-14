#include "sh42.h"

void word_analyze(t_analyzer *analyzer, t_lexer *lexer, t_job *job)
{
	// ft_printf("WOWOWORD   %u         %s\n", analyzer->state, ((t_token*)lexer->tok->content)->data);
	(void)job;
	(void)lexer;
	analyzer->state = A_WORD;
	//check les prochain token pour savoir si ils sont conforme a la grammaire
	// TANT QUE token word 
	// premier token word  = cmd 
	// le suivant = opt 
	// le reste = cmd data
}

void end_analyze(t_analyzer *analyzer, t_lexer *lexer, t_job *job)
{
	// ft_printf("ENNNNNND   %u         %s\n", analyzer->state, ((t_token*)lexer->tok->content)->data);
	(void)lexer;
	analyzer->state = A_END;
	(void)job;
	//NE PASSERA PEUT ETRE PAS DEDANS CF P_END DU LEXER
	// doit en theorie etre le dernier token de a list et free la list si la list de jobs est OK
}	

void separator_analyze(t_analyzer *analyzer, t_lexer *lexer, t_job *job)
{
	// ft_printf("SEPARARARTOR   %u         %s\n", analyzer->state, ((t_token*)lexer->tok->content)->data);
	analyzer->state = A_SEPARATOR;
	(void)job;
	if (lexer->tok->next && !ft_strcmp("(null)", ((t_token*)lexer->tok->next->content)->data))
		analyzer->state = A_END;
	// delimite le list de token en une list ou un job
}

void redirect_analyze(t_analyzer *analyzer, t_lexer * lexer, t_job *job)
{
	// ft_printf("REDIDIDIRECT   %u         %s\n", analyzer->state, ((t_token*)lexer->tok->content)->data);
	(void)lexer;
	(void)job;
	analyzer->state = A_REDIRECT;
	// if (((t_token*)lexer->tok->content)->id == P_GREAT)
	// 	analyzer->fd_flags = O_RDWR + O_CREAT + O_TRUNC;
	// else if (((t_token*)lexer->tok->content)->id == P_DGREAT || ((t_token*)lexer->tok->content)->id == P_ANDDGREAT)
	// 	analyzer->fd_flags = O_RDWR + O_CREAT + O_APPEND;
	// else if (((t_token*)lexer->tok->content)->id == P_LESS)
	// 	analyzer->fd_flags = O_RDONLY;
	// else if (((t_token*)lexer->tok->content)->id == P_DLESSDASH || ((t_token*)lexer->tok->content)->id == P_DLESS)
		// analyzer->state = P_HEREDOC_REDIRECT;

	// delimite une list et determine la redirection IN ou OUT ou HERE_DOC
	// met dans la struct t_filedesc l'action IN OUT HERE_DOC...
	// depuis l'actual FD vers le wanted FD
}

void error_analyze(t_analyzer *analyzer, t_lexer *lexer, t_job *job)
{
	// ft_printf("EROROORRR  %u         %s\n", analyzer->state, ((t_token*)lexer->tok->content)->data);
	(void)lexer;
	(void)job;
	analyzer->state = A_ERROR;
	if (lexer->tok->next && !ft_strcmp("(null)", ((t_token*)lexer->tok->next->content)->data))
		analyzer->state = A_END;
	// en theorie doit devalider la list de token et la flush
}

void ionbr_analyze(t_analyzer *analyzer, t_lexer *lexer, t_job *job)
{
	// ft_printf("IOOOOOOONBR  %u         %s\n", analyzer->state, ((t_token*)lexer->tok->content)->data);
	(void)lexer;
	(void)job;
	analyzer->state = A_IONUMBER;
	// delimite la list de token en token IONBR
	// cree la struct job en consequence
	// CAD attribue l'IONBR au fd et dermine la redirection en fct de loperateur
}

void assign_analyze(t_analyzer *analyzer, t_lexer *lexer, t_job *job)
{
	// ft_printf("ASSSSSIIIIIGN  %u         %s\n", analyzer->state, ((t_token*)lexer->tok->content)->data);
	(void)lexer;
	(void)job;
	analyzer->state = A_ASSIGN;
	// delimite la list de token en token ASSIGN
	// cree la struct job en consequence
	// CAD cree un token dans la list assign pour pouvoir check ensuite si les tokens word suivant correspondent a un assign
}

// void start_analyze(t_analyzer *analyzer, t_job *job, t_lexer *lexer)
// {
// 	ft_printf("ASSSSSIIIIIGN  %u         %s\n", analyzer->state, ((t_token*)lexer->tok->content)->data);
// 	(void)job;
// 	analyzer->state = A_START;
// }

// t_job *init_job(t_job *job)
// {
// 	if (!(job = (t_job*)malloc(sizeof(t_job))))
// 		return (NULL);
// 	job->pid = 0;
// 	job->cmd = NULL;
// 	job->env = NULL;
// 	job->fd->action = 0;
// 	job->fd->actual = 1;
// 	job->fd->wanted = 1;
// 	job->status = 1; // 1 = running | 0 = stopped
// 	job->term_modes = NULL;
// 	return (job);
// }

t_job	*analyzer(t_core *shell)
{
	t_analyzer *analyzer;
	t_lexer *lexer;
	t_job *job;
	t_lst **head;

	job = NULL;
	analyzer = NULL;
	lexer = shell->lexer;
	head = &lexer->tok;
	analyzer = init_analyze(analyzer);
	analyzer->state = A_START;
	// job = init_job(job);
	if (parser(shell, lexer) != TRUE)
	{
		//erreur
		return (job); //shell->job = NULL;
	}
	// while (analyzer->state != A_END)
	while (analyzer->state != A_END && ft_strcmp("(null)", ((t_token*)lexer->tok->next->content)->data))
	{
		ft_printf("analyzer state %u || token id %u || token data %s\n", analyzer->state, ((t_token*)lexer->tok->content)->id ,((t_token*)lexer->tok->content)->data);
		analyzer->analyze[analyzer->state][((t_token*)lexer->tok->content)->id](analyzer, lexer, job);
		lexer->tok = lexer->tok->next; // faire une fct get_token qui passe au token suivant ??
	}
	lexer->tok = *head;
	return (job);
}
