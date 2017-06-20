/*
   SSDM Algorithm
   By Ke Bai and Jing Lu
 */

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <limits>

using namespace std;

//#define DEBUG

#define extraLibTime 50 
#define baseLatency 91 
#define latencyIncRate 0.075

typedef struct _Node 
{
    string funcName;
    unsigned long long stackSz;
    unsigned int NumOfFuncCalls;
} Node;

typedef struct _Edge
{
    string src;
    string sink;
    int pathNum;
    bool duplicate;
    bool cuttable;
} Edge;

typedef struct _benefit
{
    int b;
    Edge e;
} Benefit;

int file2vector (
	const string &benchmarkName,
	vector<Edge> &edgeVec,
	vector< vector<Node> > &pathVec,
	vector<string> &recursiveFnVec,
	int spmSize
	)
{
    ifstream infile(benchmarkName.c_str());
    if (!infile.is_open())
	return 1;

    string pattern = " ";
    string line;
    int ctl = 0;

    while (getline(infile,line))
    {
	if (line.compare("#") == 0)
	{
	    ctl++;
	    getline(infile,line);
	}
	if (ctl == 0)
	{
	    Edge e;
	    string::size_type pos;
	    line += pattern;

	    int size = line.size();
	    int cnt = 0;
	    for (int i=0; i<size; i++)
	    {
		pos = line.find(pattern,i);
		if (pos<size)
		{
		    if (cnt == 0)
		    {
			e.src = line.substr(i,pos-i);
			cnt++;
		    }
		    else if (cnt == 1)
		    {
			e.sink = line.substr(i,pos-i);
			cnt++; 
		    }
		    else if (cnt == 2)
		    {
			e.pathNum = atoi((line.substr(i,pos-i)).c_str());
			cnt++; 
		    }
		    i = pos + pattern.size() - 1;
		}
	    }

	    e.cuttable = true;
	    e.duplicate = false;
	    edgeVec.push_back(e);
	}
	else if (ctl == 1)
	{
	    Node n;
	    vector<Node> path;
	    string::size_type pos;
	    line += pattern;

	    int size = line.size();
	    int cnt = 0;
	    for (int i=0; i<size; i++)
	    {
		pos = line.find(pattern,i);
		if (pos<size)
		{
		    if (cnt == 0)
		    {
			n.funcName = line.substr(i,pos-i);
			cnt++;
		    }
		    else if (cnt == 1)
		    {
			n.stackSz = atoi((line.substr(i,pos-i)).c_str());
			//cout << n.stackSz<<endl;
			//cout <<std::numeric_limits<long long>::max()<<endl;
			if(n.stackSz != std::numeric_limits<int>::max() && n.stackSz > spmSize){
			    cout<<"error! The stack size of function "<<n.funcName<<" exceeds the SPM size limit! SPM size = "<<spmSize<<", and function stack size = "<<n.stackSz<<endl;
			    exit(-1);
			}
			cnt++; 
		    }
		    else if (cnt == 2)
		    {
			n.NumOfFuncCalls = atoi((line.substr(i,pos-i)).c_str());
			path.push_back(n);
			cnt = 0; 
		    }
		    i = pos + pattern.size() - 1;
		}				
	    }

	    pathVec.push_back(path);
	}
	else if (ctl == 2)
	{
	    string::size_type pos;
	    line += pattern;

	    int size = line.size();
	    int cnt = 0;
	    for (int i=0; i<size; i++)
	    {
		pos = line.find(pattern,i);
		if (pos<size)
		{
		    recursiveFnVec.push_back(line.substr(i,pos-i));
		    i = pos + pattern.size() - 1;
		}
	    }
	}
	else
	    cout<<"error! The format of input is incorrect!"<<endl;
    }

    infile.close();
    for(vector<Edge>::iterator it = edgeVec.begin(); it != edgeVec.end(); it++){
	for(vector<Edge>::iterator itt = it + 1; itt != edgeVec.end(); itt++){
	    if(it->src == itt->src && it->sink == itt->sink){
		it->duplicate = true;
		itt->duplicate = true;
	    }
	}
    }

#ifdef DEBUG
    cout<<"<<<<<<<<<<<<<<<<<<<<<<<<<Edge pair: "<<endl;
    for (vector<Edge>::iterator iter=edgeVec.begin(); iter!=edgeVec.end(); ++iter)
	cout<<"<"<<(*iter).src<<"->"<<(*iter).sink<<","<<(*iter).pathNum<<","<<(*iter).cuttable<<">"<<endl;

    cout<<"<<<<<<<<<<<<<<<<<<<<<<<<<Paths: "<<endl;
    for (vector< vector<Node> >::iterator iter=pathVec.begin(); iter!=pathVec.end(); ++iter)
    {
	for (vector<Node>::iterator iterNode=(*iter).begin(); iterNode!=(*iter).end(); ++iterNode)
	    cout<<"<"<<(*iterNode).funcName<<","<<(*iterNode).stackSz<<","<<(*iterNode).NumOfFuncCalls<<">"<<"\t";
	cout<<endl;
    }

    if (recursiveFnVec.size() != 0)
    {
	cout<<"<<<<<<<<<<<<<<<<<<<<<<<<<Recursive functions: "<<endl;
	for (vector<string>::iterator iter=recursiveFnVec.begin(); iter!=recursiveFnVec.end(); ++iter)
	    cout<<*iter<<endl;
    }
#endif

    if (infile.eof())
	return 4;
    if (infile.bad())
	return 2;
    if (infile.fail())
	return 3;
	
	return 0;
}

