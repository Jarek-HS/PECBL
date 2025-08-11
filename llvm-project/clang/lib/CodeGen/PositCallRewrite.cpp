//===--- PositCallRewrite.cpp - Rewrite posit builtin calls -*- C++ -*-===//

#include "PositCallRewrite.h"
#include "CodeGenFunction.h"
#include "clang/AST/Expr.h"
#include "clang/AST/Decl.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/raw_ostream.h"

using namespace clang;
using namespace CodeGen;

namespace {

unsigned getPrintfFormatIndex(StringRef Name) {
  if (Name == "printf" || Name == "vprintf") return 0;
  if (Name == "fprintf" || Name == "vfprintf") return 1;
  if (Name == "sprintf" || Name == "vsprintf") return 1;
  if (Name == "snprintf" || Name == "vsnprintf") return 2;
  return 0;
}

llvm::FunctionCallee getPosit32ToLDFn(CodeGenFunction &CGF) {
  llvm::Module &M = CGF.CGM.getModule();
  llvm::LLVMContext &Ctx = M.getContext();
  llvm::Type *LDoubleTy = CGF.ConvertType(CGF.getContext().LongDoubleTy);
  llvm::Type *FloatTy = llvm::Type::getFloatTy(Ctx);
  return M.getOrInsertFunction("posit32_to_LD", LDoubleTy, FloatTy);
}
llvm::FunctionCallee getLDFnToPosit32Fn(CodeGenFunction &CGF) {
  llvm::Module &M = CGF.CGM.getModule();
  llvm::LLVMContext &Ctx = M.getContext();
  llvm::Type *LDoubleTy = CGF.ConvertType(CGF.getContext().LongDoubleTy);
  llvm::Type *FloatTy = llvm::Type::getFloatTy(Ctx);
  return M.getOrInsertFunction("LD_to_posit32", FloatTy, LDoubleTy);
}

llvm::FunctionCallee getPosit32ToDoubleFn(CodeGenFunction &CGF) {
  llvm::Module &M = CGF.CGM.getModule();
  llvm::LLVMContext &Ctx = M.getContext();
  llvm::Type *FloatTy = llvm::Type::getFloatTy(Ctx);
  llvm::Type *DoubleTy = llvm::Type::getDoubleTy(Ctx);
  return M.getOrInsertFunction("posit32_to_double", DoubleTy, FloatTy);
}

llvm::FunctionCallee getDoubleToPosit32Fn(CodeGenFunction &CGF) {
  llvm::Module &M = CGF.CGM.getModule();
  llvm::LLVMContext &Ctx = M.getContext();
  llvm::Type *FloatTy = llvm::Type::getFloatTy(Ctx);
  llvm::Type *DoubleTy = llvm::Type::getDoubleTy(Ctx);
  return M.getOrInsertFunction("double_to_posit32", FloatTy, DoubleTy);
}

llvm::FunctionCallee getPositToLDoubleFn(CodeGenFunction &CGF) {
  llvm::Module &M = CGF.CGM.getModule();
  llvm::LLVMContext &Ctx = M.getContext();
  llvm::Type *LDoubleTy = CGF.ConvertType(CGF.getContext().LongDoubleTy);
  llvm::Type *DoubleTy = llvm::Type::getDoubleTy(Ctx);
  return M.getOrInsertFunction("posit64_to_LD", LDoubleTy, DoubleTy);
}

llvm::FunctionCallee getLDoubleToPositFn(CodeGenFunction &CGF) {
  llvm::Module &M = CGF.CGM.getModule();
  llvm::LLVMContext &Ctx = M.getContext();
  llvm::Type *LDoubleTy = CGF.ConvertType(CGF.getContext().LongDoubleTy);
  llvm::Type *DoubleTy = llvm::Type::getDoubleTy(Ctx);
  return M.getOrInsertFunction("LD_to_posit64", DoubleTy, LDoubleTy);
}

} // end anonymous namespace

