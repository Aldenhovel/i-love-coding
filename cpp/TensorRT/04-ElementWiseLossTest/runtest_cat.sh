# std values
python buildcpp.cat.py -a f -b f -o f -d ff && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a  cat.log
python buildcpp.cat.py -a f -b f -o f -d fi && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a  cat.log
python buildcpp.cat.py -a f -b f -o f -d fb && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a  cat.log
python buildcpp.cat.py -a f -b f -o f -d if && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a  cat.log
python buildcpp.cat.py -a f -b f -o f -d ii && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a  cat.log
python buildcpp.cat.py -a f -b f -o f -d ib && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a  cat.log
python buildcpp.cat.py -a f -b f -o f -d bf && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a  cat.log
python buildcpp.cat.py -a f -b f -o f -d bi && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a  cat.log
python buildcpp.cat.py -a f -b f -o f -d bb && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a  cat.log

# f-f-?
python buildcpp.cat.py -a f -b f -o f -d ff && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a  cat.log
python buildcpp.cat.py -a f -b f -o h -d ff && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a  cat.log
python buildcpp.cat.py -a f -b f -o i8 -d ff && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a  cat.log
python buildcpp.cat.py -a f -b f -o i32 -d ff && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a  cat.log
python buildcpp.cat.py -a f -b f -o b -d ff && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a  cat.log

# f-h-?
python buildcpp.cat.py -a f -b h -o f -d ff && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a  cat.log
python buildcpp.cat.py -a f -b h -o h -d ff && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a  cat.log
python buildcpp.cat.py -a f -b h -o i8 -d ff && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a  cat.log
python buildcpp.cat.py -a f -b h -o i32 -d ff && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a  cat.log
python buildcpp.cat.py -a f -b h -o b -d ff && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a  cat.log

# f-i8-?
python buildcpp.cat.py -a f -b i8 -o f -d fi && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a  cat.log
python buildcpp.cat.py -a f -b i8 -o h -d fi && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log
python buildcpp.cat.py -a f -b i8 -o i8 -d fi && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log
python buildcpp.cat.py -a f -b i8 -o i32 -d fi && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log
python buildcpp.cat.py -a f -b i8 -o b -d fi && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log

# f-i32-?
python buildcpp.cat.py -a f -b i32 -o f -d fi && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log
python buildcpp.cat.py -a f -b i32 -o h -d fi && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log
python buildcpp.cat.py -a f -b i32 -o i8 -d fi && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log
python buildcpp.cat.py -a f -b i32 -o i32 -d fi && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log
python buildcpp.cat.py -a f -b i32 -o b -d fi && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log

# f-b-?
python buildcpp.cat.py -a f -b b -o f -d fb && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log
python buildcpp.cat.py -a f -b b -o h -d fb && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log
python buildcpp.cat.py -a f -b b -o i8 -d fb && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log
python buildcpp.cat.py -a f -b b -o i32 -d fb && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log
python buildcpp.cat.py -a f -b b -o b -d fb && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log

# h-h-?
python buildcpp.cat.py -a h -b h -o f -d ff && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log
python buildcpp.cat.py -a h -b h -o h -d ff && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log
python buildcpp.cat.py -a h -b h -o i8 -d ff && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log
python buildcpp.cat.py -a h -b h -o i32 -d ff && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log
python buildcpp.cat.py -a h -b h -o b -d ff && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log

# h-i8-?
python buildcpp.cat.py -a h -b i8 -o f -d fi && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log
python buildcpp.cat.py -a h -b i8 -o h -d fi && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log
python buildcpp.cat.py -a h -b i8 -o i8 -d fi && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log
python buildcpp.cat.py -a h -b i8 -o i32 -d fi && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log
python buildcpp.cat.py -a h -b i8 -o b -d fi && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log

# h-i32-?
python buildcpp.cat.py -a h -b i32 -o f -d fi && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log
python buildcpp.cat.py -a h -b i32 -o h -d fi && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log
python buildcpp.cat.py -a h -b i32 -o i8 -d fi && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log
python buildcpp.cat.py -a h -b i32 -o i32 -d fi && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log
python buildcpp.cat.py -a h -b i32 -o b -d fi && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log

# h-b-?
python buildcpp.cat.py -a h -b b -o f -d fb && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log
python buildcpp.cat.py -a h -b b -o h -d fb && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log
python buildcpp.cat.py -a h -b b -o i8 -d fb && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log
python buildcpp.cat.py -a h -b b -o i32 -d fb && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log
python buildcpp.cat.py -a h -b b -o b -d fb && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log

# i8-i8-?
python buildcpp.cat.py -a i8 -b i8 -o f -d ii && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log
python buildcpp.cat.py -a i8 -b i8 -o h -d ii && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log
python buildcpp.cat.py -a i8 -b i8 -o i8 -d ii && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log
python buildcpp.cat.py -a i8 -b i8 -o i32 -d ii && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log
python buildcpp.cat.py -a i8 -b i8 -o b -d ii && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log

# i8-i32-?
python buildcpp.cat.py -a i8 -b i32 -o f -d ii && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log
python buildcpp.cat.py -a i8 -b i32 -o h -d ii && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log
python buildcpp.cat.py -a i8 -b i32 -o i8 -d ii && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log
python buildcpp.cat.py -a i8 -b i32 -o i32 -d ii && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log
python buildcpp.cat.py -a i8 -b i32 -o b -d ii && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log

# i8-b-?
python buildcpp.cat.py -a i8 -b b -o f -d ib && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log
python buildcpp.cat.py -a i8 -b b -o h -d ib && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log
python buildcpp.cat.py -a i8 -b b -o i8 -d ib && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log
python buildcpp.cat.py -a i8 -b b -o i32 -d ib && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log
python buildcpp.cat.py -a i8 -b b -o b -d ib && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log

# i32-i32-?
python buildcpp.cat.py -a i32 -b i32 -o f -d ii && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log
python buildcpp.cat.py -a i32 -b i32 -o h -d ii && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log
python buildcpp.cat.py -a i32 -b i32 -o i8 -d ii && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log
python buildcpp.cat.py -a i32 -b i32 -o i32 -d ii && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log
python buildcpp.cat.py -a i32 -b i32 -o b -d ii && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log

# i32-b-?
python buildcpp.cat.py -a i32 -b b -o f -d ib && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log
python buildcpp.cat.py -a i32 -b b -o h -d ib && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log
python buildcpp.cat.py -a i32 -b b -o i8 -d ib && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log
python buildcpp.cat.py -a i32 -b b -o i32 -d ib && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log
python buildcpp.cat.py -a i32 -b b -o b -d ib && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log

# b-b-?
python buildcpp.cat.py -a b -b b -o f -d bb && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log
python buildcpp.cat.py -a b -b b -o h -d bb && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log
python buildcpp.cat.py -a b -b b -o i8 -d bb && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log
python buildcpp.cat.py -a b -b b -o i32 -d bb && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log
python buildcpp.cat.py -a b -b b -o b -d bb && sh $TRT_SOURCE/build/check.sh 2>&1 | tee -a cat.log