long long cost (const vector<Node> &segment)
{
    long long cost1 = 0, cost2 = 0;
    long long sumStackSizes = 0;

    cost1 = (*(segment.end()-1)).NumOfFuncCalls * extraLibTime;

    for (vector<Node>::const_iterator iterSeg=segment.begin(); iterSeg!=segment.end(); ++iterSeg)
	sumStackSizes += (*iterSeg).stackSz;

    cost2 = (*(segment.end()-1)).NumOfFuncCalls * 2 * (baseLatency + latencyIncRate * sumStackSizes);

    return (cost1 + cost2);
}

bool isCuttableEdge(
	const string &src, 
	const string &sink, 
	const int pathNum, 
	const vector<Edge> &edgeVec
	)
{
    if (src.compare(sink) == 0)
	return false;

    for (vector<Edge>::const_iterator iter=edgeVec.begin(); iter!=edgeVec.end(); ++iter)
    {
	if (((*iter).src.compare(src) == 0) && ((*iter).sink.compare(sink) == 0))
	{
	    if ((*iter).duplicate != 0)
	    {
		if (((*iter).pathNum == pathNum) && (*iter).cuttable) 
		    return true;
		else 
		    return false;
	    }
	    else
	    {
		if ((*iter).cuttable)
		    return true;
		else
		    return false;
	    }
	}
    }

    cout<<"error! Function name must be wrong!"<<endl;
	
	
	return false;
}

bool isEqual(
	vector<Node> &segment1,
	vector<Node> &segment2
	)
{
    if (segment1.size() != segment2.size())
	return false;
    else
    {
	for (vector<Node>::iterator iter1=segment1.begin(),iter2=segment2.begin(); 
		(iter1!=segment1.end() && iter2!=segment2.end()); ++iter1,++iter2)
	{
	    if (((*iter1).funcName.compare((*iter2).funcName) == 0) && ((*iter1).stackSz == (*iter2).stackSz) && ((*iter1).NumOfFuncCalls == (*iter2).NumOfFuncCalls))
		continue;
	    else
		return false;
	}
	return true;
    }
}

bool isBelongsTo(
	vector<Node> &segment,
	vector< vector<Node> > &segments
	)
{
    for (vector< vector<Node> >::iterator iter=segments.begin(); iter!=segments.end(); ++iter)
    {
	if (isEqual(*iter,segment))
	    return true;
    }
    return false;
}

