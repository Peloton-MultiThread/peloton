//===----------------------------------------------------------------------===//
//
//                         Peloton
//
// negation_translator.cpp
//
// Identification: src/codegen/negation_translator.cpp
//
// Copyright (c) 2015-17, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#include "codegen/negation_translator.h"

#include "codegen/type/type_system.h"
#include "expression/operator_expression.h"

namespace peloton {
namespace codegen {

// Constructor
NegationTranslator::NegationTranslator(
    const expression::OperatorUnaryMinusExpression &unary_minus_expression,
    CompilationContext &ctx)
    : ExpressionTranslator(unary_minus_expression, ctx) {
  PL_ASSERT(unary_minus_expression.GetChildrenSize() == 1);
}

Value NegationTranslator::DeriveValue(CodeGen &codegen,
                                      RowBatch::Row &row) const {
  const auto &negation_expr =
      GetExpressionAs<expression::OperatorUnaryMinusExpression>();
  Value child_value = row.DeriveValue(codegen, *negation_expr.GetChild(0));
  return child_value.CallUnaryOp(codegen, OperatorId::Negation);
}

}  // namespace codegen
}  // namespace peloton