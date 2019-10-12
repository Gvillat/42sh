#include "sh42.h"

// void init_assign_analyze(t_anal analyze)
// {
// 	analyze[A_ASSIGN][P_NEWLINE] =
// 	analyze[A_ASSIGN][P_ANDIF] =
// 	analyze[A_ASSIGN][P_AND] =
// 	analyze[A_ASSIGN][P_ORIF] =
// 	analyze[A_ASSIGN][P_PIPE] =
// 	analyze[A_ASSIGN][P_DSEMI] =
// 	analyze[A_ASSIGN][P_SEMICOLON] =
// 	analyze[A_ASSIGN][P_DLESSDASH] =
// 	analyze[A_ASSIGN][P_DLESS] =
// 	analyze[A_ASSIGN][P_LESSGREAT] =
// 	analyze[A_ASSIGN][P_LESS] =
// 	analyze[A_ASSIGN][P_DGREAT] =
// 	analyze[A_ASSIGN][P_GREATAND] =
// 	analyze[A_ASSIGN][P_CLOBBER] =
// 	analyze[A_ASSIGN][P_GREAT] =
// 	analyze[A_ASSIGN][P_IONUMBER] =
// 	analyze[A_ASSIGN][P_ASSIGN] =
// 	analyze[A_ASSIGN][P_WORD] =
// 	analyze[A_ASSIGN][P_END] =
// }

// void init_ionumber_analyze(t_anal analyze)
// {
// 	analyze[A_IONUMBER][P_NEWLINE] =
// 	analyze[A_IONUMBER][P_ANDIF] =
// 	analyze[A_IONUMBER][P_AND] =
// 	analyze[A_IONUMBER][P_ORIF] =
// 	analyze[A_IONUMBER][P_PIPE] =
// 	analyze[A_IONUMBER][P_DSEMI] =
// 	analyze[A_IONUMBER][P_SEMICOLON] =
// 	analyze[A_IONUMBER][P_DLESSDASH] =
// 	analyze[A_IONUMBER][P_DLESS] =
// 	analyze[A_IONUMBER][P_LESSGREAT] =
// 	analyze[A_IONUMBER][P_LESS] =
// 	analyze[A_IONUMBER][P_DGREAT] =
// 	analyze[A_IONUMBER][P_GREATAND] =
// 	analyze[A_IONUMBER][P_CLOBBER] =
// 	analyze[A_IONUMBER][P_GREAT] =
// 	analyze[A_IONUMBER][P_IONUMBER] =
// 	analyze[A_IONUMBER][P_ASSIGN] =
// 	analyze[A_IONUMBER][P_WORD] =
// 	analyze[A_IONUMBER][P_END] =
// }

// void init_redirect_analyze(t_anal analyze)
// {
// 	analyze[A_REDIRECT][P_NEWLINE] =
// 	analyze[A_REDIRECT][P_ANDIF] =
// 	analyze[A_REDIRECT][P_AND] =
// 	analyze[A_REDIRECT][P_ORIF] =
// 	analyze[A_REDIRECT][P_PIPE] =
// 	analyze[A_REDIRECT][P_DSEMI] =
// 	analyze[A_REDIRECT][P_SEMICOLON] =
// 	analyze[A_REDIRECT][P_DLESSDASH] =
// 	analyze[A_REDIRECT][P_DLESS] =
// 	analyze[A_REDIRECT][P_LESSGREAT] =
// 	analyze[A_REDIRECT][P_LESS] =
// 	analyze[A_REDIRECT][P_DGREAT] =
// 	analyze[A_REDIRECT][P_GREATAND] =
// 	analyze[A_REDIRECT][P_CLOBBER] =
// 	analyze[A_REDIRECT][P_GREAT] =
// 	analyze[A_REDIRECT][P_IONUMBER] =
// 	analyze[A_REDIRECT][P_ASSIGN] =
// 	analyze[A_REDIRECT][P_WORD] =
// 	analyze[A_REDIRECT][P_END] =
// }

// void init_end_analyze(t_anal analyze)
// {
// 	analyze[A_END][P_NEWLINE] = separator_analyze;
// 	analyze[A_END][P_ANDIF] = redirect_analyze;
// 	analyze[A_END][P_AND] = redirect_analyze;
// 	analyze[A_END][P_ORIF] = redirect_analyze;
// 	analyze[A_END][P_PIPE] = redirect_analyze;
// 	analyze[A_END][P_DSEMI] = separator_analyze;
// 	analyze[A_END][P_SEMICOLON] = separator_analyze;
// 	analyze[A_END][P_DLESSDASH] = redirect_analyze;
// 	analyze[A_END][P_DLESS] = redirect_analyze;
// 	analyze[A_END][P_LESSGREAT] = redirect_analyze;
// 	analyze[A_END][P_LESS] = redirect_analyze;
// 	analyze[A_END][P_DGREAT] = redirect_analyze;
// 	analyze[A_END][P_GREATAND] = redirect_analyze;
// 	analyze[A_END][P_CLOBBER] = redirect_analyze;
// 	analyze[A_END][P_GREAT] = redirect_analyze;
// 	analyze[A_END][P_IONUMBER] = ionbr_analyze;
// 	analyze[A_END][P_ASSIGN] = assign_analyze;
// 	analyze[A_END][P_WORD] = word_analyze;
// 	analyze[A_END][P_END] = end_analyze;
// }

