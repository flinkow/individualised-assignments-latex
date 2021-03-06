#include "exprrep.hpp"

#include <utility>

symcomp::ExprRep::ExprRep(std::string basic, std::string laTeX) : Basic(std::move(basic)), LaTeX(std::move(laTeX))
{
}

symcomp::ExprRep::ExprRep(const std::string& basic)
{
    *this = ExprRep(symcomp::util::StringToSymEngineExpression(basic));
}

symcomp::ExprRep::ExprRep(const SymEngine::Expression& expression)
{
    std::ostringstream oss;
    oss << expression;

    auto basic = oss.str();

    oss.str("");
    oss.clear();

    oss << SymEngine::latex(expression);

    auto laTeX = oss.str();

    *this = ExprRep(basic, laTeX);
}

symcomp::ExprRep::ExprRep(const SymEngine::MatrixBase &matrix)
{
    *this = ExprRep(symcomp::util::MatrixToBasic(matrix), symcomp::util::MatrixToLaTeX(matrix));
}

int symcomp::ExprRep::ReturnToLua(gsl::not_null<lua_State *> L) const
{
    lua_newtable(L);                        // table @-1
    lua_pushstring(L, this->Basic.c_str()); // table @-2, string @-1
    lua_rawseti(L, -2, 1);                  // basic is table[1]
    lua_pushstring(L, this->LaTeX.c_str()); // table @-2, string @-1
    lua_rawseti(L, -2, 2);                  // laTeX is table[2]

    return 1; // one return value (a table)
}

int symcomp::ReturnExprRepVectorToLua(gsl::not_null<lua_State *> L, const symcomp::ExprRepCollection& collection)
{
    lua_newtable(L); // vector @-1

    int i = 1;

    for (auto& value : collection)
    {
        value.ReturnToLua(L); // table @-1, vector @-2
        lua_rawseti(L, -2, i++);
    }

    return 1;
}
