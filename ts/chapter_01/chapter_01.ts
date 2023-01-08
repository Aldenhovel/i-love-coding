// 类型检查
let a0: string = "hello world";

// 函数类型检查，可以限制参数类型和返回类型
function sum(a: number, b: number): number {
    return a + b;
}
let res: number = sum(12, 34);
console.log(res);

// 类型
let a1: number = 10;
let a2: string = "hello world";
let a3: boolean = false;
let a4: "male" | "female" = "male";

// any
let a5: any = "hello";
let a51: number = a5;
console.log(typeof(a51));

// unknown
let e: unknown = 3; // 相当于不可以赋值的 any ，是安全的
//let n: number; n = e; 不合法，需要先类型断言
let n: number = <number>e; // let n: number = e as number;
console.log(n)


// void
function fn1(): void {
    console.log("this is fn1.");
}
fn1();

//never
function fn2(): never {
    throw new Error("oops!");
}
fn2();

// tuple
let t: [string, string] = ["hello", "world"];   // 元组，固定长度固定类型

