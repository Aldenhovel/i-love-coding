// 类型检查
var a0 = "hello world";
// 函数类型检查，可以限制参数类型和返回类型
function sum(a, b) {
    return a + b;
}
var res = sum(12, 34);
console.log(res);
// 类型
var a1 = 10;
var a2 = "hello world";
var a3 = false;
var a4 = "male";
// any
var a5 = "hello";
var a51 = a5;
console.log(typeof (a51));
// unknown
var e = 3; // 相当于不可以赋值的 any ，是安全的
//let n: number; n = e; 不合法，需要先类型断言
var n = e; // let n: number = e as number;
console.log(n);
// void
function fn1() {
    console.log("this is fn1.");
}
fn1();
//never
function fn2() {
    throw new Error("oops!");
}
fn2();
// tuple
var t = ["hello", "world"]; // 元组，固定长度固定类型
