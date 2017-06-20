#include <stdio.h>
#include <stdlib.h>

#define NUM_NODES                          100
#define NONE                               9999

struct _NODE
{
	int iDist;
	int iPrev;
};
typedef struct _NODE NODE;

struct _QITEM
{
	int iNode;
	int iDist;
	int iPrev;
	struct _QITEM *qNext;
};
typedef struct _QITEM QITEM;


QITEM *qHead = NULL;

int AdjMatrix[NUM_NODES][NUM_NODES];

int g_qCount = 0;
NODE rgnNodes[NUM_NODES];
int ch;
int iPrev, iNode;
int i, iCost, iDist;


void print_path (NODE *rgnNodes, int chNode)
{
	if (rgnNodes[chNode].iPrev != NONE)
	{
		print_path(rgnNodes, rgnNodes[chNode].iPrev);
	}
	_fprintf (_gArgs.outputStream[0]," %d", chNode);
	_fflush(_gArgs.outputStream[0]);
}


void enqueue (int iNode, int iDist, int iPrev)
{
	QITEM *qNew = (QITEM *) _malloc(sizeof(QITEM));
	QITEM *qLast = qHead;

	if (!qNew) 
	{
		_fprintf(_gArgs.outputStream[0], "Out of memory.\n");_fflush(_gArgs.outputStream[0]);
		exit(1);
	}
	qNew->iNode = iNode;
	qNew->iDist = iDist;
	qNew->iPrev = iPrev;
	qNew->qNext = NULL;

	if (!qLast) 
	{
		qHead = qNew;
	}
	else
	{
		while (qLast->qNext) qLast = qLast->qNext;
		qLast->qNext = qNew;
	}
	g_qCount++;
	//               ASSERT(g_qCount);
}


void dequeue (int *piNode, int *piDist, int *piPrev)
{
	QITEM *qKill = qHead;

	if (qHead)
	{
		//                 ASSERT(g_qCount);
		*piNode = qHead->iNode;
		*piDist = qHead->iDist;
		*piPrev = qHead->iPrev;
		qHead = qHead->qNext;
		_free(qKill);
		g_qCount--;
	}
}


int qcount (void)
{
	return(g_qCount);
}

int dijkstra(int chStart, int chEnd) 
{



	for (ch = 0; ch < NUM_NODES; ch++)
	{
		rgnNodes[ch].iDist = NONE;
		rgnNodes[ch].iPrev = NONE;
	}

	if (chStart == chEnd) 
	{
		_fprintf(_gArgs.outputStream[0],"Shortest path is 0 in cost. Just stay where you are.\n");
		_fflush(_gArgs.outputStream[0]);
	}
	else
	{
		rgnNodes[chStart].iDist = 0;
		rgnNodes[chStart].iPrev = NONE;

		enqueue (chStart, 0, NONE);

		while (qcount() > 0)
		{
			dequeue (&iNode, &iDist, &iPrev);
			for (i = 0; i < NUM_NODES; i++)
			{
				if ((iCost = AdjMatrix[iNode][i]) != NONE)
				{
					if ((NONE == rgnNodes[i].iDist) || 
							(rgnNodes[i].iDist > (iCost + iDist)))
					{
						rgnNodes[i].iDist = iDist + iCost;
						rgnNodes[i].iPrev = iNode;
						enqueue (i, iDist + iCost, iNode);
					}
				}
			}
		}

		_fprintf(_gArgs.outputStream[0],"Shortest path is %d in cost. ", rgnNodes[chEnd].iDist);
		_fprintf(_gArgs.outputStream[0],"Path is: ");
		_fflush(_gArgs.outputStream[0]);
		print_path(rgnNodes, chEnd);
		_fprintf(_gArgs.outputStream[0],"\n");
		_fflush(_gArgs.outputStream[0]);
	}
	return 0;
}

int k;
//int main(int argc, char *argv[]) {
int Entry(){
	int i,j;//,k;
//	FILE *fp;

//	if (argc<2) {
//		fprintf(stderr, "Usage: dijkstra <filename>\n");
//		fprintf(stderr, "Only supports matrix size is #define'd.\n");
//	}

	/* open the adjacency matrix file */
//	fp = fopen (argv[1],"r");

	/* make a fully connected matrix */
	for (i=0;i<NUM_NODES;i++) {
		for (j=0;j<NUM_NODES;j++) {
			/* make it more sparce */
			fscanf(_gArgs.inputStream[0],"%d",&k);
			AdjMatrix[i][j]= k;
		}
	}

	/* finds 10 shortest paths between nodes */
	for (i=0,j=NUM_NODES/2;i<20;i++,j++) {
		j=j%NUM_NODES;
		dijkstra(i,j);
	}

	//exit(0);
	return 0;


}
