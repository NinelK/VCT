(* ::Package:: *)

SetDirectory["/Users/ninel/Documents/potts/potts/"];

CQ[list_] := Module[{c = list, pos}, pos = Position[c, 1];
   If[c[[2, 2]] == 1 && Length@pos > 2, 0, c[[2, 2]]]];

DeleteCentral[x_] := 
 Module[{c = ArrayPad[x, 1], w, l}, {w, l} = Dimensions[x];
  Table[CQ[c[[i - 1 ;; i + 1, j - 1 ;; j + 1]]], {i, 2, w + 1}, {j, 2,
     l + 1}]];

CountLegs[gr_] := 
  Module[{mc = 
     MorphologicalComponents[
      Image[DeleteCentral[
        Map[If[# > 0, 1, 0] &, 
         ImageData@SkeletonTransform[ColorNegate@gr], {2}]]]]}, 
   Max[mc]];

fibersI=Import["./output/fib.out","Table"];
types=First@Import["./output/types.out","Table"];
conts=Import["./output/contactM900.out","Table"];

indexes=Import["./output/ctags"<>ToString[900]<>".out","Table"];

mFB=Map[If[#>0&&types[[#]]==2,#,0]&,indexes,{2}];
(*F[x_]:={Mean[x],StandardDeviation[x]};*)
F[x_]:=Mean[x];
legsC=Table[Module[{mCell=Map[If[#==n,0,1]&,indexes,{2}]},{n,CountLegs[ImageCrop@Image[mCell\[Transpose]]],types[[n]]}],{n,1,Length@types-1}];
legsFB=Select[legsC,#[[3]]==2&][[;;,2]];

params=<<"params.txt";

newline={params,{F@(ComponentMeasurements[mFB,"Area"][[;;,2]]2.5^2),
F[ComponentMeasurements[mFB,"ConvexCoverage"][[;;,2]]],F[(1-ComponentMeasurements[mFB,"Elongation"][[;;,2]])^-1],
F[(1-ComponentMeasurements[mFB,"CaliperElongation"][[;;,2]])^-1],N@F[legsFB]}};

If[Position[FileNames[], "output.txt"]=={},

	newline>>"output.txt",
	out=<<"output.txt";
	(newline~Join~out)>>"output.txt"

	]

Exit[]
