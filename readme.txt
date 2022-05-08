new:
1.   Created FoolProof class with 5/6 old foolproof funcs
2.   Wrote AllCorrect() func that checks all of 5/6 old foolproof funcs
edit:
3.   Removed '-' from 2nd  regex in FoolProof::SignsCorrect()
  cuz (-3) is a normal case
4.   + in SingsCorrect() in regexes put \\ before ( and )
5.   Changed GetSimpleFunc(), now there's a liiiitle repeating of code
  instead of creating new class every time func was called.
6.   Did replacing of 'pi' and 'e' in GlobalReplace() on doubles