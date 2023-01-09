// 类对象限制
var Person;
Person = {
    name: "LiMing",
    sex: "male",
    age: 19,
    intro: "He is a good person",
    school: "GDUT",
};
// 箭头函数限制
var fn;
fn = function (n1, n2) {
    return n1 + n2;
};
// 数组类型限制
var strArr = ["abc", "def", "xyz"];
var numArr = [1, 2, 3];
// 枚举类型实例
var Gender;
(function (Gender) {
    Gender[Gender["male"] = 0] = "male";
    Gender[Gender["female"] = 1] = "female";
})(Gender || (Gender = {}));
var LiMing = {
    name: "LiMing",
    gender: Gender.male,
};
var a = "hello";
var b = 4;
