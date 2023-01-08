// 类对象限制
let Person: {
    name: string,
    sex: "male" | "female",
    age: number,
    intro?: string,             // intro 可有可无
    [propName: string]: any,    // 可以添加其他的属性成员
}

Person = {
    name: "LiMing",
    sex: "male",
    age: 19,
    intro: "He is a good person",
    school: "GDUT",
}

// 箭头函数限制
let fn: (a: number, b: number) => number;
fn = function (n1: number, n2: number) {
    return n1 + n2;
}

// 数组类型限制
let strArr: string[] = ["abc", "def", "xyz"];
let numArr: Array<number> = [1, 2, 3];

// 枚举类型实例
enum Gender {
    male,
    female,
}
let LiMing = {
    name: "LiMing",
    gender: Gender.male,
};

// 类型别名
type type1 = string;
type type2 = 1| 2| 3| 4| 5;
let a: type1 = "hello";
let b: type2 = 4;