#include"../include/minishell.h"

void	postorderTravelBinSTree(t_astnode *pipenode)
{
	int	i;

	i = 0;
	if(pipenode)
	{
		printf("node type : %d  ", pipenode->nodetype);
		if(pipenode->pvalue_index)
		{
			while(pipenode->pvalue_index[i] != -1)
			{
				printf("       value : %s         ", data->plexer->pptokens[pipenode->pvalue_index[i]]);
				i++;
			}
		}
		printf("\n");
		postorderTravelBinSTree(pipenode->pleftchild);
		postorderTravelBinSTree(pipenode->prightchild);
	}
}

// void	postorderTravelBinSTree(t_astnode *node)
// {
// 	int i = 0;

// 	if(node)
// 	{
// 		printf("node type : %d  ", node->nodetype);
// 		if(node->pvalue_index)
// 		{
// 			while(node->pvalue_index[i] != -1)
// 			{
// 				printf("       value : %s         ", data->plexer->pptokens[node->pvalue_index[i]]);
// 				i++;
// 			}
// 		}
// 		printf("\n");
// 		postorderTravelBinSTree(node->pleftchild);
// 		postorderTravelBinSTree(node->prightchild);
// 	}
// }

