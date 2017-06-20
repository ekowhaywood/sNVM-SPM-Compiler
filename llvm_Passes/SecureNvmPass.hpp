#ifndef __COMMON_HEADER__
#define __COMMON_HEADER__

//#include "sysfuncindex.h"

#include "llvm/Pass.h"
#include "llvm/PassManager.h"
#include "llvm/Analysis/CallGraph.h"
#include "llvm/IR/Attributes.h"
#include "llvm/IR/InlineAsm.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Value.h"
#include "llvm/Transforms/Utils/Cloning.h"
#include "llvm/Transforms/Utils/ValueMapper.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/Debug.h"

#include <fstream>
#include <queue>
#include <tuple>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <sstream>


#include "llvm/Pass.h"
#include "llvm/Analysis/AliasAnalysis.h"
#include "llvm/Analysis/CallGraph.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Dominators.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/GlobalVariable.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/InstVisitor.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include "llvm/Transforms/Utils/Cloning.h"
#include "llvm/Transforms/Utils/ValueMapper.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/YAMLTraits.h"

#include <cmath>
#include <deque>
#include <fstream>
#include <iostream>
#include <set>
#include <stack>
#include <string>
#include <utility>
#include <vector>
#include <unordered_set>
#include <unordered_map>





using namespace llvm;

extern std::vector<Instruction *> deleteList;

class MemAccessInst
{
public:
	enum Type { load=1, store=2 } ;
	enum OperadType { global , stack , dynamic } ;
	
	bool exclude ;
	Instruction * Inst;
	GlobalVariable * GVaddress;
	AllocaInst * StackAddress ;
	//Value * addrOperand ;
	Type type ;
	OperadType operandType;
	
	static MemAccessInst *	 get(Instruction *I);
	Value * getPointerOperand();
	bool setPointerOperand(Value * newAddr);

};


#define DEBUG_TYPE "smmssm"
extern std::pair<std::vector<std::vector<CallGraphNode::CallRecord *> >, std::unordered_set<CallGraphNode *> > extractPaths(CallGraphNode::CallRecord *);
extern void bfsPrint(CallGraphNode::CallRecord *, std::vector<std::vector<CallGraphNode::CallRecord *> > &paths, std::ofstream &);


extern DataLayout * TD ;
extern std::vector<std::string> LibraryFunctions ;
extern std::vector<std::string> UserFunctions ;
extern std::vector<MemAccessInst *> AllMemAccessInst;
extern std::map<CallInst * , int > CallInstList ;
extern unsigned long getAllMemAccessInst(Module &mod);


// stack mgt routine
extern void CreateSpAsmFtnType(Module & mod);
extern Instruction * InsertGetStackRegisterValue(Module &mod, Value * var , Instruction * Position  ,bool AfterPosition = false );
extern Instruction * InsertPutStackRegisterValue(Module &mod , Value* var , Instruction * Position , bool AfterPosition = false );
Instruction * InsertPutStackRegisterValue(Module &mod , Value* var , IRBuilder<> &builder  );
extern bool runStackMgtPass(const Module &mod , CallGraph &cg);


// code mgt routine
//typedef struct _FunctionData
//{
//	std::string sectionname;
//	GlobalVariable * lma ;
//	GlobalVariable * lmastop;
//	unsigned int idx;
//	unsigned int regionidx;
//} _FunctionData ;
//
//extern std::map < int , std::vector<Function * >  > regions_ ;
//extern std::map < Function * , _FunctionData *> funcs ;
extern bool runCodeMgtPass( Module &mod, CallGraph &cg);
extern bool runStackMgtPass( Module &mod , CallGraph &cg );
extern bool insertAddrTrans( Module &mod , CallGraph &cg );
//extern void RegisterFunctionMapping(Module &  ) ;
extern void replaceMallocAndFree (Module &mod);

//
extern std::map<CallInst * , int > wrapInstListForCodeMgt   ;
extern std::map<CallInst * , int > wrapInstListForStackMgt   ;
//

extern std::map< Function * , unsigned int > funcIndex ;
extern std::unordered_map <Function *, Value *> funcNameStr;
extern std::unordered_map <Function *, int> funcOverlay;
extern std::unordered_map <Function *, std::pair <Value *, Value *>> funcLoadAddr;
extern std::unordered_set<Function *> referredFuncs;




extern void CCC (Module &mod , CallInst * c ,int mgtFlag );

//extern void SetLibraryFunctions();
extern bool isLibraryFunction(Function *);
//extern bool isLibraryFunction(std::string );

extern CallInst * WrapApplicationMainFtn(Module &mod );
extern void ReplaceExitFtnCalls(Module &mod ) ;

extern void CreateWrapToFtnWithStackMgt			(Module & , CallInst * );
extern void CreateWrapToFtnWithCodeMgtStackMgt	(Module & , CallInst * );
extern void CreateWrapToFtnWithCodeMgt			(Module & , CallInst * );

extern void InsertDebugMsg(Module &mod , Function * f );


#endif