namespace clang {
namespace CodeGen {
  #define DEFINE_UNARY_FLOAT_FN(NAME, RET_TYPE) \
  llvm::Function *getOrDeclare##NAME(CodeGenFunction &CGF) { \
    llvm::Module &M = CGF.CGM.getModule(); \
    llvm::LLVMContext &Ctx = M.getContext(); \
    llvm::Type *Ty = RET_TYPE; \
    llvm::FunctionType *FT = llvm::FunctionType::get(Ty, {Ty}, false); \
    if (llvm::Function *Old = M.getFunction(#NAME)) { \
      if (Old->getFunctionType() != FT) \
        Old->eraseFromParent(); \
      else \
        return Old; \
    } \
    llvm::Function *NewF = llvm::Function::Create(FT, llvm::Function::ExternalLinkage, #NAME, &M); \
    NewF->setCallingConv(llvm::CallingConv::C); \
    return NewF; \
  }
  
  #define DEFINE_BINARY_FLOAT_FN(NAME, RET_TYPE) \
  llvm::Function *getOrDeclare##NAME(CodeGenFunction &CGF) { \
    llvm::Module &M = CGF.CGM.getModule(); \
    llvm::LLVMContext &Ctx = M.getContext(); \
    llvm::Type *Ty = RET_TYPE; \
    llvm::FunctionType *FT = llvm::FunctionType::get(Ty, {Ty, Ty}, false); \
    if (llvm::Function *Old = M.getFunction(#NAME)) { \
      if (Old->getFunctionType() != FT) \
        Old->eraseFromParent(); \
      else \
        return Old; \
    } \
    llvm::Function *NewF = llvm::Function::Create(FT, llvm::Function::ExternalLinkage, #NAME, &M); \
    NewF->setCallingConv(llvm::CallingConv::C); \
    return NewF; \
  }
  
  #define DEFINE_TERNARY_FLOAT_FN(NAME, RET_TYPE) \
  llvm::Function *getOrDeclare##NAME(CodeGenFunction &CGF) { \
    llvm::Module &M = CGF.CGM.getModule(); \
    llvm::LLVMContext &Ctx = M.getContext(); \
    llvm::Type *Ty = RET_TYPE; \
    llvm::FunctionType *FT = llvm::FunctionType::get(Ty, {Ty, Ty, Ty}, false); \
    if (llvm::Function *Old = M.getFunction(#NAME)) { \
      if (Old->getFunctionType() != FT) \
        Old->eraseFromParent(); \
      else \
        return Old; \
    } \
    llvm::Function *NewF = llvm::Function::Create(FT, llvm::Function::ExternalLinkage, #NAME, &M); \
    NewF->setCallingConv(llvm::CallingConv::C); \
    return NewF; \
  }
  
  // Trigonometric
  DEFINE_UNARY_FLOAT_FN(sinl, CGF.ConvertType(CGF.getContext().LongDoubleTy))
  DEFINE_UNARY_FLOAT_FN(sin, llvm::Type::getDoubleTy(Ctx))
  DEFINE_UNARY_FLOAT_FN(cosl, CGF.ConvertType(CGF.getContext().LongDoubleTy))
  DEFINE_UNARY_FLOAT_FN(cos, llvm::Type::getDoubleTy(Ctx))
  DEFINE_UNARY_FLOAT_FN(tanl, CGF.ConvertType(CGF.getContext().LongDoubleTy))
  DEFINE_UNARY_FLOAT_FN(tan, llvm::Type::getDoubleTy(Ctx))
  DEFINE_UNARY_FLOAT_FN(asinl, CGF.ConvertType(CGF.getContext().LongDoubleTy))
  DEFINE_UNARY_FLOAT_FN(asin, llvm::Type::getDoubleTy(Ctx))
  DEFINE_UNARY_FLOAT_FN(acosl, CGF.ConvertType(CGF.getContext().LongDoubleTy))
  DEFINE_UNARY_FLOAT_FN(acos, llvm::Type::getDoubleTy(Ctx))
  DEFINE_UNARY_FLOAT_FN(atanl, CGF.ConvertType(CGF.getContext().LongDoubleTy))
  DEFINE_UNARY_FLOAT_FN(atan, llvm::Type::getDoubleTy(Ctx))
  DEFINE_BINARY_FLOAT_FN(atan2l, CGF.ConvertType(CGF.getContext().LongDoubleTy))
  DEFINE_BINARY_FLOAT_FN(atan2, llvm::Type::getDoubleTy(Ctx))
  
  // Hyperbolic
  DEFINE_UNARY_FLOAT_FN(sinhl, CGF.ConvertType(CGF.getContext().LongDoubleTy))
  DEFINE_UNARY_FLOAT_FN(sinh, llvm::Type::getDoubleTy(Ctx))
  DEFINE_UNARY_FLOAT_FN(coshl, CGF.ConvertType(CGF.getContext().LongDoubleTy))
  DEFINE_UNARY_FLOAT_FN(cosh, llvm::Type::getDoubleTy(Ctx))
  DEFINE_UNARY_FLOAT_FN(tanhl, CGF.ConvertType(CGF.getContext().LongDoubleTy))
  DEFINE_UNARY_FLOAT_FN(tanh, llvm::Type::getDoubleTy(Ctx))
  DEFINE_UNARY_FLOAT_FN(asinhl, CGF.ConvertType(CGF.getContext().LongDoubleTy))
  DEFINE_UNARY_FLOAT_FN(asinh, llvm::Type::getDoubleTy(Ctx))
  DEFINE_UNARY_FLOAT_FN(acoshl, CGF.ConvertType(CGF.getContext().LongDoubleTy))
  DEFINE_UNARY_FLOAT_FN(acosh, llvm::Type::getDoubleTy(Ctx))
  DEFINE_UNARY_FLOAT_FN(atanhl, CGF.ConvertType(CGF.getContext().LongDoubleTy))
  DEFINE_UNARY_FLOAT_FN(atanh, llvm::Type::getDoubleTy(Ctx))
  
  // Exponential & Log
  DEFINE_UNARY_FLOAT_FN(expl, CGF.ConvertType(CGF.getContext().LongDoubleTy))
  DEFINE_UNARY_FLOAT_FN(exp, llvm::Type::getDoubleTy(Ctx))
  DEFINE_UNARY_FLOAT_FN(logl, CGF.ConvertType(CGF.getContext().LongDoubleTy))
  DEFINE_UNARY_FLOAT_FN(log, llvm::Type::getDoubleTy(Ctx))
  DEFINE_UNARY_FLOAT_FN(log10l, CGF.ConvertType(CGF.getContext().LongDoubleTy))
  DEFINE_UNARY_FLOAT_FN(log10, llvm::Type::getDoubleTy(Ctx))
  DEFINE_UNARY_FLOAT_FN(log1pl, CGF.ConvertType(CGF.getContext().LongDoubleTy))
  DEFINE_UNARY_FLOAT_FN(log1p, llvm::Type::getDoubleTy(Ctx))
  
  // Power
  DEFINE_BINARY_FLOAT_FN(powl, CGF.ConvertType(CGF.getContext().LongDoubleTy))
  DEFINE_BINARY_FLOAT_FN(pow, llvm::Type::getDoubleTy(Ctx))
  DEFINE_UNARY_FLOAT_FN(sqrtl, CGF.ConvertType(CGF.getContext().LongDoubleTy))
  DEFINE_UNARY_FLOAT_FN(sqrt, llvm::Type::getDoubleTy(Ctx))
  
  // Rounding & Absolute
  DEFINE_UNARY_FLOAT_FN(fabsl, CGF.ConvertType(CGF.getContext().LongDoubleTy))
  DEFINE_UNARY_FLOAT_FN(fabs, llvm::Type::getDoubleTy(Ctx))
  DEFINE_UNARY_FLOAT_FN(floorl, CGF.ConvertType(CGF.getContext().LongDoubleTy))
  DEFINE_UNARY_FLOAT_FN(floor, llvm::Type::getDoubleTy(Ctx))
  DEFINE_UNARY_FLOAT_FN(ceill, CGF.ConvertType(CGF.getContext().LongDoubleTy))
  DEFINE_UNARY_FLOAT_FN(ceil, llvm::Type::getDoubleTy(Ctx))
  DEFINE_UNARY_FLOAT_FN(roundl, CGF.ConvertType(CGF.getContext().LongDoubleTy))
  DEFINE_UNARY_FLOAT_FN(round, llvm::Type::getDoubleTy(Ctx))
  DEFINE_UNARY_FLOAT_FN(truncl, CGF.ConvertType(CGF.getContext().LongDoubleTy))
  DEFINE_UNARY_FLOAT_FN(trunc, llvm::Type::getDoubleTy(Ctx))
  
  // Modulo & Fractional
  DEFINE_BINARY_FLOAT_FN(fmodl, CGF.ConvertType(CGF.getContext().LongDoubleTy))
  DEFINE_BINARY_FLOAT_FN(fmod, llvm::Type::getDoubleTy(Ctx))
  DEFINE_BINARY_FLOAT_FN(modfl, CGF.ConvertType(CGF.getContext().LongDoubleTy))
  DEFINE_BINARY_FLOAT_FN(modf, llvm::Type::getDoubleTy(Ctx))
  
  // Misc
  DEFINE_TERNARY_FLOAT_FN(fmal, CGF.ConvertType(CGF.getContext().LongDoubleTy))
  DEFINE_TERNARY_FLOAT_FN(fma, llvm::Type::getDoubleTy(Ctx))
  DEFINE_BINARY_FLOAT_FN(hypotl, CGF.ConvertType(CGF.getContext().LongDoubleTy))
  DEFINE_BINARY_FLOAT_FN(hypot, llvm::Type::getDoubleTy(Ctx))
  DEFINE_UNARY_FLOAT_FN(cbrtl, CGF.ConvertType(CGF.getContext().LongDoubleTy))
  DEFINE_UNARY_FLOAT_FN(cbrt, llvm::Type::getDoubleTy(Ctx))
  
  //
  DEFINE_UNARY_FLOAT_FN(expm1l, CGF.ConvertType(CGF.getContext().LongDoubleTy))
  DEFINE_UNARY_FLOAT_FN(expm1, llvm::Type::getDoubleTy(Ctx))
  DEFINE_BINARY_FLOAT_FN(remainderl, CGF.ConvertType(CGF.getContext().LongDoubleTy))
  DEFINE_BINARY_FLOAT_FN(remainder, llvm::Type::getDoubleTy(Ctx))
  DEFINE_BINARY_FLOAT_FN(remquol, CGF.ConvertType(CGF.getContext().LongDoubleTy))
  DEFINE_BINARY_FLOAT_FN(remquo, llvm::Type::getDoubleTy(Ctx))
  DEFINE_BINARY_FLOAT_FN(copysignl, CGF.ConvertType(CGF.getContext().LongDoubleTy))
  DEFINE_BINARY_FLOAT_FN(copysign, llvm::Type::getDoubleTy(Ctx))
  DEFINE_UNARY_FLOAT_FN(nearbyintl, CGF.ConvertType(CGF.getContext().LongDoubleTy))
  DEFINE_UNARY_FLOAT_FN(nearbyint, llvm::Type::getDoubleTy(Ctx))
  DEFINE_UNARY_FLOAT_FN(rint, CGF.ConvertType(CGF.getContext().LongDoubleTy))
  DEFINE_UNARY_FLOAT_FN(rintl, CGF.ConvertType(CGF.getContext().LongDoubleTy))
  DEFINE_UNARY_FLOAT_FN(log2, CGF.ConvertType(CGF.getContext().LongDoubleTy))
  DEFINE_UNARY_FLOAT_FN(log2l, CGF.ConvertType(CGF.getContext().LongDoubleTy))
  DEFINE_BINARY_FLOAT_FN(nextafter, CGF.ConvertType(CGF.getContext().LongDoubleTy))
  DEFINE_BINARY_FLOAT_FN(nextafterl, CGF.ConvertType(CGF.getContext().LongDoubleTy))
  DEFINE_BINARY_FLOAT_FN(frexpl, CGF.ConvertType(CGF.getContext().LongDoubleTy))
  DEFINE_BINARY_FLOAT_FN(frexp, llvm::Type::getDoubleTy(Ctx))
  DEFINE_BINARY_FLOAT_FN(ldexpl, CGF.ConvertType(CGF.getContext().LongDoubleTy))
  DEFINE_BINARY_FLOAT_FN(ldexp, llvm::Type::getDoubleTy(Ctx))
  DEFINE_BINARY_FLOAT_FN(scalbnl, CGF.ConvertType(CGF.getContext().LongDoubleTy))
  DEFINE_BINARY_FLOAT_FN(scalbn, llvm::Type::getDoubleTy(Ctx))
  DEFINE_UNARY_FLOAT_FN(tgammal, CGF.ConvertType(CGF.getContext().LongDoubleTy))
  DEFINE_UNARY_FLOAT_FN(tgamma, llvm::Type::getDoubleTy(Ctx))
  DEFINE_UNARY_FLOAT_FN(lgammal, CGF.ConvertType(CGF.getContext().LongDoubleTy))
  DEFINE_UNARY_FLOAT_FN(lgamma, llvm::Type::getDoubleTy(Ctx))
  DEFINE_UNARY_FLOAT_FN(ilogbl, CGF.ConvertType(CGF.getContext().LongDoubleTy))
  DEFINE_UNARY_FLOAT_FN(ilogb, llvm::Type::getDoubleTy(Ctx))
  #undef DEFINE_UNARY_FLOAT_FN
  #undef DEFINE_BINARY_FLOAT_FN
  #undef DEFINE_TERNARY_FLOAT_FN
}
}

namespace clang {
  namespace CodeGen {
llvm::Value *wrapWithPositConversion(llvm::Value *OrigArg, CodeGenFunction &CGF) {
  CGBuilderTy &Builder = CGF.Builder;
  llvm::FunctionCallee ToLDouble = getPositToLDoubleFn(CGF);
  return Builder.CreateCall(ToLDouble, OrigArg, "posit_to_ldouble");
}

llvm::Value *wrapWithPosit32Conversion(llvm::Value *OrigArg, CodeGenFunction &CGF) {
  CGBuilderTy &Builder = CGF.Builder;
  llvm::FunctionCallee ToLDouble = getPosit32ToDoubleFn(CGF);
  return Builder.CreateCall(ToLDouble, OrigArg, "posit32_to_ld");
}

llvm::Value *unwrapFromPositResult(llvm::Value *CallResult, CodeGenFunction &CGF) {
  CGBuilderTy &Builder = CGF.Builder;
  llvm::FunctionCallee ToPosit = getLDoubleToPositFn(CGF);
  return Builder.CreateCall(ToPosit, CallResult, "ldouble_to_posit");
}

llvm::Value *unwrapFromPosit32Result(llvm::Value *CallResult, CodeGenFunction &CGF) {
  CGBuilderTy &Builder = CGF.Builder;
  llvm::FunctionCallee ToPosit = getDoubleToPosit32Fn(CGF);
  return Builder.CreateCall(ToPosit, CallResult, "ld_to_posit32");
}



RValue EmitWrappedPositBuiltinCall(CodeGenFunction &CGF,
                                   const CallExpr *E,
                                   const FunctionDecl *FD,
                                   CGCallee callee,
                                   ReturnValueSlot ReturnValue,
                                   llvm::CallBase **CallOrInvoke) {
  CallArgList CallArgs;
  ASTContext &Ctx = CGF.getContext();
  CodeGenTypes &Types = CGF.CGM.getTypes();
  unsigned FmtIndex;
  // Format string rewrite for printf-style
  
  if (FD) {
    FmtIndex = getPrintfFormatIndex(FD->getName());
  }
bool ModifiedFlag = false;
llvm::Value *NewFmtVal = nullptr;
QualType OrigFmtType;
// 嘗試抓取 format string 並改寫
if (E->getNumArgs() > FmtIndex) {
  const Expr *FmtArg = E->getArg(FmtIndex)->IgnoreParenImpCasts();
  if (const StringLiteral *FmtStr = dyn_cast<StringLiteral>(FmtArg)) {
    std::string Modified = FmtStr->getString().str();
    size_t pos = 0;
    while ((pos = Modified.find('%', pos)) != std::string::npos) {
      size_t next = pos + 1;
      while (next < Modified.size() && strchr("-0+ #0123456789.*", Modified[next])) ++next;

      if (next < Modified.size() && Modified[next] == 'l') {
        if (next + 1 < Modified.size() && strchr("fgea", Modified[next + 1])) {
          Modified[next] = 'L'; // 將 l 改為 L
          ModifiedFlag = true;
          pos = next + 2;
          continue;
        }
      }

      if (next < Modified.size() && strchr("fgea", Modified[next])) {
        Modified.insert(next, "L");
        ModifiedFlag = true;
        pos = next + 2;
      } else {
        pos = next + 1;
      }
    }

    if (ModifiedFlag) {
      llvm::LLVMContext &LLVMCtx = CGF.CGM.getLLVMContext();
      llvm::Constant *NewStrConst = llvm::ConstantDataArray::getString(LLVMCtx, Modified);
      llvm::GlobalVariable *GV = new llvm::GlobalVariable(
          CGF.CGM.getModule(), NewStrConst->getType(), true,
          llvm::GlobalValue::PrivateLinkage, NewStrConst, ".fposit.fmt");
      GV->setUnnamedAddr(llvm::GlobalValue::UnnamedAddr::Global);
      GV->setAlignment(llvm::Align(1));
      llvm::Constant *Zero = llvm::ConstantInt::get(llvm::Type::getInt32Ty(LLVMCtx), 0);
      llvm::Constant *Indices[] = {Zero, Zero};
      llvm::Constant *NewPtr = llvm::ConstantExpr::getGetElementPtr(NewStrConst->getType(), GV, Indices);

      OrigFmtType = E->getArg(FmtIndex)->getType();
      NewFmtVal = llvm::ConstantExpr::getBitCast(NewPtr, CGF.ConvertType(OrigFmtType));
    }
  }
}
// 加入 CallArgs：處理所有參數
for (unsigned i = 0; i < E->getNumArgs(); ++i) {
  QualType QT = E->getArg(i)->getType();
  llvm::Value *Val;

  if (i == FmtIndex && ModifiedFlag) {
    Val = NewFmtVal;
  } else {
    Val = CGF.EmitScalarExpr(E->getArg(i));
  }

  // 如果是 posit-float，進行轉換
  if (CGF.getLangOpts().Fposit) {
    if (QT->isSpecificBuiltinType(BuiltinType::Float)) {
      Val = wrapWithPosit32Conversion(Val, CGF);
      QT = CGF.getContext().DoubleTy;
    } else if (QT->isSpecificBuiltinType(BuiltinType::Double)) {
      Val = wrapWithPositConversion(Val, CGF);
      QT = CGF.getContext().LongDoubleTy;
    }
  }

  // 確保 bitcast 到正確 LLVM type
  llvm::Type *ExpectedTy = CGF.ConvertType(QT);
  if (!Val->getType()->isPointerTy() && Val->getType() != ExpectedTy) {
    Val = CGF.Builder.CreateBitCast(Val, ExpectedTy);
  }

  CallArgs.add(RValue::get(Val), QT);
}

  QualType RetTy = E->getType();
  if (CGF.getLangOpts().Fposit) {
    if (RetTy->isSpecificBuiltinType(BuiltinType::Double)) {
      RetTy = Ctx.LongDoubleTy;
    } else if (RetTy->isSpecificBuiltinType(BuiltinType::Float)) {
      RetTy = Ctx.DoubleTy;
    }
  }

  const FunctionType *FTy = RetTy->isFunctionType()
                                ? RetTy->castAs<FunctionType>()
                                : Ctx.getFunctionType(RetTy, std::nullopt, {})->castAs<FunctionType>();

  FunctionProtoType::ExtProtoInfo EPI;
  EPI.Variadic = true;
  QualType VarargFT = Ctx.getFunctionType(RetTy, std::nullopt, EPI);
  const CGFunctionInfo &CallInfo = Types.arrangeFreeFunctionCall(CallArgs,
      VarargFT->castAs<FunctionType>(), false);

  llvm::Value *CalleeFn = callee.getFunctionPointer();
  llvm::FunctionType *AdjustedFnTy = Types.GetFunctionType(CallInfo);
  llvm::Value *AdjustedCallee = CalleeFn;

  CGCallee Adjusted = CGCallee::forDirect(llvm::FunctionCallee(AdjustedFnTy, AdjustedCallee), callee.getAbstractInfo());
  RValue CallResult = CGF.EmitCall(CallInfo, Adjusted, ReturnValue, CallArgs, CallOrInvoke);

  if (CGF.getLangOpts().Fposit && CallResult.isScalar()) {
    llvm::Value *Val = CallResult.getScalarVal();
    if (!Val) {
      return CallResult;
    }

    if (Val->getType()->isFP128Ty()) {
      if (E->getType()->isSpecificBuiltinType(BuiltinType::Double)){
        llvm::Value *ConvertedResult = unwrapFromPositResult(Val, CGF);
      return RValue::get(ConvertedResult);
      }else if (E->getType()->isSpecificBuiltinType(BuiltinType::LongDouble)){
        return RValue::get(Val);
      }
    } else if (Val->getType()->isDoubleTy() && E->getType()->isSpecificBuiltinType(BuiltinType::Float)) {
      llvm::Value *ConvertedResult = unwrapFromPosit32Result(Val, CGF);
      return RValue::get(ConvertedResult);
    }
  }

  return CallResult;
}


} // namespace CodeGen
} // namespace clang
