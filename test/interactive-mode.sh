# test_unclosed_quote.sh
#
# should return a syntax error message, like in bash
#
# test/interactive-mode.sh: line 5: unexpected EOF while looking for matching `"'
# test/interactive-mode.sh: line 6: syntax error: unexpected end of file
#
# either handle it or make sure it doesn't seg fault

echo "This is an unclosed quote
