
python buildcpp.py -x $1 -d i -i f -o f && sh $TRT_SOURCE/build/check.sh

python buildcpp.py -x $1 -d i -i i8 -o f && sh $TRT_SOURCE/build/check.sh
python buildcpp.py -x $1 -d i -i i8 -o h && sh $TRT_SOURCE/build/check.sh
python buildcpp.py -x $1 -d i -i i8 -o i8 && sh $TRT_SOURCE/build/check.sh
python buildcpp.py -x $1 -d i -i i8 -o i32 && sh $TRT_SOURCE/build/check.sh
python buildcpp.py -x $1 -d i -i i8 -o b && sh $TRT_SOURCE/build/check.sh


python buildcpp.py -x $1 -d i -i i32 -o f && sh $TRT_SOURCE/build/check.sh
python buildcpp.py -x $1 -d i -i i32 -o h && sh $TRT_SOURCE/build/check.sh
python buildcpp.py -x $1 -d i -i i32 -o i8 && sh $TRT_SOURCE/build/check.sh
python buildcpp.py -x $1 -d i -i i32 -o i32 && sh $TRT_SOURCE/build/check.sh
python buildcpp.py -x $1 -d i -i i32 -o b && sh $TRT_SOURCE/build/check.sh


