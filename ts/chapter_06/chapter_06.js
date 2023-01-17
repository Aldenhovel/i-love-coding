// if else
var a = 10;
if (a < 10) {
    console.log("a < 10");
}
else if (a < 20) {
    console.log("10 <= a < 20");
}
else {
    console.log("a > 20");
}
// for
for (var i = 0; i < 10; i++) {
    console.log(i);
}
// for in
var arr = [11, 22];
for (var num in arr) {
    console.log(num);
}
// for of
// 除了支持 Array 还支持 String Map Sets 等数据结构的遍历
var str = "Hello";
for (var _i = 0, str_1 = str; _i < str_1.length; _i++) {
    var char = str_1[_i];
    console.log(char);
}
// forEach
var arr1 = [12, 34, 556];
arr1.forEach(function (value, index, array) {
    console.log(value);
});
// every
// 比较推荐用 .every 而非 .forEach 这里是对整个 Array 各个元素做判断，非 filter 或者 map 操作，因此返回 boolean
var res = arr1.every(function (value, index, array) {
    return value > 20;
});
console.log("".concat(arr1, " == every element > 20? == ").concat(res));
// filter
var filterArr = arr1.filter(function (value, index, array) {
    return value > 20;
});
console.log("".concat(arr1, " == filter element > 20 == ").concat(filterArr));
// map
var mapArr = arr1.map(function (value, index, array) {
    return value + 1;
});
console.log("".concat(arr1, " == map element += 1 == ").concat(mapArr));
