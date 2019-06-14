
make clean

make

for file in ./testbench/*

do
if test -f $file
then
arr=(${arr[*]} $file)
fi
done
echo ${arr[@]}


	
for ((i=0; i < ${#arr[@]}; i++))
do
	./postman.out ${arr[$i]}
	
done
