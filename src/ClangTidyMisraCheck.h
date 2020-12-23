//===--- ClangTidyMisraCheck.h - clang-tidy-misra ---------------*- C++ -*-===//
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef CLANG_TIDY_MISRA_CHECK_H
#define CLANG_TIDY_MISRA_CHECK_H

#include "../../ClangTidy.h"
#include <string>

namespace clang {
class CompilerInstance;
namespace tidy {
namespace misra {

class ClangTidyMisraCheck : public ClangTidyCheck {
public:
  ClangTidyMisraCheck(StringRef CheckName, ClangTidyContext *Context);

  virtual void registerPPCallbacks(CompilerInstance &Compiler) override final;

  virtual void
  check(const ast_matchers::MatchFinder::MatchResult &Result) override final;

  virtual void storeOptions(ClangTidyOptions::OptionMap &Opts) override;

  /// \brief A simplified version of ClangTidyCheck::diag.
  void diag(SourceLocation Loc,
            DiagnosticIDs::Level Level = DiagnosticIDs::Warning);

  /// \brief Check if the element at \c loc should be ignored. Compiler-built-in
  /// or command-line-specified code most likely should not be checked. Also,
  /// system headers might have to be excluded as well.
  /// \param loc Location to evaluate.
  /// \return True if \c loc should be ignored (not checked), false if not.
  bool isIgnored(clang::SourceLocation loc);

protected:
  virtual void registerPPCallbacksImpl();
  virtual void checkImpl(const ast_matchers::MatchFinder::MatchResult &Result);

  bool isC() const;
  bool isCPlusPlus() const;

  /// \brief Check if \c loc is a built in, e.g. defined by the compiler itself.
  /// \param loc Location within the translation unit to be tested.
  /// \return True if \c loc is within a built-in, false if not.
  bool isBuiltIn(clang::SourceLocation loc) const;

  /// \brief Check whether or not \c loc has been specified at the command line.
  /// For example, passing -DMY_MACRO_VALUE=36 to the Clang would cause the
  /// return value for the \c loc value of MY_MACRO_VALUE to be true.
  /// \param loc Location within the translation unit to be tested.
  /// \return True if \c loc was defined at the command line, false if not.
  bool isCommandLine(clang::SourceLocation loc);

  /// Return the current AST context.
  clang::ASTContext &getASTContext() const;

  /// Return the current preprocessor.
  clang::Preprocessor &getPreprocessor() const;

  /// Return the current compiler instance.
  CompilerInstance &getCI() const;

  /// \brief Check if this checker is enabled.
  ///
  /// The following enables all MISRA C++ 2008 checks:
  /// \code
  /// clang-tidy -checks=misra-cpp2008* ...
  /// \endcode
  bool checkerIsActive() const;

  /// Return the text of the token at \p start.
  std::string srcLocToTokenString(const SourceLocation start);

private:
  const std::string CheckName;
  CompilerInstance *CI;
  const bool IgnoreInvalidLocations;
  const bool IgnoreBuiltInLocations;
  const bool IgnoreCommandLineLocations;
};

} // namespace misra
} // namespace tidy
} // namespace clang

#endif // CLANG_TIDY_MISRA_CHECK_H
