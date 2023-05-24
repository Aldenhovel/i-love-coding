import argparse

parser = argparse.ArgumentParser()

parser.add_argument(
        "-x",	# 参数缩写 -x
        "--x-data",	# 参数全称 --x-data
        help="input x data here.",	# 帮助信息
        type=str,	# 参数类型
        )

parser.add_argument(
        "-y",
        "--y-data",
        help="input y data here.",
        type=float,
        nargs="+",	# 允许传入多个参数值
        )

args = parser.parse_args()
x = args.x_data	# --x-data 对应 x_data
y = args.y_data	# --t-data 对应 y-data
print(x, type(x))
print(y, type(y))

"""
python argparse_demo.py --x-data abc --y-data 123 23
python argparse_demo.py -x abc -y 123 23

>>
abc <class 'str'>
[123.0, 23.0] <class 'list'>
"""