// void	init_separator_analyze(t_anal analyze)
// {
// 	analyze[A_SEPARATOR][P_WORD] = end_analyze;
// 	analyze[A_SEPARATOR][P_SPSTRING] = end_analyze;
// 	analyze[A_SEPARATOR][P_GREAT] = end_analyze;
// 	analyze[A_SEPARATOR][P_GREATAND] = end_analyze;
// 	analyze[A_SEPARATOR][P_LESS] = end_analyze;
// 	analyze[A_SEPARATOR][P_LESSAND] = end_analyze;
// 	analyze[A_SEPARATOR][P_DGREAT] = end_analyze;
// 	analyze[A_SEPARATOR][P_DLESS] = end_analyze;
// 	analyze[A_SEPARATOR][P_DLESSDASH] = end_analyze;
// 	analyze[A_SEPARATOR][P_ANDDGREAT] = end_analyze;
// 	analyze[A_SEPARATOR][P_SEMICOLON] = end_analyze;
// 	analyze[A_SEPARATOR][P_NEWLINE] = end_analyze;
// 	analyze[A_SEPARATOR][P_END] = end_analyze;
// }

void init_start_analyze(t_anal analyze)
{
	analyze[A_START][P_NEWLINE] = separator_analyze;
	analyze[A_START][P_ANDIF] = redirect_analyze;
	analyze[A_START][P_AND] = redirect_analyze;
	analyze[A_START][P_ORIF] = redirect_analyze;
	analyze[A_START][P_PIPE] = redirect_analyze;
	analyze[A_START][P_DSEMI] = separator_analyze;
	analyze[A_START][P_SEMICOLON] = separator_analyze;
	analyze[A_START][P_DLESSDASH] = redirect_analyze;
	analyze[A_START][P_DLESS] = redirect_analyze;
	analyze[A_START][P_LESSGREAT] = redirect_analyze;
	analyze[A_START][P_LESS] = redirect_analyze;
	analyze[A_START][P_DGREAT] = redirect_analyze;
	analyze[A_START][P_GREATAND] = redirect_analyze;
	analyze[A_START][P_CLOBBER] = redirect_analyze;
	analyze[A_START][P_GREAT] = redirect_analyze;
	analyze[A_START][P_IONUMBER] = ionbr_analyze;
	analyze[A_START][P_ASSIGN] = assign_analyze;
	analyze[A_START][P_WORD] = word_analyze;
	analyze[A_START][P_END] = end_analyze;
}

void init_word_analyze(t_anal analyze)
{
	analyze[A_WORD][P_NEWLINE] = separator_analyze;
	analyze[A_WORD][P_ANDIF] = redirect_analyze;
	analyze[A_WORD][P_AND] = redirect_analyze;
	analyze[A_WORD][P_ORIF] = redirect_analyze;
	analyze[A_WORD][P_PIPE] = redirect_analyze;
	analyze[A_WORD][P_DSEMI] = separator_analyze;
	analyze[A_WORD][P_SEMICOLON] = separator_analyze;
	analyze[A_WORD][P_DLESSDASH] = redirect_analyze;
	analyze[A_WORD][P_DLESS] = redirect_analyze;
	analyze[A_WORD][P_LESSGREAT] = redirect_analyze;
	analyze[A_WORD][P_LESS] = redirect_analyze;
	analyze[A_WORD][P_DGREAT] = redirect_analyze;
	analyze[A_WORD][P_GREATAND] = redirect_analyze;
	analyze[A_WORD][P_CLOBBER] = redirect_analyze;
	analyze[A_WORD][P_GREAT] = redirect_analyze;
	analyze[A_WORD][P_IONUMBER] = ionbr_analyze;
	analyze[A_WORD][P_ASSIGN] = assign_analyze;
	analyze[A_WORD][P_WORD] = word_analyze;
	analyze[A_WORD][P_END] = end_analyze;
}

static void	bzero_analyze(t_anal parsing)
{
	int		index;
	int		state;

	index = 0;
	while (index < NB_ANALYZER_STATE)
	{
		state = 0;
		while (state < NB_OF_TOKENS)
			parsing[index][state++] = error_analyze;
		++index;
	}
}

t_analyzer *init_analyze(t_analyzer *analyzer)
{
	if (!(analyzer = (t_analyzer*)malloc(sizeof(t_analyzer))))
		return (NULL);
	bzero_analyze(analyzer->analyze);
	init_start_analyze(analyzer->analyze);
	// init_ionumber_analyze(analyzer->analyze);
	// init_assign_analyze(analyzer->analyze);
	init_word_analyze(analyzer->analyze);
	// init_separator_analyze(analyzer->analyze);
	// init_redirect_analyze(analyzer->analyze);
	// init_end_analyze(analyzer->analyze);
	return (analyzer);
}