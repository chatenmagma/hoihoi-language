// Generated from /home/chatenmagma/Workspace/hoihoi-language/grammar/HoihoiParser.g4 by ANTLR 4.13.1
import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link HoihoiParser}.
 */
public interface HoihoiParserListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link HoihoiParser#program}.
	 * @param ctx the parse tree
	 */
	void enterProgram(HoihoiParser.ProgramContext ctx);
	/**
	 * Exit a parse tree produced by {@link HoihoiParser#program}.
	 * @param ctx the parse tree
	 */
	void exitProgram(HoihoiParser.ProgramContext ctx);
	/**
	 * Enter a parse tree produced by {@link HoihoiParser#stmt}.
	 * @param ctx the parse tree
	 */
	void enterStmt(HoihoiParser.StmtContext ctx);
	/**
	 * Exit a parse tree produced by {@link HoihoiParser#stmt}.
	 * @param ctx the parse tree
	 */
	void exitStmt(HoihoiParser.StmtContext ctx);
	/**
	 * Enter a parse tree produced by {@link HoihoiParser#simpleStmt}.
	 * @param ctx the parse tree
	 */
	void enterSimpleStmt(HoihoiParser.SimpleStmtContext ctx);
	/**
	 * Exit a parse tree produced by {@link HoihoiParser#simpleStmt}.
	 * @param ctx the parse tree
	 */
	void exitSimpleStmt(HoihoiParser.SimpleStmtContext ctx);
	/**
	 * Enter a parse tree produced by {@link HoihoiParser#blockStmt}.
	 * @param ctx the parse tree
	 */
	void enterBlockStmt(HoihoiParser.BlockStmtContext ctx);
	/**
	 * Exit a parse tree produced by {@link HoihoiParser#blockStmt}.
	 * @param ctx the parse tree
	 */
	void exitBlockStmt(HoihoiParser.BlockStmtContext ctx);
	/**
	 * Enter a parse tree produced by {@link HoihoiParser#ifStmt}.
	 * @param ctx the parse tree
	 */
	void enterIfStmt(HoihoiParser.IfStmtContext ctx);
	/**
	 * Exit a parse tree produced by {@link HoihoiParser#ifStmt}.
	 * @param ctx the parse tree
	 */
	void exitIfStmt(HoihoiParser.IfStmtContext ctx);
	/**
	 * Enter a parse tree produced by {@link HoihoiParser#elif}.
	 * @param ctx the parse tree
	 */
	void enterElif(HoihoiParser.ElifContext ctx);
	/**
	 * Exit a parse tree produced by {@link HoihoiParser#elif}.
	 * @param ctx the parse tree
	 */
	void exitElif(HoihoiParser.ElifContext ctx);
	/**
	 * Enter a parse tree produced by {@link HoihoiParser#else}.
	 * @param ctx the parse tree
	 */
	void enterElse(HoihoiParser.ElseContext ctx);
	/**
	 * Exit a parse tree produced by {@link HoihoiParser#else}.
	 * @param ctx the parse tree
	 */
	void exitElse(HoihoiParser.ElseContext ctx);
	/**
	 * Enter a parse tree produced by {@link HoihoiParser#whileStmt}.
	 * @param ctx the parse tree
	 */
	void enterWhileStmt(HoihoiParser.WhileStmtContext ctx);
	/**
	 * Exit a parse tree produced by {@link HoihoiParser#whileStmt}.
	 * @param ctx the parse tree
	 */
	void exitWhileStmt(HoihoiParser.WhileStmtContext ctx);
	/**
	 * Enter a parse tree produced by {@link HoihoiParser#funStmt}.
	 * @param ctx the parse tree
	 */
	void enterFunStmt(HoihoiParser.FunStmtContext ctx);
	/**
	 * Exit a parse tree produced by {@link HoihoiParser#funStmt}.
	 * @param ctx the parse tree
	 */
	void exitFunStmt(HoihoiParser.FunStmtContext ctx);
	/**
	 * Enter a parse tree produced by {@link HoihoiParser#args}.
	 * @param ctx the parse tree
	 */
	void enterArgs(HoihoiParser.ArgsContext ctx);
	/**
	 * Exit a parse tree produced by {@link HoihoiParser#args}.
	 * @param ctx the parse tree
	 */
	void exitArgs(HoihoiParser.ArgsContext ctx);
	/**
	 * Enter a parse tree produced by {@link HoihoiParser#suite}.
	 * @param ctx the parse tree
	 */
	void enterSuite(HoihoiParser.SuiteContext ctx);
	/**
	 * Exit a parse tree produced by {@link HoihoiParser#suite}.
	 * @param ctx the parse tree
	 */
	void exitSuite(HoihoiParser.SuiteContext ctx);
	/**
	 * Enter a parse tree produced by {@link HoihoiParser#assign}.
	 * @param ctx the parse tree
	 */
	void enterAssign(HoihoiParser.AssignContext ctx);
	/**
	 * Exit a parse tree produced by {@link HoihoiParser#assign}.
	 * @param ctx the parse tree
	 */
	void exitAssign(HoihoiParser.AssignContext ctx);
	/**
	 * Enter a parse tree produced by {@link HoihoiParser#objectType}.
	 * @param ctx the parse tree
	 */
	void enterObjectType(HoihoiParser.ObjectTypeContext ctx);
	/**
	 * Exit a parse tree produced by {@link HoihoiParser#objectType}.
	 * @param ctx the parse tree
	 */
	void exitObjectType(HoihoiParser.ObjectTypeContext ctx);
	/**
	 * Enter a parse tree produced by {@link HoihoiParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterExpr(HoihoiParser.ExprContext ctx);
	/**
	 * Exit a parse tree produced by {@link HoihoiParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitExpr(HoihoiParser.ExprContext ctx);
	/**
	 * Enter a parse tree produced by {@link HoihoiParser#or}.
	 * @param ctx the parse tree
	 */
	void enterOr(HoihoiParser.OrContext ctx);
	/**
	 * Exit a parse tree produced by {@link HoihoiParser#or}.
	 * @param ctx the parse tree
	 */
	void exitOr(HoihoiParser.OrContext ctx);
	/**
	 * Enter a parse tree produced by {@link HoihoiParser#and}.
	 * @param ctx the parse tree
	 */
	void enterAnd(HoihoiParser.AndContext ctx);
	/**
	 * Exit a parse tree produced by {@link HoihoiParser#and}.
	 * @param ctx the parse tree
	 */
	void exitAnd(HoihoiParser.AndContext ctx);
	/**
	 * Enter a parse tree produced by {@link HoihoiParser#comparaision}.
	 * @param ctx the parse tree
	 */
	void enterComparaision(HoihoiParser.ComparaisionContext ctx);
	/**
	 * Exit a parse tree produced by {@link HoihoiParser#comparaision}.
	 * @param ctx the parse tree
	 */
	void exitComparaision(HoihoiParser.ComparaisionContext ctx);
	/**
	 * Enter a parse tree produced by {@link HoihoiParser#addition}.
	 * @param ctx the parse tree
	 */
	void enterAddition(HoihoiParser.AdditionContext ctx);
	/**
	 * Exit a parse tree produced by {@link HoihoiParser#addition}.
	 * @param ctx the parse tree
	 */
	void exitAddition(HoihoiParser.AdditionContext ctx);
	/**
	 * Enter a parse tree produced by {@link HoihoiParser#multiplication}.
	 * @param ctx the parse tree
	 */
	void enterMultiplication(HoihoiParser.MultiplicationContext ctx);
	/**
	 * Exit a parse tree produced by {@link HoihoiParser#multiplication}.
	 * @param ctx the parse tree
	 */
	void exitMultiplication(HoihoiParser.MultiplicationContext ctx);
	/**
	 * Enter a parse tree produced by {@link HoihoiParser#primary}.
	 * @param ctx the parse tree
	 */
	void enterPrimary(HoihoiParser.PrimaryContext ctx);
	/**
	 * Exit a parse tree produced by {@link HoihoiParser#primary}.
	 * @param ctx the parse tree
	 */
	void exitPrimary(HoihoiParser.PrimaryContext ctx);
	/**
	 * Enter a parse tree produced by {@link HoihoiParser#clusterLiteral}.
	 * @param ctx the parse tree
	 */
	void enterClusterLiteral(HoihoiParser.ClusterLiteralContext ctx);
	/**
	 * Exit a parse tree produced by {@link HoihoiParser#clusterLiteral}.
	 * @param ctx the parse tree
	 */
	void exitClusterLiteral(HoihoiParser.ClusterLiteralContext ctx);
	/**
	 * Enter a parse tree produced by {@link HoihoiParser#attribute}.
	 * @param ctx the parse tree
	 */
	void enterAttribute(HoihoiParser.AttributeContext ctx);
	/**
	 * Exit a parse tree produced by {@link HoihoiParser#attribute}.
	 * @param ctx the parse tree
	 */
	void exitAttribute(HoihoiParser.AttributeContext ctx);
	/**
	 * Enter a parse tree produced by {@link HoihoiParser#fun}.
	 * @param ctx the parse tree
	 */
	void enterFun(HoihoiParser.FunContext ctx);
	/**
	 * Exit a parse tree produced by {@link HoihoiParser#fun}.
	 * @param ctx the parse tree
	 */
	void exitFun(HoihoiParser.FunContext ctx);
	/**
	 * Enter a parse tree produced by {@link HoihoiParser#primitive}.
	 * @param ctx the parse tree
	 */
	void enterPrimitive(HoihoiParser.PrimitiveContext ctx);
	/**
	 * Exit a parse tree produced by {@link HoihoiParser#primitive}.
	 * @param ctx the parse tree
	 */
	void exitPrimitive(HoihoiParser.PrimitiveContext ctx);
}