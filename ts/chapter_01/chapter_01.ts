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
let a5: any;
let a6: unknown = "a";




