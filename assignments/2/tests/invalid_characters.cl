(* Author: Agam Agarwal (CS12B1003) *)
class Main inherits IO {
	main():IO {	--there are two invalid (non-printable) characters (\302 and \240) after IO
		out_string("check")
	};
};