#/bin/bash
#LEXER=/home/compilers/course/assignments/2/lexer
LEXER=/usr/class/cs3020/cool/lib/.i686/lexer
mkdir -p results
for file in $(ls *.cool)
do
	$LEXER $file > results/$file.out
	echo $file
	diff $file.out results/$file.out
done
