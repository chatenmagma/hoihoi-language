// Generated from /home/chatenmagma/Workspace/hoihoi-language/grammar/HoihoiLexer.g4 by ANTLR 4.13.1

#include <deque>
#include <vector>
#include <memory>
#include <string>
#include <utility>

import org.antlr.v4.runtime.Lexer;
import org.antlr.v4.runtime.CharStream;
import org.antlr.v4.runtime.Token;
import org.antlr.v4.runtime.TokenStream;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.misc.*;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast", "CheckReturnValue", "this-escape"})
public class HoihoiLexer extends Lexer {
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
	public static String[] channelNames = {
		"DEFAULT_TOKEN_CHANNEL", "HIDDEN"
	};

	public static String[] modeNames = {
		"DEFAULT_MODE"
	};

	private static String[] makeRuleNames() {
		return new String[] {
			"IF", "ELIF", "ELSE", "COMPARE", "CASE", "RETURN", "PASS", "WHILE", "DEF", 
			"HIGH", "NEUTRAL", "LOW", "ARROW", "DOT", "STAR", "COMMA", "SEMI_COLON", 
			"COLON", "ASSIGN", "PLUS", "MINUS", "SLASH", "MODULO", "LESS_THAN", "GREATER_THAN", 
			"PRIMITIVE", "OR", "AND", "NOT", "EQUAL", "NOT_EQUAL", "ADD_ASSIGN", 
			"SUB_ASSIGN", "MUL_ASSIGN", "HEAP", "HOLE", "FLAT", "QUOTE", "DQUOTE", 
			"EMPTY", "THING", "NUMBER_LITERAL", "STRING_LITERAL", "IDENTIFIER", "OPEN_PAREN", 
			"CLOSE_PAREN", "OPEN_BRASE", "CLOSE_BRASE", "OPEN_BRACKET", "CLOSE_BRACKET", 
			"NEWLINE", "WS", "CONTENT", "RN"
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



	    std::deque<std::unique_ptr<antlr4::Token>> pendingTokens;
	    std::vector<size_t> indents = { 0 };

	    size_t indentationCount(const std::string& text)
	    {
	        size_t count = 0;

	        // text contient par exemple "\n    "
	        // On ne compte que les espaces/tabs après le newline.
	        for (size_t i = 0; i < text.size(); ++i)
	        {
	            if (text[i] == ' ')
	            {
	                ++count;
	            }
	            else if (text[i] == '\t')
	            {
	                // Convention simple : tab = 4 espaces
	                count += 4;
	            }
	        }

	        return count;
	    }

	    std::unique_ptr<antlr4::Token> makeLayoutToken(size_t type)
	    {
	        auto token = std::make_unique<antlr4::CommonToken>(
	            std::pair<antlr4::TokenSource*, antlr4::CharStream*>{this, _input},
	            type,
	            antlr4::Token::DEFAULT_CHANNEL,
	            getCharIndex(),
	            getCharIndex() - 1
	        );

	        token->setLine(getLine());
	        token->setCharPositionInLine(getCharPositionInLine());

	        return token;
	    }

	    std::unique_ptr<antlr4::Token> popPending()
	    {
	        auto token = std::move(pendingTokens.front());
	        pendingTokens.pop_front();
	        return token;
	    }

	    std::unique_ptr<antlr4::Token> nextToken() override
	    {
	        // Des tokens INDENT/DEDENT sont déjà en attente.
	        if (!pendingTokens.empty())
	        {
	            return popPending();
	        }

	        // Demande au lexer ANTLR normal de produire le prochain token.
	        auto token = antlr4::Lexer::nextToken();

	        // EOF :
	        // s'il reste des niveaux d'indentation ouverts,
	        // il faut générer les DEDENT manquants.
	        if (token->getType() == antlr4::Token::EOF)
	        {
	            while (indents.size() > 1)
	            {
	                indents.pop_back();
	                pendingTokens.push_back(makeLayoutToken(DEDENT));
	            }

	            pendingTokens.push_back(std::move(token));

	            return popPending();
	        }

	        // On ne s'intéresse qu'aux NEWLINE.
	        if (token->getType() == NEWLINE)
	        {
	            const std::string text = token->getText();

	            // Après le NEWLINE, regarde ce qui arrive.
	            const size_t next = _input->LA(1);

	            // Ligne vide / commentaire :
	            // on ne modifie PAS l'indentation.
	            if (next == '\n' ||
	                next == '\r' ||
	                next == '#' ||
	                next == antlr4::Token::EOF)
	            {
	                return token;
	            }

	            const size_t indent = indentationCount(text);
	            const size_t previous = indents.back();

	            if (indent > previous)
	            {
	                indents.push_back(indent);
	                pendingTokens.push_back(makeLayoutToken(INDENT));
	            }
	            else if (indent < previous)
	            {
	                while (indents.size() > 1 && indents.back() > indent)
	                {
	                    indents.pop_back();
	                    pendingTokens.push_back(makeLayoutToken(DEDENT));
	                }
	            }
	        }

	        return token;
	    }

	    void reset() override
	    {
	        antlr4::Lexer::reset();

	        pendingTokens.clear();

	        indents.clear();
	        indents.push_back(0);
	    }


	public HoihoiLexer(CharStream input) {
		super(input);
		_interp = new LexerATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}

	@Override
	public String getGrammarFileName() { return "HoihoiLexer.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public String[] getChannelNames() { return channelNames; }

	@Override
	public String[] getModeNames() { return modeNames; }

	@Override
	public ATN getATN() { return _ATN; }

	public static final String _serializedATN =
		"\u0004\u00007\u015f\u0006\uffff\uffff\u0002\u0000\u0007\u0000\u0002\u0001"+
		"\u0007\u0001\u0002\u0002\u0007\u0002\u0002\u0003\u0007\u0003\u0002\u0004"+
		"\u0007\u0004\u0002\u0005\u0007\u0005\u0002\u0006\u0007\u0006\u0002\u0007"+
		"\u0007\u0007\u0002\b\u0007\b\u0002\t\u0007\t\u0002\n\u0007\n\u0002\u000b"+
		"\u0007\u000b\u0002\f\u0007\f\u0002\r\u0007\r\u0002\u000e\u0007\u000e\u0002"+
		"\u000f\u0007\u000f\u0002\u0010\u0007\u0010\u0002\u0011\u0007\u0011\u0002"+
		"\u0012\u0007\u0012\u0002\u0013\u0007\u0013\u0002\u0014\u0007\u0014\u0002"+
		"\u0015\u0007\u0015\u0002\u0016\u0007\u0016\u0002\u0017\u0007\u0017\u0002"+
		"\u0018\u0007\u0018\u0002\u0019\u0007\u0019\u0002\u001a\u0007\u001a\u0002"+
		"\u001b\u0007\u001b\u0002\u001c\u0007\u001c\u0002\u001d\u0007\u001d\u0002"+
		"\u001e\u0007\u001e\u0002\u001f\u0007\u001f\u0002 \u0007 \u0002!\u0007"+
		"!\u0002\"\u0007\"\u0002#\u0007#\u0002$\u0007$\u0002%\u0007%\u0002&\u0007"+
		"&\u0002\'\u0007\'\u0002(\u0007(\u0002)\u0007)\u0002*\u0007*\u0002+\u0007"+
		"+\u0002,\u0007,\u0002-\u0007-\u0002.\u0007.\u0002/\u0007/\u00020\u0007"+
		"0\u00021\u00071\u00022\u00072\u00023\u00073\u00024\u00074\u00025\u0007"+
		"5\u0001\u0000\u0001\u0000\u0001\u0000\u0001\u0001\u0001\u0001\u0001\u0001"+
		"\u0001\u0001\u0001\u0001\u0001\u0002\u0001\u0002\u0001\u0002\u0001\u0002"+
		"\u0001\u0002\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0003"+
		"\u0001\u0003\u0001\u0003\u0001\u0003\u0001\u0004\u0001\u0004\u0001\u0004"+
		"\u0001\u0004\u0001\u0004\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0005"+
		"\u0001\u0005\u0001\u0005\u0001\u0005\u0001\u0006\u0001\u0006\u0001\u0006"+
		"\u0001\u0006\u0001\u0006\u0001\u0007\u0001\u0007\u0001\u0007\u0001\u0007"+
		"\u0001\u0007\u0001\u0007\u0001\b\u0001\b\u0001\b\u0001\b\u0001\t\u0001"+
		"\t\u0001\t\u0001\t\u0001\t\u0001\n\u0001\n\u0001\n\u0001\n\u0001\n\u0001"+
		"\n\u0001\n\u0001\n\u0001\u000b\u0001\u000b\u0001\u000b\u0001\u000b\u0001"+
		"\f\u0001\f\u0001\f\u0001\r\u0001\r\u0001\u000e\u0001\u000e\u0001\u000f"+
		"\u0001\u000f\u0001\u0010\u0001\u0010\u0001\u0011\u0001\u0011\u0001\u0012"+
		"\u0001\u0012\u0001\u0013\u0001\u0013\u0001\u0014\u0001\u0014\u0001\u0015"+
		"\u0001\u0015\u0001\u0016\u0001\u0016\u0001\u0017\u0001\u0017\u0001\u0018"+
		"\u0001\u0018\u0001\u0019\u0001\u0019\u0001\u001a\u0001\u001a\u0001\u001a"+
		"\u0001\u001b\u0001\u001b\u0001\u001b\u0001\u001b\u0001\u001c\u0001\u001c"+
		"\u0001\u001c\u0001\u001c\u0001\u001d\u0001\u001d\u0001\u001d\u0001\u001e"+
		"\u0001\u001e\u0001\u001e\u0001\u001f\u0001\u001f\u0001\u001f\u0001 \u0001"+
		" \u0001 \u0001!\u0001!\u0001!\u0001\"\u0001\"\u0001\"\u0001\"\u0001\""+
		"\u0001#\u0001#\u0001#\u0001#\u0001#\u0001$\u0001$\u0001$\u0001$\u0001"+
		"$\u0001%\u0001%\u0001&\u0001&\u0001\'\u0001\'\u0001\'\u0001\'\u0001\'"+
		"\u0001\'\u0001(\u0001(\u0001(\u0001(\u0001(\u0001(\u0001)\u0004)\u0106"+
		"\b)\u000b)\f)\u0107\u0001)\u0001)\u0005)\u010c\b)\n)\f)\u010f\t)\u0003"+
		")\u0111\b)\u0001*\u0001*\u0001*\u0001*\u0003*\u0117\b*\u0001*\u0005*\u011a"+
		"\b*\n*\f*\u011d\t*\u0001*\u0001*\u0001*\u0001*\u0001*\u0001*\u0003*\u0125"+
		"\b*\u0001*\u0005*\u0128\b*\n*\f*\u012b\t*\u0001*\u0001*\u0003*\u012f\b"+
		"*\u0001+\u0001+\u0005+\u0133\b+\n+\f+\u0136\t+\u0001,\u0001,\u0001-\u0001"+
		"-\u0001.\u0001.\u0001/\u0001/\u00010\u00010\u00011\u00011\u00012\u0001"+
		"2\u00052\u0146\b2\n2\f2\u0149\t2\u00013\u00043\u014c\b3\u000b3\f3\u014d"+
		"\u00013\u00013\u00014\u00014\u00054\u0154\b4\n4\f4\u0157\t4\u00014\u0001"+
		"4\u00015\u00035\u015c\b5\u00015\u00015\u0000\u00006\u0001\u0003\u0003"+
		"\u0004\u0005\u0005\u0007\u0006\t\u0007\u000b\b\r\t\u000f\n\u0011\u000b"+
		"\u0013\f\u0015\r\u0017\u000e\u0019\u000f\u001b\u0010\u001d\u0011\u001f"+
		"\u0012!\u0013#\u0014%\u0015\'\u0016)\u0017+\u0018-\u0019/\u001a1\u001b"+
		"3\u001c5\u001d7\u001e9\u001f; =!?\"A#C$E%G&I\'K(M)O*Q+S,U-W.Y/[0]1_2a"+
		"3c4e5g6i7k\u0000\u0001\u0000\u0007\u0001\u000009\u0004\u0000\n\n\r\r\'"+
		"\'\\\\\u0004\u0000\n\n\r\r\"\"\\\\\u0003\u0000AZ__az\u0004\u000009AZ_"+
		"_az\u0002\u0000\t\t  \u0002\u0000\n\n\f\r\u016c\u0000\u0001\u0001\u0000"+
		"\u0000\u0000\u0000\u0003\u0001\u0000\u0000\u0000\u0000\u0005\u0001\u0000"+
		"\u0000\u0000\u0000\u0007\u0001\u0000\u0000\u0000\u0000\t\u0001\u0000\u0000"+
		"\u0000\u0000\u000b\u0001\u0000\u0000\u0000\u0000\r\u0001\u0000\u0000\u0000"+
		"\u0000\u000f\u0001\u0000\u0000\u0000\u0000\u0011\u0001\u0000\u0000\u0000"+
		"\u0000\u0013\u0001\u0000\u0000\u0000\u0000\u0015\u0001\u0000\u0000\u0000"+
		"\u0000\u0017\u0001\u0000\u0000\u0000\u0000\u0019\u0001\u0000\u0000\u0000"+
		"\u0000\u001b\u0001\u0000\u0000\u0000\u0000\u001d\u0001\u0000\u0000\u0000"+
		"\u0000\u001f\u0001\u0000\u0000\u0000\u0000!\u0001\u0000\u0000\u0000\u0000"+
		"#\u0001\u0000\u0000\u0000\u0000%\u0001\u0000\u0000\u0000\u0000\'\u0001"+
		"\u0000\u0000\u0000\u0000)\u0001\u0000\u0000\u0000\u0000+\u0001\u0000\u0000"+
		"\u0000\u0000-\u0001\u0000\u0000\u0000\u0000/\u0001\u0000\u0000\u0000\u0000"+
		"1\u0001\u0000\u0000\u0000\u00003\u0001\u0000\u0000\u0000\u00005\u0001"+
		"\u0000\u0000\u0000\u00007\u0001\u0000\u0000\u0000\u00009\u0001\u0000\u0000"+
		"\u0000\u0000;\u0001\u0000\u0000\u0000\u0000=\u0001\u0000\u0000\u0000\u0000"+
		"?\u0001\u0000\u0000\u0000\u0000A\u0001\u0000\u0000\u0000\u0000C\u0001"+
		"\u0000\u0000\u0000\u0000E\u0001\u0000\u0000\u0000\u0000G\u0001\u0000\u0000"+
		"\u0000\u0000I\u0001\u0000\u0000\u0000\u0000K\u0001\u0000\u0000\u0000\u0000"+
		"M\u0001\u0000\u0000\u0000\u0000O\u0001\u0000\u0000\u0000\u0000Q\u0001"+
		"\u0000\u0000\u0000\u0000S\u0001\u0000\u0000\u0000\u0000U\u0001\u0000\u0000"+
		"\u0000\u0000W\u0001\u0000\u0000\u0000\u0000Y\u0001\u0000\u0000\u0000\u0000"+
		"[\u0001\u0000\u0000\u0000\u0000]\u0001\u0000\u0000\u0000\u0000_\u0001"+
		"\u0000\u0000\u0000\u0000a\u0001\u0000\u0000\u0000\u0000c\u0001\u0000\u0000"+
		"\u0000\u0000e\u0001\u0000\u0000\u0000\u0000g\u0001\u0000\u0000\u0000\u0000"+
		"i\u0001\u0000\u0000\u0000\u0001m\u0001\u0000\u0000\u0000\u0003p\u0001"+
		"\u0000\u0000\u0000\u0005u\u0001\u0000\u0000\u0000\u0007z\u0001\u0000\u0000"+
		"\u0000\t\u0082\u0001\u0000\u0000\u0000\u000b\u0087\u0001\u0000\u0000\u0000"+
		"\r\u008e\u0001\u0000\u0000\u0000\u000f\u0093\u0001\u0000\u0000\u0000\u0011"+
		"\u0099\u0001\u0000\u0000\u0000\u0013\u009d\u0001\u0000\u0000\u0000\u0015"+
		"\u00a2\u0001\u0000\u0000\u0000\u0017\u00aa\u0001\u0000\u0000\u0000\u0019"+
		"\u00ae\u0001\u0000\u0000\u0000\u001b\u00b1\u0001\u0000\u0000\u0000\u001d"+
		"\u00b3\u0001\u0000\u0000\u0000\u001f\u00b5\u0001\u0000\u0000\u0000!\u00b7"+
		"\u0001\u0000\u0000\u0000#\u00b9\u0001\u0000\u0000\u0000%\u00bb\u0001\u0000"+
		"\u0000\u0000\'\u00bd\u0001\u0000\u0000\u0000)\u00bf\u0001\u0000\u0000"+
		"\u0000+\u00c1\u0001\u0000\u0000\u0000-\u00c3\u0001\u0000\u0000\u0000/"+
		"\u00c5\u0001\u0000\u0000\u00001\u00c7\u0001\u0000\u0000\u00003\u00c9\u0001"+
		"\u0000\u0000\u00005\u00cb\u0001\u0000\u0000\u00007\u00ce\u0001\u0000\u0000"+
		"\u00009\u00d2\u0001\u0000\u0000\u0000;\u00d6\u0001\u0000\u0000\u0000="+
		"\u00d9\u0001\u0000\u0000\u0000?\u00dc\u0001\u0000\u0000\u0000A\u00df\u0001"+
		"\u0000\u0000\u0000C\u00e2\u0001\u0000\u0000\u0000E\u00e5\u0001\u0000\u0000"+
		"\u0000G\u00ea\u0001\u0000\u0000\u0000I\u00ef\u0001\u0000\u0000\u0000K"+
		"\u00f4\u0001\u0000\u0000\u0000M\u00f6\u0001\u0000\u0000\u0000O\u00f8\u0001"+
		"\u0000\u0000\u0000Q\u00fe\u0001\u0000\u0000\u0000S\u0105\u0001\u0000\u0000"+
		"\u0000U\u012e\u0001\u0000\u0000\u0000W\u0130\u0001\u0000\u0000\u0000Y"+
		"\u0137\u0001\u0000\u0000\u0000[\u0139\u0001\u0000\u0000\u0000]\u013b\u0001"+
		"\u0000\u0000\u0000_\u013d\u0001\u0000\u0000\u0000a\u013f\u0001\u0000\u0000"+
		"\u0000c\u0141\u0001\u0000\u0000\u0000e\u0143\u0001\u0000\u0000\u0000g"+
		"\u014b\u0001\u0000\u0000\u0000i\u0151\u0001\u0000\u0000\u0000k\u015b\u0001"+
		"\u0000\u0000\u0000mn\u0005i\u0000\u0000no\u0005f\u0000\u0000o\u0002\u0001"+
		"\u0000\u0000\u0000pq\u0005e\u0000\u0000qr\u0005l\u0000\u0000rs\u0005i"+
		"\u0000\u0000st\u0005f\u0000\u0000t\u0004\u0001\u0000\u0000\u0000uv\u0005"+
		"e\u0000\u0000vw\u0005l\u0000\u0000wx\u0005s\u0000\u0000xy\u0005e\u0000"+
		"\u0000y\u0006\u0001\u0000\u0000\u0000z{\u0005c\u0000\u0000{|\u0005o\u0000"+
		"\u0000|}\u0005m\u0000\u0000}~\u0005p\u0000\u0000~\u007f\u0005a\u0000\u0000"+
		"\u007f\u0080\u0005r\u0000\u0000\u0080\u0081\u0005e\u0000\u0000\u0081\b"+
		"\u0001\u0000\u0000\u0000\u0082\u0083\u0005c\u0000\u0000\u0083\u0084\u0005"+
		"a\u0000\u0000\u0084\u0085\u0005s\u0000\u0000\u0085\u0086\u0005e\u0000"+
		"\u0000\u0086\n\u0001\u0000\u0000\u0000\u0087\u0088\u0005r\u0000\u0000"+
		"\u0088\u0089\u0005e\u0000\u0000\u0089\u008a\u0005t\u0000\u0000\u008a\u008b"+
		"\u0005u\u0000\u0000\u008b\u008c\u0005r\u0000\u0000\u008c\u008d\u0005n"+
		"\u0000\u0000\u008d\f\u0001\u0000\u0000\u0000\u008e\u008f\u0005p\u0000"+
		"\u0000\u008f\u0090\u0005a\u0000\u0000\u0090\u0091\u0005s\u0000\u0000\u0091"+
		"\u0092\u0005s\u0000\u0000\u0092\u000e\u0001\u0000\u0000\u0000\u0093\u0094"+
		"\u0005w\u0000\u0000\u0094\u0095\u0005h\u0000\u0000\u0095\u0096\u0005i"+
		"\u0000\u0000\u0096\u0097\u0005l\u0000\u0000\u0097\u0098\u0005e\u0000\u0000"+
		"\u0098\u0010\u0001\u0000\u0000\u0000\u0099\u009a\u0005d\u0000\u0000\u009a"+
		"\u009b\u0005e\u0000\u0000\u009b\u009c\u0005f\u0000\u0000\u009c\u0012\u0001"+
		"\u0000\u0000\u0000\u009d\u009e\u0005h\u0000\u0000\u009e\u009f\u0005i\u0000"+
		"\u0000\u009f\u00a0\u0005g\u0000\u0000\u00a0\u00a1\u0005h\u0000\u0000\u00a1"+
		"\u0014\u0001\u0000\u0000\u0000\u00a2\u00a3\u0005n\u0000\u0000\u00a3\u00a4"+
		"\u0005e\u0000\u0000\u00a4\u00a5\u0005u\u0000\u0000\u00a5\u00a6\u0005t"+
		"\u0000\u0000\u00a6\u00a7\u0005r\u0000\u0000\u00a7\u00a8\u0005a\u0000\u0000"+
		"\u00a8\u00a9\u0005l\u0000\u0000\u00a9\u0016\u0001\u0000\u0000\u0000\u00aa"+
		"\u00ab\u0005l\u0000\u0000\u00ab\u00ac\u0005o\u0000\u0000\u00ac\u00ad\u0005"+
		"w\u0000\u0000\u00ad\u0018\u0001\u0000\u0000\u0000\u00ae\u00af\u0005-\u0000"+
		"\u0000\u00af\u00b0\u0005>\u0000\u0000\u00b0\u001a\u0001\u0000\u0000\u0000"+
		"\u00b1\u00b2\u0005.\u0000\u0000\u00b2\u001c\u0001\u0000\u0000\u0000\u00b3"+
		"\u00b4\u0005*\u0000\u0000\u00b4\u001e\u0001\u0000\u0000\u0000\u00b5\u00b6"+
		"\u0005,\u0000\u0000\u00b6 \u0001\u0000\u0000\u0000\u00b7\u00b8\u0005;"+
		"\u0000\u0000\u00b8\"\u0001\u0000\u0000\u0000\u00b9\u00ba\u0005:\u0000"+
		"\u0000\u00ba$\u0001\u0000\u0000\u0000\u00bb\u00bc\u0005=\u0000\u0000\u00bc"+
		"&\u0001\u0000\u0000\u0000\u00bd\u00be\u0005+\u0000\u0000\u00be(\u0001"+
		"\u0000\u0000\u0000\u00bf\u00c0\u0005-\u0000\u0000\u00c0*\u0001\u0000\u0000"+
		"\u0000\u00c1\u00c2\u0005/\u0000\u0000\u00c2,\u0001\u0000\u0000\u0000\u00c3"+
		"\u00c4\u0005%\u0000\u0000\u00c4.\u0001\u0000\u0000\u0000\u00c5\u00c6\u0005"+
		"<\u0000\u0000\u00c60\u0001\u0000\u0000\u0000\u00c7\u00c8\u0005>\u0000"+
		"\u0000\u00c82\u0001\u0000\u0000\u0000\u00c9\u00ca\u0005$\u0000\u0000\u00ca"+
		"4\u0001\u0000\u0000\u0000\u00cb\u00cc\u0005o\u0000\u0000\u00cc\u00cd\u0005"+
		"r\u0000\u0000\u00cd6\u0001\u0000\u0000\u0000\u00ce\u00cf\u0005a\u0000"+
		"\u0000\u00cf\u00d0\u0005n\u0000\u0000\u00d0\u00d1\u0005d\u0000\u0000\u00d1"+
		"8\u0001\u0000\u0000\u0000\u00d2\u00d3\u0005n\u0000\u0000\u00d3\u00d4\u0005"+
		"o\u0000\u0000\u00d4\u00d5\u0005t\u0000\u0000\u00d5:\u0001\u0000\u0000"+
		"\u0000\u00d6\u00d7\u0005=\u0000\u0000\u00d7\u00d8\u0005=\u0000\u0000\u00d8"+
		"<\u0001\u0000\u0000\u0000\u00d9\u00da\u0005!\u0000\u0000\u00da\u00db\u0005"+
		"=\u0000\u0000\u00db>\u0001\u0000\u0000\u0000\u00dc\u00dd\u0005+\u0000"+
		"\u0000\u00dd\u00de\u0005=\u0000\u0000\u00de@\u0001\u0000\u0000\u0000\u00df"+
		"\u00e0\u0005-\u0000\u0000\u00e0\u00e1\u0005=\u0000\u0000\u00e1B\u0001"+
		"\u0000\u0000\u0000\u00e2\u00e3\u0005*\u0000\u0000\u00e3\u00e4\u0005=\u0000"+
		"\u0000\u00e4D\u0001\u0000\u0000\u0000\u00e5\u00e6\u0005h\u0000\u0000\u00e6"+
		"\u00e7\u0005e\u0000\u0000\u00e7\u00e8\u0005a\u0000\u0000\u00e8\u00e9\u0005"+
		"p\u0000\u0000\u00e9F\u0001\u0000\u0000\u0000\u00ea\u00eb\u0005h\u0000"+
		"\u0000\u00eb\u00ec\u0005o\u0000\u0000\u00ec\u00ed\u0005l\u0000\u0000\u00ed"+
		"\u00ee\u0005e\u0000\u0000\u00eeH\u0001\u0000\u0000\u0000\u00ef\u00f0\u0005"+
		"f\u0000\u0000\u00f0\u00f1\u0005l\u0000\u0000\u00f1\u00f2\u0005a\u0000"+
		"\u0000\u00f2\u00f3\u0005t\u0000\u0000\u00f3J\u0001\u0000\u0000\u0000\u00f4"+
		"\u00f5\u0005\'\u0000\u0000\u00f5L\u0001\u0000\u0000\u0000\u00f6\u00f7"+
		"\u0005\"\u0000\u0000\u00f7N\u0001\u0000\u0000\u0000\u00f8\u00f9\u0005"+
		"e\u0000\u0000\u00f9\u00fa\u0005m\u0000\u0000\u00fa\u00fb\u0005p\u0000"+
		"\u0000\u00fb\u00fc\u0005t\u0000\u0000\u00fc\u00fd\u0005y\u0000\u0000\u00fd"+
		"P\u0001\u0000\u0000\u0000\u00fe\u00ff\u0005t\u0000\u0000\u00ff\u0100\u0005"+
		"h\u0000\u0000\u0100\u0101\u0005i\u0000\u0000\u0101\u0102\u0005n\u0000"+
		"\u0000\u0102\u0103\u0005g\u0000\u0000\u0103R\u0001\u0000\u0000\u0000\u0104"+
		"\u0106\u0007\u0000\u0000\u0000\u0105\u0104\u0001\u0000\u0000\u0000\u0106"+
		"\u0107\u0001\u0000\u0000\u0000\u0107\u0105\u0001\u0000\u0000\u0000\u0107"+
		"\u0108\u0001\u0000\u0000\u0000\u0108\u0110\u0001\u0000\u0000\u0000\u0109"+
		"\u010d\u0005.\u0000\u0000\u010a\u010c\u0007\u0000\u0000\u0000\u010b\u010a"+
		"\u0001\u0000\u0000\u0000\u010c\u010f\u0001\u0000\u0000\u0000\u010d\u010b"+
		"\u0001\u0000\u0000\u0000\u010d\u010e\u0001\u0000\u0000\u0000\u010e\u0111"+
		"\u0001\u0000\u0000\u0000\u010f\u010d\u0001\u0000\u0000\u0000\u0110\u0109"+
		"\u0001\u0000\u0000\u0000\u0110\u0111\u0001\u0000\u0000\u0000\u0111T\u0001"+
		"\u0000\u0000\u0000\u0112\u011b\u0003K%\u0000\u0113\u0116\u0005\\\u0000"+
		"\u0000\u0114\u0117\u0003k5\u0000\u0115\u0117\t\u0000\u0000\u0000\u0116"+
		"\u0114\u0001\u0000\u0000\u0000\u0116\u0115\u0001\u0000\u0000\u0000\u0117"+
		"\u011a\u0001\u0000\u0000\u0000\u0118\u011a\b\u0001\u0000\u0000\u0119\u0113"+
		"\u0001\u0000\u0000\u0000\u0119\u0118\u0001\u0000\u0000\u0000\u011a\u011d"+
		"\u0001\u0000\u0000\u0000\u011b\u0119\u0001\u0000\u0000\u0000\u011b\u011c"+
		"\u0001\u0000\u0000\u0000\u011c\u011e\u0001\u0000\u0000\u0000\u011d\u011b"+
		"\u0001\u0000\u0000\u0000\u011e\u011f\u0003K%\u0000\u011f\u012f\u0001\u0000"+
		"\u0000\u0000\u0120\u0129\u0003M&\u0000\u0121\u0124\u0005\\\u0000\u0000"+
		"\u0122\u0125\u0003k5\u0000\u0123\u0125\t\u0000\u0000\u0000\u0124\u0122"+
		"\u0001\u0000\u0000\u0000\u0124\u0123\u0001\u0000\u0000\u0000\u0125\u0128"+
		"\u0001\u0000\u0000\u0000\u0126\u0128\b\u0002\u0000\u0000\u0127\u0121\u0001"+
		"\u0000\u0000\u0000\u0127\u0126\u0001\u0000\u0000\u0000\u0128\u012b\u0001"+
		"\u0000\u0000\u0000\u0129\u0127\u0001\u0000\u0000\u0000\u0129\u012a\u0001"+
		"\u0000\u0000\u0000\u012a\u012c\u0001\u0000\u0000\u0000\u012b\u0129\u0001"+
		"\u0000\u0000\u0000\u012c\u012d\u0003M&\u0000\u012d\u012f\u0001\u0000\u0000"+
		"\u0000\u012e\u0112\u0001\u0000\u0000\u0000\u012e\u0120\u0001\u0000\u0000"+
		"\u0000\u012fV\u0001\u0000\u0000\u0000\u0130\u0134\u0007\u0003\u0000\u0000"+
		"\u0131\u0133\u0007\u0004\u0000\u0000\u0132\u0131\u0001\u0000\u0000\u0000"+
		"\u0133\u0136\u0001\u0000\u0000\u0000\u0134\u0132\u0001\u0000\u0000\u0000"+
		"\u0134\u0135\u0001\u0000\u0000\u0000\u0135X\u0001\u0000\u0000\u0000\u0136"+
		"\u0134\u0001\u0000\u0000\u0000\u0137\u0138\u0005(\u0000\u0000\u0138Z\u0001"+
		"\u0000\u0000\u0000\u0139\u013a\u0005)\u0000\u0000\u013a\\\u0001\u0000"+
		"\u0000\u0000\u013b\u013c\u0005{\u0000\u0000\u013c^\u0001\u0000\u0000\u0000"+
		"\u013d\u013e\u0005}\u0000\u0000\u013e`\u0001\u0000\u0000\u0000\u013f\u0140"+
		"\u0005[\u0000\u0000\u0140b\u0001\u0000\u0000\u0000\u0141\u0142\u0005]"+
		"\u0000\u0000\u0142d\u0001\u0000\u0000\u0000\u0143\u0147\u0003k5\u0000"+
		"\u0144\u0146\u0007\u0005\u0000\u0000\u0145\u0144\u0001\u0000\u0000\u0000"+
		"\u0146\u0149\u0001\u0000\u0000\u0000\u0147\u0145\u0001\u0000\u0000\u0000"+
		"\u0147\u0148\u0001\u0000\u0000\u0000\u0148f\u0001\u0000\u0000\u0000\u0149"+
		"\u0147\u0001\u0000\u0000\u0000\u014a\u014c\u0007\u0005\u0000\u0000\u014b"+
		"\u014a\u0001\u0000\u0000\u0000\u014c\u014d\u0001\u0000\u0000\u0000\u014d"+
		"\u014b\u0001\u0000\u0000\u0000\u014d\u014e\u0001\u0000\u0000\u0000\u014e"+
		"\u014f\u0001\u0000\u0000\u0000\u014f\u0150\u00063\u0000\u0000\u0150h\u0001"+
		"\u0000\u0000\u0000\u0151\u0155\u0005#\u0000\u0000\u0152\u0154\b\u0006"+
		"\u0000\u0000\u0153\u0152\u0001\u0000\u0000\u0000\u0154\u0157\u0001\u0000"+
		"\u0000\u0000\u0155\u0153\u0001\u0000\u0000\u0000\u0155\u0156\u0001\u0000"+
		"\u0000\u0000\u0156\u0158\u0001\u0000\u0000\u0000\u0157\u0155\u0001\u0000"+
		"\u0000\u0000\u0158\u0159\u00064\u0000\u0000\u0159j\u0001\u0000\u0000\u0000"+
		"\u015a\u015c\u0005\r\u0000\u0000\u015b\u015a\u0001\u0000\u0000\u0000\u015b"+
		"\u015c\u0001\u0000\u0000\u0000\u015c\u015d\u0001\u0000\u0000\u0000\u015d"+
		"\u015e\u0005\n\u0000\u0000\u015el\u0001\u0000\u0000\u0000\u0010\u0000"+
		"\u0107\u010d\u0110\u0116\u0119\u011b\u0124\u0127\u0129\u012e\u0134\u0147"+
		"\u014d\u0155\u015b\u0001\u0000\u0001\u0000";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}