void findSegments(
	const Edge &edge,
	const vector<Edge> &edgeVec,
	vector< vector<Node> > &upSegments,
	vector< vector<Node> > &downSegments,
	vector< vector<Node> > &pathVec
	)
{
    int pathNum = 0;
    for (vector< vector<Node> >::iterator iter=pathVec.begin(); iter!=pathVec.end(); ++iter)
    {
	pathNum++;

	vector<Node>::iterator sUp,eUp,prevUp;
	sUp = eUp = prevUp = (*iter).begin();

	vector<Node>::iterator sDown,eDown,prevDown;
	sDown = eDown = prevDown = (*iter).begin();
	bool found = false;
	for (vector<Node>::iterator iterNode=(*iter).begin(); iterNode!=(*iter).end(); ++iterNode)
	{		
	    if (isCuttableEdge((*prevUp).funcName,(*iterNode).funcName,pathNum,edgeVec))
		sUp = iterNode;

	    if ((edge.src.compare((*iterNode).funcName) == 0) && (edge.sink.compare((*(iterNode+1)).funcName) == 0))
	    {			
		if (edge.duplicate != 0)
		{
		    if (edge.pathNum == pathNum)
		    {
			eUp = iterNode;
			found = true;
			sDown = eDown = prevDown = ++iterNode;
			break;
		    }
		}
		else
		{
		    eUp = iterNode;
		    found = true;
		    sDown = eDown = prevDown = ++iterNode;
		    break;
		}
	    }

	    prevUp = iterNode;
	}

	if (sUp <= eUp)
	{
	    vector<Node> segUp;
	    segUp.assign(sUp,(eUp+1));
	    if (!isBelongsTo(segUp,upSegments) && found)
		upSegments.push_back(segUp);
	}

	found = false;
	if (sDown != (*iter).begin())
	{
	    vector<Node>::iterator iterNode;
	    for (iterNode=sDown; iterNode!=(*iter).end(); ++iterNode)
	    {
		if (isCuttableEdge((*prevDown).funcName,(*iterNode).funcName,pathNum,edgeVec))
		{
		    found = true;
		    eDown = prevDown;
		    break;
		}

		prevDown = iterNode;
	    }

	    if (iterNode == (*iter).end() && !found)
		eDown = iterNode-1;

	    vector<Node> segDown;
	    segDown.assign(sDown,(eDown+1));
	    downSegments.push_back(segDown);
	}
    }
}

bool isRecursive(
	const string &Fn,
	const vector<string> &recursiveFnVec
	)
{
    if (recursiveFnVec.size() != 0)
    {
	for (vector<string>::const_iterator iter=recursiveFnVec.begin(); iter!=recursiveFnVec.end(); ++iter)
	{
	    if (Fn.compare(*iter) == 0)
		return true;
	}
	return false;
    }
    else 
	return false;
}

