// Generated from /home/chatenmagma/Workspace/hoihoi-language/grammar/HoihoiParser.g4 by ANTLR 4.13.1
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast", "CheckReturnValue"})
public class HoihoiParser extends Parser {
	static { RuntimeMetaData.checkVersion("4.13.1", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		INDENT=1, DEDENT=2, IF=3, ELIF=4, ELSE=5, COMPARE=6, CASE=7, RETURN=8, 
		PASS=9, WHILE=10, DEF=11, HIGH=12, NEUTRAL=13, LOW=14, ARROW=15, DOT=16, 
		STAR=17, COMMA=18, SEMI_COLON=19, COLON=20, ASSIGN=21, PLUS=22, MINUS=23, 
		SLASH=24, MODULO=25, LESS_THAN=26, GREATER_THAN=27, PRIMITIVE=28, OR=29, 
		AND=30, NOT=31, EQUAL=32, NOT_EQUAL=33, ADD_ASSIGN=34, SUB_ASSIGN=35, 
		MUL_ASSIGN=36, HEAP=37, HOLE=38, FLAT=39, QUOTE=40, DQUOTE=41, EMPTY=42, 
		THING=43, NUMBER_LITERAL=44, STRING_LITERAL=45, IDENTIFIER=46, OPEN_PAREN=47, 
		CLOSE_PAREN=48, OPEN_BRASE=49, CLOSE_BRASE=50, OPEN_BRACKET=51, CLOSE_BRACKET=52, 
		NEWLINE=53, WS=54, CONTENT=55;
	public static final int
		RULE_program = 0, RULE_stmt = 1, RULE_simpleStmt = 2, RULE_blockStmt = 3, 
		RULE_ifStmt = 4, RULE_elif = 5, RULE_else = 6, RULE_whileStmt = 7, RULE_funStmt = 8, 
		RULE_args = 9, RULE_suite = 10, RULE_assign = 11, RULE_objectType = 12, 
		RULE_expr = 13, RULE_or = 14, RULE_and = 15, RULE_comparaision = 16, RULE_addition = 17, 
		RULE_multiplication = 18, RULE_primary = 19, RULE_clusterLiteral = 20, 
		RULE_attribute = 21, RULE_fun = 22, RULE_primitive = 23;
	private static String[] makeRuleNames() {
		return new String[] {
			"program", "stmt", "simpleStmt", "blockStmt", "ifStmt", "elif", "else", 
			"whileStmt", "funStmt", "args", "suite", "assign", "objectType", "expr", 
			"or", "and", "comparaision", "addition", "multiplication", "primary", 
			"clusterLiteral", "attribute", "fun", "primitive"
		};
	}
	public static final String[] ruleNames = makeRuleNames();

	private static String[] makeLiteralNames() {
		return new String[] {
			null, null, null, "'if'", "'elif'", "'else'", "'compare'", "'case'", 
			"'return'", "'pass'", "'while'", "'def'", "'high'", "'neutral'", "'low'", 
			"'->'", "'.'", "'*'", "','", "';'", "':'", "'='", "'+'", "'-'", "'/'", 
			"'%'", "'<'", "'>'", "'$'", "'or'", "'and'", "'not'", "'=='", "'!='", 
			"'+='", "'-='", "'*='", "'heap'", "'hole'", "'flat'", "'''", "'\"'", 
			"'empty'", "'thing'", null, null, null, "'('", "')'", "'{'", "'}'", "'['", 
			"']'"
		};
	}
	private static final String[] _LITERAL_NAMES = makeLiteralNames();
	private static String[] makeSymbolicNames() {
		return new String[] {
			null, "INDENT", "DEDENT", "IF", "ELIF", "ELSE", "COMPARE", "CASE", "RETURN", 
			"PASS", "WHILE", "DEF", "HIGH", "NEUTRAL", "LOW", "ARROW", "DOT", "STAR", 
			"COMMA", "SEMI_COLON", "COLON", "ASSIGN", "PLUS", "MINUS", "SLASH", "MODULO", 
			"LESS_THAN", "GREATER_THAN", "PRIMITIVE", "OR", "AND", "NOT", "EQUAL", 
			"NOT_EQUAL", "ADD_ASSIGN", "SUB_ASSIGN", "MUL_ASSIGN", "HEAP", "HOLE", 
			"FLAT", "QUOTE", "DQUOTE", "EMPTY", "THING", "NUMBER_LITERAL", "STRING_LITERAL", 
			"IDENTIFIER", "OPEN_PAREN", "CLOSE_PAREN", "OPEN_BRASE", "CLOSE_BRASE", 
			"OPEN_BRACKET", "CLOSE_BRACKET", "NEWLINE", "WS", "CONTENT"
		};
	}
	private static final String[] _SYMBOLIC_NAMES = makeSymbolicNames();
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}

	@Override
	public String getGrammarFileName() { return "HoihoiParser.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }

	public HoihoiParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ProgramContext extends ParserRuleContext {
		public TerminalNode EOF() { return getToken(HoihoiParser.EOF, 0); }
		public List<TerminalNode> NEWLINE() { return getTokens(HoihoiParser.NEWLINE); }
		public TerminalNode NEWLINE(int i) {
			return getToken(HoihoiParser.NEWLINE, i);
		}
		public List<StmtContext> stmt() {
			return getRuleContexts(StmtContext.class);
		}
		public StmtContext stmt(int i) {
			return getRuleContext(StmtContext.class,i);
		}
		public ProgramContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_program; }
	}

	public final ProgramContext program() throws RecognitionException {
		ProgramContext _localctx = new ProgramContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_program);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(51);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,0,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(48);
					match(NEWLINE);
					}
					} 
				}
				setState(53);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,0,_ctx);
			}
			setState(57);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 2520083075202824L) != 0)) {
				{
				{
				setState(54);
				stmt();
				}
				}
				setState(59);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(63);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==NEWLINE) {
				{
				{
				setState(60);
				match(NEWLINE);
				}
				}
				setState(65);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(66);
			match(EOF);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class StmtContext extends ParserRuleContext {
		public SimpleStmtContext simpleStmt() {
			return getRuleContext(SimpleStmtContext.class,0);
		}
		public List<TerminalNode> NEWLINE() { return getTokens(HoihoiParser.NEWLINE); }
		public TerminalNode NEWLINE(int i) {
			return getToken(HoihoiParser.NEWLINE, i);
		}
		public BlockStmtContext blockStmt() {
			return getRuleContext(BlockStmtContext.class,0);
		}
		public StmtContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_stmt; }
	}

	public final StmtContext stmt() throws RecognitionException {
		StmtContext _localctx = new StmtContext(_ctx, getState());
		enterRule(_localctx, 2, RULE_stmt);
		try {
			int _alt;
			setState(75);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case RETURN:
			case PASS:
			case HIGH:
			case NEUTRAL:
			case LOW:
			case MINUS:
			case PRIMITIVE:
			case NOT:
			case EMPTY:
			case NUMBER_LITERAL:
			case STRING_LITERAL:
			case IDENTIFIER:
			case OPEN_PAREN:
			case OPEN_BRACKET:
				enterOuterAlt(_localctx, 1);
				{
				setState(68);
				simpleStmt();
				setState(70); 
				_errHandler.sync(this);
				_alt = 1;
				do {
					switch (_alt) {
					case 1:
						{
						{
						setState(69);
						match(NEWLINE);
						}
						}
						break;
					default:
						throw new NoViableAltException(this);
					}
					setState(72); 
					_errHandler.sync(this);
					_alt = getInterpreter().adaptivePredict(_input,3,_ctx);
				} while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER );
				}
				break;
			case IF:
			case WHILE:
			case DEF:
				enterOuterAlt(_localctx, 2);
				{
				setState(74);
				blockStmt();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class SimpleStmtContext extends ParserRuleContext {
		public AssignContext assign() {
			return getRuleContext(AssignContext.class,0);
		}
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode PASS() { return getToken(HoihoiParser.PASS, 0); }
		public TerminalNode RETURN() { return getToken(HoihoiParser.RETURN, 0); }
		public SimpleStmtContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_simpleStmt; }
	}

	public final SimpleStmtContext simpleStmt() throws RecognitionException {
		SimpleStmtContext _localctx = new SimpleStmtContext(_ctx, getState());
		enterRule(_localctx, 4, RULE_simpleStmt);
		int _la;
		try {
			setState(84);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,6,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(77);
				assign();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(78);
				expr();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(79);
				match(PASS);
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(80);
				match(RETURN);
				setState(82);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if ((((_la) & ~0x3f) == 0 && ((1L << _la) & 2520083075198976L) != 0)) {
					{
					setState(81);
					expr();
					}
				}

				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class BlockStmtContext extends ParserRuleContext {
		public IfStmtContext ifStmt() {
			return getRuleContext(IfStmtContext.class,0);
		}
		public WhileStmtContext whileStmt() {
			return getRuleContext(WhileStmtContext.class,0);
		}
		public FunStmtContext funStmt() {
			return getRuleContext(FunStmtContext.class,0);
		}
		public BlockStmtContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_blockStmt; }
	}

	public final BlockStmtContext blockStmt() throws RecognitionException {
		BlockStmtContext _localctx = new BlockStmtContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_blockStmt);
		try {
			setState(89);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case IF:
				enterOuterAlt(_localctx, 1);
				{
				setState(86);
				ifStmt();
				}
				break;
			case WHILE:
				enterOuterAlt(_localctx, 2);
				{
				setState(87);
				whileStmt();
				}
				break;
			case DEF:
				enterOuterAlt(_localctx, 3);
				{
				setState(88);
				funStmt();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class IfStmtContext extends ParserRuleContext {
		public TerminalNode IF() { return getToken(HoihoiParser.IF, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode COLON() { return getToken(HoihoiParser.COLON, 0); }
		public SuiteContext suite() {
			return getRuleContext(SuiteContext.class,0);
		}
		public List<ElifContext> elif() {
			return getRuleContexts(ElifContext.class);
		}
		public ElifContext elif(int i) {
			return getRuleContext(ElifContext.class,i);
		}
		public ElseContext else_() {
			return getRuleContext(ElseContext.class,0);
		}
		public IfStmtContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_ifStmt; }
	}

	public final IfStmtContext ifStmt() throws RecognitionException {
		IfStmtContext _localctx = new IfStmtContext(_ctx, getState());
		enterRule(_localctx, 8, RULE_ifStmt);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(91);
			match(IF);
			setState(92);
			expr();
			setState(93);
			match(COLON);
			setState(94);
			suite();
			setState(98);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==ELIF) {
				{
				{
				setState(95);
				elif();
				}
				}
				setState(100);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			setState(102);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==ELSE) {
				{
				setState(101);
				else_();
				}
			}

			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ElifContext extends ParserRuleContext {
		public TerminalNode ELIF() { return getToken(HoihoiParser.ELIF, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode COLON() { return getToken(HoihoiParser.COLON, 0); }
		public SuiteContext suite() {
			return getRuleContext(SuiteContext.class,0);
		}
		public ElifContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_elif; }
	}

	public final ElifContext elif() throws RecognitionException {
		ElifContext _localctx = new ElifContext(_ctx, getState());
		enterRule(_localctx, 10, RULE_elif);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(104);
			match(ELIF);
			setState(105);
			expr();
			setState(106);
			match(COLON);
			setState(107);
			suite();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ElseContext extends ParserRuleContext {
		public TerminalNode ELSE() { return getToken(HoihoiParser.ELSE, 0); }
		public TerminalNode COLON() { return getToken(HoihoiParser.COLON, 0); }
		public SuiteContext suite() {
			return getRuleContext(SuiteContext.class,0);
		}
		public ElseContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_else; }
	}

	public final ElseContext else_() throws RecognitionException {
		ElseContext _localctx = new ElseContext(_ctx, getState());
		enterRule(_localctx, 12, RULE_else);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(109);
			match(ELSE);
			setState(110);
			match(COLON);
			setState(111);
			suite();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class WhileStmtContext extends ParserRuleContext {
		public TerminalNode WHILE() { return getToken(HoihoiParser.WHILE, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode COLON() { return getToken(HoihoiParser.COLON, 0); }
		public SuiteContext suite() {
			return getRuleContext(SuiteContext.class,0);
		}
		public WhileStmtContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_whileStmt; }
	}

	public final WhileStmtContext whileStmt() throws RecognitionException {
		WhileStmtContext _localctx = new WhileStmtContext(_ctx, getState());
		enterRule(_localctx, 14, RULE_whileStmt);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(113);
			match(WHILE);
			setState(114);
			expr();
			setState(115);
			match(COLON);
			setState(116);
			suite();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class FunStmtContext extends ParserRuleContext {
		public TerminalNode DEF() { return getToken(HoihoiParser.DEF, 0); }
		public TerminalNode IDENTIFIER() { return getToken(HoihoiParser.IDENTIFIER, 0); }
		public TerminalNode OPEN_PAREN() { return getToken(HoihoiParser.OPEN_PAREN, 0); }
		public TerminalNode CLOSE_PAREN() { return getToken(HoihoiParser.CLOSE_PAREN, 0); }
		public TerminalNode COLON() { return getToken(HoihoiParser.COLON, 0); }
		public SuiteContext suite() {
			return getRuleContext(SuiteContext.class,0);
		}
		public ArgsContext args() {
			return getRuleContext(ArgsContext.class,0);
		}
		public TerminalNode ARROW() { return getToken(HoihoiParser.ARROW, 0); }
		public ObjectTypeContext objectType() {
			return getRuleContext(ObjectTypeContext.class,0);
		}
		public FunStmtContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_funStmt; }
	}

	public final FunStmtContext funStmt() throws RecognitionException {
		FunStmtContext _localctx = new FunStmtContext(_ctx, getState());
		enterRule(_localctx, 16, RULE_funStmt);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(118);
			match(DEF);
			setState(119);
			match(IDENTIFIER);
			setState(120);
			match(OPEN_PAREN);
			setState(122);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==IDENTIFIER) {
				{
				setState(121);
				args();
				}
			}

			setState(124);
			match(CLOSE_PAREN);
			setState(127);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==ARROW) {
				{
				setState(125);
				match(ARROW);
				setState(126);
				objectType();
				}
			}

			setState(129);
			match(COLON);
			setState(130);
			suite();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ArgsContext extends ParserRuleContext {
		public List<TerminalNode> IDENTIFIER() { return getTokens(HoihoiParser.IDENTIFIER); }
		public TerminalNode IDENTIFIER(int i) {
			return getToken(HoihoiParser.IDENTIFIER, i);
		}
		public List<TerminalNode> COMMA() { return getTokens(HoihoiParser.COMMA); }
		public TerminalNode COMMA(int i) {
			return getToken(HoihoiParser.COMMA, i);
		}
		public List<ObjectTypeContext> objectType() {
			return getRuleContexts(ObjectTypeContext.class);
		}
		public ObjectTypeContext objectType(int i) {
			return getRuleContext(ObjectTypeContext.class,i);
		}
		public List<TerminalNode> COLON() { return getTokens(HoihoiParser.COLON); }
		public TerminalNode COLON(int i) {
			return getToken(HoihoiParser.COLON, i);
		}
		public ArgsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_args; }
	}

	public final ArgsContext args() throws RecognitionException {
		ArgsContext _localctx = new ArgsContext(_ctx, getState());
		enterRule(_localctx, 18, RULE_args);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(132);
			match(IDENTIFIER);
			setState(135);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==COMMA) {
				{
				setState(133);
				match(COMMA);
				setState(134);
				objectType();
				}
			}

			setState(145);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==COLON) {
				{
				{
				setState(137);
				match(COLON);
				setState(138);
				match(IDENTIFIER);
				setState(141);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==COMMA) {
					{
					setState(139);
					match(COMMA);
					setState(140);
					objectType();
					}
				}

				}
				}
				setState(147);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class SuiteContext extends ParserRuleContext {
		public TerminalNode NEWLINE() { return getToken(HoihoiParser.NEWLINE, 0); }
		public TerminalNode INDENT() { return getToken(HoihoiParser.INDENT, 0); }
		public TerminalNode DEDENT() { return getToken(HoihoiParser.DEDENT, 0); }
		public List<StmtContext> stmt() {
			return getRuleContexts(StmtContext.class);
		}
		public StmtContext stmt(int i) {
			return getRuleContext(StmtContext.class,i);
		}
		public SuiteContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_suite; }
	}

	public final SuiteContext suite() throws RecognitionException {
		SuiteContext _localctx = new SuiteContext(_ctx, getState());
		enterRule(_localctx, 20, RULE_suite);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(148);
			match(NEWLINE);
			setState(149);
			match(INDENT);
			setState(151); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				{
				setState(150);
				stmt();
				}
				}
				setState(153); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( (((_la) & ~0x3f) == 0 && ((1L << _la) & 2520083075202824L) != 0) );
			setState(155);
			match(DEDENT);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class AssignContext extends ParserRuleContext {
		public TerminalNode IDENTIFIER() { return getToken(HoihoiParser.IDENTIFIER, 0); }
		public TerminalNode ASSIGN() { return getToken(HoihoiParser.ASSIGN, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode COMMA() { return getToken(HoihoiParser.COMMA, 0); }
		public ObjectTypeContext objectType() {
			return getRuleContext(ObjectTypeContext.class,0);
		}
		public TerminalNode ADD_ASSIGN() { return getToken(HoihoiParser.ADD_ASSIGN, 0); }
		public TerminalNode SUB_ASSIGN() { return getToken(HoihoiParser.SUB_ASSIGN, 0); }
		public TerminalNode MUL_ASSIGN() { return getToken(HoihoiParser.MUL_ASSIGN, 0); }
		public AssignContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_assign; }
	}

	public final AssignContext assign() throws RecognitionException {
		AssignContext _localctx = new AssignContext(_ctx, getState());
		enterRule(_localctx, 22, RULE_assign);
		int _la;
		try {
			setState(171);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,18,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(157);
				match(IDENTIFIER);
				setState(160);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==COMMA) {
					{
					setState(158);
					match(COMMA);
					setState(159);
					objectType();
					}
				}

				setState(162);
				match(ASSIGN);
				setState(163);
				expr();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(164);
				match(IDENTIFIER);
				setState(167);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==COMMA) {
					{
					setState(165);
					match(COMMA);
					setState(166);
					objectType();
					}
				}

				setState(169);
				_la = _input.LA(1);
				if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 120259084288L) != 0)) ) {
				_errHandler.recoverInline(this);
				}
				else {
					if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
					_errHandler.reportMatch(this);
					consume();
				}
				setState(170);
				expr();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ObjectTypeContext extends ParserRuleContext {
		public List<TerminalNode> IDENTIFIER() { return getTokens(HoihoiParser.IDENTIFIER); }
		public TerminalNode IDENTIFIER(int i) {
			return getToken(HoihoiParser.IDENTIFIER, i);
		}
		public List<TerminalNode> OR() { return getTokens(HoihoiParser.OR); }
		public TerminalNode OR(int i) {
			return getToken(HoihoiParser.OR, i);
		}
		public TerminalNode THING() { return getToken(HoihoiParser.THING, 0); }
		public ObjectTypeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_objectType; }
	}

	public final ObjectTypeContext objectType() throws RecognitionException {
		ObjectTypeContext _localctx = new ObjectTypeContext(_ctx, getState());
		enterRule(_localctx, 24, RULE_objectType);
		int _la;
		try {
			setState(182);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case IDENTIFIER:
				enterOuterAlt(_localctx, 1);
				{
				setState(173);
				match(IDENTIFIER);
				setState(178);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (_la==OR) {
					{
					{
					setState(174);
					match(OR);
					setState(175);
					match(IDENTIFIER);
					}
					}
					setState(180);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				}
				break;
			case THING:
				enterOuterAlt(_localctx, 2);
				{
				setState(181);
				match(THING);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ExprContext extends ParserRuleContext {
		public OrContext or() {
			return getRuleContext(OrContext.class,0);
		}
		public TerminalNode NOT() { return getToken(HoihoiParser.NOT, 0); }
		public ExprContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expr; }
	}

	public final ExprContext expr() throws RecognitionException {
		ExprContext _localctx = new ExprContext(_ctx, getState());
		enterRule(_localctx, 26, RULE_expr);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(185);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if (_la==NOT) {
				{
				setState(184);
				match(NOT);
				}
			}

			setState(187);
			or();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class OrContext extends ParserRuleContext {
		public List<AndContext> and() {
			return getRuleContexts(AndContext.class);
		}
		public AndContext and(int i) {
			return getRuleContext(AndContext.class,i);
		}
		public List<TerminalNode> OR() { return getTokens(HoihoiParser.OR); }
		public TerminalNode OR(int i) {
			return getToken(HoihoiParser.OR, i);
		}
		public OrContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_or; }
	}

	public final OrContext or() throws RecognitionException {
		OrContext _localctx = new OrContext(_ctx, getState());
		enterRule(_localctx, 28, RULE_or);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(189);
			and();
			setState(194);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==OR) {
				{
				{
				setState(190);
				match(OR);
				setState(191);
				and();
				}
				}
				setState(196);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class AndContext extends ParserRuleContext {
		public List<ComparaisionContext> comparaision() {
			return getRuleContexts(ComparaisionContext.class);
		}
		public ComparaisionContext comparaision(int i) {
			return getRuleContext(ComparaisionContext.class,i);
		}
		public List<TerminalNode> AND() { return getTokens(HoihoiParser.AND); }
		public TerminalNode AND(int i) {
			return getToken(HoihoiParser.AND, i);
		}
		public List<AdditionContext> addition() {
			return getRuleContexts(AdditionContext.class);
		}
		public AdditionContext addition(int i) {
			return getRuleContext(AdditionContext.class,i);
		}
		public AndContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_and; }
	}

	public final AndContext and() throws RecognitionException {
		AndContext _localctx = new AndContext(_ctx, getState());
		enterRule(_localctx, 30, RULE_and);
		int _la;
		try {
			setState(213);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,25,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(197);
				comparaision();
				setState(202);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (_la==AND) {
					{
					{
					setState(198);
					match(AND);
					setState(199);
					comparaision();
					}
					}
					setState(204);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(205);
				addition();
				setState(210);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (_la==AND) {
					{
					{
					setState(206);
					match(AND);
					setState(207);
					addition();
					}
					}
					setState(212);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ComparaisionContext extends ParserRuleContext {
		public List<AdditionContext> addition() {
			return getRuleContexts(AdditionContext.class);
		}
		public AdditionContext addition(int i) {
			return getRuleContext(AdditionContext.class,i);
		}
		public TerminalNode EQUAL() { return getToken(HoihoiParser.EQUAL, 0); }
		public TerminalNode NOT_EQUAL() { return getToken(HoihoiParser.NOT_EQUAL, 0); }
		public TerminalNode LESS_THAN() { return getToken(HoihoiParser.LESS_THAN, 0); }
		public TerminalNode GREATER_THAN() { return getToken(HoihoiParser.GREATER_THAN, 0); }
		public ComparaisionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_comparaision; }
	}

	public final ComparaisionContext comparaision() throws RecognitionException {
		ComparaisionContext _localctx = new ComparaisionContext(_ctx, getState());
		enterRule(_localctx, 32, RULE_comparaision);
		try {
			setState(231);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,26,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(215);
				addition();
				setState(216);
				match(EQUAL);
				setState(217);
				addition();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(219);
				addition();
				setState(220);
				match(NOT_EQUAL);
				setState(221);
				addition();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(223);
				addition();
				setState(224);
				match(LESS_THAN);
				setState(225);
				addition();
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(227);
				addition();
				setState(228);
				match(GREATER_THAN);
				setState(229);
				addition();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class AdditionContext extends ParserRuleContext {
		public List<MultiplicationContext> multiplication() {
			return getRuleContexts(MultiplicationContext.class);
		}
		public MultiplicationContext multiplication(int i) {
			return getRuleContext(MultiplicationContext.class,i);
		}
		public List<TerminalNode> PLUS() { return getTokens(HoihoiParser.PLUS); }
		public TerminalNode PLUS(int i) {
			return getToken(HoihoiParser.PLUS, i);
		}
		public List<TerminalNode> MINUS() { return getTokens(HoihoiParser.MINUS); }
		public TerminalNode MINUS(int i) {
			return getToken(HoihoiParser.MINUS, i);
		}
		public AdditionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_addition; }
	}

	public final AdditionContext addition() throws RecognitionException {
		AdditionContext _localctx = new AdditionContext(_ctx, getState());
		enterRule(_localctx, 34, RULE_addition);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(233);
			multiplication();
			setState(238);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==PLUS || _la==MINUS) {
				{
				{
				setState(234);
				_la = _input.LA(1);
				if ( !(_la==PLUS || _la==MINUS) ) {
				_errHandler.recoverInline(this);
				}
				else {
					if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
					_errHandler.reportMatch(this);
					consume();
				}
				setState(235);
				multiplication();
				}
				}
				setState(240);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class MultiplicationContext extends ParserRuleContext {
		public List<AttributeContext> attribute() {
			return getRuleContexts(AttributeContext.class);
		}
		public AttributeContext attribute(int i) {
			return getRuleContext(AttributeContext.class,i);
		}
		public List<TerminalNode> STAR() { return getTokens(HoihoiParser.STAR); }
		public TerminalNode STAR(int i) {
			return getToken(HoihoiParser.STAR, i);
		}
		public List<TerminalNode> MODULO() { return getTokens(HoihoiParser.MODULO); }
		public TerminalNode MODULO(int i) {
			return getToken(HoihoiParser.MODULO, i);
		}
		public List<TerminalNode> SLASH() { return getTokens(HoihoiParser.SLASH); }
		public TerminalNode SLASH(int i) {
			return getToken(HoihoiParser.SLASH, i);
		}
		public MultiplicationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_multiplication; }
	}

	public final MultiplicationContext multiplication() throws RecognitionException {
		MultiplicationContext _localctx = new MultiplicationContext(_ctx, getState());
		enterRule(_localctx, 36, RULE_multiplication);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(241);
			attribute();
			setState(246);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while ((((_la) & ~0x3f) == 0 && ((1L << _la) & 50462720L) != 0)) {
				{
				{
				setState(242);
				_la = _input.LA(1);
				if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & 50462720L) != 0)) ) {
				_errHandler.recoverInline(this);
				}
				else {
					if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
					_errHandler.reportMatch(this);
					consume();
				}
				setState(243);
				attribute();
				}
				}
				setState(248);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class PrimaryContext extends ParserRuleContext {
		public TerminalNode IDENTIFIER() { return getToken(HoihoiParser.IDENTIFIER, 0); }
		public FunContext fun() {
			return getRuleContext(FunContext.class,0);
		}
		public ClusterLiteralContext clusterLiteral() {
			return getRuleContext(ClusterLiteralContext.class,0);
		}
		public TerminalNode PRIMITIVE() { return getToken(HoihoiParser.PRIMITIVE, 0); }
		public PrimitiveContext primitive() {
			return getRuleContext(PrimitiveContext.class,0);
		}
		public TerminalNode OPEN_PAREN() { return getToken(HoihoiParser.OPEN_PAREN, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode CLOSE_PAREN() { return getToken(HoihoiParser.CLOSE_PAREN, 0); }
		public TerminalNode EMPTY() { return getToken(HoihoiParser.EMPTY, 0); }
		public PrimaryContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_primary; }
	}

	public final PrimaryContext primary() throws RecognitionException {
		PrimaryContext _localctx = new PrimaryContext(_ctx, getState());
		enterRule(_localctx, 38, RULE_primary);
		try {
			setState(259);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,29,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(249);
				match(IDENTIFIER);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(250);
				fun();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(251);
				clusterLiteral();
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(252);
				match(PRIMITIVE);
				setState(253);
				primitive();
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(254);
				match(OPEN_PAREN);
				setState(255);
				expr();
				setState(256);
				match(CLOSE_PAREN);
				}
				break;
			case 6:
				enterOuterAlt(_localctx, 6);
				{
				setState(258);
				match(EMPTY);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class ClusterLiteralContext extends ParserRuleContext {
		public TerminalNode OPEN_BRACKET() { return getToken(HoihoiParser.OPEN_BRACKET, 0); }
		public TerminalNode CLOSE_BRACKET() { return getToken(HoihoiParser.CLOSE_BRACKET, 0); }
		public List<PrimitiveContext> primitive() {
			return getRuleContexts(PrimitiveContext.class);
		}
		public PrimitiveContext primitive(int i) {
			return getRuleContext(PrimitiveContext.class,i);
		}
		public List<TerminalNode> COMMA() { return getTokens(HoihoiParser.COMMA); }
		public TerminalNode COMMA(int i) {
			return getToken(HoihoiParser.COMMA, i);
		}
		public ClusterLiteralContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_clusterLiteral; }
	}

	public final ClusterLiteralContext clusterLiteral() throws RecognitionException {
		ClusterLiteralContext _localctx = new ClusterLiteralContext(_ctx, getState());
		enterRule(_localctx, 40, RULE_clusterLiteral);
		int _la;
		try {
			setState(274);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case OPEN_BRACKET:
				enterOuterAlt(_localctx, 1);
				{
				setState(261);
				match(OPEN_BRACKET);
				setState(270);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if ((((_la) & ~0x3f) == 0 && ((1L << _la) & 52776566550528L) != 0)) {
					{
					setState(262);
					primitive();
					setState(267);
					_errHandler.sync(this);
					_la = _input.LA(1);
					while (_la==COMMA) {
						{
						{
						setState(263);
						match(COMMA);
						setState(264);
						primitive();
						}
						}
						setState(269);
						_errHandler.sync(this);
						_la = _input.LA(1);
					}
					}
				}

				setState(272);
				match(CLOSE_BRACKET);
				}
				break;
			case HIGH:
			case NEUTRAL:
			case LOW:
			case MINUS:
			case NUMBER_LITERAL:
			case STRING_LITERAL:
				enterOuterAlt(_localctx, 2);
				{
				setState(273);
				primitive();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class AttributeContext extends ParserRuleContext {
		public PrimaryContext primary() {
			return getRuleContext(PrimaryContext.class,0);
		}
		public TerminalNode OPEN_BRACKET() { return getToken(HoihoiParser.OPEN_BRACKET, 0); }
		public ExprContext expr() {
			return getRuleContext(ExprContext.class,0);
		}
		public TerminalNode CLOSE_BRACKET() { return getToken(HoihoiParser.CLOSE_BRACKET, 0); }
		public TerminalNode IDENTIFIER() { return getToken(HoihoiParser.IDENTIFIER, 0); }
		public TerminalNode DOT() { return getToken(HoihoiParser.DOT, 0); }
		public TerminalNode COLON() { return getToken(HoihoiParser.COLON, 0); }
		public FunContext fun() {
			return getRuleContext(FunContext.class,0);
		}
		public AttributeContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_attribute; }
	}

	public final AttributeContext attribute() throws RecognitionException {
		AttributeContext _localctx = new AttributeContext(_ctx, getState());
		enterRule(_localctx, 42, RULE_attribute);
		int _la;
		try {
			setState(293);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,36,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(276);
				primary();
				setState(281);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==OPEN_BRACKET) {
					{
					setState(277);
					match(OPEN_BRACKET);
					setState(278);
					expr();
					setState(279);
					match(CLOSE_BRACKET);
					}
				}

				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(283);
				primary();
				setState(286);
				_errHandler.sync(this);
				switch ( getInterpreter().adaptivePredict(_input,34,_ctx) ) {
				case 1:
					{
					setState(284);
					_la = _input.LA(1);
					if ( !(_la==DOT || _la==COLON) ) {
					_errHandler.recoverInline(this);
					}
					else {
						if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
						_errHandler.reportMatch(this);
						consume();
					}
					setState(285);
					match(IDENTIFIER);
					}
					break;
				}
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(288);
				primary();
				setState(291);
				_errHandler.sync(this);
				switch ( getInterpreter().adaptivePredict(_input,35,_ctx) ) {
				case 1:
					{
					setState(289);
					_la = _input.LA(1);
					if ( !(_la==DOT || _la==COLON) ) {
					_errHandler.recoverInline(this);
					}
					else {
						if ( _input.LA(1)==Token.EOF ) matchedEOF = true;
						_errHandler.reportMatch(this);
						consume();
					}
					setState(290);
					fun();
					}
					break;
				}
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class FunContext extends ParserRuleContext {
		public TerminalNode IDENTIFIER() { return getToken(HoihoiParser.IDENTIFIER, 0); }
		public TerminalNode OPEN_PAREN() { return getToken(HoihoiParser.OPEN_PAREN, 0); }
		public TerminalNode CLOSE_PAREN() { return getToken(HoihoiParser.CLOSE_PAREN, 0); }
		public List<ExprContext> expr() {
			return getRuleContexts(ExprContext.class);
		}
		public ExprContext expr(int i) {
			return getRuleContext(ExprContext.class,i);
		}
		public List<TerminalNode> COMMA() { return getTokens(HoihoiParser.COMMA); }
		public TerminalNode COMMA(int i) {
			return getToken(HoihoiParser.COMMA, i);
		}
		public FunContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_fun; }
	}

	public final FunContext fun() throws RecognitionException {
		FunContext _localctx = new FunContext(_ctx, getState());
		enterRule(_localctx, 44, RULE_fun);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(295);
			match(IDENTIFIER);
			setState(296);
			match(OPEN_PAREN);
			setState(305);
			_errHandler.sync(this);
			_la = _input.LA(1);
			if ((((_la) & ~0x3f) == 0 && ((1L << _la) & 2520083075198976L) != 0)) {
				{
				setState(297);
				expr();
				setState(302);
				_errHandler.sync(this);
				_la = _input.LA(1);
				while (_la==COMMA) {
					{
					{
					setState(298);
					match(COMMA);
					setState(299);
					expr();
					}
					}
					setState(304);
					_errHandler.sync(this);
					_la = _input.LA(1);
				}
				}
			}

			setState(307);
			match(CLOSE_PAREN);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	@SuppressWarnings("CheckReturnValue")
	public static class PrimitiveContext extends ParserRuleContext {
		public TerminalNode NUMBER_LITERAL() { return getToken(HoihoiParser.NUMBER_LITERAL, 0); }
		public TerminalNode MINUS() { return getToken(HoihoiParser.MINUS, 0); }
		public TerminalNode STRING_LITERAL() { return getToken(HoihoiParser.STRING_LITERAL, 0); }
		public TerminalNode HIGH() { return getToken(HoihoiParser.HIGH, 0); }
		public TerminalNode NEUTRAL() { return getToken(HoihoiParser.NEUTRAL, 0); }
		public TerminalNode LOW() { return getToken(HoihoiParser.LOW, 0); }
		public PrimitiveContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_primitive; }
	}

	public final PrimitiveContext primitive() throws RecognitionException {
		PrimitiveContext _localctx = new PrimitiveContext(_ctx, getState());
		enterRule(_localctx, 46, RULE_primitive);
		int _la;
		try {
			setState(317);
			_errHandler.sync(this);
			switch (_input.LA(1)) {
			case MINUS:
			case NUMBER_LITERAL:
				enterOuterAlt(_localctx, 1);
				{
				setState(310);
				_errHandler.sync(this);
				_la = _input.LA(1);
				if (_la==MINUS) {
					{
					setState(309);
					match(MINUS);
					}
				}

				setState(312);
				match(NUMBER_LITERAL);
				}
				break;
			case STRING_LITERAL:
				enterOuterAlt(_localctx, 2);
				{
				setState(313);
				match(STRING_LITERAL);
				}
				break;
			case HIGH:
				enterOuterAlt(_localctx, 3);
				{
				setState(314);
				match(HIGH);
				}
				break;
			case NEUTRAL:
				enterOuterAlt(_localctx, 4);
				{
				setState(315);
				match(NEUTRAL);
				}
				break;
			case LOW:
				enterOuterAlt(_localctx, 5);
				{
				setState(316);
				match(LOW);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static final String _serializedATN =
		"\u0004\u00017\u0140\u0002\u0000\u0007\u0000\u0002\u0001\u0007\u0001\u0002"+
		"\u0002\u0007\u0002\u0002\u0003\u0007\u0003\u0002\u0004\u0007\u0004\u0002"+
		"\u0005\u0007\u0005\u0002\u0006\u0007\u0006\u0002\u0007\u0007\u0007\u0002"+
		"\b\u0007\b\u0002\t\u0007\t\u0002\n\u0007\n\u0002\u000b\u0007\u000b\u0002"+
		"\f\u0007\f\u0002\r\u0007\r\u0002\u000e\u0007\u000e\u0002\u000f\u0007\u000f"+
		"\u0002\u0010\u0007\u0010\u0002\u0011\u0007\u0011\u0002\u0012\u0007\u0012"+
		"\u0002\u0013\u0007\u0013\u0002\u0014\u0007\u0014\u0002\u0015\u0007\u0015"+
		"\u0002\u0016\u0007\u0016\u0002\u0017\u0007\u0017\u0001\u0000\u0005\u0000"+
		"2\b\u0000\n\u0000\f\u00005\t\u0000\u0001\u0000\u0005\u00008\b\u0000\n"+
		"\u0000\f\u0000;\t\u0000\u0001\u0000\u0005\u0000>\b\u0000\n\u0000\f\u0000"+
		"A\t\u0000\u0001\u0000\u0001\u0000\u0001\u0001\u0001\u0001\u0004\u0001"+
		"G\b\u0001\u000b\u0001\f\u0001H\u0001\u0001\u0003\u0001L\b\u0001\u0001"+
		"\u0002\u0001\u0002\u0001\u0002\u0001\u0002\u0001\u0002\u0003\u0002S\b"+
		"\u0002\u0003\u0002U\b\u0002\u0001\u0003\u0001\u0003\u0001\u0003\u0003"+
		"\u0003Z\b\u0003\u0001\u0004\u0001\u0004\u0001\u0004\u0001\u0004\u0001"+
		"\u0004\u0005\u0004a\b\u0004\n\u0004\f\u0004d\t\u0004\u0001\u0004\u0003"+
		"\u0004g\b\u0004\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005\u0001"+
		"\u0005\u0001\u0006\u0001\u0006\u0001\u0006\u0001\u0006\u0001\u0007\u0001"+
		"\u0007\u0001\u0007\u0001\u0007\u0001\u0007\u0001\b\u0001\b\u0001\b\u0001"+
		"\b\u0003\b{\b\b\u0001\b\u0001\b\u0001\b\u0003\b\u0080\b\b\u0001\b\u0001"+
		"\b\u0001\b\u0001\t\u0001\t\u0001\t\u0003\t\u0088\b\t\u0001\t\u0001\t\u0001"+
		"\t\u0001\t\u0003\t\u008e\b\t\u0005\t\u0090\b\t\n\t\f\t\u0093\t\t\u0001"+
		"\n\u0001\n\u0001\n\u0004\n\u0098\b\n\u000b\n\f\n\u0099\u0001\n\u0001\n"+
		"\u0001\u000b\u0001\u000b\u0001\u000b\u0003\u000b\u00a1\b\u000b\u0001\u000b"+
		"\u0001\u000b\u0001\u000b\u0001\u000b\u0001\u000b\u0003\u000b\u00a8\b\u000b"+
		"\u0001\u000b\u0001\u000b\u0003\u000b\u00ac\b\u000b\u0001\f\u0001\f\u0001"+
		"\f\u0005\f\u00b1\b\f\n\f\f\f\u00b4\t\f\u0001\f\u0003\f\u00b7\b\f\u0001"+
		"\r\u0003\r\u00ba\b\r\u0001\r\u0001\r\u0001\u000e\u0001\u000e\u0001\u000e"+
		"\u0005\u000e\u00c1\b\u000e\n\u000e\f\u000e\u00c4\t\u000e\u0001\u000f\u0001"+
		"\u000f\u0001\u000f\u0005\u000f\u00c9\b\u000f\n\u000f\f\u000f\u00cc\t\u000f"+
		"\u0001\u000f\u0001\u000f\u0001\u000f\u0005\u000f\u00d1\b\u000f\n\u000f"+
		"\f\u000f\u00d4\t\u000f\u0003\u000f\u00d6\b\u000f\u0001\u0010\u0001\u0010"+
		"\u0001\u0010\u0001\u0010\u0001\u0010\u0001\u0010\u0001\u0010\u0001\u0010"+
		"\u0001\u0010\u0001\u0010\u0001\u0010\u0001\u0010\u0001\u0010\u0001\u0010"+
		"\u0001\u0010\u0001\u0010\u0003\u0010\u00e8\b\u0010\u0001\u0011\u0001\u0011"+
		"\u0001\u0011\u0005\u0011\u00ed\b\u0011\n\u0011\f\u0011\u00f0\t\u0011\u0001"+
		"\u0012\u0001\u0012\u0001\u0012\u0005\u0012\u00f5\b\u0012\n\u0012\f\u0012"+
		"\u00f8\t\u0012\u0001\u0013\u0001\u0013\u0001\u0013\u0001\u0013\u0001\u0013"+
		"\u0001\u0013\u0001\u0013\u0001\u0013\u0001\u0013\u0001\u0013\u0003\u0013"+
		"\u0104\b\u0013\u0001\u0014\u0001\u0014\u0001\u0014\u0001\u0014\u0005\u0014"+
		"\u010a\b\u0014\n\u0014\f\u0014\u010d\t\u0014\u0003\u0014\u010f\b\u0014"+
		"\u0001\u0014\u0001\u0014\u0003\u0014\u0113\b\u0014\u0001\u0015\u0001\u0015"+
		"\u0001\u0015\u0001\u0015\u0001\u0015\u0003\u0015\u011a\b\u0015\u0001\u0015"+
		"\u0001\u0015\u0001\u0015\u0003\u0015\u011f\b\u0015\u0001\u0015\u0001\u0015"+
		"\u0001\u0015\u0003\u0015\u0124\b\u0015\u0003\u0015\u0126\b\u0015\u0001"+
		"\u0016\u0001\u0016\u0001\u0016\u0001\u0016\u0001\u0016\u0005\u0016\u012d"+
		"\b\u0016\n\u0016\f\u0016\u0130\t\u0016\u0003\u0016\u0132\b\u0016\u0001"+
		"\u0016\u0001\u0016\u0001\u0017\u0003\u0017\u0137\b\u0017\u0001\u0017\u0001"+
		"\u0017\u0001\u0017\u0001\u0017\u0001\u0017\u0003\u0017\u013e\b\u0017\u0001"+
		"\u0017\u0000\u0000\u0018\u0000\u0002\u0004\u0006\b\n\f\u000e\u0010\u0012"+
		"\u0014\u0016\u0018\u001a\u001c\u001e \"$&(*,.\u0000\u0004\u0001\u0000"+
		"\"$\u0001\u0000\u0016\u0017\u0002\u0000\u0011\u0011\u0018\u0019\u0002"+
		"\u0000\u0010\u0010\u0014\u0014\u015d\u00003\u0001\u0000\u0000\u0000\u0002"+
		"K\u0001\u0000\u0000\u0000\u0004T\u0001\u0000\u0000\u0000\u0006Y\u0001"+
		"\u0000\u0000\u0000\b[\u0001\u0000\u0000\u0000\nh\u0001\u0000\u0000\u0000"+
		"\fm\u0001\u0000\u0000\u0000\u000eq\u0001\u0000\u0000\u0000\u0010v\u0001"+
		"\u0000\u0000\u0000\u0012\u0084\u0001\u0000\u0000\u0000\u0014\u0094\u0001"+
		"\u0000\u0000\u0000\u0016\u00ab\u0001\u0000\u0000\u0000\u0018\u00b6\u0001"+
		"\u0000\u0000\u0000\u001a\u00b9\u0001\u0000\u0000\u0000\u001c\u00bd\u0001"+
		"\u0000\u0000\u0000\u001e\u00d5\u0001\u0000\u0000\u0000 \u00e7\u0001\u0000"+
		"\u0000\u0000\"\u00e9\u0001\u0000\u0000\u0000$\u00f1\u0001\u0000\u0000"+
		"\u0000&\u0103\u0001\u0000\u0000\u0000(\u0112\u0001\u0000\u0000\u0000*"+
		"\u0125\u0001\u0000\u0000\u0000,\u0127\u0001\u0000\u0000\u0000.\u013d\u0001"+
		"\u0000\u0000\u000002\u00055\u0000\u000010\u0001\u0000\u0000\u000025\u0001"+
		"\u0000\u0000\u000031\u0001\u0000\u0000\u000034\u0001\u0000\u0000\u0000"+
		"49\u0001\u0000\u0000\u000053\u0001\u0000\u0000\u000068\u0003\u0002\u0001"+
		"\u000076\u0001\u0000\u0000\u00008;\u0001\u0000\u0000\u000097\u0001\u0000"+
		"\u0000\u00009:\u0001\u0000\u0000\u0000:?\u0001\u0000\u0000\u0000;9\u0001"+
		"\u0000\u0000\u0000<>\u00055\u0000\u0000=<\u0001\u0000\u0000\u0000>A\u0001"+
		"\u0000\u0000\u0000?=\u0001\u0000\u0000\u0000?@\u0001\u0000\u0000\u0000"+
		"@B\u0001\u0000\u0000\u0000A?\u0001\u0000\u0000\u0000BC\u0005\u0000\u0000"+
		"\u0001C\u0001\u0001\u0000\u0000\u0000DF\u0003\u0004\u0002\u0000EG\u0005"+
		"5\u0000\u0000FE\u0001\u0000\u0000\u0000GH\u0001\u0000\u0000\u0000HF\u0001"+
		"\u0000\u0000\u0000HI\u0001\u0000\u0000\u0000IL\u0001\u0000\u0000\u0000"+
		"JL\u0003\u0006\u0003\u0000KD\u0001\u0000\u0000\u0000KJ\u0001\u0000\u0000"+
		"\u0000L\u0003\u0001\u0000\u0000\u0000MU\u0003\u0016\u000b\u0000NU\u0003"+
		"\u001a\r\u0000OU\u0005\t\u0000\u0000PR\u0005\b\u0000\u0000QS\u0003\u001a"+
		"\r\u0000RQ\u0001\u0000\u0000\u0000RS\u0001\u0000\u0000\u0000SU\u0001\u0000"+
		"\u0000\u0000TM\u0001\u0000\u0000\u0000TN\u0001\u0000\u0000\u0000TO\u0001"+
		"\u0000\u0000\u0000TP\u0001\u0000\u0000\u0000U\u0005\u0001\u0000\u0000"+
		"\u0000VZ\u0003\b\u0004\u0000WZ\u0003\u000e\u0007\u0000XZ\u0003\u0010\b"+
		"\u0000YV\u0001\u0000\u0000\u0000YW\u0001\u0000\u0000\u0000YX\u0001\u0000"+
		"\u0000\u0000Z\u0007\u0001\u0000\u0000\u0000[\\\u0005\u0003\u0000\u0000"+
		"\\]\u0003\u001a\r\u0000]^\u0005\u0014\u0000\u0000^b\u0003\u0014\n\u0000"+
		"_a\u0003\n\u0005\u0000`_\u0001\u0000\u0000\u0000ad\u0001\u0000\u0000\u0000"+
		"b`\u0001\u0000\u0000\u0000bc\u0001\u0000\u0000\u0000cf\u0001\u0000\u0000"+
		"\u0000db\u0001\u0000\u0000\u0000eg\u0003\f\u0006\u0000fe\u0001\u0000\u0000"+
		"\u0000fg\u0001\u0000\u0000\u0000g\t\u0001\u0000\u0000\u0000hi\u0005\u0004"+
		"\u0000\u0000ij\u0003\u001a\r\u0000jk\u0005\u0014\u0000\u0000kl\u0003\u0014"+
		"\n\u0000l\u000b\u0001\u0000\u0000\u0000mn\u0005\u0005\u0000\u0000no\u0005"+
		"\u0014\u0000\u0000op\u0003\u0014\n\u0000p\r\u0001\u0000\u0000\u0000qr"+
		"\u0005\n\u0000\u0000rs\u0003\u001a\r\u0000st\u0005\u0014\u0000\u0000t"+
		"u\u0003\u0014\n\u0000u\u000f\u0001\u0000\u0000\u0000vw\u0005\u000b\u0000"+
		"\u0000wx\u0005.\u0000\u0000xz\u0005/\u0000\u0000y{\u0003\u0012\t\u0000"+
		"zy\u0001\u0000\u0000\u0000z{\u0001\u0000\u0000\u0000{|\u0001\u0000\u0000"+
		"\u0000|\u007f\u00050\u0000\u0000}~\u0005\u000f\u0000\u0000~\u0080\u0003"+
		"\u0018\f\u0000\u007f}\u0001\u0000\u0000\u0000\u007f\u0080\u0001\u0000"+
		"\u0000\u0000\u0080\u0081\u0001\u0000\u0000\u0000\u0081\u0082\u0005\u0014"+
		"\u0000\u0000\u0082\u0083\u0003\u0014\n\u0000\u0083\u0011\u0001\u0000\u0000"+
		"\u0000\u0084\u0087\u0005.\u0000\u0000\u0085\u0086\u0005\u0012\u0000\u0000"+
		"\u0086\u0088\u0003\u0018\f\u0000\u0087\u0085\u0001\u0000\u0000\u0000\u0087"+
		"\u0088\u0001\u0000\u0000\u0000\u0088\u0091\u0001\u0000\u0000\u0000\u0089"+
		"\u008a\u0005\u0014\u0000\u0000\u008a\u008d\u0005.\u0000\u0000\u008b\u008c"+
		"\u0005\u0012\u0000\u0000\u008c\u008e\u0003\u0018\f\u0000\u008d\u008b\u0001"+
		"\u0000\u0000\u0000\u008d\u008e\u0001\u0000\u0000\u0000\u008e\u0090\u0001"+
		"\u0000\u0000\u0000\u008f\u0089\u0001\u0000\u0000\u0000\u0090\u0093\u0001"+
		"\u0000\u0000\u0000\u0091\u008f\u0001\u0000\u0000\u0000\u0091\u0092\u0001"+
		"\u0000\u0000\u0000\u0092\u0013\u0001\u0000\u0000\u0000\u0093\u0091\u0001"+
		"\u0000\u0000\u0000\u0094\u0095\u00055\u0000\u0000\u0095\u0097\u0005\u0001"+
		"\u0000\u0000\u0096\u0098\u0003\u0002\u0001\u0000\u0097\u0096\u0001\u0000"+
		"\u0000\u0000\u0098\u0099\u0001\u0000\u0000\u0000\u0099\u0097\u0001\u0000"+
		"\u0000\u0000\u0099\u009a\u0001\u0000\u0000\u0000\u009a\u009b\u0001\u0000"+
		"\u0000\u0000\u009b\u009c\u0005\u0002\u0000\u0000\u009c\u0015\u0001\u0000"+
		"\u0000\u0000\u009d\u00a0\u0005.\u0000\u0000\u009e\u009f\u0005\u0012\u0000"+
		"\u0000\u009f\u00a1\u0003\u0018\f\u0000\u00a0\u009e\u0001\u0000\u0000\u0000"+
		"\u00a0\u00a1\u0001\u0000\u0000\u0000\u00a1\u00a2\u0001\u0000\u0000\u0000"+
		"\u00a2\u00a3\u0005\u0015\u0000\u0000\u00a3\u00ac\u0003\u001a\r\u0000\u00a4"+
		"\u00a7\u0005.\u0000\u0000\u00a5\u00a6\u0005\u0012\u0000\u0000\u00a6\u00a8"+
		"\u0003\u0018\f\u0000\u00a7\u00a5\u0001\u0000\u0000\u0000\u00a7\u00a8\u0001"+
		"\u0000\u0000\u0000\u00a8\u00a9\u0001\u0000\u0000\u0000\u00a9\u00aa\u0007"+
		"\u0000\u0000\u0000\u00aa\u00ac\u0003\u001a\r\u0000\u00ab\u009d\u0001\u0000"+
		"\u0000\u0000\u00ab\u00a4\u0001\u0000\u0000\u0000\u00ac\u0017\u0001\u0000"+
		"\u0000\u0000\u00ad\u00b2\u0005.\u0000\u0000\u00ae\u00af\u0005\u001d\u0000"+
		"\u0000\u00af\u00b1\u0005.\u0000\u0000\u00b0\u00ae\u0001\u0000\u0000\u0000"+
		"\u00b1\u00b4\u0001\u0000\u0000\u0000\u00b2\u00b0\u0001\u0000\u0000\u0000"+
		"\u00b2\u00b3\u0001\u0000\u0000\u0000\u00b3\u00b7\u0001\u0000\u0000\u0000"+
		"\u00b4\u00b2\u0001\u0000\u0000\u0000\u00b5\u00b7\u0005+\u0000\u0000\u00b6"+
		"\u00ad\u0001\u0000\u0000\u0000\u00b6\u00b5\u0001\u0000\u0000\u0000\u00b7"+
		"\u0019\u0001\u0000\u0000\u0000\u00b8\u00ba\u0005\u001f\u0000\u0000\u00b9"+
		"\u00b8\u0001\u0000\u0000\u0000\u00b9\u00ba\u0001\u0000\u0000\u0000\u00ba"+
		"\u00bb\u0001\u0000\u0000\u0000\u00bb\u00bc\u0003\u001c\u000e\u0000\u00bc"+
		"\u001b\u0001\u0000\u0000\u0000\u00bd\u00c2\u0003\u001e\u000f\u0000\u00be"+
		"\u00bf\u0005\u001d\u0000\u0000\u00bf\u00c1\u0003\u001e\u000f\u0000\u00c0"+
		"\u00be\u0001\u0000\u0000\u0000\u00c1\u00c4\u0001\u0000\u0000\u0000\u00c2"+
		"\u00c0\u0001\u0000\u0000\u0000\u00c2\u00c3\u0001\u0000\u0000\u0000\u00c3"+
		"\u001d\u0001\u0000\u0000\u0000\u00c4\u00c2\u0001\u0000\u0000\u0000\u00c5"+
		"\u00ca\u0003 \u0010\u0000\u00c6\u00c7\u0005\u001e\u0000\u0000\u00c7\u00c9"+
		"\u0003 \u0010\u0000\u00c8\u00c6\u0001\u0000\u0000\u0000\u00c9\u00cc\u0001"+
		"\u0000\u0000\u0000\u00ca\u00c8\u0001\u0000\u0000\u0000\u00ca\u00cb\u0001"+
		"\u0000\u0000\u0000\u00cb\u00d6\u0001\u0000\u0000\u0000\u00cc\u00ca\u0001"+
		"\u0000\u0000\u0000\u00cd\u00d2\u0003\"\u0011\u0000\u00ce\u00cf\u0005\u001e"+
		"\u0000\u0000\u00cf\u00d1\u0003\"\u0011\u0000\u00d0\u00ce\u0001\u0000\u0000"+
		"\u0000\u00d1\u00d4\u0001\u0000\u0000\u0000\u00d2\u00d0\u0001\u0000\u0000"+
		"\u0000\u00d2\u00d3\u0001\u0000\u0000\u0000\u00d3\u00d6\u0001\u0000\u0000"+
		"\u0000\u00d4\u00d2\u0001\u0000\u0000\u0000\u00d5\u00c5\u0001\u0000\u0000"+
		"\u0000\u00d5\u00cd\u0001\u0000\u0000\u0000\u00d6\u001f\u0001\u0000\u0000"+
		"\u0000\u00d7\u00d8\u0003\"\u0011\u0000\u00d8\u00d9\u0005 \u0000\u0000"+
		"\u00d9\u00da\u0003\"\u0011\u0000\u00da\u00e8\u0001\u0000\u0000\u0000\u00db"+
		"\u00dc\u0003\"\u0011\u0000\u00dc\u00dd\u0005!\u0000\u0000\u00dd\u00de"+
		"\u0003\"\u0011\u0000\u00de\u00e8\u0001\u0000\u0000\u0000\u00df\u00e0\u0003"+
		"\"\u0011\u0000\u00e0\u00e1\u0005\u001a\u0000\u0000\u00e1\u00e2\u0003\""+
		"\u0011\u0000\u00e2\u00e8\u0001\u0000\u0000\u0000\u00e3\u00e4\u0003\"\u0011"+
		"\u0000\u00e4\u00e5\u0005\u001b\u0000\u0000\u00e5\u00e6\u0003\"\u0011\u0000"+
		"\u00e6\u00e8\u0001\u0000\u0000\u0000\u00e7\u00d7\u0001\u0000\u0000\u0000"+
		"\u00e7\u00db\u0001\u0000\u0000\u0000\u00e7\u00df\u0001\u0000\u0000\u0000"+
		"\u00e7\u00e3\u0001\u0000\u0000\u0000\u00e8!\u0001\u0000\u0000\u0000\u00e9"+
		"\u00ee\u0003$\u0012\u0000\u00ea\u00eb\u0007\u0001\u0000\u0000\u00eb\u00ed"+
		"\u0003$\u0012\u0000\u00ec\u00ea\u0001\u0000\u0000\u0000\u00ed\u00f0\u0001"+
		"\u0000\u0000\u0000\u00ee\u00ec\u0001\u0000\u0000\u0000\u00ee\u00ef\u0001"+
		"\u0000\u0000\u0000\u00ef#\u0001\u0000\u0000\u0000\u00f0\u00ee\u0001\u0000"+
		"\u0000\u0000\u00f1\u00f6\u0003*\u0015\u0000\u00f2\u00f3\u0007\u0002\u0000"+
		"\u0000\u00f3\u00f5\u0003*\u0015\u0000\u00f4\u00f2\u0001\u0000\u0000\u0000"+
		"\u00f5\u00f8\u0001\u0000\u0000\u0000\u00f6\u00f4\u0001\u0000\u0000\u0000"+
		"\u00f6\u00f7\u0001\u0000\u0000\u0000\u00f7%\u0001\u0000\u0000\u0000\u00f8"+
		"\u00f6\u0001\u0000\u0000\u0000\u00f9\u0104\u0005.\u0000\u0000\u00fa\u0104"+
		"\u0003,\u0016\u0000\u00fb\u0104\u0003(\u0014\u0000\u00fc\u00fd\u0005\u001c"+
		"\u0000\u0000\u00fd\u0104\u0003.\u0017\u0000\u00fe\u00ff\u0005/\u0000\u0000"+
		"\u00ff\u0100\u0003\u001a\r\u0000\u0100\u0101\u00050\u0000\u0000\u0101"+
		"\u0104\u0001\u0000\u0000\u0000\u0102\u0104\u0005*\u0000\u0000\u0103\u00f9"+
		"\u0001\u0000\u0000\u0000\u0103\u00fa\u0001\u0000\u0000\u0000\u0103\u00fb"+
		"\u0001\u0000\u0000\u0000\u0103\u00fc\u0001\u0000\u0000\u0000\u0103\u00fe"+
		"\u0001\u0000\u0000\u0000\u0103\u0102\u0001\u0000\u0000\u0000\u0104\'\u0001"+
		"\u0000\u0000\u0000\u0105\u010e\u00053\u0000\u0000\u0106\u010b\u0003.\u0017"+
		"\u0000\u0107\u0108\u0005\u0012\u0000\u0000\u0108\u010a\u0003.\u0017\u0000"+
		"\u0109\u0107\u0001\u0000\u0000\u0000\u010a\u010d\u0001\u0000\u0000\u0000"+
		"\u010b\u0109\u0001\u0000\u0000\u0000\u010b\u010c\u0001\u0000\u0000\u0000"+
		"\u010c\u010f\u0001\u0000\u0000\u0000\u010d\u010b\u0001\u0000\u0000\u0000"+
		"\u010e\u0106\u0001\u0000\u0000\u0000\u010e\u010f\u0001\u0000\u0000\u0000"+
		"\u010f\u0110\u0001\u0000\u0000\u0000\u0110\u0113\u00054\u0000\u0000\u0111"+
		"\u0113\u0003.\u0017\u0000\u0112\u0105\u0001\u0000\u0000\u0000\u0112\u0111"+
		"\u0001\u0000\u0000\u0000\u0113)\u0001\u0000\u0000\u0000\u0114\u0119\u0003"+
		"&\u0013\u0000\u0115\u0116\u00053\u0000\u0000\u0116\u0117\u0003\u001a\r"+
		"\u0000\u0117\u0118\u00054\u0000\u0000\u0118\u011a\u0001\u0000\u0000\u0000"+
		"\u0119\u0115\u0001\u0000\u0000\u0000\u0119\u011a\u0001\u0000\u0000\u0000"+
		"\u011a\u0126\u0001\u0000\u0000\u0000\u011b\u011e\u0003&\u0013\u0000\u011c"+
		"\u011d\u0007\u0003\u0000\u0000\u011d\u011f\u0005.\u0000\u0000\u011e\u011c"+
		"\u0001\u0000\u0000\u0000\u011e\u011f\u0001\u0000\u0000\u0000\u011f\u0126"+
		"\u0001\u0000\u0000\u0000\u0120\u0123\u0003&\u0013\u0000\u0121\u0122\u0007"+
		"\u0003\u0000\u0000\u0122\u0124\u0003,\u0016\u0000\u0123\u0121\u0001\u0000"+
		"\u0000\u0000\u0123\u0124\u0001\u0000\u0000\u0000\u0124\u0126\u0001\u0000"+
		"\u0000\u0000\u0125\u0114\u0001\u0000\u0000\u0000\u0125\u011b\u0001\u0000"+
		"\u0000\u0000\u0125\u0120\u0001\u0000\u0000\u0000\u0126+\u0001\u0000\u0000"+
		"\u0000\u0127\u0128\u0005.\u0000\u0000\u0128\u0131\u0005/\u0000\u0000\u0129"+
		"\u012e\u0003\u001a\r\u0000\u012a\u012b\u0005\u0012\u0000\u0000\u012b\u012d"+
		"\u0003\u001a\r\u0000\u012c\u012a\u0001\u0000\u0000\u0000\u012d\u0130\u0001"+
		"\u0000\u0000\u0000\u012e\u012c\u0001\u0000\u0000\u0000\u012e\u012f\u0001"+
		"\u0000\u0000\u0000\u012f\u0132\u0001\u0000\u0000\u0000\u0130\u012e\u0001"+
		"\u0000\u0000\u0000\u0131\u0129\u0001\u0000\u0000\u0000\u0131\u0132\u0001"+
		"\u0000\u0000\u0000\u0132\u0133\u0001\u0000\u0000\u0000\u0133\u0134\u0005"+
		"0\u0000\u0000\u0134-\u0001\u0000\u0000\u0000\u0135\u0137\u0005\u0017\u0000"+
		"\u0000\u0136\u0135\u0001\u0000\u0000\u0000\u0136\u0137\u0001\u0000\u0000"+
		"\u0000\u0137\u0138\u0001\u0000\u0000\u0000\u0138\u013e\u0005,\u0000\u0000"+
		"\u0139\u013e\u0005-\u0000\u0000\u013a\u013e\u0005\f\u0000\u0000\u013b"+
		"\u013e\u0005\r\u0000\u0000\u013c\u013e\u0005\u000e\u0000\u0000\u013d\u0136"+
		"\u0001\u0000\u0000\u0000\u013d\u0139\u0001\u0000\u0000\u0000\u013d\u013a"+
		"\u0001\u0000\u0000\u0000\u013d\u013b\u0001\u0000\u0000\u0000\u013d\u013c"+
		"\u0001\u0000\u0000\u0000\u013e/\u0001\u0000\u0000\u0000)39?HKRTYbfz\u007f"+
		"\u0087\u008d\u0091\u0099\u00a0\u00a7\u00ab\u00b2\u00b6\u00b9\u00c2\u00ca"+
		"\u00d2\u00d5\u00e7\u00ee\u00f6\u0103\u010b\u010e\u0112\u0119\u011e\u0123"+
		"\u0125\u012e\u0131\u0136\u013d";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}