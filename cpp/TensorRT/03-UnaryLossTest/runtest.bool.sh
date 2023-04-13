
python buildcpp.py -x $1 -d b -i f -o f && sh $TRT_SOURCE/build/check.sh

python buildcpp.py -x $1 -d b -i b -o f && sh $TRT_SOURCE/build/check.sh
python buildcpp.py -x $1 -d b -i b -o h && sh $TRT_SOURCE/build/check.sh
python buildcpp.py -x $1 -d b -i b -o i8 && sh $TRT_SOURCE/build/check.sh
python buildcpp.py -x $1 -d b -i b -o i32 && sh $TRT_SOURCE/build/check.sh
python buildcpp.py -x $1 -d b -i b -o b && sh $TRT_SOURCE/build/check.sh

