//===- PositCallRewrite.h - Posit Call Wrapping Interface -*- C++ -*-===//

#ifndef LLVM_CLANG_CODEGEN_POSITCALLREWRITE_H
#define LLVM_CLANG_CODEGEN_POSITCALLREWRITE_H

#include "clang/AST/Expr.h"
#include "clang/AST/Decl.h"
#include "CodeGenFunction.h"
#include "llvm/IR/Value.h"

namespace clang {
namespace CodeGen {
//===----------------------------------------------------------------------===//
// Posit Trigonometric Function Call Rewriting 16
//===----------------------------------------------------------------------===//
// Rewrite Fabsl/Fabsf
llvm::Function *getOrDeclarefabsl(clang::CodeGen::CodeGenFunction &CGF);
llvm::Function *getOrDeclarefabs(clang::CodeGen::CodeGenFunction &CGF);
// Rewrite Sinl/Sin
llvm::Function *getOrDeclaresinl(clang::CodeGen::CodeGenFunction &CGF);
llvm::Function *getOrDeclaresin(clang::CodeGen::CodeGenFunction &CGF);
// Rewrite Cosl/Cos
llvm::Function *getOrDeclarecosl(clang::CodeGen::CodeGenFunction &CGF);
llvm::Function *getOrDeclarecos(clang::CodeGen::CodeGenFunction &CGF);
// Rewritw Tanl/Tan
llvm::Function *getOrDeclaretanl(clang::CodeGen::CodeGenFunction &CGF);
llvm::Function *getOrDeclaretan(clang::CodeGen::CodeGenFunction &CGF);
// Rewrite Asinl/Asin
llvm::Function *getOrDeclareasinl(clang::CodeGen::CodeGenFunction &CGF);
llvm::Function *getOrDeclareasin(clang::CodeGen::CodeGenFunction &CGF);
// Rewrite Acosl/Acos
llvm::Function *getOrDeclareacosl(clang::CodeGen::CodeGenFunction &CGF);
llvm::Function *getOrDeclareacos(clang::CodeGen::CodeGenFunction &CGF);
// Rewrite Atanl/Atan
llvm::Function *getOrDeclareatanl(clang::CodeGen::CodeGenFunction &CGF);
llvm::Function *getOrDeclareatan(clang::CodeGen::CodeGenFunction &CGF);
// Rewrite Atan2l/Atan2
llvm::Function *getOrDeclareatan2l(clang::CodeGen::CodeGenFunction &CGF);
llvm::Function *getOrDeclareatan2(clang::CodeGen::CodeGenFunction &CGF);
//===----------------------------------------------------------------------===//
//Posit Hyperbolic Function Call Rewriting 14
 //===----------------------------------------------------------------------===//
llvm::Function *getOrDeclaresinhl(clang::CodeGen::CodeGenFunction &CGF);
llvm::Function *getOrDeclaresinh(clang::CodeGen::CodeGenFunction &CGF);
llvm::Function *getOrDeclarecosh(clang::CodeGen::CodeGenFunction &CGF);
llvm::Function *getOrDeclarecoshl(clang::CodeGen::CodeGenFunction &CGF);
llvm::Function *getOrDeclaretanhl(clang::CodeGen::CodeGenFunction &CGF);
llvm::Function *getOrDeclaretanh(clang::CodeGen::CodeGenFunction &CGF);
llvm::Function *getOrDeclareasinhl(clang::CodeGen::CodeGenFunction &CGF);
llvm::Function *getOrDeclareasinh(clang::CodeGen::CodeGenFunction &CGF);
llvm::Function *getOrDeclareacoshl(clang::CodeGen::CodeGenFunction &CGF);
llvm::Function *getOrDeclareacosh(clang::CodeGen::CodeGenFunction &CGF);
llvm::Function *getOrDeclareatanhl(clang::CodeGen::CodeGenFunction &CGF);
llvm::Function *getOrDeclareatanh(clang::CodeGen::CodeGenFunction &CGF);
llvm::Function *getOrDeclareatanhl(clang::CodeGen::CodeGenFunction &CGF);
llvm::Function *getOrDeclareatanh(clang::CodeGen::CodeGenFunction &CGF);
//===----------------------------------------------------------------------===//
//Exponential & Log 10 
//===----------------------------------------------------------------------===//
llvm::Function *getOrDeclareexp(CodeGenFunction &CGF);
llvm::Function *getOrDeclareexpl(CodeGenFunction &CGF);
llvm::Function *getOrDeclarelog(CodeGenFunction &CGF);
llvm::Function *getOrDeclarelogl(CodeGenFunction &CGF);
llvm::Function *getOrDeclarelog10(CodeGenFunction &CGF);
llvm::Function *getOrDeclarelog10l(CodeGenFunction &CGF);
llvm::Function *getOrDeclarelog1p(CodeGenFunction &CGF);
llvm::Function *getOrDeclarelog1pl(CodeGenFunction &CGF);
llvm::Function *getOrDeclareatanh(CodeGenFunction &CGF);
llvm::Function *getOrDeclareatanhl(CodeGenFunction &CGF);
//===----------------------------------------------------------------------===//
//Ｐower 4
//===----------------------------------------------------------------------===//
llvm::Function *getOrDeclarepow(CodeGenFunction &CGF);
llvm::Function *getOrDeclarepowl(CodeGenFunction &CGF);
llvm::Function *getOrDeclaresqrt(CodeGenFunction &CGF);
llvm::Function *getOrDeclaresqrtl(CodeGenFunction &CGF);

//===----------------------------------------------------------------------===//
//Rounding / Absolute8
//===---------------------------------------------------------------------===//
llvm::Function *getOrDeclarefloor(CodeGenFunction &CGF);
llvm::Function *getOrDeclarefloorl(CodeGenFunction &CGF);
llvm::Function *getOrDeclareceil(CodeGenFunction &CGF);
llvm::Function *getOrDeclareceill(CodeGenFunction &CGF);
llvm::Function *getOrDeclareround(CodeGenFunction &CGF);
llvm::Function *getOrDeclareroundl(CodeGenFunction &CGF);
llvm::Function *getOrDeclaretrunc(CodeGenFunction &CGF);
llvm::Function *getOrDeclaretruncl(CodeGenFunction &CGF);
//===----------------------------------------------------------------------===//
//Modulo / Fraction 4
//===---------------------------------------------------------------------===//
llvm::Function *getOrDeclaremodf(CodeGenFunction &CGF);
llvm::Function *getOrDeclaremodfl(CodeGenFunction &CGF);
llvm::Function *getOrDeclarefmod(CodeGenFunction &CGF);
llvm::Function *getOrDeclarefmodl(CodeGenFunction &CGF);
//===----------------------------------------------------------------------===//
//Miscellaneous 38
//===---------------------------------------------------------------------===//
llvm::Function *getOrDeclarefma(CodeGenFunction &CGF);
llvm::Function *getOrDeclarefmal(CodeGenFunction &CGF);
llvm::Function *getOrDeclarehypot(CodeGenFunction &CGF);
llvm::Function *getOrDeclarehypotl(CodeGenFunction &CGF);
llvm::Function *getOrDeclarecbrt(CodeGenFunction &CGF);
llvm::Function *getOrDeclarecbrtl(CodeGenFunction &CGF);
llvm::Function *getOrDeclareexpm1l(CodeGenFunction &CGF);
llvm::Function *getOrDeclareexpm1(CodeGenFunction &CGF);
llvm::Function *getOrDeclareremainderl(CodeGenFunction &CGF);
llvm::Function *getOrDeclareremainder(CodeGenFunction &CGF);
llvm::Function *getOrDeclaredremquo(CodeGenFunction &CGF);
llvm::Function *getOrDeclaredremquol(CodeGenFunction &CGF);
llvm::Function *getOrDeclarecopysignl(CodeGenFunction &CGF);
llvm::Function *getOrDeclarecopysign(CodeGenFunction &CGF);
llvm::Function *getOrDeclarerint(CodeGenFunction &CGF);
llvm::Function *getOrDeclarerintl(CodeGenFunction &CGF);
llvm::Function *getOrDeclarenearbyint(CodeGenFunction &CGF);
llvm::Function *getOrDeclarenearbyintl(CodeGenFunction &CGF);
llvm::Function *getOrDeclareremquo(CodeGenFunction &CGF);
llvm::Function *getOrDeclareremquol(CodeGenFunction &CGF);
llvm::Function *getOrDeclarelog2(CodeGenFunction &CGF);
llvm::Function *getOrDeclarelog2l(CodeGenFunction &CGF);
llvm::Function *getOrDeclarenextafter(CodeGenFunction &CGF);
llvm::Function *getOrDeclarenextafterl(CodeGenFunction &CGF);
llvm::Function *getOrDeclarefrexp(CodeGenFunction &CGF);
llvm::Function *getOrDeclarefrexpl(CodeGenFunction &CGF);
llvm::Function *getOrDeclareldexp(CodeGenFunction &CGF);
llvm::Function *getOrDeclareldexpl(CodeGenFunction &CGF);
llvm::Function *getOrDeclarescalbn(CodeGenFunction &CGF);
llvm::Function *getOrDeclarescalbnl(CodeGenFunction &CGF);
llvm::Function *getOrDeclaretgamma(CodeGenFunction &CGF);
llvm::Function *getOrDeclaretgammal(CodeGenFunction &CGF);
llvm::Function *getOrDeclarelgamma(CodeGenFunction &CGF);
llvm::Function *getOrDeclarelgammal(CodeGenFunction &CGF);
llvm::Function *getOrDeclareilogb(CodeGenFunction &CGF);
llvm::Function *getOrDeclareilogbl(CodeGenFunction &CGF);
llvm::Function *getOrDeclarelog2(CodeGenFunction &CGF);
llvm::Function *getOrDeclarelog2l(CodeGenFunction &CGF);
//===----------------------------------------------------------------------===//
/// Wraps a value with a posit_to_double conversion call.
llvm::Value *wrapWithPositConversion(llvm::Value *OrigArg, CodeGenFunction &CGF);

/// Wraps a value with a posit32_to_double conversion call.
llvm::Value *wrapWithPosit32Conversion(llvm::Value *OrigArg, CodeGenFunction &CGF);

/// Wraps a value with a double_to_posit conversion call.
llvm::Value *unwrapFromPositResult(llvm::Value *CallResult, CodeGenFunction &CGF);

/// Wraps a value with a double_to_posit32 conversion call.
llvm::Value *unwrapFromPositResult32(llvm::Value *CallResult, CodeGenFunction &CGF);

/// Handles wrapping of builtin calls (like printf/fabs) with posit conversion logic.
RValue EmitWrappedPositBuiltinCall(CodeGenFunction &CGF,
                                   const CallExpr *E,
                                   const FunctionDecl *FD,
                                   CGCallee callee,
                                   ReturnValueSlot ReturnValue,
                                   llvm::CallBase **CallOrInvoke);

} // namespace CodeGen
} // namespace clang

#endif // LLVM_CLANG_CODEGEN_POSITCALLREWRITE_H
