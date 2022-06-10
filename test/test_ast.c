#include"../include/minishell.h"

void	postorderTravelBinSTree(t_astnode *node)
{
	int i = 0;

	if(node)
	{
		printf("node type : %d  ", node->nodetype);
		if(node->pvalue_index)
		{
			while(node->pvalue_index[i] != -1)
			{
				printf("       value : %s         ", data->plexer->pptokens[node->pvalue_index[i]]);
				i++;
			}
		}
		printf("\n");
		postorderTravelBinSTree(node->pleftchild);
		postorderTravelBinSTree(node->prightchild);
	}
}

