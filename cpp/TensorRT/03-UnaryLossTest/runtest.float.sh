python buildcpp.py -x $1 -d f -i f -o f && sh $TRT_SOURCE/build/check.sh

python buildcpp.py -x $1 -d f -i f -o f && sh $TRT_SOURCE/build/check.sh
python buildcpp.py -x $1 -d f -i f -o h && sh $TRT_SOURCE/build/check.sh
python buildcpp.py -x $1 -d f -i f -o i8 && sh $TRT_SOURCE/build/check.sh
python buildcpp.py -x $1 -d f -i f -o i32 && sh $TRT_SOURCE/build/check.sh
python buildcpp.py -x $1 -d f -i f -o b && sh $TRT_SOURCE/build/check.sh

python buildcpp.py -x $1 -d f -i h -o f && sh $TRT_SOURCE/build/check.sh
python buildcpp.py -x $1 -d f -i h -o h && sh $TRT_SOURCE/build/check.sh
python buildcpp.py -x $1 -d f -i h -o i8 && sh $TRT_SOURCE/build/check.sh
python buildcpp.py -x $1 -d f -i h -o i32 && sh $TRT_SOURCE/build/check.sh
python buildcpp.py -x $1 -d f -i h -o b && sh $TRT_SOURCE/build/check.sh