void SSDM(
	vector<Edge> &edgeVec,
	vector< vector<Node> > &pathVec,
	const vector<string> &recursiveFnVec,
	const int W
	)
{
    while (1) 
    {
	vector<Benefit> benefit;

	for (vector<Edge>::const_iterator iter=edgeVec.begin(); iter!=edgeVec.end(); ++iter)
	{
	    if ((*iter).cuttable && !isRecursive((*iter).sink,recursiveFnVec))
	    {
		vector< vector<Node> > upSegments, downSegments;
		findSegments((*iter),edgeVec,upSegments,downSegments,pathVec);
		long long cost_before = 0;
		for (vector< vector<Node> >::iterator iterUp=upSegments.begin(); iterUp!=upSegments.end(); ++iterUp)			
		    cost_before += cost(*iterUp);
		for (vector< vector<Node> >::iterator iterDown=downSegments.begin(); iterDown!=downSegments.end(); ++iterDown)			
		    cost_before += cost(*iterDown);

#ifdef DEBUG
		cout<<"Before removing the cut on edge <"<<(*iter).src<<"->"<<(*iter).sink<<"> in the path "<<(*iter).pathNum<<", the cost is: "<<cost_before<<endl;
#endif

		vector< vector<Node> > newSegments;
		for (vector< vector<Node> >::iterator iter1=upSegments.begin(); iter1!=upSegments.end(); ++iter1)
		{
		    for (vector< vector<Node> >::iterator iter2=downSegments.begin(); iter2!=downSegments.end(); ++iter2)
		    {
			vector<Node> newSegment;
			newSegment.insert(newSegment.begin(),(*iter1).begin(),(*iter1).end());
			newSegment.insert(newSegment.end(),(*iter2).begin(),(*iter2).end());
			newSegments.push_back(newSegment);
		    }
		}

		bool voilate = false;
		long long cost_after = 0;
		for (vector< vector<Node> >::iterator iterSeg=newSegments.begin(); iterSeg!=newSegments.end(); ++iterSeg)
		{
		    long long segStackSzs = 0;
		    for (vector<Node>::iterator iterNode=(*iterSeg).begin(); iterNode!=(*iterSeg).end(); ++iterNode)
			segStackSzs += (*iterNode).stackSz;

		    if (segStackSzs > W)
		    {
#ifdef DEBUG
			cout<<"Removing the cut on edge <"<<(*iter).src<<"->"<<(*iter).sink<<"> in the path "<<(*iter).pathNum<<" voilate the size constraint!"<<endl;
#endif
			voilate = true;
			break;
		    }

		    cost_after += cost(*iterSeg);
		}

#ifdef DEBUG
		cout<<"After removing the cut on edge <"<<(*iter).src<<"->"<<(*iter).sink<<"> in the path "<<(*iter).pathNum<<", the cost is: "<<cost_after<<endl;
#endif

		if (voilate)
		    continue;

		long long B = cost_before - cost_after;
#ifdef DEBUG
		cout<<"Removing benefit of removing the cut on edge <"<<(*iter).src<<"->"<<(*iter).sink<<"> in the path "<<(*iter).pathNum<<" is: "<<B<<endl;
#endif

		if (B > 0)
		{
		    Benefit Ben;
		    Ben.b = B;
		    Ben.e.src = (*iter).src;
		    Ben.e.sink = (*iter).sink;
		    Ben.e.pathNum = (*iter).pathNum;
		    benefit.push_back(Ben);
		}
	    }
	}

	if (benefit.size() == 0)
	    break;

	Benefit B_max;
	B_max.b = 0;
	for (vector<Benefit>::iterator iter=benefit.begin(); iter!=benefit.end(); ++iter)
	{
	    if ((*iter).b > B_max.b)
	    {
		B_max.b = (*iter).b;
		B_max.e.src = (*iter).e.src;
		B_max.e.sink = (*iter).e.sink;
		B_max.e.pathNum = (*iter).e.pathNum;
	    }
	}

	for (vector<Edge>::iterator iter=edgeVec.begin(); iter!=edgeVec.end(); ++iter)
	{
	    if ((B_max.e.src.compare((*iter).src) == 0) && (B_max.e.sink.compare((*iter).sink) == 0) && (B_max.e.pathNum == (*iter).pathNum))
	    {
		(*iter).cuttable = false;
#ifdef DEBUG
		cout<<"Cut on edge <"<<(*iter).src<<"->"<<(*iter).sink<<"> in the path "<<(*iter).pathNum<<" is removed!"<<endl;
#endif
		break;
	    }
	}
    }
}

int main (int argc, char **argv) 
{
    vector<Edge>edgeVec;
    vector< vector<Node> > pathVec;  
    vector<string> recursiveFnVec;
    int spmSize = 0;
    string benchmarkName;

    if (argc != 3)
    {
	cout<<"Usage: ./EdgeCutting <benchmark name> <SPM size>"<<endl;
	return -1;
    }
    benchmarkName = argv[1];
    spmSize = atoi(argv[2]);

    switch (file2vector(benchmarkName,edgeVec,pathVec,recursiveFnVec, spmSize))
    {
	case 1:
	    cout<<"error!can not open file: "<<benchmarkName<<endl;
	    return -1;
	    break;
	case 2:
	    cout<<"error!systerm failure"<<endl;
	    return -1;
	    break;
	case 3:
	    cout<<"error!read failure"<<endl;
	    return -1;
	    break;
	default:
	    break;
    }

    SSDM(edgeVec,pathVec,recursiveFnVec,spmSize);

    //cout<<"SPM size = "<<spmSize<<" bytes, follow the following instruction for library insertions:"<<endl;
    //cout<<"\n***************************************************"<<endl;
    for (vector<Edge>::iterator iter=edgeVec.begin(); iter!=edgeVec.end(); ++iter)
    {
	if ((*iter).cuttable)
	{	int n = 1;
	    vector<Node> curPath = pathVec[(*iter).pathNum - 1];
	    for(vector<Node>::iterator it = curPath.begin(); it + 1 != curPath.end(); it++){
		n++;
		if(it->funcName == iter->src && (it+1)->funcName == iter->sink)
		    break;
	    }
	    //cout<<"_store() and _load() must be inserted before and after the #"<<n<<" function "<<(*iter).sink<<" on path "<<(*iter).pathNum<<" respectively"<<endl;
	    cout << (*iter).pathNum << " " << n <<  " " << (*iter).sink << "\n";
	}			
    }
    //cout<<"***************************************************"<<endl;

    return 0;
}
