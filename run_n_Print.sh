mkdir imgs
python draw.py >> ./imgs/out.txt
cp cpmfem.c def.h cellmoves.c ./imgs
ffmpeg -framerate 15 -i ./imgs/example%03d00.png -vf scale=720:720 -c:v libx264 -pix_fmt yuv420p ./imgs/out.mp4
