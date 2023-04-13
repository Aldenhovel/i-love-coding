"""
    example:
    $ python calc_loss.py -i f -o h -x kLOG

    -i input type:  {f: float, h: half, i8: int8_t, i32: int32_t, b: bool}
    -o output type: {f: float, h: half, i8: int8_t, i32: int32_t, b: bool}
    -x operation:   {kEXP, kLOG, ... }
"""
import argparse

parser = argparse.ArgumentParser()
parser.add_argument("-i", "--intype", default="")
parser.add_argument("-o", "--outtype", default="")
parser.add_argument("-x", "--option", default="")

args = parser.parse_args()

ca_in = args.intype
ca_out = args.outtype
op = args.option


gt_file = f"./f_f_{op}.txt"
ca_file = f"./{ca_in}_{ca_out}_{op}.txt"


def read_txt_file(file_path):
    with open(file_path) as file:
        data = file.readlines()
        data = [line.rstrip('\n') for line in data]
    return data


gt_values = read_txt_file(gt_file)
ca_values = read_txt_file(ca_file)
print("\n")
print(f"in: {ca_in} ---- out: {ca_out} ---- op: {op}")
print("\n")
print("GroundTruth:\toutput:{" + " / ".join(gt_values) + "}")
print("Candidate:\toutput:{" + " / ".join(ca_values) + "}")

assert len(gt_values) == len(ca_values)
loss, loss_pct = [], []
for ix, (gt_v, ca_v) in enumerate(zip(gt_values, ca_values)):
    gt_v = float(gt_v)
    ca_v = float(ca_v)
    if gt_v <= 100 and gt_v >=-100 and ca_v>=-100 and ca_v <= 100:
        loss.append(abs(gt_v - ca_v))


mse = sum([*map(lambda x: round(x**2, 10), loss)]) / len(loss)
loss = [*map(lambda x: str(round(x, 6)), loss)]
print("PrecisionLoss:\t" + " / ".join(loss) + f", mse={str(mse)}")
print("MeanSqureError:\t" + str(mse))
print("\n\n")
