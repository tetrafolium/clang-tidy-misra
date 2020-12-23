//===--- 27-0-1.cpp - clang-tidy-misra ------------------------------------===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "27-0-1.h"
#include "rules/common/BannedInclude.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Lex/Preprocessor.h"

namespace clang {
namespace tidy {
namespace misra {
namespace cpp2008 {

Rule_27_0_1::Rule_27_0_1(llvm::StringRef Name, ClangTidyContext *Context)
	: ClangTidyMisraCheck(Name, Context) {
}

void Rule_27_0_1::registerPPCallbacksImpl() {
	using BannedIncludePPCallback = common::BannedInclude<Rule_27_0_1>;
	getPreprocessor().addPPCallbacks(::llvm::make_unique<BannedIncludePPCallback>(
						 *this, BannedIncludePPCallback::StringSet{"cstdio"}));
}

} // namespace cpp2008
} // namespace misra
} // namespace tidy
} // namespace clang
