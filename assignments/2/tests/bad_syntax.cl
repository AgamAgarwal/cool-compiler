(* Author: Agam Agarwal (CS12B1003) *)
Int x;	--flagging error for this is not the lexer's job
String y;
if x==0 then
	y<-'zero'
elif x<0 then
	y<-"negative"
else then
	"positive"=>y	--this isn't the lexer's job either, it won't give an error