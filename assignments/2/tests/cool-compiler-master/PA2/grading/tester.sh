#/bin/bash
LEXER=/home/compilers/course/assignments/2/lexer
for file in $(ls *.cool)
do
	$LEXER $file > results/$file.out
	echo $file
	diff $file.out results/$file.out
done